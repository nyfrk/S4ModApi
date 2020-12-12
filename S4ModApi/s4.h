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
#include "safemem.h"

#pragma pack(push, 1)

// Settlers 4 Entities
// fields marked with capital S are serialized, a lower case s means that they are serialized but are specially encoded 
struct CPersistance {
	inline LPVOID* GetVtable() { return *(LPVOID**)this; }
	S4_ROLE_ENUM GetRoleClass();

	virtual LPVOID vfunc0() = 0; // returns some static value. Has probably something to do with serialization or rtti
	virtual VOID serialize(DWORD *) = 0;
};
class ISettlerRole : public CPersistance {
	/* + 4 S */ CHAR unk_04;
	/* + 5 S */ BYTE unk_05;
	/* + 6 S */ BYTE walkspeed; // in ticks per field
	/* + 7 S */ BYTE unk_07; 
	/* + 8 S */ WORD unk_08; 
	/* + 10 S */ BYTE unk_0A; 
	/* + 11 S */ BYTE unk_0B; 
	/* + 12 S */ BYTE unk_0C; 
	/* + 13 _ */ BYTE pad_0D; 
	/* + 14 S */ WORD unk_0E; 
	/* + 16 S */ WORD unk_10; 
	/* + 18 S */ WORD unk_12; 
	/* + 20 S */ WORD unk_14; 
	/* + 22 _ */ WORD pad_16; 
	/* + 24 S */ DWORD unk_18; 
	/* + 28 S */ DWORD unk_1C; 
	/* + 32 S */ WORD unk_20; 
	/* + 34 S */ WORD unk_22; 
	/* + 36 _ */ WORD unk_24; 
	/* + 38 _ */ WORD unk_26; 
	/* + 40 _ */ WORD unk_28; 
	/* + 42 _ */ WORD unk_2A; 

