#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define SIZE 10

struct foo {
  int id;
  int refs;
  struct foo* next;
  pthread_mutex_t mutex;
};

int hash(int id) {
  return id % SIZE;
}

struct foo* map[SIZE];
pthread_mutex_t hash_lock;

struct foo* alloc(int id) {
  struct foo* p;
  if ((p = (struct foo*)malloc(sizeof(struct foo))) != NULL) {
    p->id = id;
    p->refs = 1;
    if (pthread_mutex_init(&p->mutex, NULL) != 0) {
      free(p);
      return NULL;
    }
    printf("pid %ld tid %ld alloc id %d\n", (unsigned long)getpid(), (unsigned long)pthread_self(), id);
  }
  int index = hash(id);
  pthread_mutex_lock(&hash_lock);
  p->next = map[index];
  map[index] = p;
  pthread_mutex_unlock(&hash_lock);
  return p;
}

void hold(struct foo* p) {
  pthread_mutex_lock(&p->mutex);
  p->refs++;
  pthread_mutex_unlock(&p->mutex);
}

struct foo* find(int id) {
  struct foo* p;
  pthread_mutex_lock(&hash_lock);
  for (p = map[hash(id)]; p != NULL; p = p->next) {
    if (p->id = id) {
      break;
    }
  }
  pthread_mutex_unlock(&hash_lock);
  return p;
}

void release(struct foo* p) {
  if (p == NULL) {
    return;
  }
  pthread_mutex_lock(&p->mutex);
  if (p->refs == 1) { // last ref
    pthread_mutex_unlock(&p->mutex);
    pthread_mutex_lock(&hash_lock);
    pthread_mutex_lock(&p->mutex);
    if (p->refs != 1) {
      p->refs--;
      pthread_mutex_unlock(&p->mutex);
      pthread_mutex_unlock(&hash_lock);
    }
    int index = hash(p->id);
    struct foo* f = map[index];
    if (f == p) {
      map[index] = p->next;
    } else {
      while (f->next != p) {
        f = f->next;
      }
      f->next = p->next;
    }
    pthread_mutex_unlock(&hash_lock);
    pthread_mutex_unlock(&p->mutex);
    pthread_mutex_destroy(&p->mutex);
    int id = p->id;
    free(p);
    printf("pid %ld tid %ld free id %d\n", (unsigned long)getpid(), (unsigned long)pthread_self(), id);
  } else {
    p->refs--;
    pthread_mutex_unlock(&p->mutex);
  }
}

void* thread_task(void* arg) {
  int i;
  for (i = 0; i < 10; i++) {
    alloc(i + 1);
  }
}

int main(int argc, char* argv[]) {
  pthread_mutex_init(&hash_lock, NULL);
  pthread_t tid;
  int err = 0;
  int i;
  err = pthread_create(&tid, NULL, thread_task, NULL);
  if (err != 0) {
    err_exit(err, "can't create thread");
  }
  sleep(1);
  for (i = 0; i < 10; i++) {
    struct foo* p = find(i + 1);
    release(p);
  }
  pthread_join(tid, NULL);
  return 0;
}
