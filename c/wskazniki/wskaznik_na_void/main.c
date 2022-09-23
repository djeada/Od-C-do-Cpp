#include <stdio.h>
#include <stdlib.h>

int main() {
  int n = 10;
  void *arr = malloc(sizeof(int) * n);

  for (int i = 0; i < n; i++) {
    int *p = arr + i * sizeof(int);
    *p = i;
  }

  for (int i = 0; i < n; i++) {
    int *p = arr + i * sizeof(int);
    printf("%d \n", *p);
  }
  free(arr);
  return 0;
}
