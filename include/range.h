#ifndef RANGE_H
#define RANGE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define BIOS_RANGE new_range(0xbfc00000, 512*1024)
#define MEM_CONTROL new_range(0x1f801000, 36)
#define RAM_SIZE new_range(0x1f801060, 4)
#define CACHE_CONTROL new_range(0xfffe0130, 4)

typedef struct range_s {
	uint32_t start;
	uint32_t length;
	uint32_t (*contains)(struct range_s*, uint32_t);
} range_t;

range_t *new_range(uint32_t start, uint32_t length);
uint32_t range_contains(range_t *range, uint32_t addr);
#endif