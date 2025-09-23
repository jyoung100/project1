#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
	int i = 1;
	pid_t pid = fork();
	if(pid == 0){
		setenv("LD_PRELOAD", "./mem_shim.so", 1);
		execvp(argv[i], &argv[i]);
		_exit(127);
	}

	waitpid(pid, NULL, 0);
	
	return 0;
}


