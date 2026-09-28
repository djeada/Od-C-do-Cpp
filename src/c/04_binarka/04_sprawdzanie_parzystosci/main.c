#include <stdbool.h>
#include <stdio.h>

bool czy_parzysta(unsigned int liczba) { return (liczba & 1u) == 0u; }

int main(void) {
  const unsigned int liczby[] = {0u, 1u, 2u, 7u, 42u};

  for (size_t i = 0; i < sizeof(liczby) / sizeof(liczby[0]); ++i) {
    printf("%u jest %s\n", liczby[i],
           czy_parzysta(liczby[i]) ? "parzysta" : "nieparzysta");
  }

  return 0;
}
