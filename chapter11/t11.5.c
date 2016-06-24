#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void errexit(int err, const char* indicator) {
  printf("%s error %d\n", indicator, err);
  exit(1);
}

void* thread_task1(void* arg) {
  printf("thread 1 returning\n");
  return (void*)5;
}

void* thread_task2(void* args) {
  printf("thread 2 exit\n");
  pthread_exit((void*)6);
}

int main(int argc, char* argv[]) {
  pthread_t tid1, tid2;
  void* tret;
  int err;
  err = pthread_create(&tid1, NULL, thread_task1, NULL);
  if (err != 0) {
    errexit(err, "can't create thread 1");
  }
  err = pthread_create(&tid2, NULL, thread_task2, NULL);
  if (err != 0) {
    errexit(err, "can't create thread 2");
  }
  err = pthread_join(tid1, &tret);
  if (err != 0) {
    errexit(err, "can't join with thread 1");
  }
  printf("thread 1 exit code %ld\n", (long)tret);
  err = pthread_join(tid2, &tret);
  if (err != 0) {
    errexit(err, "can't join with thread 2");
  }
  printf("thread 2 exit code %ld\n", (long)tret);
  return 0;
}
