#include <stdio.h>
#include <string.h>

#define MAX_KONTAKTOW 8

struct Kontakt {
  char imie[32];
  char telefon[20];
};

struct KsiazkaAdresowa {
  struct Kontakt kontakty[MAX_KONTAKTOW];
  size_t liczba;
};

static int dodaj_kontakt(struct KsiazkaAdresowa *ksiazka, const char *imie,
                         const char *telefon) {
  if (ksiazka == NULL || imie == NULL || telefon == NULL ||
      ksiazka->liczba >= MAX_KONTAKTOW) {
    return -1;
  }

  struct Kontakt *kontakt = &ksiazka->kontakty[ksiazka->liczba];
  snprintf(kontakt->imie, sizeof(kontakt->imie), "%s", imie);
  snprintf(kontakt->telefon, sizeof(kontakt->telefon), "%s", telefon);
  ++ksiazka->liczba;
  return 0;
}

static const struct Kontakt *znajdz_kontakt(const struct KsiazkaAdresowa *ksiazka,
                                             const char *imie) {
  if (ksiazka == NULL || imie == NULL) {
    return NULL;
  }

  for (size_t i = 0; i < ksiazka->liczba; ++i) {
    if (strcmp(ksiazka->kontakty[i].imie, imie) == 0) {
      return &ksiazka->kontakty[i];
    }
  }
  return NULL;
}

int main(void) {
  struct KsiazkaAdresowa ksiazka = {0};

  dodaj_kontakt(&ksiazka, "Anna", "+48 111 222 333");
  dodaj_kontakt(&ksiazka, "Piotr", "+48 444 555 666");

  const struct Kontakt *kontakt = znajdz_kontakt(&ksiazka, "Piotr");
  if (kontakt != NULL) {
    printf("%s: %s\n", kontakt->imie, kontakt->telefon);
  }

  return 0;
}
