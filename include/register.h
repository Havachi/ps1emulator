#ifndef REGISTER_H
#define REGISTER_H
#define REGISTER_INIT_VALUE 0xCAFECAFE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

typedef struct reg_s {
	uint32_t	value;
	void		(*write)(struct reg_s*, uint32_t);
	uint32_t	(*read)(struct reg_s*);
} reg_t;

reg_t		*new_register(reg_t *reg, uint32_t init_value);
reg_t		**init_registers(uint32_t init_value, int n);
void		write_register(reg_t *reg, uint32_t value);
uint32_t	read_register(reg_t *reg);
#endif