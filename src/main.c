#include "bios.h"
#include "ram.h"
#include "cpu.h"
#include "interconnect.h"

int main()
{
	bios_t	*bios;
	ram_t	*ram;
	interconnect_t *inter;
	cpu_t	*cpu;
	int running;
	int cycle;

	bios = new_bios("bios/SCPH1001.BIN");
	ram = new_ram(RAM_SIZE);
	inter = new_interconnect(bios,ram);
	cpu = new_cpu(inter);
	running = 1;
	cycle = 0;
	while(running){
		run_next_instruction(cpu);
		cycle++;
	}
	//print_all_registers(cpu);
}