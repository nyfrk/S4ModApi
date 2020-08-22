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
#include "CSettlerSendHook.h"

static hlib::CallPatch OnSettlerCommandHook;

bool __stdcall CSettlerSendHook::OnNewCommand(DWORD position, S4_MOVEMENT_ENUM command) {
	TRACE;
	mutex.lock();
	auto observers = GetInstance().observers; // obtain a copy since the callbacks may modify the vector
	mutex.unlock();
	for (auto& observer : observers) {
		if (((LPS4SETTLERSENDCALLBACK)observer.callback)(position, command, 0))
			return true;
	}
	return false;
}

static void __declspec(naked) __newCommand() {
	__asm {
		push eax
		push ecx
		push edx
		push esi
		cmp g_isGE, 0
		jz lbl_he
		push ebp // this is the position for the GE
		jmp lbl_cont
	lbl_he :
		push ebx // this is the position for the HE
	lbl_cont :
		call CSettlerSendHook::OnNewCommand
		pop edx
		pop ecx
		test al, al
		pop eax
		jz lbl_cont2
		mov eax, edi // cancel the command
	lbl_cont2 :
		sub edi, eax
		sar edi, 1
		test edi, edi
		ret
	}
}

CSettlerSendHook& CSettlerSendHook::GetInstance() {
	static CSettlerSendHook inst;
	return inst;
}

bool CSettlerSendHook::Init() {
	TRACE;
	if (!g_Patterns.OnSettlerCommandHook) return false;

	DWORD addr = g_Patterns.OnSettlerCommandHook;
	OnSettlerCommandHook = hlib::CallPatch(addr, (DWORD)__newCommand, 1);

	return true;
}

void CSettlerSendHook::Patch() {
	TRACE;
	OnSettlerCommandHook.patch();
}

void CSettlerSendHook::Unpatch() {
	TRACE;
	OnSettlerCommandHook.unpatch();
}

CSettlerSendHook::CSettlerSendHook() { TRACE; }
