#ifndef CPU_H
#define CPU_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "interconnect.h"
#include "instruction.h"
#include "opcode.h"
#include "register.h"

typedef struct cpu_s
{
	uint32_t		pc;
	interconnect_t	*inter;
	reg_t			**registers;
	uint32_t		(*load32)(struct cpu_s*, uint32_t);
	instruction_t	*next_instruction;
}cpu_t;

cpu_t *new_cpu(interconnect_t *inter);
void run_next_instruction(cpu_t *cpu);
uint32_t cpu_load32(cpu_t *cpu, uint32_t addr);
void cpu_store32(cpu_t *cpu, uint32_t addr, uint32_t value);
void decode_exec(cpu_t *cpu, instruction_t *instruction);

// Debuging
void print_all_registers(cpu_t *cpu);
#endif