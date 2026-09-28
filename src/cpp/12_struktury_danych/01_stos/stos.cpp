#include "stos.h"

#include <algorithm>
#include <ostream>
#include <stdexcept>

Stos::Stos() : Stos(3) {}

Stos::Stos(int r) : tablica(nullptr), rozmiar(r), indeksGorny(-1) {
  if (r <= 0) {
    throw std::invalid_argument("Rozmiar stosu musi byc dodatni.");
  }
  tablica = new int[rozmiar];
}

Stos::Stos(const Stos &innyStos)
    : tablica(new int[innyStos.rozmiar]), rozmiar(innyStos.rozmiar),
      indeksGorny(innyStos.indeksGorny) {
  std::copy(innyStos.tablica, innyStos.tablica + indeksGorny + 1, tablica);
}

Stos &Stos::operator=(const Stos &innyStos) {
  if (this == &innyStos) {
    return *this;
  }

  int *nowaTablica = new int[innyStos.rozmiar];
  std::copy(innyStos.tablica, innyStos.tablica + innyStos.indeksGorny + 1,
            nowaTablica);

  delete[] tablica;
  tablica = nowaTablica;
  rozmiar = innyStos.rozmiar;
  indeksGorny = innyStos.indeksGorny;
  return *this;
}

Stos::~Stos() { delete[] tablica; }

bool Stos::czyPusty() const { return indeksGorny < 0; }

bool Stos::czyPelny() const { return indeksGorny >= rozmiar - 1; }

bool Stos::odlozNaStos(int dana) {
  if (czyPelny()) {
    return false;
  }
  tablica[++indeksGorny] = dana;
  return true;
}

int Stos::sciagnijZeStosu() {
  if (czyPusty()) {
    throw std::underflow_error("Stos jest pusty.");
  }
  return tablica[indeksGorny--];
}

void operator++(Stos &nasz_stos) {
  int *tmp = new int[nasz_stos.rozmiar + 1];
  std::copy(nasz_stos.tablica, nasz_stos.tablica + nasz_stos.indeksGorny + 1,
            tmp);
  delete[] nasz_stos.tablica;
  nasz_stos.tablica = tmp;
  ++nasz_stos.rozmiar;
}

void operator--(Stos &nasz_stos) {
  if (nasz_stos.rozmiar <= 1) {
    return;
  }

  const int nowyRozmiar = nasz_stos.rozmiar - 1;
  if (nasz_stos.indeksGorny >= nowyRozmiar) {
    nasz_stos.indeksGorny = nowyRozmiar - 1;
  }

  int *tmp = new int[nowyRozmiar];
  std::copy(nasz_stos.tablica, nasz_stos.tablica + nasz_stos.indeksGorny + 1,
            tmp);
  delete[] nasz_stos.tablica;

  nasz_stos.tablica = tmp;
  nasz_stos.rozmiar = nowyRozmiar;
}

std::ostream &operator<<(std::ostream &out, const Stos &nasz_stos) {
  out << "Twoj piekny stos: ";
  for (int i = 0; i <= nasz_stos.indeksGorny; ++i) {
    out << nasz_stos.tablica[i] << "  ";
  }
  return out;
}
