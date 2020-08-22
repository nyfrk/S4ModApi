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
