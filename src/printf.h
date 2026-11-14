#pragma once

#include <stdint.h>
#include <stdarg.h>

int printf(const char*,...);
int puts(const char*);
int vsnprintf(char *buf, int len, const char *fmt, va_list vlist);
