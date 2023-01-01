#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  /*
  wektor = {1, 2, 3, 4, 5}

 'wektor.rend()'  |  1'wektor.begin()'  |  2  |  3  |  4  |  5 'wektor.rbegin()'
 |   'wektor.end()'

 wektor.begin() : pierwszy element
 wektor.end()   : adres za ostatnim elementem
 wektor.rbegin(): ostatni element
 wektor.rend()  : adres przed pierwszym elementem
 */

  std::vector<int> vec = {4, 5, 6, 7};

  // wypisz: 7 6 5 4
  for (auto ritr = vec.rbegin(); ritr != vec.rend(); ritr++)
    std::cout << *ritr << std::endl;

  auto ritr = std::find(vec.rbegin(), vec.rend(), 6);

  // Wstawianie
  // vec.insert(ritr, 9);      //compile error
  vec.insert(ritr.base(), 9); // vec : {1,2,3,9,4,5}

  // ritr jest uniewazniony
  ritr = std::find(vec.rbegin(), vec.rend(),
                   6); // bez tego wiersza mamy double free

  // Usuwanie
  // vec.erase(ritr);      //compile error
  vec.erase(ritr.base()); // vec: {1,2,4,5}

  return 0;
}
