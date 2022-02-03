///////////////////////////////////////////////////////////////////////////////
// MIT License
//
// Copyright (c) 2022 nyfrk <nyfrk@gmx.net> and contributors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#define COM_NO_WINDOWS_H
#include <objbase.h>
#include <ddraw.h>

#define S4HCALL __stdcall

extern "C" {

#define IID_ISettlers4Api __uuidof(ISettlers4Api)

interface __declspec(uuid("b3b5169a-dca0-493c-c08e-99ca36c2b863")) ISettlers4Api;


typedef interface ISettlers4Api  FAR * LPSETTLERS4API;
typedef interface ISettlers4Api2 FAR * LPSETTLERS4API2;

#define S4API LPSETTLERS4API

typedef UINT32 S4HOOK;
typedef LPVOID S4CUSTOMUI;

enum S4_EDITION_ENUM : DWORD {
	S4_EDITION_GOLD = 1,
	S4_EDITION_HISTORY = 2,
};

enum S4_ENTITY_ENUM : BYTE {
	S4_ENTITY_UNKNOWN,

	S4_ENTITY_BUILDING,
	S4_ENTITY_PILE,

	// Ground Mobile Entities
		// Settler
			S4_ENTITY_SETTLER,
		// Animal
			S4_ENTITY_LANDANIMAL,
		// Vehicles
			// Wheelers
				S4_ENTITY_CART,
				// Catapult
					S4_ENTITY_CATAPULT_MAYA,
					S4_ENTITY_CATAPULT_TROJAN,
					S4_ENTITY_CATAPULT_ROMAN,
					S4_ENTITY_CATAPULT_VIKING,
			// Ships
				S4_ENTITY_FERRY,
				S4_ENTITY_TRANSPORTSHIP,
				// War Ship
					S4_ENTITY_WARSHIP_MAYA,
					S4_ENTITY_WARSHIP_TROJAN,
					S4_ENTITY_WARSHIP_ROMAN,
					S4_ENTITY_WARSHIP_VIKING,

	// Flying Mobile Entites
		S4_ENTITY_MANAKOPTER,

	// Stationary Deco Entities
		S4_ENTITY_DECO,
		S4_ENTITY_HIVE,
		S4_ENTITY_MUSHROOM,
		S4_ENTITY_PLANT,
		S4_ENTITY_SHADOW_HERB,
		S4_ENTITY_STONE,
		S4_ENTITY_TREE,
};

enum S4_GROUND_ENUM : BYTE {
	WATER1 = 0, // water1 does only exist without waves (it ignores the pond flag)
	WATER2 = 1, // this ground respects the pond flag
	WATER3 = 2, // this ground respects the pond flag
	WATER4 = 3, // this ground respects the pond flag
	WATER5 = 4, // this ground respects the pond flag
	WATER6 = 5, // this ground respects the pond flag
	WATER7 = 6, // this ground respects the pond flag
	WATER8 = 7, // deep sea, this ground respects the pond flag
	GRASS = 16,
	GRASS_ROCK = 17, // transition triangles only: grass grass rock
	GRASS_ISLE = 18,
	GRASS_DESERT = 20, // transition triangles only: grass grass desert
	GRASS_SWAMP = 21, // transition triangles only: grass grass swamp
	GRASS_MUD = 23,  // transition triangles only: grass grass mud
	DARKGRASS = 24, 
	DARKGRASS_GRASS = 25, // transition triangles only: darkgrass darkgrass grass
	SANDYROAD = 28,
	COBBLEDROAD = 29,
	ROCK = 32,
	ROCK_GRASS = 33, // transition triangles only: rock rock grass
	ROCK_SNOW = 35, // transition triangles only: rock rock snow
	BEACH = 48,
	DESERT = 64,
	DESERT_GRASS = 65, // transition triangles only: desert desert grass
	SWAMP = 80,
	SWAMP_GRASS = 81, // transition triangles only: swamp swamp grass
	RIVER1 = 96,
	RIVER2 = 97,
	RIVER3 = 98,
	RIVER4 = 99,
	SNOW = 128,
	SNOW_ROCK = 129,  // transition triangles only: snow snow rock
	MUD = 144,
	MUD_GRASS = 145,  // transition triangles only: mud mud grass
};

enum S4_RESOURCE_ENUM : BYTE {
	S4_RESOURCE_NONE,
	S4_RESOURCE_FISH_1,	S4_RESOURCE_FISH_2, S4_RESOURCE_FISH_3, S4_RESOURCE_FISH_4, S4_RESOURCE_FISH_5, S4_RESOURCE_FISH_6, S4_RESOURCE_FISH_7, S4_RESOURCE_FISH_8, S4_RESOURCE_FISH_9, S4_RESOURCE_FISH_10, S4_RESOURCE_FISH_11, S4_RESOURCE_FISH_12, S4_RESOURCE_FISH_13, S4_RESOURCE_FISH_14, S4_RESOURCE_FISH_15, S4_RESOURCE_FISH_16,
	S4_RESOURCE_COAL_1, S4_RESOURCE_COAL_2, S4_RESOURCE_COAL_3, S4_RESOURCE_COAL_4, S4_RESOURCE_COAL_5, S4_RESOURCE_COAL_6, S4_RESOURCE_COAL_7, S4_RESOURCE_COAL_8, S4_RESOURCE_COAL_9, S4_RESOURCE_COAL_10, S4_RESOURCE_COAL_11, S4_RESOURCE_COAL_12, S4_RESOURCE_COAL_13, S4_RESOURCE_COAL_14, S4_RESOURCE_COAL_15, S4_RESOURCE_COAL_16,
	S4_RESOURCE_IRON_1, S4_RESOURCE_IRON_2, S4_RESOURCE_IRON_3, S4_RESOURCE_IRON_4, S4_RESOURCE_IRON_5, S4_RESOURCE_IRON_6, S4_RESOURCE_IRON_7, S4_RESOURCE_IRON_8, S4_RESOURCE_IRON_9, S4_RESOURCE_IRON_10, S4_RESOURCE_IRON_11, S4_RESOURCE_IRON_12, S4_RESOURCE_IRON_13, S4_RESOURCE_IRON_14, S4_RESOURCE_IRON_15, S4_RESOURCE_IRON_16,
	S4_RESOURCE_GOLD_1, S4_RESOURCE_GOLD_2, S4_RESOURCE_GOLD_3, S4_RESOURCE_GOLD_4, S4_RESOURCE_GOLD_5, S4_RESOURCE_GOLD_6, S4_RESOURCE_GOLD_7, S4_RESOURCE_GOLD_8, S4_RESOURCE_GOLD_9, S4_RESOURCE_GOLD_10, S4_RESOURCE_GOLD_11, S4_RESOURCE_GOLD_12, S4_RESOURCE_GOLD_13, S4_RESOURCE_GOLD_14, S4_RESOURCE_GOLD_15, S4_RESOURCE_GOLD_16,
	S4_RESOURCE_SULPHUR_1, S4_RESOURCE_SULPHUR_2, S4_RESOURCE_SULPHUR_3, S4_RESOURCE_SULPHUR_4, S4_RESOURCE_SULPHUR_5, S4_RESOURCE_SULPHUR_6, S4_RESOURCE_SULPHUR_7, S4_RESOURCE_SULPHUR_8, S4_RESOURCE_SULPHUR_9, S4_RESOURCE_SULPHUR_10, S4_RESOURCE_SULPHUR_11, S4_RESOURCE_SULPHUR_12, S4_RESOURCE_SULPHUR_13, S4_RESOURCE_SULPHUR_14, S4_RESOURCE_SULPHUR_15, S4_RESOURCE_SULPHUR_16,
	S4_RESOURCE_STONEMINE_1, S4_RESOURCE_STONEMINE_2, S4_RESOURCE_STONEMINE_3, S4_RESOURCE_STONEMINE_4, S4_RESOURCE_STONEMINE_5, S4_RESOURCE_STONEMINE_6, S4_RESOURCE_STONEMINE_7, S4_RESOURCE_STONEMINE_8, S4_RESOURCE_STONEMINE_9, S4_RESOURCE_STONEMINE_10, S4_RESOURCE_STONEMINE_11, S4_RESOURCE_STONEMINE_12, S4_RESOURCE_STONEMINE_13, S4_RESOURCE_STONEMINE_14, S4_RESOURCE_STONEMINE_15, S4_RESOURCE_STONEMINE_16,
	S4_RESOURCE_STONE_1, S4_RESOURCE_STONE_2, S4_RESOURCE_STONE_3, S4_RESOURCE_STONE_4, S4_RESOURCE_STONE_5, S4_RESOURCE_STONE_6, S4_RESOURCE_STONE_7, S4_RESOURCE_STONE_8, S4_RESOURCE_STONE_9, S4_RESOURCE_STONE_10, S4_RESOURCE_STONE_11, S4_RESOURCE_STONE_12, S4_RESOURCE_STONE_13, S4_RESOURCE_STONE_14, S4_RESOURCE_STONE_15, S4_RESOURCE_STONE_16,
	S4_RESOURCE_WOOD, // trees
};

// Roles define what an entity "does" or is destined for. You may create custom 
// roles for entities. Just make sure to implement the proper Role interface for 
// the entity type (building/pile/settler) you wish to program.
enum S4_ROLE_ENUM : BYTE {
	S4_ROLE_UNKNOWN,
	
	// Pile Roles
	S4_ROLE_PILE_ANYWHERE,
	S4_ROLE_PILE_BUILDING_SITE,
	S4_ROLE_PILE_DELIVERY,
	S4_ROLE_PILE_PRODUCTION,
	S4_ROLE_PILE_STORAGE,
	S4_ROLE_PILE_TRADE,

	// Building Roles
	S4_ROLE_BUILDING_WORKUP,  // needs confirmation
	S4_ROLE_BUILDING_ANIMALRANCH,
	S4_ROLE_BUILDING_MILITARY, // needs confirmation
	S4_ROLE_BUILDING_CASTLE,
	S4_ROLE_BUILDING_TRADING,
	S4_ROLE_BUILDING_BARRACK,
	S4_ROLE_BUILDING_BIGTEMPLE,
	S4_ROLE_BUILDING_SITE,
	S4_ROLE_BUILDING_MUSHROOMFARM,
	S4_ROLE_BUILDING_DARKTEMPLE,
	S4_ROLE_BUILDING_EYECATCHER,
	S4_ROLE_BUILDING_FARM,
	S4_ROLE_BUILDING_GATHER,
	S4_ROLE_BUILDING_LOOKOUTTOWER,
	S4_ROLE_BUILDING_MANAKOPTERHALL,
	S4_ROLE_BUILDING_MINE,
	S4_ROLE_BUILDING_PRODUCTION,
	S4_ROLE_BUILDING_RESIDENCE,
	S4_ROLE_BUILDING_SIMPLE,
	S4_ROLE_BUILDING_SMALLTEMPLE,
	S4_ROLE_BUILDING_STORAGE,
	S4_ROLE_BUILDING_WORKSHOP,

	// Settler Roles
	S4_ROLE_SETTLER_BUILDER,
	S4_ROLE_SETTLER_CARRIER,
	S4_ROLE_SETTLER_DARKGARDENER,
	S4_ROLE_SETTLER_DIGGER,
	S4_ROLE_SETTLER_DONKEY,
	S4_ROLE_SETTLER_DOOR,
	S4_ROLE_SETTLER_FLEE,
	S4_ROLE_SETTLER_FREEWORKER,
	S4_ROLE_SETTLER_HOUSEWORKER,
	S4_ROLE_SETTLER_HUNTER,
	S4_ROLE_SETTLER_MUSHROOMFARMER,
	S4_ROLE_SETTLER_SLAVE,
	S4_ROLE_SETTLER_TOWERSOLDIER,

	// The following are selectables
	S4_ROLE_SETTLER_GARDENER,
	S4_ROLE_SETTLER_GEOLOGIST,
	S4_ROLE_SETTLER_PIONEER,
	S4_ROLE_SETTLER_PRIEST,
	S4_ROLE_SETTLER_THIEF,

	// The following roles have a WarriorBehaviour attached. Note that 
	// war machines/ships do not have a role but inherit directly from WarriorBehaviour!
	S4_ROLE_SETTLER_SOLDIER,
	S4_ROLE_SETTLER_SQUADLEADER,  // needs confirmation
	S4_ROLE_SETTLER_HJB,  // needs confirmation
	S4_ROLE_SETTLER_SHAMAN,
	S4_ROLE_SETTLER_SABOTEUR,
};

enum S4_TRIBE_ENUM : BYTE {
	S4_TRIBE_NONE = 255,
	S4_TRIBE_ANY = 254,
	S4_TRIBE_ROMAN = 0, // tribe 0
	S4_TRIBE_VIKING,
	S4_TRIBE_MAYA,
	S4_TRIBE_DARK,
	S4_TRIBE_TROJAN,
};

enum S4_GOOD_ENUM : BYTE {
	S4_GOOD_NONE = 0,
	S4_GOOD_AGAVE, // good id 1
	S4_GOOD_AMMO,
	S4_GOOD_ARMOR,
	S4_GOOD_AXE,
	S4_GOOD_BATTLEAXE,
	S4_GOOD_BLOWGUN,
	S4_GOOD_BOARD,
	S4_GOOD_BOW,
	S4_GOOD_BREAD,
	S4_GOOD_COAL, // 10
	S4_GOOD_FISH,
	S4_GOOD_FLOUR,
	S4_GOOD_GOAT,
	S4_GOOD_GOLDBAR,
	S4_GOOD_GOLDORE,
	S4_GOOD_GRAIN,
	S4_GOOD_GUNPOWDER,
	S4_GOOD_HAMMER,
	S4_GOOD_HONEY,
	S4_GOOD_IRONBAR,// 20
	S4_GOOD_IRONORE,
	S4_GOOD_LOG,
	S4_GOOD_MEAD,
	S4_GOOD_MEAT,
	S4_GOOD_PICKAXE,
	S4_GOOD_PIG,
	S4_GOOD_ROD,
	S4_GOOD_SAW,
	S4_GOOD_SCYTHE,
	S4_GOOD_SHEEP, // 30
	S4_GOOD_SHOVEL,
	S4_GOOD_STONE,
	S4_GOOD_SULFUR,
	S4_GOOD_SWORD,
	S4_GOOD_TEQUILA,
	S4_GOOD_WATER,
	S4_GOOD_WINE,
	S4_GOOD_BACKPACKCATAPULT,
	S4_GOOD_GOOSE,
	S4_GOOD_EXPLOSIVEARROW, // 40
	S4_GOOD_SUNFLOWEROIL,
	S4_GOOD_SUNFLOWER, // good id 42
};

enum S4_BUILDING_ENUM : BYTE {
	S4_BUILDING_NONE = 0,
	//S4_BUILDING_READY,
	//S4_BUILDING_UNDERCONSTRUCTION,
	S4_BUILDING_WOODCUTTERHUT, // building id 1
	S4_BUILDING_FORESTERHUT,
	S4_BUILDING_SAWMILL,
	S4_BUILDING_STONECUTTERHUT,
	S4_BUILDING_WATERWORKHUT,
	S4_BUILDING_FISHERHUT,
	S4_BUILDING_HUNTERHUT,
	S4_BUILDING_SLAUGHTERHOUSE,
	S4_BUILDING_MILL,
	S4_BUILDING_BAKERY, // 10
	S4_BUILDING_GRAINFARM,
	S4_BUILDING_ANIMALRANCH,
	S4_BUILDING_DONKEYRANCH,
	S4_BUILDING_STONEMINE,
	S4_BUILDING_IRONMINE,
	S4_BUILDING_GOLDMINE,
	S4_BUILDING_COALMINE,
	S4_BUILDING_SULFURMINE,
	S4_BUILDING_SMELTGOLD,
	S4_BUILDING_SMELTIRON, // 20
	S4_BUILDING_TOOLSMITH,
	S4_BUILDING_WEAPONSMITH,
	S4_BUILDING_VEHICLEHALL,
	S4_BUILDING_BARRACKS,
	S4_BUILDING_CHARCOALMAKER,
	S4_BUILDING_TRAININGCENTER,
	S4_BUILDING_HEALERHUT,
	S4_BUILDING_AMMOMAKERHUT,
	S4_BUILDING_GUNPOWDERMAKERHUT,
	S4_BUILDING_LANDSCAPEMAKERHUT, // 30
	S4_BUILDING_SHIPYARD,
	S4_BUILDING_PORT,
	S4_BUILDING_MARKETPLACE,
	S4_BUILDING_STORAGEAREA,
	S4_BUILDING_VINYARD,
	S4_BUILDING_AGAVEFARMERHUT,
	S4_BUILDING_TEQUILAMAKERHUT,
	S4_BUILDING_BEEKEEPERHUT,
	S4_BUILDING_MEADMAKERHUT,
	S4_BUILDING_RESIDENCESMALL,// 40
	S4_BUILDING_RESIDENCEMEDIUM,
	S4_BUILDING_RESIDENCEBIG,
	S4_BUILDING_SMALLTEMPLE,
	S4_BUILDING_BIGTEMPLE,
	S4_BUILDING_LOOKOUTTOWER,
	S4_BUILDING_GUARDTOWERSMALL,
	S4_BUILDING_GUARDTOWERBIG,
	S4_BUILDING_CASTLE,
	S4_BUILDING_MUSHROOMFARM,
	S4_BUILDING_DARKTEMPLE, // 50
	S4_BUILDING_FORTRESS,
	S4_BUILDING_PORTA,
	S4_BUILDING_PORTB,
	S4_BUILDING_PORTC,
	S4_BUILDING_PORTD,
	S4_BUILDING_PORTE,
	S4_BUILDING_PORTF,
	S4_BUILDING_SHIPYARDA,
	S4_BUILDING_SHIPYARDB,
	S4_BUILDING_SHIPYARDC,
	S4_BUILDING_SHIPYARDD,
	S4_BUILDING_SHIPYARDE,
	S4_BUILDING_SHIPYARDF,
	S4_BUILDING_EYECATCHER01,
	S4_BUILDING_EYECATCHER02,
	S4_BUILDING_EYECATCHER03,
	S4_BUILDING_EYECATCHER04,
	S4_BUILDING_EYECATCHER05,
	S4_BUILDING_EYECATCHER06,
	S4_BUILDING_EYECATCHER07,
	S4_BUILDING_EYECATCHER08,
	S4_BUILDING_EYECATCHER09,
	S4_BUILDING_EYECATCHER10,
	S4_BUILDING_EYECATCHER11,
	S4_BUILDING_EYECATCHER12,
	S4_BUILDING_SHIPYARDG,
	S4_BUILDING_SHIPYARDH,
	S4_BUILDING_PORTG,
	S4_BUILDING_PORTH,
	S4_BUILDING_MANACOPTERHALL,
	S4_BUILDING_SUNFLOWEROILMAKERHUT,
	S4_BUILDING_SUNFLOWERFARMERHUT,
};

enum S4_SETTLER_ENUM : BYTE {
	S4_SETTLER_NONE = 0,
	S4_SETTLER_CARRIER, // settler id 1
	S4_SETTLER_DIGGER,
	S4_SETTLER_BUILDER,
	S4_SETTLER_WOODCUTTER,
	S4_SETTLER_STONECUTTER,
	S4_SETTLER_FORESTER,
	S4_SETTLER_FARMERGRAIN,
	S4_SETTLER_FARMERANIMALS,
	S4_SETTLER_FISHER,
	S4_SETTLER_WATERWORKER,
	S4_SETTLER_HUNTER,
	S4_SETTLER_SAWMILLWORKER,
	S4_SETTLER_SMELTER,
	S4_SETTLER_MINEWORKER,
	S4_SETTLER_SMITH,
	S4_SETTLER_MILLER,
	S4_SETTLER_BAKER,
	S4_SETTLER_BUTCHER,
	S4_SETTLER_SHIPYARDWORKER,
	S4_SETTLER_HEALER,
	S4_SETTLER_CHARCOALMAKER,
	S4_SETTLER_AMMOMAKER,
	S4_SETTLER_VEHICLEMAKER,
	S4_SETTLER_VINTNER,
	S4_SETTLER_BEEKEEPER,
	S4_SETTLER_MEADMAKER,
	S4_SETTLER_AGAVEFARMER,
	S4_SETTLER_TEQUILAMAKER,
	S4_SETTLER_SWORDSMAN_01,
	S4_SETTLER_DARK_WARRIOR = S4_SETTLER_SWORDSMAN_01,
	S4_SETTLER_SWORDSMAN_02,
	S4_SETTLER_SWORDSMAN_03,
	S4_SETTLER_BOWMAN_01,
	S4_SETTLER_DARK_THROWER = S4_SETTLER_BOWMAN_01,
	S4_SETTLER_BOWMAN_02,
	S4_SETTLER_BOWMAN_03,
	S4_SETTLER_MEDIC_01,
	S4_SETTLER_MEDIC_02,
	S4_SETTLER_MEDIC_03,
	S4_SETTLER_AXEWARRIOR_01,
	S4_SETTLER_AXEWARRIOR_02,
	S4_SETTLER_AXEWARRIOR_03,
	S4_SETTLER_BLOWGUNWARRIOR_01,
	S4_SETTLER_BLOWGUNWARRIOR_02,
	S4_SETTLER_BLOWGUNWARRIOR_03,
	S4_SETTLER_SQUADLEADER,
	S4_SETTLER_PRIEST,
	S4_SETTLER_SABOTEUR,
	S4_SETTLER_PIONEER,
	S4_SETTLER_THIEF,
	S4_SETTLER_GEOLOGIST,
	S4_SETTLER_GARDENER,
	S4_SETTLER_LANDSCAPER,
	S4_SETTLER_DARKGARDENER,
	S4_SETTLER_MUSHROOMFARMER,
	S4_SETTLER_SHAMAN,
	S4_SETTLER_SLAVED_SETTLER,
	S4_SETTLER_TEMPLE_SERVANT,
	S4_SETTLER_ANGEL_01,
	S4_SETTLER_ANGEL_02,
	S4_SETTLER_ANGEL_03,
	S4_SETTLER_DONKEY,
	S4_SETTLER_BACKPACKCATAPULTIST_01,
	S4_SETTLER_BACKPACKCATAPULTIST_02,
	S4_SETTLER_BACKPACKCATAPULTIST_03,
	S4_SETTLER_SUNFLOWERFARMER,
	S4_SETTLER_SUNFLOWEROILMAKER,
	S4_SETTLER_MANACOPTERMASTER,

	S4_SETTLER_UNK68 = 68, // The first 6 entities of a game are this. Maybe the spawn flags set in the editor?
	S4_SETTLER_UNK69 = 69, // Probably door swordman of a tower
};

enum S4_ANIMAL_ENUM : BYTE {
	S4_ANIMAL_NONE = 0,
	S4_ANIMAL_HOG = 1,
	S4_ANIMAL_BUG_1 = 2, // unconfirmed, is it an IEntity?
	S4_ANIMAL_BUG_2 = 3, // unconfirmed, is it an IEntity?
	S4_ANIMAL_DEER_FEMALE = 4,
	S4_ANIMAL_DEER_MALE = 5,
	S4_ANIMAL_FOX = 6,
	S4_ANIMAL_CHICKEN = 7, // unconfirmed, is it an IEntity?
	S4_ANIMAL_JAGUAR = 8, // unconfirmed
	S4_ANIMAL_BUNNY_RED = 9,
	S4_ANIMAL_DOLPHIN = 10, // unconfirmed, probably not an IEntity
	S4_ANIMAL_SEA_MONSTER = 11, // unconfirmed, probably not an IEntity
	S4_ANIMAL_SHARK = 12, // unconfirmed, probably not an IEntity
	S4_ANIMAL_BEAR = 13, // unconfirmed
	S4_ANIMAL_WOLF = 14, // unconfirmed
	S4_ANIMAL_FISH = 15, // unconfirmed, probably not an IEntity
	S4_ANIMAL_BUNNY_GRAY = 16,
	S4_ANIMAL_BULL = 17, // unconfirmed
	S4_ANIMAL_SEAGUL = 0, // unknown, probably an effect?
	S4_ANIMAL_DONKEY = 0, // unknown, probably an ISettler?
	S4_ANIMAL_BUTTERFLY_1 = 0, // unknown, probably an effect?
	S4_ANIMAL_BUTTERFLY_2 = 0, // unknown, probably an effect?
	S4_ANIMAL_BUTTERFLY_3 = 0, // unknown, probably an effect?
	S4_ANIMAL_DUCK_MALE = 0,  // unknown, probably an effect?
	S4_ANIMAL_DUCK_FEMALE = 0,  // unknown, probably an effect?
	S4_ANIMAL_PARROT = 0,  // unknown, probably an effect?
};

enum S4_VEHICLE_ENUM : BYTE {
	S4_VEHICLE_NONE = 0,
	S4_VEHICLE_WARSHIP, // vehicle id 1
	S4_VEHICLE_FERRY,
	S4_VEHICLE_TRANSPORTSHIP,
	S4_VEHICLE_WARMACHINE,
	S4_VEHICLE_CART,
	S4_VEHICLE_FOUNDATION_CART,
};

enum S4_TREE_ENUM : BYTE {
	S4_TREE_NONE = 0,
	S4_TREE_OAK = 1,
	S4_TREE_BEECH = 2,
	S4_TREE_ASH = 3,
	S4_TREE_LINDEN = 4,
	S4_TREE_BIRCH = 5,
	S4_TREE_POPLAR = 6,
	S4_TREE_CHESTNUT = 7,
	S4_TREE_MAPLE = 8,
	S4_TREE_FIR = 9,
	S4_TREE_SPRUCE = 10,
	S4_TREE_COCONUT = 11,
	S4_TREE_DATE = 12,
	S4_TREE_WALNUT = 13,
	S4_TREE_CORKOAK = 14,
	S4_TREE_PINE = 15,
	S4_TREE_PINE2 = 16,
	S4_TREE_OLIVE_LARGE = 17,
	S4_TREE_OLIVE_SMALL = 18,

	// Trees the tribes grow
	S4_TREE_ROMAN_1 = S4_TREE_FIR,
	S4_TREE_ROMAN_2 = S4_TREE_SPRUCE,
	S4_TREE_VIKING_1 = S4_TREE_FIR,
	S4_TREE_VIKING_2 = S4_TREE_SPRUCE,
	S4_TREE_MAYA_1 = S4_TREE_WALNUT,
	S4_TREE_MAYA_2 = S4_TREE_CORKOAK,
	S4_TREE_TROJAN_1 = S4_TREE_PINE,
	S4_TREE_TROJAN_2 = S4_TREE_PINE2,
	S4_TREE_TROJAN_3 = S4_TREE_OLIVE_LARGE,
	S4_TREE_TROJAN_4 = S4_TREE_OLIVE_SMALL,
};

enum S4_OBJECT_ENUM : BYTE { // plants and stuff
	S4_OBJECT_NONE = 0,
	S4_OBJECT_1 = 1,
	S4_OBJECT_WHEAT = S4_OBJECT_1 + 208,
	S4_OBJECT_SUNFLOWER = S4_OBJECT_1 + 254,
	// todo: add all objects
};

enum S4_SPELL_ENUM : BYTE {
	S4_SPELL_NONE = 0,
	S4_SPELL_1,
	S4_SPELL_2,
	S4_SPELL_3,
	S4_SPELL_4,
	S4_SPELL_5,
	S4_SPELL_6,
	S4_SPELL_7,
	S4_SPELL_8,
};

enum S4_GUI_ENUM : DWORD {
	S4_GUI_UNKNOWN=0,
	S4_SCREEN_MAINMENU=1,
	S4_SCREEN_TUTORIAL,
	S4_SCREEN_ADDON,
	S4_SCREEN_MISSIONCD,
	S4_SCREEN_NEWWORLD,
	S4_SCREEN_NEWWORLD2,
	S4_SCREEN_SINGLEPLAYER,
	S4_SCREEN_MULTIPLAYER,
	S4_SCREEN_LOADGAME,
	S4_SCREEN_CREDITS,
	S4_SCREEN_ADDON_TROJAN,
	S4_SCREEN_ADDON_ROMAN,
	S4_SCREEN_ADDON_MAYAN,
	S4_SCREEN_ADDON_VIKING,
	S4_SCREEN_ADDON_SETTLE,
	S4_SCREEN_MISSIONCD_ROMAN,
	S4_SCREEN_MISSIONCD_VIKING,
	S4_SCREEN_MISSIONCD_MAYAN,
	S4_SCREEN_MISSIONCD_CONFL,
	S4_SCREEN_SINGLEPLAYER_CAMPAIGN,
	S4_SCREEN_SINGLEPLAYER_DARKTRIBE,
	S4_SCREEN_SINGLEPLAYER_MAPSELECT_SINGLE,
	S4_SCREEN_SINGLEPLAYER_MAPSELECT_MULTI,
	S4_SCREEN_SINGLEPLAYER_MAPSELECT_RANDOM,
	S4_SCREEN_SINGLEPLAYER_MAPSELECT_USER,
	S4_SCREEN_SINGLEPLAYER_LOBBY,
	S4_SCREEN_MULTIPLAYER_MAPSELECT_MULTI,
	S4_SCREEN_MULTIPLAYER_MAPSELECT_RANDOM,
	S4_SCREEN_MULTIPLAYER_MAPSELECT_USER,
	S4_SCREEN_MULTIPLAYER_LOBBY,
	S4_SCREEN_LOADGAME_CAMPAIGN,
	S4_SCREEN_LOADGAME_MAP,
	S4_SCREEN_LOADGAME_MULTIPLAYER,
	S4_SCREEN_AFTERGAME_SUMMARY,
	S4_SCREEN_AFTERGAME_DETAILS,
	S4_SCREEN_INGAME,
	S4_SCREEN_MISSION_DESCRIPTION,
	S4_MENU_EXTRAS_SAVE,
	S4_MENU_EXTRAS_MISSION,
	S4_MENU_EXTRAS_CHATSETTINGS,
	S4_MENU_EXTRAS_QUIT,
	S4_MENU_SETTINGS_GRAPHICS,
	S4_MENU_SETTINGS_AUDIO,
	S4_MENU_SETTINGS_GAME,
	S4_MENU_SETTINGS_NOTIFICATIONS,
	S4_MENU_BUILDINGS_FOUNDATION,
	S4_MENU_BUILDINGS_METAL,
	S4_MENU_BUILDINGS_FOOD,
	S4_MENU_BUILDINGS_MISC,
	S4_MENU_BUILDINGS_MISC_DECOSUB,
	S4_MENU_BUILDINGS_MILITARY,
	S4_MENU_SETTLERS_SUMMARY,
	S4_MENU_SETTLERS_WORKERS,
	S4_MENU_SETTLERS_SPECIALISTS,
	S4_MENU_SETTLERS_SEARCH,
	S4_MENU_GOODS_SUMMARY,
	S4_MENU_GOODS_DISTRIBUTION,
	S4_MENU_GOODS_PRIORITY,
	S4_MENU_STATISTICS_WARRIORS,
	S4_MENU_STATISTICS_LAND,
	S4_MENU_STATISTICS_GOODS,
	S4_MENU_UNITSELECTION_DONKEY,
	S4_MENU_UNITSELECTION_MILITARY,
	S4_MENU_UNITSELECTION_SPECIALISTS,
	S4_MENU_UNITSELECTION_VEHICLES,
	S4_MENU_UNITSELECTION_FERRY,
	S4_MENU_UNITSELECTION_TRADINGVEHICLE,
	S4_MENU_UNITSELECTION_SUB_SPELLS,
	S4_MENU_UNITSELECTION_SUB_GROUPINGS,
	S4_MENU_SELECTION_SUB_TRADE,
	S4_MENU_SELECTION_SUB_BUILDVEHICLE,
	S4_MENU_SELECTION_SUB_BARRACKS,

	S4_GUI_ENUM_MAXVALUE // never put anything below this
};

enum S4_ENTITY_CAUSE : BOOL {
	S4_ENTITY_DESTRUCTED = 1,
	S4_ENTITY_CONSTRUCTED,
};

enum S4_MOVEMENT_ENUM : DWORD {
	S4_MOVEMENT_FORWARD,
	S4_MOVEMENT_PATROL,
	S4_MOVEMENT_ACCUMULATE,
	S4_MOVEMENT_WATCH = 4,
	S4_MOVEMENT_STOP = 8,
};

typedef struct S4UiElement {
	WORD x, y, w, h;
	WORD sprite;
	WORD id;
} *LPS4UIELEMENT;
typedef CONST S4UiElement* LPCS4UIELEMENT;

#define S4_CUSTOMUIFLAGS_FROMRES_IMG (1<<0) // load image from resource
#define S4_CUSTOMUIFLAGS_FROMRES_IMGHOVER (1<<1) // load image from resource
#define S4_CUSTOMUIFLAGS_FROMRES_IMGSELECTED (1<<2) // load image from resource
#define S4_CUSTOMUIFLAGS_FROMRES_IMGSELECTEDHOVER (1<<3) // load image from resource
#define S4_CUSTOMUIFLAGS_TYPE_TOGGLE (1<<4) // is a toggle
#define S4_CUSTOMUIFLAGS_RESET_ON_HIDE (1<<5) // reset state on hide
#define S4_CUSTOMUIFLAGS_NO_PILLARBOX (1<<6) // do not draw relative to pillarbox
#define S4_CUSTOMUIFLAGS_TRANSPARENT (1<<7) // use alpha blending
#define S4_CUSTOMUIFLAGS_ALIGN_TOP (0)
#define S4_CUSTOMUIFLAGS_ALIGN_MIDDLE (1<<8)
#define S4_CUSTOMUIFLAGS_ALIGN_BOTTOM (1<<9)
#define S4_CUSTOMUIFLAGS_ALIGN_LEFT (0)
#define S4_CUSTOMUIFLAGS_ALIGN_CENTER (1<<10)
#define S4_CUSTOMUIFLAGS_ALIGN_RIGHT (1<<11)
#define S4_CUSTOMUIFLAGS_ANCHOR_TOP (0)
#define S4_CUSTOMUIFLAGS_ANCHOR_MIDDLE (1<<12)
#define S4_CUSTOMUIFLAGS_ANCHOR_BOTTOM (1<<13)
#define S4_CUSTOMUIFLAGS_ANCHOR_LEFT (0)
#define S4_CUSTOMUIFLAGS_ANCHOR_CENTER (1<<14)
#define S4_CUSTOMUIFLAGS_ANCHOR_RIGHT (1<<15)

enum S4_CUSTOM_UI_ENUM : DWORD {
	S4_CUSTOM_UI_UNSELECTED = 0,
	S4_CUSTOM_UI_SELECTED = 1,
	S4_CUSTOM_UI_HOVERING = 2,
	S4_CUSTOM_UI_HOVERING_SELECTED = 3,
};
typedef HRESULT(FAR S4HCALL* LPS4UICALLBACK)(S4CUSTOMUI lpUiElement, S4_CUSTOM_UI_ENUM newstate);
typedef BOOL(FAR S4HCALL* LPS4UIFILTERCALLBACK)(S4CUSTOMUI lpUiElement);
typedef struct S4CustomUiElement {
	SIZE_T size;
	HMODULE mod;
	LPCWSTR szImg, szImgHover, szImgSelected, szImgSelectedHover;
	DWORD flags;
	INT x, y;
	S4_GUI_ENUM screen;
	LPS4UICALLBACK actionHandler;
	LPS4UIFILTERCALLBACK filter;
} *LPS4CUSTOMUIELEMENT;
typedef CONST LPS4CUSTOMUIELEMENT LPCS4CUSTOMUIELEMENT;
typedef struct S4BltParams {
	VOID* caller;
	WORD* imagePalette;
	BYTE* imageData;
	INT imageWidth;
	INT imageHeight;
	INT destX;
	INT destY;
	INT destClippingOffsetY;
	WORD* subSurface;
	BOOL imageHighRes;
	INT destWidth;
	INT destHeight;
	INT surfaceWidth;
	INT surfaceHeight;
	INT stride;
	DWORD zoomFactor;
	WORD* surface;
	BOOL isFogOfWar;
	WORD settlerId;
	WORD spriteId;
	HDC destinationDc;
} *LPS4BLTPARAMS;

typedef struct S4GuiBltParams {
	DWORD id;
	LPVOID dstSurface;
	LPRECT dstRect;
	LPVOID srcSurface;
	LPRECT srcRect;
	DWORD ddbltFlags;
	LPVOID ddbltfx;
} *LPS4GUIBLTPARAMS;

/** Callback types **/
typedef HRESULT(FAR S4HCALL* LPS4FRAMECALLBACK)(LPDIRECTDRAWSURFACE7 lpSurface, INT32 iPillarboxWidth, LPVOID lpReserved);
typedef HRESULT(FAR S4HCALL* LPS4MAPINITCALLBACK)(LPVOID lpReserved0, LPVOID lpReserved1);
typedef HRESULT(FAR S4HCALL* LPS4MOUSECALLBACK)(DWORD dwMouseButton, INT iX, INT iY, DWORD dwMsgId, HWND hwnd, LPCS4UIELEMENT lpUiElement);
typedef HRESULT(FAR S4HCALL* LPS4SETTLERSENDCALLBACK)(DWORD dwPosition, S4_MOVEMENT_ENUM dwCommand, LPVOID lpReserved);
typedef HRESULT(FAR S4HCALL* LPS4TICKCALLBACK)(DWORD dwTick, BOOL bHasEvent, BOOL bIsDelayed);
typedef HRESULT(FAR S4HCALL* LPS4LUAOPENCALLBACK)(VOID);
typedef BOOL   (FAR S4HCALL* LPS4BLTCALLBACK)(LPS4BLTPARAMS params, BOOL discard);
typedef BOOL   (FAR S4HCALL* LPS4GUIBLTCALLBACK)(LPS4GUIBLTPARAMS params, BOOL discard);
typedef HRESULT(FAR S4HCALL* LPS4ENTITYCALLBACK)(WORD entity, S4_ENTITY_CAUSE cause); // called when an entity is spawned or destructed // todo: implement me


HRESULT __declspec(nothrow) S4HCALL S4CreateInterface(CONST GUID FAR* lpGUID, LPSETTLERS4API FAR* lplpS4H);

static LPSETTLERS4API inline S4HCALL S4ApiCreate() {
	LPSETTLERS4API out = NULL;
	S4CreateInterface(&IID_ISettlers4Api, &out);
	return out;
}

#undef  INTERFACE
#define INTERFACE ISettlers4Api
DECLARE_INTERFACE_(ISettlers4Api, IUnknown) {
	/** IUnknown methods **/
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR * ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

	/** ISettlers4Api methods **/
	STDMETHOD_(LPVOID, GetDebugData) (THIS_ LPVOID, LPVOID) PURE;
	STDMETHOD_(DWORD, GetLastError) (THIS) PURE;

	/** Hooks/Observers **/
	STDMETHOD(RemoveListener)(THIS_ S4HOOK) PURE;
	STDMETHOD_(S4HOOK, AddFrameListener)(THIS_ LPS4FRAMECALLBACK) PURE;
	STDMETHOD_(S4HOOK, AddUIFrameListener)(THIS_ LPS4FRAMECALLBACK, S4_GUI_ENUM) PURE;
	STDMETHOD_(S4HOOK, AddMapInitListener)(THIS_ LPS4MAPINITCALLBACK) PURE;
	STDMETHOD_(S4HOOK, AddMouseListener)(THIS_ LPS4MOUSECALLBACK) PURE;
	STDMETHOD_(S4HOOK, AddSettlerSendListener)(THIS_ LPS4SETTLERSENDCALLBACK) PURE;
	STDMETHOD_(S4HOOK, AddTickListener)(THIS_ LPS4TICKCALLBACK) PURE;
	STDMETHOD_(S4HOOK, AddLuaOpenListener)(THIS_ LPS4LUAOPENCALLBACK) PURE;
	STDMETHOD_(S4HOOK, AddBltListener)(THIS_ LPS4BLTCALLBACK) PURE;
	STDMETHOD_(S4HOOK, AddEntityListener)(THIS_ LPS4ENTITYCALLBACK) PURE;
	STDMETHOD_(S4HOOK, AddGuiBltListener)(THIS_ LPS4GUIBLTCALLBACK) PURE;

	/** Misc helper functions **/
	STDMETHOD(GetMD5OfModule)(THIS_ HMODULE module, LPSTR out, SIZE_T sz) PURE;
	STDMETHOD_(BOOL, IsEdition)(THIS_ S4_EDITION_ENUM edition) PURE;
	STDMETHOD_(HWND, GetHwnd)(THIS) PURE;

	/** Settlers 4 functions **/
	STDMETHOD(GetHoveringUiElement)(THIS_ LPS4UIELEMENT) PURE;
	STDMETHOD_(BOOL, IsCurrentlyOnScreen)(THIS_ S4_GUI_ENUM) PURE;
	STDMETHOD_(S4_ENTITY_ENUM, EntityGetClass)(THIS_ WORD entity) PURE;
	STDMETHOD_(BOOL, EntityGetPosition)(THIS_ WORD entity, LPINT x, LPINT y) PURE;
	STDMETHOD_(BOOL, EntitygGetDirection)(THIS_ WORD entity, LPDWORD dir) PURE;
	STDMETHOD_(BOOL, EntityGetHealth)(THIS_ WORD entity, LPDWORD health) PURE;
	STDMETHOD_(BOOL, EntityGetMaxHealth)(THIS_ WORD entity, LPDWORD maxHealth) PURE;
	STDMETHOD_(BOOL, EntityGetTribe)(THIS_ WORD entity, S4_TRIBE_ENUM* tribe) PURE;
	STDMETHOD_(BOOL, EntityTreeGetType)(THIS_ WORD entity, S4_TREE_ENUM* tree) PURE;
	STDMETHOD_(BOOL, EntityPileGetType)(THIS_ WORD entity, S4_GOOD_ENUM* good) PURE;
	STDMETHOD_(BOOL, EntityDecoGetType)(THIS_ WORD entity, LPDWORD deco) PURE;
	STDMETHOD_(BOOL, EntityPileGetAmount)(THIS_ WORD entity, LPDWORD amount) PURE;
	STDMETHOD_(BOOL, EntitySettlerGetType)(THIS_ WORD entity, S4_SETTLER_ENUM* settler) PURE;
	STDMETHOD_(BOOL, EntityVehicleGetType)(THIS_ WORD entity, S4_VEHICLE_ENUM* vehicle) PURE;
	STDMETHOD_(BOOL, EntityAnimalGetType)(THIS_ WORD entity, S4_ANIMAL_ENUM *animal) PURE;
	STDMETHOD_(BOOL, EntityBuildingGetType)(THIS_ WORD entity, S4_BUILDING_ENUM* building) PURE;
	STDMETHOD_(BOOL, EntityStoneGetLevel)(THIS_ WORD entity, LPDWORD level) PURE;
	STDMETHOD_(BOOL, EntityGetRole)(THIS_ WORD entity, LPVOID* role) PURE;
	STDMETHOD_(BOOL, EntitygGetRoleClass)(THIS_ WORD entity, S4_ROLE_ENUM * role) PURE;
	STDMETHOD_(BOOL, EntitygGetOwner)(THIS_ WORD entity, LPDWORD player) PURE;

	STDMETHOD_(BOOL, ClearSelection)(THIS) PURE;
	STDMETHOD_(BOOL, GetSelection)(THIS_ PWORD out, SIZE_T outlen, PSIZE_T selectionCount) PURE;
	STDMETHOD_(BOOL, RemoveSelection)(THIS_ PWORD settlers, SIZE_T settlerslen, PSIZE_T removedCount) PURE;
	STDMETHOD_(BOOL, StartBuildingPlacement)(THIS_ S4_BUILDING_ENUM building) PURE;

	/** Landscape functions **/
	STDMETHOD_(DWORD, LandscapeGetHeight)(THIS_ INT x, INT y) PURE; // defined in CS4Landscape.cpp
	STDMETHOD_(S4_GROUND_ENUM, LandscapeGetType)(THIS_ INT x, INT y) PURE; // defined in CS4Landscape.cpp
	STDMETHOD_(BOOL, LandscapeIsPond)(THIS_ INT x, INT y) PURE; // defined in CS4Landscape.cpp
	STDMETHOD_(BOOL, LandscapeIsDarkLand)(THIS_ INT x, INT y) PURE; // defined in CS4Landscape.cpp
	STDMETHOD_(BOOL, LandscapeIsDarkLandBorder)(THIS_ INT x, INT y) PURE; // defined in CS4Landscape.cpp
	STDMETHOD_(DWORD, LandscapeGetFogOfWar)(THIS_ INT x, INT y) PURE; // defined in CS4Landscape.cpp
	STDMETHOD_(BOOL, LandscapeIsFoundingStone)(THIS_ INT x, INT y) PURE; // defined in CS4Landscape.cpp
	STDMETHOD_(S4_RESOURCE_ENUM, LandscapeGetResource)(THIS_ INT x, INT y) PURE; // defined in CS4Landscape.cpp
	STDMETHOD_(BOOL, LandscapeSetResource)(THIS_ INT x, INT y, S4_RESOURCE_ENUM res) PURE; // defined in CS4Landscape.cpp
	STDMETHOD_(DWORD, LandscapeGetObject)(THIS_ INT x, INT y) PURE; // defined in CS4Landscape.cpp
	STDMETHOD_(DWORD, LandscapeGetOwner)(THIS_ INT x, INT y) PURE; // defined in CS4Landscape.cpp

	/** Settlers 4 NetEvents functions **/
	STDMETHOD_(BOOL, SendWarriors)(THIS_ INT x, INT y, S4_MOVEMENT_ENUM mode, PWORD warriors, SIZE_T countOfWarriors, DWORD player = 0) PURE;
	STDMETHOD_(BOOL, BuildBuilding)(THIS_ S4_BUILDING_ENUM buildingType, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, CrushBuilding)(THIS_ DWORD building, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, ToggleBuildingPriority)(THIS_ DWORD building, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, ToggleBuildingHalt)(THIS_ DWORD building, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingWorkarea)(THIS_ DWORD building, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingProduction)(THIS_ DWORD building, S4_GOOD_ENUM good, INT amount, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingProductionPercentMode)(THIS_ DWORD building, BOOL enable, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingProductionPercentage)(THIS_ DWORD building, BYTE swords, BYTE bows, BYTE armors, BYTE racespecialweapons, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, CastSpell)(THIS_ DWORD priest, DWORD spell, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Casting.cpp
	STDMETHOD_(BOOL, GarrisonWarriors)(THIS_ DWORD building, DWORD player = 0) PURE; // defined in CS4GarrisonWarriors.cpp
	STDMETHOD_(BOOL, UnGarrisonWarriors)(THIS_ DWORD building, INT column, BOOL bowman, DWORD player = 0) PURE; // defined in CS4GarrisonWarriors.cpp
	STDMETHOD_(BOOL, ChangeGoodDistribution)(THIS_ S4_GOOD_ENUM good, S4_BUILDING_ENUM building, INT percent, DWORD ecosector, DWORD player = 0) PURE; // defined in CS4GoodDistribution.cpp
	STDMETHOD_(BOOL, ChangeGoodPriority)(THIS_ S4_GOOD_ENUM good, INT offset, DWORD ecosector, DWORD player = 0) PURE; // defined in CS4GoodDistribution.cpp
	STDMETHOD_(BOOL, RecruitWarriors)(THIS_ DWORD building, S4_SETTLER_ENUM unit, INT amount, DWORD player = 0) PURE; // defined in CS4Recruit.cpp
	STDMETHOD_(BOOL, RecruitVehicle)(THIS_ DWORD building, S4_VEHICLE_ENUM unit, INT amount, DWORD player = 0) PURE; // defined in CS4Recruit.cpp
	STDMETHOD_(BOOL, SetTradingRoute)(THIS_ DWORD sourceBuilding, DWORD destinationBuilding, DWORD player = 0) PURE; // defined in CS4Trading.cpp
	STDMETHOD_(BOOL, TradeGood)(THIS_ DWORD buidling, S4_GOOD_ENUM good, INT amount, DWORD player = 0) PURE; // defined in CS4Trading.cpp
	STDMETHOD_(BOOL, StoreGood)(THIS_ DWORD buidling, S4_GOOD_ENUM good, BOOL enable, DWORD player = 0) PURE; // defined in CS4Trading.cpp

	/** UI Rendering **/
	STDMETHOD_(S4CUSTOMUI, ShowMessageBox)(THIS_ LPCWSTR title, LPCWSTR message, INT x, INT y, INT w, INT h, DWORD flags = 0) PURE;
	STDMETHOD_(S4CUSTOMUI, CreateCustomUiElement)(THIS_ LPCS4CUSTOMUIELEMENT) PURE;
	STDMETHOD_(BOOL, DestroyCustomUiElement)(THIS_ S4CUSTOMUI) PURE;
	STDMETHOD_(BOOL, HideCustomUiElement)(THIS_ S4CUSTOMUI) PURE;
	STDMETHOD_(BOOL, ShowCustomUiElement)(THIS_ S4CUSTOMUI) PURE;

	/** S4 Scripting **/
	STDMETHOD_(DWORD, GetLocalPlayer)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsAdd)(THIS_ S4_BUILDING_ENUM building, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsAmount)(THIS_ S4_BUILDING_ENUM building, DWORD status, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, BuildingsCrush)(THIS_ DWORD building) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, BuildingsDelete)(THIS_ DWORD building, DWORD mode) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, BuildingsExistsBuildingInArea)(THIS_ S4_BUILDING_ENUM building, INT x, INT y, INT r, DWORD status, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsGetFirstBuilding)(THIS_ S4_BUILDING_ENUM building, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsGetInhabitantAmount)(THIS_ DWORD building, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsGetTarget)(THIS_ DWORD building) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, BuildingsIsSelected)(THIS_ S4_BUILDING_ENUM building) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, DarkTribeAddManakopter)(THIS_ INT x, INT y, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, DarkTribeFlyTo)(THIS_ INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, AIActivate)(THIS_ DWORD player, BOOL activate) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MakeDark)(THIS_ INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MakeGreen)(THIS_ INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, EffectsAdd)(THIS_ DWORD effect, DWORD sound, INT x, INT y, DWORD delay) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, ArePlayerAreasConnected)(THIS_ INT x1, INT y1, DWORD player2, INT x2, INT y2, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, GameDefaultGameEndCheck)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, DisableLastNPlayersInStatistic)(THIS_ DWORD n) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, EnableLandExploredCheck)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, FindAnyUnit)(THIS_ INT x, INT y, INT r, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GetAmountOfTreesInArea)(THIS_ INT x, INT y, INT r) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GetDifficulty)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GetNumberOfSquaresWithDarkLand)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GetOffenceFightingStrength)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, HasPlayerLost)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, IsAlmostAllLandExplored)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, IsAreaDarkLand)(THIS_ INT x, INT y, INT r) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, IsAreaGreen)(THIS_ INT x, INT y, INT r) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, IsAreaOwned)(THIS_ INT x, INT y, INT r, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GetNumberOfPlayers)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(S4_TRIBE_ENUM, GetPlayerTribe)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, ResetFogging)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetAlliesDontRevealFog)(THIS_ BOOL enable) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetFightingStrength)(THIS_ DWORD strength, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, ShowClock)(THIS_ DWORD seconds) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, Time)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GoodsAddPileEx)(THIS_ S4_GOOD_ENUM good, DWORD amount, INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GoodsAmount)(THIS_ S4_GOOD_ENUM good, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GoodsDelete)(THIS_ S4_GOOD_ENUM good, INT x, INT y, INT r) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GoodsGetAmountInArea)(THIS_ S4_GOOD_ENUM good, INT x, INT y, INT r, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, MagicCastSpell)(THIS_ S4_TRIBE_ENUM tribe, S4_SPELL_ENUM spell, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MagicIncreaseMana)(THIS_ INT amount, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, MapAddDecoObject)(THIS_ DWORD object, INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MapDeleteDecoObject)(THIS_ INT x, INT y, INT r) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, MapSize)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MapPointIsOnScreen)(THIS_ INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MapSetScreenPos)(THIS_ INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersAdd)(THIS_ S4_SETTLER_ENUM settler, INT amount, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersAddToFerry)(THIS_ DWORD ferry, S4_SETTLER_ENUM settler, INT amount) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, SettlersAmount)(THIS_ S4_SETTLER_ENUM settler, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, SettlersAmountInArea)(THIS_ S4_SETTLER_ENUM settler, INT x, INT y, INT r, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersIsSelected)(THIS_ S4_SETTLER_ENUM settler, INT amount) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersKillSelectableSettlers)(THIS_ S4_SETTLER_ENUM settler, INT x, INT y, INT r, BOOL animation, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, SettlersProductionAmount)(THIS_ S4_SETTLER_ENUM settler) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersSetHealthInArea)(THIS_ S4_SETTLER_ENUM settler, INT x, INT y, INT r, DWORD health, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticBuildingsCaptured)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticGoodsProduced)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticLandOwnedByPlayer)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticManaCollected)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticMushroomFarmsDestroyed)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticServantsFreed)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticSpellsCast)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticUnitsDestroyed)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, ClearMarker)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, DeleteWorldCursor)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, PressButton)(THIS_ DWORD dialog, DWORD control) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, RevealWorldMap)(THIS_ BOOL enable) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SelectNextBuilding)(THIS_ S4_BUILDING_ENUM building) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetMarker)(THIS_ INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetWorldCursor)(THIS_ INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetZoom)(THIS_ INT zoom) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesAdd)(THIS_ S4_VEHICLE_ENUM vehicle, DWORD direction, DWORD ammo, DWORD commands, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, VehiclesAddWheelerToFerry)(THIS_ DWORD ferry, S4_VEHICLE_ENUM vehicle) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesAmount)(THIS_ S4_VEHICLE_ENUM vehicle, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesAmountInArea)(THIS_ S4_VEHICLE_ENUM vehicle, INT x, INT y, INT r, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesGetFerryCargoInArea)(THIS_ INT x, INT y, INT r, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesGetHealth)(THIS_ INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, VehiclesIsSelected)(THIS_ S4_VEHICLE_ENUM vehicle, INT amount) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, VehiclesKill)(THIS_ S4_VEHICLE_ENUM vehicle, INT x, INT y, INT r, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetGround)(THIS_ INT x, INT y, INT r, DWORD ground) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, ShowTextMessage)(THIS_ LPCSTR message, DWORD icon, DWORD reserved) PURE; // defined in CS4Scripting.cpp

	/** Never extend this interface, create a new one if you need more methods 
		Otherwise you will break the ABI **/
};




}


