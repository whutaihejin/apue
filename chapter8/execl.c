#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
  pid_t pid;
  if ((pid = fork()) < 0) {
    printf("fork error.\n");
    exit(0);
  } else if (pid == 0) {
    // child
    if (execl("/usr/bin/interprete", "interprete", "arg1", "arg2") < 0) {
      printf("execl error.\n");
    }
  }
  
  // parent
  if (waitpid(pid, NULL, 0) < 0) {
    printf("wait error.\n");
  }
  return 0;
}
