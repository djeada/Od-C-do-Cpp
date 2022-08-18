#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void podmienWartoscNapisuV1(char zrodlo[], char* cel, int dlugosc){
    // odczytuje kolejne znaki napisu cel i zapisuj je w napisie zrodlo
    for (int i = 0; i < dlugosc; i++)
    {
        zrodlo[i] = cel[i];
    }
}

void podmienWartoscNapisuV2(char **zrodlo, char *cel)
{
      // nie zmienia dotychczasowych wartosci zrodla, tylko to na co bedzie wskazywac zrodlo
    *zrodlo = cel;
}

char* utworzNowyNapis(char *cel, int dlugosc)
{
    // nie dotykamy sie do zadnych zewnetrznych danych (poza odczytem)
    char *nowyNapis = (char*)malloc(sizeof(char)*dlugosc);
    for (int i = 0; i < dlugosc; i++)
    {
        nowyNapis[i] = cel[i];
    }
    return nowyNapis;
}


int main(){

    // Przyklad 1:
    // char napis[5] = "ala"; // inicjalizacja
  
    // Przyklad 2:
    // char napis[5];
    // napis = "ala"; // przypisanie

    // Przyklad 3:
    // char napis[5];
    // strcpy(napis, "ala"); // kopiowanie znak po znaku

    // Przyklad 4:
    // char* napis;  // wskaznik jest niezainicjalizowany, wartosc nieznana
    // *napis = "ala";
    // char* innyNapis = "tom";
    // strcpy(napis, innyNapis); // niezdefiniowane zachowanie

    // Przyklad 5:
    // char* napis = "ala"; // wskaznik na staly napis, lepiej uzyc const char*
    // char* innyNapis = "tom";
    // strcpy(napis, innyNapis); // segfault 


    char napis[5] = "ala";
    char innyNapis[5] = "tom";

    podmienWartoscNapisuV1(napis, innyNapis, 5);
    printf("Napis po podmianie: %s\n", napis);
    printf("Inny napis po podmianie: %s\n", innyNapis);
    printf("\n");
  
    char* napisWskaznik = NULL;
    podmienWartoscNapisuV2(&napisWskaznik, innyNapis);
    printf("Napis po podmianie: %s\n", napisWskaznik);
    printf("Inny napis po podmianie: %s\n", innyNapis);
    printf("\n");

    const char* zmodyfikowanyNapis = utworzNowyNapis(innyNapis, 5);
    printf("Zmodyfikowany napis: %s\n", zmodyfikowanyNapis);
    free((void*)zmodyfikowanyNapis);

    return 0;
}
