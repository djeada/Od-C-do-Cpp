#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  std::vector<int> vec = {4, 5, 6, 7};

  std::cout << "Od końca:";
  for (auto ritr = vec.rbegin(); ritr != vec.rend(); ++ritr) {
    std::cout << ' ' << *ritr;
  }
  std::cout << '\n';

  auto ritr = std::find(vec.rbegin(), vec.rend(), 6);
  if (ritr != vec.rend()) {
    // base() wskazuje na element następujący po elemencie reverse_iteratora.
    vec.insert(ritr.base(), 9);
  }

  ritr = std::find(vec.rbegin(), vec.rend(), 6);
  if (ritr != vec.rend()) {
    // Aby usunąć dokładnie *ritr, cofamy base() o jeden element.
    vec.erase(std::prev(ritr.base()));
  }

  std::cout << "Po operacjach:";
  for (int value : vec) {
    std::cout << ' ' << value;
  }
  std::cout << '\n';

  return 0;
}
