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
#include "s4.h"
#include "patterns.h"

#include "CSettlers4Api.h"
#include "CFrameHook.h"
#include "Console.h"

static hlib::JmpPatch OnFrameHook;
static DWORD* pBase = nullptr;

DWORD __stdcall CFrameHook::OnFrame() {
	TRACE;
	// cache the IsCurrentlyOnScreen results in this array
	BYTE s4_gui_state[S4_GUI_ENUM_MAXVALUE] = { 0 }; // 0 == unknown, 1 == visible, 2 == hidden
	if (pBase) {
		INT32 pillarboxWidth = 0;
		if (S4::GetInstance().PillarboxWidth) pillarboxWidth = *S4::GetInstance().PillarboxWidth;
		LPDIRECTDRAWSURFACE7 dst = (LPDIRECTDRAWSURFACE7)(*(DWORD*)(*(DWORD*)(*(DWORD*)(*pBase) + (g_isGE ? 0x3C : 0x5C)) + 0x4));
		mutex.lock();
		auto observers = GetInstance().observers; // obtain a copy since the callbacks may modify the vector
		mutex.unlock();
		for (auto& observer : observers) {
			auto& param = observer.param;
			if (param && param < S4_GUI_ENUM_MAXVALUE) {
				switch (s4_gui_state[param]) {
					case 0: {
						auto res = CSettlers4Api::GetInstance().IsCurrentlyOnScreen((S4_GUI_ENUM)param);
						s4_gui_state[param] = res ? 1 : 2;
						if (res) break; else continue;
					}
					case 1: break;
					default: continue;
				}			
			}
			((LPS4FRAMECALLBACK)observer.callback)(dst, pillarboxWidth, 0);
		}
	}
	return (DWORD)(OnFrameHook.getAddress() + 5);
}

static void __declspec(naked) __onFrame() {
	__asm {
		push ecx
		push edx
		call CFrameHook::OnFrame
		pop edx
		pop ecx
		pop edi
		pop esi
		cmp g_isGE, 0
		jz lbl_HE
		pop ebp // gold edition
		jmp lbl_end
		lbl_HE :
		pop ebx // history edition
			lbl_end :
		push eax
			mov al, 01
			ret
	}
}

CFrameHook& CFrameHook::GetInstance() {
	static CFrameHook inst;
	return inst;
}

bool CFrameHook::Init() {
	TRACE;
	if (!g_Patterns.OnFrameHook || !g_Patterns.Backbuffer) return false;

	OnFrameHook = hlib::JmpPatch(g_Patterns.OnFrameHook + 12, (DWORD)__onFrame);
	pBase = (DWORD*)(g_Patterns.Backbuffer + (g_isGE ? 34 : 22));

	return true;
}

void CFrameHook::Patch() {
	TRACE;
	OnFrameHook.patch();
}

void CFrameHook::Unpatch() {
	TRACE;
	OnFrameHook.unpatch();
}

CFrameHook::CFrameHook() { TRACE; }
