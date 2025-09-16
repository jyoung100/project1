#define _GNU_SOURCE
#include <stddef.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>


int malloc_count = 0;
int resolving = 0;
void *(*original_malloc) (size_t size) = NULL;

void __attribute__((destructor)) library_cleanup() {
	printf("Number of calls to malloc: %d\n", malloc_count);
	printf("Unloading library.\n");
}


void *malloc(size_t size){
    if(!original_malloc){
        if(resolving)
            return NULL;
    	resolving = 1;
		original_malloc = dlsym(RTLD_NEXT , "malloc");
    	resolving = 0;
    	if(!original_malloc)
        	return NULL;
    }
	++malloc_count;
	return original_malloc(size);
}

