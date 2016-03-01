#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void usage();

char buf[] = "a write to stdout\n";
int globval = 6;

int main(int argc, char *argv[]) {
  
  int autoval = 88;
  int sleep_value;
  pid_t pid;
  
  if (argc != 2) {
    usage();
    exit(-1);
  }
  sleep_value = atoi(argv[1]);
  if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
    printf("write occurs errer, eixt.\n");
    exit(-1);
  }
  printf("before fork\n");
  if ((pid = fork()) <0) {
  } else if (pid == 0) {
    // child process
    globval++;
    autoval++;
  } else {
    sleep(sleep_value);
  }
  printf("pid = %ul, globval = %d, autoval = %d\n",
        getpid(), globval, autoval);
  return 0;
}

void usage() {
  printf("usage:\n");
  printf("  ./t8.2 <sleep_time> int value like 2.\n");
}
