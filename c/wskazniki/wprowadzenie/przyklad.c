#include <stdio.h>

void zwieksz(int x) { x = x + 5; }

void zwieksz_wsk(int *x) { *x = *x + 5; }

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

int main() {

  int a = 5;
  int b = 20;

  int *p1 = &a;
  int *p2 = &b;

  printf("Wartosc przechowywana przez zmienna a: %d \n", a);
  printf("Wartosc przechowywana przez zmienna b: %d \n", b);

  printf("Adres zmiennej a: %d \n", &a);
  printf("Adres zmiennej b: %d \n", &b);

  printf("Wartosc przechowywana przez wskaznik p1: %d \n", p1);
  printf("Wartosc przechowywana przez wskaznik p2: %d \n", p2);

  printf("Wartosc wskazywana przez wskaznik p1: %d \n", *p1);
  printf("Wartosc wskazywana przez wskaznik p2: %d \n", *p2);

  int tab[] = {9, 8, 22, 30, 83};

  p1 = tab;

  for (int i = 0; i < 5; i++) {
    printf("Wartosc elementu %d tablicy tab: %d \n", i, *(p1++));
  }

  printf("Wartosc przed wykonaniem funkcji zwieksz: %d \n", a);
  zwieksz(a);
  printf("Wartosc po wykonaniu funkcji zwieksz: %d \n", a);
  zwieksz_wsk(&a);
  printf("Wartosc po wykonaniu funkcji zwieksz_ref: %d \n", a);

  swap(&a, &b);
  printf("Wartosc przechowywana przez zmienna a: %d \n", a);
  printf("Wartosc przechowywana przez zmienna b: %d \n", b);

  return 0;
}
