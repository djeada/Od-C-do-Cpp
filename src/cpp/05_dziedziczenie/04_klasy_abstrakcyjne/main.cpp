#include <iostream>

struct Abstract {
  virtual ~Abstract() = default;
  virtual void f() = 0;
};

struct Concrete : Abstract {
  void f() override { std::cout << "Concrete::f\n"; }
  virtual void g() { std::cout << "Concrete::g\n"; }
};

struct Abstract2 : Concrete {
  void g() override = 0;
};

int main() {
  Concrete b;
  Abstract &a = b;
  a.f();
  b.g();
  return 0;
}
