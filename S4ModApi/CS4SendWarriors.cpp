#include "CSettlers4Api.h"
#include "patterns.h"
#include "globals.h"
#include "safemem.h"
#include "s4.h"

BOOL CSettlers4Api::SendWarriors(INT x, INT y, S4_MOVEMENT_ENUM mode, PWORD warriors, SIZE_T countOfWarriors, DWORD player) {
	TRACE;

	DWORD localPlayer = player ? player : S4::GetInstance().GetLocalPlayer();
	if (!localPlayer) return FALSE;

	DWORD pos = ((WORD)y) << 16 | ((WORD)x);

	static DWORD heapAlloc = 0;
	static DWORD fillEventArg = 0;
	static DWORD one;
	static DWORD fillEvent = 0;
	static DWORD sendEvent = 0;
	one = 1;
	if (!heapAlloc) {
		DWORD addr = g_Patterns.OnSettlerCommandHook + (g_isGE ? 88 : 99);
		DWORD off = READ_AT((LPCVOID)addr, 1);
		if (addr && off)
			heapAlloc = addr + off + 5;
		else
			return FALSE;
	}
	if (!g_isGE && !fillEvent) {
		DWORD addr = g_Patterns.OnSettlerCommandHook + 0xB4;
		DWORD off = READ_AT((LPCVOID)addr, 1);
		if (addr && off)
			fillEvent = addr + off + 5;
		else
			return FALSE;
	}
	if (!sendEvent) {
		DWORD addr = g_Patterns.OnSettlerCommandHook + (g_isGE ? 0xE9 : 0xC3);
		DWORD off = READ_AT((LPCVOID)addr, 1);
		if (addr && off)
			sendEvent = addr + off + 5;
		else
			return FALSE;
	}
	//if (!fillEventArg)
	//	fillEventArg = READ_AT((LPCVOID)(g_Patterns.OnSettlerCommandHook - (g_isGE ? 0x73 : 0x66))); // local player
	//if (!fillEventArg)
	//	fillEventArg = (DWORD)&one;
	//DWORD dwFillEventArg = *(DWORD*)fillEventArg;

	auto repetitions = (countOfWarriors+99u) / 100u;
	for (auto i = 0u; i < repetitions; i++) {
		auto lower = i * 100;
		auto count = min(countOfWarriors - lower, 100) * sizeof(WORD);
		void* mem = NULL;

		__asm {
			// Allocate the mem just like the game would do it. 
			// The game will free it for us later
			push count
			//mov eax, S4_Main
			//add eax, 0x94FBF7
			call heapAlloc
			add esp, 04 // cdecl!
			mov mem, eax
		}

		if (mem) {
			memcpy(mem, &warriors[lower], count);

#pragma pack(push, 1)
			union {
				struct EventStruct_t {
					/*00*/DWORD CEvn_Logic_vtbl; // 0x14 // vtable
					/*04*/DWORD movementCommandId; // 0x18 // 0x1396
					/*08*/DWORD position;  // 0x1C
					/*0C*/DWORD commandType; // 0x20
					/*10*/DWORD tick; // 0x24
					/*14*/DWORD null; // 0x28 // always 0 ?
					/*18*/DWORD settlersArray; // 0x2C
					/*1C*/WORD sizeofArray; // 0x30
					/*1E*/BYTE dl; // 0x32 // local player
				} eventStruct;
				BYTE eventStructBytes[32]; // event struct is at least 32 bytes
			} u1;
#pragma pack(pop)

			if (g_isGE) {
				// note for the GE we must populate the struct ourselfs as the function is inlined :(
				static const DWORD vtblPtr = READ_AT(g_Patterns.OnSettlerCommandHook, 0xC5);
				u1.eventStruct.CEvn_Logic_vtbl = *(DWORD*)(vtblPtr);
				u1.eventStruct.movementCommandId = 0x1396;
				u1.eventStruct.position = pos;
				u1.eventStruct.commandType = mode;
				DWORD stick = 0;
				static const DWORD tickPtr = READ_AT(g_Patterns.OnSettlerCommandHook, 0x87);
				if (tickPtr) {
					stick = *(DWORD*)(tickPtr);
					if (stick) {
						stick = *(DWORD*)(stick + 0x18);
						if (stick) {
							stick = *(DWORD*)(stick);
						}
					}
				}
				u1.eventStruct.tick = stick;
				u1.eventStruct.null = 0;
				u1.eventStruct.settlersArray = (DWORD)mem;
				u1.eventStruct.sizeofArray = (WORD)count;
				u1.eventStruct.dl = (BYTE)localPlayer;
				void* arg = &u1.eventStruct;
				static const DWORD* pthisptr = (DWORD*)READ_AT(g_Patterns.OnSettlerCommandHook, 0x7D);
				if (pthisptr && *pthisptr) {
					DWORD pthis = *pthisptr;
					__asm {
						// send the event just like the game would do it
						mov ecx, pthis
						push arg
						call sendEvent
					}
				}
			} else {
				// we could populate this ourselfs buf its easier to let
				// the game do it for us. The game will basically just
				// copy the arguments and insert the events tick number
				__asm {
					// fill the event struct just like the game would do it
					push count
					lea ecx, u1.eventStructBytes
					push mem
					push localPlayer
					push mode // command type
					push pos // target position
					push 0x1396 // movement command id
					call fillEvent

					// send the event just like the game would do it
					lea eax, u1.eventStructBytes
					push eax
					call sendEvent
				}
			}


		} // if (mem)
	} // for

	return TRUE;
}



