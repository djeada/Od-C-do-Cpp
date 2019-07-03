#include <iostream>

/*
maska: liczba z bitami ustawiony (1) i ywłączonymi (0)
używana aby ustawić, wyłączyć, odwrócić bity innej liczby za pomocą pojedynczej
operacji logicznej lub czytać

0000 0010 Masa
1001 0110 Flaga
flaga & maska
maska zasłania bity

*/
using namespace std;

int main() {
  int flag = 15;  // 0000 1111
  int mask = 182; // 1011 0110

  flag = flag | mask;

  // bity maski ustawią bity flagi

  flag = flag & ~(mask);

  // bity maski czyszczą bity flagi

  flag = flag ^ mask;

  // toggle

  // does the flag have bit 1 set to 1?

  if ((flags & MASK) == MASK)
}