	virtual ISettlerRole* vfunc2(BYTE) = 0;
	virtual DWORD vfunc3() = 0; // todo: type me
	virtual VOID walk(LPVOID) = 0; // this may also check the landscape to adjust the walk speed, it will also register for logic update
	virtual DWORD vfunc5() = 0; // todo: type me
	virtual VOID vfunc6(LPVOID) = 0; // may call register logic update
	virtual DWORD vfunc7() = 0; // todo: type me
	virtual VOID vfunc8() = 0;
	virtual DWORD vfunc9() = 0; // todo: type me
	virtual DWORD vfunc10() = 0; // todo: type me
	virtual DWORD vfunc11() = 0; // todo: type me
	virtual VOID vfunc12(WORD) = 0; // setter for unk_20
	virtual VOID vfunc13(WORD) = 0; // setter for unk_22
	virtual DWORD vfunc14() = 0; // todo: type me
	virtual DWORD vfunc15(INT) = 0; // this accesses a map
	virtual DWORD vfunc16(INT*) = 0;
	virtual DWORD vfunc17(DWORD) = 0; // may return the only param
	virtual DWORD vfunc18() = 0; // todo: type me
	virtual BYTE vfunc19() = 0; // may return 0
	virtual VOID vfunc20(INT, WORD) = 0; // setter for unk_20 and unk_14
	virtual DWORD vfunc21(INT) = 0; // getter for unk_20 and unk_14
	virtual DWORD vfunc22() = 0; // may return 0
	virtual DWORD vfunc23() = 0; // may return 0
	virtual DWORD vfunc24() = 0; // may return 0
	virtual DWORD vfunc25() = 0; // may return 0
	virtual DWORD vfunc26() = 0; // may return 0
	virtual DWORD vfunc27() = 0; // may return 1
	virtual DWORD vfunc28() = 0; // may return 0
	virtual BYTE vfunc29() = 0;  // may return 0
	virtual DWORD vfunc30(INT, INT) = 0; // accesses the map
	virtual BYTE vfunc31(LPVOID) = 0;
	virtual VOID vfunc32(INT,INT **, WORD, WORD, DWORD) = 0;
};
class IBuildingRole : public CPersistance {
	// todo
};
class IPileRole : public CPersistance {
	// todo
};
// todo: role subclassing
struct IEntity : public CPersistance {
	/* + 4 S */ DWORD id; // entity id (index of self in the entity pool)
	/* + 8 S */ WORD id2;
	/* +10 S */ 
	enum EntityType_e : BYTE {
		OBJECTTYPE_SETTLER = 1,
		OBJECTTYPE_SHIP = 2,
		OBJECTTYPE_LANDVEHICLE = 4,
		OBJECTTYPE_BUILDING = 8,
		OBJECTTYPE_GOOD = 16,
		OBJECTTYPE_PLANT = 32, // tree, wheat, sunflower plant, grasses etc
		OBJECTTYPE_UNKNOWN = 64,
		OBJECTTYPE_ANIMAL = 128,// bunny, deer, etc bytes;
	} entityType;
	/* +11 _ */ BYTE unk0; // unused alignment byte (?)
	/* +12 S */ WORD objectId; // this is the settler/building id etc
	/* +14 _ */ BYTE unk1[6]; // unused bytes (?), none of them are serialized
	/* +20 S */ 	
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
	} baseType;
	/* +21 S */ BYTE selectionFlags;
	/* +22 S */ BYTE unk2;
	/* +23 S */ BYTE unk3;
	/* +24 S */ WORD x;
	/* +26 S */ WORD y;
	/* +28 _ */ DWORD unk5;
	/* +32 S */ struct {
		BYTE player : 4; // only the 4 most significant bits are the player, todo: confirm it
		BYTE tribe : 4; // only the 4 least significant bits are the tribe
#pragma warning(suppress: 4201) // supress unnamed structures
	};
	/* +33 S */ BYTE health;
	/* +34 _ */ BYTE pad0;
	/* +35 _ */ BYTE pad1;

	virtual IEntity* vfunc2(LPVOID) = 0; // probably some kind of destroy/dispose method
	virtual DWORD clearSelection() = 0;
	virtual VOID vfunc4() = 0; // something with map access
	virtual LPVOID vfunc5() = 0;
	virtual DWORD vfunc6(INT) = 0;
	virtual VOID vfunc7(DWORD, DWORD) = 0;
	virtual VOID vfunc8(DWORD) = 0;
	virtual VOID vfunc9() = 0;
	virtual DWORD vfunc10() = 0; // simple getter for buildings
	virtual DWORD vfunc11() = 0; // returns always 0 for buildings
	virtual VOID vfunc12() = 0; // does nothing for buildings
	virtual VOID vfunc13(INT) = 0;
	virtual VOID vfunc14() = 0;
	virtual DWORD vfunc15() = 0;  // returns always 0 for buildings
	virtual DWORD vfunc16() = 0;  // returns always 0 for buildings
	virtual VOID vfunc17(INT,INT) = 0;
	virtual DWORD vfunc18(INT) = 0;
	virtual VOID vfunc19() = 0;
	virtual VOID vfunc20(DWORD) = 0;
	virtual DWORD vfunc21() = 0;  // returns always 0 for buildings
	virtual DWORD vfunc22() = 0;  // returns always 0 for buildings
	virtual DWORD vfunc23() = 0;  // returns always 0 for buildings
	virtual DWORD vfunc24() = 0;  // returns always 0 for buildings

	S4_ENTITY_ENUM GetClass();
	inline void clrSelectionVisibility() { selectionFlags &= 0b11111001; }
	inline void setSelectionVisibility() { selectionFlags |= 0b00000110; } // there can be max 100 settlers that have visible selection markers!
	//inline BYTE getTribe() { return tribe & 0xF; } // 0 == roman, 1 == viking 2 == maya, 3 == darktribe, 4 == troyan
	//inline bool isTribe() { return tribe & 10; } // return true if this object is a tribe object 
};
struct IAnimatedEntity : public IEntity {
	/* +36 S */ BYTE unk6;
	/* +37 S */ BYTE unk7;
	/* +38 S */ WORD unk8;
	/* +40 S */ WORD unk9;
	/* +42 S */ WORD unk10;
	/* +44 S */ DWORD unk11;
	/* +48 S */ DWORD unk12;
	/* +52 s */ INT unk13;
	/* +56 s */ INT unk14;

