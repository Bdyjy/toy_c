/* 异常，用于错误处理
*/

#pragma once

#include "Defines.h"
#include <exception>
#include <stdio.h>
#include <stdarg.h>

#define EXCPTION_MESSAGE_MAX_LENGHT 1000

TC_NAMESPACE_START

class Exception : public std::exception
{
public:
	Exception() : std::exception() {}
	Exception(const char* str) : std::exception(str) {}
	Exception(const Exception& ex) : std::exception(ex.what()) {}
};

inline Exception _GenException(const char* format, ...)
{
	char msg[EXCPTION_MESSAGE_MAX_LENGHT] = { 0 };

	va_list args;
	va_start(args, format);
	vsprintf_s(msg, format, args);
	va_end(args);

	return Exception(msg);
}

#define GEN_EXCEPTION(format, ...) throw _GenException(format, __VA_ARGS__)

TC_NAMESPACE_END