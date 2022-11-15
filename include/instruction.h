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
	uint32_t	t;
	uint32_t	s;
	uint32_t	imm_value;
	uint32_t	imm_se_value;
	uint32_t	d;
	uint32_t	subopcode;
	uint32_t	shift;
	uint32_t	imm_jump;
	uint32_t	cop_opcode;
	uint32_t	found_at_pc;

} instruction_t;

typedef struct t_s
{
	uint32_t	index;
}t_t;

instruction_t	*new_instruction(uint32_t instruction, uint32_t found_at_pc);
uint32_t		get_opcode(uint32_t instruction);
uint32_t		get_t(uint32_t instruction);
uint32_t		get_s(uint32_t instruction);
uint32_t		get_imm_value(uint32_t instruction);
uint32_t		get_imm_se(uint32_t instruction);
uint32_t		get_d(uint32_t instruction);
uint32_t		get_subopcode(uint32_t instruction);
uint32_t		shift(uint32_t instruction);
uint32_t		get_imm_jump(uint32_t instruction);
uint32_t		get_cop_opcode(uint32_t instruction);
#endif