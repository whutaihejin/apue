#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void print_id(char *prefix);
void *thread_task(void *arg);

int main(int argc, char *argv[]) {
  pthread_t tid;
  int flag = pthread_create(&tid, NULL, thread_task, NULL);
  if (flag != 0) {
    printf("thread create error\n");
  }
  print_id("main thread:");
  sleep(2);
  return 0;
}

void print_id(char *prefix) {
  printf("%s pid = %lu, tid = %lu\n", prefix, (unsigned long int)getpid(), (unsigned long int)pthread_self());
}

void *thread_task(void *arg) {
  print_id("child thread:");
  return NULL;
}
