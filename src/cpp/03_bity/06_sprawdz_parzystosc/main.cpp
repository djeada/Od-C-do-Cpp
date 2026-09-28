#include <iostream>

bool czyParzysta(unsigned int liczba) { return (liczba & 1u) == 0u; }

int main() {
  const unsigned int a = 8;
  const unsigned int b = 7;

  std::cout << std::boolalpha;
  std::cout << a << " parzysta: " << czyParzysta(a) << '\n';
  std::cout << b << " parzysta: " << czyParzysta(b) << '\n';

  return 0;
}
