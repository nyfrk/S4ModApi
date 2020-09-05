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
#include "safemem.h"

#include "CLuaOpenHook.h"

static hlib::JmpPatch OnLuaOpenHook;
static DWORD backjmp, origjmp;

DWORD __stdcall CLuaOpenHook::OnLuaOpen() {
	TRACE;
	mutex.lock();
	auto observers = GetInstance().observers; // obtain a copy since the callbacks may modify the vector
	mutex.unlock();
	for (auto& observer : observers) {
		((LPS4LUAOPENCALLBACK)observer.callback)();
	}
	return 0;
}

static void __declspec(naked) __onLuaOpenHE() {
	__asm {
		call origjmp
		call CLuaOpenHook::OnLuaOpen
		jmp backjmp
	}
}

CLuaOpenHook& CLuaOpenHook::GetInstance() {
	static CLuaOpenHook inst;
	return inst;
}

bool CLuaOpenHook::Init() {
	TRACE;
	if (!g_Patterns.OnLuaOpenHook) return false;

	DWORD addr = g_Patterns.OnLuaOpenHook;
	if (!addr) return false;
	addr += 30;
	DWORD off = READ_AT((LPCVOID)addr, 1);
	if (!off) return false;
	origjmp = addr + off + 5;
	backjmp = addr + 5;
	OnLuaOpenHook = hlib::JmpPatch(addr, (DWORD)(__onLuaOpenHE));

	return true;
}

void CLuaOpenHook::Patch() {
	TRACE;
	OnLuaOpenHook.patch();
}

void CLuaOpenHook::Unpatch() {
	TRACE;
	OnLuaOpenHook.unpatch();
}

CLuaOpenHook::CLuaOpenHook() { TRACE; }
