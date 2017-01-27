#pragma once

#include <iostream>

#ifndef DEBUG 
#define DEBUG 1
#endif

#define FLOW_LOG_LEVEL_FATAL 0
#define FLOW_LOG_LEVEL_ERROR 1
#define FLOW_LOG_LEVEL_WARN	 2
#define FLOW_LOG_LEVEL_INFO  3

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

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
	operator <<(LogData<Begin> begin, const char (&value)[n])
{
	return { { begin.list, value } };
}

inline void printList(std::ostream &os, None)
{
}

template <typename Begin, typename Last>
void printList(std::ostream &os, const Pair<Begin, Last> &data)
{
	printList(os, data.first);
	os << data.second;
}

template <typename List>
void log_file_line(const char *file, int line, const LogData<List> &data)
{
	std::cout << file << " (" << line << "): ";
	printList(std::cout, data.list);
	std::cout << "\n";
}

template <typename List>
void log_fatal(const LogData<List> &data)
{
	printList(std::cerr, data.list);
	std::cout << "\n";
}

template <typename List>
void log_fatal(const char *file, int line, const LogData<List> &data)
{
	std::cerr << file << " (" << line << "): ";
	printList(std::cerr, data.list);
	std::cout << "\n";
}

#ifndef FLOW_LOG_LEVEL
#define FLOW_LOG_LEVEL FLOW_LOG_LEVEL_INFO
#endif

#if FLOW_LOG_LEVEL >= FLOW_LOG_LEVEL_INFO
#define LOG(x) \
	log_file_line(__FILENAME__,__LINE__,LogData<None>() << x)
#else
#define LOG(x)
#endif

#ifdef DEBUG
#define ASSERT(x, ...) \
	if (!(x)) {\
		log_fatal(LogData<None>() << "***************************"); \
		log_fatal(LogData<None>() << "     ASSERTION FAILED"); \
		log_fatal(LogData<None>() << "***************************"); \
		log_fatal(__FILE__,__LINE__, LogData<None>() << ":"); \
		log_fatal(LogData<None>() << "Condition: " << #x); \
		log_fatal(LogData<None>() << __VA_ARGS__); \
		__debugbreak(); \
	}
#else
#define ASSERT(x)
#endif