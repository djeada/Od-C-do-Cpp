#include <stdio.h>

void zwykla_funkcja() {
    printf("Zwykla funkcja\n");
    int a = 1;
    int b = 2;
    printf("Wynik dodawania %d + %d = %d\n", a, b, a + b);
}

void funkcja_z_parametrami(int a, int b) {
    printf("Funkcja z parametrami\n");
    printf("Wynik dodawania %d + %d = %d\n", a, b, a + b);
}

int funkcja_z_parametrami_zwracajaca_wartosc(int a, int b) {
    printf("Funkcja z parametrami zwracajaca wartosc\n");
    printf("Wynik dodawania %d + %d = %d\n", a, b, a + b);
    return a + b;
}

void funkcja_z_parametrami_modyfikujaca_wskaznik(int a, int b, int *wynik) {
    printf("Funkcja z parametrami modyfikujaca wskaznik\n");
    *wynik = a + b;
}

int main() {
       printf("\n");
    zwykla_funkcja();

  printf("\n");
    funkcja_z_parametrami(1, 2);
    
  printf("\n");
    int wynik = funkcja_z_parametrami_zwracajaca_wartosc(1, 2);
    printf("Wynik funkcji zwracajacej wartosc: %d\n", wynik);

     printf("\n");
    funkcja_z_parametrami_modyfikujaca_wskaznik(5, 2, &wynik);
    printf("Wynik funkcji z parametrami modyfikujacej wskaznik: %d + %d = %d\n", 5, 2, wynik);
    
    return 0;
}
