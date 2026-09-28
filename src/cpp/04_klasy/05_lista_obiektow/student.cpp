#include "student.h"

#include <ostream>
#include <utility>

Student::Student() : imie("xxx"), nazwisko("xxx"), indeks(0) {}

Student::Student(std::string a, std::string b, int c)
    : imie(std::move(a)), nazwisko(std::move(b)), indeks(c) {}

bool operator<(const Student &s1, const Student &s2) {
  return s1.nazwisko < s2.nazwisko;
}

std::ostream &operator<<(std::ostream &strumien, const Student &s) {
  strumien << "Imie: " << s.imie << '\n';
  strumien << "Nazwisko: " << s.nazwisko << '\n';
  strumien << "Indeks: " << s.indeks << '\n';
  return strumien;
}
