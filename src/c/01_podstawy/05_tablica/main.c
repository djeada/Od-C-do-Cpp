#include <stdio.h>

#define MAX_ROZMIAR 100

/**
 * Funkcja modyfikująca wartość w tablicy.
 *
 * @param tablica Tablica, w której modyfikujemy wartość.
 * @param indeks Indeks elementu do zmodyfikowania.
 * @param nowa_wartosc Nowa wartość, którą ustawiamy w elemencie o podanym
 * indeksie.
 */
void zmien_wartosc(int tablica[], int indeks, int nowa_wartosc) {
  tablica[indeks] = nowa_wartosc;
}

/**
 * Funkcja wczytująca wartości od użytkownika i zapisująca je w tablicy.
 *
 * @param tablica Tablica, do której zapisujemy wartości.
 * @param rozmiar Rozmiar tablicy.
 */
void wczytaj_dane(int tablica[], int rozmiar) {
  for (int i = 0; i < rozmiar; i++) {
    printf("Podaj wartość dla indeksu %d: ", i);
    scanf("%d", &tablica[i]);
  }
}

int main() {
  int moja_tablica[MAX_ROZMIAR];
  int rozmiar_tablicy;

  printf("Podaj rozmiar tablicy (maksymalny rozmiar: %d): ", MAX_ROZMIAR);
  scanf("%d", &rozmiar_tablicy);

  // Sprawdzenie, czy rozmiar nie jest zbyt duży.
  if (rozmiar_tablicy > MAX_ROZMIAR) {
    printf("Podany rozmiar jest zbyt duży!\n");
    return 1;
  }

  // Wczytanie wartości od użytkownika.
  wczytaj_dane(moja_tablica, rozmiar_tablicy);

  // Wyświetlenie zawartości tablicy przed modyfikacją.
  printf("\nZawartość tablicy przed modyfikacją:\n");
  for (int i = 0; i < rozmiar_tablicy; i++) {
    printf("%d ", moja_tablica[i]);
  }
  printf("\n");

  // Modyfikacja wartości w tablicy.
  zmien_wartosc(moja_tablica, 2, 10);

  // Wyświetlenie zawartości tablicy po modyfikacji.
  printf("\nZawartość tablicy po modyfikacji:\n");
  for (int i = 0; i < rozmiar_tablicy; i++) {
    printf("%d ", moja_tablica[i]);
  }
  printf("\n");

  return 0;
}
