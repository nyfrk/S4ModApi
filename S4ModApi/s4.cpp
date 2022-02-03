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

#include "s4.h"
#include "patterns.h" // patterns
#include "globals.h" // g_isGE
#include "safemem.h" // READ_AT
#include "Log.h"

static inline DWORD AddIfNotNull(DWORD sum, INT add) {
	if (sum) sum += add;
	return sum;
}
#define LOAD_PTR_OFF(dest, patternaddr, patternoffset, postderefoffset) dest = (decltype(dest))AddIfNotNull(READ_AT(patternaddr, patternoffset),postderefoffset)
#define LOAD_PTR(dest, patternaddr, patternoffset) LOAD_PTR_OFF(dest, patternaddr, patternoffset, 0)
#define LOAD_FUNC(dest, patternaddr, patternoffset) {\
	dest = (decltype(dest))nullptr;\
	if (patternaddr) {\
		DWORD addr = (patternaddr) + (patternoffset); \
		DWORD off = READ_AT((LPCVOID)addr, 1); \
		if (off) dest = (decltype(dest))(addr + off + 5);\
	}\
}

void S4::Initialize() {
	TRACE;
	LOAD_PTR(		PillarboxWidth		, g_Patterns.PillarboxWidth		, 16					);
	LOAD_PTR(		HoveringUiElement	, g_Patterns.HoveringUiElement	, 14					);
	LOAD_PTR(		Hwnd				, g_Patterns.Hwnd				, g_isGE ? 1 : 3		);
	LOAD_PTR(		MenuScreenObj		, g_Patterns.MenuScreenObj		, 12					);
	LOAD_PTR(		CurrentMenuScreen	, g_Patterns.CurrentMenuScreen	, 17					);
	LOAD_PTR(		GameMenusWndProc	, g_Patterns.GameMenusWndProc	, -4					);
	LOAD_PTR(		WndProcChain		, g_Patterns.WndProcChain		, 6						);
	LOAD_PTR_OFF(	ActiveIngameMenu	, g_Patterns.ActiveIngameMenu	, 3	, 8					);
	LOAD_PTR(		SettlerPrototypes	, g_Patterns.SettlerFilter		, g_isGE ? 19 : 18		);
	LOAD_PTR_OFF(	Selection			, g_Patterns.SettlerFilter		, g_isGE ? 56 : 49, -4	);
	LOAD_PTR(		EntityPool			, g_Patterns.SettlerFilter		, g_isGE ? -35 : -18	);
	LOAD_PTR(		LocalPlayer 		, g_Patterns.OnSettlerCommandHook, g_isGE ? -0x73 : -0x66);
	LOAD_FUNC(      LocalEvent          , g_Patterns.LocalEvent         , 3);// todo: ge support
	LOAD_PTR(		Tick, 
					g_isGE ? g_Patterns.OnSettlerCommandHook : g_Patterns.NetEventConstuctor, 
					g_isGE ? 0x87 : 4 );
	LOAD_FUNC(      __SendNetEvent      , g_Patterns.OnSettlerCommandHook, (g_isGE ? 0xE9 : 0xC3));
	if (g_isGE) {
		LOAD_PTR(NetEventVTbl, g_Patterns.OnSettlerCommandHook, 0xC5);
		NetEventVTbl = READ_AT((LPCVOID)NetEventVTbl);
	} else {
		LOAD_PTR(NetEventVTbl, g_Patterns.RecruitmentEventConstructor, 8);
	}
	LOAD_FUNC(__realloc, g_Patterns.Lua, 18);
	LOAD_FUNC(__free, g_Patterns.Lua, 3);
	LOAD_PTR(lua_state, g_Patterns.Lua, 44);

	// history edition only, todo: add gold edition support
	EventConstructor = (LPCVOID)AddIfNotNull(g_Patterns.NetEventConstuctor, -0x12);

	MapSize = (decltype(MapSize))(S4_Main + 0xD6921C);// he only, todo: make pattern
	GameTime = (decltype(GameTime))(S4_Main + 0xE66B14);
	Blockmap2 = (decltype(Blockmap2))(S4_Main + 0x11630D0);// he only, todo: make pattern
	LandscapeMap = (decltype(LandscapeMap))(S4_Main + 0xD69220);// he only, todo: make pattern
	EntityMap = (decltype(EntityMap))(S4_Main + 0x11630DC);// he only, todo: make pattern
	ResourceMap = (decltype(ResourceMap))(S4_Main + 0x11630E4);// he only, todo: make pattern
	EcoSectorMap = (decltype(EcoSectorMap))(S4_Main + 0xEF1A18);// he only, todo: make pattern
	EcoSectorPool = (decltype(EcoSectorPool))(S4_Main + 0xEF1A20);// he only, todo: make pattern
	EntityPoolSize = (decltype(EntityPoolSize))(S4_Main + 0xE9B0BC);
}

