#include "zespolona.h"

#include <cmath>
#include <stdexcept>

Zespolona::Zespolona() : Re(0), Im(0) {}

Zespolona::Zespolona(double a, double b) : Re(a), Im(b) {}

double Zespolona::Modul() { return std::sqrt(Re * Re + Im * Im); }

void Zespolona::Sprzezenie() { Im *= -1; }

Zespolona operator+(const Zespolona &z1, const Zespolona &z2) {
  return Zespolona(z1.Re + z2.Re, z1.Im + z2.Im);
}

Zespolona operator-(const Zespolona &z1, const Zespolona &z2) {
  return Zespolona(z1.Re - z2.Re, z1.Im - z2.Im);
}

Zespolona operator*(const Zespolona &z1, const Zespolona &z2) {
  return Zespolona(z1.Re * z2.Re - z1.Im * z2.Im,
                   z1.Im * z2.Re + z2.Im * z1.Re);
}

Zespolona operator/(const Zespolona &z1, const Zespolona &z2) {
  const double mianownik = z2.Re * z2.Re + z2.Im * z2.Im;
  if (mianownik == 0.0) {
    throw std::domain_error("Dzielenie przez zero zespolone.");
  }

  const double re = (z1.Re * z2.Re + z1.Im * z2.Im) / mianownik;
  const double im = (z1.Im * z2.Re - z1.Re * z2.Im) / mianownik;
  return Zespolona(re, im);
}

ostream &operator<<(ostream &out, const Zespolona &z) {
  if (z.Im >= 0) {
    out << z.Re << " + j" << z.Im << endl;
  } else {
    out << z.Re << " - j" << std::abs(z.Im) << endl;
  }
  return out;
}

bool operator==(const Zespolona &z1, const Zespolona &z2) {
  return z1.Re == z2.Re && z1.Im == z2.Im;
}
