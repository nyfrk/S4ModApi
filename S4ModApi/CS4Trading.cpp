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

BOOL CSettlers4Api::SetTradingRoute(DWORD sourceBuilding, DWORD destinationBuilding, DWORD player) {
	TRACE;

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // vtable
			/*04*/DWORD eventId; // 0x138D
			/*08*/DWORD sourceBuilding;
			/*0C*/DWORD destinationBuilding;
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
	if (!u1.eventStruct.CEvn_Logic_vtbl) return FALSE;
	u1.eventStruct.eventId = 0x138D;
	u1.eventStruct.sourceBuilding = sourceBuilding;
	u1.eventStruct.destinationBuilding = destinationBuilding;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}

BOOL CSettlers4Api::TradeGood(DWORD buidling, S4_GOOD_ENUM good, INT amount, DWORD player) {
	TRACE;

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // vtable
			/*04*/DWORD eventId; // 0x13BE
			/*08*/WORD good;
			/*0A*/WORD buidling;
			/*0C*/INT32 amount;
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
	u1.eventStruct.eventId = 0x138E;
	u1.eventStruct.good = (WORD)(good);
	u1.eventStruct.buidling = (WORD)buidling;
	u1.eventStruct.amount = amount;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}

BOOL CSettlers4Api::StoreGood(DWORD buidling, S4_GOOD_ENUM good, BOOL enable, DWORD player) {
	TRACE;

	DWORD vtbl = S4::GetInstance().GetNetEventVTbl(); // 00E4BA08
	if (!vtbl) return FALSE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

#pragma pack(push, 1)
	static union {
		struct EventStruct_t {
			/*00*/DWORD CEvn_Logic_vtbl; // vtable
			/*04*/DWORD eventId; // 0x13B4
			/*08*/WORD good;
			/*0A*/WORD buidling;
			/*0C*/INT32 enable;
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
	u1.eventStruct.eventId = 0x13B4;
	u1.eventStruct.good = (WORD)(good);
	u1.eventStruct.buidling = (WORD)buidling;
	u1.eventStruct.enable = enable;
	u1.eventStruct.tick = S4::GetInstance().GetCurrentTick();
	u1.eventStruct.player = (BYTE)localPlayer;

	return S4::GetInstance().SendNetEvent(&u1);
}

