#ifndef OPCODE_H
#define OPCODE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "instruction.h"
#include "register.h"
#include "interconnect.h"

void	op_lui(reg_t **registers, instruction_t *instruction);
void	op_ori(reg_t **registers, instruction_t *instruction);
void	op_or(reg_t **registers, instruction_t *instruction);
void	op_sw(interconnect_t *inter, reg_t **registers, instruction_t *instruction);
void	op_sll(reg_t **registers, instruction_t *instruction);
void	op_addiu(reg_t **registers, instruction_t *instruction);
void	op_j(uint32_t *pc, instruction_t *instruction);

#endif