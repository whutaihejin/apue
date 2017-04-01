#include <stdio.h>
#include <time.h>
#include <string>
#include <sys/time.h>
#include <stdint.h>

inline int64_t Now() {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

inline bool Weekday(time_t* tv) {
  if (tv == NULL) return false;
  struct tm* tmptr = localtime(tv);
  char buf[3];
  if (strftime(buf, 3, "%u", tmptr) == 0) {
    return false;
  }
  return (buf[0] == '6' || buf[0] == '7') ? true : false;
}

inline bool Weekday() {
  time_t tv = time(NULL);
  return Weekday(&tv);
}

inline int64_t MakeTime(const std::string& time) {
  // boost format check
  // check
  return MakeTime(time, "%Y-%m-%d %T");
}
inline int64_t MakeTime(const std::string& time, const std::string& format) {
  struct tm back_tm;
  strptime(time.c_str(), format.c_str(), &back_tm);
  return mktime(&back_tm); 
}

inline int64_t MakeTime(const char* time, const char* format) {
  return MakeTime(std::string(time), std::string(format)); 
}

void ShowTime(time_t* tv) {
  if (tv == NULL) return;
  struct tm* tmptr = localtime(tv);
  char buf[64];
  if (strftime(buf, 64, "%F %T", tmptr) != 0) {
    printf("%s\n", buf);
  }
}

int main(int argc, char* argv[]) {
  int64_t tv = MakeTime("2016-11-11 02:13:26");
  ShowTime(&tv);

  std::string time_str = "16-12-12 15:1:17";
  int64_t ttvv = MakeTime(time_str);
  ShowTime(&ttvv);

  time_t cur = time(NULL);
  printf("cur time is %ld\n", cur);
  struct tm* ptm = gmtime(&cur);
  char buf[64];
  if (strftime(buf, 64, "%F %T", ptm) != 0) {
    printf("%s\n", buf);
  }

  cur -= 24 * 60 * 60;
  for (int i = 0; i < 15; ++i) {
    cur += 24 * 60 * 60;
    ShowTime(&cur);
    printf(" weekend %d\n", Weekday(&cur));
  }

  char buffer[64] = "2016-11-20 13:55:22";
  struct tm back_tm;
  strptime(buffer, "%Y-%m-%d %T", &back_tm);
  time_t mytv = mktime(&back_tm);

  ShowTime(&mytv);
  printf(" heihei\n");

  
  
  
  
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  cur = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
  printf("cur time is %ld\n", cur);


  return 0;
}
