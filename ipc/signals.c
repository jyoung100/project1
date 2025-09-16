#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int *x = NULL;

void sighandler(int signum) {
    printf("Ha ha, I won't die.\n");
}

void fixX(int signum) {
    printf("fixing x...\n");
    x = malloc(sizeof(int));
    exit(EXIT_FAILURE);
}

int main()
{
    signal(SIGINT, sighandler);
    signal(SIGTERM, sighandler);
    signal(SIGSEGV, fixX);

    *x = 546;

    while (true) {
        printf("I'm wasting cycles! %d\n", getpid());
        sleep(5);
        
        
    }
}
