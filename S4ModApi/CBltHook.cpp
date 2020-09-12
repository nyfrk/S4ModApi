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

#include "CBltHook.h"

static hlib::CallPatch OnBltHook;

BOOL __stdcall CBltHook::OnBlt(DWORD caller, DWORD ecx, DWORD edx, DWORD _0, DWORD _1, DWORD _2, DWORD _3, DWORD _4, DWORD _5, DWORD _6) {
	//TRACE; // we do not log this as it will be a mayor performance hit
	mutex.lock();
	auto observers = GetInstance().observers; // obtain a copy since the callbacks may modify the vector
	mutex.unlock();
	BOOL discard = false;
	for (auto& observer : observers) {
		discard |= ((LPS4BLTCALLBACK)observer.callback)(ecx, edx, _0, _1, _2, _3, _4, _5, _6, discard, caller);
	}
	return discard;
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

	return true;
}

void CBltHook::Patch() {
	TRACE;
	OnBltHook.patch();
}

void CBltHook::Unpatch() {
	TRACE;
	OnBltHook.unpatch();
}

CBltHook::CBltHook() { TRACE; }
