#pragma once

#include "windows.h"

extern HMODULE g_hModule;
HMODULE IncreaseModuleRefcount(LPCVOID target); // NULL on failure
BOOL DecreaseModuleRefcount(HMODULE module); // true if successfull