#ifndef S4MODAPI // header aggregation
///////////////////////////////////////////////////////////////////////////////
// safemem.h
///////////////////////////////////////////////////////////////////////////////

extern "C" {

	/**
	 * Read memory from source (safe read)
	 **/
	void* __stdcall memget_s(void* dst, const void* src, size_t len);

	/**
	 * Write memory at destination (safe write)
	 **/
	void* __stdcall memset_s(void* dst, const void* src, size_t len);

	/**
	 * Read a DWORD from memory or return 0 on failure. (Safe read)
	 **/
	DWORD __stdcall READ_AT(const void* src, int offset = 0);

	/**
	 * Write a DWORD to memory or return 0 on failure. (Safe write)
	 **/
	BOOL __stdcall WRITE_AT(void* dst, DWORD val, int offset = 0);

	/**
	 * Find a pattern in process memory. The address of the first match will be returned.
	 *
	 * @param startAddr The first address to start searching
	 * @param pattern The pattern. Eg. "12 34 ? 1F C3".
	 * @param endAddr Do not search at addresses greater or equal to the endAddr. (endAddr is excluded)
	 */
	extern "C" UINT32 __stdcall FindPattern(UINT32 startAddr, const char* pattern, UINT32 endAddr = -1);

}


///////////////////////////////////////////////////////////////////////////////
// hlib.h
///////////////////////////////////////////////////////////////////////////////

