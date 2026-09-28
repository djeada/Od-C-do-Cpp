#ifndef PRACOWNIK_H
#define PRACOWNIK_H

#include <iosfwd>
#include <string>

enum stanowisko { PREZES, PROGRAMISTA, TRENER };

class Pracownik {
private:
  std::string imie;
  std::string nazwisko;
  stanowisko status;
  int zarobki;

public:
  Pracownik();
  Pracownik(std::string i, std::string n, stanowisko s, int z);

  friend bool operator<(const Pracownik &p1, const Pracownik &p2);
  friend bool operator>(const Pracownik &p1, const Pracownik &p2);
  friend bool operator==(const Pracownik &p1, const Pracownik &p2);
  friend std::ostream &operator<<(std::ostream &out, const Pracownik &p);
};

void sortowanie(Pracownik *tablica, int n);

#endif
