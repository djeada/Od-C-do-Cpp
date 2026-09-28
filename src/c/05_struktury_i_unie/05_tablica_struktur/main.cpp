#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Student {
  std::string imie;
  std::string nazwisko;
  int numer;
};

bool wczytaj_dane(std::vector<Student> &studenci) {
  for (std::size_t i = 0; i < studenci.size(); ++i) {
    std::cout << "Podaj imie studenta " << i << ": ";
    if (!(std::cin >> studenci[i].imie)) {
      return false;
    }

    std::cout << "Podaj nazwisko studenta " << i << ": ";
    if (!(std::cin >> studenci[i].nazwisko)) {
      return false;
    }

    std::cout << "Podaj numer studenta " << i << ": ";
    if (!(std::cin >> studenci[i].numer)) {
      return false;
    }
  }
  return true;
}

bool zapisz_dane(const std::string &nazwa, const std::vector<Student> &studenci) {
  std::ofstream plik(nazwa);
  if (!plik) {
    return false;
  }

  for (const auto &student : studenci) {
    plik << student.imie << ';' << student.nazwisko << ';' << student.numer
         << '\n';
  }

  return static_cast<bool>(plik);
}

int main() {
  std::cout << "Podaj liczbe studentow: ";
  int n;
  if (!(std::cin >> n) || n < 0) {
    std::cerr << "Nieprawidlowa liczba studentow.\n";
    return 1;
  }

  std::vector<Student> studenci(static_cast<std::size_t>(n));
  if (!wczytaj_dane(studenci)) {
    std::cerr << "Nie udalo sie wczytac danych.\n";
    return 1;
  }

  if (!zapisz_dane("lista_studentow.csv", studenci)) {
    std::cerr << "Nie udalo sie zapisac pliku.\n";
    return 1;
  }

  return 0;
}
