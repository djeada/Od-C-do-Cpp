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

void surowyWskaznik() {
  Tunczyk *p = new Tunczyk("Gunner");
  p->info();
  delete p; // przy surowym wskazniku odpowiedzialnosc jest po stronie autora
}

void sharedPointer() {
  auto p = std::make_shared<Tunczyk>("Smokey");
  p->info();

  std::cout << "Liczba wlascicieli: " << p.use_count() << std::endl;

  Tunczyk *obserwator = p.get();
  obserwator->info(); // nie wolno wywolywac delete na obserwatorze

  std::shared_ptr<Tunczyk> p2 = p;
  std::cout << "Po kopii: " << p.use_count() << std::endl;

  p.reset();
  std::cout << "Po reset p, p2 ma licznik: " << p2.use_count() << std::endl;
}

int main() {
  surowyWskaznik();
  sharedPointer();
  return 0;
}
