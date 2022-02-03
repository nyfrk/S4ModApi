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

#include "globals.h" // g_isGE, S4_Main
#include "hlib.h" // CallPatch, Patch
#include "patterns.h"

#include "CSelectionMod.h"

static std::vector<hlib::Patch> valuePatches;
static hlib::CallPatch BoxSelectLimitPatch;
static hlib::CallPatch AltSelectLimitPatch;
static const DWORD OriginalSelectionLimit = 100;
static DWORD maxSelection = OriginalSelectionLimit;
static struct SelectionMarker { DWORD x, y, markerType /*1=normal, 5C=silver, 5D=gold, 5E=priest, 5F=armored*/; } *selectionMarkersArray = nullptr; // new buffer, since games buffer is fixed to 100 elements
static struct HealthBubble { DWORD x, y, unk[3]; } *healthBubblesArray = nullptr; // new buffer, since games buffer is fixed to 100 elements
static S4HOOK SendWarriorHook;
static S4API s4;

static void __declspec(naked) __newSelectLimitHE() {
	__asm {
		sar eax, 1
		cmp eax, maxSelection
		ret
	}
}
static void __declspec(naked) __newSelectLimitGE() {
	__asm {
		sar edx, 1
		cmp edx, maxSelection
		ret
	}
}
//static void __declspec(naked) __newCommandLimitGE() { // this is only required for the GE
//	__asm {
//		cmp edi, maxSelection
//		jle lbl_end
//		mov edi, maxSelection
//		lbl_end :
//		ret
//	}
//}

HRESULT S4HCALL CSelectionMod::OnSettlersSend(DWORD dwPosition, S4_MOVEMENT_ENUM dwCommand, LPVOID lpReserved) {
	UNREFERENCED_PARAMETER(lpReserved);
	const std::lock_guard<decltype(mutex)> lock(mutex);
	INT x = LOWORD(dwPosition);
	INT y = HIWORD(dwPosition);
	auto sel = maxSelection;
	WORD* settlers = new WORD[sel];
	SIZE_T settlersSelected = 0;
	if (s4->GetSelection(settlers, sel, &settlersSelected)) {
		s4->SendWarriors(x, y, dwCommand, settlers, settlersSelected);
	}
	return TRUE;
}

CSelectionMod& CSelectionMod::GetInstance() {
	static CSelectionMod inst;
	return inst;
}

template<typename T> static void SafeFree(T &mem) {
	if (mem) {
		free(mem);
		mem = nullptr;
	}
}

DWORD CSelectionMod::SetMaxSelection(DWORD newLimit) {
	TRACE;
	const std::lock_guard<decltype(mutex)> lock(mutex);
	if (newLimit > 10000) return 1;
	if (maxSelection == newLimit) return 0;

	Setup();

	if (newLimit == OriginalSelectionLimit) {
		SafeFree(selectionMarkersArray);
		SafeFree(healthBubblesArray);
		maxSelection = OriginalSelectionLimit;
		Uninstall();
		return 0;
	}

	Uninstall();

	auto newSelectionMarkersArray = (SelectionMarker*)realloc(selectionMarkersArray, max(1, newLimit) * sizeof(SelectionMarker));
	auto newHealthBubblesArray = (HealthBubble*)realloc(healthBubblesArray, max(1, newLimit) * sizeof(HealthBubble));

	if (!newSelectionMarkersArray || !newHealthBubblesArray) {
		SafeFree(selectionMarkersArray);
		SafeFree(healthBubblesArray);
		maxSelection = OriginalSelectionLimit;
		return 2;
	}

	//if (!selectionMarkersArray) {
	//	// copy values from games array to newSelectionMarkersArray
	//}
	//if (!healthBubblesArray) {
	//	// copy values from games array to newHealthBubblesArray
	//}
	memset(newSelectionMarkersArray, 0, max(1, newLimit) * sizeof(SelectionMarker));
	memset(newHealthBubblesArray, 0, max(1, newLimit) * sizeof(HealthBubble));

	selectionMarkersArray = newSelectionMarkersArray;
	healthBubblesArray = newHealthBubblesArray;
	maxSelection = newLimit;

	Install();
	return 0;
}

DWORD CSelectionMod::GetMaxSelection() {
	const std::lock_guard<decltype(mutex)> lock(mutex);
	return maxSelection;
}

