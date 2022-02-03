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

#include "CSettlers4Api.h"
#include "patterns.h"
#include "globals.h"
#include "safemem.h"
#include "s4.h"
#include "hlib.h"

BOOL CSettlers4Api::GarrisonWarriors(DWORD building, DWORD player) {
	TRACE;

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // [2C] vtable
			/*04*/DWORD eventId; // [28] 0x13A7
			/*08*/DWORD buildingIndex; // [24]
			/*0C*/INT32 amount; // [20] Must be -1. Other values have no effect?
			/*10*/DWORD tick; // [1C]
			/*14*/BYTE flags; //  [18]  always 0x00 ?
			/*16*/BYTE __pad[3]; // [17] ignored
			/*18*/DWORD settlersArray; // [14] must be 0
			/*1C*/WORD sizeofArray; // [10] always 0
			/*1E*/BYTE player; // [E]
		} eventStruct;
		BYTE eventStructBytes[32]; // event struct is at least 32 bytes
	} u1;
#pragma pack(pop)

	ZeroMemory(&u1, sizeof(u1));
	u1.eventStruct.CEvn_Logic_vtbl = vtbl;
	u1.eventStruct.eventId = 0x13A7; // garrison event
	u1.eventStruct.buildingIndex = building;
	u1.eventStruct.amount = -1;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}

BOOL CSettlers4Api::UnGarrisonWarriors(DWORD building, INT column, BOOL bowman, DWORD player) {
	TRACE;

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // [2C] vtable
			/*04*/DWORD eventId; // [28] 0x13A8
			/*08*/WORD type;// 0==swordmen, 1==bowmen
			/*0A*/WORD buildingIndex; //
			/*0C*/INT32 unit; // index of the unit in the building to remove. Is in range 0..5. Use -1 to remove em all.
			/*10*/DWORD tick; // [1C]
			/*14*/BYTE flags; //  [18]  always 0x0f00 ?
			/*16*/BYTE __pad[3]; // [17] ignored
			/*18*/DWORD settlersArray; // [14] must be 0
			/*1C*/WORD sizeofArray; // [10] always 0
			/*1E*/BYTE player; // [E]
		} eventStruct;
		BYTE eventStructBytes[32]; // event struct is at least 32 bytes
	} u1;
#pragma pack(pop)

	ZeroMemory(&u1, sizeof(u1));
	u1.eventStruct.CEvn_Logic_vtbl = vtbl;
	u1.eventStruct.eventId = 0x13A8; // ungarrison event
	u1.eventStruct.type = (WORD)bowman;
	u1.eventStruct.buildingIndex = (WORD)building;
	u1.eventStruct.unit = column;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}


