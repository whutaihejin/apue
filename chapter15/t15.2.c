#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLINE 20

void print_exit(const char* msg) {
  printf("%s\n", msg);
  exit(1);
}

int main(int argc, char* argv[]) {
  int n;
  int fd[2];
  pid_t pid;
  char line[MAXLINE];
  if (pipe(fd) < 0) {
    print_exit("pipe error");
  }
  if ((pid = fork()) < 0) {
    print_exit("fork error");
  } else if (pid > 0) { // parent
    close(fd[0]);
    write(fd[1], "hello world\n", 12);
  } else {
    close(fd[1]);
    n = read(fd[0], line, MAXLINE);
    write(STDOUT_FILENO, line, n);
  }
  return 0;
}
