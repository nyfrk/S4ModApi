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

#include <Windows.h>
#include <atomic>
#include "md5.h"

extern bool g_isGE; // true if gold edition, false if history edition.

extern DWORD S4_Main; // base address of S4_Main.exe
extern DWORD DDRAW; // base address of DDRAW.dll
extern DWORD EventEngine; // base address of EventEngine.dll. This is only present in the gold edition.
extern DWORD GuiEngine2; // base address of GuiEngine2.dll. This is only present in the gold edition.
extern DWORD GfxEngine; // base address of GfxEngine.dll. This is only present in the gold edition.
extern MD5 g_md5; // md5 of the exe
extern std::atomic_bool g_isInitialized; // variable that indicates when s4api has been initialized


DWORD WINAPI InitializeGlobals(HMODULE mod);