S4& S4::GetInstance() {
	static S4 instance;
	return instance;
}

DWORD S4::GetEntityPoolSize() {
	return EntityPoolSize != NULL ? *EntityPoolSize : 0;

}

DWORD S4::GetMapSize() { 
	return MapSize != NULL ? *MapSize : 0; 
}

WORD* S4::GetBlockMap2() {
	return Blockmap2 != NULL ? *Blockmap2 : 0;
}

DWORD S4::GetGameTime() {
	return GameTime != NULL ? *GameTime : 0;
}

WorldField* S4::GetLandscapeAt(WORD x, WORD y) {
	if (LandscapeMap && *LandscapeMap) {
		auto size = GetMapSize();
		if (size != 0 && y < size && x < size)	return &((*LandscapeMap)[y * size + x]);
	}
	return NULL;
}
IEntity* S4::GetEntityAt(WORD x, WORD y) {
	if (EntityPool) {
		auto eid = GetEntityIdAt(x, y);
		if (eid) {
			return EntityPool[eid];
		}
	}
	return NULL;
}
WORD S4::GetEntityIdAt(WORD x, WORD y) {
	if (EntityMap && *EntityMap) {
		auto size = GetMapSize();
		if (size == 0 || y >= size || x >= size) return NULL;
		return (*EntityMap)[y * size + x];
	}
	return 0;
}
S4_RESOURCE_ENUM S4::GetResourceAt(WORD x, WORD y) {
	if (ResourceMap && *ResourceMap) {
		auto size = GetMapSize();
		if (size != 0 && y < size && x < size) {
			return (*ResourceMap)[y * size + x];
		}
	}
	return S4_RESOURCE_ENUM::S4_RESOURCE_NONE;
}
BOOL S4::SetResourceAt(WORD x, WORD y, S4_RESOURCE_ENUM res) {
	if (ResourceMap && *ResourceMap) {
		auto size = GetMapSize();
		if (size != 0 && y < size && x < size) {
			(*ResourceMap)[y * size + x] = res;
			return TRUE;
		}
	}
	return FALSE;
}
EcoSector* S4::GetEcoSectorAt(WORD x, WORD y) {
	if (EcoSectorMap && *EcoSectorMap && EcoSectorPool) {
		auto size = GetMapSize();
		if (size != 0 && y < size && x < size) {
			auto ecoId = (*EcoSectorMap)[y * size + x];
			if (ecoId != 0) return &(EcoSectorPool[ecoId]);
		}
	}
	return NULL;
}

WORD S4::LandscapeGetEcoSector(WORD x, WORD y) {
	if (EcoSectorMap && *EcoSectorMap && EcoSectorPool) {
		auto size = GetMapSize();
		if (size != 0 && y < size && x < size) {
			auto ecoId = (*EcoSectorMap)[y * size + x];
			return ecoId;
		}
	}
	return NULL;
}

DWORD S4::GetOwnerAt(WORD x, WORD y) {
	auto sector = GetEcoSectorAt(x, y);
	return sector ? sector->GetOwningPlayer() : 0;
}

BOOL S4::IsOccupied(WORD x, WORD y) {
	if (Blockmap2 && *Blockmap2 && Blockmap2) {
		auto size = GetMapSize();
		if (size != 0 && y < size && x < size) {
			auto ecoId = (*Blockmap2)[y * size + x];
			//TODO7
			return ecoId == 0;
		}
	}
	return FALSE;
}


DWORD S4::GetLocalPlayer() { return READ_AT(LocalPlayer); }
DWORD S4::GetCurrentTick() { return READ_AT((LPCVOID)READ_AT((LPCVOID)AddIfNotNull(READ_AT(Tick), 0x18))); }
BOOL S4::SendNetEvent(Event_t& event) { if (__SendNetEvent) { __SendNetEvent(&event); return TRUE; } return FALSE; }
BOOL S4::SendLocalEvent(Event_t& event) { 
	if (LocalEvent) {
		LPCVOID pEvent = &event;
		LPCVOID pLocalEvent = (LPCVOID)LocalEvent;
		DWORD dwEcx = READ_AT(Tick); // event engine
		if (!dwEcx) return FALSE;
		__asm {
			push pEvent
			mov ecx, dwEcx
			call pLocalEvent // push event (thiscall)
		}
		return TRUE; 
	} return FALSE; 
}

