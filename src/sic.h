#pragma once

#include <stdint.h>
#include <stdbool.h>

void sic_remap_irq(uint8_t irq, uint8_t cpu, uint8_t prio, bool mask);
uint8_t sic_claim();
void sic_eoi();
