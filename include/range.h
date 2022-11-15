#ifndef RANGE_H
#define RANGE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define RAM_RANGE new_range(0x00000000, 2 * 1024 * 1024, "RAM")
#define BIOS_RANGE new_range(0x1fc00000, 512 * 1024, "BIOS")
#define SYS_CONTROL_RANGE new_range(0x1f801000, 36, "SYS_CONTROL")
#define RAM_SIZE_RANGE new_range(0x1f801060, 4, "RAM_SIZE")
#define CACHE_CONTROL_RANGE new_range(0xfffe0130, 4, "CACHE_CONTROL")
#define SPU_RANGE new_range(0x1f801c00, 640, "SPU")
//Unused
#define EXPANSION_2_RANGE new_range(0x1f802000, 66, "EXPANSION_2")


typedef struct range_s {
	char		*name;//Debugging purposes
	uint32_t	start;
	uint32_t	length;
	bool		(*contains)(struct range_s*, uint32_t, uint32_t *);
	uint32_t	(*offset)(struct range_s*, uint32_t);
} range_t;

range_t		*new_range(uint32_t start, uint32_t length, char *name);
bool		range_contains(range_t *range, uint32_t addr, uint32_t *offset);
uint32_t	get_offset(range_t *range, uint32_t addr);

#endif