#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sig_cld(int signo) {
  pid_t pid;
  int status;
  printf("SIGCLD received\n");
  if (signal(SIGCLD, sig_cld) == SIG_ERR) {
    printf("signal error\n");
    exit(1);
  }
  if ((pid = wait(&status)) < 0) {
    printf("wait error\n");
    exit(1);
  }
  printf("pid=%d\n", pid);
}

int main() {
  pid_t pid;
  if (signal(SIGCLD, sig_cld) == SIG_ERR) {
    printf("signal error\n");
    exit(1);
  }
  if ((pid = fork()) < 0) {
    printf("fork error\n");
    exit(1);
  } else if (pid == 0) { // child
    sleep(2);
    _exit(0);
  }
  // parent
  pause();
  return 0;
}
