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

#pragma once

#include "windows.h"
#include <vector>
#include <mutex>
#include <string>
#include "S4ModApi.h"
#include "CDialog.h"

class CMessageBox;

typedef HRESULT(FAR S4HCALL* LPMESSAGEBOXHANDLER)(CMessageBox* messagebox, INT reason);

class CMessageBox : public CDialog {
public:
	enum HideReasonEnum : DWORD {
		CMessageBox_HideReason_Default, // default state, window is hidden per default
		CMessageBox_HideReason_NotHidden, // the window is not hidden (is visible)
		CMessageBox_HideReason_Method, // hide() method was called by user
		CMessageBox_HideReason_OkButton, // ok button was used
		CMessageBox_HideReason_CloseButton, // close button was used
	};

	CMessageBox(LPCWSTR title, LPCWSTR message, INT x, INT y, INT w, INT h, DWORD flags = 0);

	HideReasonEnum GetHideReason();
	void SetHandler(LPMESSAGEBOXHANDLER);

protected:
	virtual BOOL OnDraw(HDC hdc, const POINT *cursor, const RECT* client) override;
	virtual BOOL OnMouse(DWORD dwMouseButton, INT iX, INT iY, DWORD dwMsgId, HWND hwnd) override;
	virtual BOOL OnShow() override; // do not call Hide() from here (will deadlock)
	virtual BOOL OnHide() override; // do not call Show() from here (will deadlock)

private:
	CMessageBox(const CMessageBox&) = delete;
	CMessageBox& operator=(CMessageBox const&) = delete;

	std::wstring m_title, m_message;
	RECT m_closeButton, m_okButton, m_windowRect;
	HideReasonEnum m_hideReason;
	volatile LPMESSAGEBOXHANDLER m_handler;
};
