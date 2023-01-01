#include <stdio.h>

int main() {

  int liczba_a = 15;
  int liczba_b = 10;

  int *wsk_a = &liczba_a;
  int *wsk_b = &liczba_b;

  ++*wsk_a; // To samo co ++(*wsk). Moge zmieniac wartosc przez wskaznik.
  *wsk_b++; // To samo co *(wsk++). Moge zmieniac wartosc wskaznika.

  printf("Liczba a: %d\n", liczba_a);
  printf("Liczba b: %d\n", liczba_b);

  printf("Wartosc na ktora wskazuje wsk_a: %d\n", *wsk_a);
  printf("Wartosc na ktora wskazuje wsk_b: %d\n", *wsk_b);

  return 0;
}
