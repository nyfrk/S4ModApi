///////////////////////////////////////////////////////////////////////////////
// MIT License
//
// Copyright (c) 2020 nyfrk <nyfrk@gmx.net>
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
//
///////////////////////////////////////////////////////////////////////////////
// Quick and dirty library for external hacks. No additional dependencies needed.
///////////////////////////////////////////////////////////////////////////////
// 
//
#ifndef HLIB_H
#define HLIB_H

#include "windows.h"
#include <string>
#include <vector>

//#define HLIB_INTERNAL

namespace hlib {

#ifndef HLIB_INTERNAL
	typedef void* HMEMORYMODULE;

	/**
	 * Adjust token priviliges such that this process is allowed to debug.
	 */
	void SetDebugPrivileges(void);

	/**
	 * Get a process handle. This will request the following rights:
	 * PROCESS_SUSPEND_RESUME, PROCESS_VM_OPERATION, PROCESS_VM_READ,
	 * PROCESS_VM_WRITE, PROCESS_QUERY_INFORMATION, PROCESS_CREATE_THREAD,
	 * PROCESS_TERMINATE, SYNCHRONIZE
	 *
	 * @param dwId The ID of the process.
	 * @return HANDLE of the process. Call CloseHandle() for it when done.
	 */
	HANDLE GetProcessHandleById(DWORD dwId);

	/**
	 * Get a process handle. This will request the following rights:
	 * PROCESS_SUSPEND_RESUME, PROCESS_VM_OPERATION, PROCESS_VM_READ,
	 * PROCESS_VM_WRITE, PROCESS_QUERY_INFORMATION, PROCESS_CREATE_THREAD,
	 * PROCESS_TERMINATE, SYNCHRONIZE
	 *
	 * @param comp The name of the process. Eg "GTA5.exe".
	 * @param hMod An optional pointer that is to receive the base address of the game.
	 * @return HANDLE of the process. Call CloseHandle() for it when done.
	 */
	HANDLE GetProcessHandleByName(const char* comp, HMODULE* hMod = NULL);

	/**
	 * Get a process handle. This will request the following rights:
	 * PROCESS_SUSPEND_RESUME, PROCESS_VM_OPERATION, PROCESS_VM_READ,
	 * PROCESS_VM_WRITE, PROCESS_QUERY_INFORMATION, PROCESS_CREATE_THREAD,
	 * PROCESS_TERMINATE, SYNCHRONIZE
	 *
	 * @param comp The name of the processes window. Eg "Grand Theft Auto V".
	 * @param hMod An optional pointer that is to receive the base address of the game.
	 * @return HANDLE of the process. Call CloseHandle() for it when done.
	 */
	HANDLE GetProcessHandleByWindowName(const char* comp, HMODULE* hMod = NULL);

	/**
	 * Find the HMODULE of a DLL in a remote process.
	 *
	 * @param hProcess The handle of the process.
	 * @param dllname The name of the DLL. Eg. "kernel32". This is passed to LoadLibraryA.
	 * @return The HMODULE (base address) of the DLL in the remote process. Or NULL if the
	 *         DLL cannot be found.
	 */
	HMODULE SearchDllInProcess(HANDLE, const char*);

	/**
	 * Inject a DLL into a remote process.
	 *
	 * @param hProcess The handle of the process.
	 * @param dllname The name of the DLL. Eg. "kernel32". This is passed to LoadLibraryA.
	 * @param hModule A pointer to a HMODULE to receive the HMODULE of the injected DLL.
	 * @return if successfull true, otherwise false.
	 */
	bool InjectDLL(HANDLE hProcess, const char* dllname, HMODULE* hModule);

	/**
	 * Inject a DLL into a remote process using manual memory mapping. (Load a DLL from
	 * memory)
	 *
	 * @param hProcess The handle of the process.
	 * @param data A pointer to the DLL in memory.
	 * @param size The size of the DLL in bytes.
	 * @param hMod A pointer to a HMEMORYMODULE to receive the HMEMORYMODULE of the injected DLL.
	 *             Note that since windows is not aware of this DLL many functions that expect a
	 *             HMODULE do not work.
	 * @return if successfull true, otherwise false.
	 */
	bool InjectDLL(HANDLE hProcess, const void* data, UINT64 size, HMEMORYMODULE* hMod);

