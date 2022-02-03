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
#include "patterns.h"
#include "s4.h"
#include "safemem.h"
#include "globals.h"

DWORD CSettlers4Api::LandscapeGetHeight(INT x, INT y) {
	TRACE;
	auto landscape = S4::GetInstance().GetLandscapeAt((WORD)x, (WORD)y);
	if (landscape) return landscape->GetTerrainHeight();
	return 0;
}

S4_GROUND_ENUM CSettlers4Api::LandscapeGetType(INT x, INT y) {
	TRACE;
	auto landscape = S4::GetInstance().GetLandscapeAt((WORD)x, (WORD)y);
	if (landscape) return landscape->GetTerrainType();
	return S4_GROUND_ENUM::WATER8;
}

BOOL CSettlers4Api::LandscapeIsPond(INT x, INT y) {
	TRACE;
	auto landscape = S4::GetInstance().GetLandscapeAt((WORD)x, (WORD)y);
	if (landscape) return landscape->IsPondBrush();
	return FALSE;
}

BOOL CSettlers4Api::LandscapeIsDarkLand(INT x, INT y) {
	TRACE;
	auto landscape = S4::GetInstance().GetLandscapeAt((WORD)x, (WORD)y);
	if (landscape) return landscape->IsDarkLand();
	return FALSE;
}

BOOL CSettlers4Api::LandscapeIsDarkLandBorder(INT x, INT y) {
	TRACE;
	auto landscape = S4::GetInstance().GetLandscapeAt((WORD)x, (WORD)y);
	if (landscape) return landscape->IsDarkBorder();
	return FALSE;
}

DWORD CSettlers4Api::LandscapeGetFogOfWar(INT x, INT y) {
	TRACE;
	auto landscape = S4::GetInstance().GetLandscapeAt((WORD)x, (WORD)y);
	if (landscape) return landscape->GetFogOfWarLevel();
	return (DWORD)-1;
}

BOOL CSettlers4Api::LandscapeIsFoundingStone(INT x, INT y) {
	TRACE;
	auto landscape = S4::GetInstance().GetLandscapeAt((WORD)x, (WORD)y);
	if (landscape) return landscape->IsFoundingStone();
	return FALSE;
}

S4_RESOURCE_ENUM CSettlers4Api::LandscapeGetResource(INT x, INT y) {
	TRACE;
	return S4::GetInstance().GetResourceAt((WORD)x, (WORD)y);
}

BOOL CSettlers4Api::LandscapeSetResource(INT x, INT y, S4_RESOURCE_ENUM res) {
	TRACE;
	return S4::GetInstance().SetResourceAt((WORD)x, (WORD)y, res);
}

DWORD CSettlers4Api::LandscapeGetObject(INT x, INT y) {
	TRACE;
	return S4::GetInstance().GetEntityIdAt((WORD)x, (WORD)y);
}

DWORD CSettlers4Api::LandscapeGetOwner(INT x, INT y) {
	TRACE;
	return S4::GetInstance().GetOwnerAt((WORD)x, (WORD)y);
}

DWORD CSettlers4Api::LandscapeGetEcoSector(INT x, INT y) {
	TRACE;
	return S4::GetInstance().LandscapeGetEcoSector((WORD)x, (WORD)y);
}

BOOL CSettlers4Api::LandscapeIsOccupied(INT x, INT y) {
	TRACE;
	return S4::GetInstance().IsOccupied((WORD)x, (WORD)y);
}