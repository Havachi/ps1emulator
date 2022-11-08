#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

typedef struct instruction_s
{
	uint32_t	raw_instruction;
	uint32_t	opcode;
	uint32_t	register_index;
	uint32_t	register_index2;
	uint32_t	imm_value;
	uint32_t	imm_se_value;
	uint32_t	d;
	uint32_t	subopcode;
	uint32_t	shift;
	uint32_t	imm_jump;

} instruction_t;

typedef struct register_index_s
{
	uint32_t	index;
}register_index_t;

instruction_t	*new_instruction(uint32_t instruction);
uint32_t		get_opcode(uint32_t instruction);
//t
uint32_t		get_register_index(uint32_t instruction);
//s
uint32_t		get_register_index2(uint32_t instruction);
uint32_t		get_imm_value(uint32_t instruction);
uint32_t		get_imm_se(uint32_t instruction);
uint32_t		get_d(uint32_t instruction);
uint32_t		get_subopcode(uint32_t instruction);
uint32_t		shift(uint32_t instruction);
uint32_t		get_imm_jump(uint32_t instruction);
#endif