#include <algorithm>
#include <iostream>
#include <vector>

void sortujPodciag(std::vector<int> &wektor, int klucz) {
  // znajdź pierwsze wystąpienie klucza
  auto it = std::find(wektor.begin(), wektor.end(), klucz);
  // posortuj elementy wektora występujące przed znalezioną liczbą
  std::sort(wektor.begin(), it);
}

int main() {
  // stwórz wektor losowych liczb całkowitych z przedziału [0, 10]
  std::vector<int> wektor{1, 7, 3, 5, 7, 2, 9, 8, 0, 7};

  sortujPodciag(wektor, 2);

  // wyświetl posortowany wektor
  for (const auto &i : wektor) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  return 0;
}
