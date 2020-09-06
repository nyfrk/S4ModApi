#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "S4ModApi.h"
#pragma comment(lib, "S4ModApi")

static S4API s4; // the interface to the Settlers 4 Mod API
static LPCVOID splashHandle; // the handle to the splash image

static void CleanUp() {
    if (NULL != splashHandle) {
        s4->DestroyCustomUiElement(splashHandle);
        splashHandle = NULL;
    }
    if (NULL != s4) {
        s4->Release();
        s4 = NULL;
    }
};

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved ) {    
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
        s4 = S4ApiCreate(); // get an interface to the mod api
        if (NULL == s4) break;

        WCHAR imgFn[MAX_PATH]; // the filename of the splash image
        INT filenameLen = GetModuleFileNameW(hModule, imgFn, _countof(imgFn))
            - 4; // subtract 4 to remove the .asi file ending
        if (filenameLen <= 0) break;

        // append \splash.bmp to the filename of the module
        wcscpy_s(&imgFn[filenameLen], _countof(imgFn) - filenameLen, L"\\splash.bmp");

        S4CustomUiElement cuie = { 0 };
        cuie.size = sizeof(cuie);
        cuie.szImg = imgFn;
        cuie.x = 50;
        cuie.y = 50;
        cuie.screen = S4_SCREEN_MAINMENU;
        cuie.actionHandler = [](LPCVOID lpUiElement, S4_CUSTOM_UI_ENUM newstate) {
            if (newstate & S4_CUSTOM_UI_SELECTED) {
                CleanUp();
            }
            return (HRESULT)0;
        };
 
        splashHandle = s4->CreateCustomUiElement(&cuie);
        break;
    } 
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        CleanUp();
        break;
    }
    return TRUE;
}

