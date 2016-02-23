#include <stdio.h>
#include <stdlib.h>

void exit_handler() {
  printf("this is exit_handler\n");
}

void exit_echo() {
  printf("this is exit_echo\n");
}

int main(int argc, char *argv[]) {
  if (atexit(exit_handler) != 0) {
    printf("register exit_handler failed!\n");
  }
  if (atexit(exit_echo) != 0) {
    printf("register exit_echo failed!\n");
  }
  if (atexit(exit_echo) != 0) {
    printf("register exit_echo failed!\n");
  }
  printf("main done!\n");
  return 0;
}
