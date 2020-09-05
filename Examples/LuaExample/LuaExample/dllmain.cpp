#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

#include "resource.h"
#include "S4ModApi.h"
#pragma comment(lib, "S4ModApi")

static S4API s4; // the interface to the Settlers 4 Mod API
static LPCVOID rwmButton, smButton; // the handle to the buttons
static bool rwmClicked, smClicked; // when a button is clicked, we turn set the variable true
static S4HOOK luaOpenHook, tickHook; // store the hook handle
char tblName[] = "Ext"; // the table name we will add the lua function to
char showMessageFuncname[] = "ShowMessage"; // the name we use as the table index for our function

static void CleanUp() {
    if (NULL != rwmButton) {
        s4->DestroyCustomUiElement(rwmButton);
        rwmButton = NULL;
    }
    if (NULL != smButton) {
        s4->DestroyCustomUiElement(smButton);
        smButton = NULL;
    }
    if (NULL != luaOpenHook) {
        s4->RemoveListener(luaOpenHook);
        luaOpenHook = NULL;
    }
    if (NULL != tickHook) {
        s4->RemoveListener(tickHook);
        tickHook = NULL;
    }
    if (NULL != s4) {
        s4->Release();
        s4 = NULL;
    }
};

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
        s4 = S4ApiCreate(); // get an interface to the mod api
        if (NULL == s4) break;

        // Create the Ext.ShowMessage lua function and append it to the games
        // lua VM uppon initialization
        luaOpenHook = s4->AddLuaOpenListener([]() {
            // Create the Ext table (we only do this once)
            lua_pushobject(lua_createtable());
            lua_setglobal(tblName);

            // Add the ShowMessage function to the Ext table
            lua_pushobject(lua_getglobal(tblName));
            lua_pushstring(showMessageFuncname);
            lua_pushcfunction([] {
                auto str = luaL_check_string(1); // first argument is mandatory string
                if (str) {
                    auto icon = luaL_opt_int(2, 9); // the second argument is an optional int that defaults to 9 (exclamation mark)
                    s4->ShowTextMessage(str, icon, 0);
                    lua_pushnumber(strlen(str));  // we push the string length as result
                }
                else { // something went wrong and we got a null pointer
                    lua_pushnil();
                }
                return;
            });
            lua_settable(); // insert ShowMessage element to Ext table
            return (HRESULT)0;
        });

        // Create some buttons so we can test the lua functions
        S4CustomUiElement cuie = { 0 };
        cuie.size = sizeof(cuie);
        cuie.mod = hModule;
        cuie.szImg = MAKEINTRESOURCEW(IDB_RWM);
        cuie.szImgHover = MAKEINTRESOURCEW(IDB_RWM_HOVER);
        cuie.szImgSelectedHover = MAKEINTRESOURCEW(IDB_RWM_DOWN);
        cuie.x = 300;
        cuie.y = 5;
        cuie.screen = S4_SCREEN_INGAME;
        cuie.flags = S4_CUSTOMUIFLAGS_TRANSPARENT | S4_CUSTOMUIFLAGS_FROMRES_IMG | S4_CUSTOMUIFLAGS_FROMRES_IMGHOVER |  S4_CUSTOMUIFLAGS_FROMRES_IMGSELECTED;
        cuie.actionHandler = [](LPCVOID lpUiElement, S4_CUSTOM_UI_ENUM newstate) {
            if (newstate & S4_CUSTOM_UI_ENUM::S4_CUSTOM_UI_SELECTED) 
                rwmClicked = true; // process the click on the next tick
            return (HRESULT)0;
        };
        rwmButton = s4->CreateCustomUiElement(&cuie);
        cuie.szImg = MAKEINTRESOURCEW(IDB_SM);
        cuie.szImgHover = MAKEINTRESOURCEW(IDB_SM_HOVER);
        cuie.szImgSelectedHover = MAKEINTRESOURCEW(IDB_SM_DOWN);
        cuie.y = 50;
        cuie.actionHandler = [](LPCVOID lpUiElement, S4_CUSTOM_UI_ENUM newstate) {
            if (newstate & S4_CUSTOM_UI_ENUM::S4_CUSTOM_UI_SELECTED)
                smClicked = true; // process the click on the next tick
            return (HRESULT)0;
        };
        smButton = s4->CreateCustomUiElement(&cuie);

        // only perform lua actions in the tick procedure
        tickHook = s4->AddTickListener([](DWORD tick, BOOL a, BOOL b) {
            if (rwmClicked) {
                rwmClicked = false;
                static bool revealed = false;
                revealed = !revealed;
                s4->RevealWorldMap(revealed);
                s4->ShowTextMessage(revealed ? "Revealing the world map" : "Hiding the world map", 7, 0);
            }
            if (smClicked) {
                smClicked = false;
                char str[] = "This message was created by the LuaExample plugin through calling Ext.ShowMessage from lua.";
                auto icon = s4->GetLocalPlayer() - 1;

                // we now call the lua function that we created before as Ext.ShowMessage
                lua_pushstring(str); // push the first argument
                lua_pushnumber(icon);  // push the second argument

                // read the function from the table
                lua_pushobject(lua_getglobal(tblName));	
                lua_pushstring(showMessageFuncname);
                auto func = lua_gettable();

                if (!lua_callfunction(func)) {
                    // execution went successfull, get the result
                    auto res = (int)lua_getnumber(lua_getresult(1));

                    // we create yet another message that presents the result
                    char out[100];
                    sprintf_s(out, "Ext.ShowMessage(\"%.15s[...]\",%i) returned %d (expected %d)", str, icon, res, (int)(_countof(str)-1));
                    s4->ShowTextMessage(out, 9, 0);
                }
            }
            return (HRESULT)0;
        });

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

