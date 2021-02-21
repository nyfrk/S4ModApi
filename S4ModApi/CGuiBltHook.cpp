///////////////////////////////////////////////////////////////////////////////
// GNU Lesser General Public License v3 (LGPL v3) 
//
// Copyright (c) 2020 nyfrk <nyfrk@gmx.net>
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

#include "CGuiBltHook.h"

static hlib::CallPatch OnComposeBltHook, OnSettlerIdHook;

BOOL __stdcall CGuiBltHook::OnBlt(DWORD id, LPVOID dstSurface, LPRECT dstRect, LPVOID srcSurface, LPRECT srcRect, DWORD ddbltFlags, LPVOID ddbltfx) {
	//TRACE; // we do not log this as it will be a mayor performance hit
	mutex.lock();
	auto observers = GetInstance().observers; // obtain a copy since the callbacks may modify the vector
	mutex.unlock();
	BOOL discard = false;
	S4GuiBltParams params;

	params.id = id / 4; // id goes from 0x130 (incl) to 0x167 (excl)
	params.dstSurface = dstSurface;
	params.dstRect = dstRect;
	params.srcSurface = srcSurface;
	params.srcRect = srcRect;
	params.ddbltFlags = ddbltFlags;
	params.ddbltfx = ddbltfx;

	for (auto& observer : observers) {
		discard |= ((LPS4GUIBLTCALLBACK)observer.callback)(&params, discard);
	}

	return discard;
}

static void __declspec(naked) __onBlt() {
	__asm {
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
		fsave[esp]

		push ecx
		push[esp + 256 + 4 + 20]
		push[esp + 256 + 4 + 20]
		push[esp + 256 + 4 + 20]
		push[esp + 256 + 4 + 20]
		push[esp + 256 + 4 + 20]
		push ecx
		push edi
		call CGuiBltHook::OnBlt
		pop ecx

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

		test al, al
		pushf
		xor eax, eax
		popf
		jnz lbl_skip_original
		push[esp + 20]
		push[esp + 20]
		push[esp + 20]
		push[esp + 20]
		push[esp + 20]
		call [esi + 0x18]

		lbl_skip_original:
		
		pop esi // ret addr
		add esp, 20 // clean the stack

		push esi
		test eax, eax
		ret
	}
}

CGuiBltHook& CGuiBltHook::GetInstance() {
	static CGuiBltHook inst;
	return inst;
}

bool CGuiBltHook::Init() {
	TRACE;
	/*
		S4_Main.exe+2647C6 - 8B 45 FC              - mov eax,[ebp-04]
		S4_Main.exe+2647C9 - 8B 15 08875401        - mov edx,[S4_Main.exe+1058708] { (04860720) }
		S4_Main.exe+2647CF - 8D 80 D8456E01        - lea eax,[eax+S4_Main.exe+11F45D8]
		S4_Main.exe+2647D5 - 8B 4A 5C              - mov ecx,[edx+5C]
		S4_Main.exe+2647D8 - 50                    - push eax
		S4_Main.exe+2647D9 - 8B 45 FC              - mov eax,[ebp-04]
		S4_Main.exe+2647DC - FF 34 17              - push [edi+edx]
		S4_Main.exe+2647DF - 8B 31                 - mov esi,[ecx]
		S4_Main.exe+2647E1 - 8D 80 B8466E01        - lea eax,[eax+S4_Main.exe+11F46B8]
		S4_Main.exe+2647E7 - 50                    - push eax
		S4_Main.exe+2647E8 - FF 56 18              - call dword ptr [esi+18]    <--- we hook here, 5 arguments + ecx
		S4_Main.exe+2647EB - 85 C0                 - test eax,eax

	*/


	DWORD addr = S4_Main != 0 ? S4_Main + 0x2647E8 : 0;
	if (!addr) return false;

	OnComposeBltHook = hlib::CallPatch(addr, (DWORD)__onBlt);
	
	return true;
}

void CGuiBltHook::Patch() {
	TRACE;
	OnComposeBltHook.patch();
}

void CGuiBltHook::Unpatch() {
	TRACE;
	OnComposeBltHook.unpatch();
}

CGuiBltHook::CGuiBltHook() { TRACE; }
