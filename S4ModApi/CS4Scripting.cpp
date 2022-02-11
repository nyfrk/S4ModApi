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

#include "CSettlers4Api.h"
#include "patterns.h"
#include "globals.h"
#include "safemem.h"
#include "s4.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

static inline void lua_push(double d) { lua_pushnumber(d); }
static inline void lua_push(char* s) { lua_pushstring(s); }
static bool _IsLuaState() { return S4::GetInstance().GetLuaState() != 0; }
#define CHECK_LUA_STATE if (!_IsLuaState()) return 0;
static bool CallLuaFunc(char* lst, char* fun) {	lua_pushobject(lua_getglobal(lst));	lua_push(fun); return !lua_callfunction(lua_gettable()); }
#define LUA_PUSH1(a) lua_push(a);
#define LUA_PUSH2(a,b) LUA_PUSH1(a);lua_push(b);
#define LUA_PUSH3(a,b,c) LUA_PUSH2(a,b);lua_push(c);
#define LUA_PUSH4(a,b,c,d) LUA_PUSH3(a,b,c);lua_push(d);
#define LUA_PUSH5(a,b,c,d,e) LUA_PUSH4(a,b,c,d);lua_push(e);
#define LUA_PUSH6(a,b,c,d,e,f) LUA_PUSH5(a,b,c,d,e);lua_push(f);
#define LUA_PUSH7(a,b,c,d,e,f,g) LUA_PUSH6(a,b,c,d,e,f);lua_push(g);
#define PLAYER_GUARD_(t) if (!player) {player = S4::GetInstance().GetLocalPlayer(); if (!player) return t;}
#define PLAYER_GUARD PLAYER_GUARD_(0)
#define NO_GUARD ;
#define LUA_RET_NUMBER(lst,fun) (CallLuaFunc(lst, fun) ? (DWORD)lua_getnumber(lua_getresult(1)) : (DWORD)0);
#define LUA_RET_VOID(lst,fun) CallLuaFunc(lst, fun)

// let the lua lib link to the original heap management functions
extern "C" void* __cdecl _s4_realloc(void* b, size_t s) {
	return S4::GetInstance().realloc(b, s);
}
extern "C" void __cdecl _s4_free(void* b) {
	return S4::GetInstance().free(b);
}
extern "C" void* __cdecl _s4_lua_state() {
	return S4::GetInstance().GetLuaState();
}

