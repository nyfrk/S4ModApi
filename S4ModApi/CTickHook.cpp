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
#include "hlib.h" // CallPatch
#include "patterns.h"
#include "CTickHook.h"

static hlib::CallPatch OnTickHook;

bool __stdcall CTickHook::OnTick(DWORD tick, bool hasEvent) {
	TRACE;
	bool delay = false;

	mutex.lock();
	auto observers = GetInstance().observers; // obtain a copy since the callbacks may modify the vector
	mutex.unlock();
	for (auto& observer : observers) {
		delay |= (bool)(((LPS4TICKCALLBACK)observer.callback)(tick, hasEvent, delay));
	}
	return delay;
}

static void __declspec(naked) __onTick() {
	__asm {
		cmp g_isGE, 0
		jz lbl_he
		mov eax, [ecx] // only for ge
		lbl_he:
		mov eax, [eax + 0x0C]
		call eax
		push eax
		push ecx
		push edx
		movzx eax, al
		push eax
		push ebx // tick
		call CTickHook::OnTick
		pop edx
		pop ecx
		test al, al
		pop eax
		jz lbl_processEvent
		xor eax, eax
		lbl_processEvent :
		ret
	}
}

CTickHook& CTickHook::GetInstance() {
	static CTickHook inst;
	return inst;
}

bool CTickHook::Init() {
	TRACE;
	if (!g_Patterns.OnSettlerCommandHook) return false;

	DWORD addr = g_Patterns.OnTickHook + (g_isGE ? 6 : 8);
	OnTickHook = hlib::CallPatch(addr, (DWORD)__onTick);

	return true;
}

void CTickHook::Patch() {
	TRACE;
	OnTickHook.patch();
}

void CTickHook::Unpatch() {
	TRACE;
	OnTickHook.unpatch();
}

CTickHook::CTickHook() { TRACE; }
