
## Wyjątki

Błąd - wszystko, co uniemożliwia poprawne działanie programu.
Sygnał - informacja przesyłana do procesu.
Wyjątek - mechanizm języka programowania umożliwiający programiście wyrażenie, że dana funkcja nie może poprawnie kontynuować działania.

Błędy składniowe – użycie kodu niezgodnego z konwencjami danego języka programowania, wykrywane w czasie kompilacji.
Błędy logiczne – kod, który miał zostać uruchomiony nie jest uruchomiony, błędy w ifach, zła kolejność wykonywania operacji
Błędy semantyczne – program został błędnie zakodowany, nie robi tego, co powinien robić

Problemy z pamięcią:

- Przepełnienie stosu (rekurencja, rozmiar zmiennych statycznych)
- Rozmiar zmiennych

### Działanie wyjątków

Wyrzucenie wyjątku powoduje przerwanie działania funkcji, w której wystąpiło wyrzucenie.
Istnieje możliwość obsłużenia wyjątku przy pomocy bloku try-catch. Catch musi sprecyzować typ wyjątku, który ma zostać obsłużony. Jeśli typ pokrywa się z typem wyjątku, to blok catch zostanie wykonany.

```c++
#include <iostream>

void funkcja() { throw std::runtime_error("Wyjatek"); }

int main() {
  try {
    funkcja();
  } catch (std::runtime_error &e) {
    std::cout << "Wyjatek: " << e.what() << std::endl;
  }

  std::cout << "Zycie toczy sie dalej" << std::endl;

  return 0;
}
```
