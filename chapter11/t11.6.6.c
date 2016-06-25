#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct msg {
  int id;
  struct msg* next;
};

pthread_cond_t ready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void walk(struct msg* queue) {
  while (queue) {
    printf("%d -> ", queue->id);
    queue = queue->next;
  }
  printf("\n");
}

void offer(struct msg** queue, struct msg* item) {
  pthread_mutex_lock(&mutex);
  if (*queue != NULL) {
    item->next = *queue;
    *queue = item;
  } else {
    item->next = *queue;
    *queue = item;
  }
  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&ready);
}

struct msg* poll(struct msg** queue) {
  struct msg* item;
  pthread_mutex_lock(&mutex);
  while (*queue == NULL) {
    pthread_cond_wait(&ready, &mutex);
  }
  item = *queue;
  *queue = (*queue)->next;
  pthread_mutex_unlock(&mutex);
  return item;
}

void* thread_task(void* arg) {
  struct msg* queue = (struct msg*)arg;
  for (;;) {
    struct msg* item = poll(&queue);
    printf("poll msg: id %d addr %lx\n", item->id, (unsigned long)item);
    //free(item);
    sleep(1);
  }
}

int main(int argc, char* argv[]) {
  pthread_t tid;
  struct msg* queue;
  //pthread_create(&tid, NULL, thread_task, (void*)queue);
  long count = 0;
  for (;;) {
    struct msg* item = (struct msg*)malloc(sizeof(struct msg));
    item->id = (++count % 10000);
    offer(&queue, item);
    printf("offer msg: id %d addr %lx\n", item->id, (unsigned long)item);
    walk(queue);
    sleep(2);
  }
  return 0;
}
