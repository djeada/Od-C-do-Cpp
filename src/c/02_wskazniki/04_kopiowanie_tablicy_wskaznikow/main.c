#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Osoba {
  char imie[20];
  int wiek;
};

int main(void) {
  const size_t liczbaOsob = 3;
  struct Osoba *wskTablica = malloc(liczbaOsob * sizeof(*wskTablica));
  if (wskTablica == NULL) {
    fprintf(stderr, "Blad alokacji pamieci.\n");
    return EXIT_FAILURE;
  }

  snprintf(wskTablica[0].imie, sizeof(wskTablica[0].imie), "%s", "Jan");
  wskTablica[0].wiek = 25;
  snprintf(wskTablica[1].imie, sizeof(wskTablica[1].imie), "%s", "Joanna");
  wskTablica[1].wiek = 30;
  snprintf(wskTablica[2].imie, sizeof(wskTablica[2].imie), "%s", "Jacek");
  wskTablica[2].wiek = 35;

  struct Osoba normalnaTablica[3];
  memcpy(normalnaTablica, wskTablica, sizeof(normalnaTablica));
  free(wskTablica);

  for (size_t i = 0; i < liczbaOsob; i++) {
    printf("Imię: %s\n", normalnaTablica[i].imie);
    printf("Wiek: %d\n\n", normalnaTablica[i].wiek);
  }

  return EXIT_SUCCESS;
}
