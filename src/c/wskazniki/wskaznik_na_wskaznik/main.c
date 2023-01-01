#include <stdio.h>

void zmien_wsk(int *wsk, int b) { wsk = &b; }

void zmien_wsk2(int **wsk, int b) { *wsk = &b; }

int main() {
  int a = 10;
  int *p = &a;
  int **pp = &p;

  printf("Wartosc zmiennej a: %d\n", a);
  printf("Wartosc zmiennej na ktora wskazuje wskaznik p: %d\n", *p);
  printf(
      "Wartosc zmiennej na ktora wskazuje wskaznik na ktory wskazuje pp: %d\n",
      **pp);

  printf("Adres zmiennej a: %lu\n", &a);
  printf("Adres przechowywany przez wskaznik p: %lu\n", p);

  printf("Adres wskaznika p: %lu\n", &p);
  printf("Adres przechowywany przez wskaznik pp: %lu\n", pp);

  a = 15;
  printf("Wartosc zmiennej a: %d\n", a);

  *p = 20;
  printf("Wartosc zmiennej a: %d\n", a);

  **pp = 7;
  printf("Wartosc zmiennej a: %d\n", a);

  int b = 30;
  zmien_wsk(p, b);
  printf("Wartosc zmiennej na ktora wskazuje wskaznik p: %d\n", *p);
  zmien_wsk2(&p, b);
  printf("Wartosc zmiennej na ktora wskazuje wskaznik p: %d\n", *p);

  return 0;
}
