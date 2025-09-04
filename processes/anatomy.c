

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

extern char **environ;

void whereis(char *name, void *p);

int y = 56;
int uy;

int main(int argc, char **argv)
{
	int x = 12;

	//moves environ
	setenv("PATH","STUFF",0);
	
	int *px = malloc(sizeof(int));
	whereis("main", main);
	whereis("&y", &y);
	whereis("&x", &x);
	whereis("px", px);
	
	return EXIT_SUCCESS;	
}

void whereis(char *name, void *p)
{
	printf("%s = %p (main + %lx)\n", name, p,
		   ((uintptr_t)p - (uintptr_t)main));
}
