///////////////////////////////////////////////////////////////////////////////
// MIT License
//
// Copyright (c) 2020 nyfrk <nyfrk@gmx.net>
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
typedef LPCVOID S4CUSTOMUI;

enum S4_EDITION_ENUM : DWORD {
	S4_EDITION_GOLD = 1,
	S4_EDITION_HISTORY = 2,
};

enum S4_OBJECT_TYPE : WORD {
	S4_OBJECT_UNKNOWN,
	S4_OBJECT_EMPTY,

	// TRIBES
	S4_OBJECT_TRIBE_NONE,
	S4_OBJECT_TRIBE,
	S4_OBJECT_TRIBE_ROMAN, // tribe 0
	S4_OBJECT_TRIBE_VIKING,
	S4_OBJECT_TRIBE_MAYA,
	S4_OBJECT_TRIBE_DARK,
	S4_OBJECT_TRIBE_TROJAN,

	// GOODS
	S4_OBJECT_GOOD = S4_OBJECT_TRIBE_TROJAN + 256,
	S4_OBJECT_GOOD_AGAVE, // good id 1
	S4_OBJECT_GOOD_AMMO,
	S4_OBJECT_GOOD_ARMOR,
	S4_OBJECT_GOOD_AXE,
	S4_OBJECT_GOOD_BATTLEAXE,
	S4_OBJECT_GOOD_BLOWGUN,
	S4_OBJECT_GOOD_BOARD,
	S4_OBJECT_GOOD_BOW,
	S4_OBJECT_GOOD_BREAD,
	S4_OBJECT_GOOD_COAL, // 10
	S4_OBJECT_GOOD_FISH,
	S4_OBJECT_GOOD_FLOUR,
	S4_OBJECT_GOOD_GOAT,
	S4_OBJECT_GOOD_GOLDBAR,
	S4_OBJECT_GOOD_GOLDORE,
	S4_OBJECT_GOOD_GRAIN,
	S4_OBJECT_GOOD_GUNPOWDER,
	S4_OBJECT_GOOD_HAMMER,
	S4_OBJECT_GOOD_HONEY,
	S4_OBJECT_GOOD_IRONBAR,// 20
	S4_OBJECT_GOOD_IRONORE,
	S4_OBJECT_GOOD_LOG,
	S4_OBJECT_GOOD_MEAD,
	S4_OBJECT_GOOD_MEAT,
	S4_OBJECT_GOOD_PICKAXE,
	S4_OBJECT_GOOD_PIG,
	S4_OBJECT_GOOD_ROD,
	S4_OBJECT_GOOD_SAW,
	S4_OBJECT_GOOD_SCYTHE,
	S4_OBJECT_GOOD_SHEEP, // 30
	S4_OBJECT_GOOD_SHOVEL,
	S4_OBJECT_GOOD_STONE,
	S4_OBJECT_GOOD_SULFUR,
	S4_OBJECT_GOOD_SWORD,
	S4_OBJECT_GOOD_TEQUILA,
	S4_OBJECT_GOOD_WATER,
	S4_OBJECT_GOOD_WINE,
	S4_OBJECT_GOOD_BACKPACKCATAPULT,
	S4_OBJECT_GOOD_GOOSE,
	S4_OBJECT_GOOD_EXPLOSIVEARROW, // 40
	S4_OBJECT_GOOD_SUNFLOWEROIL,
	S4_OBJECT_GOOD_SUNFLOWER, // good id 42

