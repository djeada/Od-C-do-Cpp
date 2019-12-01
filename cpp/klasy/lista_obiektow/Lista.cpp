#include "Lista.h"

Lista::Lista(Student s) { glowa = new Wezel(s); }

Lista::~Lista() {
  Wezel *oczyszczacz = glowa;

  while (glowa != nullptr) {
    glowa = glowa->getNastepny();
    delete oczyszczacz;
    oczyszczacz = glowa;
  }
}

void Lista::wstaw(Student s) {

  Wezel *strzalka = glowa;

  while (strzalka->getNastepny() != nullptr) {
    strzalka = strzalka->getNastepny();
  }

  Wezel *nowy = new Wezel(s);
  strzalka->setNastepny(nowy);
}

void swap(Wezel *&a, Wezel *&b) {
  Student temp = b->getStudent();
  b->setStudent(a->getStudent());
  a->setStudent(temp);
}

Wezel *znajdzMin(Wezel *glowa) {

  Wezel *min = glowa;
  Wezel *strzalka = glowa;

  while (strzalka->getNastepny() != nullptr) {
    strzalka = strzalka->getNastepny();

    if (strzalka->getStudent() < min->getStudent()) {
      min = strzalka;
    }
  }

  return min;
}

void Lista::posortuj() {

  Wezel *strzalka = glowa;

  while (strzalka != nullptr) {
    Wezel *min = znajdzMin(strzalka);
    swap(min, strzalka);
    strzalka = strzalka->getNastepny();
  }
}

ostream &operator<<(ostream &strumien, const Lista &l) {
  Wezel *strzalka = l.glowa;

  int i = 1;
  while (strzalka != nullptr) {
    cout << "Student: " << i << endl;
    cout << strzalka->getStudent() << endl;
    strzalka = strzalka->getNastepny();
    i++;
  }

  return strumien;
}
