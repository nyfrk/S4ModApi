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

#include <Windows.h>
#include "S4ModApi.h"

#pragma pack(push, 1)
// Ui Elements
struct UiElement_t { // struct is 0x24 bytes 
	WORD x, y, w, h;
	WORD sprite; // [+8] (?)
	WORD id; // [+10]
	WORD _unk1[5]; // [+12] // todo: i probably fuckd up counting here
	WORD id2, id3; // [+20] id3 is always id2+1 (?). Maybe some kind of linked list refs.
	WORD _unk2[5]; // [+24]
};
struct ActiveIngameMenu_t {
	DWORD main;
	DWORD sub;
};
struct Selection_t { // struct is xx bytes
	WORD* BasePtr; // Array of settler IDs
	WORD* EndPtr;

	DWORD count() const { return EndPtr - BasePtr; } // number of settlers in the selection
};
struct Event_t {
	Event_t();
	Event_t(DWORD _4, DWORD _8, DWORD _C, DWORD param2, DWORD param1, DWORD eventId); // todo: better names
	operator bool() const { return eventId != 0; }
	LPCVOID vtbl;
	DWORD eventId;
	DWORD param[2];
	DWORD tick;
	BYTE flags;
	BYTE __pad1[3];
	LPCVOID settlers;
	WORD sizeofSettlers;
	BYTE player;
	BYTE __pad2;
};

//#define VFUNC { return 0; }
//#define VFUNCVOID { }

struct Settler_t { // struct is 92 bytes
	LPCVOID vtable; // [+0] // vtable, contains 32 virtual methods
	//virtual DWORD vfunc0() VFUNC; // returns a static like [S4_Main.exe+D645C4]. 
	//virtual DWORD vfunc1(DWORD unk) VFUNC;
	//virtual DWORD vfunc2(DWORD unk) VFUNC;
	//virtual DWORD vfunc3() VFUNC; // executes and [ecx+14],FFFFF9FF for settlers. // clears selection? 
	//virtual DWORD vfunc4() VFUNC;
	//virtual DWORD vfunc5() VFUNC;
	//virtual DWORD vfunc6(DWORD unk) VFUNC;
	//virtual DWORD vfunc7(DWORD unk0, DWORD unk1) VFUNC;
	//virtual DWORD vfunc8(DWORD unk) VFUNC;
	//virtual DWORD vfunc9() VFUNC;
	//virtual DWORD vfunc10() VFUNC; // movzx eax, byte ptr[ecx + 21] for settlers
	//virtual DWORD vfunc11() VFUNC; // returns 0 for settlers
	//virtual void vfunc12(DWORD unk0, DWORD unk1) VFUNCVOID; // does nothing for settlers
	//virtual DWORD vfunc13(DWORD unk) VFUNC;
	//virtual DWORD vfunc14() VFUNC;
	//virtual DWORD vfunc15() VFUNC; // returns 0x18 for some settlers and 0x0 for buildings
	//virtual void vfunc16(DWORD) VFUNCVOID; //  does nothing for settlers
	//virtual void vfunc17(DWORD, DWORD) VFUNCVOID; //  does nothing for settlers
	//virtual DWORD vfunc18(DWORD) VFUNC; //  does nothing and returns 0 for settlers
	//virtual void vfunc19() VFUNCVOID;
	//virtual DWORD vfunc20(DWORD) VFUNC; // probably called SetEvent
	//virtual DWORD vfunc21() VFUNC; //  does nothing and returns 0 for settlers
	//virtual DWORD vfunc22(DWORD) VFUNC; //  does nothing and returns 0 for settlers
	//virtual DWORD vfunc23(DWORD) VFUNC; //  does nothing and returns 0 for settlers
	//virtual DWORD vfunc24(DWORD) VFUNC; //  does nothing and returns 0 for settlers
	//virtual DWORD vfunc25() VFUNC;
	//virtual DWORD vfunc26() VFUNC;
	//virtual void vfunc27() VFUNCVOID; //  executes or [ecx+14],80000000 for settlers
	//virtual DWORD vfunc28(DWORD, DWORD) VFUNC;
	//virtual BYTE vfunc29() VFUNC; // does nothing and returns 0 for settlers
	//virtual DWORD vfunc30() VFUNC;
	//virtual DWORD vfunc31() VFUNC;
	//virtual DWORD vfunc32(DWORD) VFUNC; // todo: i fucked up counting somewhere... the vtable contains 32 methods

