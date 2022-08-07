#include <stdio.h>

int main() {

  // wypisywanie wartosci na ekran
  printf("Hello World\n");
  printf("1 2 3\n");

  int liczbaCalkowita = 1;
  double liczbaZmiennoPrzecinkowa = 2.72;
  char znak = 'x';

  // wypisywanie zmiennych na ekran
  printf("Wartosc zmiennej liczbaCalkowita: %d\n", liczbaCalkowita);
  printf("Wartosc zmiennej liczbaZmiennoPrzecinkowa: %f\n",
         liczbaZmiennoPrzecinkowa);
  printf("Wartosc zmiennej znak: %c\n", znak);

  // pobieranie danych z klawiatury
  scanf("%d", &liczbaCalkowita);
  scanf("%lf", &liczbaZmiennoPrzecinkowa);
  scanf(" %c", &znak); // uwaga na spacje

  // wypisywanie danych na ekran
  printf("Wartosc liczbaCalkowita: %d\n", liczbaCalkowita);
  printf("Wartosc liczbaZmiennoPrzecinkowa: %f\n", liczbaZmiennoPrzecinkowa);
  printf("Wartosc znak: %c\n", znak);

  // stale
  const int LICZBA_CALKOWITA = 1;
  printf("Wartosc zmiennej LICZBA_CALKOWITA: %d\n", LICZBA_CALKOWITA);

  // nie mozna nadpisac stalej
  // LICZBA_CALKOWITA = 2;

  // mozna pobrac nowe dane z klawiatury ale nie zostana zapisane
  scanf("%d", &LICZBA_CALKOWITA);
  printf("Wartosc zmiennej LICZBA_CALKOWITA: %d\n", LICZBA_CALKOWITA);

  return 0;
}
