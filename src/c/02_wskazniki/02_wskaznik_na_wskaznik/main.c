#include <stdio.h>

void zmienWskaznik(int *wsk, int b) { wsk = &b; }

void zmienWskaznik2(int **wsk, int b) { *wsk = &b; }

int main() {
  int a = 10;
  int *p = &a;
  int **pp = &p;

  printf("Wartosc zmiennej a: %d\n", a);
  printf("Wartosc zmiennej na ktora wskazuje wskaznik p: %d\n", *p);
  printf(
      "Wartosc zmiennej na ktora wskazuje wskaznik na ktory wskazuje pp: %d\n",
      **pp);

  printf("Adres zmiennej a: %p\n", (void *)&a);
  printf("Adres przechowywany przez wskaznik p: %p\n", (void *)p);

  printf("Adres wskaznika p: %p\n", (void *)&p);
  printf("Adres przechowywany przez wskaznik pp: %p\n", (void *)pp);

  a = 15;
  printf("Wartosc zmiennej a: %d\n", a);

  *p = 20;
  printf("Wartosc zmiennej a: %d\n", a);

  **pp = 7;
  printf("Wartosc zmiennej a: %d\n", a);

  int b = 30;
  zmienWskaznik(p, b);
  printf("Wartosc zmiennej na ktora wskazuje wskaznik p: %d\n", *p);

  zmienWskaznik2(&p, b);
  printf("Wartosc zmiennej na ktora wskazuje wskaznik p: %d\n", *p);

  return 0;
}
