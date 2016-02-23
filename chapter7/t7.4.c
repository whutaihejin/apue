#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("i < argc condition\n");
  for (int i = 0; i < argc; ++i) {
    printf("argv[%d]=%s\n", i, argv[i]);
  }
  printf("argv[i] != NULL condition\n");
  for (int i = 0; argv[i] != NULL; ++i) {
    printf("argv[%d]=%s\n", i, argv[i]);
  }
}
