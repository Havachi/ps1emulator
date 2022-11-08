#include "interconnect.h"

interconnect_t *new_interconnect(bios_t *bios)
{
	interconnect_t *interconnect;
	interconnect = (interconnect_t *)malloc(sizeof(interconnect_t));
	if(interconnect == NULL)
	{
		fprintf(stderr, "Error: Could not allocate memory for interconnect\n");
		exit(1);
	}
	interconnect->bios = bios;
	interconnect->load32 = interconnect_load32;
	interconnect->store32 = interconnect_store32;
	return (interconnect);
}

uint32_t interconnect_load32(interconnect_t *interconnect, uint32_t addr)
{
	uint32_t	offset;
	range_t		*bios_range;
	if (addr % 4 != 0)
	{
		fprintf(stderr, "Error: Address 0x%08x is not aligned\n", addr);
		exit(1);
	}
	bios_range = BIOS_RANGE;
	offset = bios_range->contains(bios_range, addr);
	free(bios_range);
	return (interconnect->bios->load32(interconnect->bios, offset));

}

void interconnect_store32(interconnect_t *interconnect, uint32_t addr, uint32_t value)
{
	uint32_t	offset;
	range_t		*range;
	if (addr % 4 != 0)
	{
		fprintf(stderr, "Error: Address 0x%08x is not aligned\n", addr);
		exit(1);
	}
	interconnect = interconnect;
	if((addr & 0xFFFF0000) == 0xFFFE0000)
	{
		range = CACHE_CONTROL;
		offset = range->contains(range, addr);
		free(range);
		fprintf(stderr,"Unhandeled write to CACHE_CONTROL\n");
	}
	else if((addr & 0xFFFF0000) == 0x1f800000)
	{
		range = RAM_SIZE;
		offset = range->contains(range, addr);
		free(range);
		fprintf(stderr,"Unhandeled write to RAM_SIZE\n");
		return;
	}
	else
	{
		range = MEM_CONTROL;
		offset = range->contains(range, addr);
		free(range);
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
			return;
		}
	}


	fprintf(stderr,"Unhandeled store32 at 0x%08x\n", addr);
}