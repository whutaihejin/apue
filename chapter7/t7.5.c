#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char *argv[]) {
  if (!environ) {
    printf("environ is NULL\n");
    exit(0);
  }
  char** p = environ;
  for (int i = 0; p[i] != NULL; ++p) {
    printf("%s\n", p[i]);
  }
  return 0;
}
