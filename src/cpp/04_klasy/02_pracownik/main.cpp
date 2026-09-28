#include "pracownik.h"

#include <array>
#include <iostream>

int main() {
  Pracownik p1;
  Pracownik p2("Jan", "Kowalski", PREZES, 4000);

  std::cout << p1;
  std::cout << p2;

  std::array<Pracownik, 4> tab = {
      p1, p2, Pracownik("Krzysztof", "Jerzyna", TRENER, 3000),
      Pracownik("Programista", "Programista", PROGRAMISTA, 3000)};

  std::cout << "\nTablica przed sortowaniem:\n";
  for (const auto &pracownik : tab) {
    std::cout << pracownik;
  }

  sortowanie(tab.data(), static_cast<int>(tab.size()));

  std::cout << "\nTablica po sortowaniu:\n";
  for (const auto &pracownik : tab) {
    std::cout << pracownik;
  }

  return 0;
}
