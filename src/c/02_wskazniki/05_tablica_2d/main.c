#include <stdio.h>
#include <stdlib.h>

#define LICZBA_WIERSZY 5
#define LICZBA_KOLUMN 10

int main(void) {
  int **tablica = malloc(LICZBA_WIERSZY * sizeof(*tablica));
  if (tablica == NULL) {
    fprintf(stderr, "Blad alokacji pamieci.\n");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < LICZBA_WIERSZY; i++) {
    tablica[i] = malloc(LICZBA_KOLUMN * sizeof(*tablica[i]));
    if (tablica[i] == NULL) {
      fprintf(stderr, "Blad alokacji pamieci.\n");
      for (int j = 0; j < i; ++j) {
        free(tablica[j]);
      }
      free(tablica);
      return EXIT_FAILURE;
    }
  }

  for (int i = 0; i < LICZBA_WIERSZY; i++) {
    for (int j = 0; j < LICZBA_KOLUMN; j++) {
      tablica[i][j] = (i + 1) * (j + 1);
    }
  }

  for (int i = 0; i < LICZBA_WIERSZY; i++) {
    for (int j = 0; j < LICZBA_KOLUMN; j++) {
      printf("%d ", tablica[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < LICZBA_WIERSZY; i++) {
    free(tablica[i]);
  }
  free(tablica);

  return EXIT_SUCCESS;
}