// export the lua functions
//#pragma comment(linker, "/EXPORT:_" "lua_open") // todo: make state manipulation possible
//#pragma comment(linker, "/EXPORT:_" "lua_close")
//#pragma comment(linker, "/EXPORT:_" "lua_setstate")
#pragma comment(linker, "/EXPORT:_" "lua_settagmethod")
#pragma comment(linker, "/EXPORT:_" "lua_gettagmethod")
#pragma comment(linker, "/EXPORT:_" "lua_newtag")
#pragma comment(linker, "/EXPORT:_" "lua_copytagmethods")
#pragma comment(linker, "/EXPORT:_" "lua_settag")
#pragma comment(linker, "/EXPORT:_" "lua_error")
#pragma comment(linker, "/EXPORT:_" "lua_dofile")
#pragma comment(linker, "/EXPORT:_" "lua_dostring")
#pragma comment(linker, "/EXPORT:_" "lua_dobuffer")
#pragma comment(linker, "/EXPORT:_" "lua_callfunction")
#pragma comment(linker, "/EXPORT:_" "lua_beginblock")
#pragma comment(linker, "/EXPORT:_" "lua_endblock")
#pragma comment(linker, "/EXPORT:_" "lua_lua2C")
#pragma comment(linker, "/EXPORT:_" "lua_isnil")
#pragma comment(linker, "/EXPORT:_" "lua_istable")
#pragma comment(linker, "/EXPORT:_" "lua_isuserdata")
#pragma comment(linker, "/EXPORT:_" "lua_iscfunction")
#pragma comment(linker, "/EXPORT:_" "lua_isnumber")
#pragma comment(linker, "/EXPORT:_" "lua_isstring")
#pragma comment(linker, "/EXPORT:_" "lua_isfunction")
#pragma comment(linker, "/EXPORT:_" "lua_getnumber")
#pragma comment(linker, "/EXPORT:_" "lua_getstring")
#pragma comment(linker, "/EXPORT:_" "lua_strlen")
#pragma comment(linker, "/EXPORT:_" "lua_getcfunction")
#pragma comment(linker, "/EXPORT:_" "lua_getuserdata")
#pragma comment(linker, "/EXPORT:_" "lua_pushnil")
#pragma comment(linker, "/EXPORT:_" "lua_pushnumber")
#pragma comment(linker, "/EXPORT:_" "lua_pushlstring")
#pragma comment(linker, "/EXPORT:_" "lua_pushstring")
#pragma comment(linker, "/EXPORT:_" "lua_pushlstring")
#pragma comment(linker, "/EXPORT:_" "lua_pushcclosure")
#pragma comment(linker, "/EXPORT:_" "lua_pushusertag")
#pragma comment(linker, "/EXPORT:_" "lua_pushobject")
#pragma comment(linker, "/EXPORT:_" "lua_pop")
#pragma comment(linker, "/EXPORT:_" "lua_getglobal")
#pragma comment(linker, "/EXPORT:_" "lua_rawgetglobal")
#pragma comment(linker, "/EXPORT:_" "lua_setglobal")
#pragma comment(linker, "/EXPORT:_" "lua_rawsetglobal")
#pragma comment(linker, "/EXPORT:_" "lua_settable")
#pragma comment(linker, "/EXPORT:_" "lua_rawsettable")
#pragma comment(linker, "/EXPORT:_" "lua_gettable")
#pragma comment(linker, "/EXPORT:_" "lua_rawgettable")
#pragma comment(linker, "/EXPORT:_" "lua_tag")
#pragma comment(linker, "/EXPORT:_" "lua_nextvar")
#pragma comment(linker, "/EXPORT:_" "lua_next")
#pragma comment(linker, "/EXPORT:_" "lua_ref")
#pragma comment(linker, "/EXPORT:_" "lua_getref")
#pragma comment(linker, "/EXPORT:_" "lua_unref")
#pragma comment(linker, "/EXPORT:_" "lua_createtable")
#pragma comment(linker, "/EXPORT:_" "lua_collectgarbage")
#pragma comment(linker, "/EXPORT:_" "lua_seterrormethod")
#pragma comment(linker, "/EXPORT:_" "luaL_openlib")
#pragma comment(linker, "/EXPORT:_" "luaL_argerror")
#pragma comment(linker, "/EXPORT:_" "luaL_check_lstr")
#pragma comment(linker, "/EXPORT:_" "luaL_opt_lstr")
#pragma comment(linker, "/EXPORT:_" "luaL_check_number")
#pragma comment(linker, "/EXPORT:_" "luaL_opt_number")
#pragma comment(linker, "/EXPORT:_" "luaL_functionarg")
#pragma comment(linker, "/EXPORT:_" "luaL_tablearg")
#pragma comment(linker, "/EXPORT:_" "luaL_nonnullarg")
#pragma comment(linker, "/EXPORT:_" "luaL_verror")
#pragma comment(linker, "/EXPORT:_" "luaL_openspace")
#pragma comment(linker, "/EXPORT:_" "luaL_resetbuffer")
#pragma comment(linker, "/EXPORT:_" "luaL_addchar")
#pragma comment(linker, "/EXPORT:_" "luaL_getsize")
#pragma comment(linker, "/EXPORT:_" "luaL_addsize")
#pragma comment(linker, "/EXPORT:_" "luaL_newbuffer")
#pragma comment(linker, "/EXPORT:_" "luaL_oldbuffer")
#pragma comment(linker, "/EXPORT:_" "luaL_buffer")
#pragma comment(linker, "/EXPORT:_" "luaL_findstring")
#pragma comment(linker, "/EXPORT:_" "luaL_chunkid")
#pragma comment(linker, "/EXPORT:_" "luaL_filesource")
#pragma comment(linker, "/EXPORT:_" "lua_stackedfunction")
#pragma comment(linker, "/EXPORT:_" "lua_funcinfo")
#pragma comment(linker, "/EXPORT:_" "lua_currentline")
#pragma comment(linker, "/EXPORT:_" "lua_getobjname")
#pragma comment(linker, "/EXPORT:_" "lua_getlocal")
#pragma comment(linker, "/EXPORT:_" "lua_setlocal")
#pragma comment(linker, "/EXPORT:_" "lua_nups")
#pragma comment(linker, "/EXPORT:_" "lua_setlinehook")
#pragma comment(linker, "/EXPORT:_" "lua_setcallhook")
#pragma comment(linker, "/EXPORT:_" "lua_setdebug")


