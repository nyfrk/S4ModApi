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
#include <Windowsx.h> // GET_X_LPARAM, GET_Y_LPARAM
#include "s4.h"
#include "patterns.h"
#include "CMouseHook.h"
#include "CSettlers4Api.h"

static hlib::CallPatch OnMouseButtonHook, OnMouseWheelHookHE;

bool __stdcall CMouseHook::OnMouse(HWND hwnd, DWORD msg, DWORD wparam, DWORD lparam) {
	TRACE;
	S4UiElement uiElement;
	LPCS4UIELEMENT lpUiElement = 
		CSettlers4Api::GetInstance().GetHoveringUiElement(&uiElement) == 0 ? &uiElement : NULL;
	mutex.lock();
	auto observers = GetInstance().observers; // obtain a copy since the callbacks may modify the vector
	mutex.unlock();
	for (auto& observer : observers) {
		if (0 != ((LPS4MOUSECALLBACK)observer.callback)(wparam, (INT16)(GET_X_LPARAM(lparam)), (INT16)(GET_Y_LPARAM(lparam)), msg, hwnd, lpUiElement))
			return true;
	}
	return false;
}

static void __declspec(naked) __onMouseHE() {
	__asm {
		push eax
		push ecx
		push edx

		//push edi

		push[ebp - 0x04] // lparam
		push[ebp - 0x08] // wparam
		push[ebp - 0x0C] // msg
		push[ebp + 0x08] // hwnd
		call CMouseHook::OnMouse

		pop edx
		pop ecx
		test al, al
		pop eax
		jnz cancelEvent

		test eax, 0x08000000
		//mov ecx, [ebp - 4] // the opcodes we replaced
		//xor ecx, ebp

		ret

		cancelEvent :
		//cancel the event
		pop eax // remove the return address from stack
		pop edi
		pop esi
		pop ebx
		xor eax, eax
		mov esp, ebp
		pop ebp
		ret 16
	}
}

static void __declspec(naked) __onMouseGE() {
	__asm {
		push eax
		push edx

		push[esp + 0x2C] // lparam
		push[esp + 0x1C + 4] // wparam
		push[esp + 0x0C + 8] // msg
		push[esp + 0x28 + 12] // hwnd
		call CMouseHook::OnMouse

		pop edx
		test al, al
		pop eax
		jnz cancelEvent

		test eax, 0x08000000 // the opcode we replaced

		ret

		cancelEvent :
		pop eax // pop return address
		xor eax, eax
		pop edi
		pop esi
		pop ebp
		pop ebx
		pop ecx
		pop ecx
		ret 16
	}
}

CMouseHook& CMouseHook::GetInstance() {
	static CMouseHook inst;
	return inst;
}

bool CMouseHook::Init() {
	TRACE;
	if (!g_Patterns.OnMouseButtonHook) return false;

	DWORD addr = g_Patterns.OnMouseButtonHook + (g_isGE ? 19 : 20);
	DWORD addr2 = g_Patterns.OnMouseButtonHook + 68;
	OnMouseButtonHook = hlib::CallPatch(addr, (DWORD)(g_isGE ? __onMouseGE : __onMouseHE));
	OnMouseWheelHookHE = hlib::CallPatch(addr2, (DWORD)__onMouseHE); // this is not required for the GE as the original hook already catches that too.

	return true;
}

void CMouseHook::Patch() {
	TRACE;
	OnMouseButtonHook.patch();
	OnMouseWheelHookHE.patch();
}

void CMouseHook::Unpatch() {
	TRACE;
	OnMouseButtonHook.unpatch();
	OnMouseWheelHookHE.unpatch();
}

CMouseHook::CMouseHook() { TRACE; }
