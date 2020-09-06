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
typedef HRESULT(FAR S4HCALL* LPS4LUAOPENCALLBACK)(VOID);


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
	STDMETHOD_(S4CUSTOMUI, ShowMessageBox)(THIS_ LPCWSTR title, LPCWSTR message, INT x, INT y, INT w, INT h, DWORD flags = 0) PURE;
	STDMETHOD_(S4CUSTOMUI, CreateCustomUiElement)(THIS_ LPCS4CUSTOMUIELEMENT) PURE;
	STDMETHOD_(BOOL, DestroyCustomUiElement)(THIS_ S4CUSTOMUI) PURE;
	STDMETHOD_(BOOL, HideCustomUiElement)(THIS_ S4CUSTOMUI) PURE;
	STDMETHOD_(BOOL, ShowCustomUiElement)(THIS_ S4CUSTOMUI) PURE;

	/** S4 Scripting **/
	STDMETHOD_(DWORD, GetLocalPlayer)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsAdd)(THIS_ S4_OBJECT_TYPE building, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsAmount)(THIS_ S4_OBJECT_TYPE building, DWORD status, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, BuildingsCrush)(THIS_ DWORD building) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, BuildingsDelete)(THIS_ DWORD building, DWORD mode) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, BuildingsExistsBuildingInArea)(THIS_ S4_OBJECT_TYPE building, INT x, INT y, INT r, DWORD status, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsGetFirstBuilding)(THIS_ S4_OBJECT_TYPE building, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsGetInhabitantAmount)(THIS_ DWORD building, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsGetTarget)(THIS_ DWORD building) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, BuildingsIsSelected)(THIS_ S4_OBJECT_TYPE building) PURE; // defined in CS4Scripting.cpp
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
	STDMETHOD_(S4_OBJECT_TYPE, GetPlayerTribe)(THIS_ DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, ResetFogging)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetAlliesDontRevealFog)(THIS_ BOOL enable) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetFightingStrength)(THIS_ DWORD strength, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, ShowClock)(THIS_ DWORD seconds) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, Time)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GoodsAddPileEx)(THIS_ S4_OBJECT_TYPE good, DWORD amount, INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GoodsAmount)(THIS_ S4_OBJECT_TYPE good, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GoodsDelete)(THIS_ S4_OBJECT_TYPE good, INT x, INT y, INT r) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GoodsGetAmountInArea)(THIS_ S4_OBJECT_TYPE good, INT x, INT y, INT r, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, MagicCastSpell)(THIS_ S4_OBJECT_TYPE tribe, S4_OBJECT_TYPE spell, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MagicIncreaseMana)(THIS_ INT amount, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, MapAddDecoObject)(THIS_ DWORD object, INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MapDeleteDecoObject)(THIS_ INT x, INT y, INT r) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, MapSize)(THIS) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MapPointIsOnScreen)(THIS_ INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MapSetScreenPos)(THIS_ INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersAdd)(THIS_ S4_OBJECT_TYPE settler, INT amount, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersAddToFerry)(THIS_ DWORD ferry, S4_OBJECT_TYPE settler, INT amount) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, SettlersAmount)(THIS_ S4_OBJECT_TYPE settler, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, SettlersAmountInArea)(THIS_ S4_OBJECT_TYPE settler, INT x, INT y, INT r, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersIsSelected)(THIS_ S4_OBJECT_TYPE settler, INT amount) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersKillSelectableSettlers)(THIS_ S4_OBJECT_TYPE settler, INT x, INT y, INT r, BOOL animation, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, SettlersProductionAmount)(THIS_ S4_OBJECT_TYPE settler) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersSetHealthInArea)(THIS_ S4_OBJECT_TYPE settler, INT x, INT y, INT r, DWORD health, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
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
	STDMETHOD_(BOOL, SelectNextBuilding)(THIS_ S4_OBJECT_TYPE building) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetMarker)(THIS_ INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetWorldCursor)(THIS_ INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetZoom)(THIS_ INT zoom) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesAdd)(THIS_ S4_OBJECT_TYPE vehicle, DWORD direction, DWORD ammo, DWORD commands, INT x, INT y, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, VehiclesAddWheelerToFerry)(THIS_ DWORD ferry, S4_OBJECT_TYPE vehicle) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesAmount)(THIS_ S4_OBJECT_TYPE vehicle, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesAmountInArea)(THIS_ S4_OBJECT_TYPE vehicle, INT x, INT y, INT r, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesGetFerryCargoInArea)(THIS_ INT x, INT y, INT r, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesGetHealth)(THIS_ INT x, INT y) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, VehiclesIsSelected)(THIS_ S4_OBJECT_TYPE vehicle, INT amount) PURE; // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, VehiclesKill)(THIS_ S4_OBJECT_TYPE vehicle, INT x, INT y, INT r, DWORD player = 0) PURE; // defined in CS4Scripting.cpp
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