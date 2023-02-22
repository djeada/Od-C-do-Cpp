#include <stdio.h>

void zwieksz(int x) { x = x + 5; }

void zwiekszWskaźnik(int *x) { *x = *x + 5; }

void zamienMiejscami(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

int main() {

  int a = 5;
  int b = 20;

  int *wsk1 = &a;
  int *wsk2 = &b;

  printf("Wartość przechowywana przez zmienną a: %d \n", a);
  printf("Wartość przechowywana przez zmienną b: %d \n", b);

  printf("Adres zmiennej a: %d \n", &a);
  printf("Adres zmiennej b: %d \n", &b);

  printf("Wartość przechowywana przez wskaźnik wsk1: %d \n", wsk1);
  printf("Wartość przechowywana przez wskaźnik wsk2: %d \n", wsk2);

  printf("Wartość wskazywana przez wskaźnik wsk1: %d \n", *wsk1);
  printf("Wartość wskazywana przez wskaźnik wsk2: %d \n", *wsk2);

  int tablica[] = {9, 8, 22, 30, 83};

  wsk1 = tablica;

  for (int i = 0; i < 5; i++) {
    printf("Wartość elementu %d tablicy tablica: %d \n", i, *(wsk1++));
  }

  printf("Wartość przed wykonaniem funkcji zwieksz: %d \n", a);
  zwieksz(a);
  printf("Wartość po wykonaniu funkcji zwieksz: %d \n", a);
  zwiekszWskaźnik(&a);
  printf("Wartość po wykonaniu funkcji zwiekszWskaźnik: %d \n", a);

  zamienMiejscami(&a, &b);
  printf("Wartość przechowywana przez zmienną a: %d \n", a);
  printf("Wartość przechowywana przez zmienną b: %d \n", b);

  return 0;
}