//#include "windows.h"
//#include <vector>

namespace hlib {

	///////////////////////////////////////////////////////////////////////////////
	// Quick and dirty byte patching class that keeps track of the patched address.
	// You can implement a custom patch by inheriting from AbstractPatch.
	// Or include the template to create easy static patches
	///////////////////////////////////////////////////////////////////////////////
	class AbstractPatch {
	public:
		AbstractPatch();
		AbstractPatch(UINT64 addr, size_t len);
		AbstractPatch(UINT64 addr, size_t len, const void* orig);
		AbstractPatch(const AbstractPatch&) = delete;
		AbstractPatch& operator=(const AbstractPatch&) = delete;
		AbstractPatch(AbstractPatch&&);
		AbstractPatch& operator=(AbstractPatch&&);
		~AbstractPatch();

		bool patch();
		bool unpatch();

		// Call this to read the memory and check if the patch is applied. Returns 
		// false if the state is broken (neither applied nor the expected state)
		bool update();

		bool isPatched() const;

		UINT64 getAddress() const;
		virtual bool setAddress(UINT64 addr); // change address if patch is not applied yet

	protected:
		virtual bool applyPatch(HANDLE hProcess) = 0;
		virtual bool cmpPatch(const void* mem) = 0;

		UINT64 m_addr;
		bool m_isStrict;
		bool m_isPatched;
		void* m_orig;
		size_t m_len;
	};

