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

  printf("Wartość przechowywana przez zmienną a: %d \n", a);
  printf("Wartość przechowywana przez zmienną b: %d \n", b);

  printf("Adres zmiennej a: %d \n", &a);
  printf("Adres zmiennej b: %d \n", &b);

  printf("Wartość przechowywana przez wskaźnik p1: %d \n", p1);
  printf("Wartość przechowywana przez wskaźnik p2: %d \n", p2);

  printf("Wartość wskazywana przez wskaźnik p1: %d \n", *p1);
  printf("Wartość wskazywana przez wskaźnik p2: %d \n", *p2);

  int tab[] = {9, 8, 22, 30, 83};

  p1 = tab;

  for (int i = 0; i < 5; i++) {
    printf("Wartość elementu %d tablicy tab: %d \n", i, *(p1++));
  }

  printf("Wartość przed wykonaniem funkcji zwiększ: %d \n", a);
  zwieksz(a);
  printf("Wartość po wykonaniu funkcji zwiększ: %d \n", a);
  zwieksz_wsk(&a);
  printf("Wartość po wykonaniu funkcji zwiększ_ref: %d \n", a);

  swap(&a, &b);
  printf("Wartość przechowywana przez zmienną a: %d \n", a);
  printf("Wartość przechowywana przez zmienną b: %d \n", b);

  return 0;
}
