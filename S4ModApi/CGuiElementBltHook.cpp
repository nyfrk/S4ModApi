///////////////////////////////////////////////////////////////////////////////
// GNU Lesser General Public License v3 (LGPL v3) 
//
// Copyright (c) 2022 nyfrk <nyfrk@gmx.net> and contributors
//
// This file is part of S4ModApi.
//
// S4ModApi is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// S4ModApi is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with S4ModApi. If not, see <https://www.gnu.org/licenses/lgpl-3.0>.
///////////////////////////////////////////////////////////////////////////////

#include "globals.h" // g_isGE, hProcess
#include "hlib.h" // JmpPatch
#include "patterns.h"
#include "safemem.h"

#include "CGuiElementBltHook.h"

static hlib::CallPatch OnBltHook;
DWORD OrigFunction; // you store the original function address here. Populate it before you install the call patch.

#pragma pack(push, 1)
struct GUIElement
{
	WORD x;						//0
	WORD y;						//2
	WORD width;					//4
	WORD height;				//6
	WORD mainTexture;			//8
	WORD valueLink;				//10
	WORD unknown;				//12
	WORD buttonPressedTexture;	//14
	DWORD textOffset;			//18
	WORD tooltipLink;			//20
	WORD tooltipLinkExtra;		//22
	BYTE imageStyle;			//24
	BYTE id;					//25
	//enum where the first 4 bits define which font style to use and last 4 bits define effects (Like pressed etc)
	BYTE textStyle;				//26
	BYTE effects;				//27
	WORD unknown4;				//28
	WORD showTexture;			//30
	WORD unknownData[3];		//32
		//sizeof == 36
};
struct GUIContainer
{
	WORD type;
	WORD x;
	WORD y;
	WORD width;
	WORD height;
	WORD mainTexture;
	WORD transparency;
	WORD containerPointer;
	//sizeof == 36
};
#pragma pack(pop)

#pragma optimize("", off)
BOOL __stdcall CGuiElementBltHook::OnElementBlt(DWORD _0, DWORD _1, DWORD uiContainer, DWORD surfaceWidth, DWORD surfaceHeight, DWORD uiElement) {
	//TRACE; // we do not log this as it will be a mayor performance hit
	UNREFERENCED_PARAMETER(_0);
	UNREFERENCED_PARAMETER(_1);
	mutex.lock();
	auto observers = GetInstance().observers; // obtain a copy of all the observers since the callbacks may modify the vector
	mutex.unlock();
	BOOL discard = false;
	S4GuiElementBltParams params; // create a struct at S4ModApi.h 

	const auto ptr = READ_AT((const void*)(S4_Main + 0xE94814));
	const auto val = READ_AT((const void*)(ptr + 0xC98));
	params.currentGFXCollection = (WORD)val;

	params.surfaceWidth = surfaceWidth;
	params.surfaceHeight = surfaceHeight;

	GUIElement* element = (GUIElement*)uiElement;
	GUIContainer* container = (GUIContainer*)uiContainer;
	char* text = (char*)(const void*)(S4_Main + 0x1065218 + (element->id * 300));
	params.containerType = container->type;
	params.mainTexture = element->mainTexture;
	params.buttonPressedTexture = element->buttonPressedTexture;
	params.x = element->x;
	params.y = element->y;
	params.textStyle = (S4_UI_TEXTSTYLE)element->textStyle;
	params.imageStyle = (S4_UI_TYPE)element->imageStyle;
	params.effects = (S4_UI_EFFECTS)element->effects;
	params.height = element->height;
	params.width = element->width;
	params.valueLink = element->valueLink;
	params.tooltipLink = element->tooltipLink;
	params.tooltipLinkExtra = element->tooltipLinkExtra;
	params.showTexture = element->showTexture;
	params.xOffset = container->x;
	params.yOffset = container->y;
	params.backTexture = container->mainTexture;
	if (element->textOffset) {
		params.text = (char*)element->textOffset;
	}
	else {
		params.text = text;
	}

	const auto tooltipMasterPtr = READ_AT((const void*)(S4_Main + 0x10540D8));
	const auto tooltipArrayPtr = READ_AT((const void*)(tooltipMasterPtr + 4));
	if (element->tooltipLinkExtra) {
		auto tooltipPtr = READ_AT((const void*)(tooltipArrayPtr + (element->tooltipLinkExtra * 4)));
		params.tooltipExtraText = (char*)(const void*)(tooltipPtr);
	}
	else {
		params.tooltipExtraText = "";
	}
	if (element->tooltipLink) {
		auto tooltipPtr = READ_AT((const void*)(tooltipArrayPtr + (element->tooltipLink * 4)));
		params.tooltipText = (char*)(const void*)(tooltipPtr);
	}
	else {
		params.tooltipText = "";
	}


	// iterate observers
	for (auto& observer : observers) {
		discard |= ((LPS4GUIDRAWCALLBACK)observer.callback)(&params, discard);
	}

	return discard;
}
#pragma optimize("", on)