	virtual VOID vfunc25() = 0;
	virtual VOID vfunc26() = 0;
	virtual VOID vfunc27(DWORD) = 0;
};
struct IMovingEntity : public IAnimatedEntity {
	/* +60 S */ DWORD unk15;
	/* +64 S */ CHAR unk16;
	/* +65 S */ BYTE unk17;
	/* +66 S */ BYTE unk18;
	/* +67 _ */ BYTE pad2;
	/* +68 _ */ WORD unk19;
	/* +70 _ */ WORD unk20;
	/* +72 S */ DWORD unk21;
	/* +76 s */ DWORD unk22;
	/* +80 _ */ LPVOID unk23;
	/* +84 _ */ DWORD unk24;
	virtual VOID vfunc28(LPVOID, WORD) = 0;
	virtual BYTE vfunc29() = 0;
};
struct CVehicle : public IMovingEntity {
	/* +88 _ */ LPVOID unk25;
	/* +92 S */ BYTE unk26;
	/* +93 S */ BYTE unk27;
	/* +94 S */ BYTE unk28;
	/* +95 S */ BYTE unk29;
	/* +96 S */ BYTE unk30;
	/* +97 S */ BYTE unk31;
	/* +98 S */ BYTE unk32;
	/* +99 S */ BYTE unk33;
	/* +100 S */ BYTE unk34;
	/* +101 S */ BYTE unk35;
	/* +102 S */ WORD unk36;
	/* +104 S */ DWORD unk37;
	/* +108 S */ BYTE unk38;
	/* +109 S */ BYTE unk39;
	/* +110 S */ BYTE unk40;
	/* +111 S */ BYTE unk41;
	/* +112 S */ WORD unk42;
	/* +114 S */ WORD unk43;
	/* +116 S */ WORD unk44;
	/* +118 S */ WORD unk45;
	/* +120 S */ WORD unk46;
	/* +122 _ */ BYTE unk47[6];
	/* +128 s */ INT32 unk48;
	/* +132 s */ INT32 unk49;
	/* +136 _ */ DWORD unk50;
	/* +140 _ */ DWORD unk51;
	/* +144 _ */ DWORD unk52;

	virtual VOID vfunc30() = 0;
	virtual VOID vfunc31() = 0;
	virtual VOID vfunc32() = 0;
	virtual VOID vfunc33() = 0;
	virtual VOID vfunc34() = 0;
	virtual DWORD vfunc35() = 0; // returns unk4 from +24
	virtual VOID vfunc36() = 0;
	virtual VOID vfunc37() = 0;
	virtual VOID vfunc38() = 0;
	virtual VOID vfunc39(INT) = 0;
	virtual VOID vfunc40() = 0;
	virtual VOID vfunc41(DWORD) = 0;
	virtual VOID vfunc42(DWORD) = 0;
	virtual VOID vfunc43() = 0; // sets bit 0x20 at selectionFlags +21 
	virtual VOID vfunc44() = 0; // clears bit 0x20 at selectionFlags +21 
	virtual VOID vfunc45() = 0;
	virtual VOID vfunc46() = 0;
	virtual VOID vfunc47() = 0;
	virtual VOID vfunc48() = 0;
	virtual VOID vfunc49(DWORD) = 0;
	virtual VOID vfunc50(DWORD) = 0; 
	virtual BYTE vfunc51() = 0; // is a bool that returns true if unk33 at +99 is non-zero
	virtual DWORD vfunc52() = 0; // getter for byte at +99
	virtual VOID vfunc53() = 0; // decrements byte at +99 if non-zero
	virtual VOID vfunc54(DWORD) = 0; 
};
struct CAnimal : public IMovingEntity {
	/* +88 S */ WORD unk25;
	/* +90 _ */ BYTE unk26[14];
	/* +104 S */ BYTE unk27;
	/* +105 S */ BYTE unk28;
	/* +106 S */ BYTE unk29;
	/* +107 S */ BYTE unk30;
	/* +108 S */ BYTE unk31;
	/* +109 S */ BYTE unk32;
	/* +110 _ */ WORD pad3;
	/* +112 S */ DWORD unk33;
	/* +116 _ */ DWORD unk34;
	/* +120 S */ DWORD unk35;

	virtual VOID vfunc30() = 0;
	virtual DWORD vfunc31() = 0; // todo:
	virtual VOID vfunc32(CHAR) = 0; // this is probably the default state machine for animals
};
struct CSettler : public IMovingEntity {
	/* +88 _ */ ISettlerRole* role; // the settler role object

	virtual DWORD onUpdate() = 0; // this will dispatch the call to the onUdate of the role object
};
struct CWheeler : public CVehicle {
	/* +148 S */ DWORD unk53;
	/* +152 S */ DWORD unk54;
	/* +156 S */ DWORD unk55;

