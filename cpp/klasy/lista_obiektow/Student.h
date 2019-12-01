#ifndef __Student_H__
#define __Student_H__

#include <iostream>

using namespace std;

class Student {
  string imie;
  string nazwisko;
  int indeks;

public:
  Student();
  Student(string a, string b, int c);

  friend bool operator<(const Student &s1, const Student &s2);
  friend ostream &operator<<(ostream &strumien, const Student &s);
};

#endif
