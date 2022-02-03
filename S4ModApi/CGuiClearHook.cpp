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

#include "CGuiClearHook.h"

static hlib::JmpPatch OnClearHook;
DWORD Orig; // you store the original function address here. Populate it before you install the call patch.
DWORD backJmp;

struct GUIContainer {
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

#pragma optimize("", off)
void __stdcall CGuiClearHook::OnClear(DWORD *surfaceContainer) {
	//TRACE; // we do not log this as it will be a mayor performance hit
	mutex.lock();
	auto observers = GetInstance().observers; // obtain a copy of all the observers since the callbacks may modify the vector
	mutex.unlock();
	BOOL discard = false;
	S4GuiClearParams params;
	GUIContainer *c = (GUIContainer*)surfaceContainer;
	params.surfaceWidth = c->width;
	params.surfaceHeight = c->height;
	params.x = c->x;
	params.y = c->y;
	params.surfaceId = c->type;

	// iterate observers
	for (auto& observer : observers) {
		discard |= ((LPS4GUICLEARCALLBACK)observer.callback)(&params, discard);
	}

	return;
}
#pragma optimize("", on)

static void __declspec(naked) __onHook() {
	__asm {
		call Orig


		push esi
		call CGuiClearHook::OnClear  // we call your stdcall hook procedure, this is allowed to change eax, ecx and edx as well as the xmm / fpu registers

		
		jmp backJmp
	}
}

CGuiClearHook& CGuiClearHook::GetInstance() {
	static CGuiClearHook inst;
	return inst;
}

bool CGuiClearHook::Init() {
	TRACE;

	const DWORD addr = S4_Main != 0 ? S4_Main + 0x0027227F : 0;
	if (!addr) return false;
	Orig = S4_Main + 0x25F000;
	backJmp = S4_Main + 0x00272284;
	OnClearHook = hlib::JmpPatch(addr, (DWORD)__onHook);

	return true;
}

void CGuiClearHook::Patch() {
	TRACE;
	OnClearHook.patch();
}

void CGuiClearHook::Unpatch() {
	TRACE;
	OnClearHook.unpatch();
}

CGuiClearHook::CGuiClearHook() { TRACE; }
