#include <iostream>

int main() {
  const int i = 9;

  const int *p1 = &i;
  std::cout << "Stala wartosc przez wskaznik: " << *p1 << '\n';

  int b = 0;
  int *const p2 = &b;
  *p2 = 5;
  std::cout << "Staly wskaznik, zmienne dane: " << b << '\n';

  // const_cast jest bezpieczny tylko wtedy, gdy obiekt bazowy nie byl
  // pierwotnie zadeklarowany jako const.
  int j = 5;
  const int &widokConst = j;
  const_cast<int &>(widokConst) = 6;
  std::cout << j << '\n';

  // const int naprawdęStaly = 5;
  // const_cast<int &>(naprawdeStaly) = 6; // UB - nie robimy tego.

  return 0;
}
