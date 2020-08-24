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

// for some units (specialists) building is the eco sector number
BOOL CSettlers4Api::RecruitWarriors(DWORD building, S4_OBJECT_TYPE unit, INT amount, DWORD player) {
	TRACE;

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // vtable
			/*04*/DWORD eventId; // 0x13B7
			/*08*/WORD unit;  // 1D == swordman lv1, 1E == lv2 etc
			/*10*/WORD buildingIndex;  //
			/*0C*/INT32 amount; // put 100 for infinite
			/*10*/DWORD tick; // 
			/*14*/BYTE flags; //  always 0xf500 ?
			/*16*/BYTE __pad[3]; // ignored
			/*18*/DWORD settlersArray; // must be 0
			/*1C*/WORD sizeofArray; // always 0
			/*1E*/BYTE player; // 
		} eventStruct;
		BYTE eventStructBytes[32]; // event struct is at least 32 bytes
	} u1;
#pragma pack(pop)

	ZeroMemory(&u1, sizeof(u1));

	switch (unit) {
		case S4_OBJECT_SETTLER_CARRIER:
		case S4_OBJECT_SETTLER_DIGGER:
		case S4_OBJECT_SETTLER_BUILDER:
			u1.eventStruct.eventId = 0x13A3;  // civilian recruitment event
			u1.eventStruct.unit = (WORD)MAKE_SETTLER_INDEX(unit);
			//building is the eco sector id !!!
			break;
		case S4_OBJECT_SETTLER_SWORDSMAN_01:
		case S4_OBJECT_SETTLER_SWORDSMAN_02:
		case S4_OBJECT_SETTLER_SWORDSMAN_03:
		case S4_OBJECT_SETTLER_BOWMAN_01:
		case S4_OBJECT_SETTLER_BOWMAN_02:
		case S4_OBJECT_SETTLER_BOWMAN_03:
		case S4_OBJECT_SETTLER_MEDIC_01:
		case S4_OBJECT_SETTLER_MEDIC_02:
		case S4_OBJECT_SETTLER_MEDIC_03:
		case S4_OBJECT_SETTLER_AXEWARRIOR_01:
		case S4_OBJECT_SETTLER_AXEWARRIOR_02:
		case S4_OBJECT_SETTLER_AXEWARRIOR_03:
		case S4_OBJECT_SETTLER_BLOWGUNWARRIOR_01:
		case S4_OBJECT_SETTLER_BLOWGUNWARRIOR_02:
		case S4_OBJECT_SETTLER_BLOWGUNWARRIOR_03:
		case S4_OBJECT_SETTLER_SQUADLEADER:
		case S4_OBJECT_SETTLER_BACKPACKCATAPULTIST_01:
		case S4_OBJECT_SETTLER_BACKPACKCATAPULTIST_02:
		case S4_OBJECT_SETTLER_BACKPACKCATAPULTIST_03:
			u1.eventStruct.eventId = 0x13B7;  // barracks recruitment event
			u1.eventStruct.unit = (WORD)MAKE_SETTLER_INDEX(unit);
			break;
		case S4_OBJECT_SETTLER_SABOTEUR:
		case S4_OBJECT_SETTLER_PIONEER:
		case S4_OBJECT_SETTLER_THIEF:
		case S4_OBJECT_SETTLER_GEOLOGIST:
		case S4_OBJECT_SETTLER_GARDENER:
		//case S4_OBJECT_SETTLER_LANDSCAPER:
		//case S4_OBJECT_SETTLER_DARKGARDENER:
		//case S4_OBJECT_SETTLER_SHAMAN:
			u1.eventStruct.eventId = 0x13AF; // specialists recruitment event
			u1.eventStruct.unit = (WORD)MAKE_SETTLER_INDEX(unit);
			//building is the eco sector id !!!
			break;
		case S4_OBJECT_VEHICLE_WARSHIP:
		case S4_OBJECT_VEHICLE_FERRY:
		case S4_OBJECT_VEHICLE_TRANSPORTSHIP:
		case S4_OBJECT_VEHICLE_WARMACHINE:
		case S4_OBJECT_VEHICLE_CART:
		case S4_OBJECT_VEHICLE_FOUNDATION_CART:
			u1.eventStruct.eventId = 0x13B0; // vehicle recruitment event (shipyard, vehicle hall)
			u1.eventStruct.unit = (WORD)MAKE_VEHICLE_INDEX(unit);
			break;

		default: return FALSE; // currently not supported
	}

	u1.eventStruct.CEvn_Logic_vtbl = vtbl; // 00E4BA08
	u1.eventStruct.buildingIndex = (WORD)building;
	u1.eventStruct.amount = amount;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}



