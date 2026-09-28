#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct Zakres {
  int *poczatek;
  size_t liczba;
};

static int porownaj_int(const void *a, const void *b) {
  int x = *(const int *)a;
  int y = *(const int *)b;
  return (x > y) - (x < y);
}

static void *sortuj_zakres(void *arg) {
  struct Zakres *zakres = arg;
  qsort(zakres->poczatek, zakres->liczba, sizeof(*zakres->poczatek),
        porownaj_int);
  return NULL;
}

static void scal(const int *lewy, size_t n_lewy, const int *prawy,
                 size_t n_prawy, int *wynik) {
  size_t i = 0;
  size_t j = 0;
  size_t k = 0;

  while (i < n_lewy && j < n_prawy) {
    wynik[k++] = lewy[i] <= prawy[j] ? lewy[i++] : prawy[j++];
  }

  while (i < n_lewy) {
    wynik[k++] = lewy[i++];
  }
  while (j < n_prawy) {
    wynik[k++] = prawy[j++];
  }
}

int main(void) {
  int dane[] = {9, 1, 8, 2, 7, 3, 6, 4, 5, 0, 11, 10};
  const size_t n = sizeof(dane) / sizeof(dane[0]);
  const size_t srodek = n / 2;

  struct Zakres zakresy[2] = {
      {.poczatek = dane, .liczba = srodek},
      {.poczatek = dane + srodek, .liczba = n - srodek},
  };

  pthread_t watki[2];
  for (size_t i = 0; i < 2; ++i) {
    int wynik = pthread_create(&watki[i], NULL, sortuj_zakres, &zakresy[i]);
    if (wynik != 0) {
      fprintf(stderr, "pthread_create: %d\n", wynik);
      return EXIT_FAILURE;
    }
  }

  for (size_t i = 0; i < 2; ++i) {
    pthread_join(watki[i], NULL);
  }

  int wynik[sizeof(dane) / sizeof(dane[0])];
  scal(dane, srodek, dane + srodek, n - srodek, wynik);

  printf("Posortowane:");
  for (size_t i = 0; i < n; ++i) {
    printf(" %d", wynik[i]);
  }
  printf("\n");

  return EXIT_SUCCESS;
}
