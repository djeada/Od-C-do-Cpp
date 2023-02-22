#include <stdio.h>

int main() {

  // wypisz powitanie na ekran
  printf("Witaj w programie!\n");

  // deklaruj zmienne i przypisz wartości początkowe
  int calkowitaLiczba = 1;
  double liczbaZmiennoPrzecinkowa = 2.72;
  char znak = 'x';

  // wypisz wartości zmiennych na ekran
  printf("Wartość zmiennej calkowitaLiczba: %d\n", calkowitaLiczba);
  printf("Wartość zmiennej liczbaZmiennoPrzecinkowa: %f\n",
         liczbaZmiennoPrzecinkowa);
  printf("Wartość zmiennej znak: %c\n", znak);

  // poproś użytkownika o podanie wartości zmiennych
  printf("Podaj wartość dla zmiennej calkowitaLiczba: ");
  scanf("%d", &calkowitaLiczba);
  printf("Podaj wartość dla zmiennej liczbaZmiennoPrzecinkowa: ");
  scanf("%lf", &liczbaZmiennoPrzecinkowa);
  printf("Podaj wartość dla zmiennej znak: ");
  scanf(" %c", &znak); // uwaga na spację przed %c

  // wypisz wartości zmiennych na ekran
  printf("Nowa wartość calkowitaLiczba: %d\n", calkowitaLiczba);
  printf("Nowa wartość liczbaZmiennoPrzecinkowa: %f\n",
         liczbaZmiennoPrzecinkowa);
  printf("Nowa wartość znak: %c\n", znak);

  // deklaruj stałą
  const int STAŁA_CALKOWITA = 1;
  printf("Wartość stałej STAŁA_CALKOWITA: %d\n", STAŁA_CALKOWITA);

  // próba nadpisania wartości stałej (zakomentowane)
  // STAŁA_CALKOWITA = 2;

  // poproś użytkownika o podanie nowej wartości dla stałej (nie zostanie
  // zapisana)
  printf("Podaj wartość dla stałej STAŁA_CALKOWITA: ");
  scanf("%d", &STAŁA_CALKOWITA);
  printf("Nowa wartość STAŁA_CALKOWITA: %d\n", STAŁA_CALKOWITA);

  return 0;
}
