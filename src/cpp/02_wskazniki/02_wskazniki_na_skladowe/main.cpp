#include <iostream>

class Foo {
public:
  int x;
  int y;

  Foo(int x, int y) : x(x), y(y) {}

  void wypisz() { std::cout << x << " " << y << std::endl; }

  void zwieksz() {
    x++;
    y++;
  }
};

int main() {
  Foo foo(10, 20);

  // wskazniki na zwykle pola
  int *x = &foo.x;
  int *y = &foo.y;
  *x = 100;
  *y = 200;
  std::cout << foo.x << std::endl;
  std::cout << foo.y << std::endl;

  // wskaznik na metode
  void (Foo::*f)();

  // wskaznik wskazuje na funkcje Foo::wypisz()
  f = &Foo::wypisz;
  (foo.*f)();

  // wskaznik wskazuje na funkcje Foo::zwieksz()
  f = &Foo::zwieksz;
  (foo.*f)();

  // wskaznik ponownie wskazuje na funkcje Foo::wypisz()
  f = &Foo::wypisz;
  (foo.*f)();

  return 0;
}