	class Patch : public AbstractPatch {
	public:
		struct BYTE5 { const BYTE buf[5]; };
		Patch();
		Patch(UINT64 address, const void* patch, size_t len);
		Patch(UINT64 address, const void* patch, const void* expectedOrig, size_t len);
		Patch(UINT64 address, DWORD patch); // patch 4 bytes
		Patch(UINT64 address, DWORD patch, DWORD expectedOrig);
		Patch(UINT64 address, BYTE patch); // patch 1 bytes
		Patch(UINT64 address, BYTE patch, BYTE expected); // patch 1 bytes
		Patch(UINT64 address, BYTE bPatch, DWORD dwPatch, size_t nops = 0); // patch 5 bytes and some nops (0x90) after these 5 bytes
		Patch(UINT64 address, BYTE bPatch, DWORD dwPatch, const BYTE5* expected, size_t nops = 0);

		~Patch();

		Patch(Patch&&);
		Patch& operator=(Patch&&);

	protected:
		virtual bool applyPatch(HANDLE hProcess);
		virtual bool cmpPatch(const void* mem);
		void* m_patch;
	};
	class JmpPatch : public Patch {
	public:
		JmpPatch();
		JmpPatch(UINT64 address, DWORD jumpTargetAddr, size_t nops = 0);
		JmpPatch(UINT64 address, DWORD jumpTargetAddr, const BYTE5* expectedOrig, size_t nops = 0);
		virtual bool setAddress(UINT64 addr); // change address if patch is not applied yet
		bool setDestination(UINT64 dest); // change destination if patch is not applied yet
	protected:
		JmpPatch(BYTE opcode, UINT64 address, DWORD jumpTargetAddr, size_t nops);
		JmpPatch(BYTE opcode, UINT64 address, DWORD jumpTargetAddr, const BYTE5* expectedOrig, size_t nops);
	};
	class CallPatch : public JmpPatch {
	public:
		CallPatch();
		CallPatch(UINT64 address, DWORD jumpTargetAddr, size_t nops = 0);
		CallPatch(UINT64 address, DWORD jumpTargetAddr, const BYTE5* expectedOrig, size_t nops = 0);
	};
	class NopPatch : public AbstractPatch {
	public:
		NopPatch();
		NopPatch(UINT64 address, size_t len = 1);
		NopPatch(UINT64 address, const void* expected, size_t len);
	protected:
		virtual bool applyPatch(HANDLE hProcess);
		virtual bool cmpPatch(const void* mem);
	};

}

