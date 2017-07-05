#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

static char* name = "taihejin";

static void alarm_handler(int signo) {
  struct passwd *rootptr;
  printf("in signal handler\n");
  signal(SIGALRM, alarm_handler);
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
    if ((ptr = getpwnam(name)) == NULL) {
      printf("getpwnam error %d\n", errno);
      exit(0);
    }
    if (strcmp(ptr->pw_name, name) != 0) {
      printf("return value corrupted! pw_name=%s\n", ptr->pw_name);
      exit(0);
    }
    // pause();
  }
  return 0;
}
