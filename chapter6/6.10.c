#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>

inline int64_t Now() {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

bool Weekday(time_t* tv) {
  if (tv == NULL) return false;
  struct tm* tmptr = gmtime(tv);
  char buf[4];
  if (strftime(buf, 4, "%u", tmptr) == 0) {
    return false;
  }
  return (buf[0] == '6' || buf[0] == '7') ? true : false;
}

bool Weekday() {
  time_t tv = time(NULL);
  return Weekday(&tv);
}

void ShowTime(time_t* tv) {
  if (tv == NULL) return;
  struct tm* tmptr = localtime(tv);
  char buf[64];
  if (strftime(buf, 64, "%c", tmptr) != 0) {
    printf("%s\n", buf);
  }
}

int main(int argc, char* argv[]) {
  time_t cur = time(NULL);
  printf("cur time is %ld\n", cur);
  struct tm* ptm = gmtime(&cur);
  char buf[64];
  if (strftime(buf, 64, "%u", ptm) != 0) {
    if (buf[0] == '7') {
      printf("%s\n", buf);
    }
  }

  for (int i = 0; i < 8; ++i) {
    cur += i * 24 * 60 * 60;
    ShowTime(&cur);
    printf(" weekend %d\n", Weekday(&cur));
  }

  
  
  
  
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  cur = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
  printf("cur time is %ld\n", cur);


  return 0;
}
