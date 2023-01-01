#include <algorithm>
#include <iostream>
#include <vector>

/*
Obiekty moga zachowywac sie jak funkcje.
*/

class PrzykladowaKlasa {
public:
  const void operator()(const std::string napis) {
    std::cout << "Otrzymalem napis: " << napis << std::endl;
  }
};

// Funktory moga miec normalne konstruktory

class Powieksz {
  int wartosc;

public:
  Powieksz(int wartosc) : wartosc(wartosc) {}
  void operator()(int element) { std::cout << element + wartosc << std::endl; }
};

int main() {
  PrzykladowaKlasa obiekt;
  obiekt("Witaj swiecie!");

  std::vector<int> vec = {2, 3, 4, 5};
  std::for_each(vec.begin(), vec.end(), Powieksz(5));

  return 0;
}
