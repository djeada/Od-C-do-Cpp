#ifndef STUDENT_H
#define STUDENT_H

#include <iosfwd>
#include <string>

class Student {
  std::string imie;
  std::string nazwisko;
  int indeks;

public:
  Student();
  Student(std::string a, std::string b, int c);

  friend bool operator<(const Student &s1, const Student &s2);
  friend std::ostream &operator<<(std::ostream &strumien, const Student &s);
};

#endif