DWORD CSettlers4Api::GetLocalPlayer() {
	TRACE;
	return S4::GetInstance().GetLocalPlayer();
}

DWORD CSettlers4Api::BuildingsAdd(S4_BUILDING_ENUM building, INT x, INT y, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH4(x, y, player, building);
	return LUA_RET_NUMBER("Buildings", "AddBuilding");
}

DWORD CSettlers4Api::BuildingsAmount(S4_BUILDING_ENUM building, DWORD status, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH3(player, building, status);
	return LUA_RET_NUMBER("Buildings", "Amount");
}

BOOL CSettlers4Api::BuildingsCrush(DWORD building) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH1(building);
	return LUA_RET_VOID("Buildings", "CrushBuilding");
}

BOOL CSettlers4Api::BuildingsDelete(DWORD building, DWORD mode) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH2(building, mode);
	return LUA_RET_VOID("Buildings", "Delete");
}

BOOL CSettlers4Api::BuildingsExistsBuildingInArea(S4_BUILDING_ENUM building, INT x, INT y, INT r, DWORD status, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH6(player, building, x, y, r, status);
	return LUA_RET_NUMBER("Buildings", "ExistsBuildingInArea");
}

DWORD CSettlers4Api::BuildingsGetFirstBuilding(S4_BUILDING_ENUM building, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH2(player, building);
	return LUA_RET_NUMBER("Buildings", "GetFirstBuilding");
}

DWORD CSettlers4Api::BuildingsGetInhabitantAmount(DWORD building, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH2(player, building);
	return LUA_RET_NUMBER("Buildings", "GetInhabitantAmount");
}

DWORD CSettlers4Api::BuildingsGetTarget(DWORD building) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH1(building);
	return LUA_RET_NUMBER("Buildings", "GetTarget");
}

BOOL CSettlers4Api::BuildingsIsSelected(S4_BUILDING_ENUM building) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH1(building);
	return LUA_RET_NUMBER("Buildings", "IsSelected");
}

DWORD CSettlers4Api::DarkTribeAddManakopter(INT x, INT y, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH3(x,y,player);
	return LUA_RET_NUMBER("DarkTribe", "AddManakopter");
}

BOOL CSettlers4Api::DarkTribeFlyTo(INT x, INT y) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH2(x, y);
	return LUA_RET_VOID("DarkTribe", "FlyTo");
}

BOOL CSettlers4Api::AIActivate(DWORD player, BOOL activate) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH1(player);
	return LUA_RET_VOID("Debug", activate ? "ActivateAI" : "DeactivateAI");
}

BOOL CSettlers4Api::MakeDark(INT x, INT y) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH2(x, y);
	return LUA_RET_VOID("Debug", "MakeDark");
}

BOOL CSettlers4Api::MakeGreen(INT x, INT y) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH2(x, y);
	return LUA_RET_VOID("Debug", "MakeGreen");
}

DWORD CSettlers4Api::EffectsAdd(DWORD effect, DWORD sound, INT x, INT y, DWORD delay) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH5(effect, sound, x, y, delay);
	return LUA_RET_NUMBER("Effects", "AddEffect");
}

DWORD CSettlers4Api::ArePlayerAreasConnected(INT x1, INT y1, DWORD player2, INT x2, INT y2, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH6(player2, x1, y1, player, x2, y2);
	return LUA_RET_NUMBER("Game", "ArePlayerAreasConnected");
}

BOOL CSettlers4Api::GameDefaultGameEndCheck() {
	TRACE;
	CHECK_LUA_STATE;
	return LUA_RET_VOID("Game", "DefaultGameEndCheck");
}

BOOL CSettlers4Api::DisableLastNPlayersInStatistic(DWORD n) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH1(n)
	return LUA_RET_VOID("Game", "DisableLastNPlayersInStatistic");
}

BOOL CSettlers4Api::EnableLandExploredCheck() {
	TRACE;
	CHECK_LUA_STATE;
	return LUA_RET_VOID("Game", "EnableLandExploredCheck");
}

BOOL CSettlers4Api::FindAnyUnit(INT x, INT y, INT r, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH4(player, x, y, r);
	return LUA_RET_NUMBER("Game", "FindAnyUnit");
}

DWORD CSettlers4Api::GetAmountOfTreesInArea(INT x, INT y, INT r) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH3(x, y, r);
	return LUA_RET_NUMBER("Game", "GetAmountOfTreesInArea");
}

