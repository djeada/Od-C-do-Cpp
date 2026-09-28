#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>

class Wektor {
public:
  explicit Wektor(int dlugosc) : dlugosc(0), pojemnosc(0), dane(nullptr) {
    if (dlugosc < 0) {
      throw std::invalid_argument("Długość wektora nie może być ujemna.");
    }

    this->dlugosc = dlugosc;
    pojemnosc = dlugosc;
    dane = new double[pojemnosc]();
  }

  Wektor(const Wektor &inny)
      : dlugosc(inny.dlugosc), pojemnosc(inny.pojemnosc),
        dane(new double[inny.pojemnosc]()) {
    std::copy(inny.dane, inny.dane + dlugosc, dane);
  }

  Wektor(Wektor &&inny) noexcept
      : dlugosc(inny.dlugosc), pojemnosc(inny.pojemnosc), dane(inny.dane) {
    inny.dlugosc = 0;
    inny.pojemnosc = 0;
    inny.dane = nullptr;
  }

  Wektor &operator=(Wektor inny) noexcept {
    swap(inny);
    return *this;
  }

  ~Wektor() { delete[] dane; }

  void swap(Wektor &inny) noexcept {
    std::swap(dlugosc, inny.dlugosc);
    std::swap(pojemnosc, inny.pojemnosc);
    std::swap(dane, inny.dane);
  }

  void zmienDlugosc(int nowaDlugosc) {
    if (nowaDlugosc < 0) {
      throw std::invalid_argument("Długość wektora nie może być ujemna.");
    }

    if (nowaDlugosc <= pojemnosc) {
      dlugosc = nowaDlugosc;
      return;
    }

    double *noweDane = new double[nowaDlugosc]();
    std::copy(dane, dane + dlugosc, noweDane);
    delete[] dane;
    dane = noweDane;
    pojemnosc = nowaDlugosc;
    dlugosc = nowaDlugosc;
  }

  void wypisz() const {
    std::cout << "[";
    for (int i = 0; i < dlugosc; i++) {
      std::cout << dane[i];
      if (i < dlugosc - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "]" << std::endl;
  }

  int pobierzDlugosc() const { return dlugosc; }
  int pobierzPojemnosc() const { return pojemnosc; }

  double &operator[](int indeks) {
    sprawdzIndeks(indeks);
    return dane[indeks];
  }

  const double &operator[](int indeks) const {
    sprawdzIndeks(indeks);
    return dane[indeks];
  }

private:
  void sprawdzIndeks(int indeks) const {
    if (indeks < 0 || indeks >= dlugosc) {
      throw std::out_of_range("Nieprawidłowy indeks.");
    }
  }

  int dlugosc;
  int pojemnosc;
  double *dane;
};

int main() {
  Wektor v(3);
  v[0] = 1.0;
  v[1] = 2.0;
  v[2] = 3.0;
  v.wypisz();

  Wektor kopia = v;
  kopia.zmienDlugosc(5);
  kopia[3] = 4.0;
  kopia[4] = 5.0;
  kopia.wypisz();

  v.wypisz();
  return 0;
}