static void __declspec(naked) __onHook() {
	__asm {
		// first we preserve all the xmm registers onto the stack. That are 128 bytes. 
		sub     esp, 16
		movdqu[esp], xmm0
		sub     esp, 16
		movdqu[esp], xmm1
		sub     esp, 16
		movdqu[esp], xmm2
		sub     esp, 16
		movdqu[esp], xmm3
		sub     esp, 16
		movdqu[esp], xmm4
		sub     esp, 16
		movdqu[esp], xmm5
		sub     esp, 16
		movdqu[esp], xmm6
		sub     esp, 16
		movdqu[esp], xmm7

		// second we preserve the fpu registers onto the stack. That are another 128 bytes.
		sub     esp, 128
		fsave[esp]

		// at this point we increased the stack by 260 bytes (don't forget to consider the pushed return address for the call instruction). We also did not change any registers.

		// preserve the ecx and edx registers. We need them to later call the original function that we replaced. We
		// cannot call it from c context since we cannot declare it as fastcall or any other calling convention.
		push edx
		push ecx

		// now we start preparing our hook procedure invocation. That means, we push all arguments right-to-left onto the stack. At this point we increased the stack by 268 bytes

		push[esp + 276]
		push[esp + 276] // note that the offset does not change as push already subtracts 4 from the esp register
		push[esp + 276]
		push esi
		push edx  // the additional registers get passed as arguments too
		push ecx
		call CGuiElementBltHook::OnElementBlt  // we call your stdcall hook procedure, this is allowed to change eax, ecx and edx as well as the xmm / fpu registers

		// since we cannot use fastcall to call the original function in the hook procedure, we must call it from assembler. 
		// first restore the edx and ecx registers we preserved before
		pop ecx
		pop edx

		// restore the fpu and mmu registers. 
		frstor[esp]
		add     esp, 128
		movdqu  xmm7, [esp]
		add     esp, 16
		movdqu  xmm6, [esp]
		add     esp, 16
		movdqu  xmm5, [esp]
		add     esp, 16
		movdqu  xmm4, [esp]
		add     esp, 16
		movdqu  xmm3, [esp]
		add     esp, 16
		movdqu  xmm2, [esp]
		add     esp, 16
		movdqu  xmm1, [esp]
		add     esp, 16
		movdqu  xmm0, [esp]
		add     esp, 16

		// now we test the return value from our hook procedure. If it is zero we call the original function now.
		// otherwise we skip it (so that an observer can basically decide to nop it). Return values are passed in the eax 
		// register. al is just the least significant byte of the eax register. 

		test al, al

		// if the return value is non-zero, we skip calling the original function
		jnz lbl_skip_original

		// the hook procedure decided that we want to call the original function. Note that
		// we cannot just call it now since there is the return address of the last call pushed
		// onto the stack. So we must either pop it temporary or repush all the arguments. 
		// when poping it, we must decide a register that we are allowed to modify without
		// the game noticing it. So we just repush all the arguments directly from stack.
		push[esp + 12]
		push[esp + 12]
		push[esp + 12]
		// ecx and edx are already prepared
		call OrigFunction

		// since this function is not really a fastcall, we must (as the caller) clean the stack. We do this by increasing the stack
		// pointer by 12 bytes
		add esp, 12

		lbl_skip_original:

		// at this point the stack is off by 4 bytes, which is because of the initially pushed return value. 
		// since the game wants to clean the stack, we can just ret now, which will pop the address from
		// the stack and copy it to the IP register. The game will then pop the 3 dwords it previously 
		// pushed onto the stack.

		ret
	}
}

CGuiElementBltHook& CGuiElementBltHook::GetInstance() {
	static CGuiElementBltHook inst;
	return inst;
}

bool CGuiElementBltHook::Init() {
	TRACE;

	DWORD addr = S4_Main != 0 ? S4_Main + 0x0027241C : 0;
	if (!addr) return false;
	OrigFunction = S4_Main + 0x272600;
	OnBltHook = hlib::CallPatch(addr, (DWORD)__onHook);

	return true;
}

void CGuiElementBltHook::Patch() {
	TRACE;
	OnBltHook.patch();
}

void CGuiElementBltHook::Unpatch() {
	TRACE;
	OnBltHook.unpatch();
}

CGuiElementBltHook::CGuiElementBltHook() { TRACE; }
