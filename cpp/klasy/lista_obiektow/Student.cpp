#include "Student.h"

Student::Student() {
  imie = "xxx";
  nazwisko = "xxx";
  indeks = 0;
}

Student::Student(string a, string b, int c) {
  imie = a;
  nazwisko = b;
  indeks = c;
}

bool operator<(const Student &s1, const Student &s2) {
  return s1.nazwisko < s2.nazwisko;
}

ostream &operator<<(ostream &strumien, const Student &s) {
  cout << "Imie: " << s.imie << endl;
  cout << "Nazwisko: " << s.nazwisko << endl;
  cout << "Indeks: " << s.indeks << endl;
  return strumien;
}
