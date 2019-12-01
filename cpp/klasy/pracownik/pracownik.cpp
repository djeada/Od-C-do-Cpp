#include "pracownik.h"

Pracownik::Pracownik() {
  imie = "";
  nazwisko = "";
  status = PROGRAMISTA;
  zarobki = 0;
}

Pracownik::Pracownik(string i, string n, stanowisko s, int z) {
  imie = i;
  nazwisko = n;
  status = s;
  zarobki = z;
}

// Prezes < Trener < Programista

bool operator<(const Pracownik &p1, const Pracownik &p2) {
  if (p2.status == PREZES && p1.status != PREZES) {
    return true;
  }
  if (p2.status == TRENER && p1.status == PROGRAMISTA) {
    return true;
  }
  return false;
}

bool operator>(const Pracownik &p1, const Pracownik &p2) {
  if (p1.status == PREZES && p2.status != PREZES) {
    return true;
  }
  if (p1.status == TRENER && p2.status == PROGRAMISTA) {
    return true;
  }
  return false;
}

bool operator==(const Pracownik &p1, const Pracownik &p2) {
  return (p1.status == p2.status);
}

string getStanowisko(stanowisko status) {
  switch (status) {
  case PREZES:
    return "Prezes";
  case PROGRAMISTA:
    return "Programista";
  case TRENER:
    return "Trener";
  }
  return "";
}

ostream &operator<<(ostream &out, const Pracownik &p) {
  cout << "Pracownik " << p.imie << " " << p.nazwisko
       << " pracuje na stanowisku " << getStanowisko(p.status) << " i zarabia "
       << p.zarobki << endl;
  return out;
}

void swap(Pracownik &p1, Pracownik &p2) {
  Pracownik temp = p1;
  p1 = p2;
  p2 = temp;
}

/* 4 2 6
   4 2 6
   4 6 2
   6 4 2
*/

// ustawiamy pracowników według stanowiska
void sortowanie(Pracownik *tablica, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (tablica[i] < tablica[j]) {
        swap(tablica[i], tablica[j]);
      }
    }
  }
}
