#include <iostream>
#include <stdexcept>

class Wektor {
public:
  // Konstruktor przyjmujący długość wektora i tworzący wektor wypełniony
  // zerami.
  Wektor(int dlugosc)
      : dlugosc(dlugosc), pojemnosc(dlugosc), dane(new double[dlugosc]()) {}

  // Destruktor, zwalniający pamięć.
  ~Wektor() { delete[] dane; }

  // Metoda zmieniająca długość wektora.
  void zmienDlugosc(int nowaDlugosc) {
    if (nowaDlugosc < 0) {
      throw std::invalid_argument("Długość wektora nie może być ujemna.");
    }

    if (nowaDlugosc <= pojemnosc) {
      dlugosc = nowaDlugosc;
    } else {
      double *noweDane = new double[nowaDlugosc]();
      for (int i = 0; i < dlugosc; i++) {
        noweDane[i] = dane[i];
      }
      delete[] dane;
      dane = noweDane;
      pojemnosc = nowaDlugosc;
      dlugosc = nowaDlugosc;
    }
  }

  // Metoda wypisująca zawartość wektora.
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

  // Metoda zwracająca długość wektora.
  int pobierzDlugosc() const { return dlugosc; }

  // Metoda zwracająca pojemność wektora.
  int pobierzPojemnosc() const { return pojemnosc; }

  // Dostęp do elementów wektora za pomocą operatora [].
  double &operator[](int indeks) {
    if (indeks < 0 || indeks >= dlugosc) {
      throw std::out_of_range("Nieprawidłowy indeks.");
    }
    return dane[indeks];
  }

private:
  int dlugosc;
  int pojemnosc;
  double *dane; // Wskaźnik na dynamicznie zaalokowaną tablicę przechowującą
                // elementy wektora.
};

int main() {
  Wektor v(3);
  v[0] = 1.0;
  v[1] = 2.0;
  v[2] = 3.0;
  v.wypisz(); // [1, 2, 3]
  v.zmienDlugosc(5);
  v.wypisz(); // [1, 2, 3, 0, 0]
  v[3] = 4.0;
  v[4] = 5.0;
  v.wypisz(); // [1, 2, 3, 4]
  return 0;
}
