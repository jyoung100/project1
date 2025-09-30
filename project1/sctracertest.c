#define _GNU_SOURCE
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wordexp.h>
#include <sys/reg.h>
#include <signal.h>
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

int main(int argc, char **argv) {

    //create child process
    pid_t child = fork();
    if (child == -1) {
        perror("fork");
        return 1;
    }
    //create array to hold systems calls
    call calls[10000];
    //count of system calls
    int count = 0;

    if (child == 0) {
        if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
            perror("ptrace(TRACEME)");
            _exit(1);
        }
        //use wordexp to create an expanded string containing target program and arguments
        wordexp_t we;
        wordexp(argv[1], &we, WRDE_NOCMD);

        raise(SIGSTOP); 
        //exec to child process, bring arguments
        execvp(we.we_wordv[0], we.we_wordv);
        perror("execvp");
        wordfree(&we);
        _exit(1);
    } else {

        int status = 0;
        //wait for child
        waitpid(child, &status, 0);
        //stop at first system call
        ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);
        //create mapping for system calls
        enum {SYSMAP_SIZE = 3000};
        int sys_index[SYSMAP_SIZE];
        for (int i = 0; i < SYSMAP_SIZE; i++) {
            sys_index[i] = -1;
        }
        //create a boolean to determine if the call is on entry
        bool on_entry = false; 

        while (1) {

            //exit if child has exited
            if (WIFEXITED(status) || WIFSIGNALED(status)) {break;}

            //wait for system call
            ptrace(PTRACE_SYSCALL, child, NULL, NULL);
            waitpid(child, &status, 0);

            //ensure its a system call
            if (WIFSTOPPED(status) && (WSTOPSIG(status) & 0x80)) {
                //flip the boolean
                on_entry = !on_entry;
                
                if (on_entry) {
                    //grab the system call number
                    long sc = ptrace(PTRACE_PEEKUSER, child, sizeof(long) * ORIG_RAX, NULL);

                    //update mapping
                    int idx = sys_index[sc];
                    if (idx >= 0) {
                        calls[idx].countr += 1;
                    } else {
                        calls[count].call_num = (int)sc;
                        calls[count].countr = 1;
                        sys_index[sc] = count;
                        count++;
                    }
                }
            }
        }

        //use bubble sort to sort calls ascending
        for (int i = 0; i < count; i++) {
            for (int j = 0; j + 1 < count; j++) {
                if (calls[j].call_num > calls[j+1].call_num) {
                    call tmp = calls[j];
                    calls[j] = calls[j+1];
                    calls[j+1] = tmp;
                }
            }
        }

        //open output file
        FILE *out = fopen(argv[2], "w");

        //write all system calls
        for (int i = 0; i < count; i++) {
            fprintf(out, "%d\t%d\n", calls[i].call_num, calls[i].countr);
        }
        fclose(out);
    }

    return 0;
}
