
## Typ wyliczeniowy enum

Typ wyliczeniowy <code>enum</code> pozwala na tworzenie zmiennych, które mogą przyjmować jedynie z góry określone wartości. Wartości te mają czytelne nazwy, a dodatkowo <code>enum</code> jest bardzo szybki i opłaca się go używać nawet w krytycznych miejscach programu.

```c++
#include <iostream>

enum class Kolor { Czerwony, Zielony, Niebieski };

int main() {
  Kolor kolor = Color::Czerwony;

  switch (kolor) {
  case Color::Czerwony:
    std::cout << "Wybrano czerwony." << std::endl;
    break;
  case Color::Zielony:
    std::cout << "Wybrano zielony." << std::endl;
    break;
  case Color::Niebieski:
    std::cout << "Wybrano niebieski." << std::endl;
    break;
  default:
    std::cout << "Blad!" << std::endl;
  }

  return 0;
}
```
