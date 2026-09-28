#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static void wypiszBinarnie(unsigned int liczba) {
  for (int bit = (int)(sizeof(liczba) * CHAR_BIT) - 1; bit >= 0; --bit) {
    putchar((liczba & (1u << bit)) != 0u ? '1' : '0');
  }
}

static int wczytajPozycje(unsigned int *pozycja) {
  const unsigned int liczbaBitow = (unsigned int)(sizeof(unsigned int) * CHAR_BIT);
  if (scanf("%u", pozycja) != 1 || *pozycja >= liczbaBitow) {
    fprintf(stderr, "Pozycja musi byc w zakresie 0-%u.\n", liczbaBitow - 1u);
    return -1;
  }
  return 0;
}

int main(void) {
  unsigned int liczba;
  printf("Podaj nieujemna liczbe: ");
  if (scanf("%u", &liczba) != 1) {
    return EXIT_FAILURE;
  }

  printf("Binarnie: ");
  wypiszBinarnie(liczba);
  printf("\n");

  unsigned int pozycja;

  printf("Podaj pozycje bitu, ktory chcesz sprawdzic: ");
  if (wczytajPozycje(&pozycja) != 0) {
    return EXIT_FAILURE;
  }
  printf("Bit %u: %u\n", pozycja, (liczba >> pozycja) & 1u);

  printf("Podaj pozycje bitu, ktory chcesz ustawic: ");
  if (wczytajPozycje(&pozycja) != 0) {
    return EXIT_FAILURE;
  }
  liczba |= 1u << pozycja;
  wypiszBinarnie(liczba);
  printf("\n");

  printf("Podaj pozycje bitu, ktory chcesz wyczyscic: ");
  if (wczytajPozycje(&pozycja) != 0) {
    return EXIT_FAILURE;
  }
  liczba &= ~(1u << pozycja);
  wypiszBinarnie(liczba);
  printf("\n");

  return EXIT_SUCCESS;
}
