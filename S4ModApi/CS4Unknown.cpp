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
#include "globals.h"
#include <mutex>

HRESULT CSettlers4Api::QueryInterface(REFIID riid, LPVOID* ppvObj) {
	TRACE;
	if (ppvObj == NULL) {
		return E_POINTER;
	}

	if (riid == IID_IUnknown) {
		*ppvObj = static_cast<IUnknown*>(this);
	}
	else if (riid == IID_ISettlers4Api) {
		*ppvObj = static_cast<ISettlers4Api*>(this);
	}
	else {
		*ppvObj = NULL;
		return E_NOINTERFACE;
	}

	(static_cast<IUnknown*>(*ppvObj))->AddRef();

	return S_OK;
}

static std::mutex mtx; // ref counter lock

ULONG CSettlers4Api::AddRef() {
	TRACE;
	std::lock_guard<std::mutex> lock(mtx);
	return ++m_refs;
}

ULONG CSettlers4Api::Release() {
	TRACE;
	std::lock_guard<std::mutex> lock(mtx);
	// Decrement the object's internal counter.
	auto lRefCount = --m_refs;
	if (lRefCount <= 0) {
		//delete this;
		return 0;
	}
	return lRefCount;
}
