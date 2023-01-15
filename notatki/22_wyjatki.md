
## Wyjątki
W językach programowania, pojęcie błędu oznacza wszystko, co uniemożliwia poprawne działanie programu. Błędy mogą być podzielone na kilka kategorii, takie jak: błędy składniowe, błędy logiczne, błędy semantyczne oraz problemy z pamięcią.

* Błędy składniowe to użycie kodu niezgodnego z konwencjami danego języka programowania, które są wykrywane podczas kompilacji. Błędy logiczne to błędy, które uniemożliwiają uruchomienie programu lub powodują, że kod nie działa tak, jak powinien. Błędy semantyczne to błędy, które powstają z powodu niepoprawnego zakodowania programu.
* Problemy z pamięcią to między innymi przepełnienie stosu (np. przez rekurencję lub zbyt duże rozmiary zmiennych statycznych) oraz brak dostatecznej ilości pamięci dla programu.

Aby radzić sobie z tymi błędami, do niektórych języków programowania zostało wprowadzone pojęcie oraz mechanizm wyjątku. Pojęcie wyjątku odnosi się do sytuacji, w której program nie jest w stanie dalej działać poprawnie. Mechanizm natomiast pozwala programiście na zasygnalizowanie, że dana funkcja nie jest w stanie kontynuować swojego działania. 

### Działanie wyjątków

Wyrzucenie wyjątku powoduje natychmiastowe przerwanie działania funkcji. Możliwe jest jednak obsłużenie wyjątku przy pomocy bloku `try-catch`. Aby to zrobić, należy określić typ wyjątku, który ma zostać obsłużony w bloku `catch`. Jeśli typ pokrywa się z typem wyjątku, to blok `catch` zostanie wykonany.

Poniższy kod przedstawia przykład użycia wyjątku:

```c++
#include <iostream>

void funkcja() { throw std::runtime_error("wystapila wyjatkowa sytuacja!"); }

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

W powyższym przykładzie, funkcja `funkcja()` wyrzuca wyjątek typu `std::runtime_error` z komunikatem "Wyjatek". Następnie, w bloku `try-catch`, wyjątek jest obsługiwany. W bloku `catch`, jest wyświetlany komunikat "Wyjatek: wystapila wyjatkowa sytuacja!". Na końcu, program wyświetla komunikat "Zycie toczy sie dalej" co sugeruje że program nie zakończył działania po napotkaniu błędu.

Warto również zauważyć, że istnieje kilka różnych typów wyjątków, a programiści mogą tworzyć własne typy wyjątków, aby dostosować je do potrzeb swojego kodu. Obsługa wyjątków pozwala na zwiększenie niezawodności programów, ponieważ pozwala na przechwytywanie i obsługę błędów w sposób, który nie kończy działania programu.

### Własne wyjątki

Tak jak wspomniano wcześniej, programiści mogą tworzyć własne typy wyjątków, aby dostosować je do potrzeb swojego kodu. Można to zrobić poprzez dziedziczenie po już istniejących klasach wyjątków lub tworzenie własnej klasy wyjątku od podstaw.

W C++, można dziedziczyć po klasie `std::exception` lub `std::runtime_error`, aby utworzyć własny typ wyjątku. Poniżej mamy przykład tworzenia własnego typu wyjątku dziedziczącego po `std::exception`:

```c++
class WlasnyWyjatek : public std::exception
{
public:
    WlasnyWyjatek(const std::string& wiadomosc) : wiadomosc(wiadomosc) {}
    virtual const char* what() const throw() { return wiadomosc.c_str(); }
private:
    std::string wiadomosc;
};
```

W powyższym przykładzie, klasa `WlasnyWyjatek` dziedziczy po klasie `std::exception` i posiada konstruktor, który przyjmuje wiadomość opisową. Nadpisujemy metodę `what()`, aby użyć naszej wiadomości. OD teraz można używać obiektów `WlasnyWyjatek` w kodzie w taki sam sposób jak standardowe typy wyjątków.
