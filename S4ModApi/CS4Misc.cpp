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
#include "md5.h"
#include "safemem.h"

HRESULT CSettlers4Api::GetMD5OfModule(HMODULE module, LPSTR out, SIZE_T sz) {
	TRACE;
	if (!out || !sz) return ERROR_BAD_ARGUMENTS;
	MD5 md5;
	WCHAR filename[MAX_PATH + 1];
	auto len = GetModuleFileNameW(module, filename, MAX_PATH);
	if (!len) return GetLastError();
	filename[len] = '\0';
	auto res = ComputeMD5(filename, &md5);
	if (!res) return res;
	md5.ToString(out, sz); // covert to string
	return ERROR_SUCCESS;
}

BOOL CSettlers4Api::IsEdition(S4_EDITION_ENUM edition) {
	TRACE;
	switch (edition) {
		case S4_EDITION_GOLD: return g_isGE;
		case S4_EDITION_HISTORY: return !g_isGE;
		default: return FALSE;
	}
}

HWND CSettlers4Api::GetHwnd() {
	TRACE;
	auto& pHwnd = S4::GetInstance().Hwnd;
	return (HWND)READ_AT(pHwnd);
}

HRESULT CSettlers4Api::GetHoveringUiElement(LPS4UIELEMENT out) {
	TRACE;
	if (out) {
		auto& ppUi = S4::GetInstance().HoveringUiElement;
		UiElement_t* pUi = (UiElement_t*)READ_AT(ppUi);
		if (pUi) {
			UiElement_t ui;
			memget_s(&ui, pUi, sizeof ui);
			out->x = ui.x;
			out->y = ui.y;
			out->w = ui.w;
			out->h = ui.h;
			out->id = ui.id;
			out->sprite = ui.sprite;
			return 0;
		}
	}
	return -1;
}
