#include <stdio.h>

int dodaj(int a, int b) { return a + b; }

int odejmij(int a, int b) { return a - b; }

int main() {

  // Definicja wskaźnika na funkcję o sygnaturze int(int, int)
  int (*operacja)(int, int);

  // Wskaźnik operacja wskazuje teraz na funkcję dodaj
  operacja = &dodaj;

  // Wywołanie funkcji dodaj przez wskaźnik
  int wynik = operacja(5, 3);
  printf("Wynik dodawania: %d\n", wynik);

  // Wskaźnik operacja wskazuje teraz na funkcję odejmij
  operacja = &odejmij;

  // Wywołanie funkcji odejmij przez wskaźnik
  wynik = operacja(5, 3);
  printf("Wynik odejmowania: %d\n", wynik);

  return 0;
}
