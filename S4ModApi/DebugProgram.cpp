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

#include "windows.h"
#include "Console.h"
#include "S4ModApi.h"
#include <vector>
#include "DebugRender.h"
#include "CMessageBox.h"
#include "globals.h"
#include "Log.h"

#define DEBUG_KEY VK_F5
#define DEBUG_KEY_STR "F5"

extern "C" HRESULT __declspec(nothrow) S4HCALL S4HooksGetDebugData(UINT32 type, LPSTR buf, SIZE_T bufsize);

CMessageBox g_GreetingsMessageBox(
	L"g_GreetingsMessageBox", 
	L"It appears that you are running a debug build of the S4ModApi.dll.\n"
	"You should update it to a release build if you are not a developer or bug tester. "
	"See https://github.com/nyfrk/S4ModApi for proper release.\n\n"
	"You can press " DEBUG_KEY_STR " to toggle the console window. ", 100, 100, 450, 250);

void DebugProgramMain() {
	TRACE;

	//std::vector<S4HOOK> hooks;
	
	while (1) {
		TRACE;

		cout << endl << "** Welcome to the S4ModApi Debug Menu **" << endl << endl;
		
		{
			// print the patterns
			char* buf = new char[4096];
			cout << "$ S4HooksGetDebugData(0x80000000," << HEXNUM(buf) << "," << dec << 2048 << ")" << endl;
			auto ret = S4HooksGetDebugData(0x80000000, buf, 4096);
			cout << "  " << HEXNUM(ret) << endl;
			delete[] buf;
		}

		Sleep(1000);

		cout << "$ S4ApiCreate()" << endl;
		auto S4API = S4ApiCreate();
		if (S4API) {
			cout << "  success." << endl;
		} else {
			cout << "  failure." << endl;
			for (int t = 3; t >= 0; t--) {
				cout << "  will retry in " << dec << t << " seconds." << endl;
				Sleep(1000);
			}
			continue;
		}

		g_GreetingsMessageBox.Show();

		//{ 	cout << "$ " << HEXNUM(S4API) << "->AddFrameListener(" << HEXNUM(DebugFrameProc) << ")" << endl;
		//	auto res = S4API->AddFrameListener(DebugFrameProc);
		//	cout << "  " << dec << res << endl;
		//	hooks.push_back(res);
		//}

		while (GetAsyncKeyState(DEBUG_KEY) >= 0) {
			Sleep(100);

			if (GetAsyncKeyState(VK_MULTIPLY) < 0) {
				CMessageBox test(L"loL", L"Das ist eine test nachricht", 200, 200, 400, 150);
				test.Show();
				while (GetAsyncKeyState(VK_MULTIPLY) < 0) { Sleep(10); }
				cout << "Reason = " << dec << (DWORD)test.GetHideReason() << endl;
			}
		}
		while (GetAsyncKeyState(DEBUG_KEY) < 0) Sleep(10);

		//for (auto& hook : hooks) {
		//	cout << "$ " << HEXNUM(S4API) << "->RemoveListener(" << dec << (DWORD)hook << ")" << endl;
		//	auto res = S4API->RemoveListener(hook);
		//	cout << "  " << dec << res << endl;
		//}

		//hooks.clear();

		{ 	cout << "$ " << HEXNUM(S4API) << "->Release()" << endl;
			auto res = S4API->Release();
			cout << "  " << dec << res << endl; 
		}

		cout << endl << "** goodbye **" << endl << endl;


		Sleep(2000);

		HWND hwnd = GetConsoleHwnd();
		ShowWindow(hwnd, SW_HIDE);

		while (GetAsyncKeyState(DEBUG_KEY) >= 0) Sleep(100);
		while (GetAsyncKeyState(DEBUG_KEY) < 0) Sleep(10);

		ShowWindow(hwnd, SW_SHOW);
	}

}


#endif