#ifndef INTERCONNECT_H
#define INTERCONNECT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bios.h"
#include "range.h"
#include "ram.h"

typedef struct interconnect_s
{
	bios_t		*bios;
	ram_t		*ram;
	uint32_t	(*load32)(struct interconnect_s*, uint32_t);
	void		(*store32)(struct interconnect_s*, uint32_t, uint32_t);
	uint16_t	(*load16)(struct interconnect_s*, uint32_t);
	void		(*store16)(struct interconnect_s*, uint32_t, uint16_t);
	void		(*store8)(struct interconnect_s*, uint32_t, uint8_t);
} interconnect_t;


interconnect_t	*new_interconnect(bios_t *bios, ram_t *ram);

uint32_t		interconnect_load32(interconnect_t *interconnect, uint32_t addr);
void			interconnect_store32(interconnect_t *interconnect, uint32_t addr, uint32_t value);

uint16_t		interconnect_load16(interconnect_t *interconnect, uint32_t addr);
void			interconnect_store16(interconnect_t *interconnect, uint32_t addr, uint16_t value);

void			interconnect_store8(interconnect_t *interconnect, uint32_t addr, uint8_t value);

uint32_t		mask_region(uint32_t addr);

#endif