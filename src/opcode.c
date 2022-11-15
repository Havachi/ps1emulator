#include "opcode.h"

void	op_lui(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t imm = instruction->imm_value;
	uint32_t reg_index = instruction->t;

	uint32_t value = imm << 16;
	cpu->set_reg(cpu, reg_index, value);
	printf("lui $%d, 0x%08x\n", reg_index, imm);
}

void	op_ori(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t imm = instruction->imm_value;
	uint32_t reg_index = instruction->t;
	uint32_t reg_index2 = instruction->s;


	uint32_t value = cpu->registers[reg_index2]->read(cpu->registers[reg_index2]) | imm;
	cpu->set_reg(cpu, reg_index, value);

	printf("ori $%d, $%d, 0x%08x\n", reg_index, reg_index, imm);

}

void	op_or(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t t = instruction->t;
	uint32_t s = instruction->s;
	uint32_t d = instruction->d;

	uint32_t value = cpu->registers[s]->read(cpu->registers[s]) | cpu->registers[t]->read(cpu->registers[t]);
	cpu->set_reg(cpu, d, value);
	printf("or $%d, $%d, $%d\n", d, s, t);
}

void	op_sw(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t sr = cpu->cop0_registers[12]->read(cpu->cop0_registers[12]);

	if((sr & 0x10000) != 0)
	{
		printf("sw: Ignoring store while cache is isolated\n");
		return;
	}
	uint32_t imm = instruction->imm_se_value;
	uint32_t t = instruction->t;
	uint32_t s = instruction->s;
	printf("sw $%d, 0x%08x($%d)\n", t, imm, s);

	uint32_t value = cpu->registers[t]->read(cpu->registers[t]);
	uint32_t addr = cpu->registers[s]->read(cpu->registers[s]) + imm;

	cpu->inter->store32(cpu->inter, addr, value);

}

void	op_lw(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t sr = cpu->cop0_registers[12]->read(cpu->cop0_registers[12]);

	if((sr & 0x10000) != 0)
	{
		printf("lw: Ignoring store while cache is isolated\n");
		return;
	}
	uint32_t imm = instruction->imm_se_value;
	uint32_t t = instruction->t;
	uint32_t s = instruction->s;
	printf("lw $%d, 0x%08x($%d)\n", t, imm, s);

	uint32_t addr = cpu->registers[s]->read(cpu->registers[s]) + imm;
	uint32_t value = cpu->inter->load32(cpu->inter, addr);

	cpu->load->index = t;
	cpu->load->value = value;
}

void	op_sll(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t shift = instruction->shift;
	uint32_t t = instruction->t;
	uint32_t d = instruction->d;

	uint32_t value = cpu->registers[t]->read(cpu->registers[t]) << shift;

	cpu->set_reg(cpu, d, value);

	printf("sll $%d, $%d, 0x%08x\n", d, t, shift);
}

void	op_addiu(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t imm = instruction->imm_se_value;
	uint32_t t = instruction->t;
	uint32_t s = instruction->s;

	uint32_t value = cpu->registers[s]->read(cpu->registers[s]) + imm;

	cpu->set_reg(cpu, t, value);

	printf("addiu $%d, $%d, 0x%08x\n", t, s, imm);
}

void	op_j(cpu_t *cpu, instruction_t *instruction)
{
	jump(cpu, instruction);
	printf("j 0x%08x\n", instruction->imm_jump);
}

void	jump(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t imm = instruction->imm_jump;
	cpu->pc = (cpu->pc & 0xf0000000) | (imm << 2);
}

void	branch(cpu_t *cpu, uint32_t offset)
{
	offset = offset << 2;
	uint32_t pc = cpu->pc;
	pc += offset;
	pc -= 4;
	cpu->pc = pc;
}

void	op_bne(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t s = instruction->s;
	uint32_t t = instruction->t;
	uint32_t i = instruction->imm_se_value;

	uint32_t reg_s_val = cpu->registers[s]->read(cpu->registers[s]);
	uint32_t reg_t_val = cpu->registers[t]->read(cpu->registers[t]);

	if(reg_s_val != reg_t_val)
	{
		branch(cpu, i);
		printf("bne $%d, $%d, 0x%08x\n", s, t, i);
	}else
		printf("Skipped: bne $%d, $%d, 0x%08x\n", s, t, i);


}

