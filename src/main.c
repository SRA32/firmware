#include <stdint.h>
#include <string.h>
#include <libfdt.h>
#include "uart.h"
#include "ic.h"
#include "printf.h"
#include "pl110.h"
#include "flanterm/flanterm.h"
#include "flanterm/flanterm_backends/fb.h"
#include "ahci.h"
#include "lock.h"

void internal_local_handler();

struct flanterm_context *ft_ctx;

typedef struct {
    uint32_t excb;
    uint32_t intb;
    uint32_t locb;
} intc_t;

intc_t intc;

void flanterm_init()
{
    ft_ctx = flanterm_fb_init(
        NULL,
        NULL,
        (uint32_t*)0x400000, 640, 480, 640 * 4,
        8, 16,
        8, 8,
        8, 0,
        NULL,
        NULL, NULL,
        NULL, NULL,
        NULL, NULL,
        NULL, 0, 0, 1,
        1, 1,
        5,
        0,
        true
    );
}

void int_handler(void)
{
    printf("Handled interrupt!\n");
    asm ("iret");
}

void local_handler(void)
{
    uint32_t reason = lic_reason();
    uint32_t cpu = 0;

    asm (
        "sw $r26, %0"
        : "=m"(cpu)
    );

    printf("Local interrupt handled.\n");

    if (reason & REASON_TIMER)
    {
        printf("Timer interrupt for CPU #%d handled!\n", cpu);
        lic_clear(REASON_TIMER);
    }

    if (reason & REASON_IPI)
    {
        printf("IPI for CPU #%d handled!\n", cpu);
        lic_clear(REASON_IPI);
    }
}

void timer_arm(uint64_t deadline)
{
    uint32_t low = (uint32_t)deadline;
    uint32_t high = (uint32_t)(deadline >> 32);

    asm (
        "mov $r0, %0\n"
        "mov $r1, %1\n"
        "wcr $r0, 9\n" // Write low to TDEAD0
        "wcr $r1, 10\n" // Write high to TDEAD1
        : : "r"(low), "r"(high) : "$r0", "$r1"
    );
}

bool bsp_started = false;
uint32_t ap_done = 0;

spinlock_t ap_lock = SPINLOCK_INIT;

void ap_start()
{
    while (!bsp_started);

    uint32_t cpu = 0;

    asm (
        "sw $r26, %0"
        : "=m"(cpu)
    );

    printf("Hello from CPU %d\n", cpu);

    lock(&ap_lock); ap_done++; unlock(&ap_lock);

    while (1)
    {
    }
}

void main(void *fdt)
{
    uart_puts("Hello world from SRA32 Apollo firmware.\n");
    pl110_init();
    flanterm_init();

    printf("Flanterm initialised.\n");
    bsp_started = true;

    while (ap_done < 3);
    printf("All cores have been initialized.\n");

    while (1)
    {
    }
}

void _putchar(char character)
{
    if (character == '\n')
    {
        flanterm_write(ft_ctx, "\n\r", 2);
        return;
    }

    char buf[] = {character, 0};
    flanterm_write(ft_ctx, buf, sizeof(buf) - 1);
}

