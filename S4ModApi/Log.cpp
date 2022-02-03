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

#ifdef _DEBUG

#include "Log.h"
#include <sstream>

std::ofstream g_LogStream;
std::recursive_mutex g_LogStream_Mutex;
volatile int isLogTraceInit = false;
static __declspec(thread) int depth = 0;
static __declspec(thread) std::string g_lastfunc;

std::string GetLogstreamFilename() {
	char fname[MAX_PATH + 1];
	auto len = GetModuleFileNameA(NULL, fname, MAX_PATH);
	fname[len] = '\0';
	char* logfname = fname;
	for (int i = len; i >= 0; --i) {
		if (fname[i] == '\\' || fname[i] == '/') {
			fname[++i] = '\0';
			break;
		}
	}
	return std::string(logfname) + "S4ModApi.log";
}

void DestroyLogstream() {
	std::lock_guard<decltype(g_LogStream_Mutex)> lock(g_LogStream_Mutex);
	isLogTraceInit = false;
	g_LogStream.close(); 
}

void InitLogstream() {
	std::lock_guard<decltype(g_LogStream_Mutex)> lock(g_LogStream_Mutex);
	g_LogStream.open(GetLogstreamFilename(), std::ios_base::out);
	g_LogStream << "This is a S4ModApi.log file. It has been produced by S4ModApi.dll." << endl
		<< "See https://github.com/nyfrk/S4Hooks for more information on this project." << endl
		<< "You can safely delete this log file. If the log creation annoys you, just switch" << endl 
		<< "to a release build (you are using a debug build)" << endl << endl;
	isLogTraceInit = true;
}

std::string RAIILogTrace::Timestamp(int extended) {
	SYSTEMTIME time;
	GetSystemTime(&time);
	std::stringstream ss;
	ss << dec;
	if (extended) {
		ss <<
			std::setfill('0') << std::setw(4) << time.wYear << '-' <<
			std::setfill('0') << std::setw(2) << time.wMonth << '-' <<
			std::setfill('0') << std::setw(2) << time.wDay << ' ' <<
			std::setfill('0') << std::setw(2) << time.wHour << ':' <<
			std::setfill('0') << std::setw(2) << time.wMinute << ':' <<
			std::setfill('0') << std::setw(2) << time.wSecond << "#" <<
			std::setfill('0') << std::setw(4) << time.wMilliseconds;
	}
	else {
		DWORD t = ((DWORD)time.wMilliseconds)
			+ (1000u * (DWORD)time.wSecond) 
			+ (1000u * 60u * (DWORD)time.wMinute);
		t %= 1000000;
		ss << std::setfill(' ') << std::setw(6) << t;
	}
	return ss.str();
}

std::string RAIILogTrace::Indentation() {
	std::stringstream ss;
	for (int i = 0; i < depth; i++) {
		ss << "  ";
	}
	return ss.str();
}

RAIILogTrace::RAIILogTrace(std::string file, unsigned line, std::string func, LPCVOID a) {
	if (!isLogTraceInit) return;
	std::lock_guard<decltype(g_LogStream_Mutex)> lock(g_LogStream_Mutex);
	if (!isLogTraceInit) return;
	g_LogStream << LOG_PROLOG_LONG << Indentation();
	if (g_lastfunc == func) {
		g_LogStream << "code at " << file << ":" << dec << line << "    // in " << func << std::endl;
		nodestructor = true;
	}
	else {
		g_LogStream << func << "("<< HEXNUM(a) <<") {    // at " << file << ":" << dec << line << std::endl;
		++depth;
		lastfunc = g_lastfunc;
		g_lastfunc = func;
		nodestructor = false;
	}
	g_LogStream.flush();
}

RAIILogTrace::RAIILogTrace(std::string file, unsigned line, std::string func) : func(func) {
	if (!isLogTraceInit) return;
	std::lock_guard<decltype(g_LogStream_Mutex)> lock(g_LogStream_Mutex);
	if (!isLogTraceInit) return;
	g_LogStream << LOG_PROLOG_LONG << Indentation();
	if (g_lastfunc == func) {
		g_LogStream << "code at " << file << ":" << dec << line << "    // in " << func << std::endl;
		nodestructor = true;
	}
	else {
		g_LogStream << func << " {    // at " << file << ":" << dec << line << std::endl;
		++depth;
		lastfunc = g_lastfunc;
		g_lastfunc = func;
		nodestructor = false;
	}
	g_LogStream.flush();
}

RAIILogTrace::~RAIILogTrace() {
	if (!isLogTraceInit) return;
	std::lock_guard<decltype(g_LogStream_Mutex)> lock(g_LogStream_Mutex);
	if (!isLogTraceInit) return;
	g_lastfunc = lastfunc;
	if (!nodestructor) {
		--depth;
		g_LogStream << LOG_PROLOG_LONG << Indentation() << "} // " << func << std::endl;
		g_LogStream.flush();
	}
}

#endif