#include <stdio.h>
int main(int argc, char *argv[]) {
  int i;
  char **ptr;
  extern char **environ;

  printf("begin------------\n");
  for (i = 0; i < argc; i++) {
    printf("argv[%d]: %s\n", i, argv[i]);
  }
  printf("------------\n");
  for (ptr = environ; *ptr != NULL; ptr++) {
    printf("%s\n", *ptr);
  }
  printf("end------------\n");
  return 0;
}
