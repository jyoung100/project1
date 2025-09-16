#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//see also strtok_r and strsep

int main() {
  char *message = "When 900 years,,, old you, reach, look as good, you will not.";
  char *buf = malloc(1024);
  memset(buf, 0, 1024);
  strcpy(buf, message);

  char *token = strtok(buf, ",");
  while (NULL != token) {
      printf("token: %s\n",token);
      token = strtok(NULL, ",");
  }
}
