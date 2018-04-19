#pragma once

#include <iostream>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#ifndef DEBUG 
#define DEBUG
#endif

#define PH_LOG_LEVEL_FATAL 0
#define PH_LOG_LEVEL_ERROR 1
#define PH_LOG_LEVEL_WARN  2
#define PH_LOG_LEVEL_INFO  3

#define PH_LOG_LEVEL_FATAL_COLOR  4
#define PH_LOG_LEVEL_ERROR_COLOR 12
#define PH_LOG_LEVEL_WARN_COLOR  14
#define PH_LOG_LEVEL_INFO_COLOR  10

#define PH_LEN(x) (sizeof(x) / sizeof(x)[0])

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

template <typename T>
bool IsInBounds(const T& value, const T& low, const T& high) {
	return !(value < low) && !(high < value);
}

#ifdef _WIN32
static void SetConsoleColor(int colorCode) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorCode);
}
#else
static void SetConsoleColor(int colorCode) {
}
#endif

namespace ph {

	struct None { };

	template <typename First, typename Second>
	struct Pair {
		First first;
		Second second;
	};

	template <typename List>
	struct LogData {
		List list;
	};

	template <typename Begin, typename Value>
	LogData<Pair<Begin, const Value &>> operator<<(LogData<Begin> begin, const Value &value) {
		return { { begin.list,value } };
	}

	template <typename Begin, size_t n>
	LogData<Pair<Begin, const char*>>
		operator <<(LogData<Begin> begin, const char(&value)[n]) {
		return { { begin.list, value } };
	}

	inline void PrintList(std::ostream &os, None) { }

	template <typename Begin, typename Last>
	void PrintList(std::ostream &os, const Pair<Begin, Last> &data) {
		PrintList(os, data.first);
		os << data.second;
	}

	template <typename List>
	void LogMessage(const char *file, int line, const LogData<List> &data, int level = -1) {
		switch (level) {
		case PH_LOG_LEVEL_FATAL:
			std::cout << "[FATAL]:   " << file << " (" << line << "): ";
			break;
		case PH_LOG_LEVEL_ERROR:
			std::cout << "[ERROR]:   " << file << " (" << line << "): ";
			break;
		case PH_LOG_LEVEL_WARN:
			std::cout << "[WARNING]: " << file << " (" << line << "): ";
			break;
		case PH_LOG_LEVEL_INFO:
			std::cout << "[INFO]:    " << file << " (" << line << "): ";
			break;
		default:
			std::cout << file << " (" << line << "): ";
			break;
		}
		PrintList(std::cout, data.list);
		std::cout << "\n";
	}

	template <typename List>
	void LogMessage(const LogData<List> &data) {
		PrintList(std::cout, data.list);
		std::cout << "\n";
	}
}

void GLCheckError();
bool GLLogCall(const char* function, const char* file, int line);

#ifdef DEBUG
#define GLCall(x) GLCheckError();\
		x; \
		if (!GLLogCall(#x, __FILE__, __LINE__)) __debugbreak();
#else
#define GLCall(x) x
#endif

#ifndef PHOENIX_LOG_LEVEL
#define PH_LOG_LEVEL PH_LOG_LEVEL_INFO
#endif

#if PH_LOG_LEVEL >= PH_LOG_LEVEL_FATAL
#define PH_FATAL(x) \
	SetConsoleColor(13); \
	ph::LogMessage(__FILENAME__, __LINE__, LogData<None>() << x, PH_LOG_LEVEL_FATAL); \
	SetConsoleColor(15);
#else
#define PHOENIX_FATAL(x)
#endif

#if PH_LOG_LEVEL >= PH_LOG_LEVEL_ERROR
#define PH_ERROR(x) \
	SetConsoleColor(12); \
	ph::LogMessage(__FILENAME__, __LINE__, LogData<None>() << x, PH_LOG_LEVEL_ERROR); \
	SetConsoleColor(15);
#else
#define PHOENIX_ERROR(x)
#endif

#if PH_LOG_LEVEL >= PH_LOG_LEVEL_WARN
#define PH_WARN(x) \
	SetConsoleColor(14); \
	ph::LogMessage(__FILENAME__, __LINE__, LogData<None>() << x, PH_LOG_LEVEL_WARN); \
	SetConsoleColor(15);
#else
#define PHOENIX_WARN(x)
#endif

#if PH_LOG_LEVEL >= PH_LOG_LEVEL_INFO
#define PH_INFO(x) \
	SetConsoleColor(10); \
	ph::LogMessage(__FILENAME__, __LINE__, LogData<None>() << x, PH_LOG_LEVEL_INFO); \
	SetConsoleColor(15);
#else
#define PHOENIX_INFO(x)
#endif

#ifdef DEBUG
#define PH_ASSERT(x, ...) \
	if (!(x)) {\
		SetConsoleColor(207); \
		ph::LogMessage(LogData<None>() << "***************************"); \
		ph::LogMessage(LogData<None>() << "     ASSERTION FAILED"); \
		ph::LogMessage(LogData<None>() << "***************************"); \
		ph::LogMessage(__FILE__, __LINE__, LogData<None>() << ":"); \
		ph::LogMessage(LogData<None>() << "Condition: " << #x); \
		ph::LogMessage(LogData<None>() << __VA_ARGS__); \
		SetConsoleColor(15); \
		__debugbreak(); \
	}
#else
#define PHOENIX_ASSERT(x, ...)
#endif
