#pragma once

#include <stdint.h>
#include <stdbool.h>

#define CPU(n) (1 << n)

#define REASON_TIMER 1
#define REASON_IPI 2

void sic_remap_irq(uint8_t irq, uint8_t cpu, uint8_t prio, bool mask);
uint8_t sic_claim();
void sic_eoi();

uint32_t lic_reason();
void lic_clear(uint32_t reason);
void lic_ipi(uint32_t cpu_mask);
