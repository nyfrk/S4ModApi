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

#if _DEBUG

#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <sstream>
#include <iomanip>
#include <iostream>

static FILE* g_ConsoleFile = NULL;

void InitConsole() {
	AllocConsole();
	g_ConsoleFile = NULL;
	freopen_s(&g_ConsoleFile, "conout$", "w", stdout);
}

void DestroyConsole() {
	if (g_ConsoleFile != NULL) {
		fclose(g_ConsoleFile);
		g_ConsoleFile = NULL;
	}
	FreeConsole();
}

HWND GetConsoleHwnd() { 
	// This snipped was taken from https://support.microsoft.com/de-ch/help/124103/how-to-obtain-a-console-window-handle-hwnd

	const unsigned MY_BUFSIZE = 1024; // Buffer size for console window titles.
	HWND hwndFound;         // This is what is returned to the caller.
	char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated WindowTitle
	char pszOldWindowTitle[MY_BUFSIZE]; // Contains original WindowTitle
	GetConsoleTitleA(pszOldWindowTitle, MY_BUFSIZE); // Fetch current window title.
	sprintf_s(pszNewWindowTitle, "%d/%d", // Format a "unique" NewWindowTitle.
		GetTickCount(),
		GetCurrentProcessId());
	SetConsoleTitleA(pszNewWindowTitle); // Change current window title.
	Sleep(40); // Ensure window title has been updated.
	hwndFound = FindWindowA(NULL, pszNewWindowTitle); // Look for NewWindowTitle.
	SetConsoleTitleA(pszOldWindowTitle); // Restore original window title.
	return hwndFound;
}

#endif