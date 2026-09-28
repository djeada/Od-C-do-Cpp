#include <algorithm>
#include <iostream>
#include <vector>

template <class T> void wypisz(const T &kontener) {
  std::cout << "{";
  bool pierwszy = true;
  for (const auto &element : kontener) {
    if (!pierwszy) {
      std::cout << ", ";
    }
    std::cout << element;
    pierwszy = false;
  }
  std::cout << "}" << std::endl;
}

// O(n^2) w najgorszym przypadku: każde erase przesuwa resztę wektora.
template <typename T>
std::vector<T> usunElement1(std::vector<T> wektor, const T &element) {
  for (auto itr = wektor.begin(); itr != wektor.end();) {
    if (*itr == element) {
      itr = wektor.erase(itr);
    } else {
      ++itr;
    }
  }
  return wektor;
}

// O(n): usuwa tylko pierwsze wystąpienie.
template <typename T>
std::vector<T> usunElement2(std::vector<T> wektor, const T &element) {
  auto itr = std::find(wektor.begin(), wektor.end(), element);
  if (itr != wektor.end()) {
    wektor.erase(itr);
  }
  return wektor;
}

// O(n): idiom erase-remove usuwa wszystkie wystąpienia.
template <typename T>
std::vector<T> usunElement3(std::vector<T> wektor, const T &element) {
  auto nowyKoniec = std::remove(wektor.begin(), wektor.end(), element);
  wektor.erase(nowyKoniec, wektor.end());
  return wektor;
}

int main() {
  const std::vector<int> c = {1, 4, 6, 1, 1, 1, 1, 12, 18, 16};
  wypisz(c);
  wypisz(usunElement1(c, 1));
  wypisz(usunElement2(c, 1));
  wypisz(usunElement3(c, 1));
  return 0;
}
