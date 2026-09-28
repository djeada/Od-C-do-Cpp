#include <iostream>
#include <string>

class Zwierze {
public:
  explicit Zwierze(std::string nazwa) : nazwa_(std::move(nazwa)) {}

  void przedstawSie() const {
    std::cout << "Jestem " << nazwa_ << std::endl;
  }

protected:
  const std::string &nazwa() const { return nazwa_; }

private:
  std::string nazwa_;
};

class Pies : public Zwierze {
public:
  Pies(std::string nazwa, std::string rasa)
      : Zwierze(std::move(nazwa)), rasa_(std::move(rasa)) {}

  void opis() const {
    przedstawSie();
    std::cout << "Rasa: " << rasa_ << ", nazwa z klasy bazowej: " << nazwa()
              << std::endl;
  }

private:
  std::string rasa_;
};

int main() {
  Pies pies("Burek", "mieszaniec");
  pies.opis();
  return 0;
}
