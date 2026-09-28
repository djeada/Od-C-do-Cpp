#include <iostream>

class PrzykladowaKlasa {};

int suma(int x, int y) { return x + y; }

int kwadrat(int &x) { return x * x; }

int stalyKwadrat(const int &x) { return x * x; }

int zmiennaGlobalna;

int &foo() { return zmiennaGlobalna; }
int bar() { return zmiennaGlobalna; }

int main() {
  int i = 2;   // i jest lvalue
  int *p = &i; // &i pozwala pobrać adres lvalue

  PrzykladowaKlasa d1;
  PrzykladowaKlasa d2;
  d2 = PrzykladowaKlasa(); // tymczasowy obiekt jest rvalue

  int x = 2;
  int c = i + 2; // wynik wyrażenia i + 2 jest rvalue
  i = suma(3, 4);

  int &adres = i;
  const int &r = 5; // const lvalue reference może wiązać się z rvalue

  std::cout << "Adres i: " << static_cast<void *>(p) << '\n';
  std::cout << "x=" << x << ", c=" << c << ", i=" << i << '\n';
  std::cout << "referencja do i: " << adres << '\n';
  std::cout << "const ref do rvalue: " << r << '\n';
  std::cout << "kwadrat(i): " << kwadrat(i) << '\n';
  std::cout << "stalyKwadrat(40): " << stalyKwadrat(40) << '\n';

  foo() = 50; // foo() zwraca lvalue reference
  std::cout << "foo(): " << foo() << ", bar(): " << bar() << '\n';

  // Obiekty są używane, żeby przykład nie sprowadzał się do martwych deklaracji.
  std::cout << "Adres d1: " << static_cast<const void *>(&d1)
            << ", adres d2: " << static_cast<const void *>(&d2) << '\n';

  return 0;
}
