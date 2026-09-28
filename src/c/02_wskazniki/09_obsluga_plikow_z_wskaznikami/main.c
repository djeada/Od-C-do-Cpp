#include <stdio.h>
#include <stdlib.h>

int zapiszDoPliku(const char *nazwa_pliku, const char *tekst) {
  FILE *plik = fopen(nazwa_pliku, "w");
  if (plik == NULL) {
    perror("fopen");
    return -1;
  }

  if (fprintf(plik, "%s", tekst) < 0) {
    perror("fprintf");
    fclose(plik);
    return -1;
  }

  if (fclose(plik) == EOF) {
    perror("fclose");
    return -1;
  }

  return 0;
}

int wyswietlPlik(const char *nazwa_pliku) {
  FILE *plik = fopen(nazwa_pliku, "r");
  if (plik == NULL) {
    perror("fopen");
    return -1;
  }

  int ch;
  while ((ch = fgetc(plik)) != EOF) {
    if (putchar(ch) == EOF) {
      fclose(plik);
      return -1;
    }
  }

  if (ferror(plik)) {
    perror("fgetc");
    fclose(plik);
    return -1;
  }

  return fclose(plik) == 0 ? 0 : -1;
}

int main(void) {
  const char *tekst =
      "To jest tekst, ktory zapiszemy do pliku.\nMoze byc w nim kilka linijek.\n";

  if (zapiszDoPliku("plik.txt", tekst) != 0) {
    return EXIT_FAILURE;
  }
  if (wyswietlPlik("plik.txt") != 0) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
