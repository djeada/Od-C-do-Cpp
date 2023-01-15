## Szablony

Szablony to mechanizm języka C++, który umożliwia tworzenie uniwersalnych klas i funkcji, które mogą przyjmować różne typy danych. Dzięki szablonom, możemy uniknąć tworzenia wielu odmiennych definicji tej samej funkcji czy klasy, dostosowując ją do różnych typów danych.

### Szablon funkcji

Szablon funkcji pozwala na napisanie jednej definicji funkcji, która będzie mogła przyjmować argumenty różnych typów. Aby utworzyć szablon funkcji, należy użyć słowa kluczowego `template` oraz oznaczyć typ argumentów jako typ uogólniony, np. `T`. Przykład funkcji `max2`, która zwraca większą z dwóch przekazanych wartości typu `T`:

```c++
template <typename T> T max2(T arg1, T arg2) {
  return arg1 > arg2 ? arg1 : arg2;
}
```

Funkcja ta może być używana z różnymi typami danych:

```c++
max2(10, 20);     // 20
max2(16.2, 3.14); // 16.2
max2('a', 'b');   // 'b'
```

Kompilator jest w stanie automatycznie wywnioskować typy argumentów na podstawie podanych wartości. Jeśli typy argumentów nie będą pasować do operacji w ciele funkcji, kompilator zgłosi błąd.

### Szablon klasy

Podobnie jak w przypadku funkcji, szablon klasy pozwala na napisanie jednej definicji klasy, która będzie mogła pracować z różnymi typami danych. Aby utworzyć szablon klasy, należy również użyć słowa kluczowego template oraz oznaczyć typ pól jako typ uogólniony, np. `T`. Przykład klasy `Foo`, która posiada pole `x` typu `T`:

```c++
template <typename T> class Foo {
  T x;

public:
  Foo(T x) : x(x) {
    std::cout << "Utworzono obiekt Foo o typie pola x: " << typeid(T).name()
              << std::endl;
  }
  T getX() { return x; }
};
```

Klasa ta może być używana z różnymi typami danych, tworząc obiekty z odpowiednim typem pola `x`:

```c++
Foo<int> foo1(10); // utworzy obiekt z polami x typu int
Foo<float> foo2(3.14); // utworzy obiekt z polami x typu float
Foo<char> foo3('a'); // utworzy obiekt z polami x typu char
```

Kompilator automatycznie dopasuje typ pola `x` do podanego typu podczas tworzenia obiektu. Tak jak w przypadku szablonów funkcji, jeśli typ pola nie będzie pasować do operacji w ciele klasy, kompilator zgłosi błąd.

Szablony są bardzo przydatnym mechanizmem języka C++, pozwalającym na uniwersalne i elastyczne podejście do tworzenia kodu. Dzięki nim możemy uniknąć konieczności tworzenia wielu odmiennych definicji tej samej funkcji czy klasy dla różnych typów danych.
