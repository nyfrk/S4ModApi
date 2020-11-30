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

static inline BOOL isBuilding(const Settler_t& obj, S4_BUILDING_ENUM id) {
	if (obj.objectType != Settler_t::OBJECTTYPE_BUILDING) return FALSE;
	switch (id) {
	case S4_BUILDING_PORTA:
	case S4_BUILDING_PORTB:
	case S4_BUILDING_PORTC:
	case S4_BUILDING_PORTD:
	case S4_BUILDING_PORTE:
	case S4_BUILDING_PORTF:
	case S4_BUILDING_PORTG:
	case S4_BUILDING_PORTH:
		return obj.settlerType == S4_BUILDING_PORT
			&& obj.goodType == id;
	case S4_BUILDING_SHIPYARDA:
	case S4_BUILDING_SHIPYARDB:
	case S4_BUILDING_SHIPYARDC:
	case S4_BUILDING_SHIPYARDD:
	case S4_BUILDING_SHIPYARDE:
	case S4_BUILDING_SHIPYARDF:
	case S4_BUILDING_SHIPYARDG:
	case S4_BUILDING_SHIPYARDH:
		return obj.settlerType == S4_BUILDING_SHIPYARD
			&& obj.goodType == id;
	default: return obj.settlerType == id;
	}
}
static inline BOOL isVehicle(const Settler_t& obj, S4_VEHICLE_ENUM id) {
	if ((obj.objectType & (Settler_t::OBJECTTYPE_LANDVEHICLE | Settler_t::OBJECTTYPE_SHIP)) == 0)
		return FALSE;
	switch (obj.baseType) {
		case Settler_t::BASETYPE_WARMACHINE:
		case Settler_t::BASETYPE_TRADINGCART:
		case Settler_t::BASETYPE_WARSHIP:
		case Settler_t::BASETYPE_CIVILIAN_SHIP:
			return obj.settlerType == id;
		default: return FALSE;
	}
}
static inline BOOL isSettler(const Settler_t& obj, S4_SETTLER_ENUM id) {
	if (obj.objectType != Settler_t::OBJECTTYPE_SETTLER) return FALSE;
	return obj.settlerType == id;
}
static inline BOOL isGood(const Settler_t& obj, S4_GOOD_ENUM id) {
	if (obj.objectType != Settler_t::OBJECTTYPE_GOOD) return FALSE;
	return obj.goodType == id;
}
static inline BOOL isPlant(const Settler_t& obj, S4_OBJECT_ENUM id) {
	if (obj.objectType != Settler_t::OBJECTTYPE_PLANT) return FALSE;
	return obj.settlerType == id;
}
/*static BOOL isAnimal(const Settler_t& obj, S4_OBJECT_TYPE id) {
	if (obj.objectType != Settler_t::OBJECTTYPE_ANIMAL) return FALSE;
	//switch (id) {
	//	case S4_OBJECT_ANIMAL:	return TRUE;
	//	default: return obj.settlerType == MAKE_ANIMAL_INDEX(id);
	//}
}*/

static BOOL GetPoolObject(Settler_t& obj, WORD object) {
	auto pool = S4::GetInstance().SettlerPool;
	if (!pool) return FALSE;
	auto pObj = (Settler_t*)READ_AT(&(pool[object]));
	if (!pObj) return FALSE;
	return NULL != memget_s(&obj, pObj, sizeof(obj));
}

BOOL CSettlers4Api::IsObjectBuilding(WORD object, S4_BUILDING_ENUM type) {
	TRACE;
	Settler_t obj = { 0 };
	if (GetPoolObject(obj, object)) {
		return isBuilding(obj, type);
	}
	return FALSE;
}

BOOL CSettlers4Api::IsObjectSettler(WORD object, S4_SETTLER_ENUM type) {
	TRACE;
	Settler_t obj = { 0 };
	if (GetPoolObject(obj, object)) {
		return isSettler(obj, type);
	}
	return FALSE;
}

BOOL CSettlers4Api::IsObjectObject(WORD object, S4_OBJECT_ENUM type) {
	TRACE;
	Settler_t obj = { 0 };
	if (GetPoolObject(obj, object)) {
		return isPlant(obj, type);
	}
	return FALSE;
}

BOOL CSettlers4Api::IsObjectVehicle(WORD object, S4_VEHICLE_ENUM type) {
	TRACE;
	Settler_t obj = { 0 };
	if (GetPoolObject(obj, object)) {
		return isVehicle(obj, type);
	}
	return FALSE;
}

BOOL CSettlers4Api::IsObjectGood(WORD object, S4_GOOD_ENUM type) {
	TRACE;
	Settler_t obj = { 0 };
	if (GetPoolObject(obj, object)) {
		return isGood(obj, type);
	}
	return FALSE;
}

BOOL CSettlers4Api::IsObjectTribe(WORD object, S4_TRIBE_ENUM type) {
	TRACE;
	Settler_t obj = { 0 };
	if (GetPoolObject(obj, object)) {
		switch (type) {
			case S4_TRIBE_NONE: return !obj.isTribe();
			case S4_TRIBE_ANY: return obj.isTribe();
			default: return obj.isTribe() && obj.getTribe() == type;
		};
	}
	return FALSE;
}

