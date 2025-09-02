

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    printf("before\n");
    pid_t p = fork();

    if (p == 0) {
        printf("I'm a child\n");
    } else {
        //do some work
        kill(p, SIGTERM);
        waitpid(p, NULL, 0);
        printf("I'm parental\n");
    }
    
    printf("after %d\n", p);
}