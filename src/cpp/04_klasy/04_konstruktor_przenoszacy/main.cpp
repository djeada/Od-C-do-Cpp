#include <iostream>
#include <stdexcept>
#include <utility>

void printInt(int &i) { std::cout << "lvalue reference: " << i << std::endl; }

void printInt2(int &&i) { std::cout << "rvalue reference: " << i << std::endl; }

class Move {
private:
  int *data;

public:
  explicit Move(int d) : data(new int(d)) {}

  Move(const Move &source)
      : data(source.data != nullptr ? new int(*source.data) : nullptr) {}

  Move(Move &&source) noexcept : data(std::exchange(source.data, nullptr)) {}

  Move &operator=(const Move &source) {
    if (this == &source) {
      return *this;
    }

    Move kopia(source);
    swap(kopia);
    return *this;
  }

  Move &operator=(Move &&source) noexcept {
    if (this != &source) {
      delete data;
      data = std::exchange(source.data, nullptr);
    }
    return *this;
  }

  ~Move() { delete data; }

  void swap(Move &other) noexcept { std::swap(data, other.data); }

  int value() const {
    if (data == nullptr) {
      throw std::logic_error("Obiekt zostal przeniesiony.");
    }
    return *data;
  }
};

int main() {
  int a = 5;
  printInt(a);
  printInt2(a + 1);

  Move obiekt(1);
  Move kopia(obiekt);
  Move przeniesiony(std::move(kopia));

  Move przypisany(0);
  przypisany = obiekt;

  Move przeniesionyPrzezPrzypisanie(0);
  przeniesionyPrzezPrzypisanie = std::move(przypisany);

  std::cout << obiekt.value() << ' ' << przeniesiony.value() << ' '
            << przeniesionyPrzezPrzypisanie.value() << '\n';

  return 0;
}
