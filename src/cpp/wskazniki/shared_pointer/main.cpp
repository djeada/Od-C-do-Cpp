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
  Tunczyk *p = new Tunczyk("Gunner");
  p->info();
  // delete p; // alles super
  // mamy wyciek pamieci
}

void foo2() {
  std::shared_ptr<Tunczyk> p(new Tunczyk("Gunner")); // count : 1
  p->info();

  std::cout << "Liczba instancji: " << p.use_count() << std::endl;

  Tunczyk *t = p.get(); // zwroc surowy wskaznik
  t->info();
  // delete t; // bedzie seg fault
  std::cout << "Liczba instancji: " << p.use_count() << std::endl;

  std::shared_ptr<Tunczyk> p2 = p;

  std::cout << "Liczba instancji: " << p.use_count() << std::endl;

  // wyzeruj wskaznik p
  p = nullptr;

  std::cout << "Liczba instancji: " << p2.use_count() << std::endl;

  // wymus usuniecie
  // p2.reset();
  //   std::cout << p2.use_count() << std::endl;
}

int main() {
  foo();
  foo2();
  return 0;
}
