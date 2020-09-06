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

#include "CMessageBox.h"
#include "Log.h"

CMessageBox::CMessageBox(LPCWSTR title, LPCWSTR message, INT x, INT y, INT w, INT h, DWORD flags) :
	CDialog(x,y,w,h,flags),
	m_windowRect(m_position),
	m_title(title),
	m_message(message),
	m_handler(nullptr),
	m_hideReason(CMessageBox_HideReason_Default) { TRACE; }

CMessageBox::HideReasonEnum CMessageBox::GetHideReason() {
	TRACE;
	return m_hideReason; 
}

void CMessageBox::SetHandler(LPMESSAGEBOXHANDLER h) {
	TRACE;
	m_handler = h;
}

BOOL CMessageBox::OnShow() { // do not call Hide() from here (will deadlock)
	TRACE;
	m_hideReason = CMessageBox_HideReason_NotHidden;
	return CDialog::OnShow();
}

BOOL CMessageBox::OnHide() { // do not call Show() from here (will deadlock)
	TRACE;
	m_hideReason = CMessageBox_HideReason_Method;
	return CDialog::OnHide();
}

BOOL CMessageBox::OnMouse(DWORD dwMouseButton, INT iX, INT iY, DWORD dwMsgId, HWND hwnd) {
	TRACE;
	UNREFERENCED_PARAMETER(dwMouseButton);
	UNREFERENCED_PARAMETER(hwnd);
		
	if (dwMsgId == WM_LBUTTONUP) {
		POINT p;
		p.x = iX;
		p.y = iY;
		if (PtInRect(&m_closeButton, p)) {
			Hide();
			m_hideReason = CMessageBox_HideReason_CloseButton;
			auto handler = m_handler;
			if (handler) {
				handler(this, CMessageBox_HideReason_CloseButton);
			}
		}
		else if (PtInRect(&m_okButton, p)) {
			Hide();
			m_hideReason = CMessageBox_HideReason_OkButton;
			auto handler = m_handler;
			if (handler) {
				handler(this, CMessageBox_HideReason_OkButton);
			}
		}
	}

	return TRUE;
}

BOOL CMessageBox::OnDraw(HDC hdc, const POINT* cursor, const RECT* client) {
	TRACE;

	UpdatePositionWithOffsetsFlags(m_windowRect, client);

	const RECT& rc = GetRect();
	const POINT& p = *cursor;

	HPEN borderPen = CreatePen(PS_SOLID, 2, RGB(41, 149, 204));

	              
	HFONT hfont = CreateFont(
		16, 
		0, 
		0, 
		0, 
		0, 
		0, 
		0, 
		0, 
		DEFAULT_CHARSET,
		OUT_TT_ONLY_PRECIS,
		0, 
		CLEARTYPE_QUALITY,//ANTIALIASED_QUALITY, 
		0, 
		"SegoeUI");

	
	SelectObject(hdc, GetStockObject(NULL_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	
	// white body
	SetDCBrushColor(hdc, RGB(255, 255, 255));
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	
	// gray bottom row
	SetDCBrushColor(hdc, RGB(240, 240, 240));
	Rectangle(hdc, rc.left, rc.bottom - 50 - 2, rc.right, rc.bottom);
	
	// blue upper row
	const int bluRowHeight = 25;
	auto UpperRowColor = RGB(41, 149, 204);
	SetDCBrushColor(hdc, UpperRowColor);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.top + bluRowHeight);
	
	RECT& closeButton = m_closeButton;
	closeButton.left = rc.right - 40 - 1;
	closeButton.top = rc.top;
	closeButton.right = rc.right - 1;
	closeButton.bottom = rc.top + 23;
	
	if (cursor && PtInRect(&closeButton, p)) {
		if (GetAsyncKeyState(VK_LBUTTON) < 0)
			SetDCBrushColor(hdc, RGB(241, 112, 122)); // red box on presseddown
		else
			SetDCBrushColor(hdc, RGB(232, 17, 35)); // red box on hover
		Rectangle(hdc, closeButton.left, closeButton.top, closeButton.right, closeButton.bottom);
	}
	
	// blue border
	SelectObject(hdc, borderPen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	
	// button in bottom right corner
	RECT& button = m_okButton;
	button.left = rc.right - 75 - 10;
	button.top = rc.bottom - 35 - 5;
	button.right = rc.right - 10;
	button.bottom = rc.bottom - 12;
	bool buttonHover = cursor && PtInRect(&button, p);
	DWORD buttonBackground;
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SelectObject(hdc, GetStockObject(DC_PEN));
	if (buttonHover) {
		if (GetAsyncKeyState(VK_LBUTTON) < 0) {
			buttonBackground = RGB(204, 228, 247);
			SetDCPenColor(hdc, RGB(0, 84, 153));
		}
		else {
			buttonBackground = RGB(229, 241, 251);
			SetDCPenColor(hdc, RGB(0, 120, 215));
		}
	}
	else {
		buttonBackground = RGB(225, 225, 225);
		SetDCPenColor(hdc, RGB(173, 173, 173));
	}
	SetDCBrushColor(hdc, buttonBackground);
	Rectangle(hdc, button.left, button.top, button.right, button.bottom);
	
	// close X in top left corner
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	SelectObject(hdc, GetStockObject(WHITE_PEN));
	int x = rc.right - 22, y = rc.top + 11;
	MoveToEx(hdc, x - 5, y - 5, NULL);
	LineTo(hdc, x + 6, y + 6);
	MoveToEx(hdc, x - 5, y + 5, NULL);
	LineTo(hdc, x + 6, y - 6);
	
	RECT titleRect;
	titleRect.left = rc.left + 5;
	titleRect.top = rc.top;
	titleRect.right = closeButton.left;
	titleRect.bottom = rc.top + bluRowHeight;
	SetBkColor(hdc, UpperRowColor);
	SetTextColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, hfont);
	DrawTextW(hdc, m_title.c_str(), -1, &titleRect, DT_LEFT | DT_NOCLIP | DT_END_ELLIPSIS | DT_SINGLELINE | DT_VCENTER);
	
	SetBkColor(hdc, buttonBackground);
	SetTextColor(hdc, RGB(0, 0, 0));
	DrawTextA(hdc, "OK", -1, &button, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	
	RECT bodyRect;
	bodyRect.left = rc.left + 10;
	bodyRect.top = rc.top + bluRowHeight + 15;
	bodyRect.right = rc.right - 10;
	bodyRect.bottom = rc.bottom - 50 - 2 - 15;
	SetBkColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, hfont);
	DrawTextW(hdc, m_message.c_str(), -1, &bodyRect, DT_LEFT | DT_END_ELLIPSIS | DT_WORDBREAK);
	
	DeleteObject(borderPen);
	DeleteObject(hfont);
	return 0;
}
