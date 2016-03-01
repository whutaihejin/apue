#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void usage();

int global_val = 6;

int main(int argc, char *argv[]) {
  
  int auto_val = 88;
  pid_t pid;
  int arg_val = 0;

  if (argc != 2) {
    usage();
    exit(0);
  }
  arg_val = atoi(argv[1]);

  printf("before vfork.\n");
  if ((pid = vfork()) < 0) {
    printf("vfork occurs error.\n");
    exit(0);
  } else if (pid == 0) {
    global_val++;
    auto_val++;
    arg_val == 1 ? _exit(0) : exit(0);
  }
  printf("pid = %ld, global_val = %d, auto_val = %d\n", (long)getpid(), global_val, auto_val);
  return 0;
}

void usage() {
  printf("usage:\n");
  printf("  ./t8.4 <int_value> which 1 for _exit(0) others for exit(0).\n");
}
