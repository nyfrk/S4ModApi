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

#include "globals.h" // g_isGE, hProcess
#include "CSettlers4Api.h"
#include "hlib.h" // JmpPatch
#include "patterns.h"
#include "s4.h"
#include "safemem.h"
#include <unordered_set>
#include "CSelectionMod.h"

BOOL CSettlers4Api::ClearSelection() {
	TRACE;
	typedef void(__stdcall* ClearSelection_t)();
	auto ClearSelection = (ClearSelection_t)g_Patterns.ClearSelection.addr;
	if (!ClearSelection) return FALSE;
	ClearSelection();
	return TRUE;
}

BOOL CSettlers4Api::GetSelection(PWORD out, SIZE_T outlen, PSIZE_T selectionCount) {
	TRACE;
	if (!out) return FALSE;
	auto& s = S4::GetInstance().Selection;
	if (!s) return FALSE;
	auto ct = s->count();
	auto elementsToCopy = min(ct, outlen);
	if (selectionCount) *selectionCount = ct;
	LOG("s->BasePtr == " << HEXNUM(s->BasePtr))
	if (out && elementsToCopy) memget_s(out, s->BasePtr, elementsToCopy * sizeof(*s->BasePtr));
	return TRUE;
}

BOOL CSettlers4Api::RemoveSelection(PWORD settlers, SIZE_T settlerslen, PSIZE_T removedCount) {
	TRACE;
	if (!settlers) return FALSE;
	if (!settlerslen) {
		if (removedCount) *removedCount = 0;
		return TRUE;
	}
	auto& s = S4::GetInstance().Selection;
	if (!s) return FALSE;
	auto ppool = S4::GetInstance().EntityPool;
	if (!ppool) return FALSE;
	auto pool = *ppool;

	// build a set for settlers to remove
	std::unordered_set<WORD> removeSet;
	for (SIZE_T i = 0; i < settlerslen; i++) {
		auto e = settlers[i];
		if (e) removeSet.insert(e);
	}

	auto end = s->EndPtr;
	auto cur = s->BasePtr;
	for (auto sp = cur; sp < end; ++sp) {
		if (removeSet.find(*sp) != removeSet.end()) {
			pool[*sp].clrSelectionVisibility();
			continue;
		}
		*cur = *sp;
		++cur;
	}
	if (removedCount) *removedCount = end - cur;
	if (cur == s->BasePtr) {
		// all elements have been removed
		//ClearSelection();
	}
	s->EndPtr = cur;
	return TRUE;
}

DWORD CSettlers4Api::SetMaxSelection(DWORD newLimit) {
	TRACE;
	return CSelectionMod::GetInstance().SetMaxSelection(newLimit);
}

DWORD CSettlers4Api::GetMaxSelection() {
	TRACE;
	return CSelectionMod::GetInstance().GetMaxSelection();
}
