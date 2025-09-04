#include <stdio.h>

#define MAXREAD 2048

int main()
{

	char * poutput;
	char output[MAXREAD];
	FILE *pipe = popen("ls -al","r");

	if (pipe == NULL) perror("couldn't open pipe.");

  	while ((poutput = fgets(output, MAXREAD, pipe)) != NULL)
  	{
		printf("OUTPUT => %s",poutput);
  	}

	pclose(pipe); 
}
