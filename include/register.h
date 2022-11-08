#ifndef REGISTER_H
#define REGISTER_H
#define REGISTER_INIT_VALUE 0xCAFECAFE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

typedef struct reg_s {
	uint32_t value;
} reg_t;

reg_t	*new_register(reg_t *reg, uint32_t init_value);
reg_t **init_registers(uint32_t init_value);
uint32_t read_registers(int index, reg_t **registers);
reg_t **write_registers(int index, uint32_t value, reg_t **registers);
#endif