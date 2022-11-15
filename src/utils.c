#include "utils.h"

int32_t	add_overflow(int32_t *result, int32_t a, int32_t b)
{
	(*result) = a + b;
	if(a > 0 && b > 0 && *result < 0)
		return -1;
	if(a < 0 && b < 0 && *result > 0)
		return -1;
	return 0;
}