#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

void alarm_handler(int signo) {
  struct passwd *rootptr;
  printf("in sigal handler\n");
  if ((rootptr = getpwnam("root")) == NULL) {
    printf("getpwnam(root) error\n");
    exit(0);
  }
  alarm(1);
}

int main() {
  struct passwd *ptr;
  signal(SIGALRM, alarm_handler);
  alarm(1);
  for (;;) {
    if ((ptr = getpwnam("taihein")) == NULL) {
      printf("getpwnam error %d\n", errno);
      exit(0);
    }
    if (strcmp(ptr->pw_name, "taihejin") != 0) {
      printf("return value corrupted! pw_name=%s\n", ptr->pw_name);
      exit(0);
    }
  }
  return 0;
}
