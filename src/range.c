#include "range.h"

range_t *new_range(uint32_t start, uint32_t length)
{
	range_t *range;
	range = (range_t *)malloc(sizeof(range_t));
	if(range == NULL)
	{
		fprintf(stderr, "Error: Could not allocate memory for range\n");
		exit(1);
	}
	range->start = start;
	range->length = length;
	range->contains = range_contains;
	return (range);
}

uint32_t range_contains(range_t *range, uint32_t addr)
{
	if (addr >= range->start && addr <= range->start + range->length)
	{
		return (addr - range->start);
	}
	fprintf(stderr, "Error: Could not find value in range\n");
	exit(1);
}