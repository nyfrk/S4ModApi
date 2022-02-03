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

#include "CMod.h"

/// <summary>
/// Selection Mod that allows the player to select and command more than 
/// 100 settlers.
/// </summary>
class CSelectionMod : public CMod {
public:
	static CSelectionMod& GetInstance();

	DWORD SetMaxSelection(DWORD newLimit);
	DWORD GetMaxSelection();

protected:
	virtual bool Init();
	virtual void Patch();
	virtual void Unpatch();

private:
	CSelectionMod();
	static HRESULT S4HCALL CSelectionMod::OnSettlersSend(DWORD dwPosition, S4_MOVEMENT_ENUM dwCommand, LPVOID lpReserved);
};

