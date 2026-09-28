#include <forward_list>
#include <iostream>
#include <list>
#include <vector>

int main() {
  std::vector<int> wektor{1, 2, 3, 4, 5};

  auto itr = wektor.begin() + 2;
  auto poczatek = wektor.begin();
  auto koniec = wektor.end();

  std::cout << "Element wskazywany przez iterator: " << *itr << '\n';
  std::cout << "Odległość od początku: " << (itr - poczatek) << '\n';
  std::cout << "Czy iterator jest przed końcem: " << (itr < koniec) << '\n';

  *itr = 100;

  std::cout << "Wektor po modyfikacji:";
  for (int value : wektor) {
    std::cout << ' ' << value;
  }
  std::cout << '\n';

  // list ma iterator dwukierunkowy.
  std::list<int> lista{1, 2, 3};
  auto listaItr = lista.end();
  --listaItr;
  std::cout << "Ostatni element listy: " << *listaItr << '\n';

  // forward_list pozwala tylko na ruch do przodu.
  std::forward_list<int> listaJednokierunkowa{7, 8, 9};
  auto forwardItr = listaJednokierunkowa.begin();
  ++forwardItr;
  std::cout << "Drugi element forward_list: " << *forwardItr << '\n';

  return 0;
}
