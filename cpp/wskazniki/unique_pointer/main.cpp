/*
- dla unikalnego wskaźnika jeden obiekt może być własnością tylko jednego
unikalnego wskaźnika i kiedy że jeden unikalny wskaźnik wychodzi poza zakres lub
zaczyna posiadać inny obiekt wtedy oryginalny obiekt zostanie automatycznie
usunięty
- kolejną różnicą między wskaźnikiem unikalnym a wskaźnikiem wspólnym jest
unikalny pointer to lekki inteligentny wskaźnik, więc jest tańszy w użyciu niż
wspólny wskaźnik, jeśli masz wiele wskaźników zapisanych w swoim programie i nie
są one udostępniane preferowane jest używanie unikalnego wskaźnika zamiast
wspólnych wskaźników
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
