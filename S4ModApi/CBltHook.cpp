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

#include "CBltHook.h"

static hlib::CallPatch OnBltHook, OnSettlerIdHook;


static WORD currentlyRenderedSettlerId = 0; // S4_Main.exe+260583 - 89 85 E09BFFFF        - mov [ebp-00006420],eax


#pragma pack(push,1)
struct RenderSettlerDetails {
	/* 000 */ LPVOID unk0;
	/* 004 */ LPVOID unk1;
	/* 008 */ DWORD unk2[3];
	/* 014 */ WORD healthBubbleSprite;
	/* 016 */ WORD selectionMarkerSprite;
	/* 018 */ BYTE unk3[0x2B0];
	/* 2C8 */ BYTE type; // 1 == settler
	/* 2C9 */ DWORD unk4;
	/* 2CD */ DWORD direction;
};
#pragma pack(pop)

//BYTE __cdecl RenderSettlerHook(DWORD unk0, DWORD xpack, DWORD ypack, RenderSettlerDetails* details) {
//	SHORT x = HIWORD(xpack);
//	SHORT y = HIWORD(ypack);
//
//	return 0; // return orig return value
//}

BOOL __stdcall CBltHook::OnBlt(DWORD caller, DWORD ecx, DWORD edx, DWORD _0, DWORD _1, DWORD _2, DWORD _3, DWORD _4, DWORD _5, DWORD _6) {
	//TRACE; // we do not log this as it will be a mayor performance hit
	mutex.lock();
	auto observers = GetInstance().observers; // obtain a copy since the callbacks may modify the vector
	mutex.unlock();
	BOOL discard = false;

	S4BltParams params;

	params.caller = (decltype(params.caller))caller;
	params.imagePalette = (decltype(params.imagePalette))ecx;
	params.imageData = (decltype(params.imageData))edx;
	params.imageWidth = (decltype(params.imageWidth))_0;
	params.imageHeight = (decltype(params.imageHeight))_1;
	params.destX = (decltype(params.destX))_2;
	params.destY = (decltype(params.destY))_3;
	params.destClippingOffsetY = (decltype(params.destClippingOffsetY))_4;
	params.subSurface = (decltype(params.subSurface))_5;
	params.imageHighRes = (decltype(params.imageHighRes))_6;

	// some additional params to make the callback more useful
	INT32* GfxZoomTable = *(INT32**)(S4_Main + 0x10587A8); // This table is updated whenever the zoom level changes. If will map the source width (or height) of a gfx file to the correct destination width (or height)
	params.destWidth = GfxZoomTable[params.imageWidth] >> (_6 & 0x1F);
	params.destHeight = GfxZoomTable[params.imageHeight] >> (_6 & 0x1F);
	params.surfaceWidth = *(INT*)(S4_Main + 0xD691EC); // targets surface width (entire screen)
	params.surfaceHeight = *(INT*)(S4_Main + 0xD691F0); // targets surface height (entire screen)
	params.stride = *(INT*)(S4_Main + 0x105AAA0); // or calculate using stride = ((((surfaceWidth * bitsPerPixel) + 31) & ~31) >> 3)
	params.zoomFactor = **(DWORD**)(S4_Main + 0x10593B8);
	params.surface = *(WORD**)(S4_Main + 0x105A3D8); // this is usually same as _5, except when drawing buildings
	params.isFogOfWar = (ecx == S4_Main + 0x1208A98);

	// Get the settler id and sprite id by stack hacking
	switch (caller - S4_Main) {

		// Settler
	case 0x26121c: // coast building (like harbor or dock)
	case 0x261367: // dock worker doing its job animation
	case 0x2614c0: // settlers selection marker
	case 0x261578: // settlers unknown
	case 0x261636: // settlers health bubble
	case 0x261d06: // settlers

	// Waves
	case 0x26207b: // waves
		break;

	// Building
	case 0x262212: // building under construction (layer of phase 1)
	case 0x26241a: // building under construction (current layer)
	case 0x2624e5: // (military) buildings3
	case 0x26252e: // military buildings2
	case 0x2626a2: // buildingps (mostly input) pile of good (not for all buildings for some reason)
	case 0x262956: // settlers in military buildings (like towers, castles, etc)
	case 0x262a0c: // military buildings
	case 0x262b55: // The flag with the player chosen icon on military buildings
	case 0x262c69: // the player choosen icon on military buildings
	case 0x262d7b: // buildingps job effects (like steam for bakery)
	case 0x262e66: // building selection marker

	// Object
	case 0x263023: // objects, like grass, butterflies, trees, fishes, goods etc
	case 0x2630fc: // unknown

	// Founding Stone
	case 0x2631e1: // founding stones
		break;

	// Vehicle
	case 0x26344d: // building a vehicle (at vehicle hall or dock)
	case 0x2634c2: // ships
	case 0x263588: // the waves on moving ships
	case 0x263665: // ship selection marker
	case 0x263740: // ship ammo pie
	case 0x2637ef: // ship health bubble

	// Draw Terrain Bubbles
	case 0x2638c6: // bubbles when placing a building or changing the work area 
		break;
	default:
		break;
	}
	params.settlerId = currentlyRenderedSettlerId;
	params.spriteId = 0;

	// adapted from https://gist.github.com/chaidy/77785afbed38719e98508de5485583ca
	BITMAP bmp;
	bmp.bmType = 0;
	bmp.bmWidth = params.surfaceWidth;
	bmp.bmHeight = params.surfaceHeight;
	bmp.bmWidthBytes = params.stride;
	bmp.bmPlanes = 1;
	bmp.bmBitsPixel = 16;
	bmp.bmBits = params.surface;

	//HBITMAP hbm = CreateBitmapIndirect(&bmp);
	//HDC hdc = CreateCompatibleDC(NULL);
	//SelectObject(hdc, hbm);
	//params.destinationDc = hdc;
	
	//CreateBitmap(params.surfaceWidth, params.surfaceHeight,,16,params.surface)
	//params.destinationDc = CreateCompatibleDC(NULL);
	//GetDC
	//SelectObject(params.destinationDc, )
	//params.destinationDc

	for (auto& observer : observers) {
		discard |= ((LPS4BLTCALLBACK)observer.callback)(&params, discard);
	}

	//DeleteDC(hdc);
	//DeleteObject(hbm);

	return discard;
}

