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
#include "CSettlers4Api.h"
#include <new> // new(std::nothrow)
#include <stdio.h> // sprintf_s

HRESULT __declspec(nothrow) S4HCALL S4CreateInterface(CONST GUID FAR* lpGUID, S4API FAR* lplpS4H) {
	#pragma comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__ ",@1") // undecorated
	#pragma comment(linker, "/EXPORT:" __FUNCDNAME__ ) // stdcall decorated
	TRACE;
	
	if (!lplpS4H) return E_POINTER;
	if (!lpGUID) {
		*lplpS4H = NULL;
		return E_POINTER;
	}

	if (S_OK == CSettlers4Api::GetInstance().QueryInterface(*lpGUID, (LPVOID*)lplpS4H)) return S_OK;

	//if (*lpGUID == IID_ISettlers4Api) {
	//	return ((*lplpS4H = new(std::nothrow) CSettlers4Api()) == nullptr) ? E_OUTOFMEMORY : S_OK;
	//}

	static bool showMessageBox = true;
	if (showMessageBox) {
		const char fmt[] = 
			"Error: Missing Interface in S4ModApi.dll (%s)\n\n"
			"It appears that you are attempting to run a mod that expects a newer "
			"interface. Please go to https://github.com/nyfrk/S4ModApi and download "
			"the latest version.\n\n\n"
			"Do you want to open the URL in your browser?\n\n"
			"Click Yes if you want me to open the Download Page.\n"
			"Click No if you want to continue (no more warnings are shown)\n"
			"Click Cancel to stop the process.\n";

		char buf[_countof(fmt) + 45*2]; // 45 is length of a uuid in characters
		const char* txt = buf;
		LPOLESTR uuidStr = NULL;

		if (S_OK != StringFromCLSID(*lpGUID, &uuidStr) || uuidStr == NULL) {
			txt = fmt;
		} else {
			sprintf_s(buf, fmt, uuidStr);
			CoTaskMemFree(uuidStr);
		}

		auto idc = MessageBoxA(
			NULL, 
			txt, 
			"S4ModApi.dll", 
			MB_YESNOCANCEL | MB_TASKMODAL | MB_SETFOREGROUND | MB_TOPMOST | MB_ICONERROR);

		switch (idc) {
		case IDNO:
			break;
		case IDYES:
			system("start https://github.com/nyfrk/S4ModApi/issues/1");
			Sleep(2000);
		default: // cancel
			ExitProcess(0);
		}
		
		showMessageBox = false;
	}
	
	*lplpS4H = NULL;
	return E_NOINTERFACE;
}