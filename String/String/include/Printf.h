#ifndef PRINTF_H
#define PRINTF_H
#include <cstdarg>

auto Printf(char* dst, const void* end, const char* fmt, ...) -> char*;
auto vPrintf(char* dst, const void* end, const char* fmt, va_list argumentList) -> char*;

#endif