void	op_addi(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t imm = instruction->imm_se_value;
	uint32_t t = instruction->t;
	uint32_t s = (int32_t)instruction->s;
	int32_t result;
	int32_t ret = add_overflow(&result, ((int32_t)cpu->registers[s]->read(cpu->registers[s])), imm);
	if(ret == -1){
		printf("ADDI(bou?) Overflow detected\n");
	}else{
		cpu->set_reg(cpu, t, (uint32_t)result);
	}
	printf("addi $%d, $%d, 0x%08x\n", t, s, imm);
}

void	op_cop0(cpu_t *cpu, instruction_t *instruction)
{
	if(instruction->cop_opcode == 0b00100)
		op_mtc0(cpu, instruction);
	else
		fprintf(stderr, "Unknown cop0 instruction: 0x%08x", instruction->raw_instruction);
}

void	op_mtc0(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t cpu_r = instruction->t;
	uint32_t cop_r = instruction->d;

	uint32_t value = cpu->registers[cpu_r]->read(cpu->registers[cpu_r]);

	if(cop_r == 3 || cop_r == 5 || cop_r == 6 || cop_r == 7 || cop_r == 9 || cop_r == 11){
		if(value != 0)
			fprintf(stderr, "Unhandled write to cop0 register %d", cop_r);
	}
	else if(cop_r == 12)
		cpu->set_copreg(cpu, cpu_r, value);
	else if(cop_r == 13){
		if(value != 0)
			fprintf(stderr, "Unhandled write to CAUSE register");
	}
	else
		fprintf(stderr, "Unhandled cop0 register: 0x%08x", cop_r);
	printf("mtc0 $%d $%d\n", cpu_r, cop_r);
}

void	op_sltu(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t s = instruction->s;
	uint32_t t = instruction->t;
	uint32_t d = instruction->d;

	uint32_t reg_s_val = cpu->registers[s]->read(cpu->registers[s]);
	uint32_t reg_t_val = cpu->registers[t]->read(cpu->registers[t]);

	uint32_t value = (reg_s_val < reg_t_val)? 1 : 0;

	cpu->set_reg(cpu, d, value);

	printf("sltu $%d, $%d, $%d\n", d, s, t);
}

void	op_addu(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t d = instruction->d;
	uint32_t s = instruction->s;
	uint32_t t = instruction->t;
	uint32_t v = cpu->registers[s]->read(cpu->registers[s]) + cpu->registers[t]->read(cpu->registers[t]);

	cpu->set_reg(cpu, d, v);

	printf("addu $%d, $%d, $%d\n", d, s, t);
}

void	op_sh(cpu_t *cpu, instruction_t *instruction)
{
	if((cpu->cop0_registers[12]->read(cpu->cop0_registers[12]) & 0x10000) != 0)
	{
		printf("sh: Ignoring store while cache is isolated\n");
		return;
	}
	uint32_t i = instruction->imm_se_value;
	uint32_t t = instruction->t;
	uint32_t s = instruction->s;

	uint32_t addr = cpu->registers[s]->read(cpu->registers[s]) + i;
	uint16_t value = cpu->registers[t]->read(cpu->registers[t]);

	cpu->inter->store16(cpu->inter, addr, value);
}

void	op_jal(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t ra = cpu->pc;
	cpu->registers[31]->write(cpu->registers[31], ra);
	jump(cpu, instruction);
	printf("jal 0x%08x\n", instruction->imm_jump);
}

void	op_andi(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t imm = instruction->imm_se_value;
	uint32_t t = instruction->t;
	uint32_t s = instruction->s;

	uint32_t value = cpu->registers[s]->read(cpu->registers[s]) & imm;

	cpu->set_reg(cpu, t, value);

	printf("andi $%d, $%d, 0x%08x\n", t, s, imm);
}

void	op_sb(cpu_t *cpu, instruction_t *instruction)
{
	if (cpu->cop0_registers[12]->read(cpu->cop0_registers[12]) & 0x10000)
	{
		printf("sb: Ignoring store while cache is isolated\n");
		return;
	}
	uint32_t i = instruction->imm_se_value;
	uint32_t t = instruction->t;
	uint32_t s = instruction->s;

	uint32_t addr = cpu->registers[s]->read(cpu->registers[s]) + i;
	uint8_t value = cpu->registers[t]->read(cpu->registers[t]);

	cpu->inter->store8(cpu->inter, addr, value);
}

void	op_jr(cpu_t *cpu, instruction_t *instruction)
{
	uint32_t s = instruction->s;
	cpu->pc = cpu->registers[s]->read(cpu->registers[s]);
	printf("jr $%d\n", s);
}