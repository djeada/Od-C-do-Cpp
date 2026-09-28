#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class PrzykladowaKlasa {
public:
  void operator()(const std::string &napis) const {
    std::cout << "Otrzymalem napis: " << napis << std::endl;
  }
};

class Powieksz {
  int wartosc;

public:
  explicit Powieksz(int wartosc) : wartosc(wartosc) {}

  void operator()(int element) const {
    std::cout << element + wartosc << std::endl;
  }
};

int main() {
  PrzykladowaKlasa obiekt;
  obiekt("Witaj swiecie!");

  std::vector<int> vec = {2, 3, 4, 5};
  std::for_each(vec.begin(), vec.end(), Powieksz(5));

  return 0;
}
