#include <stdio.h>

int napisNaLiczbe(char *napis) {
  int wynik = 0;
  int indeks = 0;
  int znak;
  while (znak = napis[indeks], znak >= '0' && znak <= '9') {
    wynik = 10 * wynik + znak - '0';
    indeks++;
  }
  return wynik;
}

int main() {
  char napis1[] = "93fd";
  char napis2[] = "8  92";
  char napis3[] = " 1  ";

  printf("napis1: %d\n", napisNaLiczbe(napis1));
  printf("napis2: %d\n", napisNaLiczbe(napis2));
  printf("napis3: %d\n", napisNaLiczbe(napis3));

  return 0;
}
