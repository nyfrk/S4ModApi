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

S4_ENTITY_ENUM CSettlers4Api::EntityGetClass(WORD entity) {
	TRACE;
	auto pool = S4::GetInstance().EntityPool;
	if (pool) {
		auto e = pool[entity];
		if (e) return e->GetClass();
	}
	return S4_ENTITY_ENUM::S4_ENTITY_UNKNOWN;
}

BOOL CSettlers4Api::GetEntitiesCount(WORD* count)
{
	auto size = S4::GetInstance().GetEntityPoolSize();
	*count = size;

	return size;
}


BOOL CSettlers4Api::GetEntities(DWORD* entities, size_t size) {
	TRACE;
	auto pool = S4::GetInstance().EntityPool;
	int counter = 0;

	if (pool) {
		for (size_t i = 1; i <= size; i++) {
			const IEntity* entity = pool[i];
			if (entity != nullptr) {
				if (this->EntityGetClass(entity->id) == S4_ENTITY_SETTLER) {
					int xx = 0123;
					xx++;
				}

				DWORD owner = -1;
				EntitygGetOwner(entity->id, &owner);
				entities[counter] = entity->id;
				counter++;
				
			}
			if (counter >= size) {
				return TRUE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CSettlers4Api::EntityGetPosition(WORD entity, LPINT x, LPINT y) {
	TRACE;
	if (x || y) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e) {
				if (x) *x = e->x;
				if (y) *y = e->y;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntitygGetDirection(WORD entity, LPDWORD dir) {
	TRACE;
	if (dir) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e) {
				*dir = 0;
				//return TRUE; // todo: implement EntitygGetDirection  4 == top-left, etc.
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntityGetHealth(WORD entity, LPDWORD health) {
	TRACE;
	if (health) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e) {
				*health = e->health;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntityGetMaxHealth(WORD entity, LPDWORD maxHealth) {
	TRACE;
	if (maxHealth) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e) {
				DWORD ind;
				ind = (DWORD)e->tribe * (g_isGE ? 0x302 : 0x46);
				ind += (DWORD)e->objectId * (g_isGE ? 11 : 9);
				auto SettlerPrototypes = S4::GetInstance().SettlerPrototypes;
				if (SettlerPrototypes) {
					*maxHealth = (READ_AT(&SettlerPrototypes[ind]) & 0xFF);
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntityGetTribe(WORD entity, S4_TRIBE_ENUM* tribe) {
	TRACE;
	if (tribe) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e) {
				switch (e->tribe) {
				case 0: *tribe = S4_TRIBE_ENUM::S4_TRIBE_ROMAN; break;
				case 1: *tribe = S4_TRIBE_ENUM::S4_TRIBE_VIKING; break;
				case 2: *tribe = S4_TRIBE_ENUM::S4_TRIBE_MAYA; break;
				case 3: *tribe = S4_TRIBE_ENUM::S4_TRIBE_DARK; break;
				case 4: *tribe = S4_TRIBE_ENUM::S4_TRIBE_TROJAN; break;
				default: return FALSE;
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntityTreeGetType(WORD entity, S4_TREE_ENUM* tree) {
	TRACE;
	if (tree) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e && e->GetClass() == S4_ENTITY_TREE) {
				*tree = (S4_TREE_ENUM)e->objectId;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntityPileGetType(WORD entity, S4_GOOD_ENUM* good) {
	TRACE;
	if (good) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e && e->GetClass() == S4_ENTITY_PILE) {
				CPile* pile = (CPile*)e;
				*good = (S4_GOOD_ENUM)pile->goodType;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntityPileGetAmount(WORD entity, LPDWORD amount) {
	TRACE;
	if (amount) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e && e->GetClass() == S4_ENTITY_PILE) {
				CPile* pile = (CPile*)e;
				*amount = pile->amount;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntityDecoGetType(WORD entity, LPDWORD deco) {
	TRACE;
	if (deco) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e && e->GetClass() == S4_ENTITY_DECO) {
				*deco = e->objectId;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntitySettlerGetType(WORD entity, S4_SETTLER_ENUM* settler) {
	TRACE;
	if (settler) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e && e->GetClass() == S4_ENTITY_SETTLER) {
				*settler = (S4_SETTLER_ENUM)e->objectId;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntityVehicleGetType(WORD entity, S4_VEHICLE_ENUM* vehicle) {
	TRACE;
	if (vehicle) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e) {
				switch (e->GetClass()) {
					case S4_ENTITY_CART: *vehicle = S4_VEHICLE_CART; break;
					case S4_ENTITY_CATAPULT_MAYA: 
					case S4_ENTITY_CATAPULT_VIKING: 
					case S4_ENTITY_CATAPULT_ROMAN: 
					case S4_ENTITY_CATAPULT_TROJAN: *vehicle = S4_VEHICLE_WARMACHINE; break;
					case S4_ENTITY_FERRY:			*vehicle = S4_VEHICLE_FERRY; break;
					case S4_ENTITY_WARSHIP_MAYA: 
					case S4_ENTITY_WARSHIP_VIKING: 
					case S4_ENTITY_WARSHIP_ROMAN: 
					case S4_ENTITY_WARSHIP_TROJAN: *vehicle = S4_VEHICLE_WARSHIP; break;
					case S4_ENTITY_TRANSPORTSHIP: *vehicle = S4_VEHICLE_TRANSPORTSHIP; break;
					//case S4_ENTITY_MANAKOPTER: *vehicle = S4_VEHICLE_MANAKOPTER; break;
					default: return FALSE;
				}
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntityAnimalGetType(WORD entity, S4_ANIMAL_ENUM* animal) {
	TRACE;
	if (animal) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e && e->GetClass() == S4_ENTITY_LANDANIMAL) {
				*animal = (S4_ANIMAL_ENUM)e->objectId;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntityBuildingGetType(WORD entity, S4_BUILDING_ENUM* building) {
	TRACE;
	if (building) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e && e->GetClass() == S4_ENTITY_BUILDING) {
				*building = (S4_BUILDING_ENUM)e->objectId;
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntityStoneGetLevel(WORD entity, LPDWORD level) {
	TRACE;
	if (level) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e && e->GetClass() == S4_ENTITY_STONE) {
				return FALSE; //*level = e->; // todo: reverse me, probably just have to switch the object id of the dark stone and green stone
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntityGetRole(WORD entity, LPVOID* role) {
	TRACE;
	if (role) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e) {
				switch (e->GetClass()) {
					case S4_ENTITY_SETTLER: *role = ((CSettler*)e)->role; break;
					case S4_ENTITY_BUILDING: *role = ((CBuilding*)e)->role; break;
					case S4_ENTITY_PILE: *role = ((CPile*)e)->role; break;
					default: return FALSE;
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CSettlers4Api::EntitygGetRoleClass(WORD entity, S4_ROLE_ENUM* role) {
	TRACE;
	CPersistance* roleInst = nullptr; // role instances inherit from CPersistance
	if (role && EntityGetRole(entity, (LPVOID*)&roleInst) && roleInst) {
		*role = roleInst->GetRoleClass();
		return TRUE;
	}
	return FALSE;
}

BOOL CSettlers4Api::EntitygGetOwner(WORD entity, LPDWORD player) {
	TRACE;
	if (player) {
		auto pool = S4::GetInstance().EntityPool;
		if (pool) {
			auto e = pool[entity];
			if (e) {
				switch (e->GetClass()) {
					case S4_ENTITY_ENUM::S4_ENTITY_LANDANIMAL:
					case S4_ENTITY_ENUM::S4_ENTITY_DECO:
					case S4_ENTITY_ENUM::S4_ENTITY_HIVE:
					case S4_ENTITY_ENUM::S4_ENTITY_MUSHROOM: // better choose a dark tribe player somehow?
					case S4_ENTITY_ENUM::S4_ENTITY_PLANT:
					case S4_ENTITY_ENUM::S4_ENTITY_SHADOW_HERB:
					case S4_ENTITY_ENUM::S4_ENTITY_PILE:
					case S4_ENTITY_ENUM::S4_ENTITY_STONE:
					case S4_ENTITY_ENUM::S4_ENTITY_TREE:
					case S4_ENTITY_ENUM::S4_ENTITY_BUILDING: // owner is always that one whose terretory it is placed
						// these objects do not directly have an owner, so we return the owner 
						// of the map position at this object
						*player = S4::GetInstance().GetOwnerAt(e->x, e->y);
						return TRUE;

					case S4_ENTITY_ENUM::S4_ENTITY_CART:
					case S4_ENTITY_ENUM::S4_ENTITY_CATAPULT_MAYA:
					case S4_ENTITY_ENUM::S4_ENTITY_CATAPULT_TROJAN:
					case S4_ENTITY_ENUM::S4_ENTITY_CATAPULT_ROMAN:
					case S4_ENTITY_ENUM::S4_ENTITY_CATAPULT_VIKING:
					case S4_ENTITY_ENUM::S4_ENTITY_MANAKOPTER:
					case S4_ENTITY_ENUM::S4_ENTITY_SETTLER:
					case S4_ENTITY_ENUM::S4_ENTITY_FERRY:
					case S4_ENTITY_ENUM::S4_ENTITY_TRANSPORTSHIP:
					case S4_ENTITY_ENUM::S4_ENTITY_WARSHIP_TROJAN:
					case S4_ENTITY_ENUM::S4_ENTITY_WARSHIP_VIKING:
					case S4_ENTITY_ENUM::S4_ENTITY_WARSHIP_MAYA:
					case S4_ENTITY_ENUM::S4_ENTITY_WARSHIP_ROMAN:
						*player = e->player;
						return TRUE;
				};
			}
		}
	}
	return FALSE;
}
