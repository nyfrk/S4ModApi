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

BOOL CSettlers4Api::ChangeGoodDistribution(S4_GOOD_ENUM good, S4_BUILDING_ENUM building, INT percent, DWORD ecosector, DWORD player) {
	TRACE;

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // vtable
			/*04*/DWORD eventId;
			/*08*/WORD building;
			/*0A*/WORD good;
			/*0C*/INT16 change;
			/*0E*/WORD ecosector;
			/*10*/DWORD tick; // 
			/*14*/BYTE flags; //  always 0 ?
			/*16*/BYTE __pad[3]; // ignored
			/*18*/DWORD settlersArray; // must be 0
			/*1C*/WORD sizeofArray; // always 0
			/*1E*/BYTE player; // 
		} eventStruct;
		BYTE eventStructBytes[32]; // event struct is at least 32 bytes
	} u1;
#pragma pack(pop)

	ZeroMemory(&u1, sizeof(u1));

	u1.eventStruct.CEvn_Logic_vtbl = vtbl; // 00E4BA08
	u1.eventStruct.eventId = 0x13A4;
	u1.eventStruct.good = (WORD)(good);
	u1.eventStruct.building = (WORD)(building);
	u1.eventStruct.change = (INT16)percent;
	u1.eventStruct.ecosector = (WORD)ecosector;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}

// positive offset means lower priority, negative offset means higher priority
BOOL CSettlers4Api::ChangeGoodPriority(S4_GOOD_ENUM good, INT offset, DWORD ecosector, DWORD player) {
	TRACE;

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // vtable
			/*04*/DWORD eventId;
			/*08*/INT16 offset;
			/*0A*/WORD good;
			/*0C*/DWORD ecosector;
			/*10*/DWORD tick; // 
			/*14*/BYTE flags; //  always 0 ?
			/*16*/BYTE __pad[3]; // ignored
			/*18*/DWORD settlersArray; // must be 0
			/*1C*/WORD sizeofArray; // always 0
			/*1E*/BYTE player; // 
		} eventStruct;
		BYTE eventStructBytes[32]; // event struct is at least 32 bytes
	} u1;
#pragma pack(pop)

	ZeroMemory(&u1, sizeof(u1));

	u1.eventStruct.CEvn_Logic_vtbl = vtbl; // 00E4BA08
	u1.eventStruct.eventId = 0x13A5;
	u1.eventStruct.good = (WORD)(good);
	u1.eventStruct.offset = (INT16)offset;
	u1.eventStruct.ecosector = ecosector;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}

