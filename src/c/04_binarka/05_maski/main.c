#include <stdio.h>
#include <stdlib.h>

#define LICZBA_BITOW 8

char *decNaBin(unsigned int liczba) {
  char *wynik = malloc(LICZBA_BITOW + 1);
  if (wynik == NULL) {
    return NULL;
  }

  for (int i = 0; i < LICZBA_BITOW; i++) {
    wynik[LICZBA_BITOW - 1 - i] = (liczba & (1u << i)) != 0u ? '1' : '0';
  }
  wynik[LICZBA_BITOW] = '\0';
  return wynik;
}

int main(void) {
  unsigned int flaga = 17;
  unsigned int maska = 182;

  char *flagaNapis = decNaBin(flaga);
  char *maskaNapis = decNaBin(maska);
  char *orNapis = decNaBin(flaga | maska);
  char *andNapis = decNaBin(flaga & maska);
  char *xorNapis = decNaBin(flaga ^ maska);

  if (flagaNapis == NULL || maskaNapis == NULL || orNapis == NULL ||
      andNapis == NULL || xorNapis == NULL) {
    free(flagaNapis);
    free(maskaNapis);
    free(orNapis);
    free(andNapis);
    free(xorNapis);
    return EXIT_FAILURE;
  }

  printf("%s\n|\n%s\n=\n%s\n\n", flagaNapis, maskaNapis, orNapis);
  printf("%s\n&\n%s\n=\n%s\n\n", flagaNapis, maskaNapis, andNapis);
  printf("%s\n^\n%s\n=\n%s\n\n", flagaNapis, maskaNapis, xorNapis);

  unsigned int n = 3;
  unsigned int nowaMaska = 1u << (n - 1u);
  char *nowaMaskaNapis = decNaBin(nowaMaska);
  char *statusBituNapis = decNaBin(flaga & nowaMaska);

  if (nowaMaskaNapis == NULL || statusBituNapis == NULL) {
    free(flagaNapis);
    free(maskaNapis);
    free(orNapis);
    free(andNapis);
    free(xorNapis);
    free(nowaMaskaNapis);
    free(statusBituNapis);
    return EXIT_FAILURE;
  }

  printf("%s\n&\n%s\n=\n%s\n", flagaNapis, nowaMaskaNapis,
         statusBituNapis);

  free(flagaNapis);
  free(maskaNapis);
  free(orNapis);
  free(andNapis);
  free(xorNapis);
  free(nowaMaskaNapis);
  free(statusBituNapis);

  return EXIT_SUCCESS;
}
