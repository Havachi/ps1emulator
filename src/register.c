#include "register.h"


reg_t		**init_registers(uint32_t init_value, int n)
{
	int i;
	reg_t **registers;

	if(n < 1)
	{
		fprintf(stderr, "Error: Number of registers must be greater than 0, everybody know that\n");
		exit(1);
	}

	registers = malloc(sizeof(*registers)*n);
	i = 0;
	while(i < n){
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

uint32_t	read_register(reg_t *reg)
{
	return (reg->value);
}

void		write_register(reg_t *reg, uint32_t value)
{
	reg->value = value;
}

reg_t		*new_register(reg_t *reg, uint32_t init_value)
{
	reg = malloc(sizeof(*reg));
	reg->value = init_value;
	reg->write = write_register;
	reg->read = read_register;
	return reg;
}