DWORD CSettlers4Api::GetDifficulty() {
	TRACE;
	CHECK_LUA_STATE;
	return LUA_RET_NUMBER("Game", "GetDifficulty");
}

DWORD CSettlers4Api::GetNumberOfSquaresWithDarkLand(DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH1(player);
	return LUA_RET_NUMBER("Game", "GetNumberOfSquaresWithDarkLand");
}

DWORD CSettlers4Api::GetOffenceFightingStrength(DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH1(player);
	return LUA_RET_NUMBER("Game", "GetOffenceFightingStrength");
}

BOOL CSettlers4Api::HasPlayerLost(DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH1(player);
	return LUA_RET_NUMBER("Game", "HasPlayerLost");
}

BOOL CSettlers4Api::IsAlmostAllLandExplored(DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH1(player);
	return LUA_RET_NUMBER("Game", "IsAlmostAllLandExplored");
}

BOOL CSettlers4Api::IsAreaDarkLand(INT x, INT y, INT r) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH3(x, y, r);
	return LUA_RET_NUMBER("Game", "IsAreaDarkLand");
}

BOOL CSettlers4Api::IsAreaGreen(INT x, INT y, INT r) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH3(x, y, r);
	return LUA_RET_NUMBER("Game", "IsAreaGreen");
}

BOOL CSettlers4Api::IsAreaOwned(INT x, INT y, INT r, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH4(player, x, y, r);
	return LUA_RET_NUMBER("Game", "IsAreaOwned");
}

DWORD CSettlers4Api::GetNumberOfPlayers() {
	TRACE;
	CHECK_LUA_STATE;
	return LUA_RET_NUMBER("Game", "NumberOfPlayers");
}

S4_TRIBE_ENUM CSettlers4Api::GetPlayerTribe(DWORD player) {
	TRACE;
	if (!_IsLuaState()) return S4_TRIBE_ENUM::S4_TRIBE_NONE;
	PLAYER_GUARD_(S4_TRIBE_ENUM::S4_TRIBE_NONE);
	LUA_PUSH1(player);
	if (!CallLuaFunc("Game", "PlayerRace")) return S4_TRIBE_ENUM::S4_TRIBE_NONE;
	return (S4_TRIBE_ENUM)((DWORD)lua_getnumber(lua_getresult(1)));
}

BOOL CSettlers4Api::ResetFogging() {
	TRACE;
	CHECK_LUA_STATE;
	return LUA_RET_VOID("Game", "ResetFogging");
}

BOOL CSettlers4Api::SetAlliesDontRevealFog(BOOL enable) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH1(enable);
	return LUA_RET_VOID("Game", "SetAlliesDontRevealFog");
}

BOOL CSettlers4Api::SetFightingStrength(DWORD strength, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH2(player, strength);
	return LUA_RET_VOID("Game", "SetFightingStrength");
}

BOOL CSettlers4Api::ShowClock(DWORD seconds) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH1(seconds);
	return LUA_RET_VOID("Game", "ShowClock");
}

DWORD CSettlers4Api::Time() {
	TRACE;
	CHECK_LUA_STATE;
	return LUA_RET_NUMBER("Game", "Time");
}

DWORD CSettlers4Api::GoodsAddPileEx(S4_GOOD_ENUM good, DWORD amount, INT x, INT y) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH4(x,y,good,amount);
	return LUA_RET_NUMBER("Goods", "AddPileEx");
}

DWORD CSettlers4Api::GoodsAmount(S4_GOOD_ENUM good, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH2(player, good);
	return LUA_RET_NUMBER("Goods", "Amount");
}

DWORD CSettlers4Api::GoodsDelete(S4_GOOD_ENUM good, INT x, INT y, INT r) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH4(x,y,r, good);
	return LUA_RET_NUMBER("Goods", "Delete");
}

DWORD CSettlers4Api::GoodsGetAmountInArea(S4_GOOD_ENUM good, INT x, INT y, INT r, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH5(player, good, x, y, r);
	return LUA_RET_NUMBER("Goods", "GetAmountInArea");
}

DWORD CSettlers4Api::MagicCastSpell(S4_TRIBE_ENUM tribe, S4_SPELL_ENUM spell, INT x, INT y, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH5(player, tribe, spell, x, y);
	return LUA_RET_NUMBER("Magic", "CastSpell");
}

BOOL CSettlers4Api::MagicIncreaseMana(INT amount, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH2(player, abs(amount));
	return LUA_RET_VOID("Magic", amount < 0 ? "DecreaseMana" : "IncreaseMana");
}

