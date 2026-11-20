#include "string.h"

void *memset(void *s, int c, size_t n)
{
    unsigned char *p = s;

    while (n--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}

void *memcpy(void *d, const void *s, size_t n)
{
    unsigned char *dp = d;
    const unsigned char *sp = s;

    while (n--)
    {
        *dp++ = *sp++;
    }
    return d;
}

void *memmove(void *d, const void *s, size_t n)
{
    unsigned char *dp = d;
    const unsigned char *sp = s;

    if (dp == sp || n == 0)
    {
        return d;
    }

    if (dp < sp)
    {
        while (n--)
        {
            *dp++ = *sp++;
        }
    } else {
        dp += n;
        sp += n;
        while (n--)
        {
            *--dp = *--sp;
        }
    }

    return d;
}

void *memchr(const void *s, int c, size_t n)
{
    const unsigned char *p = s;

    while (n--) {
        if (*p == (unsigned char)c)
        {
            return (void *)p;
        }
        p++;
    }
    return NULL;
}

int memcmp(const void *a, const void *b, size_t n)
{
    const unsigned char *pa = a, *pb = b;

    while (n--) {
        if (*pa != *pb)
        {
            return *pa - *pb;
        }
        pa++;
        pb++;
    }
    return 0;
}

size_t strlen(const char *s)
{
    const char *p = s;

    while (*p)
    {
        p++;
    }
    return p - s;
}

size_t strnlen(const char *s, size_t n)
{
    size_t i = 0;

    while (i < n && s[i])
    {
        i++;
    }
    return i;
}

char *strrchr(const char *s, int c)
{
    const char *last = NULL;

    do
    {
        if (*s == (char)c)
        {
            last = s;
        }
    } while (*s++);
    return (char *)last;
}

int strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }

    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

