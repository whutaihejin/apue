#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void sig_usr(int signo);
int main(int argc, char *argv[]) {
  
  int flag = 0;
  int interval = 2;

  if (argc == 2) {
    interval = strtol(argv[1], NULL, 10);
  }

  if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
    printf("can't catch SIGUSR1\n");
  }
  if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
    printf("can't catch SIGUSR2\n");
  }
  for (;;) {
    sleep(interval);
    flag += 1;
    (flag & 0x01) ? kill(getpid(), SIGUSR1) : raise(SIGUSR2);
  }
  return 0;
}

void sig_usr(int signo) {
  if (signo == SIGUSR1) {
    printf("catch SIGUSR1\n");
  } else if (signo == SIGUSR2) {
    printf("catch SIGUSR2\n");
  }else {
    printf("unknown signal number %d\n", signo);
  }
}
