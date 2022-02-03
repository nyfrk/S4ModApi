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

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#include "CUpdate.h"
#include "Log.h"
#include <WinInet.h>
#include <sstream>
#include "module.h"
#include <fstream>
#include <iostream>
#include <locale> 
#include <codecvt>

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "version.lib")

static LPCSTR agent = "S4ModApi";

CUpdate& CUpdate::GetInstance() {
	TRACE
	static CUpdate inst;
	return inst;
}

static bool IsSkipUpdate() {
	TRACE
	WCHAR fn[MAX_PATH + 1];
	auto l = GetModuleFileNameW(g_hModule, fn, MAX_PATH);
	if (!l) return true;
	fn[l] = '\0';
	std::wstring str(fn);
	str += L"\\..\\NoUpdateForS4ModApi";
	auto attr = GetFileAttributesW(str.c_str());
	if (attr != INVALID_FILE_ATTRIBUTES) return true;
	str += L".txt";
	attr = GetFileAttributesW(str.c_str());
	return attr != INVALID_FILE_ATTRIBUTES;
}

CUpdate::EUpdateCheckStatus CUpdate::check() {
	TRACE
	if (m_hasChecked) {
		return  m_status;
	}

	if (IsSkipUpdate()) {
		LOG("skipping update");
		return  m_status;
	}

	const char* URL = "https://api.github.com/repos/nyfrk/S4ModApi/releases/latest";
	DWORD error, read;
	HINTERNET hInet, hConn;
	char data[255], urlbuf[INTERNET_MAX_URL_LENGTH];

	const char* defscheme = "http";
	URL_COMPONENTSA uc;
	ZeroMemory(&uc, sizeof(uc));
	uc.dwStructSize = sizeof(uc);
	BOOL crack = InternetCrackUrlA(URL, 0, 0, &uc);
	error = GetLastError();
	if (!crack && error == ERROR_INTERNET_UNRECOGNIZED_SCHEME && strlen(defscheme) + 3 + strlen(URL) < INTERNET_MAX_URL_LENGTH)	{
		// Prepend a protocol
		sprintf_s(urlbuf, "%s://%s", defscheme, URL);
		URL = urlbuf;
	} else if (!crack) {
		LOG("InternetCrackUrlA error " << dec << error);
		return m_status = EUpdateCheckStatus::UPDATE_CHECK_ERROR;
	}

	hInet = InternetOpenA(agent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInet) {
		error = GetLastError();
		LOG("InternetOpenA failed with error " << dec << error);
		return m_status = EUpdateCheckStatus::UPDATE_CHECK_ERROR;
	}

	hConn = InternetOpenUrlA(hInet, URL, NULL, 0, 0, 0);
	error = GetLastError();
	if (!hConn) {
		InternetCloseHandle(hInet);
		LOG("InternetOpenUrl failed with error " << dec << error);
		return m_status = EUpdateCheckStatus::UPDATE_CHECK_ERROR;
	}

	error = 0;
	std::stringstream ss;
	for (;;) {
		if (!InternetReadFile(hConn, data, sizeof(data) - 1, &read)) {
			error = GetLastError();
			break;
		}
		if (0 == read) break; // Done
		data[read] = '\0';
		ss.write(data, read);
	}

	if (m_verMayor == 0 && m_verMinor == 0) InitVersion();

	std::string str = ss.str();
	LOG("url response:" << endl << str);
	char tagname[64];
	sprintf_s(tagname, "\"tag_name\":\"v%d.%d\"", (DWORD)m_verMayor, (DWORD)m_verMinor);
	auto pos = str.find(tagname, 0);
	m_hasChecked = true;
	m_receivedTick = GetTickCount();
	if (pos == std::string::npos) {
		// there is an update
		m_status = UPDATE_CHECK_AVAILABLE;
		LOG("update found");
		const char DlTag[] = "\"browser_download_url\":\"";
		auto m = str.find(DlTag);
		if (m != std::string::npos) {
			m += _countof(DlTag)-1;
			auto e = str.find("\"", m);
			if (e != std::string::npos) {
				InstallUpdate(str.substr(m, e - m));
			}
		} else {
			LOG("download url for update not found");
		}
		
	} else {
		m_status = UPDATE_CHECK_UPTODATE;
		LOG("no update available");
	}

	InternetCloseHandle(hInet);
	InternetCloseHandle(hConn);
	return m_status;
}

DWORD CUpdate::getMillisSinceCheck() { // how many milliseconds elapsed since we polled for the last result
	TRACE
	if (!m_hasChecked) return 0;
	return GetTickCount() - m_receivedTick;
}

/*
 * This will load the version from the VERSIONINFO resource.
 */
