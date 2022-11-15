#include "instruction.h"

instruction_t	*new_instruction(uint32_t raw, uint32_t fount_at_pc)
{
	instruction_t	*instruction;
	instruction = (instruction_t *)malloc(sizeof(instruction_t));
	if(instruction == NULL)
	{
		fprintf(stderr, "Error: Could not allocate memory for instruction\n");
		exit(1);
	}
	instruction->raw_instruction = raw;
	instruction->opcode = get_opcode(raw);
	instruction->t = get_t(raw);
	instruction->s = get_s(raw);
	instruction->imm_value = get_imm_value(raw);
	instruction->imm_se_value = get_imm_se(raw);
	instruction->d = get_d(raw);
	instruction->subopcode = get_subopcode(raw);
	instruction->shift = shift(raw);
	instruction->imm_jump = get_imm_jump(raw);
	instruction->cop_opcode = get_cop_opcode(raw);
	instruction->found_at_pc = fount_at_pc;
	return (instruction);
}

uint32_t		get_opcode(uint32_t instruction)
{
	return (instruction >> 26);
}

uint32_t		get_t(uint32_t instruction)
{
	return ((instruction >> 16) & 0x1f);
}

uint32_t		get_s(uint32_t instruction)
{
	return ((instruction >> 21) & 0x1f);
}

uint32_t		get_imm_value(uint32_t instruction)
{
	return (instruction & 0xffff);
}

uint32_t		get_imm_se(uint32_t instruction)
{
	return (((int16_t)(instruction & 0xffff)) << 16) >> 16;
}

uint32_t		get_d(uint32_t instruction)
{
	return (instruction >> 11) & 0x1f;
}

uint32_t		get_subopcode(uint32_t instruction)
{
	return (instruction & 0x3f);
}

uint32_t		shift(uint32_t instruction)
{
	return (instruction >> 6) & 0x1f;
}

uint32_t		get_imm_jump(uint32_t instruction)
{
	return (instruction & 0x3ffffff);
}

uint32_t		get_cop_opcode(uint32_t instruction)
{
	return (instruction >> 21) & 0x1f;
}