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
#include "globals.h"
#include "patterns.h"
#include "s4.h"
#include <cwchar>
#include "CHook.h"
#include "md5.h"
#include "CMessageBox.h"
#include "CUpdate.h"

bool g_isGE;

DWORD S4_Main = 0;
DWORD DDRAW = 0;
DWORD EventEngine = 0;
DWORD GuiEngine2 = 0;
DWORD GfxEngine = 0;
MD5 g_md5;

#if _DEBUG
void DebugProgramMain();
#endif

DWORD WINAPI InitializeGlobals(HMODULE mod) {
	TRACE;

	// find base addresses of modules of interest
	S4_Main = (DWORD)GetModuleHandleA(NULL);
	DDRAW = (DWORD)GetModuleHandleA("DDRAW");
	EventEngine = (DWORD)GetModuleHandleA("EventEngine"); // GE only
	GuiEngine2 = (DWORD)GetModuleHandleA("GuiEngine2"); // GE only
	GfxEngine = (DWORD)GetModuleHandleA("GfxEngine"); // GE only

	// set flag if we detect the presence of any dll that is used in the gold edition
	g_isGE = EventEngine || GuiEngine2 || GfxEngine; 

	// scan for patterns
	g_Patterns.Scan();

	// initialize pointers to game structs
	S4::GetInstance().Initialize();

	// initialize all instantiated hooks (others will be lazy initialized)
	CHook::InitAll();

	// Check for updates
	CUpdate::GetInstance().check();

#if _DEBUG
		DebugProgramMain();
#endif

	FreeLibraryAndExitThread(mod, 0); // decrements the reference counter
	return 0; // never reached
}
