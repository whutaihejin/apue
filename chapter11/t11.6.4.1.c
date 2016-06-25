#include <stdio.h>
#include <pthread.h>

void time_show(struct timespec* ts) {
  clock_gettime(CLOCK_REALTIME, ts);
  struct tm* tm = localtime(&ts->tv_sec);
  char buf[64];
  if (strftime(buf, sizeof(buf), "%r", tm) != 0) {
    printf("time %s\n", buf);
  }
}

int main(int argc, char* argv[]) {
  pthread_rwlock_t rwlock;
  pthread_rwlock_init(&rwlock, NULL);
  pthread_rwlock_rdlock(&rwlock);
  printf("pthread_rwlock_rdlock has locked!\n");
  pthread_rwlock_rdlock(&rwlock);
  printf("pthread_rwlock_rdlock has locked again!\n");
  struct timespec ts;
  time_show(&ts);
  ts.tv_sec += 5;
  pthread_rwlock_timedwrlock(&rwlock, &ts);
  time_show(&ts);
  pthread_rwlock_unlock(&rwlock);
  pthread_rwlock_unlock(&rwlock);
  return 0;
}
