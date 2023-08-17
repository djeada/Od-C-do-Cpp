## Przeciążanie
Przeciążanie (ang. overloading) to mechanizm, który pozwala na posiadanie kilku definicji tej samej nazwy funkcji lub operatora, które są rozróżnialne dla kompilatora na podstawie typów argumentów. Przeciążanie jest często używane w językach takich jak C++, C# i Java.

### Przeciążanie funkcji

Przeciążanie funkcji (ang. *function overloading*) pozwala definiować wiele funkcji o tej samej nazwie, lecz różniących się typem i/lub liczbą argumentów. Jest to cecha charakterystyczna dla wielu języków programowania takich jak C++, C# czy Java.

Dzięki przeciążaniu można tworzyć funkcje bardziej uniwersalne, które radzą sobie z różnymi typami danych, a jednocześnie zachowują jednolitą nazwę, co przyczynia się do czytelności kodu.

Poniżej znajduje się przykład trzech przeciążonych funkcji o nazwie "f", różniących się typami i liczbą argumentów:

```cpp
#include <iostream>

// funkcja1
void f(int a) { std::cout << "int" << std::endl; }

// funkcja2
void f(double a) { std::cout << "double" << std::endl; }

// funkcja3
void f(int a, double b) { std::cout << "int, double" << std::endl; }

int main() {
  int a = 10;
  double b = 10.0;
  f(a);    // wywołuje funkcję1
  f(b);    // wywołuje funkcję2
  f(a, b); // wywołuje funkcję3
  return 0;
}
```

Mimo że wszystkie te funkcje mają taką samą nazwę, kompilator potrafi rozróżnić je na podstawie przekazanych argumentów.

Podczas przeciążania funkcji istotne jest unikanie sytuacji, które mogą wprowadzić niejednoznaczność wywołań. Takie sytuacje mogą wystąpić, na przykład, gdy korzysta się z domyślnych wartości argumentów.

Przyjmijmy, że dodaliśmy kolejną przeciążoną funkcję do powyższego przykładu:

```cpp
// funkcja4
void f(int a, double b = 10.0) { std::cout << "int, double with default" << std::endl; }
```

Wówczas pojawiają się problemy dla pewnych wywołań:

```cpp
f(10);       // konflikt między funkcją1 i funkcją4
f(10, 10.0); // konflikt między funkcją3 i funkcją4
```

W obu przypadkach kompilator napotkałby na niejednoznaczność, ponieważ nie jest w stanie jednoznacznie zdecydować, którą funkcję wybrać. Dlatego zaleca się ostrożność podczas kombinowania z przeciążaniem funkcji i domyślnymi wartościami argumentów.

### Przeciążanie operatorów

Przeciążanie operatorów to jedna z cech języka C++, która pozwala programiście zdefiniować zachowanie standardowych operatorów dla własnych typów danych. Oznacza to, że możliwe jest zdefiniowanie zachowania dla operatorów takich jak przypisanie (`=`), dodawanie (`+`), mnożenie (`*`) i wielu innych, dla własnych klas czy struktur.

Dzięki temu, kod staje się bardziej intuicyjny, gdyż operacje na obiektach są reprezentowane przy pomocy znanych operatorów, zamiast metod o specyficznych nazwach.

Poniżej znajduje się klasa `Foo`, dla której przeciążono kilka operatorów:

```cpp
#include <iostream>

class Foo {
public:
  Foo() { std::cout << "Konstruktor" << std::endl; }
  Foo(const Foo &foo) { std::cout << "Konstruktor kopiujący" << std::endl; }

  Foo &operator=(const Foo &foo) {
    std::cout << "Operator przypisania" << std::endl;
    // Tutaj powinno być właściwe przypisanie atrybutów
    return *this;
  }

  Foo operator+(const Foo &foo) {
    std::cout << "Operator dodawania" << std::endl;
    // Tutaj powinno być właściwe dodawanie atrybutów i zwrócenie nowego obiektu
    return *this;
  }

  Foo operator*(const Foo &foo) {
    std::cout << "Operator mnożenia" << std::endl;
    // Tutaj powinno być właściwe mnożenie atrybutów i zwrócenie nowego obiektu
    return *this;
```

Należy pamiętać, że podczas przeciążania operatorów ważne jest dbanie o poprawność logiczną i matematyczną operacji. Na przykład, jeśli przeciążamy operator dodawania dla klasy reprezentującej macierze, powinniśmy dbać o to, by dodawane były jedynie macierze o tych samych wymiarach i że wynik był poprawny matematycznie.