	/**
	 * Call a function of a DLL in a remote process.
	 *
	 * @param hProcess The handle of the process.
	 * @param dllname The name of the DLL. Eg. "kernel32".
	 * @param func The name of the function to call. Eg. "GetModuleHandleA"
	 * @param params A structure that is copied to the target processes virtual memory.
	 *               The pointer of this memory is passed as argument to the target function.
	 * @param szParams How many bytes of params to copy to the target process. If it is 0 the params argument
	 *               will be pushed directly onto the stack.
	 * @return The return value of the executed function is returned or 0 is an error occured.
	 *
	 * Note: To speed up performance make sure the DLL is loaded by this process. Otherwise the
	 *       DLL will be loaded and unloaded after the function has been called.
	 */
	UINT64 CallProcessDLL(HANDLE hProcess, const char* dllname, const char* func, const void* params, int szParams);

	/**
	 * Call a function of a DLL in a remote process.
	 *
	 * @param hProcess The handle of the process.
	 * @param hMod The HMODULE of the DLL in the target process (ie the base address).
	 * @param dllname The name of the DLL. Eg. "kernel32".
	 * @param func The name of the function to call. Eg. "GetModuleHandleA"
	 * @param params A structure that is copied to the target processes virtual memory.
	 *               The pointer of this memory is passed as argument to the target function.
	 * @param szParams How many bytes of params to copy to the target process. If it is 0 the params argument
	 *               will be pushed directly onto the stack.
	 * @return The return value of the executed function is returned or 0 is an error occured.
	 *
	 * Note: To speed up performance make sure the DLL is loaded by this process. Otherwise the
	 *       DLL will be loaded and unloaded after the function has been called.
	 */
	UINT64 CallProcessDLL(HANDLE hProcess, HMODULE hMod, const char* dllname, const char* func, const void* params, int szParams);

	/**
	 * Call a function of a DLL in a remote process.
	 *
	 * @param hProcess The handle of the process.
	 * @param hMod The HMODULE of the DLL in the target process (ie the base address).
	 * @param myMod The HMODULE of the DLL in the current process (ie the base address). Eg GetModuleHandle("kernel32").
	 * @param func The name of the function to call. Eg. "GetModuleHandleA"
	 * @param params A structure that is copied to the target processes virtual memory.
	 *               The pointer of this memory is passed as argument to the target function.
	 * @param szParams How many bytes of params to copy to the target process. If it is 0 the params argument
	 *               will be pushed directly onto the stack.
	 * @return The return value of the executed function is returned or 0 is an error occured.
	 *
	 * Note: To speed up performance make sure the DLL is loaded by this process. Otherwise the
	 *       DLL will be loaded and unloaded after the function has been called.
	 */
	UINT64 CallProcessDLL(HANDLE hProcess, HMODULE hMod, HMODULE myMod, const char* func, const void* params, int szParams);

#endif

	class StringPattern {
	public:
		StringPattern(const std::string pattern);
		StringPattern(const StringPattern& obj);
		const char* getMask() const;
		const unsigned char* getPattern() const;
		unsigned int len() const;
	private:
		std::string m_mask; // x for match, ? for ignore
		std::vector<unsigned char> m_pattern;
	};

	/**
	 * Find a pattern in process memory. The address of the first match will be returned.
	 *
	 * @param startAddr The first address to start searching
	 * @param pattern The pattern. Eg. "12 34 ? 1F C3".
	 * @param endAddr Do not search at addresses greater or equal to the endAddr. (endAddr is excluded)
	 */
	extern "C" UINT32 __stdcall FindPattern(UINT32 startAddr, const char* pattern, UINT32 endAddr = -1);

	/**
	 * Find a pattern in process memory. The address of the first match will be returned.
	 *
	 * @param hProcess The handle of the process.
	 * @param startAddr The first address to start searching
	 * @param pattern The pattern. Eg. StringPattern("12 34 ? 1F C3").
	 * @param endAddr Do not search at addresses greater or equal to the endAddr. (endAddr is excluded)
	 */
	UINT32 __stdcall FindPattern(HANDLE hProcess, UINT32 startAddr, const StringPattern& pattern, UINT32 endAddr = -1);

	/**
	 * Find a pattern in process memory. The address of the first match will be returned.
	 *
	 * @param hProcess The handle of the process.
	 * @param startAddr The first address to start searching
	 * @param pattern The pattern. Eg. "\x12\x34\x00\x1F\xC3")
	 * @param mask The mask. Eg. "xx?xx".
	 * @param len The length of the pattern in bytes.
	 * @param endAddr Do not search at addresses greater or equal to the endAddr. (endAddr is excluded)
	 */
	UINT32 __stdcall FindPattern(HANDLE hProcess, UINT32 startAddr, const unsigned char* pattern, const char* mask, unsigned int len, UINT32 endAddr = -1);

#ifndef HLIB_INTERNAL
	/**
	 * Undocumented Windows functions that allow to suspend and resume processes
	 * and all their threads. Make sure the debug priviliges are set by calling
	 * SetDebugPrivileges(). Make sure the HANDLE has the PROCESS_SUSPEND_RESUME
	 * Right.
	 * Also make sure ntdll.dll is loaded.
	 *
	 * @param ProcessHandle The handle of the process.
	 */
	typedef LONG(NTAPI* NtSuspendProcessFunc)(IN HANDLE ProcessHandle);
	typedef LONG(NTAPI* NtResumeProcessFunc)(IN HANDLE ProcessHandle);
	extern NtSuspendProcessFunc NtSuspendProcess;
	extern NtResumeProcessFunc NtResumeProcess;
#endif



