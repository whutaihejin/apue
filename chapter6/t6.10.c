#include <stdio.h>
#include <time.h>
#include <sys/time.h>
void time_show(struct tm* ptr, const char* prefix) {
  char buf[64];
  if (strftime(buf, sizeof(buf), "%c", ptr) == 0) {
    printf("strftime error\n");
    return;
  }
  printf("%s: time %s\n", prefix, buf);
}
int main(int argc, char* argv[]) {
  // time test
  time_t t = time(NULL);
  printf("time %ld by time\n", (unsigned long)t);
  time_t v;
  time(&v);
  printf("time %ld by time\n", (unsigned long)v);
  // clock_gettime test
  struct timespec ts;
  if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
    printf("clock_gettime error.\n");
  }
  printf("time %ld by clock_gettime\n", ts.tv_sec);
  // gettimeofday
  struct timeval tv;
  gettimeofday(&tv, NULL);
  printf("time %ld by gettimeofday\n", tv.tv_sec);
  // gmtime
  struct tm* tmptr = gmtime(&t);
  time_show(tmptr, "time gmtime");
  tmptr = localtime(&v);
  time_show(tmptr, "time localtime");
  tmptr = localtime(&ts.tv_sec);
  time_show(tmptr, "clock_gettime localtime");
  tmptr = gmtime(&tv.tv_sec);
  time_show(tmptr, "gettimeofday gmtime");
  return 0;
}
