#ifndef OPCODE_H
#define OPCODE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "instruction.h"
#include "register.h"
#include "interconnect.h"
#include "utils.h"
#include "cpu.h"

//forward declaration: bad
typedef struct cpu_s cpu_t;

//Processors ops
void	op_lui(cpu_t *cpu, instruction_t *instruction);
void	op_andi(cpu_t *cpu, instruction_t *instruction);
void	op_ori(cpu_t *cpu, instruction_t *instruction);
void	op_sw(cpu_t *cpu, instruction_t *instruction);
void	op_lw(cpu_t *cpu, instruction_t *instruction);
void	op_addi(cpu_t *cpu, instruction_t *instruction);
void	op_addiu(cpu_t *cpu, instruction_t *instruction);
void	op_j(cpu_t *cpu, instruction_t *instruction);
void	op_bne(cpu_t *cpu, instruction_t *instruction);
void	op_sb(cpu_t *cpu, instruction_t *instruction);
void	op_sh(cpu_t *cpu, instruction_t *instruction);
void	op_jal(cpu_t *cpu, instruction_t *instruction);
//SPECIAL ops
void	op_sll(cpu_t *cpu, instruction_t *instruction);
void	op_or(cpu_t *cpu, instruction_t *instruction);
void	op_sltu(cpu_t *cpu, instruction_t *instruction);
void	op_addu(cpu_t *cpu, instruction_t *instruction);
void	op_jr(cpu_t *cpu, instruction_t *instruction);
//Coprocessors
void	op_cop0(cpu_t *cpu, instruction_t *instruction);

//Coprocessor 0 ops
void op_mtc0(cpu_t *cpu, instruction_t *instruction);

//kinda utils
void	branch(cpu_t *cpu, uint32_t offset);
void	jump(cpu_t *cpu, instruction_t *instruction);
#endif