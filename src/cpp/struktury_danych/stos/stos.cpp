#include "stos.h"

Stos::Stos() {
  rozmiar = 3;
  tablica = new int[rozmiar];
  indeksGorny = -1;
}

Stos::Stos(int r) {
  rozmiar = r;
  tablica = new int[rozmiar];
  indeksGorny = -1;
}

Stos::Stos(const Stos &innyStos) {
  rozmiar = innyStos.rozmiar;
  tablica = new int[rozmiar];
  for (int i = 0; i <= innyStos.indeksGorny; i++)
    tablica[i] = innyStos.tablica[i];
  indeksGorny = innyStos.indeksGorny;
}

Stos::~Stos() { delete[] tablica; }

bool Stos::czyPusty() {
  if (indeksGorny < 0)
    return true;
  return false;
}

bool Stos::czyPelny() {
  if (indeksGorny >= rozmiar - 1)
    return true;
  return false;
}

bool Stos::odlozNaStos(int dana) {
  if (czyPelny()) {
    cout << "Stack overflow!" << endl;
    return false;
  }
  indeksGorny++;
  tablica[indeksGorny] = dana;
  return true;
}

int Stos::sciagnijZeStosu() {
  if (czyPusty()) {
    cerr << "Stack underflow!" << endl;
    exit(EXIT_FAILURE);
  }
  indeksGorny--;
  return tablica[indeksGorny + 1];
}

void operator++(Stos &nasz_stos) {
  int *tmp = new int[nasz_stos.rozmiar + 1];
  for (int i = 0; i <= nasz_stos.indeksGorny; i++)
    tmp[i] = nasz_stos.tablica[i];
  delete[] nasz_stos.tablica;
  nasz_stos.tablica = tmp;
  nasz_stos.rozmiar++;
}

void operator--(Stos &nasz_stos) {
  int *tmp = new int[nasz_stos.rozmiar - 1];
  nasz_stos.rozmiar--;

  if (nasz_stos.rozmiar == nasz_stos.indeksGorny)
    nasz_stos.indeksGorny--;

  for (int i = 0; i <= nasz_stos.indeksGorny; i++)
    tmp[i] = nasz_stos.tablica[i];

  delete[] nasz_stos.tablica;

  nasz_stos.tablica = tmp;
}

ostream &operator<<(ostream &out, const Stos &nasz_stos) {
  cout << "Twoj piekny stos: " << endl;
  for (int i = 0; i <= nasz_stos.indeksGorny; i++)
    cout << nasz_stos.tablica[i] << "  ";
  return out;
}
