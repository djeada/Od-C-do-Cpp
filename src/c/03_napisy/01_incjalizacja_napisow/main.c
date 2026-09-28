#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void podmienWartoscNapisuV1(char zrodlo[], const char *cel, size_t dlugosc) {
  memcpy(zrodlo, cel, dlugosc);
}

void podmienWartoscNapisuV2(char **zrodlo, char *cel) { *zrodlo = cel; }

char *utworzNowyNapis(const char *cel) {
  size_t dlugosc = strlen(cel) + 1;
  char *nowyNapis = malloc(dlugosc);
  if (nowyNapis == NULL) {
    return NULL;
  }

  memcpy(nowyNapis, cel, dlugosc);
  return nowyNapis;
}

int main(void) {
  char napis[5] = "ala";
  char innyNapis[5] = "tom";

  podmienWartoscNapisuV1(napis, innyNapis, sizeof(napis));
  printf("Napis po podmianie: %s\n", napis);
  printf("Inny napis po podmianie: %s\n\n", innyNapis);

  char *napisWskaznik = NULL;
  podmienWartoscNapisuV2(&napisWskaznik, innyNapis);
  printf("Napis po podmianie: %s\n", napisWskaznik);
  printf("Inny napis po podmianie: %s\n\n", innyNapis);

  char *zmodyfikowanyNapis = utworzNowyNapis(innyNapis);
  if (zmodyfikowanyNapis == NULL) {
    fprintf(stderr, "Blad alokacji pamieci.\n");
    return EXIT_FAILURE;
  }

  printf("Zmodyfikowany napis: %s\n", zmodyfikowanyNapis);
  free(zmodyfikowanyNapis);

  return EXIT_SUCCESS;
}