Event_t::Event_t() { ZeroMemory(this, sizeof(Event_t)); }
Event_t::Event_t(DWORD _4, DWORD _8, DWORD _C, DWORD _10, DWORD _14, DWORD _18) : Event_t() {
	auto ctor = S4::GetInstance().EventConstructor;
	if (ctor) {
		__asm {
			push _4
			push _8
			push _C
			push _10
			push _14
			push _18
			mov eax, ctor
			mov ecx, this
			call eax // thiscall, no need to clean up stack
		}
	}
}
S4_ENTITY_ENUM IEntity::GetClass() {
	switch ((DWORD)GetVtable() - S4_Main) {
	// todo: the following offsets work only for version with md5 c13883cbd796c614365ab2d670ead561
	case 0xc5821c: return S4_ENTITY_ENUM::S4_ENTITY_LANDANIMAL;
	case 0xc585e4: return S4_ENTITY_ENUM::S4_ENTITY_BUILDING;
	case 0xc59710: return S4_ENTITY_ENUM::S4_ENTITY_CART;
	case 0xc59814: return S4_ENTITY_ENUM::S4_ENTITY_CATAPULT_MAYA;
	case 0xc59918: return S4_ENTITY_ENUM::S4_ENTITY_CATAPULT_TROJAN;
	case 0xc59a1c: return S4_ENTITY_ENUM::S4_ENTITY_CATAPULT_ROMAN;
	case 0xc59b20: return S4_ENTITY_ENUM::S4_ENTITY_CATAPULT_VIKING;
	case 0xc59d10: return S4_ENTITY_ENUM::S4_ENTITY_DECO;
	case 0xc59e4c: return S4_ENTITY_ENUM::S4_ENTITY_HIVE;
	case 0xc59ec8: return S4_ENTITY_ENUM::S4_ENTITY_MUSHROOM;
	case 0xc59f44: return S4_ENTITY_ENUM::S4_ENTITY_PLANT;
	case 0xc59fc0: return S4_ENTITY_ENUM::S4_ENTITY_SHADOW_HERB;
	case 0xc5a3b8: return S4_ENTITY_ENUM::S4_ENTITY_MANAKOPTER;
	case 0xc5a7bc: return S4_ENTITY_ENUM::S4_ENTITY_PILE;
	case 0xc5bf20: return S4_ENTITY_ENUM::S4_ENTITY_SETTLER;
	case 0xc5c60c: return S4_ENTITY_ENUM::S4_ENTITY_FERRY;
	case 0xc5c81c: return S4_ENTITY_ENUM::S4_ENTITY_TRANSPORTSHIP;
	case 0xc5c8fc: return S4_ENTITY_ENUM::S4_ENTITY_WARSHIP_TROJAN;
	case 0xc5ca10: return S4_ENTITY_ENUM::S4_ENTITY_WARSHIP_VIKING;
	case 0xc5cb0c: return S4_ENTITY_ENUM::S4_ENTITY_WARSHIP_MAYA;
	case 0xc5cc20: return S4_ENTITY_ENUM::S4_ENTITY_WARSHIP_ROMAN;
	case 0xc5cde8: return S4_ENTITY_ENUM::S4_ENTITY_STONE;
	case 0xc5ce68: return S4_ENTITY_ENUM::S4_ENTITY_TREE;
	default: return S4_ENTITY_ENUM::S4_ENTITY_UNKNOWN;
	}
}

