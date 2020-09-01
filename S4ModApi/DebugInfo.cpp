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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h> // sprintf_s

#include "S4ModApi.h"
#include "patterns.h"
#include "globals.h"
#include "Log.h"

extern "C" HRESULT __declspec(nothrow) S4HCALL S4HooksGetDebugData(UINT32 type, LPSTR buf, SIZE_T bufsize) { 
	#pragma comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__ ",@100")  // undecorated
	#pragma comment(linker, "/EXPORT:" __FUNCDNAME__ ) // stdcall decorated
	TRACE;
	switch (type) {
	case 0x80000000:
		sprintf_s(buf, bufsize,
			"Detected %s Edition    \n"
			"Backbuffer           at 0x%X\n"
			"OnSettlerCommandHook at 0x%X\n"
			"OnTickHook           at 0x%X\n"
			"OnMouseButtonHook    at 0x%X\n"
			"HoveringUiElement    at 0x%X\n"
			"OnMapInitHook        at 0x%X\n"
			"PillarboxWidth       at 0x%X\n"
			"OnFrameHook          at 0x%X\n"
			"Hwnd                 at 0x%X\n"
			"MenuScreenObj       ´at 0x%X\n"
			"CurrentMenuScreen    at 0x%X\n"
			"GameMenusWndProc     at 0x%X\n"
			"WndProcChain         at 0x%X\n"
			"ActiveIngameMenu     at 0x%X\n"
			"NetEventConstuctor   at 0x%X\n"
			"RecruitmentEventCons at 0x%X\n"
			"LocalEvent           at 0x%X\n",
			(g_isGE ? "   Gold" : "History"),
			g_Patterns.Backbuffer.addr,
			g_Patterns.OnSettlerCommandHook.addr,
			g_Patterns.OnTickHook.addr,
			g_Patterns.OnMouseButtonHook.addr,
			g_Patterns.HoveringUiElement.addr,
			g_Patterns.OnMapInitHook.addr,
			g_Patterns.PillarboxWidth.addr,
			g_Patterns.OnFrameHook.addr,
			g_Patterns.Hwnd.addr,
			g_Patterns.MenuScreenObj.addr,
			g_Patterns.CurrentMenuScreen.addr,
			g_Patterns.GameMenusWndProc.addr,
			g_Patterns.WndProcChain.addr,
			g_Patterns.ActiveIngameMenu.addr,
			g_Patterns.NetEventConstuctor.addr,
			g_Patterns.RecruitmentEventConstructor.addr,
			g_Patterns.LocalEvent.addr
		);	
		LOG(endl << buf << endl);
		return 0;
	default: return -1;
	}
}