DWORD CSettlers4Api::MapAddDecoObject(DWORD object, INT x, INT y) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH3(x,y,object);
	return LUA_RET_NUMBER("Map", "AddDecoObject");
}

BOOL CSettlers4Api::MapDeleteDecoObject(INT x, INT y, INT r) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH3(x, y, r);
	return LUA_RET_VOID("Map", "DeleteDecoObject");
}

DWORD CSettlers4Api::MapSize() {
	TRACE;
	CHECK_LUA_STATE;
	return LUA_RET_NUMBER("Map", "Height");
}

BOOL CSettlers4Api::MapPointIsOnScreen(INT x, INT y) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH2(x, y);
	return LUA_RET_NUMBER("Map", "PointIsOnScreen");
}

BOOL CSettlers4Api::MapSetScreenPos(INT x, INT y) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH2(x, y);
	return LUA_RET_NUMBER("Map", "SetScreenPos");
}

BOOL CSettlers4Api::SettlersAdd(S4_SETTLER_ENUM settler, INT amount, INT x, INT y, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH5(x, y, player, settler, amount);
	return LUA_RET_VOID("Settlers", "AddSettlers"); // todo: probably has multiple return values
}

BOOL CSettlers4Api::SettlersAddToFerry(DWORD ferry, S4_SETTLER_ENUM settler, INT amount) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH3(ferry, settler, amount);
	return LUA_RET_VOID("Settlers", "AddSettlersToFerry");
}

DWORD CSettlers4Api::SettlersAmount(S4_SETTLER_ENUM settler, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH2(player, settler);
	return LUA_RET_NUMBER("Settlers", "Amount");
}

DWORD CSettlers4Api::SettlersAmountInArea(S4_SETTLER_ENUM settler, INT x, INT y, INT r, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH5(player, settler, x, y, r);
	return LUA_RET_NUMBER("Settlers", "AmountInArea");
}

BOOL CSettlers4Api::SettlersIsSelected(S4_SETTLER_ENUM settler, INT amount) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH2(settler, amount);
	return LUA_RET_NUMBER("Settlers", "IsSelected");
}

BOOL CSettlers4Api::SettlersKillSelectableSettlers(S4_SETTLER_ENUM settler, INT x, INT y, INT r, BOOL animation, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH6(player, settler, x, y, r, animation);
	return LUA_RET_VOID("Settlers", "KillSelectableSettlers");
}

DWORD CSettlers4Api::SettlersProductionAmount(S4_SETTLER_ENUM settler) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH1(settler);
	return LUA_RET_NUMBER("Settlers", "ProductionAmount");
}

BOOL CSettlers4Api::SettlersSetHealthInArea(S4_SETTLER_ENUM settler, INT x, INT y, INT r, DWORD health, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH6(player, settler, x, y, r, health);
	return LUA_RET_VOID("Settlers", "SetHealthInArea");
}

#define STATISTICS_DEFINITION(funcname) \
	DWORD CSettlers4Api::Statistic##funcname(DWORD player) {\
		TRACE;\
		CHECK_LUA_STATE;\
		PLAYER_GUARD;\
		LUA_PUSH1(player);\
		return LUA_RET_NUMBER("Statistic", #funcname);\
	}

STATISTICS_DEFINITION(BuildingsCaptured)
STATISTICS_DEFINITION(GoodsProduced)
STATISTICS_DEFINITION(LandOwnedByPlayer)
STATISTICS_DEFINITION(ManaCollected)
STATISTICS_DEFINITION(MushroomFarmsDestroyed)
STATISTICS_DEFINITION(ServantsFreed)
STATISTICS_DEFINITION(SpellsCast)
STATISTICS_DEFINITION(UnitsDestroyed)

BOOL CSettlers4Api::ClearMarker() {
	TRACE;
	CHECK_LUA_STATE;
	return LUA_RET_VOID("Tutorial", "ClearMarker");
}

BOOL CSettlers4Api::DeleteWorldCursor() {
	TRACE;
	CHECK_LUA_STATE;
	return LUA_RET_VOID("Tutorial", "DeleteWorldCursor");
}

BOOL CSettlers4Api::PressButton(DWORD dialog, DWORD control) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH2(dialog, control);
	return LUA_RET_VOID("Tutorial", "PressButton");
}

