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

#include "CSettlers4Api.h"
#include "patterns.h"
#include "globals.h"
#include "safemem.h"
#include "s4.h"

BOOL CSettlers4Api::RevealWorldMap(BOOL enable) {
	TRACE;
	__asm {
		push enable 
		mov eax, S4_Main
		add eax, 0x1159D30
		mov ecx, eax
		mov eax,[eax]
		call [eax+0x28]
	}
	return TRUE;
}

BOOL CSettlers4Api::SetZoom(DWORD level) {
	TRACE;
	Event_t ev;
	ev.vtbl = (LPCVOID)0xCAA0E0;
	ev.eventId = 0x12;
	ev.param[1] = level;
	ev.tick = S4::GetInstance().GetCurrentTick();
	S4::GetInstance().SendLocalEvent(ev);
	return TRUE;
}

BOOL CSettlers4Api::SetWorldCursor(INT x, INT y) {
	TRACE;
	// todo: do not respawn the world cursor, if it is already available somewhere
	DWORD retVal;
	__asm {
		push y
		push x
		push 0x39 // world cursor effect identifier, see https://github.com/MuffinMario/Siedler-4-Script-und-Referenzen/blob/master/custom/LUA_S4_TABLES.txt#L1530
		mov eax, S4_Main
		add eax, 0x10540D0
		mov eax, [eax]
		mov ecx, [eax+0x24]
		mov eax, [ecx]
		call [eax + 0x28] // spawn effect
		mov ecx, S4_Main
		add ecx, 0xDABE2C
		mov [ecx], eax
		mov retVal, eax
	}
	return retVal;
}

BOOL CSettlers4Api::DeleteWorldCursor() {
	TRACE;
	// S4_Main.exe+1CB340 
	((DWORD(*)())(S4_Main + 0x1CB340))();
	return TRUE;
}

BOOL CSettlers4Api::AddSettlers(S4_OBJECT_TYPE settler, DWORD amount, INT x, INT y, DWORD player) {
	TRACE;
	if (!player) {
		player = S4::GetInstance().GetLocalPlayer();
	}
	DWORD settlertype = MAKE_SETTLER_INDEX(settler);
	__asm {
		push 01
		push amount
		push settlertype
		push player
		push y
		push x
		mov eax, S4_Main
		add eax, 0x182770
		call eax
	}
	return TRUE;
}

BOOL CSettlers4Api::ShowTextMessage(LPCSTR message, DWORD icon, DWORD reserved) {
	UNREFERENCED_PARAMETER(reserved);
	TRACE;
	__asm {
		push 0 // some invokations push always 0, lua stm pushes always 1
		push 0 // output param or ignored ?
		push 0 // output param or ignored ?
		mov ecx, message // c string
		mov edx, icon // icon, 0==red, 1==blue, .., 7==white, >8==! 
		mov eax, S4_Main
		add eax, 0x12A100
		call eax // fastcall, 3 params cdecl-style + ecx and edx
		add esp, 12
	}
	return TRUE;
}

DWORD CSettlers4Api::GetLocalPlayer() {
	TRACE;
	return S4::GetInstance().GetLocalPlayer();
}

S4_OBJECT_TYPE CSettlers4Api::GetPlayerTribe(DWORD player) {
	TRACE;
	if (!player) {
		player = S4::GetInstance().GetLocalPlayer();
	}
	if (player) {
		auto tribe = READ_AT((LPVOID)(S4_Main + 0x109B5D4 + 60 * player));
		if (tribe >= 0 && tribe <= 4) 
			return (S4_OBJECT_TYPE)(S4_OBJECT_TRIBE_INDEX + tribe);
	}
	return S4_OBJECT_TYPE::S4_OBJECT_TRIBE_NONE;
}
