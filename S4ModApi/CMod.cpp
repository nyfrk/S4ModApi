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

#include "CMod.h"
#include "Console.h"
#include <algorithm>
#include "module.h"

void CMod::InitAll() {
	TRACE;
	const std::lock_guard<decltype(mutex)> lock(mutex);
	for (auto& inst : instances) inst->Setup();
}

CMod::CMod() {
	TRACE;
	const std::lock_guard<decltype(mutex)> lock(mutex);
	instances.push_back(this);
}

CMod::~CMod() {
	TRACE;
	const std::lock_guard<decltype(mutex)> lock(mutex);
	auto it = std::find(instances.rbegin(), instances.rend(), this);
	if (it != instances.rend()) {
		instances.erase((++it).base());
	}
}

void CMod::Setup() {
	TRACE;
	const std::lock_guard<decltype(mutex)> lock(mutex);
	if (m_bIsInitialized) return;
	m_bIsInitialized = Init();
	if (!m_bIsInitialized) return;

	if (m_bWantInstalled) Install();
}

void CMod::Install() {
	TRACE;
	const std::lock_guard<decltype(mutex)> lock(mutex);
	if (m_bIsInstalled) return;
	m_bWantInstalled = true;
	if (!m_bIsInitialized) { // not initialized
		Setup(); // try initialize
		if (!m_bIsInitialized) return; // still not initialized
	}
	m_bIsInstalled = true;

	Patch();
}

void CMod::Uninstall() {
	TRACE;
	const std::lock_guard<decltype(mutex)> lock(mutex);
	if (!m_bIsInstalled) return;
	m_bWantInstalled = false;
	m_bIsInstalled = false;

	Unpatch();
}

bool CMod::IsInstalled() {
	return m_bIsInstalled;
}

bool CMod::IsEnabled() {
	return m_bWantInstalled || m_bIsInstalled;
}

std::vector<CMod*> CMod::instances;
std::recursive_mutex CMod::mutex;