///////////////////////////////////////////////////////////////////////////////
// lua.h
///////////////////////////////////////////////////////////////////////////////

extern "C" {
#ifndef lua_h
#define lua_h

#define LUA_VERSION	"Lua 3.2.1"
#define LUA_COPYRIGHT	"Copyright (C) 1994-1999 TeCGraf, PUC-Rio"
#define LUA_AUTHORS 	"W. Celes, R. Ierusalimschy & L. H. de Figueiredo"


#define LUA_NOOBJECT  0

#define LUA_ANYTAG    (-1)

typedef struct lua_State lua_State;
//extern lua_State* lua_state;

typedef void (*lua_CFunction) (void);
typedef unsigned int lua_Object;

void	       lua_open(void);
void           lua_close(void);
lua_State* lua_setstate(lua_State* st);

lua_Object     lua_settagmethod(int tag, char* event); /* In: new method */
lua_Object     lua_gettagmethod(int tag, char* event);

int            lua_newtag(void);
int            lua_copytagmethods(int tagto, int tagfrom);
void           lua_settag(int tag); /* In: object */

void           lua_error(char* s);
int            lua_dofile(char* filename); /* Out: returns */
int            lua_dostring(char* string); /* Out: returns */
int            lua_dobuffer(char* buff, int size, char* name);
/* Out: returns */
int            lua_callfunction(lua_Object f);
/* In: parameters; Out: returns */

void	       lua_beginblock(void);
void	       lua_endblock(void);

lua_Object     lua_lua2C(int number);
#define	       lua_getparam(_)		lua_lua2C(_)
#define	       lua_getresult(_)		lua_lua2C(_)

int            lua_isnil(lua_Object object);
int            lua_istable(lua_Object object);
int            lua_isuserdata(lua_Object object);
int            lua_iscfunction(lua_Object object);
int            lua_isnumber(lua_Object object);
int            lua_isstring(lua_Object object);
int            lua_isfunction(lua_Object object);

double         lua_getnumber(lua_Object object);
char* lua_getstring(lua_Object object);
long           lua_strlen(lua_Object object);
lua_CFunction  lua_getcfunction(lua_Object object);
void* lua_getuserdata(lua_Object object);


void 	       lua_pushnil(void);
void           lua_pushnumber(double n);
void           lua_pushlstring(char* s, long len);
void           lua_pushstring(char* s);
void           lua_pushcclosure(lua_CFunction fn, int n);
void           lua_pushusertag(void* u, int tag);
void           lua_pushobject(lua_Object object);

lua_Object     lua_pop(void);

lua_Object     lua_getglobal(char* name);
lua_Object     lua_rawgetglobal(char* name);
void           lua_setglobal(char* name); /* In: value */
void           lua_rawsetglobal(char* name); /* In: value */

void           lua_settable(void); /* In: table, index, value */
void           lua_rawsettable(void); /* In: table, index, value */
lua_Object     lua_gettable(void); /* In: table, index */
lua_Object     lua_rawgettable(void); /* In: table, index */

int            lua_tag(lua_Object object);

char* lua_nextvar(char* varname);  /* Out: value */
int            lua_next(lua_Object o, int i);
/* Out: ref, value */

int            lua_ref(int lock); /* In: value */
lua_Object     lua_getref(int ref);
void	       lua_unref(int ref);

lua_Object     lua_createtable(void);

long	       lua_collectgarbage(long limit);


	/* =============================================================== */
	/* some useful macros/functions */

#define lua_call(name)		lua_callfunction(lua_getglobal(name))

#define lua_pushref(ref)	lua_pushobject(lua_getref(ref))

#define lua_refobject(o,l)	(lua_pushobject(o), lua_ref(l))

#define lua_register(n,f)	(lua_pushcfunction(f), lua_setglobal(n))

#define lua_pushuserdata(u)     lua_pushusertag(u, 0)

#define lua_pushcfunction(f)	lua_pushcclosure(f, 0)

#define lua_clonetag(t)		lua_copytagmethods(lua_newtag(), (t))

lua_Object     lua_seterrormethod(void);  /* In: new method */

/* ==========================================================================
** for compatibility with old versions. Avoid using these macros/functions
** If your program does need any of these, define LUA_COMPAT2_5
*/


#ifdef LUA_COMPAT2_5


lua_Object     lua_setfallback(char* event, lua_CFunction fallback);

#define lua_storeglobal		lua_setglobal
#define lua_type		lua_tag

#define lua_lockobject(o)  lua_refobject(o,1)
#define	lua_lock() lua_ref(1)
#define lua_getlocked lua_getref
#define	lua_pushlocked lua_pushref
#define	lua_unlock lua_unref

#define lua_pushliteral(o)  lua_pushstring(o)

#define lua_getindexed(o,n) (lua_pushobject(o), lua_pushnumber(n), lua_gettable())
#define lua_getfield(o,f)   (lua_pushobject(o), lua_pushstring(f), lua_gettable())

#define lua_copystring(o) (strdup(lua_getstring(o)))

#define lua_getsubscript  lua_gettable
#define lua_storesubscript  lua_settable

#endif

#endif

} // extern "C"



