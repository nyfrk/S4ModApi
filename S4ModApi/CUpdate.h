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

/**
 * This is a quick and dirty auto update script. It will replace the S4ModApi.dll with the latest 
 * non-prerelease version from the github release. 
 **/

#pragma once

#include "windef.h"
#include <string>

class CUpdate {
public:
	enum EUpdateCheckStatus {
		UPDATE_CHECK_UNK,
		UPDATE_CHECK_ERROR,
		UPDATE_CHECK_AVAILABLE,
		UPDATE_CHECK_UPTODATE,
	};

	static CUpdate& GetInstance();

	EUpdateCheckStatus check(); // check for updates
	DWORD getMillisSinceCheck(); // how many milliseconds elapsed since we polled for the last result

private:
	void InitVersion();
	void InstallUpdate(const std::string& url);

	CUpdate& operator=(const CUpdate&) = delete;
	CUpdate(const CUpdate&) = delete;
	CUpdate() = default;

	bool m_hasChecked = false;
	EUpdateCheckStatus m_status = UPDATE_CHECK_UNK;
	DWORD m_receivedTick = 0xFFFFFFFF;
	WORD m_verMayor = 0, m_verMinor = 0;
};