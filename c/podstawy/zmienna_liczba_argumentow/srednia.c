#include <stdio.h>

double srednia(const int liczba_elementow, ...) {
  va_list lista;
  double suma = 0.0;

  va_start(lista, liczba_elementow);
  for (int i = 0; i < liczba_elementow; ++i) {
    suma += va_arg(lista, double);
  }
  va_end(lista);
  return suma / liczba_elementow;
}

int main() {

  printf("Srednia z liczb 3.0, 5.0, 2.0, 4.0, 0.0: %f\n",
         srednia(5, 3.0, 5.0, 2.0, 4.0, 0.0));
  printf("Srednia z liczb 1.0, 2.0, 3.0: %f\n", srednia(3, 1.0, 2.0, 3.0));

  return 0;
}