/******************************************************************************
* Copyright (c) 1994-1999 TeCGraf, PUC-Rio.  All rights reserved.
*
* Permission is hereby granted, without written agreement and without license
* or royalty fees, to use, copy, modify, and distribute this software and its
* documentation for any purpose, including commercial applications, subject to
* the following conditions:
*
*  - The above copyright notice and this permission notice shall appear in all
*    copies or substantial portions of this software.
*
*  - The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software in a
*    product, an acknowledgment in the product documentation would be greatly
*    appreciated (but it is not required).
*
*  - Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
*
* The authors specifically disclaim any warranties, including, but not limited
* to, the implied warranties of merchantability and fitness for a particular
* purpose.  The software provided hereunder is on an "as is" basis, and the
* authors have no obligation to provide maintenance, support, updates,
* enhancements, or modifications.  In no event shall TeCGraf, PUC-Rio, or the
* authors be held liable to any party for direct, indirect, special,
* incidental, or consequential damages arising out of the use of this software
* and its documentation.
*
* The Lua language and this implementation have been entirely designed and
* written by Waldemar Celes Filho, Roberto Ierusalimschy and
* Luiz Henrique de Figueiredo at TeCGraf, PUC-Rio.
*
* This implementation contains no third-party code.
******************************************************************************/


///////////////////////////////////////////////////////////////////////////////
// lauxlib.h
///////////////////////////////////////////////////////////////////////////////

