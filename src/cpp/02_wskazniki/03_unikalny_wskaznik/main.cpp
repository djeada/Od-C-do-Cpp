#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Tunczyk {
  std::string imie;

public:
  explicit Tunczyk(std::string imie) : imie(std::move(imie)) {
    std::cout << "Konstruktor: " << this->imie << std::endl;
  }

  ~Tunczyk() { std::cout << "Destruktor: " << imie << std::endl; }

  void info() const { std::cout << imie << std::endl; }
};

void foo() {
  auto p = std::make_unique<Tunczyk>("Gunner");
  p->info();

  p = std::make_unique<Tunczyk>("Smokey");
  p->info();

  std::unique_ptr<Tunczyk> przeniesiony = std::move(p);
  std::cout << "Po przeniesieniu p jest " << (p ? "ustawiony" : "pusty")
            << std::endl;
  przeniesiony->info();
}

int main() {
  foo();
  return 0;
}
