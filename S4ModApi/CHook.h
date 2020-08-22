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
#include "S4ModApi.h"
#include <vector>
#include <mutex>
#include "Log.h"

class CHook {
	public:
		void Setup(); // processes the addresses from the pattern scanner
		void Install(); // installs the hook
		void Uninstall(); // uninstalls the hook

		S4HOOK AddListener(LPCVOID,DWORD=0,INT=0); // register an observer
		static HRESULT RemoveListener(S4HOOK); // remove an observer
		static void InitAll(); // initialize all instantiated hooks

	protected:
		virtual bool Init() = 0; // computes target addresses based on the patterns
		virtual void Patch() = 0; // installs the patches/detours
		virtual void Unpatch() = 0; // uninstalls the patches/detours

		CHook();
		~CHook();
		CHook(const CHook&) = delete;
		CHook& operator=(CHook const&) = delete;

		/** struct used for mapping S4HOOK to callback function **/
		struct ObserverEntry {
			LPCVOID callback;
			S4HOOK id;
			DWORD param;
			INT priority;
			HMODULE mod;

			ObserverEntry() = delete;
			ObserverEntry(LPCVOID callback, S4HOOK id, DWORD param, INT priority, HMODULE mod);
		};
		std::vector<ObserverEntry> observers;
		static std::recursive_mutex mutex;

private:
		/** all instances of the hooks **/
		static std::vector<CHook*> instances;
		
		static S4HOOK lowestFreeId;

		static S4HOOK FindFreeObserverId(); // get a free id for an observer

		unsigned char m_bIsInstalled : 1;
		unsigned char m_bIsInitialized : 1;
		unsigned char m_bWantInstalled : 1;
};
