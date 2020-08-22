#pragma once

#if _DEBUG

#include "S4ModApi.h"

HRESULT S4HCALL DebugFrameProc(LPDIRECTDRAWSURFACE7 lpSurface, INT32 iPillarboxWidth, LPVOID lpReserved);

#endif