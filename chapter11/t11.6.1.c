#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
struct foo {
  int id;
  int refs;
  pthread_mutex_t mutex;
};
struct foo* alloc(int id) {
  struct foo* p;
  if ((p = (struct foo*)malloc(sizeof(struct foo))) != NULL) {
    p->id = id;
    p->refs = 1;
    if (pthread_mutex_init(&p->mutex, NULL) != 0) {
      free(p);
      return NULL;
    }
  }
  return p;
}
void hold(struct foo* p) {
  pthread_mutex_lock(&p->mutex);
  p->refs++;
  pthread_mutex_unlock(&p->mutex);
}
void release(struct foo* p) {
  pthread_mutex_lock(&p->mutex);
  if (--p->refs == 0) {
    pthread_mutex_unlock(&p->mutex);
    pthread_mutex_destroy(&p->mutex);
    free(p);
  } else {
    pthread_mutex_unlock(&p->mutex);
  }
}
void* thread_task(void* arg) {
  struct foo* p = (struct foo*)arg;
  int i;
  for (i = 0; i < 100; i++) {
    hold(p);
    printf("task pid %ld tid %ld hold %d with %dth\n", (unsigned long)getpid(), (unsigned long)pthread_self(), p->id, i + 1);
  }
  for (i = 0; i < 100; i++) {
    release(p);
    printf("task pid %ld tid %ld release %d with %dth\n", (unsigned long)getpid(), (unsigned long)pthread_self(), p->id, i + 1);
  }
}
int main(int argc, char* argv[]) {
  pthread_t tid;
  int err;
  int i;
  struct foo* p = alloc(22);
  err = pthread_create(&tid, NULL, thread_task, (void*)p);
  if (err != 0) {
    err_exit(err, "can't create thread");
  }
  for (i = 0; i < 100; i++) {
    hold(p);
    printf("main pid %ld tid %ld hold %d with %dth\n", (unsigned long)getpid(), (unsigned long)pthread_self(), p->id, i + 1);
  }
  for (i = 0; i < 100; i++) {
    release(p);
    printf("main pid %ld tid %ld release %d with %dth\n", (unsigned long)getpid(), (unsigned long)pthread_self(), p->id, i + 1);
  }
  pthread_join(tid, NULL);
  release(p);
  return 0;
}
