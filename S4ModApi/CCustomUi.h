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

class CCustomUi;

class CCustomUi : public CDialog {
public:
	CCustomUi(LPCS4CUSTOMUIELEMENT);
	S4_CUSTOM_UI_ENUM GetState();
	void SetHandler(LPS4UICALLBACK);
	~CCustomUi();

protected:
	virtual BOOL OnDraw(HDC hdc, const POINT* cursor, const RECT* clientRect) override;
	virtual BOOL OnMouse(DWORD dwMouseButton, INT iX, INT iY, DWORD dwMsgId, HWND hwnd) override;
	virtual BOOL OnShow() override; // do not call Hide() from here (will deadlock)
	virtual BOOL OnHide() override; // do not call Show() from here (will deadlock)

private:
	CCustomUi(const CCustomUi&) = delete;
	CCustomUi& operator=(CCustomUi const&) = delete;

	S4_GUI_ENUM m_screenFilter;
	RECT m_rect, m_hoverRect, m_selectedRect, m_selectedHoverRect;
	HBITMAP m_hImg, m_hImgHover, m_hImgSelected, m_hImgSelectedHover;
	std::mutex m_bitmap_mtx;
	bool m_visible;

	S4_CUSTOM_UI_ENUM m_state;
	volatile LPS4UICALLBACK m_handler;
	volatile LPS4UIFILTERCALLBACK m_filterFunc;
};
