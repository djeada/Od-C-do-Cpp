#include <limits.h>
#include <stdio.h>

int napisNaLiczbe(const char *napis, int *wynik) {
  if (napis == NULL || wynik == NULL || *napis < '0' || *napis > '9') {
    return -1;
  }

  int wartosc = 0;
  for (size_t i = 0; napis[i] >= '0' && napis[i] <= '9'; ++i) {
    int cyfra = napis[i] - '0';
    if (wartosc > (INT_MAX - cyfra) / 10) {
      return -1;
    }
    wartosc = wartosc * 10 + cyfra;
  }

  *wynik = wartosc;
  return 0;
}

int main(void) {
  const char *napisy[] = {"93fd", "8  92", " 1  "};

  for (size_t i = 0; i < sizeof(napisy) / sizeof(napisy[0]); ++i) {
    int wynik;
    if (napisNaLiczbe(napisy[i], &wynik) == 0) {
      printf("%s -> %d\n", napisy[i], wynik);
    } else {
      printf("%s -> brak liczby na poczatku lub przepelnienie\n", napisy[i]);
    }
  }

  return 0;
}
