#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(int argc, char *argv[]) {
  pid_t pid;
  if ((pid = fork()) < 0) {
    printf("fork error.\n");
    exit(0);
  } else if (pid == 0) {
    if (execle("/usr/bin/t8.10.echo", 
          "t8.10.echo", "my_arg1", "MY_ARG2", (char *)0, env_init) < 0) {
      printf("execle error.\n");
    }
  }

  if (waitpid(pid, NULL, 0) < 0) {
    printf("wait error.\n");
  }

  if ((pid = fork()) < 0) {
    printf("fork error.\n");
  } else if (pid == 0) {
    if (execlp("t8.10.echo", "t8.10.echo", "only 1 arg", (char *)0) < 0) {
      printf("execlp error.\n");
    }
  }
  return 0;
}
