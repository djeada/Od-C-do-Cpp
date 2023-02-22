#include "pracownik.h"
#include <iostream>

using namespace std;

int main() {
  Pracownik p1;
  Pracownik p2("Jan", "Kowalski", PREZES, 4000);

  cout << p1;
  cout << p2;

  // wielkosc tablicy
  int n = 4;

  Pracownik tab[n];
  tab[0] = p1;
  tab[1] = p2;
  tab[2] = Pracownik("Krzysztof", "Jerzyna", TRENER, 3000);
  tab[3] = Pracownik("Programista", "Programista", PROGRAMISTA, 3000);

  cout << endl << "Tablica przed sortowaniem: " << endl;

  for (int i = 0; i < n; i++)
    cout << tab[i];

  sortowanie(tab, n);

  cout << endl << "Tablica po sortowaniu: " << endl;

  for (int i = 0; i < n; i++)
    cout << tab[i];

  return 0;
}
