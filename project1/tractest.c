#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{

	clock_t c = clock();

	printf("Time: %ld\n", c);

	printf("Arg[1]: %d\n", *argv[1]);
	
	return 0;
}
