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

#include "CHook.h"
#include "Console.h"
#include <algorithm>
#include "module.h"

void CHook::InitAll() {
	TRACE;
	const std::lock_guard<decltype(mutex)> lock(mutex);
	for (auto& inst : instances) inst->Setup();
}

HRESULT CHook::RemoveListener(S4HOOK hook) {
	TRACE;
	if (hook != 0) {
		const std::lock_guard<decltype(mutex)> lock(mutex);
		for (auto& inst : instances) {
			auto& observers = inst->observers;
			for (auto it = observers.rbegin(); it != observers.rend(); ++it) {
				if (it->id == hook) {
					DecreaseModuleRefcount(it->mod);
					observers.erase((++it).base());
					if (hook < lowestFreeId) lowestFreeId = hook;
					if (observers.empty()) {
						inst->Uninstall();
					}
					LOG("remove listener " << dec << hook << " with S_OK");
					return S_OK;
				}
			}
		}
	}

	LOG("error: remove listener " << dec << hook << " returns with E_HANDLE");
	return E_HANDLE;
}

S4HOOK CHook::FindFreeObserverId() {
	TRACE;
	std::vector<bool> usedS4HookIDsVec; // bit (!) vector that tracks used IDs
	// build bit vector
	for (auto& inst : instances) {
		for (auto& observer : inst->observers) {
			if (observer.id >= usedS4HookIDsVec.size())
				usedS4HookIDsVec.resize(observer.id);
			usedS4HookIDsVec[observer.id - 1] = true;
		}
	}

	// find first bit that is 0
	auto sz = usedS4HookIDsVec.size();
	for (UINT32 i = 0; i < sz; i++) {
		if (!usedS4HookIDsVec[i]) 
			return i + 1;
	}
	return sz + 1;
}

S4HOOK CHook::AddListener(LPCVOID lpCallback, DWORD dwParam, INT iPriority) {
	TRACE;
	if (lpCallback == NULL) {
		LOG("error: lpCallback is NULL");
		return 0;
	}
	auto mod = IncreaseModuleRefcount(lpCallback);
	if (!mod) {
		LOG("error: cannot lock code of callback in memory");
		return 0; // already unloaded?
	}
	const std::lock_guard<decltype(mutex)> lock(mutex);
	Install();
	auto hookId = FindFreeObserverId();
	ObserverEntry entry(lpCallback, hookId, dwParam, iPriority, mod);
	// insert listener according to priority (keeps vector sorted by priority)
	observers.insert(
		std::upper_bound(
			observers.begin(), 
			observers.end(), 
			entry,
			[](const ObserverEntry& a, const ObserverEntry& b) { return a.priority < b.priority; }),
		entry);
	LOG("inserted callback " << HEXNUM(lpCallback) << dec << " with param " << dec << dwParam << " in module " << HEXNUM(mod) << ". S4HOOK == " << dec << hookId);
	return hookId;
}

CHook::CHook() {
	TRACE;
	const std::lock_guard<decltype(mutex)> lock(mutex);
	instances.push_back(this);
}

CHook::~CHook() {
	TRACE;
	const std::lock_guard<decltype(mutex)> lock(mutex);
	auto it = std::find(instances.rbegin(), instances.rend(), this);
	if (it != instances.rend()) {
		instances.erase((++it).base());
	}
}

void CHook::Setup() {
	TRACE;
	if (m_bIsInitialized) return;
	m_bIsInitialized = Init();
	if (!m_bIsInitialized) return;

	if (m_bWantInstalled) Install();
}

void CHook::Install() {
	TRACE;
	if (m_bIsInstalled) return;
	m_bWantInstalled = true;
	if (!m_bIsInitialized) { // not initialized
		Setup(); // try initialize
		if (!m_bIsInitialized) return; // still not initialized
	}
	m_bIsInstalled = true;

	Patch();
}

void CHook::Uninstall() {
	TRACE;
	if (!m_bIsInstalled) return;
	m_bWantInstalled = false;
	m_bIsInstalled = false;

	Unpatch();
}

std::vector<CHook*> CHook::instances;

std::recursive_mutex CHook::mutex;
S4HOOK CHook::lowestFreeId = 1;

CHook::ObserverEntry::ObserverEntry(LPCVOID callback, S4HOOK id, DWORD param, INT priority, HMODULE mod) : 
	callback(callback),id(id),param(param), priority(priority), mod(mod) {
	TRACE;
}
