#include <iostream>

/*
Kiedy klasa pochodna nadpisuje metodę klasy bazowej poprzez zdefiniowanie tej samej funkcji,
to jeśli klient chce uzyskać dostęp do przedefiniowanej metody z klasy pochodnej
przez wskaźnik z obiektu klasy bazowej, to należy zdefiniować tę funkcję w klasie bazowej jako funkcję wirtualną.
*/

class Rodzic {
public:
  void wypisz() { std::cout << "jestem rodzicem" << std::endl; }
  virtual void wypiszWirtualnie() { std::cout << "jestem rodzicem" << std::endl; }
};

class Dziecko : public Rodzic {
public:
  void wypisz() { std::cout << "jestem dzieckiem" << std::endl; }
  void wypiszWirtualnie() { std::cout << "jestem dzieckiem" << std::endl; }
};

int main(int argc, char *argv[]) {
  Rodzic *wskaznik = new Dziecko;
  wskaznik->wypisz();
  wskaznik->wypiszWirtualnie();
  return 0;
}
