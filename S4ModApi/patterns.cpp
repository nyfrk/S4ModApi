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

#define WIN32_LEAN_AND_MEAN
#include "patterns.h"
#include "globals.h"
#include "hlib.h"
#include "Log.h"

PatternAddr::operator bool() const { return addr != NULL; }
PatternAddr::operator DWORD() const { return addr; }
PatternAddr::operator LPCVOID() const { return (LPCVOID)addr; }
void PatternAddr::Scan(LPCSTR pname, DWORD pbase, LPCSTR pbasename, LPCSTR patternStr) {
	TRACE;
	this->name = pname;
	this->basename = pbasename;
	this->base = pbase;
	this->addr = (DWORD)hlib::FindPattern(base, patternStr);

	static bool failed = false;
	if(this->addr == 0 && !failed) {
		failed = true;
		const std::string error = "Error, couldn't find pattern: \"" + std::string(pname) + "\"";
		MessageBox(nullptr, error.c_str(), "S4 - ModAPI", MB_OK);
	}
}
DWORD PatternAddr::operator+(int off) { return addr ? this->addr + off : 0; } // safe add
DWORD PatternAddr::operator-(int off) { return addr ? this->addr - off : 0; } // safe sub

#define SCAN_HE(a,b,c) a.Scan(#a"PatternHE",b,#b,c)
#define SCAN_GE(a,b,c) a.Scan(#a"PatternGE",b,#b,c)

