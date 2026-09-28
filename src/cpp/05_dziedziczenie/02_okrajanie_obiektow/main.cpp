#include <deque>
#include <iostream>
#include <memory>
#include <string>

class KlasaBazowa {
public:
  virtual ~KlasaBazowa() = default;

  virtual void wiadomosc() const {
    std::cout << "Brak informacji" << std::endl;
  }
};

class KlasaPochodna : public KlasaBazowa {
private:
  std::string imie;

public:
  explicit KlasaPochodna(std::string imie) : imie(std::move(imie)) {}

  void wiadomosc() const override {
    std::cout << "Mam na imie: " << imie << std::endl;
  }
};

int main() {
  KlasaPochodna obiekt("James");

  // Kopia do kontenera klasy bazowej powoduje object slicing.
  std::deque<KlasaBazowa> kolejka;
  kolejka.push_front(obiekt);
  kolejka.front().wiadomosc();

  // Polimorfizm zachowujemy przez wskaznik/referencje.
  std::deque<std::reference_wrapper<const KlasaBazowa>> referencje;
  referencje.push_front(obiekt);
  referencje.front().get().wiadomosc();

  return 0;
}
