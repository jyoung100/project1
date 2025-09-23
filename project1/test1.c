#define _GNU_SOURCE
#include <stddef.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv){


    void *p =  malloc(10);
    void *g = malloc(100);
    void *x = realloc(p, 123);

    free(x);

    free(NULL);

    return 0;
    
}