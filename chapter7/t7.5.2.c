#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  printf("%s\n", getenv("USER"));
  if (putenv("WEIBO=taihejin_weibo") != 0) {
    printf("put env of weibo failed!\n");
  }
  char* env = getenv("WEIBO");
  if (env != NULL) {
    printf("WEIBO = %s\n", env);
  }
  return 0;
}
