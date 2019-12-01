#ifndef __Lista_H__
#define __Lista_H__

#include "Student.h"

using namespace std;

class Wezel {
  Student nasz_student;
  Wezel *nastepny;

public:
  Wezel(Student s) {
    nasz_student = s;
    nastepny = nullptr;
  }

  void setStudent(Student s) { nasz_student = s; }

  void setNastepny(Wezel *w) { nastepny = w; }

  Student getStudent() { return nasz_student; }

  Wezel *getNastepny() { return nastepny; }
};

class Lista {
  Wezel *glowa;

public:
  Lista(Student s);
  ~Lista();

  void wstaw(Student s);
  void posortuj();

  friend ostream &operator<<(ostream &strumien, const Lista &l);
};

#endif
