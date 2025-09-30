#define _GNU_SOURCE
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wordexp.h>
#include <sys/reg.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

extern char **environ;

typedef struct {
    int call_num;
    int countr;
} call;

int compareSyscallNum(const void* a, const void* b){
	call *syscallA = (call*) a;
	call *syscallB = (call*) b;
	return (syscallA -> call_num - syscallB -> call_num);
}

int main(int argc, char **argv) {

    pid_t child = fork();
    int counter = 0;
    call calls[10000] = {0};

    if (child == 0) {
        if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
            perror("ptrace(TRACEME)");
            _exit(1);
        }
        wordexp_t we;
        int wrc = wordexp(argv[1], &we, WRDE_NOCMD);
        if (wrc != 0 || we.we_wordc == 0) {
            fprintf(stderr, "failed to parse command string\n");
            _exit(1);
        }

        raise(SIGSTOP);
        execvp(we.we_wordv[0], we.we_wordv);
        
        perror("execvp");
        wordfree(&we);
        exit(1);
    }
    else{
        bool loc = true;
        bool called  = false;
        int status, curr_syscall;

        waitpid(child, &status, 0);

        ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);

        while(1){
            if(WIFEXITED(status) || WIFSIGNALED(status)){
                break;
	      }

	    ptrace(PTRACE_SYSCALL, child, NULL, NULL);
       	    waitpid(child, &status, 0);

	    if(WIFSTOPPED(status) && (WSTOPSIG(status) & 0x80)){

		    if(loc == true){
			    curr_syscall = ptrace(PTRACE_PEEKUSER, child, sizeof(long)*ORIG_RAX, NULL);
                for(int i = 0; i < counter; i++){
				    if(calls[i].call_num == curr_syscall){
					    calls[i].countr++; called = true; break;
				    }
			    }
			    if(!called){
				    calls[counter].call_num = curr_syscall; calls[counter].countr = 1; counter++;
			    }
		loc = false;
		    }
            else{
                loc = true;
        }
	    }
	}

	FILE* outputFile = fopen(argv[2], "w");
 
	qsort(calls, counter, sizeof(call), compareSyscallNum);
	for(int i = 0; i < counter; i++){
		fprintf(outputFile, "%d\t%d\n", calls[i].call_num, calls[i].countr);
	}
	fclose(outputFile);
       	}
        return 0;
    }