/*
** $Id: lauxlib.h,v 1.12 1999/03/10 14:19:41 roberto Exp $
** Auxiliary functions for building Lua libraries
** See Copyright Notice in lua.h
*/

extern "C" {
#ifndef auxlib_h
#define auxlib_h




struct luaL_reg {
	char* name;
	lua_CFunction func;
};


#define luaL_arg_check(cond,numarg,extramsg) if (!(cond)) \
                                               luaL_argerror(numarg,extramsg)

void luaL_openlib(struct luaL_reg* l, int n);
void luaL_argerror(int numarg, char* extramsg);
#define luaL_check_string(n)  (luaL_check_lstr((n), NULL))
char* luaL_check_lstr(int numArg, long* len);
#define luaL_opt_string(n, d) (luaL_opt_lstr((n), (d), NULL))
char* luaL_opt_lstr(int numArg, char* def, long* len);
double luaL_check_number(int numArg);
#define luaL_check_int(n)	((int)luaL_check_number(n))
#define luaL_check_long(n)	((long)luaL_check_number(n))
double luaL_opt_number(int numArg, double def);
#define luaL_opt_int(n,d)	((int)luaL_opt_number(n,d))
#define luaL_opt_long(n,d)	((long)luaL_opt_number(n,d))
lua_Object luaL_functionarg(int arg);
lua_Object luaL_tablearg(int arg);
lua_Object luaL_nonnullarg(int numArg);
void luaL_verror(char* fmt, ...);
char* luaL_openspace(int size);
void luaL_resetbuffer(void);
void luaL_addchar(int c);
int luaL_getsize(void);
void luaL_addsize(int n);
int luaL_newbuffer(int size);
void luaL_oldbuffer(int old);
char* luaL_buffer(void);
int luaL_findstring(char* name, char* list[]);
void luaL_chunkid(char* out, char* source, int len);
void luaL_filesource(char* out, char* filename, int len);

#endif
} // extern "C"

///////////////////////////////////////////////////////////////////////////////
// luadebug.h
///////////////////////////////////////////////////////////////////////////////


/*
** $Id: luadebug.h,v 1.6 1999/03/04 21:17:26 roberto Exp $
** Debugging API
** See Copyright Notice in lua.h
*/

extern "C" {
#ifndef luadebug_h
#define luadebug_h

typedef lua_Object lua_Function;

typedef void (*lua_LHFunction) (int line);
typedef void (*lua_CHFunction) (lua_Function func, char* file, int line);

lua_Function lua_stackedfunction(int level);
void lua_funcinfo(lua_Object func, char** source, int* linedefined);
int lua_currentline(lua_Function func);
char* lua_getobjname(lua_Object o, char** name);

lua_Object lua_getlocal(lua_Function func, int local_number, char** name);
int lua_setlocal(lua_Function func, int local_number);

int lua_nups(lua_Function func);

lua_LHFunction lua_setlinehook(lua_LHFunction func);
lua_CHFunction lua_setcallhook(lua_CHFunction func);
int lua_setdebug(int debug);


#endif
} // extern "C"

#endif