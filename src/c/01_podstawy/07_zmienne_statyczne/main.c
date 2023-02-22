#include <stdio.h>

void foo() {
  int licznik = 0;                 // zwykla zmienna
  static int licznikStatyczny = 0; // zmienna statyczna - przechowuje wartość
                                   // pomiędzy kolejnymi wywołaniami funkcji

  printf("Zwykla zmienna: %d\n", licznik);
  printf("Zmienna statyczna: %d\n", licznikStatyczny);

  licznikStatyczny++;
  licznik++;
}

int main() {
  for (int i = 0; i < 5; i++) {
    foo();
  }
  return 0;
}
