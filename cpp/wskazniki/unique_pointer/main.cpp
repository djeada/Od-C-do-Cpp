/*
- dla unikalnego wskaznika jeden obiekt moze byc wlasnoscia tylko jednego
unikalnego wskaznika i kiedy ze jeden unikalny wskaznik wychodzi poza zakres lub
zaczyna posiadac inny obiekt wtedy oryginalny obiekt zostanie automatycznie
usuniety
- kolejna roznica miedzy wskaznikiem unikalnym a wskaznikiem wspolnym jest
unikalny pointer to lekki inteligentny wskaznik, wiec jest tanszy w uzyciu niz
wspolny wskaznik, jesli masz wiele wskaznikow zapisanych w swoim programie i nie
sa one udostepniane preferowane jest uzywanie unikalnego wskaznika zamiast
wspolnych wskaznikow
*/

#include <iostream>
#include <memory>
#include <string>

class Tunczyk {
  std::string imie;

public:
  Tunczyk(std::string imie) : imie(imie) {
    std::cout << "Konstruktor: " << imie << std::endl;
  }
  ~Tunczyk() { std::cout << "Destruktor: " << imie << std::endl; }

  void info() { std::cout << imie << std::endl; }
};

void foo() {
  std::unique_ptr<Tunczyk> p(new Tunczyk("Gunner"));
  p->info();
  p.reset(new Tunczyk("Smokey"));

  if (!p) {
    std::cout << "Prawda." << std::endl;
  } else {
    std::cout << "Falsz." << std::endl;
  }
}

int main() {
  foo();
  return 0;
}
