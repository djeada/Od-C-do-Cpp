#include <iostream>
#include <cstdlib>

class Czlowiek {
    std::string imie;
    std::string nazwisko;

    public:
        Czlowiek() {
            imie = "Blank";
            nazwisko = "Blank";
        }

        ~Czlowiek() {
            std::cout << "Czlowiek zostal zniszczony" << std::endl;
        }
        void wypisz() {
            std::cout << "Imie: " << imie << std::endl;
            std::cout << "Nazwisko: " << nazwisko << std::endl;
        }
};

int main() {

Czlowiek* czlowiek = (Czlowiek*)malloc(sizeof(Czlowiek));
czlowiek->wypisz();
free(czlowiek);

czlowiek = new Czlowiek();
czlowiek->wypisz();
delete czlowiek;

return 0;


}
