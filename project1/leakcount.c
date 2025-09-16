#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
//#include "mem_shim.c"
#define NUMBER_OF_NUMBERS 5

int main(int argc, char **argv)
{
  	int *mem = (int*)(malloc(10));
	int *mem1 = (int*)(malloc(30));
	void *p = malloc(10);
	//printf("Mem[0] Address: %p\n", mem);
	//printf("Mem1[0] Address: %p\n", mem1);
	//printf("Malloc Calls: %d\n", malloc_count);
}