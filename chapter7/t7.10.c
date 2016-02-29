#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf jmp;

void do_line(int);
void cmd_add(int);
void usage();

int main(int argc, char *argv[]) {
  if (argc != 2) {
    usage();
    return -1;
  }
  int value = atoi(argv[1]);
  int set_value = 0;
  if ((set_value = setjmp(jmp)) != 0) {
    printf("set_value = %d\n", set_value);
    return set_value;
  }
  do_line(value);
  return 0;
}

void do_line(int value) {
  if (value == 1) {
    longjmp(jmp, value);
  } else {
    cmd_add(value);
  }
}

void cmd_add(int value) {
  longjmp(jmp, value);
}

void usage() {
  printf("./t7.10 <int_value>\n");
  printf("<int_value> == 1 do_line accur longjmp.\n");
  printf("<int_value> == 2 cmd_add accur longjmp.\n");
}
