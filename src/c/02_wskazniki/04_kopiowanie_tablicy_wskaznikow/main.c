#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Zdefiniuj strukturę "Osoba" z dwoma polami: imieniem i wiekiem
struct Osoba {
  char imie[20];
  int wiek;
};

int main() {
  // Alokuj pamięć dla tablicy wskaźników do struktur
  struct Osoba *wskTablica = (struct Osoba *)malloc(3 * sizeof(struct Osoba));

  // Wypełnij tablicę wskaźników danymi
  strcpy(wskTablica[0].imie, "Jan");
  wskTablica[0].wiek = 25;
  strcpy(wskTablica[1].imie, "Joanna");
  wskTablica[1].wiek = 30;
  strcpy(wskTablica[2].imie, "Jacek");
  wskTablica[2].wiek = 35;

  // Skopiuj dane z tablicy wskaźników do tablicy normalnej
  struct Osoba normalnaTablica[3];
  for (int i = 0; i < 3; i++) {
    strcpy(normalnaTablica[i].imie, wskTablica[i].imie);
    normalnaTablica[i].wiek = wskTablica[i].wiek;
  }

  // Zwolnij pamięć z tablicy wskaźników
  free(wskTablica);

  // Wyświetl dane z tablicy normalnej
  for (int i = 0; i < 3; i++) {
    printf("Imię: %s\n", normalnaTablica[i].imie);
    printf("Wiek: %d\n\n", normalnaTablica[i].wiek);
  }

  return 0;
}
