#include "pracownik.h"

#include <ostream>
#include <utility>

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

std::string getStanowisko(stanowisko status) {
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
} // namespace

Pracownik::Pracownik()
    : imie(), nazwisko(), status(PROGRAMISTA), zarobki(0) {}

Pracownik::Pracownik(std::string i, std::string n, stanowisko s, int z)
    : imie(std::move(i)), nazwisko(std::move(n)), status(s), zarobki(z) {}

bool operator<(const Pracownik &p1, const Pracownik &p2) {
  return priorytet(p1.status) < priorytet(p2.status);
}

bool operator>(const Pracownik &p1, const Pracownik &p2) {
  return priorytet(p1.status) > priorytet(p2.status);
}

bool operator==(const Pracownik &p1, const Pracownik &p2) {
  return p1.status == p2.status;
}

std::ostream &operator<<(std::ostream &out, const Pracownik &p) {
  out << "Pracownik " << p.imie << ' ' << p.nazwisko
      << " pracuje na stanowisku " << getStanowisko(p.status) << " i zarabia "
      << p.zarobki << '\n';
  return out;
}

void sortowanie(Pracownik *tablica, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (tablica[j] < tablica[i]) {
        std::swap(tablica[i], tablica[j]);
      }
    }
  }
}
