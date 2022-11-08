#ifndef BIOS_H
#define BIOS_H
#define BIOS_SIZE 512 * 1024
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
typedef struct bios_s
{
	uint8_t		*data;
	uint32_t	(*load32)(struct bios_s*, uint32_t);
}bios_t;

bios_t *new_bios(char *path);
uint32_t bios_load32(bios_t *bios, uint32_t offset);

#endif