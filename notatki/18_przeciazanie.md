## Przeciążanie
Przeciążanie (ang. overloading) to mechanizm, który pozwala na posiadanie kilku definicji tej samej nazwy funkcji lub operatora, które są rozróżnialne dla kompilatora na podstawie typów argumentów. Przeciążanie jest często używane w językach takich jak C++, C# i Java.

### Przeciążanie funkcji

W poniższym przykładzie mamy trzy funkcje o tej samej nazwie "f", ale z różnymi typami argumentów. Kompilator jest w stanie rozróżnić, która z tych funkcji powinna zostać wywołana na podstawie typów przekazywanych argumentów.

```c++
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
  f(a);    // wywolana zostanie funkcja1
  f(b);    // wywolana zostanie funkcja2
  f(a, b); // wywolana zostanie funkcja3
  return 0;
}
```

Należy jednak pamiętać, że przy przeciążaniu funkcji należy być szczególnie ostrożnym w przypadku domyślnych wartości parametrów. Jeśli do powyższego przykładu dodalibyśmy nową funkcję o następującej definicji:

```c++
// funkcja4
void f(int a, double b = 10.0) { std::cout << "int, double" << std::endl; }
```

To mielibyśmy konflikt z funkcjami 1 i 3, ponieważ kompilator nie będzie w stanie wybrać odpowiedniej funkcji dla następujących wywołań:

```c++
f(10);       // konflikt między funkcjami 1 i 4
f(10, 10.0); // konflikt między funkcjami 3 i 4
```

### Przeciążanie operatorów

Innym typem przeciążania jest przeciążanie operatorów. W C++ możemy przeciążyć operator przypisania, operatora dodawania, operatora mnożenia i wiele innych. Oznacza to, że możemy dla różnych symboli zdefiniować całkowicie nowe zachowanie.

```c++
class Foo {
public:
  Foo() { std::cout << "Konstruktor" << std::endl; }
  Foo(const Foo &foo) { std::cout << "Konstruktor kopiujący" << std::endl; }
  Foo &operator=(const Foo &foo) {
    std::cout << "Operator przypisania" << std::endl;
    return *this;
  }
  Foo operator+(const Foo &foo) {
    std::cout << "Operator dodawania" << std::endl;
    return *this;
  }
  Foo operator*(const Foo &foo) {
    std::cout << "Operator mnożenia" << std::endl;
    return *this;
  }
};

int main() {
  Foo foo1;
  Foo foo2;
  foo1 = foo2;
  foo1 + foo2;
  foo1 * foo2;
  return 0;
}
```

W powyższym przykładzie zdefiniowaliśmy przeciążenie operatora przypisania i operatora dodawania dla klasy Foo. Dzięki temu, kiedy używamy tych operatorów w kodzie, odpowiednie metody zostaną automatycznie wywołane.

Przeciążanie operatorów pozwala na stworzenie bardziej naturalnego i czytelnego kodu, ponieważ pozwala na użycie standardowych symboli matematycznych do reprezentowania operacji na obiektach.
