#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static void wypiszBinarnie(unsigned int liczba) {
  for (int bit = (int)(sizeof(liczba) * CHAR_BIT) - 1; bit >= 0; --bit) {
    putchar((liczba & (1u << bit)) != 0u ? '1' : '0');
  }
}

static void wypiszOperacje(const char *opis, unsigned int wynik) {
  printf("%s: ", opis);
  wypiszBinarnie(wynik);
  printf(" (%u)\n", wynik);
}

int main(void) {
  unsigned int a;
  unsigned int b;

  printf("Podaj dwie nieujemne liczby: ");
  if (scanf("%u %u", &a, &b) != 2) {
    fprintf(stderr, "Nieprawidlowe dane.\n");
    return EXIT_FAILURE;
  }

  printf("a: ");
  wypiszBinarnie(a);
  printf(" (%u)\n", a);

  printf("b: ");
  wypiszBinarnie(b);
  printf(" (%u)\n", b);

  wypiszOperacje("~a", ~a);
  wypiszOperacje("a << 2", a << 2u);
  wypiszOperacje("a & b", a & b);
  wypiszOperacje("a | b", a | b);
  wypiszOperacje("a ^ b", a ^ b);

  return EXIT_SUCCESS;
}
