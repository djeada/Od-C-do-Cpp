#include "stos.h"

#include <iostream>

int main() {
  Stos s1;

  s1.odlozNaStos(3);
  s1.odlozNaStos(54);
  s1.odlozNaStos(2);

  std::cout << s1 << '\n';
  std::cout << std::boolalpha << s1.odlozNaStos(2) << '\n';

  ++s1;
  ++s1;

  std::cout << std::boolalpha << s1.odlozNaStos(2) << '\n';
  s1.odlozNaStos(10);

  std::cout << s1 << '\n';
  std::cout << std::boolalpha << s1.czyPelny() << '\n';

  Stos s2(2);
  s2.odlozNaStos(11);
  s2.odlozNaStos(7);
  std::cout << s2.sciagnijZeStosu() << '\n';

  Stos s3(s2);
  std::cout << s3 << '\n';

  return 0;
}
