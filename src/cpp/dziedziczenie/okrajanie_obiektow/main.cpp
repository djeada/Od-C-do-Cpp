#include <deque>
#include <iostream>

class KlasaBazowa {
public:
  // zmien na virtual by zadzialalo
  void wiadomosc() { std::cout << "Brak informacji" << std::endl; }
};

class KlasaPochodna : public KlasaBazowa {
private:
  std::string imie;

public:
  KlasaPochodna(std::string imie) : imie(imie) {}
  void wiadomosc() { std::cout << "Mam na imie: " << imie << std::endl; }
};

int main() {

  // tworzymy kolejke obiektow typu KlasaBazowa
  std::deque<KlasaBazowa> kolejka;

  // tworzymy obiekt typu KlasaPochodna
  KlasaPochodna obiekt("James");

  // dodajemy obiekt do kolejki
  kolejka.push_front(obiekt);

  // wyciagnij pierwszy element kolejki i wywolaj na nim metode wiadomosc
  // zamiast implementacji z klasy pochodnej otrzymamy implementacje klasy
  // bazowej co sie stalo? zamiast skopiowac przekazany obiekt, wywolany
  // zostanie konstruktor kopiujacy klasy bazowej z obiektem przekazanym jako
  // parametr.
  kolejka.front().wiadomosc();

  // rozwiazanie: przekazujemy adres zamiast kopiowac
  std::deque<KlasaBazowa *> kolejka_wsk;
  kolejka_wsk.push_front(&obiekt);
  kolejka_wsk.front()->wiadomosc();

  return 0;
}