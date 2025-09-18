#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
//#include "mem_shim.c"
#define NUMBER_OF_NUMBERS 5

int main(int argc, char **argv)
{
  	int *mem = (int*)(malloc(10));

	void *p = malloc(12);
	void *x = malloc(100);
	void *c = (int*)(calloc(50, sizeof(int)));
	void *d = malloc(7);
	int *mem1 = (int*)(malloc(30));

	int*mem2 = (int*)(calloc(5, sizeof(int)));
	
	free(mem2);

	realloc(mem, 20);
	return 0;

}

