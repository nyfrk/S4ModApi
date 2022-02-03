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

#if _DEBUG

#include "DebugRender.h"
#include "Console.h"

HRESULT S4HCALL DebugFrameProc(LPDIRECTDRAWSURFACE7 lpSurface, INT32 iPillarboxWidth, LPVOID lpReserved) {
	UNREFERENCED_PARAMETER(lpSurface);
	UNREFERENCED_PARAMETER(iPillarboxWidth);
	UNREFERENCED_PARAMETER(lpReserved);

	auto S4API = S4ApiCreate();
	if (!S4API) return 0;

	POINT p = { 0 };
	HWND hwnd = S4API->GetHwnd();
	const bool hasCursor = hwnd && GetCursorPos(&p) && ScreenToClient(hwnd, &p);

	//for (DWORD i = 0; i < S4_GUI_ENUM_MAXVALUE; i++) {
	//	if (S4API->IsCurrentlyOnScreen((S4_GUI_ENUM)i)) {
	//		cout << "  " << dec << i << " is on screen" << endl;
	//	}
	//}

	S4API->Release();
	return 0;
}

#endif