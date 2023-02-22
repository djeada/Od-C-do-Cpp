#include <iostream>

/*
Dlaczego warto uzywac const
    - Zabezpiecza przed nieumyslnym zapisem do zmiennej
    - samodokumentowanie
    - Wlacz kompilator do optymalizacji, dzieki czemu kod bedzie ciasniejszy
*/

int main() {

  const int i = 9;
  // i = 8;            // error

  const int *p1 = &i; // dane sa stale, wskaznik jest zmienny.
  //*p1 = 5;          // error
  p1++; // ok

  int b;
  int *const p2 = &b; // wskaznik jest staly, dane sa zmienne
  //*p2 = 5;            // ok
  // int *const p2 = &i; //error

  // jesli const jest na lewo od *, dane sa const
  // jesli const jest na prawo od *, wskaznik jest const

  const int j = 5;
  // static_cast<const int &>(j) = 7; // static_cast nie dziala z const

  // usuwa const
  const_cast<int &>(j) = 6;
  std::cout << j << std::endl;

  return 0;
}
