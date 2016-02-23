#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

#define display(name) pr_limits(#name, name)

static void pr_limits(char *, int);

int main(int argc, char *argv[]) {
  #ifdef RLIMIT_AS
    display(RLIMIT_AS);
  #endif
  display(RLIMIT_CORE);
  return 0;
}

static void pr_limits(char *name, int resource) {
  struct rlimit limit;
  unsigned long long lim;

  if (getrlimit(resource, &limit) != 0) {
    printf("getrlimit error for %s\n", name);
  }
  printf("%-14s ", name);
  if (limit.rlim_cur == RLIM_INFINITY) {
    printf("(infinity) ");
  } else {
    lim = limit.rlim_cur;
    printf("%10lld ", lim);
  }
  if (limit.rlim_max == RLIM_INFINITY) {
    printf("(infinity) ");
  } else {
    lim = limit.rlim_max;
    printf("%10lld ", lim);
  }
  putchar('\n');
}
