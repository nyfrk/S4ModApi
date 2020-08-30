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

#pragma once

#include "S4ModApi.h"
#include "Log.h"

extern "C" { 

struct CSettlers4Api : public ISettlers4Api {
	/** IUnknown methods **/
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj); // defined in CS4Unknown.cpp
	STDMETHOD_(ULONG, AddRef) (THIS); // defined in CS4Unknown.cpp
	STDMETHOD_(ULONG, Release) (THIS); // defined in CS4Unknown.cpp

	/** ISettlers4Api methods **/
	STDMETHOD_(DWORD, GetLastError) (THIS);
	STDMETHOD_(LPVOID, GetDebugData) (THIS_ LPVOID reserved0, LPVOID reserved1); // defined in CS4Debug.cpp

	STDMETHOD(RemoveListener)(THIS_ S4HOOK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddFrameListener)(THIS_ LPS4FRAMECALLBACK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddUIFrameListener)(THIS_ LPS4FRAMECALLBACK, S4_GUI_ENUM); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddMapInitListener)(THIS_ LPS4MAPINITCALLBACK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddMouseListener)(THIS_ LPS4MOUSECALLBACK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddSettlerSendListener)(THIS_ LPS4SETTLERSENDCALLBACK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddTickListener)(THIS_ LPS4TICKCALLBACK); // defined in CS4Listeners.cpp

	STDMETHOD(GetMD5OfModule)(THIS_ HMODULE module, LPSTR out, SIZE_T sz); // defined in CS4Misc.cpp
	STDMETHOD_(BOOL, IsEdition)(THIS_ S4_EDITION_ENUM edition); // defined in CS4Misc.cpp
	STDMETHOD_(HWND, GetHwnd)(THIS_); // defined in CS4Misc.cpp
	STDMETHOD(GetHoveringUiElement)(THIS_ LPS4UIELEMENT); // defined in CS4Misc.cpp
	STDMETHOD_(BOOL, IsCurrentlyOnScreen)(THIS_ S4_GUI_ENUM); // defined in CS4Screen.cpp
	STDMETHOD_(BOOL, IsObjectOfType)(THIS_ WORD object, S4_OBJECT_TYPE type); // defined in CS4IsObjectType.cpp
	STDMETHOD_(BOOL, ClearSelection)(THIS); // defined in CS4Selection.cpp
	STDMETHOD_(BOOL, GetSelection)(THIS_ PWORD out, SIZE_T outlen, PSIZE_T selectionCount); // defined in CS4Selection.cpp
	STDMETHOD_(BOOL, RemoveSelection)(THIS_ PWORD settlers, SIZE_T settlerslen, PSIZE_T removedCount); // defined in CS4Selection.cpp
	STDMETHOD_(BOOL, StartBuildingPlacement)(THIS_ S4_OBJECT_TYPE building); // defined in CS4MenuEvents.cpp

	/** Settlers 4 NetEvents functions **/
	STDMETHOD_(BOOL, SendWarriors)(THIS_ INT x, INT y, S4_MOVEMENT_ENUM mode, PWORD warriors, SIZE_T countOfWarriors, DWORD player); // defined in CS4SendWarriors.cpp
	STDMETHOD_(BOOL, BuildBuilding)(THIS_ S4_OBJECT_TYPE buildingType, INT x, INT y, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, CrushBuilding)(THIS_ DWORD building, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, ToggleBuildingPriority)(THIS_ DWORD building, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, ToggleBuildingHalt)(THIS_ DWORD building, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingWorkarea)(THIS_ DWORD building, INT x, INT y, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingProduction)(THIS_ DWORD building, S4_OBJECT_TYPE good, INT amount, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingProductionPercentMode)(THIS_ DWORD building, BOOL enable, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingProductionPercentage)(THIS_ DWORD building, BYTE swords, BYTE bows, BYTE armors, BYTE racespecialweapons, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, CastSpell)(THIS_ DWORD priest, DWORD spell, INT x, INT y, DWORD player); // defined in CS4Casting.cpp
	STDMETHOD_(BOOL, GarrisonWarriors)(THIS_ DWORD building, DWORD player); // defined in CS4GarrisonWarriors.cpp
	STDMETHOD_(BOOL, UnGarrisonWarriors)(THIS_ DWORD building, INT column, BOOL bowman, DWORD player); // defined in CS4GarrisonWarriors.cpp
	STDMETHOD_(BOOL, ChangeGoodDistribution)(THIS_ S4_OBJECT_TYPE good, S4_OBJECT_TYPE building, INT percent, DWORD ecosector, DWORD player); // defined in CS4GoodDistribution.cpp
	STDMETHOD_(BOOL, ChangeGoodPriority)(THIS_ S4_OBJECT_TYPE good, INT offset, DWORD ecosector, DWORD player); // defined in CS4GoodDistribution.cpp
	STDMETHOD_(BOOL, RecruitWarriors)(THIS_ DWORD building, S4_OBJECT_TYPE unit, INT amount, DWORD player); // defined in CS4Recruit.cpp
	STDMETHOD_(BOOL, SetTradingRoute)(THIS_ DWORD sourceBuilding, DWORD destinationBuilding, DWORD player); // defined in CS4Trading.cpp
	STDMETHOD_(BOOL, TradeGood)(THIS_ DWORD buidling, S4_OBJECT_TYPE good, INT amount, DWORD player); // defined in CS4Trading.cpp
	STDMETHOD_(BOOL, StoreGood)(THIS_ DWORD buidling, S4_OBJECT_TYPE good, BOOL enable, DWORD player); // defined in CS4Trading.cpp

	STDMETHOD_(S4CUSTOMUI, ShowMessageBox)(THIS_ LPCWSTR title, LPCWSTR message, INT x, INT y, INT w, INT h); // defined in CS4Screen.cpp
	STDMETHOD_(S4CUSTOMUI, CreateCustomUiElement)(THIS_ LPCS4CUSTOMUIELEMENT);
	STDMETHOD_(BOOL, DestroyCustomUiElement)(THIS_ S4CUSTOMUI);
	STDMETHOD_(BOOL, HideCustomUiElement)(THIS_ S4CUSTOMUI);
	STDMETHOD_(BOOL, ShowCustomUiElement)(THIS_ S4CUSTOMUI);

	/** S4 Scripting **/
	STDMETHOD_(BOOL, RevealWorldMap)(THIS_ BOOL); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetZoom)(THIS_ DWORD level); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetWorldCursor)(THIS_ INT x, INT y); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, DeleteWorldCursor)(THIS); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, AddSettlers)(THIS_ S4_OBJECT_TYPE settler, DWORD amount, INT x, INT y, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, ShowTextMessage)(THIS_ LPCSTR message, DWORD icon, DWORD reserved); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GetLocalPlayer)(THIS); // defined in CS4Scripting.cpp
	STDMETHOD_(S4_OBJECT_TYPE, GetPlayerTribe)(THIS_ DWORD player = 0); // defined in CS4Scripting.cpp

	~CSettlers4Api();  // defined in CS4Singleton.cpp
	static CSettlers4Api& GetInstance(); // defined in CS4Singleton.cpp

private:
	CSettlers4Api(); // defined in CS4Singleton.cpp

	LONG m_refs;
};


}