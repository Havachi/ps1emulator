#include "range.h"

range_t *new_range(uint32_t start, uint32_t length, char *name)
{
	range_t *range;
	range = (range_t *)malloc(sizeof(range_t));
	if(range == NULL)
	{
		fprintf(stderr, "Error: Could not allocate memory for range\n");
		exit(1);
	}
	if(name == NULL)
		range->name = strdup("Unnamed range");
	else
		range->name = strdup(name);
	range->start = start;
	range->length = length;
	range->contains = range_contains;
	range->offset = get_offset;
	return (range);
}

bool	range_contains(range_t *range, uint32_t addr, uint32_t *offset)
{
	if(offset != NULL)
	{
		if (addr >= range->start && addr < range->start + range->length)
		{
			*offset = addr - range->start;
			return (true);
		}
	}
	fprintf(stderr, "Error: Could not find value in range %s\n", range->name);
	return (false);
}

uint32_t	get_offset(range_t *range, uint32_t addr)
{
	return (addr - range->start);
}