static void __declspec(naked) __onSettlerId() {
	__asm {
		mov[ebp - 0x6420], eax
		mov currentlyRenderedSettlerId, ax
		ret
	}

}

static void __declspec(naked) __onBlt() {
	__asm {
		push edx
		push ecx

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
		sub     esp, 128
		fsave [esp]

		push [esp + 296]
		push [esp + 296]
		push [esp + 296]
		push [esp + 296]
		push [esp + 296]
		push [esp + 296]
		push [esp + 296]
		push edx
		push ecx
		push [esp + 304]
		call CBltHook::OnBlt
		
		frstor [esp]
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

		test eax, eax

		pop ecx
		pop edx
		pop eax
		jnz lbl_skip_original

		// not skip original blt function

		inc eax
		push ebp // repair replaced instructions
		mov ebp, esp
		push eax // must push here since the next replaced instruction will overwrite eax
		mov eax, [ebp+8]

		lbl_skip_original:
		ret
	}
}

CBltHook& CBltHook::GetInstance() {
	static CBltHook inst;
	return inst;
}

bool CBltHook::Init() {
	TRACE;
	DWORD addr = g_Patterns.OnBltHook;
	if (!addr) return false;

	OnBltHook = hlib::CallPatch(addr, (DWORD)__onBlt);
	OnSettlerIdHook = hlib::CallPatch(S4_Main + 0x260583, (DWORD)__onSettlerId, 1); // TODO: make pattern

	return true;
}

void CBltHook::Patch() {
	TRACE;
	OnBltHook.patch();
	OnSettlerIdHook.patch();
}

void CBltHook::Unpatch() {
	TRACE;
	OnBltHook.unpatch();
	OnSettlerIdHook.unpatch();
}

CBltHook::CBltHook() { TRACE; }