	///////////////////////////////////////////////////////////////////////////////
	// Quick and dirty byte patching class that keeps track of the patched address.
	// You can implement a custom patch by inheriting from AbstractPatch.
	// Or include the template to create easy static patches
	///////////////////////////////////////////////////////////////////////////////
	class AbstractPatch {
	public:
		AbstractPatch();
		AbstractPatch(UINT64 addr, size_t len);
		AbstractPatch(UINT64 addr, size_t len, const void* orig);
		AbstractPatch(const AbstractPatch&) = delete;
		AbstractPatch& operator=(const AbstractPatch&) = delete;
		AbstractPatch(AbstractPatch&&);
		AbstractPatch& operator=(AbstractPatch&&);
		~AbstractPatch();

#ifndef HLIB_INTERNAL
		bool patch(HANDLE hProcess);
		bool unpatch(HANDLE hProcess);
#endif
		bool patch();
		bool unpatch();

		// Call this to read the memory and check if the patch is applied. Returns 
		// false if the state is broken (neither applied nor the expected state)
#ifndef HLIB_INTERNAL
		bool update(HANDLE hProcess);
#endif
		bool update();

		bool isPatched() const;

		UINT64 getAddress() const;
		virtual bool setAddress(UINT64 addr); // change address if patch is not applied yet

	protected:
		virtual bool applyPatch(HANDLE hProcess) = 0;
		virtual bool cmpPatch(const void* mem) = 0;

		UINT64 m_addr;
		bool m_isStrict;
		bool m_isPatched;
		void* m_orig;
		size_t m_len;
	};

	class Patch : public AbstractPatch {
	public:
		struct BYTE5 { const BYTE buf[5]; };
		Patch();
		Patch(UINT64 address, const void* patch, size_t len);
		Patch(UINT64 address, const void* patch, const void* expectedOrig, size_t len);
		Patch(UINT64 address, DWORD patch); // patch 4 bytes
		Patch(UINT64 address, DWORD patch, DWORD expectedOrig);
		Patch(UINT64 address, BYTE patch); // patch 1 bytes
		Patch(UINT64 address, BYTE patch, BYTE expected); // patch 1 bytes
		Patch(UINT64 address, BYTE bPatch, DWORD dwPatch, size_t nops = 0); // patch 5 bytes and some nops (0x90) after these 5 bytes
		Patch(UINT64 address, BYTE bPatch, DWORD dwPatch, const BYTE5* expected, size_t nops = 0);

		~Patch();

		Patch(Patch&&);
		Patch& operator=(Patch&&);

	protected:
		virtual bool applyPatch(HANDLE hProcess);
		virtual bool cmpPatch(const void* mem);
		void* m_patch;
	};
	class JmpPatch : public Patch {
	public:
		JmpPatch();
		JmpPatch(UINT64 address, DWORD jumpTargetAddr, size_t nops = 0);
		JmpPatch(UINT64 address, DWORD jumpTargetAddr, const BYTE5* expectedOrig, size_t nops = 0);
		virtual bool setAddress(UINT64 addr); // change address if patch is not applied yet
		bool setDestination(UINT64 dest); // change destination if patch is not applied yet
	protected:
		JmpPatch(BYTE opcode, UINT64 address, DWORD jumpTargetAddr, size_t nops);
		JmpPatch(BYTE opcode, UINT64 address, DWORD jumpTargetAddr, const BYTE5* expectedOrig, size_t nops);
	};
	class CallPatch : public JmpPatch {
	public:
		CallPatch();
		CallPatch(UINT64 address, DWORD jumpTargetAddr, size_t nops = 0);
		CallPatch(UINT64 address, DWORD jumpTargetAddr, const BYTE5* expectedOrig, size_t nops = 0);
	};
	class NopPatch : public AbstractPatch {
	public:
		NopPatch();
		NopPatch(UINT64 address, size_t len = 1);
		NopPatch(UINT64 address, const void* expected, size_t len);
	protected:
		virtual bool applyPatch(HANDLE hProcess);
		virtual bool cmpPatch(const void* mem);
	};

}

#endif
