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

#include "CEntityHook.h"

static hlib::CallPatch OnEntityHook;

BOOL __stdcall CEntityHook::OnEntity() {
	return 0;
}

//static void __declspec(naked) __onEntity() {
//	// todo: add entity hook
//	__asm {
//		ret
//	}
//}

CEntityHook& CEntityHook::GetInstance() {
	static CEntityHook inst;
	return inst;
}

bool CEntityHook::Init() {
	TRACE;
	/*DWORD addr = g_Patterns.xxx;
	if (!addr) return false;

	OnEntityHook = hlib::CallPatch(addr, (DWORD)__onEntity);*/

	return true;
}

void CEntityHook::Patch() {
	TRACE;
	OnEntityHook.patch();
}

void CEntityHook::Unpatch() {
	TRACE;
	OnEntityHook.unpatch();
}

CEntityHook::CEntityHook() { TRACE; }