	// BUILDINGS
	S4_OBJECT_BUILDING = S4_OBJECT_GOOD_SUNFLOWER + 256,
	//S4_OBJECT_BUILDING_READY,
	//S4_OBJECT_BUILDING_UNDERCONSTRUCTION,
	S4_OBJECT_BUILDING_WOODCUTTERHUT, // building id 1
	S4_OBJECT_BUILDING_FORESTERHUT,
	S4_OBJECT_BUILDING_SAWMILL,
	S4_OBJECT_BUILDING_STONECUTTERHUT,
	S4_OBJECT_BUILDING_WATERWORKHUT,
	S4_OBJECT_BUILDING_FISHERHUT,
	S4_OBJECT_BUILDING_HUNTERHUT,
	S4_OBJECT_BUILDING_SLAUGHTERHOUSE,
	S4_OBJECT_BUILDING_MILL,
	S4_OBJECT_BUILDING_BAKERY, // 10
	S4_OBJECT_BUILDING_GRAINFARM,
	S4_OBJECT_BUILDING_ANIMALRANCH,
	S4_OBJECT_BUILDING_DONKEYRANCH,
	S4_OBJECT_BUILDING_STONEMINE,
	S4_OBJECT_BUILDING_IRONMINE,
	S4_OBJECT_BUILDING_GOLDMINE,
	S4_OBJECT_BUILDING_COALMINE,
	S4_OBJECT_BUILDING_SULFURMINE,
	S4_OBJECT_BUILDING_SMELTGOLD,
	S4_OBJECT_BUILDING_SMELTIRON, // 20
	S4_OBJECT_BUILDING_TOOLSMITH,
	S4_OBJECT_BUILDING_WEAPONSMITH,
	S4_OBJECT_BUILDING_VEHICLEHALL,
	S4_OBJECT_BUILDING_BARRACKS,
	S4_OBJECT_BUILDING_CHARCOALMAKER,
	S4_OBJECT_BUILDING_TRAININGCENTER,
	S4_OBJECT_BUILDING_HEALERHUT,
	S4_OBJECT_BUILDING_AMMOMAKERHUT,
	S4_OBJECT_BUILDING_GUNPOWDERMAKERHUT,
	S4_OBJECT_BUILDING_LANDSCAPEMAKERHUT, // 30
	S4_OBJECT_BUILDING_SHIPYARD,
	S4_OBJECT_BUILDING_PORT,
	S4_OBJECT_BUILDING_MARKETPLACE,
	S4_OBJECT_BUILDING_STORAGEAREA,
	S4_OBJECT_BUILDING_VINYARD,
	S4_OBJECT_BUILDING_AGAVEFARMERHUT,
	S4_OBJECT_BUILDING_TEQUILAMAKERHUT,
	S4_OBJECT_BUILDING_BEEKEEPERHUT,
	S4_OBJECT_BUILDING_MEADMAKERHUT,
	S4_OBJECT_BUILDING_RESIDENCESMALL,// 40
	S4_OBJECT_BUILDING_RESIDENCEMEDIUM,
	S4_OBJECT_BUILDING_RESIDENCEBIG,
	S4_OBJECT_BUILDING_SMALLTEMPLE,
	S4_OBJECT_BUILDING_BIGTEMPLE,
	S4_OBJECT_BUILDING_LOOKOUTTOWER,
	S4_OBJECT_BUILDING_GUARDTOWERSMALL,
	S4_OBJECT_BUILDING_GUARDTOWERBIG,
	S4_OBJECT_BUILDING_CASTLE,
	S4_OBJECT_BUILDING_MUSHROOMFARM,
	S4_OBJECT_BUILDING_DARKTEMPLE, // 50
	S4_OBJECT_BUILDING_FORTRESS,
	S4_OBJECT_BUILDING_PORTA,
	S4_OBJECT_BUILDING_PORTB,
	S4_OBJECT_BUILDING_PORTC,
	S4_OBJECT_BUILDING_PORTD,
	S4_OBJECT_BUILDING_PORTE,
	S4_OBJECT_BUILDING_PORTF,
	S4_OBJECT_BUILDING_SHIPYARDA,
	S4_OBJECT_BUILDING_SHIPYARDB,
	S4_OBJECT_BUILDING_SHIPYARDC,
	S4_OBJECT_BUILDING_SHIPYARDD,
	S4_OBJECT_BUILDING_SHIPYARDE,
	S4_OBJECT_BUILDING_SHIPYARDF,
	S4_OBJECT_BUILDING_EYECATCHER01,
	S4_OBJECT_BUILDING_EYECATCHER02,
	S4_OBJECT_BUILDING_EYECATCHER03,
	S4_OBJECT_BUILDING_EYECATCHER04,
	S4_OBJECT_BUILDING_EYECATCHER05,
	S4_OBJECT_BUILDING_EYECATCHER06,
	S4_OBJECT_BUILDING_EYECATCHER07,
	S4_OBJECT_BUILDING_EYECATCHER08,
	S4_OBJECT_BUILDING_EYECATCHER09,
	S4_OBJECT_BUILDING_EYECATCHER10,
	S4_OBJECT_BUILDING_EYECATCHER11,
	S4_OBJECT_BUILDING_EYECATCHER12,
	S4_OBJECT_BUILDING_SHIPYARDG,
	S4_OBJECT_BUILDING_SHIPYARDH,
	S4_OBJECT_BUILDING_PORTG,
	S4_OBJECT_BUILDING_PORTH,
	S4_OBJECT_BUILDING_MANACOPTERHALL,
	S4_OBJECT_BUILDING_SUNFLOWEROILMAKERHUT,
	S4_OBJECT_BUILDING_SUNFLOWERFARMERHUT,

