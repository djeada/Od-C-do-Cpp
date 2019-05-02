#include <stdio.h>

int a = 10;

static void zwieksz() {

  printf("Zwieksz \n");

  int liczba = 5;

  printf("%d \n", liczba);
  printf("%d \n", a);

  a += 1;
  liczba += 2;
}

static void zwieksz2() {

  printf("Zwieksz2 \n");

  static int liczba = 5;

  printf("%d \n", liczba);
  printf("%d \n", a);

  a -= 3;
  liczba += 2;
}

int main() {

  zwieksz();
  zwieksz2();

  zwieksz();
  zwieksz2();

  funkcja1();

  return 0;
}
