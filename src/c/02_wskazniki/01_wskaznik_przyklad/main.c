#include <stdio.h>

void zwieksz(int x) { x = x + 5; }

void zwiekszWskaznik(int *x) { *x = *x + 5; }

void zamienMiejscami(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

int main(void) {
  int a = 5;
  int b = 20;

  int *wsk1 = &a;
  int *wsk2 = &b;

  printf("Wartość przechowywana przez zmienną a: %d\n", a);
  printf("Wartość przechowywana przez zmienną b: %d\n", b);

  printf("Adres zmiennej a: %p\n", (void *)&a);
  printf("Adres zmiennej b: %p\n", (void *)&b);

  printf("Adres przechowywany przez wsk1: %p\n", (void *)wsk1);
  printf("Adres przechowywany przez wsk2: %p\n", (void *)wsk2);

  printf("Wartość wskazywana przez wsk1: %d\n", *wsk1);
  printf("Wartość wskazywana przez wsk2: %d\n", *wsk2);

  int tablica[] = {9, 8, 22, 30, 83};
  wsk1 = tablica;

  for (size_t i = 0; i < sizeof(tablica) / sizeof(tablica[0]); i++) {
    printf("Wartość elementu %zu tablicy: %d\n", i, *wsk1++);
  }

  printf("Wartość przed wykonaniem funkcji zwieksz: %d\n", a);
  zwieksz(a);
  printf("Wartość po wykonaniu funkcji zwieksz: %d\n", a);
  zwiekszWskaznik(&a);
  printf("Wartość po wykonaniu funkcji zwiekszWskaznik: %d\n", a);

  zamienMiejscami(&a, &b);
  printf("Wartość przechowywana przez zmienną a: %d\n", a);
  printf("Wartość przechowywana przez zmienną b: %d\n", b);

  return 0;
}
