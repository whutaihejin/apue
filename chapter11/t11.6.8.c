#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h> 

#define SIZE  8000000
#define BASE  1000000
#define SHARD  (SIZE / BASE)

pthread_barrier_t barrier;

int compare(const void* x, const void* y) {
  int* low = (int*)x;
  int* high = (int*)y;
  if (*low < *high) {
    return -1;
  } else {
    return *low > *high ? 1 : 0;
  }
}

struct parameter {
  void* address;
  int length;
  int size;
  int (*fun)(const void*, const void*);
};

void* thread_task(void* arg) {
  struct parameter* param = (struct parameter*) arg;
  qsort(param->address, param->length, param->size, param->fun);
  free(param);
  pthread_barrier_wait(&barrier);
}

void walk(int* nums, int size) {
  int* limit = nums + size;
  for (; nums < limit;) {
    printf("%d ", *nums++);
  }
  printf("\n");
}

void merge(int* nums, int* dest) {
  int index[SHARD] = {0};
  int i;
  int k;
  for (k = 0; k < SIZE; k++) {
    int min_value = INT_MAX;
    int min_index;
    for (i = 0; i < SHARD; i++) {
      int offset = BASE * i + index[i];
      if (index[i] < BASE && nums[offset] < min_value) {
        min_value = nums[offset];
        min_index = i;
      }
    }
    dest[k] = min_value;
    index[min_index]++;
  }
}

void test1() {
  int nums[] = {5, 6, 3, 4};
  walk(nums, SIZE);
  int dest[4];
  merge(nums, dest);
  walk(dest, SIZE);
}

void time_show() {
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);
  struct tm* value = localtime(&ts.tv_sec);
  char buf[64];
  strftime(buf, sizeof(buf), "%r", value);
  printf("time %s\n", buf);
}

int main(int argc, char* argv[]) {
  int* nums = malloc(sizeof(int) * SIZE);
  int* dest = malloc(sizeof(int) * SIZE);
  int i;
  for (i = 0; i < SIZE; i++) {
    nums[i] = random() % 100;
  }
  time_show();
  pthread_barrier_init(&barrier, NULL, SHARD + 1);
  pthread_t tid;
  for (i = 0; i < SHARD; i++) {
    struct parameter* param = (struct parameter*)malloc(sizeof(struct parameter));
    param->address = nums + i * BASE;
    param->length = BASE;
    param->size = sizeof(nums[0]);
    param->fun = compare;
    pthread_create(&tid, NULL, thread_task, (void*)param);
  }
  pthread_barrier_wait(&barrier);
  merge(nums, dest);
  time_show();
  free(nums);
  free(dest);
  return 0;
}
