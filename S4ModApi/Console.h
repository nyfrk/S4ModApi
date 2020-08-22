#pragma once

#if _DEBUG

#include <iostream>
#include <iomanip> // std::setfill, std::setw
#include "windows.h"

using std::cout;
using std::hex;
using std::dec;
using std::endl;

#define HEXNUM(a) "0x" << hex << std::setfill('0') << std::setw(8) << ((DWORD)(a))

void InitConsole();
void DestroyConsole();
HWND GetConsoleHwnd();

#endif