void Patterns::Scan() {
	TRACE;
	if (g_isGE) {
		SCAN_GE(OnSettlerCommandHook, S4_Main, "2B F8 D1 FF 85 FF 0F 8E 01 01 00 00 33 D2 66 8B 10");
		SCAN_GE(OnTickHook, S4_Main, "8B 88 B0 00 00 00 8B 01 FF 50 0C 84 C0 0F 84 DB 00 00 00 56");
		SCAN_GE(OnMouseButtonHook, EventEngine, "6A 09 83 64 24 28 EF 5D 6A 12 FF 15 ? ? ? ? 0F BF C0 A9 00 00 00 08 74");
		SCAN_GE(HoveringUiElement, GuiEngine2, "83 C4 0C 0A C8 8B 44 24 14 88 4C 24 30 A3");
		SCAN_GE(OnMapInitHook, S4_Main, "F7 D1 49 8B F9 8D 4D 54 57 89 7C 24 20 FF 15 ? ? ? ? 84 C0 74 1C 8B CF");
		SCAN_GE(OnFrameHook, GfxEngine, "00 00 89 54 24 10 0F 82 4B FF FF FF 5F 5E 5D B0 01 5B 59 C3");
		SCAN_GE(Hwnd, GfxEngine, "A1 ? ? ? ? 83 EC 20 50 FF 15 ? ? ? ? 85 C0 74 08 B0 01 83 C4 20 C2 04 00");
		SCAN_GE(Backbuffer, GfxEngine, "12 8B ? ? ? ? 8D 9E ? ? ? ? 6A 00 8B 11 53 EB 29 8B 10 68");
		SCAN_GE(ClearSelection, S4_Main, "51 8B 15 ? ? ? ? 85 D2 0F 84 ? ? ? ? A1 ? ? ? ? 8B C8 2B");
		SCAN_GE(SettlerFilter, S4_Main, "66 8B 50 0C 8D 0C 89 8D 0C 4A 8D 14 89 8D 0C 51 8A 14 8D");
		SCAN_GE(BoxSelect, S4_Main, "D1 FA 83 FA 64 73 7A 8B 46 58 8B 6E 4C 33 C9");
		SCAN_GE(AltSelect, S4_Main, "D1 FA 83 FA 64 73 1A 8B 15");
		SCAN_GE(SelectionMarkerBufferGetter, GfxEngine, "BE ? ? ? ? 8B 4E 04 6A 00 DB 06 8B 04 8D");
		SCAN_GE(SelectionMarkerBufferSetter, GfxEngine, "8B 74 24 14 C1 E0 02 41 89 B0 ? ? ? ? 89");
		SCAN_GE(HealthBubbleBufferGetter, GfxEngine, "40 83 C2 14 3B C1 89 45 E8 89 55 D8 0F 8C ? ? ? ? A1 ? ? ? ? 85 C0 0F 84 ? ? ? ? 8A 0D ? ? ? ? 84 C9 74 60 33 FF 85 C0 0F 8E ? ? ? ?");
		SCAN_GE(HealthBubbleBufferSetter, GfxEngine, "89 98 ? ? ? ? 89 3D ? ? ? ? D9 44 24 10 DF 7C 24 14 8B 5C 24 14 89 98 ? ? ? ? 89 90 ? ? ? ? 89 B0 ? ? ? ? 89 88 ? ? ? ? 33 DB");
	}
	else {
		SCAN_HE(OnSettlerCommandHook, S4_Main, "2B F8 D1 FF 85 FF 0F 8E D7 00 00 00 0F B7 00");
		SCAN_HE(OnTickHook, S4_Main, "8B 88 D8 00 00 00 8B 01 8B 40 0C FF D0 84 C0 0F 84 9A 00 00 00");
		SCAN_HE(OnMouseButtonHook, S4_Main, "6A 12 83 E6 EF FF 15 ? ? ? ? 8B 4D 14 8B FE 98 83 CF 10 25 00 00 00 08");// , "74 15 5F 5E B0 01 5B 8B 4D FC 33 CD E8"); // This hook may be too chatty. Maybe we should use the same as the GE as the HE one seems to produce lots of false data. 
		SCAN_HE(HoveringUiElement, S4_Main, "B0 01 8B CF EB 02 32 C0 8B F9 0A D8 89 3D ? ? ? ? 85 FF 0F 84");
		SCAN_HE(OnMapInitHook, S4_Main, "51 52 8D 4E 5C E8 ? ? ? ? A1 ? ? ? ? 80 B8 CC 02 00 00 00");
		SCAN_HE(PillarboxWidth, S4_Main, "8D 14 CD 00 00 00 00 2B D1 0F 10 00 0F 11 04 95 ? ? ? ? E8 ? ? ? ? B0 01 5D C2 08 00");
		SCAN_HE(OnFrameHook, S4_Main, "81 FF 68 01 00 00 0F 82 61 FF FF FF B0 01 5F");
		SCAN_HE(Hwnd, S4_Main, "51 FF 35 ? ? ? ? FF 15 ? ? ? ? 85 C0 74 04 B0 01 59 C3");
		SCAN_HE(Backbuffer, S4_Main, "6A 08 8B 0C 07 8B 01 FF 50 34 6A 00 68 00 80 00 00 8B 45 FC 8B 15");
		SCAN_HE(ClearSelection, S4_Main, "A1 ? ? ? ? 8B 0D ? ? ? ? 2B C1 D1 F8 74 61 56 33 F6 85 C0 74 53");
		SCAN_HE(SettlerFilter, S4_Main, "83 E1 0F 6B D1 46 0F B7 48 0C 03 D1 8D 0C D2");
		SCAN_HE(NetEventConstuctor, S4_Main, "89 41 0C A1 ? ? ? ? C7 01 ? ? ? ? C6 41 14 00 85 C0 74 0E 8B 40 18 85 C0 74 07 8B 00 89 41 10 EB 07");
		SCAN_HE(RecruitmentEventConstructor, S4_Main, "88 45 F2 33 C0 C7 45 D4 ? ? ? ? C7 45 EC 00 00 00 00"); // +8
		SCAN_HE(MenuScreenObj, S4_Main, "0F B6 43 1F 8B 44 81 10 03 C1 8B 0D"); // +12
		SCAN_HE(CurrentMenuScreen, S4_Main, "8B 45 28 57 89 0D ? ? ? ? 89 15 ? ? ? ? A3 ? ? ? ?"); // +17
		SCAN_HE(GameMenusWndProc, S4_Main, "6A 00 57 83 EC 08"); // -4
		SCAN_HE(WndProcChain, S4_Main, "0F B7 07 8B 04 85 ? ? ? ? 85 C0 74 0B 6A 00"); // +6
		SCAN_HE(ActiveIngameMenu, S4_Main, "8B 34 8D ? ? ? ? 85 F6 0F 84 ? ? 00 00 A1 ? ? ? ? 8B 74 B0 0C 03 F0"); // +3
		SCAN_HE(LocalEvent, S4_Main, "50 8B CA E8 ? ? ? ? B0 01 8B 4D F4"); // +4
		SCAN_HE(Lua, S4_Main, "75 0D 50 E8 ? ? ? ? 83 C4 04 33 F6 EB 1B 50 6A 00 E8 ? ? ? ? 8B F0 83 C4 08 85 F6 75 0A B9 ? ? ? ? E8 ? ? ? ? 8B 15");
		SCAN_HE(ShowTextMessage, S4_Main, "55 8B EC 53 56 57 6A 24 8B F2 8B F9");
		SCAN_HE(OnLuaOpenHook, S4_Main, "89 5F 0C 89 5F 10 89 5F 14 89 5F 18 89 5F 04 89 5F 08 89 9F ? ? ? ? 89 3D ? ? ? ? E8"); // +30
		SCAN_HE(OnBltHook, S4_Main, "55 8B EC 8B 45 08 A3 ? ? ? ? 89 15 ? ? ? ? 8B 15 ? ? ? ? 89 0D ? ? ? ? 8B 4D 20 53 56 8B 34 82 8B 45 0C");
		SCAN_HE(BoxSelect, S4_Main, "D1 F8 83 F8 64 0F 83 84 00 00 00 8B C6 25 00 FF FF 00 89 45 F8 0F B7 04 59 8B 3C 85");
		SCAN_HE(AltSelect, S4_Main, "D1 F8 83 F8 64 73 10 8B 3D ? ? ? ? 43 3B 5D F0 0F 8C 01 FF FF FF 5F 5E 5B 33 C0 8B E5 5D C2 08 00");
		SCAN_HE(SelectionMarkerBufferGetter, S4_Main, "7C A3 EB 49 85 C0 7E 45 BE ? ? ? ? 90 8B 46 04 6A 00");
		SCAN_HE(SelectionMarkerBufferSetter, S4_Main, "8B 7D F0 8D 04 49 C1 E0 02 41 89 0D ? ? ? ? 89 B8 ? ? ? ? 8B 7D 10 89 B0 ? ? ? ? 8B 75 F4 89 B0 ? ? ? ? 8A 43 14 8B 4D 0C 84 C0");
		SCAN_HE(HealthBubbleBufferGetter, S4_Main, "85 C0 7E 3C BE ? ? ? ? 66 90 8B 56 10 8B 0D ? ? ? ? 83 C2 06 6A 00");
		SCAN_HE(HealthBubbleBufferSetter, S4_Main, "8B 4D 0C 89 90 ? ? ? ? 8B 55 FC 89 90 ? ? ? ? 8B 55 F0 89 90 ? ? ? ? 8B 55 F4 89 90 ? ? ? ? 8B 15 ? ? ? ? 89 B0 ? ? ? ? 8A 43 15 84 C0");			
	}
}

Patterns g_Patterns;
