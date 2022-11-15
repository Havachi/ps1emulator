#include "cpu.h"

cpu_t *new_cpu(interconnect_t *inter)
{
	cpu_t *cpu = malloc(sizeof(cpu_t));
	cpu->pc = 0xbfc00000;	// Default PC
	cpu->inter = inter;
	cpu->registers = init_registers(REGISTER_INIT_VALUE, 32);
	cpu->cop0_registers = init_registers(0,32);
	cpu->out_regs = cpu->registers;
	cpu->load = malloc(sizeof(load_t));
	cpu->load->index = 0;
	cpu->load->value = 0;
	cpu->instruction = new_instruction(0x0, 0);
	cpu->next_instruction = new_instruction(0x0, 0);
	cpu->set_reg = set_reg;
	cpu->set_copreg = set_copreg;
	return cpu;
}

void run_next_instruction(cpu_t *cpu)
{
	cpu->set_reg(cpu, cpu->load->index, cpu->load->value);
	cpu->load->index = 0;
	cpu->load->value = 0;
	cpu->instruction = new_instruction(cpu->next_instruction->raw_instruction, cpu->next_instruction->found_at_pc);
	cpu->next_instruction = new_instruction(cpu->inter->load32(cpu->inter, cpu->pc), cpu->pc);
	cpu->pc += 4;

	decode_exec(cpu, cpu->instruction);
	cpy_out_regs(cpu);
}

uint32_t cpu_load32(cpu_t *cpu, uint32_t addr)
{
	return cpu->inter->load32(cpu->inter, addr);
}

void cpu_store32(cpu_t *cpu, uint32_t addr, uint32_t value)
{
	cpu->inter->store32(cpu->inter, addr, value);
}

void cpu_store16(cpu_t *cpu, uint32_t addr, uint16_t value)
{
	cpu->inter->store16(cpu->inter, addr, value);
}

void decode_exec(cpu_t *cpu, instruction_t *instruction)
{
	printf("Instruction @%08x -> %08x \t", instruction->found_at_pc ,instruction->raw_instruction);
	if(instruction->opcode == 0b000000)
	{
		if (instruction->subopcode == 0b000000)
			op_sll(cpu, instruction);
		else if (instruction->subopcode == 0b001000)
			op_jr(cpu, instruction);
		else if(instruction->subopcode == 0b100001)
			op_addu(cpu, instruction);
		else if(instruction->subopcode == 0b100101)
			op_or(cpu, instruction);
		else if(instruction->subopcode == 0b101011)
			op_sltu(cpu, instruction);
		else{
			fprintf(stderr, "Error: Unknown instruction %08x\n", instruction->opcode);
			exit(1);
		}
	}
	else if(instruction->opcode == 0b000010)
		op_j		(cpu, instruction);
	else if(instruction->opcode == 0b000011)
		op_jal		(cpu, instruction);
	else if(instruction->opcode == 0b000101)
		op_bne		(cpu, instruction);
	else if(instruction->opcode == 0b001000)
		op_addi		(cpu, instruction);
	else if(instruction->opcode == 0b001001)
		op_addiu	(cpu, instruction);
	else if(instruction->opcode == 0b001100)
		op_andi		(cpu, instruction);
	else if(instruction->opcode == 0b001101)
		op_ori		(cpu, instruction);
	else if(instruction->opcode == 0b001111)
		op_lui		(cpu, instruction);
	else if(instruction->opcode == 0b010000)
		op_cop0		(cpu, instruction);
	else if(instruction->opcode == 0b100011)
		op_lw		(cpu, instruction);
	else if(instruction->opcode == 0b101000)
		op_sb 		(cpu, instruction);
	else if(instruction->opcode == 0b101001)
		op_sh 		(cpu, instruction);
	else if(instruction->opcode == 0b101011)
		op_sw		(cpu, instruction);
	else
	{
		printf("Unknown instruction: 0x%08x\n", instruction->raw_instruction);
		exit(1);
	}
}

void set_reg(cpu_t *cpu, uint32_t index, uint32_t value)
{
	reg_t *reg;

	reg = cpu->out_regs[index];
	reg->write(reg, value);
	cpu->out_regs[0]->write(cpu->out_regs[0], 0);
}

void set_copreg(cpu_t *cpu, uint32_t index, uint32_t value)
{
	reg_t *reg;

	reg = cpu->cop0_registers[index];
	reg->write(reg, value);
}

void cpy_out_regs(cpu_t *cpu)
{
	int i;
	i = 0;

	while(i < 32)
	{
		cpu->registers[i]->write(cpu->registers[i], cpu->out_regs[i]->read(cpu->out_regs[i]));
		i++;
	}
}