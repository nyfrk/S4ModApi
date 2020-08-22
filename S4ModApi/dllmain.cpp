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
#include "globals.h"
#include "Console.h"
#include "Log.h"
#include "module.h" // g_hModule

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved ) {
	UNREFERENCED_PARAMETER(lpReserved);

    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
		g_hModule = hModule;

		#if _DEBUG
			InitConsole();
			InitLogstream();
			LOG("S4ModApi.dll has been attached at " << HEXNUM(g_hModule) << '.');
		#endif

		{
			// check file name
			WCHAR exeFQFilename[MAX_PATH + 1]; // fully qualified file name of the process executable
			auto len = GetModuleFileNameW(NULL, exeFQFilename, MAX_PATH);
			exeFQFilename[len] = '\0';
			LPCWSTR exeFilename = exeFQFilename; // the filename of the process executable (without path)
			for (int i = len; i >= 0; i--) {
				auto c = exeFQFilename[i];
				if (c == '\\' || c == '/') {
					exeFilename = &(exeFQFilename[i + 1]);
					break;
				}
			}
			// is filename S4_Main.exe ?
			if (0 == wcscmp(L"S4_Main.exe", exeFilename)) {
				TRACE;

				// compute the md5 of the target and cache it
				ComputeMD5(exeFQFilename, &g_md5);

				#if _DEBUG
					char md5str[2 * MD5LEN + 1];
					g_md5.ToString(md5str, sizeof(md5str));
					LOG("MD5 of " << exeFilename << " is " << md5str << '.');
				#endif

				// prevent lib from beeing unloaded when we are not ready with cleanup yet
				// use FreeLibraryAndExitThread to unload it.
				HMODULE mod = IncreaseModuleRefcount(InitializeGlobals);
				if (mod) {
					// evade the loader lock (thread gets started as soon as it becomes attached, witch will
					// only happen if the loader lock is released - thus everything is loaded
					HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InitializeGlobals, mod, 0, NULL);
					if (!hThread) {
						DecreaseModuleRefcount(mod);
						return FALSE; // unload DLL
					} else {
						CloseHandle(hThread);
					}
				}
			}
		}

		break;
    case DLL_THREAD_ATTACH:
		LOG("thread attached");
		break;
    case DLL_THREAD_DETACH:
		LOG("thread detached");
		break;
    case DLL_PROCESS_DETACH:
		#ifdef _DEBUG
			LOG("S4ModApi.dll has been detached.");
			DestroyConsole();
			DestroyLogstream();
		#endif

        break;
    }
    return TRUE;
}

