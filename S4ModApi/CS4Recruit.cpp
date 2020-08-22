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

BOOL CSettlers4Api::RecruitWarriors(DWORD building, S4_SETTLER_TYPE_ENUM unit, INT amount) {
	TRACE;

	static DWORD tickPtr = 0;
	static DWORD vtbl = 0;
	static DWORD sendEvent = 0;
	if (!sendEvent) {
		DWORD addr = g_Patterns.OnSettlerCommandHook + (g_isGE ? 0xE9 : 0xC3);
		DWORD off = READ_AT((LPCVOID)addr, 1);
		if (addr && off)
			sendEvent = addr + off + 5;
		else
			return FALSE;
	}
	if (!tickPtr) {
		tickPtr = READ_AT(g_Patterns.NetEventConstuctor, 4);
		if (!tickPtr) return FALSE;
	}
	if (!vtbl) {
		vtbl = READ_AT(g_Patterns.RecruitmentEventConstructor, 8);
		if (!vtbl) return FALSE;
	}

#pragma pack(push, 1)
			static union {
				struct EventStruct_t {
					/*00*/DWORD CEvn_Logic_vtbl; // vtable
					/*04*/DWORD eventId; // 0x13B7
					/*08*/WORD unit;  // 1D == swordman lv1, 1E == lv2 etc
					/*10*/WORD buildingIndex;  //
					/*0C*/INT32 amount; // put 100 for infinite
					/*10*/DWORD tick; // 
					/*14*/WORD flags; //  always 0xf500 ?
					/*16*/WORD __pad; // ignored
					/*18*/DWORD settlersArray; // must be 0
					/*1C*/WORD sizeofArray; // always 0
					/*1E*/BYTE dl; // always 1 ? high byte is ignored?
				} eventStruct;
				BYTE eventStructBytes[32]; // event struct is at least 32 bytes
			} u1;
#pragma pack(pop)

			ZeroMemory(&u1, sizeof(u1));
			u1.eventStruct.CEvn_Logic_vtbl = vtbl;
			u1.eventStruct.eventId = 0x13B7; // recruitment event
			u1.eventStruct.unit = (WORD)unit;
			u1.eventStruct.buildingIndex = (WORD)building;
			u1.eventStruct.amount = amount;
			u1.eventStruct.flags = 0xf500;
			u1.eventStruct.dl = 1;
			
			if (tickPtr) {
				auto stick = *(DWORD*)(tickPtr);
				if (stick) {
					stick = *(DWORD*)(stick + 0x18);
					if (stick) {
						stick = *(DWORD*)(stick);
						u1.eventStruct.tick = stick;
					}
				}
			}

			if (g_isGE) {
				// todo: needs implementation
			} else {
				__asm {
					// send the event just like the game would do it
					lea ecx, u1.eventStructBytes
					push ecx
					call sendEvent
				}
			}

	return TRUE;
}



