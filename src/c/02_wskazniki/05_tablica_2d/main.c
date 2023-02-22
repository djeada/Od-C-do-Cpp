#include <stdio.h>
#include <stdlib.h>

#define LICZBA_WIERSZY 5
#define LICZBA_KOLUMN 10

int main() {

  // tablica 2D
  int **tablica = malloc(LICZBA_WIERSZY * sizeof(int *));
  if (tablica == NULL) {
    printf("Blad alokacji pamieci.");
    return 1;
  }

  for (int i = 0; i < LICZBA_WIERSZY; i++) {
    tablica[i] = malloc(LICZBA_KOLUMN * sizeof(int));
    if (tablica[i] == NULL) {
      printf("Blad alokacji pamieci.");
      return 1;
    }
  }

  // wypelnienie tablicy
  // tabliczka mnozenia
  for (int i = 0; i < LICZBA_WIERSZY; i++) {
    for (int j = 0; j < LICZBA_KOLUMN; j++) {
      tablica[i][j] = (i + 1) * (j + 1);
    }
  }

  // wypisanie tablicy
  for (int i = 0; i < LICZBA_WIERSZY; i++) {
    for (int j = 0; j < LICZBA_KOLUMN; j++) {
      printf("%d ", tablica[i][j]);
    }
    printf("\n");
  }

  // zwolnienie pamieci
  for (int i = 0; i < LICZBA_WIERSZY; i++) {
    free(tablica[i]);
  }
  free(tablica);

  return 0;
}
