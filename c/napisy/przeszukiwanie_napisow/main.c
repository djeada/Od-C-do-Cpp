
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    
    // utworz napis
    char napis[] = "Hello World!";

    // wyswietl napis
    printf("%s\n", napis);

    // znajdz indeks pierwszego wystapienia znaku 'o'
    char* indeksWsk = strchr(napis, 'o');
    printf("%ld\n", indeksWsk - napis);


    // co jesli nie ma danego znaku?
    indeksWsk = strchr(napis, 'x');
    printf("%ld\n", indeksWsk - napis);

    // lepiej sprawdzic czy nie wskaznik nie jest NULL
    if (indeksWsk != NULL) {
        printf("%ld\n", indeksWsk - napis);
    } else {
        printf("Nie znaleziono znaku\n");
    }

    // co jesli chcemy wszystkie wystapienia danego znaku?
    indeksWsk = strchr(napis, 'o');
    while (indeksWsk != NULL) {
        printf("%ld\n", indeksWsk - napis);
        indeksWsk = strchr(indeksWsk + 1, 'o');
    }
  
    return 0;
}
