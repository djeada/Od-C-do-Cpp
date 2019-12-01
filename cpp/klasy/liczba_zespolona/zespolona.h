#ifndef zespolona_h
#define zespolona_h

#include <iostream>

using namespace std;

/*
z = 4 + j9

Zespolona z1;
Zespolona z2(2.1, 3.2);


z1 = 8 + j2;
z2 = -5 + j2;

z1 + z2 = 3 + j4

cout << z1;

*/

class Zespolona {
private:
  double Re;
  double Im;

public:
  Zespolona();
  Zespolona(double a, double b);

  double Modul();
  void Sprzezenie();

  friend Zespolona operator+(const Zespolona &z1, const Zespolona &z2);
  friend Zespolona operator-(const Zespolona &z1, const Zespolona &z2);
  friend Zespolona operator*(const Zespolona &z1, const Zespolona &z2);
  friend Zespolona operator/(const Zespolona &z1, const Zespolona &z2);
  friend bool operator==(const Zespolona &z1, const Zespolona &z2);

  friend ostream &operator<<(ostream &out, const Zespolona &z);
};

#endif
