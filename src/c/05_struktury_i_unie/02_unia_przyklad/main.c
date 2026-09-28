#include <stdio.h>

union Ocena {
  char litera;
  int zaokraglenie;
  float wynik;
};

int main(void) {
  union Ocena ocena;

  ocena.litera = 'A';
  printf("Aktywne pole litera: %c\n", ocena.litera);

  ocena.zaokraglenie = 10;
  printf("Aktywne pole zaokraglenie: %d\n", ocena.zaokraglenie);

  ocena.wynik = 9.7f;
  printf("Aktywne pole wynik: %.1f\n", ocena.wynik);

  printf("Unia przechowuje w danym momencie wartość jednego aktywnego pola.\n");
  return 0;
}
