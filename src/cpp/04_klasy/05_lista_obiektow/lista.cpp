#include "lista.h"

#include <ostream>
#include <utility>

Lista::Lista(Student s) : glowa(new Wezel(std::move(s))) {}

Lista::~Lista() {
  while (glowa != nullptr) {
    Wezel *nastepny = glowa->getNastepny();
    delete glowa;
    glowa = nastepny;
  }
}

void Lista::wstaw(Student s) {
  Wezel *strzalka = glowa;
  while (strzalka->getNastepny() != nullptr) {
    strzalka = strzalka->getNastepny();
  }
  strzalka->setNastepny(new Wezel(std::move(s)));
}

namespace {
void zamienStudentow(Wezel *a, Wezel *b) {
  Student temp = b->getStudent();
  b->setStudent(a->getStudent());
  a->setStudent(std::move(temp));
}

Wezel *znajdzMin(Wezel *glowa) {
  Wezel *min = glowa;
  for (Wezel *strzalka = glowa; strzalka != nullptr;
       strzalka = strzalka->getNastepny()) {
    if (strzalka->getStudent() < min->getStudent()) {
      min = strzalka;
    }
  }
  return min;
}
} // namespace

void Lista::posortuj() {
  for (Wezel *strzalka = glowa; strzalka != nullptr;
       strzalka = strzalka->getNastepny()) {
    zamienStudentow(znajdzMin(strzalka), strzalka);
  }
}

std::ostream &operator<<(std::ostream &strumien, const Lista &l) {
  const Wezel *strzalka = l.glowa;
  int i = 1;

  while (strzalka != nullptr) {
    strumien << "Student: " << i++ << '\n';
    strumien << strzalka->getStudent() << '\n';
    strzalka = strzalka->getNastepny();
  }

  return strumien;
}
