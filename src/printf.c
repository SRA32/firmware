#include "printf.h"

int vsnprintf(char *buf, int len, const char *fmt, va_list vlist) {
    int count = 0;

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 's':
                case 'S': {
                    fmt++;
                    char *ptr = va_arg(vlist, char*);
                    while (*ptr) {
                        buf[count++] = *ptr;
                        ptr++;
                    }
                    break;
                }
                case 'd':
                case 'D': {
                    fmt++;
                    int value = va_arg(vlist, int);
                    if (value == 0) {
                        buf[count++] = '0';
                        break;
                    } else if ((uint32_t)value < 10) {
                        buf[count++] = '0' + value;
                        break;
                    }
                    if (value >> 31) {
                        buf[count++] = '-';
                        value = -value;
                    }
                    char tmp[12];
                    int i = 0;
                    int n = value;
                    while (n > 0) {
                        tmp[i++] = ((n % 10) + '0');
                        n /= 10;
                    }
                    while (i) buf[count++] = tmp[--i];
                    break;
                }
                case 'x':
                case 'X': {
                    fmt++;
                    uint32_t value = va_arg(vlist, uint32_t);
                    if (value == 0) {
                        buf[count++] = '0';
                        break;
                    }
                    char tmp[8];
                    int i = 0;
                    char *digits = "0123456789ABCDEF";
                    while (value > 0)  {
                        tmp[i++] = digits[value & 0xF];
                        value >>= 4;
                    }
                    while (i) buf[count++] = tmp[--i];
                    break;
                }
                case 'l':
                case 'L': {
                    fmt++;
                    if (*fmt == 'D' || *fmt == 'd') {
                        fmt++;
                        // TODO. (requires some external helper functions.)
                    } else if (*fmt == 'X' || *fmt == 'x') {
                        fmt++;
                        uint64_t value = va_arg(vlist, uint64_t);
                        if (value == 0) {
                            buf[count++] = '0';
                            break;
                        }
                        char tmp[16];
                        int i = 0;
                        char *digits = "0123456789ABCDEF";
                        while (value > 0) {
                            tmp[i++] = digits[value & 0xF];
                            value >>= 4;
                        }
                        while (i) buf[count++] = tmp[--i];
                    }
                    break;
                }
                case 'c':
                case 'C': {
                    fmt++;
                    char value = (char)va_arg(vlist, int);
                    buf[count++] = value;
                    break;
                }
                default:
                    buf[count++] = *fmt;
                    fmt++;
            }
            continue;
        }

        buf[count++] = *fmt;
        fmt++;
    }
    buf[count] = 0;

    return count;
}
