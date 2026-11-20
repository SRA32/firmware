#pragma once

#include <stdint.h>

typedef struct {
    volatile uint32_t val;
} spinlock_t;

#define SPINLOCK_INIT { 0 }

void lock(spinlock_t *lock);
void unlock(spinlock_t *lock);
