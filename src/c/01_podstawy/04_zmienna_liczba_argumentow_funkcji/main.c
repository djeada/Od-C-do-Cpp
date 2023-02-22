#include <stdarg.h>
#include <stdio.h>

/**

    Oblicza średnią arytmetyczną z listy argumentów o zmiennej długości.
    @param liczbaElementow Liczba elementów na liście.
    @param ... Lista argumentów o zmiennej długości.
    @return Średnia arytmetyczna.
    */
double obliczSrednia(const int liczbaElementow, ...) {
  va_list listaArgumentow; // Zmienna przechowująca argumenty z listy.
  double suma = 0.0;

  va_start(listaArgumentow,
           liczbaElementow); // Rozpoczęcie przetwarzania argumentów.
  for (int i = 0; i < liczbaElementow; ++i) {
    suma += va_arg(listaArgumentow, double); // Pobranie kolejnego argumentu.
  }
  va_end(listaArgumentow);       // Zakończenie przetwarzania argumentów.
  return suma / liczbaElementow; // Obliczenie średniej arytmetycznej.
}

int main() {
  printf("Średnia z liczb 3.0, 5.0, 2.0, 4.0, 0.0: %f\n",
         obliczSrednia(5, 3.0, 5.0, 2.0, 4.0, 0.0));
  printf("Średnia z liczb 1.0, 2.0, 3.0: %f\n",
         obliczSrednia(3, 1.0, 2.0, 3.0));
  return 0;
}
