#include <iostream>
#include <cstdlib>

class Osoba {
    std::string imie;
    std::string nazwisko;

public:
    Osoba() {
        imie = "Nieznane";
        nazwisko = "Nieznane";
              std::cout << "Osoba została stworzona" << std::endl;
    }

    ~Osoba() {
        std::cout << "Osoba została zniszczona" << std::endl;
    }

    void wypisz() {
        std::cout << "Imię: " << imie << std::endl;
        std::cout << "Nazwisko: " << nazwisko << std::endl;
    }
};

int main() {
    // alokacja pamięci dla osoby przy użyciu funkcji malloc
    Osoba* osoba = (Osoba*)malloc(sizeof(Osoba));
    //new (osoba) Osoba(); // placement new
  
    // wywołanie metody wypisz dla osoby
    osoba->wypisz();

    //osoba->~Osoba();
    // zwolnienie pamięci zaalokowanej przy użyciu malloc
    free(osoba);

    std::cout << std::endl;

    // alokacja pamięci dla osoby przy użyciu operatora new
    osoba = new Osoba();

    // wywołanie metody wypisz dla osoby
    osoba->wypisz();

    // zwolnienie pamięci zaalokowanej przy użyciu operatora new
    delete osoba;

    return 0;
}
