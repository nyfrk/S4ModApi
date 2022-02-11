#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "S4ModApi.h"
#pragma comment(lib, "S4ModApi")

static S4API s4; // the interface to the Settlers 4 Mod API

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved ) {    
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
        s4 = S4ApiCreate(); // get an interface to the mod api
        if (NULL != s4) {
            s4->SetMaxSelection(1000);
        }
        break;
    } 
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        // cleanup
        if (NULL != s4) {
            s4->SetMaxSelection(100);
            s4->Release();
            s4 = NULL;
        }
        break;
    }
    return TRUE;
}

