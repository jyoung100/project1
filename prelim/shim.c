#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

void __attribute__((constructor)) library_init() {
    printf("Loading library.\n");
}

void __attribute__((destructor)) library_cleanup() {
    printf("Unloading library.\n");
}

int rand(void) {
    int (*original_rand)(void) = dlsym(RTLD_NEXT, "rand");
    return original_rand() % 100;
}