	DWORD id2;		// [+4]    index in the settler pool (?)
	WORD id;		// [+8] ie index in the settler pool
	enum ObjectType_e : BYTE {
		OBJECTTYPE_SETTLER = 1,
		OBJECTTYPE_SHIP = 2,
		OBJECTTYPE_LANDVEHICLE = 4,
		OBJECTTYPE_BUILDING = 8,
		OBJECTTYPE_GOOD = 16,
		OBJECTTYPE_PLANT = 32, // tree, wheat, sunflower plant, grasses etc
		OBJECTTYPE_UNKNOWN = 64,
		OBJECTTYPE_ANIMAL = 128, // bunny, deer, etc
	} objectType; // [+10]
	BYTE _unk2;  // [+11]
	WORD settlerType;// [+12]
	BYTE _unk3[6];   // [+14]
	enum BaseType_e : BYTE {
		BASETYPE_CIVILIAN = 0, // civilian building or object like wheat plant etc (wheatplant has settlerType == 209 and goodtype == 0)
		BASETYPE_SWORDMAN = 2,
		BASETYPE_BOWMAN,
		BASETYPE_RACESPECIAL,
		BASETYPE_LEADER,
		BASETYPE_PRIEST,
		BASETYPE_PARAMILITARY, // thief, pioneer etc
		BASETYPE_WARMACHINE,
		BASETYPE_TRADINGCART, // 
		BASETYPE_WARSHIP,
		BASETYPE_CIVILIAN_SHIP,
		BASETYPE_MILITARY_BUILDING, // (?)
		BASETYPE_DONKEY = 14, // 
		BASETYPE_OTHER = 64, // good or settler
	} baseType;// [+20]
	BYTE selection; // [+21] Bits (1<<2) and (1<<3) control the visibility of the selection marker and health bubble for this settler
	BYTE _unk4[10]; // [+22]
	BYTE tribe; // [+32] only the 4 least significant bits (0 == roman, 1 == viking 2 == maya, 3 == darktribe, 4 == troyan)
	BYTE health; // [+33]
	BYTE _unk5[30]; // [+34]
	BYTE goodType; // [+64] 
	BYTE _unk6[27]; // [+65]

	inline void clrSelectionVisibility() { selection &= 0b11111001; }
	inline void setSelectionVisibility() { selection |= 0b00000110; } // there can be max 100 settlers that have visible selection markers!
	inline BYTE getTribe() { return tribe & 0xF; } // 0 == roman, 1 == viking 2 == maya, 3 == darktribe, 4 == troyan
	inline bool isTribe() { return tribe & 10; } // return true if this object is a tribe object 
};
#pragma pack(pop)

struct S4 {
	friend struct Event_t;

	const INT32* PillarboxWidth;
	UiElement_t** HoveringUiElement; // if points to NULL then there is none
	HWND* Hwnd;
	LPVOID MenuScreenObj, CurrentMenuScreen;
	LPCVOID GameMenusWndProc; // this is the ingame menus proc
	LPVOID* WndProcChain; // 
		// [0] is the menus (including the main menu) 
		// [1] is chatbox 
		// [2] this is the menu on the left side (shows selections, buildings etc)
		// [3] is the group selection/magic/barracks/deco/smiths etc subsubmenu
		// [4] the menu left under the usual menu. This usually shows a summary of your goods. Is NULL if not present
		// [5] the camera. Is NULL if not present
		// [6] is the submenu (building submenu, settlers, goods, graph). Is NULL if settlers or a building is selected
		// [7] unknown
		// [8] is tutorial related. Probably an arrow handler? That one that points you to the UI elements that you have to click.
		// [9..10] unknown
		// [11] is probably the "you have won/lost" window proc
		// [12] is the timer in the top right corner (use f7 for example)
		// [13] maybe exists ? 
	ActiveIngameMenu_t *ActiveIngameMenu;
	Selection_t* Selection;
	Settler_t** SettlerPool;
	DWORD* SettlerPrototypes;
	
	DWORD GetLocalPlayer();
	DWORD GetCurrentTick();
	BOOL SendNetEvent(Event_t& event);
	BOOL SendLocalEvent(Event_t& event);
	inline BOOL S4::SendNetEvent(LPCVOID event) { return SendNetEvent(*(Event_t*)event); } // todo: use Event_t 
	inline DWORD GetNetEventVTbl() { return NetEventVTbl; }

	void Initialize();
	static S4& GetInstance();

private:
	DWORD* LocalPlayer;
	DWORD* Tick;
	DWORD NetEventVTbl;
	DWORD LocalEvent;

	void (__stdcall *__SendNetEvent)(Event_t* event) = nullptr; // this is actually a thiscall, but this pointer is ignored
	LPCVOID EventConstructor = nullptr;
	

	S4() = default;
	S4(const S4&) = delete;
	S4& operator=(S4 const&) = delete;
};

#define MAKE_RACE_INDEX(id) (id - S4_OBJECT_TRIBE_INDEX)
#define MAKE_BUILDING_INDEX(id) (id - S4_OBJECT_BUILDING_INDEX +1)
#define MAKE_GOOD_INDEX(id) (id - S4_OBJECT_GOOD_INDEX +1)
#define MAKE_SETTLER_INDEX(id) (id - S4_OBJECT_SETTLER_INDEX +1)
#define MAKE_VEHICLE_INDEX(id) (id - S4_OBJECT_VEHICLE_INDEX +1)
#define MAKE_PLANT_INDEX(id) (id - S4_OBJECT_PLANT_INDEX +1)
#define MAKE_ANIMAL_INDEX(id) (id - S4_OBJECT_ANIMAL_INDEX +1)
