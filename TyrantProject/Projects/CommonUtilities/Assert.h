#pragma once

#ifndef WINDOWS
#include <Windows.h>
#endif
#include <sstream>

#pragma warning (disable:4127)

#ifndef _DEBUG
	#define DEBUG_ASSERT(statement, message)     ((void)0)
#else
	#define DEBUG_ASSERT(statement, message)\
	if((!(statement)) == true)\
	{\
		std::string file = __FILE__; \
		int index = file.find_last_of('\\') + 1; \
		file = file.substr(index, file.length() - index); \
		\
		std::stringstream text; \
		text << "Statement: \"" << #statement << "\""; \
		text << "\nFile: \"" << file << "\""; \
		text << "\nLine: " << __LINE__; \
		text << "\n\n" << message; \
		\
		MessageBoxA(0, text.str().c_str(), "Assertion!", 0); \
		__debugbreak(); \
	}\
	else 0;
#endif


#ifdef _DEBUG
	#define RELEASE_ASSERT(statement, message)     ((void)0)
#else
	#define RELEASE_ASSERT(statement, message)\
	if((!(statement)) == true)\
	{\
		std::string file = __FILE__; \
		int index = file.find_last_of('\\') + 1; \
		file = file.substr(index, file.length() - index); \
		\
		std::stringstream text; \
		text << "Statement: \"" << #statement << "\""; \
		text << "\nFile: \"" << file << "\""; \
		text << "\nLine: " << __LINE__; \
		text << "\n\n" << message; \
		\
		MessageBoxA(0, text.str().c_str(), "Assertion!", 0); \
		__debugbreak(); \
	}\
	else 0;
#endif


#define ASSERT(statement, message)\
	if((!(statement)) == true)\
	{\
		std::string file = __FILE__; \
		int index = file.find_last_of('\\') + 1; \
		file = file.substr(index, file.length() - index); \
		\
		std::stringstream text; \
		text << "Statement: \"" << #statement << "\""; \
		text << "\nFile: \"" << file << "\""; \
		text << "\nLine: " << __LINE__; \
		text << "\n\n" << message; \
		\
		MessageBoxA(0, text.str().c_str(), "Assertion!", 0); \
		__debugbreak(); \
	}\
	else 0;