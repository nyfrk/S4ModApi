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

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#include "Log.h"

extern "C" {

	void* __stdcall memget_s(void* dst, const void* src, size_t len) {
		#pragma comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__ ) // export undecorated
		#pragma comment(linker, "/EXPORT:" __FUNCDNAME__ ) // export stdcall decorated
		TRACE;
		DWORD read = 0;
		if (!ReadProcessMemory(GetCurrentProcess(), src, dst, len, &read) || read != len) {
			return NULL;
		}
		return dst;
	}

	void* __stdcall memset_s(void* dst, const void* src, size_t len) {
		#pragma comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__ ) // export undecorated
		#pragma comment(linker, "/EXPORT:" __FUNCDNAME__ ) // export stdcall decorated
		TRACE;
		DWORD writtn = 0;
		if (!WriteProcessMemory(GetCurrentProcess(), dst, src, len, &writtn) || writtn != len) {
			return NULL;
		}
		return dst;
	}

	DWORD __stdcall READ_AT(const void* src, int offset) {
		#pragma comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__ ) // export undecorated
		#pragma comment(linker, "/EXPORT:" __FUNCDNAME__ ) // export stdcall decorated
		TRACE;
		DWORD ret;
		if (src && ReadProcessMemory(GetCurrentProcess(), (LPCVOID)((DWORD)src + offset), &ret, sizeof(DWORD), NULL)) {
			return ret;
		}
		return 0;
	}

	BOOL __stdcall WRITE_AT(void* dst, DWORD val, int offset) {
		#pragma comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__ ) // export undecorated
		#pragma comment(linker, "/EXPORT:" __FUNCDNAME__ ) // export stdcall decorated
		TRACE;
		return (dst && WriteProcessMemory(GetCurrentProcess(), (LPVOID)((DWORD)dst + offset), &val, sizeof(DWORD), NULL));
	}

}