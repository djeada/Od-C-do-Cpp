#include <stdio.h>de 

union Ocena {
    char litera;
    int zaokraglenie;
    float wynik;
};

int main()  {
    union Ocena ocena;

    ocena.litera = 'A';
    ocena.zaokraglenie = 10;
    ocena.wynik = 9.7;

    printf("Uczeń otrzymał ocenę %c %d %f\n", ocena.litera, ocena.zaokraglenie, ocena.wynik);

    union Ocena ocena2;
    
    ocena2.litera = 'B';
    printf("Uczeń otrzymał ocenę %c\n", ocena2.litera);

    ocena2.zaokraglenie = 8;
    printf("Uczeń otrzymał ocenę %d\n", ocena2.zaokraglenie);

    ocena2.wynik = 7.8;
    printf("Uczeń otrzymał ocenę %f\n", ocena2.wynik);

     return 0;
}