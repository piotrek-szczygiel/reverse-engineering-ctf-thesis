#pragma once
#include <cinttypes>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

using byte = uint8_t;
using word = uint16_t;

void dbg(const char* format, ...)
{
#ifdef PRINT_DEBUG
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);
#endif
}

void err(int exit_code, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);
    exit(exit_code);
}
