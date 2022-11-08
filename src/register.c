#include "register.h"

reg_t	*new_register(reg_t *reg, uint32_t init_value)
{
	reg = malloc(sizeof(*reg));
	reg->value = init_value;
	return reg;
}
reg_t	**init_registers(uint32_t init_value)
{
	int i;
	reg_t **registers;
	registers = malloc(sizeof(*registers)*32);
	i = 0;
	while(i < 32){
		if(i == 0)
			registers[i] = new_register(registers[i], 0x0);
		else
			registers[i] = new_register(registers[i], init_value);
		if(registers[i] == NULL){
			fprintf(stderr,"Error: Could not allocate memory for register %d", i);
			exit(1);
		}
		i++;
	}
	return (registers);
}

uint32_t read_register(int index, reg_t **registers)
{
	return registers[index]->value;
}

reg_t **write_register(int index, uint32_t value, reg_t **registers)
{
	registers[index]->value = value;
	registers[0]->value = 0;
	return registers;
}
