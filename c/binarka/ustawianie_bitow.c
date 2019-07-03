#include <stdio.h>

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
  int liczba;

  printf("Podaj liczbe: \n");
  scanf("%d", &liczba);

  long long bin = decNaBin(liczba);
  printf("%d w systemie binarnym to %lld \n", liczba, bin);

  int pozycja;

  // indeksowanie od 0
  printf("Podaj pozycje bitu, ktory chcesz sprawdzic: \n");
  scanf("%d", &pozycja);

  // Check if bit on position pozycja is 1 or 0
  int statusBitu = (liczba >> pozycja) & 1;
  printf("Bit na pozycji %d w liczbie %lld to %d \n", pozycja, bin, statusBitu);

  printf("Podaj pozycje bitu, ktory chcesz ustawic: \n");
  scanf("%d", &pozycja);

  liczba = liczba | (1 << pozycja);
  printf("Po ustawieniu bitu na pozycji %d w liczbie %lld to %lld \n", pozycja,
         bin, decNaBin(liczba));

  printf("Podaj pozycje bitu, ktory chcesz usunac: \n");
  scanf("%d", &pozycja);

  liczba = liczba & ~(1 << pozycja);
  printf("Po usunieciu bitu na pozycji %d w liczbie %lld to %lld \n", pozycja,
         bin, decNaBin(liczba));

  return 0;
}