#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
  char imie[32];
  int indeks;
  double srednia;
};

static int porownaj_studentow(const void *lewy, const void *prawy) {
  const struct Student *a = lewy;
  const struct Student *b = prawy;

  if (a->srednia < b->srednia) {
    return 1;
  }
  if (a->srednia > b->srednia) {
    return -1;
  }

  int wynik = strcmp(a->imie, b->imie);
  if (wynik != 0) {
    return wynik;
  }

  return (a->indeks > b->indeks) - (a->indeks < b->indeks);
}

int main(void) {
  struct Student studenci[] = {
      {"Anna", 103, 4.75},
      {"Piotr", 101, 3.90},
      {"Marta", 104, 4.75},
      {"Jan", 102, 4.20},
  };

  const size_t n = sizeof(studenci) / sizeof(studenci[0]);
  qsort(studenci, n, sizeof(studenci[0]), porownaj_studentow);

  for (size_t i = 0; i < n; ++i) {
    printf("%s, indeks %d, srednia %.2f\n", studenci[i].imie,
           studenci[i].indeks, studenci[i].srednia);
  }

  return 0;
}
