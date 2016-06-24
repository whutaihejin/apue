#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
struct foo {
  int a, b, c, d;
};

void printfoo(const char* prefix, const struct foo* fp) {
  printf("%s", prefix);
  printf(" struct at 0x%lx\n", (unsigned long)fp);
  printf(" foo.a = %d\n", fp->a);
  printf(" foo.b = %d\n", fp->b);
  printf(" foo.c = %d\n", fp->c);
  printf(" foo.d = %d\n", fp->d);
}

void errexit(int err, const char* indicator) {
  printf("%s error %d\n", indicator, err);
  exit(1);
}

void* thread_task1(void* arg) {
  struct foo* fp = malloc(sizeof(struct foo));
  if (fp != NULL) {
    fp->a = 1;
    fp->b = 2;
    fp->c = 3;
    fp->d = 4;
  }
  printf("thread 1: pid %ld tid %lu\n", (unsigned long)getpid(), (unsigned long)pthread_self());
  printfoo("thread 1:\n", fp);
  sleep(3);
  return (void*)fp;
}

void* thread_task2(void* args) {
  printf("thread 2: pid %ld tid %lu\n", (unsigned long)getpid(), (unsigned long)pthread_self());
  sleep(3);
  pthread_exit((void*)0);
}

int main(int argc, char* argv[]) {
  pthread_t tid1, tid2;
  struct foo* fp;
  int err;
  err = pthread_create(&tid1, NULL, thread_task1, NULL);
  if (err != 0) {
    errexit(err, "can't create thread 1");
  }
  err = pthread_create(&tid2, NULL, thread_task2, NULL);
  if (err != 0) {
    errexit(err, "can't create thread 2");
  }
  err = pthread_join(tid1, (void*)&fp);
  if (err != 0) {
    errexit(err, "can't join with thread 1");
  }
  sleep(1);
  printfoo("parent:\n", fp);
  free(fp);
  return 0;
}
