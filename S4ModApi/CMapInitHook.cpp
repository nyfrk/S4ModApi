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

#include "CMapInitHook.h"

static hlib::JmpPatch OnMapInitHook;
static DWORD backjmp;

DWORD __stdcall CMapInitHook::OnMapInit() {
	TRACE;
	mutex.lock();
	auto observers = GetInstance().observers; // obtain a copy since the callbacks may modify the vector
	mutex.unlock();
	for (auto& observer : observers) {
		((LPS4MAPINITCALLBACK)observer.callback)(0, 0);
	}
	return 0;
}

static void __declspec(naked) __onMapInitHE() {
	__asm {
		push ecx
		push edx

		call CMapInitHook::OnMapInit

		// the stuff we replaced
		lea ecx, [esi + 0x5c]

		mov eax, backjmp
		jmp eax
	}
}

static void __declspec(naked) __onMapInitGE() {
	__asm {
		// the stuff we replaced
		not ecx
		dec ecx
		mov edi, ecx

		call CMapInitHook::OnMapInit

		mov eax, backjmp
		jmp backjmp
	}
}

CMapInitHook& CMapInitHook::GetInstance() {
	static CMapInitHook inst;
	return inst;
}

bool CMapInitHook::Init() {
	TRACE;
	if (!g_Patterns.OnMapInitHook) return false;

	DWORD addr = g_Patterns.OnMapInitHook;
	OnMapInitHook = hlib::JmpPatch(addr, (DWORD)(g_isGE ? __onMapInitGE : __onMapInitHE));
	backjmp = addr + 5;

	return true;
}

void CMapInitHook::Patch() {
	TRACE;
	OnMapInitHook.patch();
}

void CMapInitHook::Unpatch() {
	TRACE;
	OnMapInitHook.unpatch();
}

CMapInitHook::CMapInitHook() { TRACE; }
