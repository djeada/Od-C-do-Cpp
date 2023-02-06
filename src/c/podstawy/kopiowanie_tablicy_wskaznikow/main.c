#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Zdefiniuj strukturę "Osoba" z dwoma członkami: imieniem i wiekiem
struct Osoba {
    char imie[20];
    int wiek;
};

int main() {
    // Alokuj pamięć dla tablicy wskaźników do struktur
    struct Osoba *ptrTablica = (struct Osoba*)malloc(3 * sizeof(struct Osoba));

    // Wypełnij tablicę wskaźników danymi
    strcpy(ptrTablica[0].imie, "Jan");
    ptrTablica[0].wiek = 25;
    strcpy(ptrTablica[1].imie, "Joanna");
    ptrTablica[1].wiek = 30;
    strcpy(ptrTablica[2].imie, "Jacek");
    ptrTablica[2].wiek = 35;

    // Skopiuj dane z tablicy wskaźników do tablicy normalnej
    struct Osoba normalnaTablica[3];
    for (int i = 0; i < 3; i++) {
        strcpy(normalnaTablica[i].imie, ptrTablica[i].imie);
        normalnaTablica[i].wiek = ptrTablica[i].wiek;
    }
    // Zwolnij pamięć z tablicy wskaźników
    free(ptrTablica);
  
    // Wyświetl dane z tablicy normalnej
    for (int i = 0; i < 3; i++) {
        printf("Imię: %s\n", normalnaTablica[i].imie);
        printf("Wiek: %d\n\n", normalnaTablica[i].wiek);
    }
  
    return 0;
}
