#include <iostream>
#include <string>
class Osoba {

  std::string imie;

public:
  Osoba(std::string imie) : imie(imie) {
    std::cout << "Konstruktor " << imie << std::endl;
  }
  ~Osoba() { std::cout << "Destruktor " << imie << std::endl; }
};

void funkcjaC() {
  Osoba c("C");
  std::cout << "Funkcja C rzuca wyjatek" << std::endl;
  throw "Wyjatek z funkcji C";
}
void funkcjaB() {
  Osoba b("B");
  std::cout << "Funkcja B przed wywolaniem funkcji C" << std::endl;
  funkcjaC();
  std::cout << "Funkcja B po wywolaniu funkcji C" << std::endl;
}
void funkcjaA() {
  Osoba a("A");
  std::cout << "Funkcja A przed wywolaniem funkcji B" << std::endl;
  try {
    funkcjaB();
  } catch (...) {
    std::cout << "Funkcja A obsluguje wyjatek" << std::endl;
  }
  std::cout << "Funkcja A po wywolaniu funkcji B" << std::endl;
}

int main() {
  std::cout << "Program rozpoczyna dzialanie" << std::endl;
  funkcjaA();
  std::cout << "Program zakonczyl dzialanie" << std::endl;
  return 0;
}
