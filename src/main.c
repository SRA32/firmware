#include <stdint.h>
#include "uart.h"
#include "sic.h"
#include "printf.h"
#include "pl110.h"
#include "earlycon.h"

#define PCI_ECAM_BASE 0xC0000000

uint16_t pcie_read16(uint8_t bus, uint8_t dev, uint8_t func, uint8_t reg)
{
    uint32_t addr = (PCI_ECAM_BASE | (bus << 20) | (dev << 15) | (func << 12)) + reg;
    return *((uint16_t*)addr);
}

uint32_t pcie_read32(uint8_t bus, uint8_t dev, uint8_t func, uint8_t reg)
{
    uint32_t addr = (PCI_ECAM_BASE | (bus << 20) | (dev << 15) | (func << 12)) + reg;
    return *((uint32_t*)addr);
}

void pcie_write32(uint8_t bus, uint8_t dev, uint8_t func, uint8_t reg, uint32_t val)
{
    uint32_t addr = (PCI_ECAM_BASE | (bus << 20) | (dev << 15) | (func << 12)) + reg;
    *((uint32_t*)addr) = val;
}

void main(void)
{
    uart_puts("Hello world from SRA32 Apollo firmware.\n");
    pl110_init();
    printf("Hello earlycon!\n");

    uint16_t vendor = pcie_read16(0, 1, 0, 0);
    uint16_t device = pcie_read16(0, 1, 0, 2);

    // Since we're firmware, we gotta allocate space for it!
    pcie_write32(0, 1, 0, 0x24, 0xFFFFFFFF);
    uint32_t ahci_size = pcie_read32(0, 1, 0, 0x24);
    printf("ICH9-AHCI (%x:%x) requires: 0x%x.\n", vendor, device, ahci_size);

    while (1) {
    }
}

int printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    char buf[1024];

    int len = vsnprintf(buf, 1024, fmt, ap);

    earlycon_puts(buf);

    return len;
}

int puts(const char *str) {
    return printf("%s\n", str);
}