	// SETTLERS
	S4_OBJECT_SETTLER = S4_OBJECT_BUILDING_SUNFLOWERFARMERHUT + 256,
	S4_OBJECT_SETTLER_CARRIER, // settler id 1
	S4_OBJECT_SETTLER_DIGGER,
	S4_OBJECT_SETTLER_BUILDER,
	S4_OBJECT_SETTLER_WOODCUTTER,
	S4_OBJECT_SETTLER_STONECUTTER,
	S4_OBJECT_SETTLER_FORESTER,
	S4_OBJECT_SETTLER_FARMERGRAIN,
	S4_OBJECT_SETTLER_FARMERANIMALS,
	S4_OBJECT_SETTLER_FISHER,
	S4_OBJECT_SETTLER_WATERWORKER,
	S4_OBJECT_SETTLER_HUNTER,
	S4_OBJECT_SETTLER_SAWMILLWORKER,
	S4_OBJECT_SETTLER_SMELTER,
	S4_OBJECT_SETTLER_MINEWORKER,
	S4_OBJECT_SETTLER_SMITH,
	S4_OBJECT_SETTLER_MILLER,
	S4_OBJECT_SETTLER_BAKER,
	S4_OBJECT_SETTLER_BUTCHER,
	S4_OBJECT_SETTLER_SHIPYARDWORKER,
	S4_OBJECT_SETTLER_HEALER,
	S4_OBJECT_SETTLER_CHARCOALMAKER,
	S4_OBJECT_SETTLER_AMMOMAKER,
	S4_OBJECT_SETTLER_VEHICLEMAKER,
	S4_OBJECT_SETTLER_VINTNER,
	S4_OBJECT_SETTLER_BEEKEEPER,
	S4_OBJECT_SETTLER_MEADMAKER,
	S4_OBJECT_SETTLER_AGAVEFARMER,
	S4_OBJECT_SETTLER_TEQUILAMAKER,
	S4_OBJECT_SETTLER_SWORDSMAN_01,
	S4_OBJECT_SETTLER_DARK_WARRIOR = S4_OBJECT_SETTLER_SWORDSMAN_01,
	S4_OBJECT_SETTLER_SWORDSMAN_02,
	S4_OBJECT_SETTLER_SWORDSMAN_03,
	S4_OBJECT_SETTLER_BOWMAN_01,
	S4_OBJECT_SETTLER_DARK_THROWER = S4_OBJECT_SETTLER_BOWMAN_01,
	S4_OBJECT_SETTLER_BOWMAN_02,
	S4_OBJECT_SETTLER_BOWMAN_03,
	S4_OBJECT_SETTLER_MEDIC_01,
	S4_OBJECT_SETTLER_MEDIC_02,
	S4_OBJECT_SETTLER_MEDIC_03,
	S4_OBJECT_SETTLER_AXEWARRIOR_01,
	S4_OBJECT_SETTLER_AXEWARRIOR_02,
	S4_OBJECT_SETTLER_AXEWARRIOR_03,
	S4_OBJECT_SETTLER_BLOWGUNWARRIOR_01,
	S4_OBJECT_SETTLER_BLOWGUNWARRIOR_02,
	S4_OBJECT_SETTLER_BLOWGUNWARRIOR_03,
	S4_OBJECT_SETTLER_SQUADLEADER,
	S4_OBJECT_SETTLER_PRIEST,
	S4_OBJECT_SETTLER_SABOTEUR,
	S4_OBJECT_SETTLER_PIONEER,
	S4_OBJECT_SETTLER_THIEF,
	S4_OBJECT_SETTLER_GEOLOGIST,
	S4_OBJECT_SETTLER_GARDENER,
	S4_OBJECT_SETTLER_LANDSCAPER,
	S4_OBJECT_SETTLER_DARKGARDENER,
	S4_OBJECT_SETTLER_MUSHROOMFARMER,
	S4_OBJECT_SETTLER_SHAMAN,
	S4_OBJECT_SETTLER_SLAVED_SETTLER,
	S4_OBJECT_SETTLER_TEMPLE_SERVANT,
	S4_OBJECT_SETTLER_ANGEL_01,
	S4_OBJECT_SETTLER_ANGEL_02,
	S4_OBJECT_SETTLER_ANGEL_03,
	S4_OBJECT_SETTLER_DONKEY,
	S4_OBJECT_SETTLER_BACKPACKCATAPULTIST_01,
	S4_OBJECT_SETTLER_BACKPACKCATAPULTIST_02,
	S4_OBJECT_SETTLER_BACKPACKCATAPULTIST_03,
	S4_OBJECT_SETTLER_SUNFLOWERFARMER,
	S4_OBJECT_SETTLER_SUNFLOWEROILMAKER,
	S4_OBJECT_SETTLER_MANACOPTERMASTER,

