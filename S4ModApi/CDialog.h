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
#include "S4ModApi.h"

#define DIALOG_RENDER_PRIORITY 100001

class CDialog {
public:
	const enum FeaturesEnum : unsigned { FeatureNone = 0, FeatureOnMouse = 1, FeatureOnDraw = 2, FeatureAll = 3 } DialogFeatures;

	CDialog(INT x, INT y, INT w, INT h, DWORD flags, FeaturesEnum = FeatureAll);
	CDialog(DWORD flags = 0, FeaturesEnum = FeatureAll);
	BOOL Show();
	BOOL Hide();
	BOOL IsShown() const;
	BOOL HasFeature(const FeaturesEnum &f) const;
	const RECT& GetRect() const;

	virtual ~CDialog();

protected:
	virtual BOOL OnDraw(HDC hdc, const POINT *cursor, const RECT* clientRect);
	virtual BOOL OnMouse(DWORD dwMouseButton, INT iX, INT iY, DWORD dwMsgId, HWND hwnd);
	virtual BOOL OnShow(); // do not call Hide() from here (will deadlock)
	virtual BOOL OnHide(); // do not call Show() from here (will deadlock)
	VOID UpdatePositionWithOffsetsFlags(const RECT& source, const RECT* clientRect);

	RECT m_position;
	DWORD m_flags;
	static S4API s4api;

private:
	CDialog(const CDialog&) = delete;
	CDialog& operator=(CDialog const&) = delete;

	volatile bool m_isShown;

	static void Cleanup();

	static void MaintainS4Api();
	void ModifyFeatureCounts(signed add);

	static std::mutex state_mutex;
	static std::condition_variable condIdle;
	static std::vector<CDialog*> pending_dialogs;
	static volatile enum State : unsigned { StateIdle, StateBusy, StateBusyCleanupRequired } state;
	static std::vector<CDialog*> dialogs; // how many messageboxes are visible
	static S4HOOK hFramehook, hMousehook;
	static unsigned countFramehook, countMousehook;

	static HRESULT S4HCALL OnFrameProc(LPDIRECTDRAWSURFACE7 lpSurface, INT32 iPillarboxWidth, LPVOID lpReserved);
	static HRESULT S4HCALL OnMouseProc(DWORD dwMouseButton, INT iX, INT iY, DWORD dwMsgId, HWND hwnd, LPCS4UIELEMENT lpUiElement);
};