	virtual VOID vfunc55() = 0;
	virtual VOID vfunc56(INT) = 0;
};
struct CShip : public CVehicle {
	/* +148 S */ DWORD unk53;
};
struct CCart : public CWheeler {
	/* +160 s */ INT32 unk56;
	/* +164 s */ INT32 unk57;
	/* +168 _ */ DWORD unk58;
	/* +172 s */ INT unk59;
	/* +176 s */ INT unk60;
	/* +180 _ */ DWORD unk61;
	/* +184 S */ BYTE unk62;
	/* +185 S */ BYTE unk63;
	/* +186 S */ BYTE unk64;
	/* +187 S */ BYTE unk65;
	/* +188 S */ CHAR unk66;
	/* +189 S */ CHAR unk67;
	/* +190 S */ BYTE unk68;
	/* +191 S */ BYTE unk69;
	/* +192 _ */ DWORD unk70;
	/* +196 S */ DWORD unk71;
	/* +200 s */ DWORD unk72[18]; // probably a byte array or some object
	/* +272 S */ CHAR unk73;
	/* +273 S */ CHAR unk74;
	/* +274 S */ CHAR unk75;
	/* +275 _ */ BYTE unk76; // probably pad
	/* +276 S */ DWORD unk77;
	/* +280 S */ DWORD unk78;
	/* +284 S */ DWORD unk79;
	/* +288 S */ DWORD unk80;
	/* +292 S */ BYTE unk81;
	/* +293 S */ CHAR unk82;
	/* +294 S */ WORD pad4;

	virtual INT vfunc57() = 0; // todo: verify whether this gets added to the CWheeler vtable
};
struct CWarriorBehaviour {
	virtual VOID warriorfunc0(INT, LPVOID, DWORD) = 0;
	virtual DWORD warriorfunc1() = 0;
	virtual DWORD warriorfunc2() = 0; // this accesses the map
	virtual VOID warriorfunc3(LPVOID, INT) = 0; // used to register for logic updates. Maybe starts a state machine?
	virtual VOID warriorfunc4() = 0;
};
struct CCatapult : public CWheeler, public CWarriorBehaviour {
	/* +160 _ */ DWORD unk56[6];
	/* +184 S */ CHAR unk57;
	/* +185 _ */ BYTE pad5[3];
	/* +188 S */ DWORD unk58;
	/* +192 S */ DWORD unk59;

	virtual DWORD vfunc57() = 0; // always returns 4. todo: verify whether this gets added to the CWheeler vtable
};
struct CWarShip : public CShip, public CWarriorBehaviour {
	/* +152 _ */ DWORD unk54;
	/* +156 _ */ DWORD unk55;
	/* +160 _ */ DWORD unk56;
	/* +164 S */ DWORD unk57;
	/* +168 S */ DWORD unk58;

	virtual DWORD vfunc55() = 0; // always returns 4. todo: verify whether this gets added to the CWheeler vtable
};
struct CFerryShip : public CShip {
	/* +152 _ */ DWORD unk54;
	/* +156 s */ DWORD unk55;
	/* +160 s */ DWORD unk56;
	/* +164 s */ DWORD unk57;
	/* +168 s */ DWORD unk58;
	/* +172 s */ DWORD unk59;
	/* +176 s */ DWORD unk60;
	/* +180 s */ DWORD unk61;
	/* +184 s */ DWORD unk62;
	/* +188 s */ DWORD unk63;
};
struct CTransportShip : public CShip {
	/* +152 S */ DWORD unk54[31];
	/* +276 S */ BYTE unk55;
	/* +277 S */ BYTE pad56[3];
};
struct CMayaCatapult : public CCatapult {/* todo: fill struct */};
struct CRomanCatapult : public CCatapult {/* todo: fill struct */ };
struct CTrojanCatapult : public CCatapult {/* todo: fill struct */ };
struct CVikingCatapult : public CCatapult {/* todo: fill struct */ };
struct CMayaWarShip : public CWarShip {/* todo: fill struct */ };
struct CRomanWarShip : public CWarShip {/* todo: fill struct */ };
struct CTrojanWarShip : public CWarShip {/* todo: fill struct */ };
struct CVikingWarShip : public CWarShip {/* todo: fill struct */ };
struct CLandAnimal : public CAnimal {
	/* +124 S */ DWORD unk_7c;
	/* +128 S */ DWORD unk_80;
	/* +132 S */ DWORD unk_84;
	/* +136 S */ DWORD unk_88;
	/* +140 S */ DWORD unk_8c;
	/* +144 S */ DWORD unk_90;
	/* +148 S */ DWORD unk_94;
	/* +152 S */ DWORD unk_98;
	/* +156 S */ DWORD unk_9c;
};
struct CBuilding : public IAnimatedEntity{
	/* +60 _ */ DWORD unk_3c;
	/* +64 S */ BYTE unk_40;
	/* +65 S */ BYTE pad_41;
	/* +66 S */ WORD unk_42;
	/* +68 S */ DWORD unk_44;
	/* +72 S */ DWORD unk_48;
	/* +76 S */ DWORD unk_4c;
	/* +80 S */ IBuildingRole* role;
	/* +84 s */ DWORD unk_54;
	/* +88 S */ DWORD unk_58;

