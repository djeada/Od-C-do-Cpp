#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
  if (a == b) {
    return;
  }

  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}

int main(void) {
  int liczbaA;
  int liczbaB;

  printf("Podaj dwie liczby: ");
  if (scanf("%d %d", &liczbaA, &liczbaB) != 2) {
    fprintf(stderr, "Nieprawidlowe dane.\n");
    return EXIT_FAILURE;
  }

  printf("Przed zamiana: %d %d\n", liczbaA, liczbaB);
  swap(&liczbaA, &liczbaB);
  printf("Po zamianie: %d %d\n", liczbaA, liczbaB);

  return EXIT_SUCCESS;
}
