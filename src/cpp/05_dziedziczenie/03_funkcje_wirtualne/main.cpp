#include <iostream>
#include <memory>

class Rodzic {
public:
  virtual ~Rodzic() = default;

  void wypisz() const { std::cout << "jestem rodzicem" << std::endl; }

  virtual void wypiszWirtualnie() const {
    std::cout << "jestem rodzicem" << std::endl;
  }
};

class Dziecko : public Rodzic {
public:
  void wypisz() const { std::cout << "jestem dzieckiem" << std::endl; }

  void wypiszWirtualnie() const override {
    std::cout << "jestem dzieckiem" << std::endl;
  }
};

int main() {
  std::unique_ptr<Rodzic> wskaznik = std::make_unique<Dziecko>();
  wskaznik->wypisz();
  wskaznik->wypiszWirtualnie();
  return 0;
}
