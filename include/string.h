#pragma once

#include <stdint.h>
#include <stddef.h>

void *memset(void *s, int c, size_t n);
void *memcpy(void *d, const void *s, size_t n);
void *memmove(void *d, const void *s, size_t n);
void *memchr(const void *s, int c, size_t n);
int memcmp(const void *a, const void *b, size_t n);
size_t strlen(const char *s);
size_t strnlen(const char *s, size_t n);
char *strrchr(const char *s, int c);
int strcmp(const char *s1, const char *s2);
