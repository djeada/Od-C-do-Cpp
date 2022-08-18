#include <stdio.h>

struct Foo {
    int liczba;
    char znak;
};

union Bar {
    int liczba;
    char znak;
};


int main() {
    struct Foo foo;
    union Bar bar;
    foo.liczba = 1;
    foo.znak = 'a';
    bar.liczba = 1;
    bar.znak = 'a';
 
    printf("Obiekt foo zawiera liczbe %d oraz znak %c\n", foo.liczba, foo.znak);
    printf("Obiekt bar zawiera liczbe %d oraz znak %c\n", bar.liczba, bar.znak);
    printf("\n");
  
    // porownaj rozmiar struktury i unii
    printf("Rozmiar struktury foo: %lu\n", sizeof(foo));
    printf("Rozmiar unii bar: %lu\n", sizeof(bar));
    printf("\n");

    // pokaz adres pol w strukturze oraz w unii
    printf("Adres pola liczba oraz pola znak w strukturze foo:\n%p\n%p\n\n", &foo.liczba, &foo.znak);
    printf("Adres pola liczba oraz pola znak w unii bar:\n%p\n%p\n", &bar.liczba, &bar.znak);

    return 0;
}
