#include <iostream>
#include <memory>
#include <utility>

class Lista {
  struct Wezel {
    int wartosc;
    std::unique_ptr<Wezel> nastepny;

    explicit Wezel(int wartosc) : wartosc(wartosc) {}
  };

  std::unique_ptr<Wezel> glowa_;

public:
  void push_front(int wartosc) {
    auto nowy = std::make_unique<Wezel>(wartosc);
    nowy->nastepny = std::move(glowa_);
    glowa_ = std::move(nowy);
  }

  bool zawiera(int wartosc) const {
    for (const Wezel *wezel = glowa_.get(); wezel != nullptr;
         wezel = wezel->nastepny.get()) {
      if (wezel->wartosc == wartosc) {
        return true;
      }
    }
    return false;
  }

  void wypisz() const {
    for (const Wezel *wezel = glowa_.get(); wezel != nullptr;
         wezel = wezel->nastepny.get()) {
      std::cout << wezel->wartosc << ' ';
    }
    std::cout << '\n';
  }
};

int main() {
  Lista lista;
  lista.push_front(3);
  lista.push_front(2);
  lista.push_front(1);

  lista.wypisz();
  std::cout << std::boolalpha << "zawiera 2: " << lista.zawiera(2) << '\n';
  std::cout << "zawiera 8: " << lista.zawiera(8) << '\n';
  return 0;
}
