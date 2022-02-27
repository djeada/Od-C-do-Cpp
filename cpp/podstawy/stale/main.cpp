#include <iostream>

/*
Dlaczego warto używać const
    - Zabezpiecza przed nieumyślnym zapisem do zmiennej
    - samodokumentowanie
    - Włącz kompilator do optymalizacji, dzięki czemu kod będzie ciaśniejszy
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

  // jeśli const jest na lewo od *, dane sa const
  // jeśli const jest na prawo od *, wskaźnik jest const

  const int j = 5;
  // static_cast<const int &>(j) = 7; // static_cast nie dziala z const

  // usuwa const
  const_cast<int &>(j) = 6;
  std::cout << j << std::endl;

  return 0;
}
