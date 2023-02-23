#include <algorithm>
#include <iostream>
#include <vector>

void obroc(std::vector<int> &wektor, int klucz) {
  // Wyszukiwanie pierwszego wystąpienia klucza
  auto it = std::find(wektor.begin(), wektor.end(), klucz);
  if (it != wektor.end()) {
    // Obrót elementów przed kluczem na koniec wektora
    std::rotate(wektor.begin(), it, wektor.end());
  }
}

int main() {
  // Tworzenie wektora losowych liczb całkowitych
  std::vector<int> wektor{3, 2, 1, 7, 9, 7, 8, 10};

  obroc(wektor, 9);

  // Wyświetlenie wyniku
  for (int x : wektor) {
    std::cout << x << " ";
  }
  std::cout << std::endl;

  return 0;
}
