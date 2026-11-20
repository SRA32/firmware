#include "ahci.h"
#include "printf.h"

#define PORT_BASE(i) (0x100 + ((i) * 0x80))
#define PX_CLB  0x00
#define PX_FB   0x08
#define PX_CMD  0x18
#define PX_SIG  0x24
#define PX_SSTS 0x28

#define PORT_FRE (1 << 4)
#define PORT_FR  (1 << 14)

void ahci_init(uint32_t addr)
{
    ahci_hdr_t *hdr = (ahci_hdr_t*)addr;
    // Enable AHCI
    hdr->ghc |= (1 << 31);
    uint32_t pi = hdr->pi;
    for (int i = 0; i < 32; i++) {
        if (pi & (1 << i)) {
            volatile uint32_t *port = (volatile uint32_t*)(addr + PORT_BASE(i));
            uint32_t ssts = port[0x28 / 4];
            uint8_t det = ssts & 0x0F;
            uint8_t ipm = (ssts >> 8) & 0x0F;
            if (det == 0x3 && ipm == 0x1) {
                uint32_t sig = port[0x24 / 4];
                port[PX_CLB / 4] = 0x800000; // Magic constants because this is just TEST.
                port[PX_FB / 4]  = 0x900000;
                port[PX_CMD / 4] |= PORT_FRE;

                while (!(port[PX_CMD / 4] & PORT_FR)) {
                }
            
                // printf("Port %d: SSTS=%x SIG=%x (101 = sata)\n", i, port[PX_SSTS / 4], port[PX_SIG / 4]);
            }
        }
    }
}
