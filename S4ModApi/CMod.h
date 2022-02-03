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
#include "S4ModApi.h"
#include <vector>
#include <mutex>
#include "Log.h"

/// <summary>
/// Mods are modifications to the game that require patterns or other initialization
/// to be already performed. Mods may be activated but not installed. When initialization
/// is completed all activated mods will be installed. 
/// 
/// CMod serves as a base class for mods. 
/// </summary>
class CMod {
	public:
		void Setup(); // processes the addresses from the pattern scanner
		void Install(); // installs the mod
		void Uninstall(); // uninstalls the mod

		bool IsInstalled(); // mod is enabled and installed
		bool IsEnabled(); // mod is enabled but not yet installed

		static void InitAll(); // initialize all activated mods

	protected:
		virtual bool Init() = 0; // computes target addresses based on the patterns
		virtual void Patch() = 0; // installs the patches/detours
		virtual void Unpatch() = 0; // uninstalls the patches/detours

		CMod();
		~CMod();
		CMod(const CMod&) = delete;
		CMod& operator=(CMod const&) = delete;

		static std::recursive_mutex mutex;

private:
		/** all instances of the mods that have been constructed **/
		static std::vector<CMod*> instances;

		unsigned char m_bIsInstalled : 1;
		unsigned char m_bIsInitialized : 1;
		unsigned char m_bWantInstalled : 1;
};