	// VEHICLES
	S4_OBJECT_VEHICLE = S4_OBJECT_SETTLER_MANACOPTERMASTER + 256,
	S4_OBJECT_VEHICLE_WARSHIP, // vehicle id 1
	S4_OBJECT_VEHICLE_FERRY,
	S4_OBJECT_VEHICLE_TRANSPORTSHIP,
	S4_OBJECT_VEHICLE_WARMACHINE,
	S4_OBJECT_VEHICLE_CART,
	S4_OBJECT_VEHICLE_FOUNDATION_CART,

	// PLANTS
	S4_OBJECT_PLANT = S4_OBJECT_VEHICLE_FOUNDATION_CART + 256,
	S4_OBJECT_PLANT_1,
	S4_OBJECT_PLANT_ROMAN_TREE = S4_OBJECT_PLANT_1 + 8, // todo: find out what the proper names are
	S4_OBJECT_PLANT_MAYAN_TREE = S4_OBJECT_PLANT_1 + 11,
	S4_OBJECT_PLANT_TROJAN_TREE = S4_OBJECT_PLANT_1 + 17,
	S4_OBJECT_PLANT_WHEAT = S4_OBJECT_PLANT_1 + 208,
	S4_OBJECT_PLANT_SUNFLOWER = S4_OBJECT_PLANT_1 + 254,
	// todo: add all plants