	virtual VOID vfunc28() = 0;
	virtual VOID vfunc29(DWORD) = 0;
	virtual VOID vfunc30(DWORD, DWORD**) = 0;
	virtual VOID vfunc31(DWORD) = 0;
};
struct CPile : public IAnimatedEntity {
	/* +60 _ */ DWORD unk_3c;
	/* +64 S */ S4_GOOD_ENUM goodType;
	/* +65 S */ BYTE amount;
	/* +66 S */ BYTE unk_42;
	/* +67 S */ BYTE unk_43;
	/* +68 S */ BYTE unk_44;
	/* +69 S */ BYTE unk_45;
	/* +70 S */ BYTE unk_46;
	/* +71 _ */ BYTE pad_47;
	/* +72 S */ WORD unk_48;
	/* +74 S */ WORD unk_4a;
	/* +76 S */ CHAR unk_4c;
	/* +77 _ */ BYTE pad_4d;
	/* +78 S */ WORD unk_4e;
	/* +80 S */ IPileRole* role;
	/* +84 S */ LPVOID unk_54;

	virtual VOID vfunc28(DWORD) = 0;
};
struct IDecoObject : public IAnimatedEntity {
	/* +60 _ */ DWORD unk_3c;
	/* +64 S */ DWORD unk_40;

	virtual DWORD vfunc28(CHAR) = 0;
	virtual BYTE vfunc29() = 0;
};
struct IFlyingEntity : public IAnimatedEntity {
	/* +60 _ */ DWORD unk_3c;
	/* +64 S */ DWORD unk_40;
	/* +68 S */ DWORD unk_44;
	/* +72 S */ WORD unk_48;
	/* +74 S */ WORD unk_4a;
	/* +76 S */ WORD unk_4c;
	/* +78 S */ CHAR unk_4e;
	/* +78 _ */ BYTE pad_4f;
	/* +80 s */ LPVOID unk_50;
	/* +84 S */ INT32 unk_54;

	virtual VOID vfunc28(DWORD) = 0;
	virtual VOID vfunc29(DWORD) = 0;
	virtual VOID vfunc30() = 0;
};
struct CManakopter : public IFlyingEntity {/* todo: fill struct */};
struct CDecoObject : public IDecoObject {
	/* +68 S */ CHAR unk_44;
	/* +69 S */ CHAR unk_45;
	/* +70 S */ BYTE unk_46;
	/* +71 _ */ BYTE pad_47;
	/* +72 S */ WORD unk_48;
	/* +74 _ */ WORD pad_4a;
};
struct CHive : public IDecoObject {/* todo: fill struct */ };
struct CMushroom : public IDecoObject {/* todo: fill struct */ };
struct CPlant : public IDecoObject {/* todo: fill struct */ };
struct CShadowHerb : public IDecoObject {/* todo: fill struct */ };
struct CStone : public IDecoObject {
	virtual VOID vfunc30() = 0;
};
struct CTree : public IDecoObject {
	/* +68 S */ CHAR unk_44;
	/* +69 S */ BYTE unk_45;
	/* +70 S */ BYTE unk_46;
	/* +71 _ */ BYTE pad_47;
	/* +72 S */ DWORD unk_48;
};

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

struct WorldField {
	union {
		struct {
			BYTE terrainHeight;
			BYTE terrainId;
			BYTE terrainAttributes;
			BYTE gameplayAttributes;
		} bytes;
		DWORD dword;
	};

