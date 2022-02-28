#include <iostream>

/*
maska: liczba z bitami ustawiony (1) i ywlaczonymi (0)
uzywana aby ustawic, wylaczyc, odwrocic bity innej liczby za pomoca pojedynczej
operacji logicznej lub czytac

0000 0010 Masa
1001 0110 Flaga
flaga & maska
maska zaslania bity

*/
using namespace std;

int main() {
  int flag = 15;  // 0000 1111
  int mask = 182; // 1011 0110

  flag = flag | mask;

  // bity maski ustawia bity flagi

  flag = flag & ~(mask);

  // bity maski czyszcza bity flagi

  flag = flag ^ mask;

  // toggle

  // does the flag have bit 1 set to 1?

  if ((flags & MASK) == MASK)
}
