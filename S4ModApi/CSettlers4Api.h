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

#pragma once

#include "S4ModApi.h"
#include "Log.h"

extern "C" { 

struct CSettlers4Api : public ISettlers4Api {
	/** IUnknown methods **/
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj); // defined in CS4Unknown.cpp
	STDMETHOD_(ULONG, AddRef) (THIS); // defined in CS4Unknown.cpp
	STDMETHOD_(ULONG, Release) (THIS); // defined in CS4Unknown.cpp

	/** ISettlers4Api methods **/
	STDMETHOD_(DWORD, GetLastError) (THIS);
	STDMETHOD_(LPVOID, GetDebugData) (THIS_ LPVOID reserved0, LPVOID reserved1); // defined in CS4Debug.cpp

	STDMETHOD(RemoveListener)(THIS_ S4HOOK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddFrameListener)(THIS_ LPS4FRAMECALLBACK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddUIFrameListener)(THIS_ LPS4FRAMECALLBACK, S4_GUI_ENUM); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddMapInitListener)(THIS_ LPS4MAPINITCALLBACK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddMouseListener)(THIS_ LPS4MOUSECALLBACK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddSettlerSendListener)(THIS_ LPS4SETTLERSENDCALLBACK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddTickListener)(THIS_ LPS4TICKCALLBACK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddLuaOpenListener)(THIS_ LPS4LUAOPENCALLBACK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddBltListener)(THIS_ LPS4BLTCALLBACK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddEntityListener)(THIS_ LPS4ENTITYCALLBACK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddGuiBltListener)(THIS_ LPS4GUIBLTCALLBACK); // defined in CS4Listeners.cpp
	STDMETHOD_(S4HOOK, AddGuiClearListener)(THIS_ LPS4GUICLEARCALLBACK); // defined in CS4Listeners.cpp

	STDMETHOD(GetMD5OfModule)(THIS_ HMODULE module, LPSTR out, SIZE_T sz); // defined in CS4Misc.cpp
	STDMETHOD_(BOOL, IsEdition)(THIS_ S4_EDITION_ENUM edition); // defined in CS4Misc.cpp
	STDMETHOD_(HWND, GetHwnd)(THIS_); // defined in CS4Misc.cpp
	STDMETHOD(GetHoveringUiElement)(THIS_ LPS4UIELEMENT); // defined in CS4Misc.cpp
	STDMETHOD_(BOOL, IsCurrentlyOnScreen)(THIS_ S4_GUI_ENUM); // defined in CS4Screen.cpp
	STDMETHOD_(S4_ENTITY_ENUM, EntityGetClass)(THIS_ WORD entity); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntityGetPosition)(THIS_ WORD entity, LPINT x, LPINT y); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntitygGetDirection)(THIS_ WORD entity, LPDWORD dir); // 4 == top-left, etc. defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntityGetHealth)(THIS_ WORD entity, LPDWORD health); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntityGetMaxHealth)(THIS_ WORD entity, LPDWORD maxHealth); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntityGetTribe)(THIS_ WORD entity, S4_TRIBE_ENUM* tribe); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntityTreeGetType)(THIS_ WORD entity, S4_TREE_ENUM* tree); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntityPileGetType)(THIS_ WORD entity, S4_GOOD_ENUM* good); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntityDecoGetType)(THIS_ WORD entity, LPDWORD deco); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntityPileGetAmount)(THIS_ WORD entity, LPDWORD amount); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntitySettlerGetType)(THIS_ WORD entity, S4_SETTLER_ENUM* settler); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntityVehicleGetType)(THIS_ WORD entity, S4_VEHICLE_ENUM* vehicle); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntityAnimalGetType)(THIS_ WORD entity, S4_ANIMAL_ENUM* animal); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntityBuildingGetType)(THIS_ WORD entity, S4_BUILDING_ENUM* building); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntityStoneGetLevel)(THIS_ WORD entity, LPDWORD level); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntityGetRole)(THIS_ WORD entity, LPVOID* role); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntitygGetRoleClass)(THIS_ WORD entity, S4_ROLE_ENUM* role); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, EntitygGetOwner)(THIS_ WORD entity, LPDWORD player); // defined in CS4Entity.cpp
	STDMETHOD_(BOOL, ClearSelection)(THIS); // defined in CS4Selection.cpp
	STDMETHOD_(BOOL, GetSelection)(THIS_ PWORD out, SIZE_T outlen, PSIZE_T selectionCount); // defined in CS4Selection.cpp
	STDMETHOD_(BOOL, RemoveSelection)(THIS_ PWORD settlers, SIZE_T settlerslen, PSIZE_T removedCount); // defined in CS4Selection.cpp
	STDMETHOD_(BOOL, StartBuildingPlacement)(THIS_ S4_BUILDING_ENUM building); // defined in CS4MenuEvents.cpp

	/** Landscape functions **/
	STDMETHOD_(DWORD, LandscapeGetHeight)(THIS_ INT x, INT y); // defined in CS4Landscape.cpp
	STDMETHOD_(S4_GROUND_ENUM, LandscapeGetType)(THIS_ INT x, INT y); // defined in CS4Landscape.cpp
	STDMETHOD_(BOOL, LandscapeIsPond)(THIS_ INT x, INT y); // defined in CS4Landscape.cpp
	STDMETHOD_(BOOL, LandscapeIsDarkLand)(THIS_ INT x, INT y); // defined in CS4Landscape.cpp
	STDMETHOD_(BOOL, LandscapeIsDarkLandBorder)(THIS_ INT x, INT y); // defined in CS4Landscape.cpp
	STDMETHOD_(DWORD, LandscapeGetFogOfWar)(THIS_ INT x, INT y); // defined in CS4Landscape.cpp
	STDMETHOD_(BOOL, LandscapeIsFoundingStone)(THIS_ INT x, INT y); // defined in CS4Landscape.cpp
	STDMETHOD_(S4_RESOURCE_ENUM, LandscapeGetResource)(THIS_ INT x, INT y); // defined in CS4Landscape.cpp
	STDMETHOD_(BOOL, LandscapeSetResource)(THIS_ INT x, INT y, S4_RESOURCE_ENUM res); // defined in CS4Landscape.cpp
	STDMETHOD_(DWORD, LandscapeGetObject)(THIS_ INT x, INT y); // defined in CS4Landscape.cpp
	STDMETHOD_(DWORD, LandscapeGetOwner)(THIS_ INT x, INT y); // defined in CS4Landscape.cpp

	/** Settlers 4 NetEvents functions **/
	STDMETHOD_(BOOL, SendWarriors)(THIS_ INT x, INT y, S4_MOVEMENT_ENUM mode, PWORD warriors, SIZE_T countOfWarriors, DWORD player); // defined in CS4SendWarriors.cpp
	STDMETHOD_(BOOL, BuildBuilding)(THIS_ S4_BUILDING_ENUM buildingType, INT x, INT y, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, CrushBuilding)(THIS_ DWORD building, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, ToggleBuildingPriority)(THIS_ DWORD building, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, ToggleBuildingHalt)(THIS_ DWORD building, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingWorkarea)(THIS_ DWORD building, INT x, INT y, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingProduction)(THIS_ DWORD building, S4_GOOD_ENUM good, INT amount, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingProductionPercentMode)(THIS_ DWORD building, BOOL enable, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, SetBuildingProductionPercentage)(THIS_ DWORD building, BYTE swords, BYTE bows, BYTE armors, BYTE racespecialweapons, DWORD player); // defined in CS4Build.cpp
	STDMETHOD_(BOOL, CastSpell)(THIS_ DWORD priest, DWORD spell, INT x, INT y, DWORD player); // defined in CS4Casting.cpp
	STDMETHOD_(BOOL, GarrisonWarriors)(THIS_ DWORD building, DWORD player); // defined in CS4GarrisonWarriors.cpp
	STDMETHOD_(BOOL, UnGarrisonWarriors)(THIS_ DWORD building, INT column, BOOL bowman, DWORD player); // defined in CS4GarrisonWarriors.cpp
	STDMETHOD_(BOOL, ChangeGoodDistribution)(THIS_ S4_GOOD_ENUM good, S4_BUILDING_ENUM building, INT percent, DWORD ecosector, DWORD player); // defined in CS4GoodDistribution.cpp
	STDMETHOD_(BOOL, ChangeGoodPriority)(THIS_ S4_GOOD_ENUM good, INT offset, DWORD ecosector, DWORD player); // defined in CS4GoodDistribution.cpp
	STDMETHOD_(BOOL, RecruitWarriors)(THIS_ DWORD building, S4_SETTLER_ENUM unit, INT amount, DWORD player); // defined in CS4Recruit.cpp
	STDMETHOD_(BOOL, RecruitVehicle)(THIS_ DWORD building, S4_VEHICLE_ENUM unit, INT amount, DWORD player); // defined in CS4Recruit.cpp
	STDMETHOD_(BOOL, SetTradingRoute)(THIS_ DWORD sourceBuilding, DWORD destinationBuilding, DWORD player); // defined in CS4Trading.cpp
	STDMETHOD_(BOOL, TradeGood)(THIS_ DWORD buidling, S4_GOOD_ENUM good, INT amount, DWORD player); // defined in CS4Trading.cpp
	STDMETHOD_(BOOL, StoreGood)(THIS_ DWORD buidling, S4_GOOD_ENUM good, BOOL enable, DWORD player); // defined in CS4Trading.cpp

	STDMETHOD_(S4CUSTOMUI, ShowMessageBox)(THIS_ LPCWSTR title, LPCWSTR message, INT x, INT y, INT w, INT h, DWORD flags); // defined in CS4Screen.cpp
	STDMETHOD_(S4CUSTOMUI, CreateCustomUiElement)(THIS_ LPCS4CUSTOMUIELEMENT);
	STDMETHOD_(BOOL, DestroyCustomUiElement)(THIS_ S4CUSTOMUI);
	STDMETHOD_(BOOL, HideCustomUiElement)(THIS_ S4CUSTOMUI);
	STDMETHOD_(BOOL, ShowCustomUiElement)(THIS_ S4CUSTOMUI);

	/** S4 Scripting **/
	STDMETHOD_(DWORD, GetLocalPlayer)(THIS); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsAdd)(THIS_ S4_BUILDING_ENUM building, INT x, INT y, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsAmount)(THIS_ S4_BUILDING_ENUM building, DWORD status, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, BuildingsCrush)(THIS_ DWORD building); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, BuildingsDelete)(THIS_ DWORD building, DWORD mode); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, BuildingsExistsBuildingInArea)(THIS_ S4_BUILDING_ENUM building, INT x, INT y, INT r, DWORD status, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsGetFirstBuilding)(THIS_ S4_BUILDING_ENUM building, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsGetInhabitantAmount)(THIS_ DWORD building, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, BuildingsGetTarget)(THIS_ DWORD building); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, BuildingsIsSelected)(THIS_ S4_BUILDING_ENUM building); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, DarkTribeAddManakopter)(THIS_ INT x, INT y, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, DarkTribeFlyTo)(THIS_ INT x, INT y); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, AIActivate)(THIS_ DWORD player, BOOL activate); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MakeDark)(THIS_ INT x, INT y); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MakeGreen)(THIS_ INT x, INT y); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, EffectsAdd)(THIS_ DWORD effect, DWORD sound, INT x, INT y, DWORD delay); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, ArePlayerAreasConnected)(THIS_ INT x1, INT y1, DWORD player2, INT x2, INT y2, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, GameDefaultGameEndCheck)(THIS); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, DisableLastNPlayersInStatistic)(THIS_ DWORD n); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, EnableLandExploredCheck)(THIS); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, FindAnyUnit)(THIS_ INT x, INT y, INT r, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GetAmountOfTreesInArea)(THIS_ INT x, INT y, INT r); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GetDifficulty)(THIS); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GetNumberOfSquaresWithDarkLand)(THIS_ DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GetOffenceFightingStrength)(THIS_ DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, HasPlayerLost)(THIS_ DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, IsAlmostAllLandExplored)(THIS_ DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, IsAreaDarkLand)(THIS_ INT x, INT y, INT r); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, IsAreaGreen)(THIS_ INT x, INT y, INT r); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, IsAreaOwned)(THIS_ INT x, INT y, INT r, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GetNumberOfPlayers)(THIS); // defined in CS4Scripting.cpp
	STDMETHOD_(S4_TRIBE_ENUM, GetPlayerTribe)(THIS_ DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, ResetFogging)(THIS); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetAlliesDontRevealFog)(THIS_ BOOL enable); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetFightingStrength)(THIS_ DWORD strength, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, ShowClock)(THIS_ DWORD seconds); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, Time)(THIS); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GoodsAddPileEx)(THIS_ S4_GOOD_ENUM good, DWORD amount, INT x, INT y); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GoodsAmount)(THIS_ S4_GOOD_ENUM good, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GoodsDelete)(THIS_ S4_GOOD_ENUM good, INT x, INT y, INT r); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, GoodsGetAmountInArea)(THIS_ S4_GOOD_ENUM good, INT x, INT y, INT r, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, MagicCastSpell)(THIS_ S4_TRIBE_ENUM tribe, S4_SPELL_ENUM spell, INT x, INT y, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MagicIncreaseMana)(THIS_ INT amount, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, MapAddDecoObject)(THIS_ DWORD object, INT x, INT y); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MapDeleteDecoObject)(THIS_ INT x, INT y, INT r); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, MapSize)(THIS); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MapPointIsOnScreen)(THIS_ INT x, INT y); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, MapSetScreenPos)(THIS_ INT x, INT y); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersAdd)(THIS_ S4_SETTLER_ENUM settler, INT amount, INT x, INT y, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersAddToFerry)(THIS_ DWORD ferry, S4_SETTLER_ENUM settler, INT amount); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, SettlersAmount)(THIS_ S4_SETTLER_ENUM settler, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, SettlersAmountInArea)(THIS_ S4_SETTLER_ENUM settler, INT x, INT y, INT r, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersIsSelected)(THIS_ S4_SETTLER_ENUM settler, INT amount); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersKillSelectableSettlers)(THIS_ S4_SETTLER_ENUM settler, INT x, INT y, INT r, BOOL animation, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, SettlersProductionAmount)(THIS_ S4_SETTLER_ENUM settler); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SettlersSetHealthInArea)(THIS_ S4_SETTLER_ENUM settler, INT x, INT y, INT r, DWORD health, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticBuildingsCaptured)(THIS_ DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticGoodsProduced)(THIS_ DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticLandOwnedByPlayer)(THIS_ DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticManaCollected)(THIS_ DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticMushroomFarmsDestroyed)(THIS_ DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticServantsFreed)(THIS_ DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticSpellsCast)(THIS_ DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, StatisticUnitsDestroyed)(THIS_ DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, ClearMarker)(THIS); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, DeleteWorldCursor)(THIS); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, PressButton)(THIS_ DWORD dialog, DWORD control); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, RevealWorldMap)(THIS_ BOOL enable); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SelectNextBuilding)(THIS_ S4_BUILDING_ENUM building); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetMarker)(THIS_ INT x, INT y); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetWorldCursor)(THIS_ INT x, INT y); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetZoom)(THIS_ INT zoom); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesAdd)(THIS_ S4_VEHICLE_ENUM vehicle, DWORD direction, DWORD ammo, DWORD commands, INT x, INT y, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, VehiclesAddWheelerToFerry)(THIS_ DWORD ferry, S4_VEHICLE_ENUM vehicle); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesAmount)(THIS_ S4_VEHICLE_ENUM vehicle, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesAmountInArea)(THIS_ S4_VEHICLE_ENUM vehicle, INT x, INT y, INT r, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesGetFerryCargoInArea)(THIS_ INT x, INT y, INT r, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(DWORD, VehiclesGetHealth)(THIS_ INT x, INT y); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, VehiclesIsSelected)(THIS_ S4_VEHICLE_ENUM vehicle, INT amount); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, VehiclesKill)(THIS_ S4_VEHICLE_ENUM vehicle, INT x, INT y, INT r, DWORD player); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, SetGround)(THIS_ INT x, INT y, INT r, DWORD ground); // defined in CS4Scripting.cpp
	STDMETHOD_(BOOL, ShowTextMessage)(THIS_ LPCSTR message, DWORD icon, DWORD reserved); // defined in CS4Scripting.cpp

	~CSettlers4Api();  // defined in CS4Singleton.cpp
	static CSettlers4Api& GetInstance(); // defined in CS4Singleton.cpp

private:
	CSettlers4Api(); // defined in CS4Singleton.cpp

	LONG m_refs;
};


}