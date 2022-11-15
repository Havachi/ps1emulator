#include "interconnect.h"

interconnect_t *new_interconnect(bios_t *bios, ram_t *ram)
{
	interconnect_t *interconnect;
	interconnect = (interconnect_t *)malloc(sizeof(interconnect_t));
	if(interconnect == NULL)
	{
		fprintf(stderr, "Error: Could not allocate memory for interconnect\n");
		exit(1);
	}
	interconnect->bios = bios;
	interconnect->ram = ram;
	interconnect->load32 = interconnect_load32;
	interconnect->store32 = interconnect_store32;
	interconnect->load16 = interconnect_load16;
	interconnect->store16 = interconnect_store16;
	interconnect->store8 = interconnect_store8;
	return (interconnect);
}

uint32_t interconnect_load32(interconnect_t *interconnect, uint32_t addr)
{
	uint32_t	offset;
	range_t		*bios_range;
	range_t		*ram_range;
	if (addr % 4 != 0)
	{
		fprintf(stderr, "Error: Address 0x%08x is not aligned\n", addr);
		exit(1);
	}
	addr = mask_region(addr);
	bios_range = BIOS_RANGE;
	ram_range = RAM_RANGE;

	if(bios_range->contains(bios_range, addr, &offset)){
		return (interconnect->bios->load32(interconnect->bios, offset));
	}else if(ram_range->contains(ram_range, addr, &offset)){
		return (interconnect->ram->load32(interconnect->ram, offset));
	}
	fprintf(stderr, "Error: Could not find value in range\n");
	free(bios_range);
	free(ram_range);
	exit(1);
}

void interconnect_store32(interconnect_t *interconnect, uint32_t addr, uint32_t value)
{
	uint32_t	offset;
	range_t		*sys_control_range;
	range_t		*ram_size_range;
	range_t		*cache_control_range;
	range_t		*ram_range;
	if (addr % 4 != 0)
	{
		fprintf(stderr, "Error: Address 0x%08x is not aligned\n", addr);
		exit(1);
	}
	interconnect = interconnect;
	addr = mask_region(addr);
	sys_control_range = SYS_CONTROL_RANGE;
	ram_size_range = RAM_SIZE_RANGE;
	cache_control_range = CACHE_CONTROL_RANGE;
	ram_range = RAM_RANGE;
	if(sys_control_range->contains(sys_control_range, addr, &offset)){
		if (offset == 0)
		{
			if(value != 0x1f000000)
			{
				fprintf(stderr,"Bad expension 1 | Base address 0x%08x\n", value);
				exit(1);
			}
		}
		else if (offset == 4)
		{
			if(value != 0x1f802000)
			{
				fprintf(stderr,"Bad expension 2 | Base address 0x%08x\n", value);
				exit(1);
			}
		}else{
			fprintf(stderr,"Unhandeled write to MEM_CONTROL\n");
		}
	}
	else if(ram_size_range->contains(ram_size_range, addr, &offset)){
		fprintf(stderr,"Unhandeled write to %s\n", ram_size_range->name);
	}
	else if(cache_control_range->contains(cache_control_range, addr, &offset)){
		fprintf(stderr,"Unhandeled write to %s\n", cache_control_range->name);
	}
	else if(ram_range->contains(ram_range, addr, &offset)){
		fprintf(stderr,"Unhandeled write to %s\n", ram_range->name);
	}
	free(sys_control_range);
	free(ram_size_range);
	free(cache_control_range);
	free(ram_range);
	fprintf(stderr,"\tUnhandeled store32 at 0x%08x\n", addr);
}

uint16_t interconnect_load16(interconnect_t *interconnect, uint32_t addr)
{
	interconnect = interconnect;
	fprintf(stderr,"Unhandeled load16 for 0x%08x\n", addr);
	return 0;
}

void interconnect_store16(interconnect_t *interconnect, uint32_t addr, uint16_t value)
{
	range_t *spu_range;
	uint32_t abs_addr;
	uint32_t offset;

	interconnect = interconnect;
	value = value;
	if (addr % 2 != 0)
	{
		fprintf(stderr, "Error(store16): Address 0x%08x is not aligned\n", addr);
		exit(1);
	}
	spu_range = SPU_RANGE;
	abs_addr = mask_region(addr);

	if(spu_range->contains(spu_range, abs_addr, &offset))
	{
		fprintf(stderr,"Unhandeled write to %s\n offset %08x", spu_range->name, offset);
		return;
	}
	fprintf(stderr, "Unhandeled store16 into 0x%08x\n", addr);

}

void interconnect_store8(interconnect_t *interconnect, uint32_t addr, uint8_t value)
{
	uint32_t abs_addr;
	uint32_t offset;
	range_t *expansion_2_range;
	interconnect = interconnect;
	value = value;

	expansion_2_range = EXPANSION_2_RANGE;
	abs_addr = mask_region(addr);

	if (expansion_2_range->contains(expansion_2_range, abs_addr, &offset))
	{
		fprintf(stderr,"Unhandeled write to %s\n offset", expansion_2_range->name);
		return;
	}
	fprintf(stderr, "Unhandeled store8 into 0x%08x\n", addr);
}

uint32_t	mask_region(uint32_t addr)
{
	uint32_t region_mask[8] = {
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
	0x7fffffff,
	0x1fffffff,
	0xffffffff, 0xffffffff};

	uint64_t index = (addr >> 29);
	return (addr & region_mask[index]);
}