#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void pre_exit(int);

int main(int argc, char *argv[]) {
  pid_t pid;
  int status;

  // normal exit
  if ((pid = fork()) < 0) {
    printf("fork occurs error.\n");
    exit(0);
  } else if (pid == 0) {
    exit(7);
  }

  if (wait(&status) != pid) {
    printf("wait occurs error.\n");
  }
  pre_exit(status);

  // abnormal exit
  if ((pid = fork()) < 0) {
    printf("fork occurs error.\n");
  } else if (pid == 0) {
    abort();
  }

  if (wait(&status) != pid) {
    printf("wait occurs error.\n");
  }
  pre_exit(status);
  // signal exit
  if ((pid = fork()) <0) {
    printf("fork occurs error.\n");
  } else if (pid == 0) {
    status /= 0;
  }
  if (wait(&status) != pid) {
    printf("wait occurs error.\n");
  }
  pre_exit(status);
  return 0;
}

void pre_exit(int status) {
  if (WIFEXITED(status)) {
    printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
  } else if (WIFSIGNALED(status)) {
    printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
          #ifdef WCOREDUMP
            WCOREDUMP(status) ? " (core file generated)" : "");
          #else
            "");
          #endif
  } else if (WIFSTOPPED(status)) {
    printf("child stoped, signal number = %d\n", WSTOPSIG(status));
  }
}
