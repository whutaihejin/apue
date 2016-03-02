#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  char *login_name = getlogin();
  printf("login_name = %s\n", login_name ? login_name : "");
  return 0;
}
