#include <stdio.h>

/*
Wstep:
Operacje bitowe sa duzo szybsze niz zwykle operacje arytmetyczne.
Uzywajac maski mozemy operowac na wielu bitach jednoczesnie.

Zastosowania:
-niskopoziomowa kontrola urzadzen
-kompresja danych
-szyfrowanie

Uwaga: liczby sa roznej dlugosci:

- 1 bit: 1b
- 4 bity: 1010b
- 8 bitow: 00110101b
*/

long long decNaBin(int liczba) {
  long long wynik = 0;
  int reszta, pom = 1;

  while (liczba != 0) {
    reszta = liczba % 2;
    liczba /= 2;
    wynik += reszta * pom;
    pom = pom * 10;
  }
  return wynik;
}

int main() {

  int decA = 0;
  int decB = 0;

  printf("Podaj dwie liczby: \n");
  scanf("%d", &decA);
  scanf("%d", &decB);

  long long binA = decNaBin(decA);
  long long binB = decNaBin(decB);

  printf("%d w systemie binarnym to %lld \n", decA, binA);
  printf("%d w systemie binarnym to %lld \n", decB, binB);

  // negacja bitowa
  printf("~%lld = %lld \n", binA, decNaBin(~decA));
  
  // przesuniecie bitowe w lewo o 2 miejsca
  printf("%lld << 2 = %lld \n", binA, decNaBin(decA << 2));

  // AND
  printf("%lld & %lld = %lld \n", binA, binB, decNaBin(decA & decB));
  
  // OR
  printf("%lld | %lld = %lld \n", binA, binB, decNaBin(decA | decB));
  
  // XOR
  printf("%lld ^ %lld = %lld \n", binA, binB, decNaBin(decA ^ decB));

  return 0;
}
