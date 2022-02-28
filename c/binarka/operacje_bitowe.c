#include <stdio.h>

/*
duzo szybsze niz operacje arytmetyczne
-niskopoziomowa kontrola urzadzen
-korekcja bledow
-algorytmy korekcji
-kompresja danych
-szyfrowanie
nie mozna dzuakac na floatach
uzywajac maski mozemy operowac na wielu bitach
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

  printf("~%lld = %lld \n", binA, decNaBin(~decA));
  printf("%lld << 2 = %lld \n", binA, decNaBin(decA << 2));

  printf("%lld & %lld = %lld \n", binA, binB, decNaBin(decA & decB));
  printf("%lld | %lld = %lld \n", binA, binB, decNaBin(decA | decB));
  printf("%lld ^ %lld = %lld \n", binA, binB, decNaBin(decA ^ decB));

  return 0;
}