#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *polacz_napisy(char *napis1, char *napis2) {
  char *wynik = (char *)malloc(strlen(napis1) + strlen(napis2) + 1);
  strcpy(wynik, napis1); // strcpy dziala nawet dla pustych napisow
  strcat(wynik, napis2);
  return wynik;
}

char *usun_n_znakow(char *napis, int n) {
  char *wynik = (char *)malloc(strlen(napis) - n + 1);
  strncpy(wynik, napis, strlen(napis) - n);
  wynik[strlen(napis) - n] = '\0';
  return wynik;
}

int main() {

  // utworz string
  char greeting[] = "Hello";

  printf("%s\n", greeting);

  // dodawanie znakow na koniec napisu daje nieprzewidywalne wyniki
  for (int i = 0; i < 10; i++) {
    greeting[strlen(greeting)] = 'a';
  }

  printf("%s\n", greeting);

  // lepiej uzyc pamieci sterty
  char *nowyNapis = polacz_napisy("Hello", " World");
  printf("%s\n", nowyNapis);

  return 0;
}
