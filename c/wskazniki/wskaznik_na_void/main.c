#include <stdio.h>

int main() {

  int a = 10;
  double b = 3.14;
  char c = 'k';

  void *vp = &a;
  printf("Wartość a: %d \n", *(int *)vp);

  vp = &b;
  printf("Wartość b: %.2f \n", *(double *)vp);

  vp = &c;
  printf("Wartość c: %c \n", *(char *)vp);

  vp = &a;
  int *p1 = (int *)vp;
  printf("Wartość a: %d \n", *p1);

  vp = &b;
  double *p2 = (double *)vp;
  printf("Wartość b: %.2f \n", *p2);

  vp = &c;
  char *p3 = (char *)vp;
  printf("Wartość c: %c \n", *p3);

  vp = p1;
  printf("Wartość a: %d \n", *(int *)vp);

  *(int *)vp = *(int *)vp + 10;
  printf("Wartość a: %d \n", *(int *)vp);

  return 0;
}
