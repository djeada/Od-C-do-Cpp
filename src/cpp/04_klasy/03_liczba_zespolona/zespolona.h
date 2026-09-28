#ifndef ZESPOLONA_H
#define ZESPOLONA_H

#include <iosfwd>

class Zespolona {
private:
  double Re;
  double Im;

public:
  Zespolona();
  Zespolona(double a, double b);

  double Modul() const;
  void Sprzezenie();

  friend Zespolona operator+(const Zespolona &z1, const Zespolona &z2);
  friend Zespolona operator-(const Zespolona &z1, const Zespolona &z2);
  friend Zespolona operator*(const Zespolona &z1, const Zespolona &z2);
  friend Zespolona operator/(const Zespolona &z1, const Zespolona &z2);
  friend bool operator==(const Zespolona &z1, const Zespolona &z2);
  friend std::ostream &operator<<(std::ostream &out, const Zespolona &z);
};

#endif
