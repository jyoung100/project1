#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int agrc, char **argv){

	printf("Child");
	void *j = malloc(*argv[1]);

	return 0;
}
