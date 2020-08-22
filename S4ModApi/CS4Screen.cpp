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
#include "globals.h"
#include "s4.h"
#include "safemem.h"

#define __isSubMenuId_impl(a) __isMenuId_impl(a, true);

static bool __isScreen_impl(const char* sid) {
	TRACE;
	if (!sid) return false;
	const BYTE* id = (const BYTE*)sid;
	auto& s4 = S4::GetInstance();
	auto currentMenuScreen = READ_AT(s4.CurrentMenuScreen);
	if (!currentMenuScreen) return false;
	auto ecx = READ_AT(s4.MenuScreenObj);
	if (!ecx) return false;
	auto unk0 = READ_AT((LPVOID)(ecx + 0xC98)); // this seems to be always 0 ?
	auto unk1 = READ_AT((LPVOID)(ecx + unk0 * 4 + 0x2A4));
	while (*id != 0) {
		auto eax = READ_AT((LPVOID)(unk1 + 0x14 + *id * 4));
		if (eax == currentMenuScreen)
			return true;
		++id;
	}
	return false;
}

static bool __isScreen_impl(BYTE id) {
	TRACE;
	BYTE b[2] = { id, 0 };
	return __isScreen_impl((const char*)b);
}

static bool __isWndProc_impl(LPCVOID wndproc) {
	TRACE;
	if (!wndproc) return false;
	auto& s4 = S4::GetInstance();
	if (!s4.WndProcChain) return false;
	return READ_AT(&(s4.WndProcChain[0])) == (DWORD)wndproc;
}

static bool __isMenuId_impl(DWORD id, bool sub = false) {
	TRACE;
	auto& m = S4::GetInstance().ActiveIngameMenu;
	ActiveIngameMenu_t menu;
	return m && memget_s(&menu, m, sizeof menu)
		&& id == (sub ? menu.sub : menu.main);
}

