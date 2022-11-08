#include "cpu.h"

cpu_t *new_cpu(interconnect_t *inter)
{
	cpu_t *cpu = malloc(sizeof(cpu_t));
	cpu->pc = 0xbfc00000;	// Default PC
	cpu->inter = inter;
	cpu->registers = init_registers(REGISTER_INIT_VALUE);
	cpu->next_instruction = new_instruction(0x0);
	return cpu;
}

void run_next_instruction(cpu_t *cpu)
{
	instruction_t *instruction;
	instruction = new_instruction(cpu->inter->load32(cpu->inter, cpu->pc));
	cpu->next_instruction = new_instruction(cpu->inter->load32(cpu->inter, cpu->pc+4));
	cpu->pc += 4;
	decode_exec(cpu, instruction);
}

uint32_t cpu_load32(cpu_t *cpu, uint32_t addr)
{
	return cpu->inter->load32(cpu->inter, addr);
}

void cpu_store32(cpu_t *cpu, uint32_t addr, uint32_t value)
{
	cpu->inter->store32(cpu->inter, addr, value);
}

void decode_exec(cpu_t *cpu, instruction_t *instruction)
{
	if(instruction->opcode == 0b000000)
	{
		if (instruction->subopcode == 0b000000)
		{
			op_sll(cpu->registers, instruction);
		}else if(instruction->subopcode == 0b100101)
		{
			op_or(cpu->registers, instruction);
		}
		else{
			fprintf(stderr, "Error: Unknown instruction %08x\n", instruction->opcode);
			exit(1);
		}
	}
	else if(instruction->opcode == 0b001111)
		op_lui(cpu->registers, instruction);
	else if(instruction->opcode == 0b001101)
		op_ori(cpu->registers, instruction);
	else if(instruction->opcode == 0b101011)
		op_sw(cpu->inter, cpu->registers, instruction);
	else if(instruction->opcode == 0b001001)
		op_addiu(cpu->registers, instruction);
	else if(instruction->opcode == 0b000010)
		op_j(&(cpu->pc), instruction);
	else
	{
		printf("Unknown opcode: 0x%x\n", instruction->opcode);
		exit(1);
	}
}

// Debuging

void print_all_registers(cpu_t *cpu)
{
	int i;
	for(i = 0; i < 32; i++){
		printf("R%d: 0x%08x\n", i, cpu->registers[i]->value);
	}
}