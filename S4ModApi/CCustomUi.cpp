///////////////////////////////////////////////////////////////////////////////
// GNU Lesser General Public License v3 (LGPL v3) 
//
// Copyright (c) 2020 nyfrk <nyfrk@gmx.net>
// Copyright (c) 2020 Viciten
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

#include "CCustomUi.h"
#include "s4.h"
#include "Log.h"

#pragma comment(lib,"Msimg32") // AlphaBlend

CCustomUi::CCustomUi(LPCS4CUSTOMUIELEMENT param) : 
	CDialog(),
	m_flags(param->flags),
	m_screenFilter(param->screen),
	m_state(S4_CUSTOM_UI_UNSELECTED),
	m_handler(param->actionHandler),
	m_filterFunc(param->filter),
	m_visible(false){
	TRACE;
	m_rect.left = param->x;
	m_rect.top = param->y;
	m_hoverRect.left = param->x;
	m_hoverRect.top = param->y;
	m_selectedRect.left = param->x;
	m_selectedRect.top = param->y;
	m_selectedHoverRect.left = param->x;
	m_selectedHoverRect.top = param->y;
	auto mod = param->mod;
	if (param->szImg) {
		if (m_flags & S4_CUSTOMUIFLAGS_FROMRES_IMG) {
			m_hImg = (HBITMAP)LoadImageW(mod, param->szImg, IMAGE_BITMAP, 0, 0, 0);
		} else {
			m_hImg = (HBITMAP)LoadImageW(NULL, param->szImg, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		if (m_hImg) {
			BITMAP bm;
			GetObjectW(m_hImg, sizeof(bm), &bm);
			m_rect.right = m_rect.left + bm.bmWidth;
			m_rect.bottom = m_rect.top + bm.bmHeight;
		} else {
			LOG("LoadImageW failed with error " << dec << GetLastError());
		}
	} else { m_hImg = NULL; }
	if (param->szImgHover) {
		if (m_flags & S4_CUSTOMUIFLAGS_FROMRES_IMG) {
			m_hImgHover = (HBITMAP)LoadImageW(mod, param->szImgHover, IMAGE_BITMAP, 0, 0, 0);
		} else {
			m_hImgHover = (HBITMAP)LoadImageW(NULL, param->szImgHover, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		if (m_hImgHover) {
			BITMAP bm;
			GetObjectW(m_hImgHover, sizeof(bm), &bm);
			m_hoverRect.right = m_hoverRect.left + bm.bmWidth;
			m_hoverRect.bottom = m_hoverRect.top + bm.bmHeight;
		} else {
			LOG("LoadImageW failed with error " << dec << GetLastError());
		}
	} else { m_hImgHover = NULL; }
	if (param->szImgSelected) {
		if (m_flags & S4_CUSTOMUIFLAGS_FROMRES_IMG) {
			m_hImgSelected = (HBITMAP)LoadImageW(mod, param->szImgSelected, IMAGE_BITMAP, 0, 0, 0);
		} else {
			m_hImgSelected = (HBITMAP)LoadImageW(NULL, param->szImgSelected, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		if (m_hImgSelected) {
			BITMAP bm;
			GetObjectW(m_hImgSelected, sizeof(bm), &bm);
			m_selectedRect.right = m_selectedRect.left + bm.bmWidth;
			m_selectedRect.bottom = m_selectedRect.top + bm.bmHeight;
		} else {
			LOG("LoadImageW failed with error " << dec << GetLastError());
		}
	} else { m_hImgSelected = NULL; }
	if (param->szImgSelectedHover) {
		if (m_flags & S4_CUSTOMUIFLAGS_FROMRES_IMG) {
			m_hImgSelectedHover = (HBITMAP)LoadImageW(mod, param->szImgSelectedHover, IMAGE_BITMAP, 0, 0, 0);
		}
		else {
			m_hImgSelectedHover = (HBITMAP)LoadImageW(NULL, param->szImgSelectedHover, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		if (m_hImgSelectedHover) {
			BITMAP bm;
			GetObjectW(m_hImgSelectedHover, sizeof(bm), &bm);
			m_selectedHoverRect.right = m_selectedHoverRect.left + bm.bmWidth;
			m_selectedHoverRect.bottom = m_selectedHoverRect.top + bm.bmHeight;
		} else {
			LOG("LoadImageW failed with error " << dec << GetLastError());
		}
	} else { m_hImgSelectedHover = NULL; }
	m_position = m_rect;
}

CCustomUi::~CCustomUi() {
	std::lock_guard<decltype(m_bitmap_mtx)> lock(m_bitmap_mtx);
	if (m_hImg) DeleteObject(m_hImg);
	if (m_hImgHover) DeleteObject(m_hImgHover);
	if (m_hImgSelected) DeleteObject(m_hImgSelected);
	if (m_hImgSelectedHover) DeleteObject(m_hImgSelectedHover);
}

S4_CUSTOM_UI_ENUM CCustomUi::GetState() {
	TRACE;
	return m_state;
}

void CCustomUi::SetHandler(LPS4UICALLBACK h) {
	TRACE;
	m_handler = h;
}

BOOL CCustomUi::OnShow() { // do not call Hide() from here (will deadlock)
	TRACE;
	return CDialog::OnShow();
}

BOOL CCustomUi::OnHide() { // do not call Show() from here (will deadlock)
	TRACE;
	return CDialog::OnHide();
}

BOOL CCustomUi::OnMouse(DWORD dwMouseButton, INT iX, INT iY, DWORD dwMsgId, HWND hwnd) {
	TRACE;
	UNREFERENCED_PARAMETER(iX);
	UNREFERENCED_PARAMETER(iY);
	UNREFERENCED_PARAMETER(dwMouseButton);
	UNREFERENCED_PARAMETER(hwnd);

	if (!m_visible) return FALSE;

	if (dwMsgId == WM_LBUTTONUP) {
		bool isNewstate = false;
		auto newstate = m_state;

		switch (m_state) {
		case S4_CUSTOM_UI_UNSELECTED:
			newstate = S4_CUSTOM_UI_SELECTED;
			isNewstate = m_flags & S4_CUSTOMUIFLAGS_TYPE_TOGGLE;
			break;
		case S4_CUSTOM_UI_SELECTED:
			newstate = S4_CUSTOM_UI_UNSELECTED;
			isNewstate = true;
			break;
		case S4_CUSTOM_UI_HOVERING:
			newstate = S4_CUSTOM_UI_HOVERING_SELECTED;
			isNewstate = m_flags & S4_CUSTOMUIFLAGS_TYPE_TOGGLE;
			break;
		case S4_CUSTOM_UI_HOVERING_SELECTED:
			newstate = S4_CUSTOM_UI_HOVERING;
			isNewstate = true;
			break;
		}

		if (isNewstate) {
			m_state = newstate;
		}
		auto cbstate = newstate;
		auto handler = m_handler;
		if (handler) {
			handler(this, cbstate);
		}
	}

	return TRUE;
}

BOOL CCustomUi::OnDraw(HDC hdc, const POINT* cursor) {
	TRACE;

	if (m_screenFilter != S4_GUI_UNKNOWN) {
		m_visible = S4API->IsCurrentlyOnScreen(m_screenFilter);
		if (m_visible && NULL != m_filterFunc && !m_filterFunc(this)) {
			m_visible = false;
		}
	} else {
		m_visible = false;
	}

	if (!m_visible) {
		if (m_flags & S4_CUSTOMUIFLAGS_RESET_ON_HIDE) 
			m_state = S4_CUSTOM_UI_UNSELECTED;
		return FALSE;
	}

	const POINT& p = *cursor;
	bool newstate = false;	
	HBITMAP hBm = NULL;
	RECT *pRect = NULL;

	switch (m_state) {
		case S4_CUSTOM_UI_UNSELECTED: {
			if (m_hImgHover && PtInRect(&m_rect, p)) {
				newstate = true;
				m_state = S4_CUSTOM_UI_HOVERING;
				goto lbl_S4_CUSTOM_UI_HOVERING;
			}
		lbl_S4_CUSTOM_UI_UNSELECTED:
			if (GetAsyncKeyState(VK_LBUTTON) < 0) {
				if (m_hImgSelectedHover) {
					hBm = m_hImgSelectedHover;
					pRect = &m_selectedHoverRect;
				} else {
					if (m_hImgHover) {
						hBm = m_hImgHover;
						pRect = &m_hoverRect;
					} else {
						hBm = m_hImg;
						pRect = &m_rect;
					}
				}
			} else {
				hBm = m_hImg;
				pRect = &m_rect;
			}
			break;
		}
		case S4_CUSTOM_UI_SELECTED: {
			if (m_hImgSelectedHover && PtInRect(&m_selectedRect, p)) {
				newstate = true;
				m_state = S4_CUSTOM_UI_HOVERING_SELECTED;
				goto lbl_S4_CUSTOM_UI_HOVERING_SELECTED;
			}
		lbl_S4_CUSTOM_UI_SELECTED:
			if (GetAsyncKeyState(VK_LBUTTON) < 0) {
				if (m_hImgHover) {
					hBm = m_hImgHover;
					pRect = &m_hoverRect;
				} else {
					hBm = m_hImg;
					pRect = &m_rect;
				}
			} else {
				if (m_hImgSelected) {
					hBm = m_hImgSelected;
					pRect = &m_selectedRect;
				} else {
					hBm = m_hImg;
					pRect = &m_rect;
				}
			}
			break;
		}
		case S4_CUSTOM_UI_HOVERING: {
			if (!PtInRect(&m_hoverRect, p)) {
				newstate = true;
				m_state = S4_CUSTOM_UI_UNSELECTED;
				goto lbl_S4_CUSTOM_UI_UNSELECTED;
			}
		lbl_S4_CUSTOM_UI_HOVERING:
			if (GetAsyncKeyState(VK_LBUTTON) < 0) {
				if (m_hImgSelectedHover) {
					hBm = m_hImgSelectedHover;
					pRect = &m_selectedHoverRect;
				} else {
					if (m_hImgHover) {
						hBm = m_hImgHover;
						pRect = &m_hoverRect;
					} else {
						hBm = m_hImg;
						pRect = &m_rect;
					}
				}
			} else {
				if (m_hImgHover) {
					hBm = m_hImgHover;
					pRect = &m_hoverRect;
				} else {
					hBm = m_hImg;
					pRect = &m_rect;
				}
			}
			break;
		}
		case S4_CUSTOM_UI_HOVERING_SELECTED: {
			if (!PtInRect(&m_selectedHoverRect, p)) {
				newstate = true;
				m_state = S4_CUSTOM_UI_SELECTED;
				goto lbl_S4_CUSTOM_UI_SELECTED;
			}
		lbl_S4_CUSTOM_UI_HOVERING_SELECTED:
			if (GetAsyncKeyState(VK_LBUTTON) < 0) {
				if (m_hImgHover) {
					hBm = m_hImgHover;
					pRect = &m_hoverRect;
				} else {
					if (m_hImgSelectedHover) {
						hBm = m_hImgSelectedHover;
						pRect = &m_selectedHoverRect;
					} else {
						if (m_hImgSelected) {
							hBm = m_hImgSelected;
							pRect = &m_selectedRect;
						} else {
							hBm = m_hImg;
							pRect = &m_rect;
						}
					}
				}
			} else {
				if (m_hImgSelectedHover) {
					hBm = m_hImgSelectedHover;
					pRect = &m_selectedHoverRect;
				} else {
					if (m_hImgSelected) {
						hBm = m_hImgSelected;
						pRect = &m_selectedRect;
					} else {
						hBm = m_hImg;
						pRect = &m_rect;
					}
				}
			}
			break;
		}
	}

	if (!hBm || !pRect) {
		LOG("not blitting custom ui at " << HEXNUM(this) << ". hBm == " << HEXNUM(hBm))
		return FALSE;
	}

	INT pillarboxWidth = 0;
	if ((m_flags & S4_CUSTOMUIFLAGS_NO_PILLARBOX) == 0) {
		auto pPillarboxWidth = S4::GetInstance().PillarboxWidth;
		if (pPillarboxWidth) pillarboxWidth = *pPillarboxWidth;
	}

	LOG("pillarbox == " << dec << pillarboxWidth)
	m_position = *pRect;
	m_position.left += pillarboxWidth;
	m_position.right += pillarboxWidth;

	LOG("blitting custom ui at " << HEXNUM(this))

	HDC memDc = CreateCompatibleDC(hdc);
	if (memDc) {	
		std::lock_guard<decltype(m_bitmap_mtx)> lock(m_bitmap_mtx);
		SelectObject(memDc, hBm);
		auto width = m_position.right - m_position.left;
		auto height = m_position.bottom - m_position.top;
		if (m_flags & S4_CUSTOMUIFLAGS_TRANSPARENT) {
			BLENDFUNCTION fnc;
			fnc.BlendOp = AC_SRC_OVER;
			fnc.BlendFlags = 0;
			fnc.SourceConstantAlpha = 0xFF;
			fnc.AlphaFormat = AC_SRC_ALPHA;
			if (!AlphaBlend(hdc,
				m_position.left,
				m_position.top,
				width,
				height,
				memDc, 0, 0, width, height, fnc)) {
				LOG("AlphaBlend failed with error code " << dec << GetLastError())
			}
		} else {
			if (!BitBlt(hdc,
				m_position.left,
				m_position.top,
				width,
				height,
				memDc, 0, 0, SRCCOPY)) {
				LOG("BitBlt failed with error code " << dec << GetLastError())
			}
		}
		DeleteDC(memDc);
	} else { LOG("bad memory DC for " << HEXNUM(this)) }

	auto handler = m_handler;
	if (newstate && handler) {
		handler(this, m_state);
	}

	return 0;
}
