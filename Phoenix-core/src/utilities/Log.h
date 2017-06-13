#pragma once

#include <iostream>
#include <stdio.h>
#include <Windows.h>

#ifndef DEBUG 
#define DEBUG 1
#endif

#define PHOENIX_LOG_LEVEL_FATAL 0
#define PHOENIX_LOG_LEVEL_ERROR 1
#define PHOENIX_LOG_LEVEL_WARN	2
#define PHOENIX_LOG_LEVEL_INFO  3

#define PHOENIX_LOG_LEVEL_FATAL_COLOR 4
#define PHOENIX_LOG_LEVEL_ERROR_COLOR 12
#define PHOENIX_LOG_LEVEL_WARN_COLOR  14
#define PHOENIX_LOG_LEVEL_INFO_COLOR  10

#define PHOENIX_LEN(x) (sizeof(x) / sizeof(x)[0])

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

template <typename T>
bool IsInBounds(const T& value, const T& low, const T& high) {
	return !(value < low) && !(high < value);
}

static void SetConsoleColor(int colorCode) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorCode);
}

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
	LogData<Pair<Begin, const Value &>>
		operator<<(LogData<Begin> begin, const Value &value)
	{
		return { { begin.list,value } };
	}

	template <typename Begin, size_t n>
	LogData<Pair<Begin, const char*>>
		operator <<(LogData<Begin> begin, const char(&value)[n])
	{
		return { { begin.list, value } };
	}

	inline void printList(std::ostream &os, None) { }

	template <typename Begin, typename Last>
	void printList(std::ostream &os, const Pair<Begin, Last> &data)
	{
		printList(os, data.first);
		os << data.second;
	}

	template <typename List>
	void log_message(const char *file, int line, const LogData<List> &data, int level = -1)
	{
		switch (level) {
		case 0:
			std::cout << "[FATAL]:   " << file << " (" << line << "): ";
			break;
		case 1:
			std::cout << "[ERROR]:   " << file << " (" << line << "): ";
			break;
		case 2:
			std::cout << "[WARNING]: " << file << " (" << line << "): ";
			break;
		case 3:
			std::cout << "[INFO]:    " << file << " (" << line << "): ";
			break;
		default:
			std::cout << file << " (" << line << "): ";
			break;
		}
		printList(std::cout, data.list);
		std::cout << "\n";
	}

	template <typename List>
	void log_message(const LogData<List> &data)
	{
		printList(std::cout, data.list);
		std::cout << "\n";
	}
}

#ifndef PHOENIX_LOG_LEVEL
#define PHOENIX_LOG_LEVEL PHOENIX_LOG_LEVEL_INFO
#endif

#if PHOENIX_LOG_LEVEL >= PHOENIX_LOG_LEVEL_FATAL
#define PHOENIX_FATAL(x) \
	SetConsoleColor(13); \
	ph::log_message(__FILENAME__, __LINE__, LogData<None>() << x, PHOENIX_LOG_LEVEL_FATAL); \
	SetConsoleColor(15);
#else
#define PHOENIX_FATAL(x)
#endif

#if PHOENIX_LOG_LEVEL >= PHOENIX_LOG_LEVEL_ERROR
#define PHOENIX_ERROR(x) \
	SetConsoleColor(12); \
	ph::log_message(__FILENAME__, __LINE__, LogData<None>() << x, PHOENIX_LOG_LEVEL_ERROR); \
	SetConsoleColor(15);
#else
#define PHOENIX_ERROR(x)
#endif

#if PHOENIX_LOG_LEVEL >= PHOENIX_LOG_LEVEL_WARN
#define PHOENIX_WARN(x) \
	SetConsoleColor(14); \
	ph::log_message(__FILENAME__, __LINE__, LogData<None>() << x, PHOENIX_LOG_LEVEL_WARN); \
	SetConsoleColor(15);
#else
#define PHOENIX_WARN(x)
#endif

#if PHOENIX_LOG_LEVEL >= PHOENIX_LOG_LEVEL_INFO
#define PHOENIX_INFO(x) \
	SetConsoleColor(10); \
	ph::log_message(__FILENAME__, __LINE__, LogData<None>() << x, PHOENIX_LOG_LEVEL_INFO); \
	SetConsoleColor(15);
#else
#define PHOENIX_INFO(x)
#endif

#ifdef DEBUG
#define PHOENIX_ASSERT(x, ...) \
	if (!(x)) {\
		SetConsoleColor(207); \
		ph::log_message(LogData<None>() << "***************************"); \
		ph::log_message(LogData<None>() << "     ASSERTION FAILED"); \
		ph::log_message(LogData<None>() << "***************************"); \
		ph::log_message(__FILE__, __LINE__, LogData<None>() << ":"); \
		ph::log_message(LogData<None>() << "Condition: " << #x); \
		ph::log_message(LogData<None>() << __VA_ARGS__); \
		SetConsoleColor(15); \
		__debugbreak(); \
	}
#else
#define PHOENIX_ASSERT(x, ...)
#endif