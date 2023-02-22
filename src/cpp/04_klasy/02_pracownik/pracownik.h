#ifndef pracownik_h
#define pracownik_h

#include <iostream>

using namespace std;

/*
Klasa pracownik zbiera informacje o pracowniku firmy
Chcemy miec mozliwosc wprowadzania nowych pracownikow
i wyszukiwania informacji z wprowadzonych

Pracownik p1;
Pracownik p2("Jan", "Kowalski", PREZES, 4000);

p1 > p2 ?

*/

enum stanowisko { PREZES, PROGRAMISTA, TRENER };

class Pracownik {
private:
  string imie;
  string nazwisko;
  stanowisko status;
  int zarobki;

public:
  Pracownik();
  Pracownik(string i, string n, stanowisko s, int z);

  friend bool operator<(const Pracownik &p1, const Pracownik &p2);
  friend bool operator>(const Pracownik &p1, const Pracownik &p2);
  friend bool operator==(const Pracownik &p1, const Pracownik &p2);

  friend ostream &operator<<(ostream &out, const Pracownik &p);
};

void sortowanie(Pracownik *tablica, int n);

#endif
