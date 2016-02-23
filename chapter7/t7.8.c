#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  size_t size = sizeof(int) * 5;
  int* array = malloc(size);
  for (int i = 0; i < 5; i++) {
    printf("%d ", array[i]);
    array[i] = i + 1;
  }
  printf("\n");
  for (int i = 0; i < 5; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
  free(array);
  int* vector = calloc(sizeof(int), 5);
  for (int i = 0; i < 5; i++) {
    printf("%d ", vector[i]);
    vector[i] = i + 1;
  }
  printf("\n");
  for (int i = 0; i < 5; i++) {
    printf("%d ", vector[i]);
  }
  printf("\n");
  free(vector);
  return 0;
}
