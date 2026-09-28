#include <stdio.h>
#include <stdlib.h>

// Obliczanie indeksu elementu na podstawie jego współrzędnych x i y
// w dwuwymiarowej tablicy o wymiarach maxX na maxY.
int oblicz_indeks(int x, int y, int maxX) { return y * maxX + x; }

int main(void) {
  int x = 4, y = 5;

  int **tablica = malloc((size_t)x * sizeof(*tablica));
  if (tablica == NULL) {
    fprintf(stderr, "Blad alokacji pamieci.\n");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < x; ++i) {
    tablica[i] = malloc((size_t)y * sizeof(*tablica[i]));
    if (tablica[i] == NULL) {
      fprintf(stderr, "Blad alokacji pamieci.\n");
      for (int j = 0; j < i; ++j) {
        free(tablica[j]);
      }
      free(tablica);
      return EXIT_FAILURE;
    }
  }

  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      tablica[i][j] = i + j;
    }
  }

  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      printf("%d ", tablica[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  int *tablica2 = malloc((size_t)x * (size_t)y * sizeof(*tablica2));
  if (tablica2 == NULL) {
    fprintf(stderr, "Blad alokacji pamieci.\n");
    for (int i = 0; i < x; ++i) {
      free(tablica[i]);
    }
    free(tablica);
    return EXIT_FAILURE;
  }

  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      int index = oblicz_indeks(j, i, y);
      tablica2[index] = i + j;
    }
  }

  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      printf("%d ", tablica2[oblicz_indeks(j, i, y)]);
    }
    printf("\n");
  }

  for (int i = 0; i < x; ++i) {
    free(tablica[i]);
  }
  free(tablica);
  free(tablica2);

  return EXIT_SUCCESS;
}
