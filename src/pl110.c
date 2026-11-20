#include "pl110.h"

#define PL110_BASE 0xF0120000

#define LCDTIMING0 0x00
#define LCDTIMING1 0x04
#define LCDUPBASE  0x10
#define LCDCONTROL 0x1C

#define WIDTH 640
#define HEIGHT 480

volatile uint32_t *lcd = (volatile uint32_t *)PL110_BASE;
uint32_t *fb;

void pl110_init()
{
    fb = (uint32_t*)0x400000;

    lcd[LCDTIMING0 / 4] = 0x9C;
    lcd[LCDTIMING1 / 4] = 479;

    lcd[LCDUPBASE / 4] = (uint32_t)fb;

    lcd[LCDCONTROL / 4] = (5 << 1) | 1 | (1 << 11);
}

void pl110_setpix(uint32_t x, uint32_t y, uint32_t color)
{
    fb[y * WIDTH + x] = color;
}
