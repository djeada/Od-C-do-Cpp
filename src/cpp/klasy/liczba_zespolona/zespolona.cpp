#include "zespolona.h"
#include <cmath>

Zespolona::Zespolona() {
  Re = 0;
  Im = 0;
}

Zespolona::Zespolona(double a, double b) {
  Re = a;
  Im = b;
}

double Zespolona::Modul() { return sqrt(Re * Re + Im * Im); }

void Zespolona::Sprzezenie() { Im *= -1; }

/*
z1 = 8 + j2;
z2 = -5 + j2;

z1 + z2 = 3 + j4
*/

Zespolona operator+(const Zespolona &z1, const Zespolona &z2) {
  Zespolona z3(z1.Re + z2.Re, z1.Im + z2.Im);
  return z3;
}

/*
z1 = 8 + j2;
z2 = -5 + j2;

z1 - z2 = 13 + j0
*/

Zespolona operator-(const Zespolona &z1, const Zespolona &z2) {
  Zespolona z3(z1.Re - z2.Re, z1.Im - z2.Im);
  return z3;
}

/*
z1 = a1 + jb1;
z2 = a2 + jb2;

z1 * z2 = (a1 + jb1)*(a2 + jb2) = a1a2 a2jb1 + a1jb2 -b1b2
= a1a2 -b1b2 + j(a2b1 + a1b2)
*/

Zespolona operator*(const Zespolona &z1, const Zespolona &z2) {
  Zespolona z3(z1.Re * z2.Re - z1.Im * z2.Im, z1.Im * z2.Re + z2.Im * z1.Re);
  return z3;
}

Zespolona operator/(const Zespolona &z1, const Zespolona &z2) {
  double a = (z1.Re * z2.Re + z1.Im * z2.Im) / (z2.Re * z2.Re + z2.Im * z2.Im);
  double b = (z1.Re * z2.Im - z1.Im * z2.Re) / (z2.Re * z2.Re + z2.Im * z2.Im);
  Zespolona z3(a, b);
  return z3;
}

ostream &operator<<(ostream &out, const Zespolona &z) {
  if (z.Im >= 0)
    cout << z.Re << " + j" << z.Im << endl;
  else
    cout << z.Re << " - j" << abs(z.Im) << endl;
  return out;
}

bool operator==(const Zespolona &z1, const Zespolona &z2) {
  return z1.Re == z2.Re && z1.Im == z2.Im;
}
