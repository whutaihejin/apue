#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void usage();

int main(int argc, char *argv[]) {
  pid_t pid;
  int sleep_val;

  if (argc != 2) {
    usage();
    exit(0);
  }
  sleep_val = atoi(argv[1]);

  if ((pid = fork()) < 0) {
    printf("fork error.\n");
    exit(0);
  } else if (pid == 0) { // first child
    if ((pid = fork()) < 0) {
      printf("fork error.\n");
      exit(0);
    } else if (pid > 0) {
      exit(0);
    }
    // second child
    sleep(sleep_val);
    printf("second child, parent pid = %ld\n", (long)getppid());
    exit(0);
  }

  if (waitpid(pid, NULL, 0) != pid) {
    printf("waitpid error.\n");
  }
  return 0;
}

void usage() {
  printf("usage:\n");
  printf("  ./t8.6.2 <int_value> for sleep time\n");
}
