#pragma once

#include <stdint.h>

void pl110_init();
void pl110_update();
void pl110_setpix(uint32_t x, uint32_t y, uint32_t color);
