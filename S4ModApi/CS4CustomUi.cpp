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
#include "CMessageBox.h"
#include "CCustomUi.h"

static HRESULT S4HCALL OnMessageBoxHide(CMessageBox* messagebox, INT reason) {
	UNREFERENCED_PARAMETER(reason);
	delete messagebox;
	return 0;
}

S4CUSTOMUI CSettlers4Api::ShowMessageBox(LPCWSTR title, LPCWSTR message, INT x, INT y, INT w, INT h) {
	TRACE;
	auto mb = new CMessageBox(title,message,x,y,w,h);
	mb->SetHandler(OnMessageBoxHide);
	mb->Show();
	return mb;
}

S4CUSTOMUI CSettlers4Api::CreateCustomUiElement(LPCS4CUSTOMUIELEMENT arg) {
	TRACE;
	if (arg && arg->size == sizeof(*arg)) {
		auto cui = new CCustomUi(arg);
		cui->Show();
		return cui;
	}
	return NULL;
}

BOOL CSettlers4Api::DestroyCustomUiElement(S4CUSTOMUI arg) {
	TRACE;
	return HideCustomUiElement(arg); // TODO: calling delete may be harmful when calling from a S4UiCallbackProc
	if (arg) {
		delete arg;
	}
	return NULL;
}

BOOL CSettlers4Api::HideCustomUiElement(S4CUSTOMUI arg) {
	TRACE;
	if (arg) {
		auto diag = (CDialog*)arg;
		diag->Hide();
		return TRUE;
	} else {
		return FALSE;
	}
}

BOOL CSettlers4Api::ShowCustomUiElement(S4CUSTOMUI arg) {
	TRACE;
	if (arg) {
		auto diag = (CDialog*)arg;
		diag->Show();
		return TRUE;
	} else {
		return FALSE;
	}
}