bool CSelectionMod::Init() {
	const std::lock_guard<decltype(mutex)> lock(mutex);
	TRACE;

	bool requiredPatterns = g_Patterns.SelectionMarkerBufferGetter &&
		g_Patterns.SelectionMarkerBufferSetter &&
		g_Patterns.HealthBubbleBufferGetter &&
		g_Patterns.HealthBubbleBufferSetter &&
		g_Patterns.BoxSelect &&
		g_Patterns.AltSelect &&
		S4_Main;

	if (!requiredPatterns) {
		if (!g_Patterns.SelectionMarkerBufferGetter) LOG("missing g_Patterns.SelectionMarkerBufferGetter");
		if (!g_Patterns.SelectionMarkerBufferSetter) LOG("missing g_Patterns.SelectionMarkerBufferSetter");
		if (!g_Patterns.HealthBubbleBufferGetter) LOG("missing g_Patterns.HealthBubbleBufferGetter");
		if (!g_Patterns.HealthBubbleBufferSetter) LOG("missing g_Patterns.HealthBubbleBufferSetter");
		if (!g_Patterns.BoxSelect) LOG("missing g_Patterns.BoxSelect");
		if (!g_Patterns.AltSelect) LOG("missing g_Patterns.AltSelect");
		if (!S4_Main) LOG("missing S4_Main");
		return false;
	}

	BoxSelectLimitPatch = hlib::CallPatch(g_Patterns.BoxSelect.addr, (DWORD)(g_isGE ? __newSelectLimitGE : __newSelectLimitHE));
	AltSelectLimitPatch = hlib::CallPatch(g_Patterns.AltSelect.addr, (DWORD)(g_isGE ? __newSelectLimitGE : __newSelectLimitHE));

	LOG("CSelectionMod::Init returns true");
	return true;
}

void CSelectionMod::Patch() {
	const std::lock_guard<decltype(mutex)> lock(mutex);
	TRACE;

	valuePatches.emplace_back(g_Patterns.SelectionMarkerBufferGetter + (g_isGE ? 1 : 9), ((DWORD)selectionMarkersArray) + 4);
	valuePatches.emplace_back(g_Patterns.SelectionMarkerBufferSetter + (g_isGE ? 10 : 18), ((DWORD)selectionMarkersArray) + 0);
	valuePatches.emplace_back(g_Patterns.SelectionMarkerBufferSetter + (g_isGE ? 34 : 27), ((DWORD)selectionMarkersArray) + 4);
	valuePatches.emplace_back(g_Patterns.SelectionMarkerBufferSetter + (g_isGE ? 40 : 36), ((DWORD)selectionMarkersArray) + 8);
	valuePatches.emplace_back(g_Patterns.HealthBubbleBufferGetter + (g_isGE ? 52 : 5), ((DWORD)healthBubblesArray) + (g_isGE ? 4 : 0));
	valuePatches.emplace_back(g_Patterns.HealthBubbleBufferSetter + (g_isGE ? 2 : 5), ((DWORD)healthBubblesArray) + 0);
	valuePatches.emplace_back(g_Patterns.HealthBubbleBufferSetter + (g_isGE ? 26 : 14), ((DWORD)healthBubblesArray) + 4);
	valuePatches.emplace_back(g_Patterns.HealthBubbleBufferSetter + (g_isGE ? 32 : 23), ((DWORD)healthBubblesArray) + 8);
	valuePatches.emplace_back(g_Patterns.HealthBubbleBufferSetter + (g_isGE ? 38 : 32), ((DWORD)healthBubblesArray) + 12);
	valuePatches.emplace_back(g_Patterns.HealthBubbleBufferSetter + (g_isGE ? 44 : 44), ((DWORD)healthBubblesArray) + 16);

	for (auto it = valuePatches.begin(); it != valuePatches.end(); it++) {
		it->patch();
	}

	BoxSelectLimitPatch.patch();
	AltSelectLimitPatch.patch();

	s4 = S4ApiCreate();
	if (s4) SendWarriorHook = s4->AddSettlerSendListener(OnSettlersSend);
}

void CSelectionMod::Unpatch() {
	const std::lock_guard<decltype(mutex)> lock(mutex);
	TRACE;
	if (SendWarriorHook && s4) s4->RemoveListener(SendWarriorHook);
	if (s4) s4->Release();
	SendWarriorHook = 0;
	s4 = 0;
	AltSelectLimitPatch.unpatch();
	BoxSelectLimitPatch.unpatch();
	for (auto it = valuePatches.rbegin(); it != valuePatches.rend(); it++) {
		it->unpatch();
	}
	valuePatches.clear();
}

CSelectionMod::CSelectionMod() { TRACE; }
