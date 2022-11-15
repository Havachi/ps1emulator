#ifndef CPU_H
#define CPU_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "interconnect.h"
#include "instruction.h"
#include "opcode.h"
#include "register.h"

typedef struct load_s{
		uint32_t	index;
		uint32_t	value;
}load_t;

typedef struct cpu_s
{
	uint32_t		pc;
	interconnect_t	*inter;
	reg_t			**registers;
	reg_t			**out_regs;
	reg_t			**cop0_registers;
	instruction_t	*instruction;
	instruction_t	*next_instruction;
	load_t			*load;
	void			(*set_reg)(struct cpu_s*, uint32_t, uint32_t);
	void			(*set_copreg)(struct cpu_s*, uint32_t, uint32_t);
}cpu_t;

cpu_t		*new_cpu(interconnect_t *inter);
void		run_next_instruction(cpu_t *cpu);
uint32_t	cpu_load32(cpu_t *cpu, uint32_t addr);
void		cpu_store32(cpu_t *cpu, uint32_t addr, uint32_t value);
void		decode_exec(cpu_t *cpu, instruction_t *instruction);
void		set_reg(cpu_t *cpu, uint32_t index, uint32_t value);
void		set_copreg(cpu_t *cpu, uint32_t index, uint32_t value);
void		cpy_out_regs(cpu_t *cpu);

#endif