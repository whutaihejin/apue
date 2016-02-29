#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  printf("----------- for getenv() test\n");
  const char* home = "HOME";
  const char* empty = "empty";
  char* value;
  printf("%s = %s\n", home, (value = getenv(home)) ? value : "NULL");
  printf("%s = %s\n", empty, (value = getenv(empty)) ? value : "NULL");
  //
  printf("----------- for putenv() test\n");
  putenv("empty=empty_value");
  printf("%s = %s\n", empty, (value = getenv(empty)) ? value : "NULL");
  putenv("empty=empty_value_1");
  printf("%s = %s\n", empty, (value = getenv(empty)) ? value : "NULL");
  //
  printf("----------- for setenv() test\n");
  const char* empty_set = "empty_set";
  setenv(empty_set, "empty_set_value", 0);
  printf("%s = %s\n", empty_set, (value = getenv(empty_set)) ? value : "NULL");
  setenv(empty_set, "empty_set_value_1", 1);
  printf("%s = %s\n", empty_set, (value = getenv(empty_set)) ? value : "NULL");
  setenv(empty_set, "empty_set_value_2", 0);
  printf("%s = %s\n", empty_set, (value = getenv(empty_set)) ? value : "NULL");
  //
  printf("----------- for unsetenv() test\n");
  unsetenv(empty_set);
  printf("%s = %s\n", empty_set, (value = getenv(empty_set)) ? value : "NULL");
  return 0;
}
