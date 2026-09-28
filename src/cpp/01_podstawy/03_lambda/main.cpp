#include <iostream>
#include <vector>

template <typename Funkcja>
void filtruj(Funkcja f, const std::vector<int> &arr) {
  for (int i : arr) {
    if (f(i)) {
      std::cout << i << " ";
    }
  }
  std::cout << std::endl;
}

int main() {
  std::cout << [](int x, int y) { return x + y; }(3, 4) << std::endl;

  auto f = [](int x, int y) { return x + y; };
  std::cout << f(3, 4) << std::endl;

  const std::vector<int> v = {1, 2, 3, 4, 5, 6};
  filtruj([](int x) { return x > 3; }, v);
  filtruj([](int x) { return x > 2 && x < 5; }, v);

  int y = 4;
  filtruj([y](int x) { return x > y; }, v);

  return 0;
}
