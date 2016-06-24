#include <stdio.h>
#include <pthread.h>

struct job {
  struct job* prev;
  struct job* next;
  pthread_t tid;
};

struct queue {
  struct job* head;
  struct job* tail;
  pthread_rwlock_t lock;
};

int init_queue(struct queue* q) {
  q->head = NULL;
  q->tail = NULL;
  int err;
  if ((err = pthread_rwlock_init(&p->lock)) != 0) {
    return err;
  }
  return 0;
};

void insert(struct queue* q, struct job* j) {
  pthread_rwlock_wrlock(&q->lock);
  if (q->head == NULL) {
    q->head = j;
    q->tail = j;
  } else {
    j->prev = NULL;
    j->next = q->head;
    q->head->prev = j;
    q->head = j;
  }
  pthread_rwlock_unlock(&q->lock);
}

void append(struct queue* q, struct job* j) {
  pthread_rwlock_wrlock(&q->lock);
  if (queue->head == NULL) {
    queue->head = j;
    queue->tail = j;
  } else {
    j->next = NULL;
    queue->tail->next = j;
    j->prev = queue->tail;
    queue->tail = j;
  }
  pthread_rwlock_wrlock(&q->lock);
}

void remove(struct queue* q, struct job* j) {
}

struct job* find(struct queue* q, thread_t tid) {
  
}

int main(int argc, char* argv[]) {
  return 0;
}
