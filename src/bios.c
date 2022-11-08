#include "bios.h"

bios_t *new_bios(char *path)
{
	int f;
	uint8_t *data;
	long size;
	bios_t *bios;

	size = 0;
	bios = NULL;
	data = NULL;
	f = -1;

	bios = (bios_t *)malloc(sizeof(bios_t));
	if (bios == NULL) {
		fprintf(stderr, "Error: Could not allocate memory for bios\n");
		exit(1);
	}
	data = (uint8_t *)malloc(BIOS_SIZE);
	if (data == NULL) {
		fprintf(stderr, "Error: Could not allocate memory for bios data\n");
		exit(1);
	}
	f = open(path, O_RDONLY);
	if (f == -1) {
		fprintf(stderr, "Error: Could not open the BIOS file at %s\n", path);
		exit(1);
	}
	size = read(f, data, BIOS_SIZE);
	if (size != BIOS_SIZE) {
		fprintf(stderr, "Error: BIOS file is not %iKB\n", BIOS_SIZE/1024);
		exit(1);
	}
	close(f);
	printf("BIOS file is %iKB\n", BIOS_SIZE/1024);
	bios->data = data;
	bios->load32 = bios_load32;
	return (bios);
}
uint32_t bios_load32(bios_t *bios, uint32_t offset)
{
	uint32_t data;

	uint32_t b0 = bios->data[offset + 0];
	uint32_t b1 = bios->data[offset + 1];
	uint32_t b2 = bios->data[offset + 2];
	uint32_t b3 = bios->data[offset + 3];

	data = b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
	return (data);
}