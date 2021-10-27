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

#include "CFrameHook.h"
#include "CMapInitHook.h"
#include "CMouseHook.h"
#include "CSettlerSendHook.h"
#include "CTickHook.h"
#include "CLuaOpenHook.h"
#include "CBltHook.h"
#include "CEntityHook.h"
#include "CGuiBltHook.h"
#include "CGuiElementBltHook.h"
#include "CGuiClearHook.h"

extern "C" {

	HRESULT CSettlers4Api::RemoveListener(S4HOOK id) {
		TRACE;
		return CHook::RemoveListener(id);
	}

	S4HOOK CSettlers4Api::AddFrameListener(LPS4FRAMECALLBACK cb) {
		TRACE;
		return CFrameHook::GetInstance().AddListener(cb);
	}

	S4HOOK CSettlers4Api::AddUIFrameListener(LPS4FRAMECALLBACK cb, S4_GUI_ENUM param) {
		TRACE;
		return CFrameHook::GetInstance().AddListener(cb, param);
	}

	S4HOOK CSettlers4Api::AddMapInitListener(LPS4MAPINITCALLBACK cb) {
		TRACE;
		return CMapInitHook::GetInstance().AddListener(cb);
	}

	S4HOOK CSettlers4Api::AddMouseListener(LPS4MOUSECALLBACK cb) {
		TRACE;
		return CMouseHook::GetInstance().AddListener(cb);
	}

	S4HOOK CSettlers4Api::AddSettlerSendListener(LPS4SETTLERSENDCALLBACK cb) {
		TRACE;
		return CSettlerSendHook::GetInstance().AddListener(cb);
	}

	S4HOOK CSettlers4Api::AddTickListener(LPS4TICKCALLBACK cb) {
		TRACE;
		return CTickHook::GetInstance().AddListener(cb);
	}

	S4HOOK CSettlers4Api::AddLuaOpenListener(LPS4LUAOPENCALLBACK cb) {
		TRACE;
		return CLuaOpenHook::GetInstance().AddListener(cb);
	}

	S4HOOK CSettlers4Api::AddBltListener(LPS4BLTCALLBACK cb) {
		TRACE;
		return CBltHook::GetInstance().AddListener(cb);
	}

	S4HOOK CSettlers4Api::AddEntityListener(LPS4ENTITYCALLBACK cb) {
		TRACE;
		return CEntityHook::GetInstance().AddListener(cb);
	}

	S4HOOK CSettlers4Api::AddGuiBltListener(LPS4GUIBLTCALLBACK cb) {
		TRACE;
		return CGuiBltHook::GetInstance().AddListener(cb);
	}

	S4HOOK CSettlers4Api::AddGuiElementBltListener(LPS4GUIDRAWCALLBACK cb) {
		TRACE;
		return CGuiElementBltHook::GetInstance().AddListener(cb);
	}

	S4HOOK CSettlers4Api::AddGuiClearListener(LPS4GUICLEARCALLBACK cb) {
		TRACE;
		return CGuiClearHook::GetInstance().AddListener(cb);
	}
}
