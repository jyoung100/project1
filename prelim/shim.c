#define _GNU_SOURCE
#include <stddef.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>


int malloc_count = 0;
static int resolving = 0;

void __attribute__((constructor)) library_init() {
	printf("Malloc_count: %d\n", malloc_count);
	printf("Loading library.\n");
}

void __attribute__((destructor)) library_cleanup() {
	printf("Number of calls to malloc: %d\n", malloc_count);
	printf("Unloading library.\n");
}

void *(*original_malloc) (size_t size) = NULL;

void *malloc(size_t size){

	original_malloc = dlsym(RTLD_NEXT , "malloc");
	void * ptr = original_malloc(size);
	++malloc_count;
	return ptr;

}

int rand(void) {
	int (*original_rand)(void) = dlsym(RTLD_NEXT, "rand");
	return original_rand() % 1000;
}