S4_ROLE_ENUM CPersistance::GetRoleClass() {
	// todo: the following offsets work only for version with md5 c13883cbd796c614365ab2d670ead561
	switch ((DWORD)GetVtable() - S4_Main) {
				// Pile Roles
	case 0xc5a66c: return S4_ROLE_ENUM::S4_ROLE_PILE_ANYWHERE;
	case 0xc5a714: return S4_ROLE_ENUM::S4_ROLE_PILE_BUILDING_SITE;
	case 0xc5a768: return S4_ROLE_ENUM::S4_ROLE_PILE_DELIVERY;
	case 0xc5a8fc: return S4_ROLE_ENUM::S4_ROLE_PILE_PRODUCTION;
	case 0xc5a8a8: return S4_ROLE_ENUM::S4_ROLE_PILE_STORAGE;
	case 0xc5a950: return S4_ROLE_ENUM::S4_ROLE_PILE_TRADE;

		// Building Roles
	case 0xc58e84: return S4_ROLE_ENUM::S4_ROLE_BUILDING_WORKUP;  // needs confirmation
	case 0xc5837c: return S4_ROLE_ENUM::S4_ROLE_BUILDING_ANIMALRANCH;
	case 0xc58f8c: return S4_ROLE_ENUM::S4_ROLE_BUILDING_MILITARY; // needs confirmation
	case 0xc58c74: return S4_ROLE_ENUM::S4_ROLE_BUILDING_CASTLE;
	case 0xc5958c: return S4_ROLE_ENUM::S4_ROLE_BUILDING_TRADING;
	case 0xc58484: return S4_ROLE_ENUM::S4_ROLE_BUILDING_BARRACK;
	case 0xc58508: return S4_ROLE_ENUM::S4_ROLE_BUILDING_BIGTEMPLE;
	case 0xc591bc: return S4_ROLE_ENUM::S4_ROLE_BUILDING_SITE;
	case 0xc58ae8: return S4_ROLE_ENUM::S4_ROLE_BUILDING_MUSHROOMFARM;
	case 0xc59284: return S4_ROLE_ENUM::S4_ROLE_BUILDING_DARKTEMPLE;
	case 0xc58b6c: return S4_ROLE_ENUM::S4_ROLE_BUILDING_EYECATCHER;
	case 0xc58cf8: return S4_ROLE_ENUM::S4_ROLE_BUILDING_FARM;
	case 0xc58f08: return S4_ROLE_ENUM::S4_ROLE_BUILDING_GATHER;
	case 0xc58d7c: return S4_ROLE_ENUM::S4_ROLE_BUILDING_LOOKOUTTOWER;
	case 0xc593d0: return S4_ROLE_ENUM::S4_ROLE_BUILDING_MANAKOPTERHALL;
	case 0xc59484: return S4_ROLE_ENUM::S4_ROLE_BUILDING_MINE;
	case 0xc59094: return S4_ROLE_ENUM::S4_ROLE_BUILDING_PRODUCTION;
	case 0xc59010: return S4_ROLE_ENUM::S4_ROLE_BUILDING_RESIDENCE;
	case 0xc58e00: return S4_ROLE_ENUM::S4_ROLE_BUILDING_SIMPLE;
	case 0xc58bf0: return S4_ROLE_ENUM::S4_ROLE_BUILDING_SMALLTEMPLE;
	case 0xc59508: return S4_ROLE_ENUM::S4_ROLE_BUILDING_STORAGE;
	case 0xc59610: return S4_ROLE_ENUM::S4_ROLE_BUILDING_WORKSHOP;

		// Settler Roles
	case 0xc5a9d8: return S4_ROLE_ENUM::S4_ROLE_SETTLER_BUILDER;
	case 0xc5ab08: return S4_ROLE_ENUM::S4_ROLE_SETTLER_CARRIER;
	case 0xc5ad04: return S4_ROLE_ENUM::S4_ROLE_SETTLER_DARKGARDENER;
	case 0xc5ad8c: return S4_ROLE_ENUM::S4_ROLE_SETTLER_DIGGER;
	case 0xc5ae90: return S4_ROLE_ENUM::S4_ROLE_SETTLER_DONKEY;
	case 0xc5af38: return S4_ROLE_ENUM::S4_ROLE_SETTLER_DOOR;
	case 0xc5afc0: return S4_ROLE_ENUM::S4_ROLE_SETTLER_FLEE;
	case 0xc5b2cc: return S4_ROLE_ENUM::S4_ROLE_SETTLER_FREEWORKER;
	case 0xc5b8b0: return S4_ROLE_ENUM::S4_ROLE_SETTLER_HOUSEWORKER;
	case 0xc5bb18: return S4_ROLE_ENUM::S4_ROLE_SETTLER_HUNTER;
	case 0xc5bbf8: return S4_ROLE_ENUM::S4_ROLE_SETTLER_MUSHROOMFARMER;
	case 0xc5c254: return S4_ROLE_ENUM::S4_ROLE_SETTLER_SLAVE;
	case 0xc5c584: return S4_ROLE_ENUM::S4_ROLE_SETTLER_TOWERSOLDIER;

		// The following are selectables
	case 0xc5b51c: return S4_ROLE_ENUM::S4_ROLE_SETTLER_GARDENER;
	case 0xc5b5f8: return S4_ROLE_ENUM::S4_ROLE_SETTLER_GEOLOGIST;
	case 0xc5bc94: return S4_ROLE_ENUM::S4_ROLE_SETTLER_PIONEER;
	case 0xc5bd1c: return S4_ROLE_ENUM::S4_ROLE_SETTLER_PRIEST;
	case 0xc5c4b4: return S4_ROLE_ENUM::S4_ROLE_SETTLER_THIEF;

		// The following roles have a WarriorBehaviour attached. Note that 
		// war machines/ships do not have a role but inherit directly from WarriorBehaviour!
	case 0xc5c3ac: return S4_ROLE_ENUM::S4_ROLE_SETTLER_SOLDIER;
	case 0xc5b7f0: return S4_ROLE_ENUM::S4_ROLE_SETTLER_SQUADLEADER;  // needs confirmation
	case 0xc5b734: return S4_ROLE_ENUM::S4_ROLE_SETTLER_HJB;  // needs confirmation
	case 0xc5c14c: return S4_ROLE_ENUM::S4_ROLE_SETTLER_SHAMAN;
	case 0xc5bdbc: return S4_ROLE_ENUM::S4_ROLE_SETTLER_SABOTEUR;
	default: return S4_ROLE_ENUM::S4_ROLE_UNKNOWN;
	};
}