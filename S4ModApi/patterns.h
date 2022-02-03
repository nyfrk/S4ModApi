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

#pragma once

#include <Windows.h>

struct PatternAddr {
	void Scan(LPCSTR name, DWORD base, LPCSTR basename, LPCSTR patternStr);

	DWORD addr;
	DWORD base;
	LPCSTR name;
	LPCSTR basename;
	
	operator bool() const;
	operator DWORD() const;
	operator LPCVOID() const;
	DWORD operator+(int off);
	DWORD operator-(int off);
};

extern struct Patterns {
	// Debug Rendering Patterns
	PatternAddr 
		OnMapInitHook,
		PillarboxWidth,
		OnFrameHook,
		Hwnd,
		Backbuffer,
		OnSettlerCommandHook,
		OnTickHook,
		OnMouseButtonHook,
		HoveringUiElement,
		MenuScreenObj,
		CurrentMenuScreen,
		GameMenusWndProc,
		WndProcChain,
		ActiveIngameMenu,
		SettlerFilter,
		ClearSelection,
		NetEventConstuctor,
		RecruitmentEventConstructor,
		LocalEvent,
		Lua,
		ShowTextMessage,
		OnLuaOpenHook,
		OnBltHook,

		BoxSelect,
		AltSelect,
		UnitsPerRightclick,
		SelectionMarkerBufferGetter,
		SelectionMarkerBufferSetter,
		HealthBubbleBufferGetter,
		HealthBubbleBufferSetter
		;

	void Scan();

	Patterns() = default;
private:
	Patterns(const Patterns&) = delete;
	Patterns& operator=(Patterns const&) = delete;
} g_Patterns;

