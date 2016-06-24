#include <stdio.h>
#include <pthread.h>
int main(int argc, char* argv[]) {
  char buf[64];
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&mutex);
  printf("mutex is locked !\n");
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  struct tm* tmp = localtime(&ts.tv_sec);
  strftime(buf, sizeof(buf), "%r", tmp);
  printf("current time is %s\n", buf);
  ts.tv_sec += 10;
  int err = pthread_mutex_timedlock(&mutex, &ts);
  clock_gettime(CLOCK_REALTIME, &ts);
  tmp = localtime(&ts.tv_sec);
  strftime(buf, sizeof(buf), "%r", tmp);
  printf("current time is %s\n", buf);
  if (err == 0) {
    printf("mutex locked again !\n");
  } else {
    printf("can't lock mutex again!\n");
  }
  return 0;
}
