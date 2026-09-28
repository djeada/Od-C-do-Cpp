#include <stddef.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  char napis[] = "Hello World!";
  printf("%s\n", napis);

  char *indeksWsk = strchr(napis, 'o');
  if (indeksWsk != NULL) {
    printf("Pierwsze 'o': %td\n", indeksWsk - napis);
  }

  indeksWsk = strchr(napis, 'x');
  if (indeksWsk != NULL) {
    printf("Pierwsze 'x': %td\n", indeksWsk - napis);
  } else {
    printf("Nie znaleziono znaku 'x'\n");
  }

  indeksWsk = strchr(napis, 'o');
  while (indeksWsk != NULL) {
    printf("Znaleziono 'o' na indeksie: %td\n", indeksWsk - napis);
    indeksWsk = strchr(indeksWsk + 1, 'o');
  }

  return 0;
}
