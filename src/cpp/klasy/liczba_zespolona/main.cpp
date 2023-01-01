#include "zespolona.h"
#include <iostream>

using namespace std;

int main() {

  Zespolona z1;
  Zespolona z2(9, 12);

  cout << z1;
  cout << z2;

  cout << z1 * z2;

  Zespolona z3(-3, -3);

  cout << z3 + z2;
  cout << z3 / z2;

  z2.Sprzezenie();

  cout << z2;

  cout << z3.Modul() << endl;

  cout << boolalpha << (z1 == z2) << endl;
  cout << boolalpha << (z3 == z3) << endl;

  return 0;
}
