

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int x = 56;

int main()
{
    printf("before\n");
    pid_t p = fork();
    x++;
    if (p == 0) {
        printf("I'm a child - %d (%p)\n", x, &x);
    } else {
        //do some work
        //kill(p, SIGTERM);
        waitpid(p, NULL, 0);
        printf("I'm parental - %d (%p)\n", x, &x);
    }
    
    printf("after %d\n", p);
}