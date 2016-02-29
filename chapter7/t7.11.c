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
  display(RLIMIT_CPU);
  display(RLIMIT_DATA);
  display(RLIMIT_FSIZE);
  #ifdef RLIMIT_MEMLOCK 
    display(RLIMIT_MEMLOCK);
  #endif
  #ifdef RLIMIT_MSGQUEUE 
    display(RLIMIT_MSGQUEUE);
  #endif
  #ifdef RLIMIT_NICE 
    display(RLIMIT_NICE);
  #endif
  display(RLIMIT_NOFILE);
  #ifdef RLIMIT_NPROC
    display(RLIMIT_NPROC);
  #endif
  #ifdef RLIMIT_NPTS 
    display(RLIMIT_NPTS);
  #endif
  #ifdef RLIMIT_RSS
    display(RLIMIT_RSS);
  #endif
  #ifdef RLIMIT_SBSIZE 
    display(RLIMIT_SBSIZE);
  #endif
  #ifdef RLIMIT_SIGPENDING
    display(RLIMIT_SIGPENDING);
  #endif
  display(RLIMIT_STACK);
  #ifdef RLIMIT_SWAP 
    display(RLIMIT_SWAP);
  #endif
  #ifdef RLIMIT_VMEM
    display(RLIMIT_VMEM);
  #endif
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
