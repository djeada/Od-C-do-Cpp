#include <cstdlib>
#include <iostream>
#include <new>
#include <string>

class Osoba {
  std::string imie;
  std::string nazwisko;

public:
  Osoba() : imie("Nieznane"), nazwisko("Nieznane") {
    std::cout << "Osoba została stworzona" << std::endl;
  }

  ~Osoba() { std::cout << "Osoba została zniszczona" << std::endl; }

  void wypisz() const {
    std::cout << "Imię: " << imie << std::endl;
    std::cout << "Nazwisko: " << nazwisko << std::endl;
  }
};

int main() {
  // malloc rezerwuje tylko surową pamięć. Konstruktor trzeba wywołać osobno.
  void *pamiec = std::malloc(sizeof(Osoba));
  if (pamiec == nullptr) {
    return EXIT_FAILURE;
  }

  Osoba *osoba = new (pamiec) Osoba();
  osoba->wypisz();
  osoba->~Osoba();
  std::free(pamiec);

  std::cout << std::endl;

  // new jednocześnie rezerwuje pamięć i konstruuje obiekt.
  osoba = new Osoba();
  osoba->wypisz();
  delete osoba;

  return EXIT_SUCCESS;
}
