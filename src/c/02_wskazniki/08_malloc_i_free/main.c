#include <stdio.h>
#include <stdlib.h>

#define ROZMIAR_TABLICY 10

int *utworzTablice() {
  int tablica[ROZMIAR_TABLICY] = {};

  for (int i = 0; i < ROZMIAR_TABLICY; i++) {
    tablica[i] = i; // wypełnienie tablicy wartościami
  }

  return tablica; // zwrócenie wskaźnika na tablicę
}

// Funkcja tworząca i zwracająca wskaźnik na tablicę o zadanej wielkości
int *utworzTabliceMalloc(int rozmiar) {
  int *tablica = malloc(rozmiar * sizeof(int)); // alokacja pamięci dla tablicy

  for (int i = 0; i < rozmiar; i++) {
    tablica[i] = i; // wypełnienie tablicy wartościami
  }

  return tablica; // zwrócenie wskaźnika na tablicę
}

void wypiszTablice(int *tablica, int rozmiar) {
  for (int i = 0; i < rozmiar; i++) {
    printf("%d ", tablica[i]);
  }
  printf("\n");
}

int main() {
  // użycie funkcji utworzTablice, która nie może zwrócić wskaźnika bez alokacji
  // pamięci
  int *tablica = utworzTablice();
  wypiszTablice(tablica, ROZMIAR_TABLICY);

  // alokacja pamieci dla tablicy
  int *tablica2 = utworzTabliceMalloc(ROZMIAR_TABLICY);

  wypiszTablice(tablica2, ROZMIAR_TABLICY);

  // zwolnienie pamięci
  free(tablica2);

  return 0;
}
