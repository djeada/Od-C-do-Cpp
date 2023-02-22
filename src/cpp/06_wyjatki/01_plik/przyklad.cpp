#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

void wczytajDane(std::string nazwa_pliku, std::vector<std::string> &wiersze) {
  std::ifstream moj_plik(nazwa_pliku);
  if (!moj_plik.is_open()) {
    throw std::runtime_error("Nie udalo sie otworzyc pliku " + nazwa_pliku);
  }
  std::string wiersz;
  while (getline(moj_plik, wiersz)) {
    wiersze.push_back(wiersz);
  }
  moj_plik.close();
}

int main() {
  std::vector<std::string> wiersze;
  try {
    wczytajDane("plik.txt", wiersze);
  } catch (std::runtime_error &e) {
    std::cerr << "Wystapil blad: " << e.what() << std::endl;
  }
  std::cout << "Tresc pliku: " << std::endl;
  for (auto wiersz : wiersze) {
    std::cout << wiersz << std::endl;
  }
  return 0;
}
