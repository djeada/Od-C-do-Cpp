#include <fstream>
#include <iostream>

using namespace std;

struct student {
  string imie;
  string nazwisko;
  int numer;
};

void wczytaj_dane(int n, student *nowi_studenci) {
  for (int i = 0; i < n; i++) {
    cout << "Podaj imie " << i << "tego studenta: " << endl;
    cin >> nowi_studenci[i].imie;
    cout << "Podaj nazwisko" << i << "tego studenta " << endl;
    cin >> nowi_studenci[i].nazwisko;
    cout << "Podaj numer" << i << "tego studenta" << endl;
    cin >> nowi_studenci[i].numer;
  }
}

void zapisz_dane(string nazwa, int n, student *nowi_studenci) {
  ofstream plik_studenci;
  plik_studenci.open(nazwa);
  for (int i = 0; i < n; i++) {
    plik_studenci << nowi_studenci[i].imie << ";" << nowi_studenci[i].nazwisko
                  << ";" << nowi_studenci[i].numer << endl;
  }

  plik_studenci.close();
}

int main() {

  // pobieramy liczbe studentow
  cout << "Podaj liczbe studentow: " << endl;
  int n;
  cin >> n;

  // alokujemy pamiec
  student *nowi_studenci = new student[n];

  // wypelniamy tablice struktur i pola w tych strukturach
  wczytaj_dane(n, nowi_studenci);

  // zapisujemy dane w pliku
  zapisz_dane("lista_studentow.csv", n, nowi_studenci);

  delete[] nowi_studenci;

  return 0;
}
