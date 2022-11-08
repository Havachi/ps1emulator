#include "opcode.h"

void op_lui(reg_t **registers, instruction_t *instruction)
{
	uint32_t imm = instruction->imm_value;
	uint32_t reg_index = instruction->register_index;

	uint32_t value = imm << 16;
	registers[reg_index]->value = value;
	printf("lui $%d, 0x%x\n", reg_index, imm);
}

void op_ori(reg_t **registers, instruction_t *instruction)
{
	uint32_t imm = instruction->imm_value;
	uint32_t reg_index = instruction->register_index;
	uint32_t reg_index2 = instruction->register_index2;

	uint32_t value = registers[reg_index2]->value | imm;
	registers[reg_index]->value = value;
	printf("ori $%d, $%d, 0x%x\n", reg_index, reg_index, imm);

}

void op_or(reg_t **registers, instruction_t *instruction)
{
	uint32_t t = instruction->register_index;
	uint32_t s = instruction->register_index2;
	uint32_t d = instruction->d;

	uint32_t value = registers[s]->value | registers[t]->value;
	registers[d]->value = value;
	printf("or $%d, $%d, $%d\n", d, s, t);
}

void	op_sw(interconnect_t *inter, reg_t **registers, instruction_t *instruction)
{
	uint32_t imm = instruction->imm_se_value;
	uint32_t reg_index = instruction->register_index;
	uint32_t reg_index2 = instruction->register_index2;

	uint32_t value = registers[reg_index]->value;
	uint32_t addr = registers[reg_index2]->value + imm;

	inter->store32(inter, addr, value);

	printf("sw $%d, 0x%x($%d)\n", reg_index, imm, reg_index2);
}

void op_sll(reg_t **registers, instruction_t *instruction)
{
	uint32_t shift = instruction->shift;
	uint32_t reg_index = instruction->register_index;
	uint32_t d = instruction->d;

	uint32_t value = registers[reg_index]->value << shift;

	registers[d]->value = value;

	printf("sll $%d, $%d, 0x%x\n", reg_index, d, shift);
}

void op_addiu(reg_t **registers, instruction_t *instruction)
{
	uint32_t imm = instruction->imm_se_value;
	uint32_t reg_index = instruction->register_index;
	uint32_t reg_index2 = instruction->register_index2;

	uint32_t value = registers[reg_index]->value + imm;

	registers[reg_index2]->value = value;

	printf("addiu $%d, $%d, 0x%x\n", reg_index, reg_index2, imm);
}

void op_j(uint32_t *pc, instruction_t *instruction)
{
	uint32_t imm = instruction->imm_jump;
	(*pc) = ((*pc) & 0xf0000000) | (imm << 2);
	printf("j 0x%x\n", imm);
}