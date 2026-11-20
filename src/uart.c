#include "uart.h"

#define UART_BASE  0xF0110000

#define UART_THR   0x00
#define UART_IER   0x04
#define UART_LSR   0x14

#define UART_LSR_THRE (1 << 5)

static inline volatile uint8_t *uart_reg(uint32_t offset)
{
    return (volatile uint8_t *)(UART_BASE + offset);
}

void uart_init()
{
    *uart_reg(UART_IER) = 0x01;
}

void uart_putc(char c)
{
    while (!(*uart_reg(UART_LSR) & UART_LSR_THRE))
        ;

    *uart_reg(UART_THR) = c;
}

void uart_puts(const char *str)
{
    while (*str)
        uart_putc(*str++);
}
