#include <stdio.h>
#include <pthread.h>
int main(int argc, char *argv[]) {
  pthread_t tid1 = 1L;
  pthread_t tid2 = 2L;
  printf("%lu == %lu is %d\n", tid1, tid2, pthread_equal(tid1, tid2));
  printf("%lu == %lu is %d\n", 1L, 1L, pthread_equal(1L, 1L));
  printf("pthread_id = %lu\n", pthread_self());
  return 0;
}
