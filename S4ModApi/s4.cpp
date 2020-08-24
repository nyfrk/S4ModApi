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

#include "s4.h"
#include "patterns.h" // patterns
#include "globals.h" // g_isGE
#include "safemem.h" // READ_AT
#include "Log.h"

static inline DWORD AddIfNotNull(DWORD sum, INT add) {
	if (sum) sum += add;
	return sum;
}
#define LOAD_PTR_OFF(dest, patternaddr, patternoffset, postderefoffset) dest = (decltype(dest))AddIfNotNull(READ_AT(patternaddr, patternoffset),postderefoffset)
#define LOAD_PTR(dest, patternaddr, patternoffset) LOAD_PTR_OFF(dest, patternaddr, patternoffset, 0)

void S4::Initialize() {
	TRACE;
	LOAD_PTR(		PillarboxWidth		, g_Patterns.PillarboxWidth		, 16					);
	LOAD_PTR(		HoveringUiElement	, g_Patterns.HoveringUiElement	, 14					);
	LOAD_PTR(		Hwnd				, g_Patterns.Hwnd				, g_isGE ? 1 : 3		);
	LOAD_PTR(		MenuScreenObj		, g_Patterns.MenuScreenObj		, 12					);
	LOAD_PTR(		CurrentMenuScreen	, g_Patterns.CurrentMenuScreen	, 17					);
	LOAD_PTR(		GameMenusWndProc	, g_Patterns.GameMenusWndProc	, -4					);
	LOAD_PTR(		WndProcChain		, g_Patterns.WndProcChain		, 6						);
	LOAD_PTR_OFF(	ActiveIngameMenu	, g_Patterns.ActiveIngameMenu	, 3	, 8					);
	LOAD_PTR(		SettlerPrototypes	, g_Patterns.SettlerFilter		, g_isGE ? 19 : 18		);
	LOAD_PTR_OFF(	Selection			, g_Patterns.SettlerFilter		, g_isGE ? 56 : 49, -4	);
	LOAD_PTR(		SettlerPool			, g_Patterns.SettlerFilter		, g_isGE ? -35 : -18	);
	LOAD_PTR(		LocalPlayer 		, g_Patterns.OnSettlerCommandHook, g_isGE ? -0x73 : -0x66);
	LOAD_PTR(		Tick, 
					g_isGE ? g_Patterns.OnSettlerCommandHook : g_Patterns.NetEventConstuctor, 
					g_isGE ? 0x87 : 4 );
	{	// __SendEvent
		DWORD addr = g_Patterns.OnSettlerCommandHook + (g_isGE ? 0xE9 : 0xC3);
		DWORD off = READ_AT((LPCVOID)addr, 1);
		if (addr && off)
			__SendNetEvent = (decltype(__SendNetEvent))(addr + off + 5);
		else
			__SendNetEvent = nullptr;
	}
	if (g_isGE) {
		LOAD_PTR(NetEventVTbl, g_Patterns.OnSettlerCommandHook, 0xC5);
		NetEventVTbl = READ_AT((LPCVOID)NetEventVTbl);
	} else {
		LOAD_PTR(NetEventVTbl, g_Patterns.RecruitmentEventConstructor, 8);
	}

}

S4& S4::GetInstance() {
	static S4 instance;
	return instance;
}

DWORD S4::GetLocalPlayer() { return READ_AT(LocalPlayer); }
DWORD S4::GetCurrentTick() { return READ_AT((LPCVOID)READ_AT((LPCVOID)AddIfNotNull(READ_AT(Tick), 0x18))); }
BOOL S4::SendNetEvent(LPCVOID event) { if (__SendNetEvent) { __SendNetEvent(event); return TRUE; } return FALSE; }