	/// <summary>
	/// This flag is set to true if there is a founding stone on this field. This is probably used
	/// for pathing calculations of settlers and pioneers.
	/// </summary>
	inline bool IsFoundingStone() const			{ return 0 != (bytes.gameplayAttributes & 0b10000000); }
	/// <summary>
	/// This is probably a camera related performance optimisation flag. It will be on at position 
	/// where the camera is very often. I am not sure what exactly it is used for or when the flag
	/// is turned on.
	/// </summary>
	inline bool IsUnknownCamRelatedBit() const	{ return 0 != (bytes.gameplayAttributes & 0b01000000); }

	inline BYTE GetFogOfWarLevel() const		{ return	  bytes.gameplayAttributes & 0b00111111; }
	/// <summary>
	/// the field connects dark land to non-dark land. This is probably used by the dark gardeners 
	/// pathfinding and/or the shader for the dark land borders. If this flag is set the dark land 
	/// flag is never set.
	/// </summary>
	inline bool IsDarkBorder() const			{ return 0 != (bytes.terrainAttributes & 0b10000000); }
	/// <summary>
	/// Checks wether the ground is dark land
	/// </summary>
	inline bool IsDarkLand() const				{ return 0 != (bytes.terrainAttributes & 0b01000000); }
	/// <summary>
	/// Retrieve the pond flag. The pond flag removes waves if the terrain type is one of the deep 
	/// water levels (WATER2 .. WATER8). Note that the pond flag may even be set if there is no water.
	/// </summary>
	inline bool IsPondBrush() const				{ return 0 != (bytes.terrainAttributes & 0b00100000); }

	inline BYTE GetSunLevel() const				{ return bytes.terrainAttributes & 0b00011111; }

	inline S4_GROUND_ENUM GetTerrainType() const{ return (S4_GROUND_ENUM)bytes.terrainId; }

	inline BYTE GetTerrainHeight() const		{ return bytes.terrainHeight; }
};

struct EcoSector {
	// sizeof(*this) == 20
	BYTE owner; // owner (player id) is only at the 4 least significant bits. The 4 most significant bits are unknown
	BYTE unk0[3];
	DWORD dwUnk[4];

	inline BYTE GetOwningPlayer() { return owner & 0xF; }
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
	IEntity** SettlerPool; // todo: rename to EntityPool
	DWORD* SettlerPrototypes;

	DWORD* MapSize;
	WorldField** LandscapeMap; // map position to WorldField
	WORD** EntityMap; // map position to entity id
	S4_RESOURCE_ENUM** ResourceMap; // map position to resource enum
	WORD** EcoSectorMap; // ids for lookup in the chunk pool. If the id is <10, then this is the base/starting eco sector for a player.
	EcoSector* EcoSectorPool;
	
	DWORD GetLocalPlayer();
	DWORD GetCurrentTick();
	BOOL SendNetEvent(Event_t& event);
	BOOL SendLocalEvent(Event_t& event);
	inline BOOL SendNetEvent(LPCVOID event) { return SendNetEvent(*(Event_t*)event); } // todo: use Event_t 
	inline DWORD GetNetEventVTbl() { return NetEventVTbl; }
	inline void free(void* p) { if (__free)__free(p); }
	inline void* realloc(void* p, size_t s) { return __realloc ? __realloc(p,s) : NULL; }
	inline void* GetLuaState() { return (void*)READ_AT(lua_state); }

	inline DWORD GetMapSize();
	WorldField* GetLandscapeAt(WORD x, WORD y);
	IEntity* GetEntityAt(WORD x, WORD y);
	WORD GetEntityIdAt(WORD x, WORD y);
	S4_RESOURCE_ENUM GetResourceAt(WORD x, WORD y);
	BOOL SetResourceAt(WORD x, WORD y, S4_RESOURCE_ENUM res);
	EcoSector* GetEcoSectorAt(WORD x, WORD y);
	inline DWORD GetOwnerAt(WORD x, WORD y);

	void Initialize();
	static S4& GetInstance();

private:
	DWORD* LocalPlayer;
	DWORD* Tick;
	DWORD NetEventVTbl;
	DWORD LocalEvent;

	void (__stdcall *__SendNetEvent)(Event_t* event) = nullptr; // this is actually a thiscall, but this pointer is ignored
	void(__cdecl* __free)(void* ) = nullptr;
	void*(__cdecl* __realloc)(void*, size_t) = nullptr;
	LPCVOID EventConstructor = nullptr;
	LPCVOID lua_state = nullptr;

	S4() = default;
	S4(const S4&) = delete;
	S4& operator=(S4 const&) = delete;
};

