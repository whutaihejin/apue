#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// one handler for both signals
void sig_usr(int);

int main() {
  if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
    printf("can't catch SIGUSR1\n");
    exit(0);
  }
  if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
    printf("can't catch SIGUSR2\n");
    exit(0);
  }
  for (;;) {
    pause();
  }
}

void sig_usr(int signo) {
  if (signo == SIGUSR1) {
    printf("received SIGUSR1\n");
  } else if (signo == SIGUSR2) {
    printf("received SIGUSR2\n");
  } else {
    printf("received %d\n", signo);
  }
}
