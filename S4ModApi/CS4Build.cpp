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
#include "hlib.h"

BOOL CSettlers4Api::BuildBuilding(S4_OBJECT_TYPE buildingType, INT x, INT y, DWORD player) {
	TRACE;

	if (buildingType < S4_OBJECT_BUILDING_INDEX || buildingType > S4_OBJECT_BUILDING_LAST) 
		return FALSE;

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // [2C] vtable
			/*04*/DWORD eventId; // [28] 0x13A1
			/*08*/DWORD buildingType; // [24] // 0x29 is medium house (basically settler type of building)
			/*0C*/WORD x; // [20] 
			/*0E*/WORD y;
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
	u1.eventStruct.eventId = 0x13A1; // build event
	u1.eventStruct.buildingType = (DWORD)buildingType - (DWORD)S4_OBJECT_BUILDING_INDEX +1;
	u1.eventStruct.x = (WORD)x;
	u1.eventStruct.y = (WORD)y;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}

BOOL CSettlers4Api::CrushBuilding(DWORD building, DWORD player) {
	TRACE;

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // [2C] vtable
			/*04*/DWORD eventId; // [28] 0x138A
			/*08*/DWORD buildingIndex;// [24]
			/*0C*/INT32 amount; // [20] Must be 0
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
	u1.eventStruct.eventId = 0x138A; // crush building event
	u1.eventStruct.buildingIndex = building;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}

BOOL CSettlers4Api::ToggleBuildingPriority(DWORD building, DWORD player) {
	TRACE;

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // [2C] vtable
			/*04*/DWORD eventId; // [28] 0x138C
			/*08*/DWORD buildingIndex;// [24]
			/*0C*/INT32 amount; // [20] Must be 0
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
	u1.eventStruct.eventId = 0x138C; // building priority event
	u1.eventStruct.buildingIndex = building;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}

BOOL CSettlers4Api::ToggleBuildingHalt(DWORD building, DWORD player) {
	TRACE;

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // [2C] vtable
			/*04*/DWORD eventId; // [28] 0x138B
			/*08*/DWORD buildingIndex;// [24]
			/*0C*/INT32 amount; // [20] Must be 0
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
	u1.eventStruct.eventId = 0x138B; // building halt event
	u1.eventStruct.buildingIndex = building;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}

BOOL CSettlers4Api::SetBuildingWorkarea(DWORD building, INT x, INT y, DWORD player) {
	TRACE;

	// note that you can set x and y however you like, no distance 
	// checks are performed. So use it carefully to avoiid cheating.

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // [2C] vtable
			/*04*/DWORD eventId; // [28] 0x1389
			/*08*/DWORD buildingIndex;// [24]
			/*0C*/WORD x; // [20]
			/*0E*/WORD y;
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
	u1.eventStruct.eventId = 0x1389; // building work area event
	u1.eventStruct.buildingIndex = building;
	u1.eventStruct.x = (WORD)x;
	u1.eventStruct.y = (WORD)y;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}

BOOL CSettlers4Api::SetBuildingProduction(DWORD building, S4_OBJECT_TYPE good, INT amount, DWORD player) {
	TRACE;

	// note that you can only produce goods the building can actually prodice.

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // [2C] vtable
			/*04*/DWORD eventId; // [28] 0x13A9
			/*08*/WORD buildingIndex;// [24]
			/*0A*/WORD good; // [20]
			/*0C*/INT amount; // 1,5,-1,100 
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
	u1.eventStruct.eventId = 0x13A9; // set building production event
	u1.eventStruct.buildingIndex = (WORD)building;
	u1.eventStruct.good = good - S4_OBJECT_GOOD_INDEX +1;
	u1.eventStruct.amount = amount;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}

BOOL CSettlers4Api::SetBuildingProductionPercentMode(DWORD building, BOOL enable, DWORD player) {
	TRACE;

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // [2C] vtable
			/*04*/DWORD eventId; // [28] 0x13AB
			/*08*/DWORD buildingIndex;// [24]
			/*0C*/DWORD disable; // Set FALSE to turn on and TRUE to turn off
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
	u1.eventStruct.eventId = 0x13AB; // set building production percent event
	u1.eventStruct.buildingIndex = (WORD)building;
	u1.eventStruct.disable = !enable;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}

BOOL CSettlers4Api::SetBuildingProductionPercentage(DWORD building, BYTE swords, BYTE bows, BYTE armors, BYTE racespecialweapons, DWORD player) {
	TRACE;

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // [2C] vtable
			/*04*/DWORD eventId; // [28] 0x13AA
			/*08*/DWORD buildingIndex;// [24]
			/*0C*/BYTE swords;
			/*0C*/BYTE bows;
			/*0C*/BYTE armors;
			/*0C*/BYTE raceSpecialWeapons; // ie axes, blowguns, backpacks
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
	u1.eventStruct.eventId = 0x13AA; // set building production percent event
	u1.eventStruct.buildingIndex = building;
	u1.eventStruct.swords = swords;
	u1.eventStruct.bows = bows;
	u1.eventStruct.armors = armors;
	u1.eventStruct.raceSpecialWeapons = racespecialweapons;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}
