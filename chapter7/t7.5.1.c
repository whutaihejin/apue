#include <stdio.h>
int main(int argc, char *argv[], char *envp[]) {
  char **p = envp;
  for (int i = 0; p[i] != NULL; ++p) {
    printf("%s\n", p[i]);
  }
  return 0;
}
