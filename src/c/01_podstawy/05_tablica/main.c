#include <stdio.h>
#include <stdlib.h>

#define MAX_ROZMIAR 100

int zmien_wartosc(int tablica[], int rozmiar, int indeks, int nowa_wartosc) {
  if (indeks < 0 || indeks >= rozmiar) {
    return -1;
  }
  tablica[indeks] = nowa_wartosc;
  return 0;
}

int wczytaj_dane(int tablica[], int rozmiar) {
  for (int i = 0; i < rozmiar; i++) {
    printf("Podaj wartość dla indeksu %d: ", i);
    if (scanf("%d", &tablica[i]) != 1) {
      return -1;
    }
  }
  return 0;
}

int main(void) {
  int moja_tablica[MAX_ROZMIAR];
  int rozmiar_tablicy;

  printf("Podaj rozmiar tablicy (1-%d): ", MAX_ROZMIAR);
  if (scanf("%d", &rozmiar_tablicy) != 1 || rozmiar_tablicy < 1 ||
      rozmiar_tablicy > MAX_ROZMIAR) {
    fprintf(stderr, "Nieprawidlowy rozmiar tablicy.\n");
    return EXIT_FAILURE;
  }

  if (wczytaj_dane(moja_tablica, rozmiar_tablicy) != 0) {
    fprintf(stderr, "Nieprawidlowa wartosc elementu.\n");
    return EXIT_FAILURE;
  }

  printf("\nZawartość tablicy przed modyfikacją:\n");
  for (int i = 0; i < rozmiar_tablicy; i++) {
    printf("%d ", moja_tablica[i]);
  }
  printf("\n");

  if (zmien_wartosc(moja_tablica, rozmiar_tablicy, 2, 10) != 0) {
    printf("Tablica ma mniej niż 3 elementy - pomijam zmianę indeksu 2.\n");
  }

  printf("\nZawartość tablicy po modyfikacji:\n");
  for (int i = 0; i < rozmiar_tablicy; i++) {
    printf("%d ", moja_tablica[i]);
  }
  printf("\n");

  return EXIT_SUCCESS;
}
