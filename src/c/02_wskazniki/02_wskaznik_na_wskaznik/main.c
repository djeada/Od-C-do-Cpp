#include <stdio.h>

void zmienWskaznikLokalnie(int *wsk, int *nowyCel) {
  wsk = nowyCel;
  printf("Wewnatrz funkcji lokalny wskaznik wskazuje na: %d\n", *wsk);
}

void zmienWskaznik(int **wsk, int *nowyCel) { *wsk = nowyCel; }

int main(void) {
  int a = 10;
  int b = 30;
  int *p = &a;
  int **pp = &p;

  printf("Wartosc zmiennej a: %d\n", a);
  printf("Wartosc przez p: %d\n", *p);
  printf("Wartosc przez pp: %d\n", **pp);

  printf("Adres zmiennej a: %p\n", (void *)&a);
  printf("Adres przechowywany przez p: %p\n", (void *)p);
  printf("Adres wskaznika p: %p\n", (void *)&p);
  printf("Adres przechowywany przez pp: %p\n", (void *)pp);

  zmienWskaznikLokalnie(p, &b);
  printf("Po zmianie lokalnej p nadal wskazuje na: %d\n", *p);

  zmienWskaznik(&p, &b);
  printf("Po zmianie przez int ** p wskazuje na: %d\n", *p);

  return 0;
}