	// INDEX
	S4_OBJECT_TRIBE_INDEX = S4_OBJECT_TRIBE_ROMAN,
	S4_OBJECT_GOOD_INDEX = S4_OBJECT_GOOD_AGAVE,
	S4_OBJECT_GOOD_INDEX_LAST = S4_OBJECT_GOOD_SUNFLOWER,
	S4_OBJECT_BUILDING_INDEX = S4_OBJECT_BUILDING_WOODCUTTERHUT,
	S4_OBJECT_BUILDING_LAST = S4_OBJECT_BUILDING_SUNFLOWERFARMERHUT,
	S4_OBJECT_SETTLER_INDEX = S4_OBJECT_SETTLER_CARRIER,
	S4_OBJECT_SETTLER_INDEX_LAST = S4_OBJECT_SETTLER_MANACOPTERMASTER,
	S4_OBJECT_VEHICLE_INDEX = S4_OBJECT_VEHICLE_WARSHIP,
	S4_OBJECT_VEHICLE_INDEX_LAST = S4_OBJECT_VEHICLE_FOUNDATION_CART,
	S4_OBJECT_PLANT_INDEX = S4_OBJECT_PLANT_1,

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

enum S4_CUSTOM_UI_ENUM : DWORD {
	S4_CUSTOM_UI_UNSELECTED = 0,
	S4_CUSTOM_UI_SELECTED = 1,
	S4_CUSTOM_UI_HOVERING = 2,
	S4_CUSTOM_UI_HOVERING_SELECTED = 3,
};
typedef HRESULT(FAR S4HCALL* LPS4UICALLBACK)(LPCVOID lpUiElement, S4_CUSTOM_UI_ENUM newstate);
typedef BOOL(FAR S4HCALL* LPS4UIFILTERCALLBACK)(LPCVOID lpUiElement);
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

/** Callback types **/
typedef HRESULT(FAR S4HCALL* LPS4FRAMECALLBACK)(LPDIRECTDRAWSURFACE7 lpSurface, INT32 iPillarboxWidth, LPVOID lpReserved);
typedef HRESULT(FAR S4HCALL* LPS4MAPINITCALLBACK)(LPVOID lpReserved0, LPVOID lpReserved1);
typedef HRESULT(FAR S4HCALL* LPS4MOUSECALLBACK)(DWORD dwMouseButton, INT iX, INT iY, DWORD dwMsgId, HWND hwnd, LPCS4UIELEMENT lpUiElement);
typedef HRESULT(FAR S4HCALL* LPS4SETTLERSENDCALLBACK)(DWORD dwPosition, S4_MOVEMENT_ENUM dwCommand, LPVOID lpReserved);
typedef HRESULT(FAR S4HCALL* LPS4TICKCALLBACK)(DWORD dwTick, BOOL bHasEvent, BOOL bIsDelayed);


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

	/** Misc helper functions **/
	STDMETHOD(GetMD5OfModule)(THIS_ HMODULE module, LPSTR out, SIZE_T sz) PURE;
	STDMETHOD_(BOOL, IsEdition)(THIS_ S4_EDITION_ENUM edition) PURE;
	STDMETHOD_(HWND, GetHwnd)(THIS) PURE;

	/** Settlers 4 functions **/
	STDMETHOD(GetHoveringUiElement)(THIS_ LPS4UIELEMENT) PURE;
	STDMETHOD_(BOOL, IsCurrentlyOnScreen)(THIS_ S4_GUI_ENUM) PURE;
	STDMETHOD_(BOOL, IsObjectOfType)(THIS_ WORD object, S4_OBJECT_TYPE type);
	STDMETHOD_(BOOL, ClearSelection)(THIS) PURE;
	STDMETHOD_(BOOL, GetSelection)(THIS_ PWORD out, SIZE_T outlen, PSIZE_T selectionCount) PURE;
	STDMETHOD_(BOOL, RemoveSelection)(THIS_ PWORD settlers, SIZE_T settlerslen, PSIZE_T removedCount) PURE;
	STDMETHOD_(BOOL, StartBuildingPlacement)(THIS_ S4_OBJECT_TYPE building) PURE;

