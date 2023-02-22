#include <stdio.h>

// Funkcja bez parametrów i wartości zwracanej
void print_zwykla_funkcja() {
  printf("Jestem zwykłą funkcją\n");
  int a = 1;
  int b = 2;
  printf("Wynik dodawania %d + %d = %d\n", a, b, a + b);
}

// Funkcja z parametrami i bez wartości zwracanej
void print_funkcja_z_parametrami(int a, int b) {
  printf("Jestem funkcją z parametrami\n");
  printf("Wynik dodawania %d + %d = %d\n", a, b, a + b);
}

// Funkcja z parametrami i wartością zwracaną
int funkcja_z_parametrami_zwracajaca_wartosc(int a, int b) {
  printf("Jestem funkcją z parametrami i zwracająca wartość\n");
  printf("Wynik dodawania %d + %d = %d\n", a, b, a + b);
  return a + b;
}

// Funkcja z parametrami i modyfikująca wartość wskazywaną przez wskaźnik
void funkcja_z_parametrami_modyfikujaca_wskaznik(int a, int b, int *wynik) {
  printf("Jestem funkcją z parametrami i modyfikuję wartość przez wskaźnik\n");
  *wynik = a + b;
}

int main() {
  printf("\n");
  print_zwykla_funkcja();

  printf("\n");
  print_funkcja_z_parametrami(1, 2);

  printf("\n");
  int wynik = funkcja_z_parametrami_zwracajaca_wartosc(1, 2);
  printf("Wynik funkcji zwracającej wartość: %d\n", wynik);

  printf("\n");
  int wynik2;
  funkcja_z_parametrami_modyfikujaca_wskaznik(5, 2, &wynik2);
  printf("Wynik funkcji modyfikującej wartość przez wskaźnik: %d + %d = %d\n",
         5, 2, wynik2);

  return 0;
}
