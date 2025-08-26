#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main()
{
	uint16_t y = 0xFEED, x = 0xBEEF;
	uint16_t *z = malloc(sizeof(uint16_t));
	uint16_t *q = malloc(sizeof(uint16_t));
	uint16_t *p = &y;

	memcpy(q, p, sizeof(uint16_t));
	*z = (x & 0xFFF0) >> 4;
	y = (*p & 0x000F) | (*z << 4);
	p = &x;
	printf("%lx %lx %lx %hx %hx\n", z, p, &y, y++, *q);
	return 0;
}
