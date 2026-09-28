#include <stdio.h>

void wypisz_liczby(int n) {
  if (n <= 0) {
    return;
  }
  if (n == 1) {
    printf("1");
    return;
  }

  wypisz_liczby(n - 1);
  printf(" %d", n);
}

int main(void) {
  int n = 5;
  wypisz_liczby(n);
  printf("\n");
  return 0;
}
