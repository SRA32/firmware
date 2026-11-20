#include "ic.h"

#define SIC_BASE 0xF0200000
#define SIC_CLAIM 0x30
#define SIC_EOI 0x40

#define LIC_BASE 0xF0300000
#define LIC_IPI 0x00
#define LIC_REASON 0x04
#define LIC_CLEAR 0x08

static inline volatile void *sic_reg(uint32_t offset)
{
    return (volatile void *)(SIC_BASE + offset);
}

static inline volatile void sic_write8(uint32_t offset, uint8_t data)
{
    *((uint8_t*)sic_reg(offset)) = data;
}

void sic_remap_irq(uint8_t irq, uint8_t cpu, uint8_t prio, bool mask)
{
    uint8_t map = (cpu & 0x1F) | (prio & 0x80);
    sic_write8(irq, mask ? 0xFF : map);
}

uint8_t sic_claim()
{
    return *((uint8_t*)sic_reg(SIC_CLAIM));
}

void sic_eoi()
{
    *((uint8_t*)sic_reg(SIC_EOI)) = 0;
}

static inline volatile void *lic_reg(uint32_t offset)
{
    return (volatile void *)(LIC_BASE + offset);
}

uint32_t lic_reason()
{
    return *((uint32_t*)lic_reg(LIC_REASON));
}

void lic_clear(uint32_t reason)
{
    *((uint32_t*)lic_reg(LIC_CLEAR)) = reason;
}

void lic_ipi(uint32_t cpu_mask)
{
    *((volatile uint32_t*)lic_reg(LIC_IPI)) = cpu_mask;
}