	/** Settlers 4 NetEvents functions **/
	STDMETHOD_(BOOL, SendWarriors)(THIS_ INT x, INT y, S4_MOVEMENT_ENUM mode, PWORD warriors, SIZE_T countOfWarriors, DWORD player = 0) PURE;
	STDMETHOD_(BOOL, BuildBuilding)(THIS_ S4_OBJECT_TYPE buildingType, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, CrushBuilding)(THIS_ DWORD building, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, ToggleBuildingPriority)(THIS_ DWORD building, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, ToggleBuildingHalt)(THIS_ DWORD building, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingWorkarea)(THIS_ DWORD building, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingProduction)(THIS_ DWORD building, S4_OBJECT_TYPE good, INT amount, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingProductionPercentMode)(THIS_ DWORD building, BOOL enable, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingProductionPercentage)(THIS_ DWORD building, BYTE swords, BYTE bows, BYTE armors, BYTE racespecialweapons, DWORD player = 0) PURE; // defined in CS4Build.cpp
	STDMETHOD_(BOOL, CastSpell)(THIS_ DWORD priest, DWORD spell, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Casting.cpp
	STDMETHOD_(BOOL, GarrisonWarriors)(THIS_ DWORD building, DWORD player = 0) PURE; // defined in CS4GarrisonWarriors.cpp
	STDMETHOD_(BOOL, UnGarrisonWarriors)(THIS_ DWORD building, INT column, BOOL bowman, DWORD player = 0) PURE; // defined in CS4GarrisonWarriors.cpp
	STDMETHOD_(BOOL, ChangeGoodDistribution)(THIS_ S4_OBJECT_TYPE good, S4_OBJECT_TYPE building, INT percent, DWORD ecosector, DWORD player = 0) PURE; // defined in CS4GoodDistribution.cpp
	STDMETHOD_(BOOL, ChangeGoodPriority)(THIS_ S4_OBJECT_TYPE good, INT offset, DWORD ecosector, DWORD player = 0) PURE; // defined in CS4GoodDistribution.cpp
	STDMETHOD_(BOOL, RecruitWarriors)(THIS_ DWORD building, S4_OBJECT_TYPE unit, INT amount, DWORD player = 0) PURE; // defined in CS4Recruit.cpp
	STDMETHOD_(BOOL, SetTradingRoute)(THIS_ DWORD sourceBuilding, DWORD destinationBuilding, DWORD player = 0) PURE; // defined in CS4Trading.cpp
	STDMETHOD_(BOOL, TradeGood)(THIS_ DWORD buidling, S4_OBJECT_TYPE good, INT amount, DWORD player = 0) PURE; // defined in CS4Trading.cpp
	STDMETHOD_(BOOL, StoreGood)(THIS_ DWORD buidling, S4_OBJECT_TYPE good, BOOL enable, DWORD player = 0) PURE; // defined in CS4Trading.cpp

	/** UI Rendering **/
	STDMETHOD_(S4CUSTOMUI, ShowMessageBox)(THIS_ LPCWSTR title, LPCWSTR message, INT x, INT y, INT w, INT h) PURE;
	STDMETHOD_(S4CUSTOMUI, CreateCustomUiElement)(THIS_ LPCS4CUSTOMUIELEMENT) PURE;
	STDMETHOD_(BOOL, DestroyCustomUiElement)(THIS_ S4CUSTOMUI) PURE;
	STDMETHOD_(BOOL, HideCustomUiElement)(THIS_ S4CUSTOMUI) PURE;
	STDMETHOD_(BOOL, ShowCustomUiElement)(THIS_ S4CUSTOMUI) PURE;

	/** S4 Scripting **/
	STDMETHOD_(BOOL, RevealWorldMap)(THIS_ BOOL) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetZoom)(THIS_ DWORD level) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetWorldCursor)(THIS_ INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, DeleteWorldCursor)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, AddSettlers)(THIS_ S4_OBJECT_TYPE settler, DWORD amount, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, ShowTextMessage)(THIS_ LPCSTR message, DWORD icon = 9, DWORD reserved = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GetLocalPlayer)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(S4_OBJECT_TYPE, GetPlayerTribe)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp

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

#endif