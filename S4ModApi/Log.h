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

#pragma once

#ifdef  _DEBUG

#include "Console.h"
#include <fstream>
#include <string>
#include <mutex>
#include <iomanip>
extern std::ofstream g_LogStream;

std::string GetLogstreamFilename();
void InitLogstream();
void DestroyLogstream();

extern volatile int isLogTraceInit;

#define LOG(a) {\
	if (isLogTraceInit) {\
		g_LogStream_Mutex.lock();\
		cout << LOG_PROLOG_SHORT << a << endl;\
		g_LogStream << LOG_PROLOG_LONG << RAIILogTrace::Indentation() << "| " << a << endl;\
		g_LogStream.flush();\
		g_LogStream_Mutex.unlock();\
	}\
}

#define TRACE_(...) RAIILogTrace __raii_logtrace__(__FILE__,__LINE__,__FUNCTION__,__VA_ARGS__);
#define TRACE TRACE_()

#define LOG_PROLOG(a) "[t:" << dec << std::setw(6) << std::setfill(' ') << GetCurrentThreadId() << ','\
	<< RAIILogTrace::Timestamp(a) << "] "
#define LOG_PROLOG_LONG LOG_PROLOG(1)
#define LOG_PROLOG_SHORT LOG_PROLOG(0)

extern std::recursive_mutex g_LogStream_Mutex;

struct RAIILogTrace {
	static std::string RAIILogTrace::Indentation();
	static std::string RAIILogTrace::Timestamp(int extended);
	RAIILogTrace(std::string file, unsigned line, std::string func);
	RAIILogTrace(std::string file, unsigned line, std::string func, LPCVOID a);
	~RAIILogTrace();
	std::string func;
	std::string lastfunc;
	bool nodestructor = false;
};

#else //  _DEBUG
#define LOG(x) ;
#define TRACE ;
#define TRACE_(x) ;
#endif //  _DEBUG
