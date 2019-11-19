#include <stdio.h>

void zmien_wsk(int *wsk, int b) { wsk = &b; }

void zmien_wsk2(int **wsk, int b) { *wsk = &b; }

int main() {
  int a = 10;
  int *p = &a;
  int **pp = &p;

  printf("Wartość zmiennej a: %d\n", a);
  printf("Wartość zmiennej na którą wskazuje wskaźnik p: %d\n", *p);
  printf(
      "Wartość zmiennej na którą wskazuje wskaźnik na który wskazuje pp: %d\n",
      **pp);

  printf("Adres zmiennej a: %lu\n", &a);
  printf("Adres przechowywany przez wskaźnik p: %lu\n", p);

  printf("Adres wskaźnika p: %lu\n", &p);
  printf("Adres przechowywany przez wskaźnik pp: %lu\n", pp);

  a = 15;
  printf("Wartość zmiennej a: %d\n", a);

  *p = 20;
  printf("Wartość zmiennej a: %d\n", a);

  **pp = 7;
  printf("Wartość zmiennej a: %d\n", a);

  int b = 30;
  zmien_wsk(p, b);
  printf("Wartość zmiennej na którą wskazuje wskaźnik p: %d\n", *p);
  zmien_wsk2(&p, b);
  printf("Wartość zmiennej na którą wskazuje wskaźnik p: %d\n", *p);

  return 0;
}
