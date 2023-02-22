#include <stdio.h>

int main() {

  int liczbaA = 15;
  int liczbaB = 10;

  int *wskA = &liczbaA;
  int *wskB = &liczbaB;

  ++(*wskA); // Moge zmieniac wartosc przez wskaznik.
  (*wskB)++; // Moge zmieniac wartosc wskaznika.

  printf("Liczba a: %d\n", liczbaA);
  printf("Liczba b: %d\n", liczbaB);

  printf("Wartosc na ktora wskazuje wskA: %d\n", *wskA);
  printf("Wartosc na ktora wskazuje wskB: %d\n", *wskB);

  return 0;
}
