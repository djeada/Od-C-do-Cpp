#include <iostream>

// zadna klasa nie moze byc dziedziczona po klasie KlasaPrzykladowa
class KlasaPrzykladowa final {
public:
  void info() { std::cout << "Klasa Przykladowa" << std::endl; }
};

class KlasaBazowa {
public:
  virtual void info() final { std::cout << "Klasa Bazowa" << std::endl; }
};

class KlasaPochodna : public KlasaBazowa {

  /* virtual void info() override {
     std::cout << "Klasa Pochodna" << std::endl;
  } */
};

int main() {
  KlasaPrzykladowa obiekt;
  obiekt.info();

  KlasaBazowa obiekt2;
  obiekt2.info();

  KlasaPochodna obiekt3;
  obiekt3.info();

  return 0;
}
