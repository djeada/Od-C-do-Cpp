#include <stdlib.h>

int index(int x, int y, int maxX) { return y * maxX + x; }

int main(void) {

  //  Malloc -> malloc -> malloc... sposób

  int x = 4, y = 5;
  int **arr = malloc(sizeof(*arr) * x);
  for (int i = 0; i < x; ++i) {
    arr[i] = malloc(sizeof(arr[0]) * y);
  }

  // Tablica 1D ze sposobem indeksowania
  int x = 4, y = 5;
  int *arr = malloc(sizeof(*arr) * x * y);
  int elem = arr[index(0, 2, x)];
  return 0;
}