BOOL CSettlers4Api::IsCurrentlyOnScreen(S4_GUI_ENUM screen) {
	TRACE_((LPCVOID)screen);
	switch (screen) {
	case S4_GUI_UNKNOWN: break;
	case S4_SCREEN_MAINMENU: return __isScreen_impl(0x2C);
	case S4_SCREEN_TUTORIAL:  return __isScreen_impl(0x30);
	case S4_SCREEN_ADDON: return __isScreen_impl(0x60); // // fixme: this is also used for random singleplayer maps screen
	case S4_SCREEN_MISSIONCD: return __isScreen_impl(0x38); // fixme: this is also used for map singleplayer select screen
	case S4_SCREEN_NEWWORLD: // fixme: needs a case
	case S4_SCREEN_NEWWORLD2: return __isScreen_impl(0x4C);
	case S4_SCREEN_SINGLEPLAYER: return __isScreen_impl(0x2E);
	case S4_SCREEN_MULTIPLAYER:  return __isScreen_impl(0x32);
	case S4_SCREEN_LOADGAME: return __isScreen_impl(0x2F);
	case S4_SCREEN_CREDITS: break; // fixme: needs a case
	case S4_SCREEN_ADDON_TROJAN: return __isScreen_impl(0x8B);
	case S4_SCREEN_ADDON_ROMAN: return __isScreen_impl(0x86);
	case S4_SCREEN_ADDON_MAYAN: return __isScreen_impl(0x85);
	case S4_SCREEN_ADDON_VIKING: return __isScreen_impl(0x89);
	case S4_SCREEN_ADDON_SETTLE: return __isScreen_impl(0x84);
	case S4_SCREEN_MISSIONCD_ROMAN: return __isScreen_impl(0x3B);
	case S4_SCREEN_MISSIONCD_VIKING: return __isScreen_impl(0x3D);
	case S4_SCREEN_MISSIONCD_MAYAN: return __isScreen_impl(0x3A);
	case S4_SCREEN_MISSIONCD_CONFL: return __isScreen_impl(0x39);
	case S4_SCREEN_SINGLEPLAYER_CAMPAIGN: return __isScreen_impl(0x27);
	case S4_SCREEN_SINGLEPLAYER_DARKTRIBE: return __isScreen_impl(0x29);
	case S4_SCREEN_SINGLEPLAYER_MAPSELECT_RANDOM: return __isScreen_impl(0x60); // fixme: see S4_SCREEN_ADDON
	case S4_SCREEN_SINGLEPLAYER_MAPSELECT_SINGLE: // fixme: needs a case
	case S4_SCREEN_SINGLEPLAYER_MAPSELECT_MULTI: // fixme: needs a case
	case S4_SCREEN_SINGLEPLAYER_MAPSELECT_USER: return __isScreen_impl(0x38); // fixme: see S4_SCREEN_MISSIONCD
	case S4_SCREEN_SINGLEPLAYER_LOBBY: return __isScreen_impl(0x1B); // fixme: this returns true if in multiplayer :/
	case S4_SCREEN_MULTIPLAYER_MAPSELECT_RANDOM: return __isScreen_impl(0x3C);
	case S4_SCREEN_MULTIPLAYER_MAPSELECT_MULTI: // fixme: needs a case
	case S4_SCREEN_MULTIPLAYER_MAPSELECT_USER:  return __isScreen_impl(0x37); // fixme: 0x37 is also used for mission descriptions of the MissionCD maps :/
	case S4_SCREEN_MULTIPLAYER_LOBBY: return __isScreen_impl(0x1B); // fixme: this returns true if in singleplayer :/
	case S4_SCREEN_LOADGAME_CAMPAIGN:// fixme: needs a case
	case S4_SCREEN_LOADGAME_MAP:// fixme: needs a case
	case S4_SCREEN_LOADGAME_MULTIPLAYER: return __isScreen_impl(0x2B);// fixme: this returns true if in any loadgame menu :/
	case S4_SCREEN_AFTERGAME_SUMMARY:  return __isScreen_impl(0x33);
	case S4_SCREEN_AFTERGAME_DETAILS:  return __isScreen_impl(0x36);
	case S4_SCREEN_INGAME: return __isWndProc_impl(S4::GetInstance().GameMenusWndProc);
	case S4_SCREEN_MISSION_DESCRIPTION: return __isScreen_impl("\x28\x37\x68\x8A"); // fixme: 0x37 is also used for multiplayer map selection :/
	case S4_MENU_EXTRAS_SAVE: return __isMenuId_impl(0x22);
	case S4_MENU_EXTRAS_MISSION:  return __isMenuId_impl(0x24);
	case S4_MENU_EXTRAS_CHATSETTINGS: return __isMenuId_impl(0x3B);
	case S4_MENU_EXTRAS_QUIT: return __isMenuId_impl(0x23);
	case S4_MENU_SETTINGS_GRAPHICS: return __isMenuId_impl(0x25);
	case S4_MENU_SETTINGS_AUDIO: return __isMenuId_impl(0x26);
	case S4_MENU_SETTINGS_GAME: return __isMenuId_impl(0x27);
	case S4_MENU_SETTINGS_NOTIFICATIONS: return __isMenuId_impl(0x28);
	case S4_MENU_BUILDINGS_FOUNDATION: return __isMenuId_impl(0xA);
	case S4_MENU_BUILDINGS_METAL: return __isMenuId_impl(0xB);
	case S4_MENU_BUILDINGS_FOOD: return __isMenuId_impl(0xC);
	case S4_MENU_BUILDINGS_MISC: return __isMenuId_impl(0xD);
	case S4_MENU_BUILDINGS_MISC_DECOSUB: return __isSubMenuId_impl(0x35);
	case S4_MENU_BUILDINGS_MILITARY: return __isMenuId_impl(0xE);
	case S4_MENU_SETTLERS_SUMMARY: return __isMenuId_impl(0x20);
	case S4_MENU_SETTLERS_WORKERS: return __isMenuId_impl(0x21);
	case S4_MENU_SETTLERS_SPECIALISTS: return __isMenuId_impl(0x1F);
	case S4_MENU_SETTLERS_SEARCH: return __isMenuId_impl(0x1E);
	case S4_MENU_GOODS_SUMMARY: return __isMenuId_impl(0x1C);
	case S4_MENU_GOODS_DISTRIBUTION: return __isMenuId_impl(0x1B);
	case S4_MENU_GOODS_PRIORITY: return __isMenuId_impl(0x1A);
	case S4_MENU_STATISTICS_WARRIORS: return __isMenuId_impl(0x1D);
	case S4_MENU_STATISTICS_LAND: return __isMenuId_impl(0x4C);
	case S4_MENU_STATISTICS_GOODS: return __isMenuId_impl(0x4D);
	case S4_MENU_UNITSELECTION_DONKEY: return __isMenuId_impl(0x2A);
	case S4_MENU_UNITSELECTION_MILITARY: return __isMenuId_impl(0x2E);
	case S4_MENU_UNITSELECTION_SPECIALISTS: return __isMenuId_impl(0x2D);
	case S4_MENU_UNITSELECTION_VEHICLES: return __isMenuId_impl(0x29);
	case S4_MENU_UNITSELECTION_FERRY: return __isMenuId_impl(0x2B);
	case S4_MENU_UNITSELECTION_TRADINGVEHICLE: return __isMenuId_impl(0x2A);
	case S4_MENU_UNITSELECTION_SUB_SPELLS: return __isSubMenuId_impl(0x39);
	case S4_MENU_UNITSELECTION_SUB_GROUPINGS: return __isSubMenuId_impl(0x38);
	case S4_MENU_SELECTION_SUB_TRADE: return __isSubMenuId_impl(0x36);
	case S4_MENU_SELECTION_SUB_BUILDVEHICLE: return __isSubMenuId_impl(0x34);
	case S4_MENU_SELECTION_SUB_BARRACKS: return __isSubMenuId_impl(0x31);
	default: break;
	}
	return FALSE;
}
