#include <stdio.h>
#include <pthread.h>
int main(int argc, char *argv[]) {
  printf("pthread_id = %lu\n", pthread_self());
  return 0;
}
