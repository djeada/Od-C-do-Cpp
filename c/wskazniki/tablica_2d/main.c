#include <stdlib.h>
#include <stdio.h>

#define LICZBA_WIERSZY 5
#define LICZBA_KOLUMN 10

int main(int argc, char *argv[]) {
  
  // tablica 2D
  int** tablica = malloc(LICZBA_WIERSZY * sizeof(int*));
    for (int i = 0; i < LICZBA_WIERSZY; i++) {
        tablica[i] = malloc(LICZBA_KOLUMN * sizeof(int));
    }

    // wypelnienie tablicy
    // tabliczka mnozenia
    for (int i = 0; i < LICZBA_WIERSZY; i++) {
        for (int j = 0; j < LICZBA_KOLUMN; j++) {
            tablica[i][j] = (i + 1)* (j + 1);
        }
    }

    // wypisanie tablicy
    for (int i = 0; i < LICZBA_WIERSZY; i++) {
        for (int j = 0; j < LICZBA_KOLUMN; j++) {
            printf("%d ", tablica[i][j]);
        }
        printf("\n");
    }

    // zwolnienie pamieci
    for (int i = 0; i < LICZBA_WIERSZY; i++) {
        free(tablica[i]);
    }
    free(tablica);


    return 0;
}