BOOL CSettlers4Api::RevealWorldMap(BOOL enable) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH1(enable);
	return LUA_RET_VOID("Tutorial", "RWM");
}

BOOL CSettlers4Api::SelectNextBuilding(S4_BUILDING_ENUM building) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH1(building);
	return LUA_RET_VOID("Tutorial", "SelectNextBuilding");
}

BOOL CSettlers4Api::SetMarker(INT x, INT y) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH2(x,y);
	return LUA_RET_VOID("Tutorial", "SetMarker");
}

BOOL CSettlers4Api::SetWorldCursor(INT x, INT y) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH2(x, y);
	return LUA_RET_VOID("Tutorial", "SetWorldCursor");
}

BOOL CSettlers4Api::SetZoom(INT zoom) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH1(zoom);
	return LUA_RET_VOID("Tutorial", "SetZoom");
}

DWORD CSettlers4Api::VehiclesAdd(S4_VEHICLE_ENUM vehicle, DWORD direction, DWORD ammo, DWORD commands, INT x, INT y, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH7(x,y,player, vehicle, direction, ammo, commands);
	return LUA_RET_NUMBER("Vehicles", "AddVehicle");
}

BOOL CSettlers4Api::VehiclesAddWheelerToFerry(DWORD ferry, S4_VEHICLE_ENUM vehicle) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH2(ferry, vehicle);
	return LUA_RET_VOID("Vehicles", "AddWheelerToFerry");
}

DWORD CSettlers4Api::VehiclesAmount(S4_VEHICLE_ENUM vehicle, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH2(player, vehicle);
	return LUA_RET_NUMBER("Vehicles", "Amount");
}

DWORD CSettlers4Api::VehiclesAmountInArea(S4_VEHICLE_ENUM vehicle, INT x, INT y, INT r, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH5(player, vehicle, x, y, r);
	return LUA_RET_NUMBER("Vehicles", "AmountInArea");
}

DWORD CSettlers4Api::VehiclesGetFerryCargoInArea(INT x, INT y, INT r, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH4(player, x, y, r);
	return LUA_RET_NUMBER("Vehicles", "GetFerryCargoInArea"); // todo: probably has multiple return values
}

DWORD CSettlers4Api::VehiclesGetHealth(INT x, INT y) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH2(x, y);
	return LUA_RET_NUMBER("Vehicles", "GetHealth");
}

BOOL CSettlers4Api::VehiclesIsSelected(S4_VEHICLE_ENUM vehicle, INT amount) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH2(vehicle, amount);
	return LUA_RET_NUMBER("Vehicles", "IsSelected");
}

BOOL CSettlers4Api::VehiclesKill(S4_VEHICLE_ENUM vehicle, INT x, INT y, INT r, DWORD player) {
	TRACE;
	CHECK_LUA_STATE;
	PLAYER_GUARD;
	LUA_PUSH5(player, vehicle, x, y, r);
	return LUA_RET_VOID("Vehicles", "KillVehicles");
}

BOOL CSettlers4Api::SetGround(INT x, INT y, INT r, DWORD ground) {
	TRACE;
	CHECK_LUA_STATE;
	LUA_PUSH4(x, y, r, ground);
	return LUA_RET_VOID("dbg", "sg");
}

BOOL CSettlers4Api::ShowTextMessage(LPCSTR message, DWORD icon, DWORD reserved) {
	TRACE;
	BYTE(__fastcall * __ShowTextMessage)(LPCSTR message, DWORD icon, DWORD ign1, DWORD ign2, DWORD unk)
		= (decltype(__ShowTextMessage))(g_Patterns.ShowTextMessage.addr);
	if (!__ShowTextMessage) return FALSE;
	BYTE retval;
	//auto retval = __ShowTextMessage(message, icon, 0, 0, reserved);
	//__asm add esp, 12 // __fastcall does expect the function to do the cleanup... but it doesnt

	// we must make this a single asm block otherwise the optimizer will screw us
	__asm { 
		push reserved
		push 0
		push 0
		mov edx, icon
		mov ecx, message
		call __ShowTextMessage
		add esp, 12
		mov retval, al
	}
	return retval;
}

BOOL CSettlers4Api::SoundPlay(S4_SOUND_ENUM sound, LPVOID reserved, LPVOID reserved2) {
	TRACE;
	UNREFERENCED_PARAMETER(sound);
	UNREFERENCED_PARAMETER(reserved);
	UNREFERENCED_PARAMETER(reserved2);
	// todo: implement me
	return FALSE;
}
