#include <iostream>

using namespace std;

/* klasa bazowa
 klasa pochodna

 A
 |
 B
 |
 C

dziedziczenie wielokrotne
 A B
 \/
 C

problem diamentu (to jest to co chcemy uzyskac)
  A
 /\
 B C
 \/
  D

domyslnie mamy:
A A
| |
B C
\/
 D

*/

class A {
  int pole_a;

public:
  void set_a(int x) { pole_a = x; }
  void print_a() { cout << "Wartosc pola a: " << pole_a << endl; }
};

class B : virtual public A {
  int pole_b;

public:
  void set_b(int x) { pole_b = x; }
  void print_b() { cout << "Wartosc pola b: " << pole_b << endl; }
};

class C : virtual public A {
  int pole_c;

public:
  void set_c(int x) { pole_c = x; }
  void print_c() { cout << "Wartosc pola c: " << pole_c << endl; }
};

class D : public B, public C {
  int pole_d;

public:
  void set_d(int x) { pole_d = x; }
  void print_d() { cout << "Wartosc pola d: " << pole_d << endl; }
};

int main() {

  cout << "Obiekt klasy A: " << endl;
  A obiekt_a;
  obiekt_a.set_a(5);
  obiekt_a.print_a();

  cout << endl << "Obiekt klasy B: " << endl;
  B obiekt_b;
  obiekt_b.set_a(10);
  obiekt_b.set_b(12);
  obiekt_b.print_a();
  obiekt_b.print_b();

  cout << endl << "Obiekt klasy C: " << endl;
  C obiekt_c;
  obiekt_c.set_a(7);
  obiekt_c.set_c(-9);
  obiekt_c.print_a();
  obiekt_c.print_c();

  cout << endl << "Obiekt klasy D: " << endl;
  D obiekt_d;
  obiekt_d.set_a(2);
  obiekt_d.set_b(6);
  obiekt_d.set_c(4);
  obiekt_d.set_d(-11);
  obiekt_d.print_a();
  obiekt_d.print_b();
  obiekt_d.print_c();
  obiekt_d.print_d();

  return 0;
}
