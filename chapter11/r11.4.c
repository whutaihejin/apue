#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void print_ids(const char* prefix) {
  pid_t pid = getpid();
  pthread_t tid = pthread_self();
  printf("%s pid %lu tid %lu (0x%lx)\n", prefix, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}
void* thread_task(void* arg) {
  print_ids("new thread: ");
  return NULL;
}
int main(int argc, char* argv[]) {
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, thread_task, NULL);
  if (ret != 0) {
    printf("create thread error, exit");
    exit(1);
  }
  //sleep(1);
  print_ids("main thread: ");
  sleep(1);
  return 0;
}
