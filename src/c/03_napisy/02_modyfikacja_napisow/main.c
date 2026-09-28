#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *polacz_napisy(const char *napis1, const char *napis2) {
  size_t dlugosc1 = strlen(napis1);
  size_t dlugosc2 = strlen(napis2);
  char *wynik = malloc(dlugosc1 + dlugosc2 + 1);
  if (wynik == NULL) {
    return NULL;
  }

  memcpy(wynik, napis1, dlugosc1);
  memcpy(wynik + dlugosc1, napis2, dlugosc2 + 1);
  return wynik;
}

char *usun_n_znakow(const char *napis, size_t n) {
  size_t dlugosc = strlen(napis);
  if (n > dlugosc) {
    return NULL;
  }

  size_t nowa_dlugosc = dlugosc - n;
  char *wynik = malloc(nowa_dlugosc + 1);
  if (wynik == NULL) {
    return NULL;
  }

  memcpy(wynik, napis, nowa_dlugosc);
  wynik[nowa_dlugosc] = '\0';
  return wynik;
}

int main(void) {
  char greeting[16] = "Hello";

  printf("%s\n", greeting);

  for (int i = 0; i < 10; i++) {
    size_t dlugosc = strlen(greeting);
    greeting[dlugosc] = 'a';
    greeting[dlugosc + 1] = '\0';
  }

  printf("%s\n", greeting);

  char *nowyNapis = polacz_napisy("Hello", " World");
  if (nowyNapis == NULL) {
    fprintf(stderr, "Nie udalo sie zaalokowac pamieci.\n");
    return EXIT_FAILURE;
  }
  printf("%s\n", nowyNapis);

  char *krotszyNapis = usun_n_znakow(nowyNapis, 6);
  if (krotszyNapis == NULL) {
    free(nowyNapis);
    fprintf(stderr, "Nie udalo sie skrocic napisu.\n");
    return EXIT_FAILURE;
  }
  printf("%s\n", krotszyNapis);

  free(krotszyNapis);
  free(nowyNapis);
  return EXIT_SUCCESS;
}
