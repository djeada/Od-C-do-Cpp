#ifndef LISTA_H
#define LISTA_H

#include "student.h"

#include <iosfwd>
#include <utility>

class Wezel {
  Student nasz_student;
  Wezel *nastepny = nullptr;

public:
  explicit Wezel(Student s) : nasz_student(std::move(s)) {}

  void setStudent(Student s) { nasz_student = std::move(s); }
  void setNastepny(Wezel *w) { nastepny = w; }

  const Student &getStudent() const { return nasz_student; }
  Wezel *getNastepny() const { return nastepny; }
};

class Lista {
  Wezel *glowa;

public:
  explicit Lista(Student s);
  Lista(const Lista &) = delete;
  Lista &operator=(const Lista &) = delete;
  ~Lista();

  void wstaw(Student s);
  void posortuj();

  friend std::ostream &operator<<(std::ostream &strumien, const Lista &l);
};

#endif
