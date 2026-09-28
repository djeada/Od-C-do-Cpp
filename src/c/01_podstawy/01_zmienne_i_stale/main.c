#include <stdio.h>
#include <stdlib.h>

int main(void) {
  printf("Witaj w programie!\n");

  int calkowitaLiczba = 1;
  double liczbaZmiennoPrzecinkowa = 2.72;
  char znak = 'x';

  printf("Wartość zmiennej calkowitaLiczba: %d\n", calkowitaLiczba);
  printf("Wartość zmiennej liczbaZmiennoPrzecinkowa: %f\n",
         liczbaZmiennoPrzecinkowa);
  printf("Wartość zmiennej znak: %c\n", znak);

  printf("Podaj wartość dla zmiennej calkowitaLiczba: ");
  if (scanf("%d", &calkowitaLiczba) != 1) {
    fprintf(stderr, "Nieprawidlowa liczba calkowita.\n");
    return EXIT_FAILURE;
  }

  printf("Podaj wartość dla zmiennej liczbaZmiennoPrzecinkowa: ");
  if (scanf("%lf", &liczbaZmiennoPrzecinkowa) != 1) {
    fprintf(stderr, "Nieprawidlowa liczba zmiennoprzecinkowa.\n");
    return EXIT_FAILURE;
  }

  printf("Podaj wartość dla zmiennej znak: ");
  if (scanf(" %c", &znak) != 1) {
    fprintf(stderr, "Nieprawidlowy znak.\n");
    return EXIT_FAILURE;
  }

  printf("Nowa wartość calkowitaLiczba: %d\n", calkowitaLiczba);
  printf("Nowa wartość liczbaZmiennoPrzecinkowa: %f\n",
         liczbaZmiennoPrzecinkowa);
  printf("Nowa wartość znak: %c\n", znak);

  const int STALA_CALKOWITA = 1;
  printf("Wartość stałej STALA_CALKOWITA: %d\n", STALA_CALKOWITA);

  // Stałej nie można nadpisać. Wartość od użytkownika trzeba wczytać do
  // osobnej, modyfikowalnej zmiennej.
  int propozycjaNowejWartosci;
  printf("Podaj proponowaną nową wartość dla stałej STALA_CALKOWITA: ");
  if (scanf("%d", &propozycjaNowejWartosci) != 1) {
    fprintf(stderr, "Nieprawidlowa liczba calkowita.\n");
    return EXIT_FAILURE;
  }

  printf("Stała nadal ma wartość: %d (podano: %d)\n", STALA_CALKOWITA,
         propozycjaNowejWartosci);

  return EXIT_SUCCESS;
}
