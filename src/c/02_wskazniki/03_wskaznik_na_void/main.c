#include <stdio.h>
#include <stdlib.h>

int main() {
  int n = 10;

  // Alokacja pamięci dla n elementów typu int
  void *tablica = malloc(sizeof(int) * n);
  if (tablica == NULL) {
    printf("Nie udało się zaalokować pamięci!");
    return 1;
  }

  // Konwersja wskaźnika na void na wskaźnik na int
  int *wskaznik_na_tablice = (int *)tablica;

  // Przypisanie wartości kolejnym elementom tablicy za pomocą wskaźnika
  for (int i = 0; i < n; i++) {
    *(wskaznik_na_tablice + i) = i;
  }

  // Wyświetlenie zawartości tablicy za pomocą wskaźnika
  for (int i = 0; i < n; i++) {
    printf("%d ", *(wskaznik_na_tablice + i));
  }
  printf("\n");

  // Zwolnienie zaalokowanej pamięci
  free(tablica);

  return 0;
}
