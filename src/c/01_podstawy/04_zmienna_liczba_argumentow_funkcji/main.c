#include <stdarg.h>
#include <stdio.h>

double obliczSrednia(int liczbaElementow, ...) {
  if (liczbaElementow <= 0) {
    return 0.0;
  }

  va_list listaArgumentow;
  double suma = 0.0;

  va_start(listaArgumentow, liczbaElementow);
  for (int i = 0; i < liczbaElementow; ++i) {
    suma += va_arg(listaArgumentow, double);
  }
  va_end(listaArgumentow);

  return suma / liczbaElementow;
}

int main(void) {
  printf("Średnia z liczb 3.0, 5.0, 2.0, 4.0, 0.0: %f\n",
         obliczSrednia(5, 3.0, 5.0, 2.0, 4.0, 0.0));
  printf("Średnia z liczb 1.0, 2.0, 3.0: %f\n",
         obliczSrednia(3, 1.0, 2.0, 3.0));
  return 0;
}
