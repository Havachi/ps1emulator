#include "ram.h"

ram_t	*new_ram(uint32_t size)
{
	ram_t	*ram = malloc(sizeof(ram_t));
	ram->data = malloc(sizeof(uint8_t) * size);
	ram->size = size;
	ram->load32 = ram_load32;
	ram->store32 = ram_store32;
	init_ram(ram);
	return ram;
}

void	init_ram(ram_t *ram)
{
	uint32_t i = 0;
	while (i < ram->size)
	{
		ram->data[i] = 0xca;
		i++;
	}
}

uint32_t ram_load32(ram_t *ram, uint32_t offset)
{
	uint32_t data;

	uint32_t b0 = ram->data[offset + 0];
	uint32_t b1 = ram->data[offset + 1];
	uint32_t b2 = ram->data[offset + 2];
	uint32_t b3 = ram->data[offset + 3];

	data = b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
	return (data);
}
void ram_store32(ram_t *ram, uint32_t offset, uint32_t data)
{
	uint8_t b0 = (uint8_t)data;
	uint8_t b1 = (uint8_t)(data >> 8) & 0xFF;
	uint8_t b2 = (uint8_t)(data >> 16) & 0xFF;
	uint8_t b3 = (uint8_t)(data >> 24) & 0xFF;

	ram->data[offset + 0] = b0;
	ram->data[offset + 1] = b1;
	ram->data[offset + 2] = b2;
	ram->data[offset + 3] = b3;
}