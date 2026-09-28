#include "pracownik.h"

namespace {
int priorytet(stanowisko status) {
  switch (status) {
  case PREZES:
    return 0;
  case TRENER:
    return 1;
  case PROGRAMISTA:
    return 2;
  }
  return 3;
}
} // namespace

Pracownik::Pracownik()
    : imie(""), nazwisko(""), status(PROGRAMISTA), zarobki(0) {}

Pracownik::Pracownik(string i, string n, stanowisko s, int z)
    : imie(i), nazwisko(n), status(s), zarobki(z) {}

// Prezes < Trener < Programista
bool operator<(const Pracownik &p1, const Pracownik &p2) {
  return priorytet(p1.status) < priorytet(p2.status);
}

bool operator>(const Pracownik &p1, const Pracownik &p2) {
  return priorytet(p1.status) > priorytet(p2.status);
}

bool operator==(const Pracownik &p1, const Pracownik &p2) {
  return p1.status == p2.status;
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
  return "Nieznane";
}

ostream &operator<<(ostream &out, const Pracownik &p) {
  out << "Pracownik " << p.imie << " " << p.nazwisko
      << " pracuje na stanowisku " << getStanowisko(p.status) << " i zarabia "
      << p.zarobki << endl;
  return out;
}

void swap(Pracownik &p1, Pracownik &p2) {
  Pracownik temp = p1;
  p1 = p2;
  p2 = temp;
}

void sortowanie(Pracownik *tablica, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (tablica[j] < tablica[i]) {
        swap(tablica[i], tablica[j]);
      }
    }
  }
}
