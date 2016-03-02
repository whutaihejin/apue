#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  char *login_name = getlogin();
  int nzero = nice(0);
  printf("login_name = %s, nzero = %d\n", login_name ? login_name : "", nzero);
  return 0;
}
