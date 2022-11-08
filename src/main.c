#include "bios.h"
#include "cpu.h"
#include "interconnect.h"

int main()
{
	bios_t	*bios;
	interconnect_t *inter;
	cpu_t	*cpu;
	int running;
	int cycle;

	bios = new_bios("bios/SCPH1001.BIN");
	inter = new_interconnect(bios);
	cpu = new_cpu(inter);
	running = 1;
	cycle = 0;
	while(running && cycle < 100){
		run_next_instruction(cpu);
		cycle++;
	}
	//print_all_registers(cpu);
}