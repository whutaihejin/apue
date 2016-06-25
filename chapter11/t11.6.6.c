#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct msg {
  int id;
  struct msg* next;
};

pthread_cond_t ready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct msg* queue;

void walk() {
  struct msg* q = queue;
  while (q) {
    printf("%d->", q->id);
    q = q->next;
  }
  printf("\n");
}

void offer(struct msg* item) {
  pthread_mutex_lock(&mutex);
  item->next = queue;
  queue = item;
  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&ready);
}

struct msg* poll() {
  struct msg* item;
  pthread_mutex_lock(&mutex);
  while (queue == NULL) {
    printf("queue addr %lx\n", (unsigned long)queue);
    pthread_cond_wait(&ready, &mutex);
  }
  item = queue;
  queue = item->next;
  pthread_mutex_unlock(&mutex);
  return item;
}

void* thread_task(void* arg) {
  printf("thread task %lx\n", (unsigned long)queue);
  for (;;) {
    struct msg* item = poll();
    printf("poll msg: id %d addr %lx\n", item->id, (unsigned long)item);
    free(item);
    walk();
    sleep(3);
  }
}

int main(int argc, char* argv[]) {
  pthread_t tid;
  pthread_create(&tid, NULL, thread_task, (void*)(queue));
  long count = 0;
  for (;;) {
    struct msg* item = (struct msg*)malloc(sizeof(struct msg));
    item->id = (++count % 10000);
    offer(item);
    printf("offer msg: id %d addr %lx\n", item->id, (unsigned long)item);
    walk();
    sleep(1);
  }
  return 0;
}
