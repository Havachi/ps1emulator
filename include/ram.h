#ifndef RAM_H
#define RAM_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define RAM_SIZE 2 * 1024 * 1024
typedef struct ram_s
{
	uint8_t		*data;
	uint32_t	size;
	uint32_t	(*load32)(struct ram_s*, uint32_t);
	void		(*store32)(struct ram_s*, uint32_t, uint32_t);
}ram_t;

ram_t		*new_ram(uint32_t size);
void		init_ram(ram_t *ram);
uint32_t	ram_load32(ram_t *ram, uint32_t offset);
void		ram_store32(ram_t *ram, uint32_t offset, uint32_t data);

#endif
