#include <stdio.h>
#include <stdlib.h>

#define ROZMIAR_TABLICY 10

void utworzTablice(int *tablica, int rozmiar) {
  for (int i = 0; i < rozmiar; i++) {
    tablica[i] = i; // wypełnienie tablicy wartościami
  }
}

// Funkcja tworząca i zwracająca wskaźnik na tablicę o zadanej wielkości
int *utworzTabliceMalloc(int rozmiar) {
  int *tablica = malloc((size_t)rozmiar * sizeof(*tablica));
  if (tablica == NULL) {
    return NULL;
  }

  for (int i = 0; i < rozmiar; i++) {
    tablica[i] = i; // wypełnienie tablicy wartościami
  }

  return tablica;
}

void wypiszTablice(const int *tablica, int rozmiar) {
  for (int i = 0; i < rozmiar; i++) {
    printf("%d ", tablica[i]);
  }
  printf("\n");
}

int main(void) {
  // Tablica o automatycznym czasie życia pozostaje własnością funkcji main.
  int tablica[ROZMIAR_TABLICY];
  utworzTablice(tablica, ROZMIAR_TABLICY);
  wypiszTablice(tablica, ROZMIAR_TABLICY);

  // Alokacja pamięci dla tablicy na stercie.
  int *tablica2 = utworzTabliceMalloc(ROZMIAR_TABLICY);
  if (tablica2 == NULL) {
    fprintf(stderr, "Nie udalo sie zaalokowac pamieci.\n");
    return EXIT_FAILURE;
  }

  wypiszTablice(tablica2, ROZMIAR_TABLICY);

  // Zwolnienie pamięci.
  free(tablica2);

  return EXIT_SUCCESS;
}
