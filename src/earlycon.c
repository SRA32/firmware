#include "earlycon.h"
#include "pl110.h"
#include "font.h"

uint32_t econ_x, econ_y;

void earlycon_init()
{
    econ_x = 0, econ_y = 0;
}

void earlycon_putc(char c)
{
    uint8_t *glyph = font + (c * FONT_HEIGHT);
    for (int y = 0; y < FONT_HEIGHT; y++) {
        for (int x = 0; x < FONT_WIDTH; x++) {
            int set = (glyph[y] >> (7 - x)) & 1;
            pl110_setpix(econ_x + x, econ_y + y, set ? 0xFFB0B0B0 : 0xFF000000);
        }
    }
}

void earlycon_puts(const char *str)
{
    while (*str) {
        if (*str == '\n') {
            econ_x = 0;
            econ_y += FONT_HEIGHT;
            str++;
            continue;
        }

        earlycon_putc(*str++);
        econ_x += FONT_WIDTH;
    }
}
