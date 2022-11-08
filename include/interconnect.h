#ifndef INTERCONNECT_H
#define INTERCONNECT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bios.h"
#include "range.h"

typedef struct interconnect_s
{
	bios_t		*bios;
	uint32_t	(*load32)(struct interconnect_s*, uint32_t);
	void		(*store32)(struct interconnect_s*, uint32_t, uint32_t);
} interconnect_t;


interconnect_t	*new_interconnect(bios_t *bios);
uint32_t		interconnect_load32(interconnect_t *interconnect, uint32_t addr);
void			interconnect_store32(interconnect_t *interconnect, uint32_t addr, uint32_t value);

#endif