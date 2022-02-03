///////////////////////////////////////////////////////////////////////////////
// MIT License
//
// Copyright (c) 2022 nyfrk <nyfrk@gmx.net> and contributors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "windef.h"

extern "C" {

	/**
	 * Read memory from source (safe read)
	 **/
	void* __stdcall memget_s(void* dst, const void* src, size_t len);

	/**
	 * Write memory at destination (safe write)
	 **/
	void* __stdcall memset_s(void* dst, const void* src, size_t len);

	/**
	 * Read a DWORD from memory or return 0 on failure. (Safe read)
	 **/
	DWORD __stdcall READ_AT(const void* src, int offset = 0);

	/**
	 * Write a DWORD to memory or return 0 on failure. (Safe write)
	 **/
	BOOL __stdcall WRITE_AT(void* dst, DWORD val, int offset = 0);

}