void CUpdate::InitVersion() {
	TRACE
	// taken from https://stackoverflow.com/a/940743/1642059
	DWORD  verHandle = 0;
	UINT   size = 0;
	LPBYTE lpBuffer = NULL;
	char szVersionFile[MAX_PATH + 1] = { 0 };
	GetModuleFileName(g_hModule, szVersionFile, MAX_PATH);
	DWORD  verSize = GetFileVersionInfoSize(szVersionFile, &verHandle);

	if (verSize != NULL) {
		LPSTR verData = new char[verSize];
		if (GetFileVersionInfo(szVersionFile, verHandle, verSize, verData)) {
			if (VerQueryValue(verData, "\\", (VOID FAR * FAR*) & lpBuffer, &size)) {
				if (size) {
					VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
					if (verInfo->dwSignature == 0xfeef04bd) {
						m_verMayor = HIWORD(verInfo->dwFileVersionMS);
						m_verMinor = LOWORD(verInfo->dwFileVersionMS);
						LOG("GetVersion(): Version retrieved successfully: " << dec << m_verMayor << '.' << m_verMinor)
					}
				}
			}
		}
		delete[] verData;
	}
}

void CUpdate::InstallUpdate(const std::string& url) {
	TRACE
	DWORD error, read;
	HINTERNET hInet, hConn;
	char data[255];

	LOG("downloading " << url);

	URL_COMPONENTSA uc;
	ZeroMemory(&uc, sizeof(uc));
	uc.dwStructSize = sizeof(uc);
	BOOL crack = InternetCrackUrlA(url.c_str(), 0, 0, &uc);
	if (!crack) {
		error = GetLastError();
		LOG("InternetCrackUrlA error " << dec << error);
		return;
	}

	hInet = InternetOpenA(agent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	if (!hInet) {
		error = GetLastError();
		LOG("InternetOpenA failed with error " << dec << error);
		return;
	}

	hConn = InternetOpenUrlA(hInet, url.c_str(), NULL, 0, 0, 0);
	if (!hConn) {
		error = GetLastError();
		InternetCloseHandle(hInet);
		LOG("InternetOpenUrl failed with error " << dec << error);
		return;
	}

	error = 0;

	WCHAR lpTempPathBuffer[MAX_PATH], 
		szZipFileName[MAX_PATH], 
		szBatFileName[MAX_PATH], 
		szUnzipFileName[MAX_PATH], 
		szModuleFileName[MAX_PATH],
		szS4FileName[MAX_PATH];
	auto v = GetTempPathW(_countof(lpTempPathBuffer),lpTempPathBuffer);
	if (v > _countof(lpTempPathBuffer) || (v == 0)) {
		error = GetLastError();
		InternetCloseHandle(hInet);
		LOG("GetTempPathW failed with error code " << dec << error);
		return;
	}

	if (0 == GetTempFileNameW(lpTempPathBuffer, L"S4MA", 0, szZipFileName)) {
		error = GetLastError();
		InternetCloseHandle(hInet);
		LOG("GetTempFileNameW failed with error code " << dec << error);
		return;
	}
	DeleteFileW(szZipFileName);
	wcscat_s(szZipFileName, L".zip");

	std::ofstream sf;
	sf.open(szZipFileName,  std::ofstream::out | std::ofstream::binary);
	if (!sf) {
		error = GetLastError();
		InternetCloseHandle(hInet);
		LOG("ofstream::open failed with error code " << dec << error);
		return;
	}

	for (;;) {
		if (!InternetReadFile(hConn, data, sizeof(data), &read)) {
			error = GetLastError();
			return;
		}
		if (0 == read) break; // Done
		sf.write(data, read);
		if (!sf) {
			error = GetLastError();
			InternetCloseHandle(hInet);
			LOG("ofstream::write failed with error code " << dec << error);
			return;
		}
	}
	sf.close();
	InternetCloseHandle(hInet);
	InternetCloseHandle(hConn);

	if (0 == GetTempFileNameW(lpTempPathBuffer, L"S4MA", 0, szBatFileName)) {
		error = GetLastError();
		DeleteFileW(szZipFileName);
		LOG("GetTempFileNameW failed with error code " << dec << error);
		return;
	}
	DeleteFileW(szBatFileName);
	wcscat_s(szBatFileName, L".bat");

	if (0 == GetTempFileNameW(lpTempPathBuffer, L"S4MA", 0, szUnzipFileName)) {
		error = GetLastError();
		DeleteFileW(szZipFileName);
		DeleteFileW(szBatFileName);
		LOG("GetTempFileNameW failed with error code " << dec << error);
		return;
	}

	auto l = GetModuleFileNameW(g_hModule, szModuleFileName, _countof(szModuleFileName)-1);
	if (!l) {
		error = GetLastError();
		DeleteFileW(szZipFileName);
		DeleteFileW(szBatFileName);
		DeleteFileW(szUnzipFileName);
		LOG("GetModuleFileNameW failed with error code " << dec << error);
		return;
	}
	szModuleFileName[l] = '\0';

	l = GetModuleFileNameW(NULL, szS4FileName, _countof(szS4FileName) - 1);
	if (!l) {
		error = GetLastError();
		DeleteFileW(szZipFileName);
		DeleteFileW(szBatFileName);
		DeleteFileW(szUnzipFileName);
		LOG("GetModuleFileNameW failed with error code " << dec << error);
		return;
	}
	szS4FileName[l] = '\0';

	std::wofstream sb;
	sb.open(szBatFileName, std::wofstream::out);

	if (!sb) {
		error = GetLastError();
		DeleteFileW(szZipFileName);
		DeleteFileW(szBatFileName);
		DeleteFileW(szUnzipFileName);
		LOG("ofstream::open failed with error code " << dec << error);
		return;
	}

	// create a batch script to perform the copy operation since it will be write protected while 
	// a process has loaded the module

	auto unwide = [](LPCWSTR a) {
		using convert_type = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_type, wchar_t> converter;
		return converter.to_bytes(a);
	};

	LOG("creating update script with" << std::endl 
		<< "zip   :" << unwide(szZipFileName) << std::endl
		<< "unzip :" << unwide(szUnzipFileName) << std::endl
		<< "module:" << unwide(szModuleFileName) << std::endl
		<< "script:" << unwide(szBatFileName))

	sb
		<< L"@echo off" << std::endl
		<< std::endl
		<< L"echo Installing automatic update for S4ModApi.dll" << std::endl
		<< L"echo see https://github.com/nyfrk/S4ModApi" << std::endl
		<< L"echo." << std::endl
		<< L"echo please wait a few seconds while performing the update." << std::endl
		<< std::endl
		<< L"del \"" << szUnzipFileName << "\"" << std::endl
		<< L"setlocal" << std::endl
		<< L"cd /d %~dp0" << std::endl
		<< L"Call :UnZipFile \"" << szUnzipFileName << "\\\" \"" << szZipFileName << "\"" << std::endl
		<< L"exit /b" << std::endl
		<< std::endl
		<< L":UnZipFile <ExtractTo> <newzipfile>" << std::endl
		<< L"set vbs=\"%temp%\\_.vbs\"" << std::endl
		<< L"if exist %vbs% del /f /q %vbs%" << std::endl
		<< L">%vbs%  echo Set fso = CreateObject(\"Scripting.FileSystemObject\")" << std::endl
		<< L">>%vbs% echo If NOT fso.FolderExists(%1) Then" << std::endl
		<< L">>%vbs% echo fso.CreateFolder(%1)" << std::endl
		<< L">>%vbs% echo End If" << std::endl
		<< L">>%vbs% echo set objShell = CreateObject(\"Shell.Application\")" << std::endl
		<< L">>%vbs% echo set FilesInZip=objShell.NameSpace(%2).items" << std::endl
		<< L">>%vbs% echo objShell.NameSpace(%1).CopyHere(FilesInZip)" << std::endl
		<< L">>%vbs% echo Set fso = Nothing" << std::endl
		<< L">>%vbs% echo Set objShell = Nothing" << std::endl
		<< L"cscript //nologo %vbs%" << std::endl
		<< L"if exist %vbs% del /f /q %vbs%" << std::endl
		<< std::endl
		<< L"del \"" << szZipFileName << "\"" << std::endl
		<< std::endl
		<< L"timeout /t 2 /nobreak" << std::endl
		<< std::endl
		<< L"copy \"" << szUnzipFileName << "\\S4ModApi.dll\" \""<< szModuleFileName <<"\"" << std::endl
		<< std::endl
		<< L"@RD /S /Q \"" << szUnzipFileName << "\\\"" << std::endl
		<< L"start \"\" \"" << szS4FileName << "\"" << std::endl
		<< L"start /b \"\" cmd /c del \"%~f0\"&exit /b" << std::endl;
	sb.close();

	std::wstring cmd = L"cmd /C \"";
	cmd += szBatFileName;
	cmd += '\"';

	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(si);

	Sleep(3000);

	if (!CreateProcessW(NULL, (LPWSTR)cmd.c_str() , NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		error = GetLastError();
		DeleteFileW(szZipFileName);
		DeleteFileW(szBatFileName);
		DeleteFileW(szUnzipFileName);
		LOG("CreateProcess failed with error " << error);
		return;
	}
	// Windows will free them for us
	//CloseHandle(pi.hProcess);
	//CloseHandle(pi.hThread);

	LOG("terminating process now")
	// let the update script install the update
	TerminateProcess(GetCurrentProcess(), 0);
	ExitProcess(0);
}
