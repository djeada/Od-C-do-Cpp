#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <unordered_set>

int main() {
  std::unordered_set<int> zbior = {2, 4, 1, 8, 5, 9};

  auto szybki = zbior.find(4);
  auto ogolny = std::find(zbior.begin(), zbior.end(), 4);
  std::cout << "unordered_set::find: " << (szybki != zbior.end()) << '\n';
  std::cout << "std::find: " << (ogolny != zbior.end()) << '\n';

  std::map<char, std::string> mapa = {
      {'p', "poniedzialek"}, {'w', "wtorek"}, {'c', "czwartek"}};

  auto mapaMember = mapa.find('c');
  auto mapaAlgorithm =
      std::find_if(mapa.begin(), mapa.end(),
                   [](const auto &element) { return element.first == 'c'; });

  std::cout << "map::find: " << (mapaMember != mapa.end()) << '\n';
  std::cout << "std::find_if: " << (mapaAlgorithm != mapa.end()) << '\n';

  std::list<int> lista = {2, 1, 4, 6, 7, 8, 4};
  lista.remove(4);

  std::cout << "Po list::remove:";
  for (int value : lista) {
    std::cout << ' ' << value;
  }
  std::cout << '\n';

  return 0;
}
