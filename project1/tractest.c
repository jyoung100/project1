#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{

	//printf("Child Process ran me\n");
	
	//printf("Argv[1]: %s\n", argv[1]);

	clock_t c = clock();

	printf("Time: %ld\n", c);


	
	return 0;
}