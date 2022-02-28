#include <stdio.h>

int main() {

  int a = 10;
  double b = 3.14;
  char c = 'k';

  void *vp = &a;
  printf("Wartosc a: %d \n", *(int *)vp);

  vp = &b;
  printf("Wartosc b: %.2f \n", *(double *)vp);

  vp = &c;
  printf("Wartosc c: %c \n", *(char *)vp);

  vp = &a;
  int *p1 = (int *)vp;
  printf("Wartosc a: %d \n", *p1);

  vp = &b;
  double *p2 = (double *)vp;
  printf("Wartosc b: %.2f \n", *p2);

  vp = &c;
  char *p3 = (char *)vp;
  printf("Wartosc c: %c \n", *p3);

  vp = p1;
  printf("Wartosc a: %d \n", *(int *)vp);

  *(int *)vp = *(int *)vp + 10;
  printf("Wartosc a: %d \n", *(int *)vp);

  return 0;
}
