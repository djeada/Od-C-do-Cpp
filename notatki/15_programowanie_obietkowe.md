## Programowanie Obiektowe

Pisanie programów, w których w interakcje ze sobą wchodzą różne <b>obiekty</b>.

1. <b>Klasa</b> to szablon, w którym definiujemy <b>pola</b> (jakie dane mogą przechowywać obiekty danej klasy) oraz <b>metody</b> (funkcje coś robiące z tymi polami).
2. Zastosowania obiektów danej klasy dostępne są przez dostępne metody.

Dlaczego?

1. Modularność: każda klasa ma jasno określony cel i wszystko, co z nim jest związane, jest zamknięte w tej klasie (przynajmniej w teorii).
2. Łatwość wielokrotnego użytku: możemy tworzyć nieskończoną ilość obiektów danej klasy, ograniczają nas jedynie fizyczne możliwości naszej maszyny.

```C++
class Prostokat {
  int a;
  int b;

public:
  Prostokat(int a, int b) {
    this->a = a;
    this->b = b;
  }

  int pole() { return a * b; }
};
```


### Konstruktor

Konstruktor jest funkcją, która jest wywoływana przy tworzeniu obiektu. Konstruktor ma taką samą nazwę jak klasa i nie posiada zwracanego typu, gdyż nigdy nie zwraca wartości. Istnieje wiele typów konstruktorów:

- konstruktor domyślny (nie ma argumentów)
- konstruktor z parametrami (argumenty są przekazywane do konstruktora)
- konstruktor kopiujący (kopiuje wartości z innego obiektu)
- konstruktor przenoszący (kopiuje wartości z innego obiektu i ustawia pola innego obiektu na domyślne wartości)

```C++
class Prostokat {
  int a;
  int b;

public:
  // konstruktor domyślny
  Prostokat() {
    a = 1;
    b = 1;
  }

  // konstruktor z parametrem
  Prostokat(int a, int b) {
    this->a = a;
    this->b = b;
  }

  // konstruktor kopiujący
  Prostokat(const Prostokat &p) {
    a = p.a;
    b = p.b;
  }

  // konstruktor przenoszący
  Prostokat(Prostokat &&p) {
    a = p.a;
    b = p.b;
    p.a = 1;
    p.b = 1;
  }
};
```

### Destruktor

Destruktor jest funkcją, która jest wywoływana przy usuwaniu obiektu. Destruktor ma taką samą nazwę jak klasa i nie posiada zwracanego typu, gdyż nigdy nie zwraca wartości.

```C++
class Prostokat {
  int a;
  int b;

public:
  Prostokat(int a, int b) {
    this->a = a;
    this->b = b;
  }

  ~Prostokat() { std::cout << "Destruktor" << std::endl; }
};
```

### Dostępność pól oraz metod

Istnieją trzy poziomy dostępu do pól oraz metod:

    - public
    - protected
    - private

Do pól i metod zdefiniowanych w sekcji <code>public</code> dostęp jest zawsze możliwy. Możemy się do nich odwołać z poziomu klasy, jak i z poziomu obiektu. W przypadku pól i metod zdefiniowanych w sekcji <code>private</code> dostęp jest możliwy tylko z poziomu klasy. Sekcja <code>protected</code> ma znaczenie przy dziedziczeniu. Klasy pochodne mają dostęp do pól i metod zdefiniowanych w sekcji <code>protected</code>, podobnie jak tych zdefiniowanych w sekcji <code>public</code>, ale nie mają dostępu do pól i metod zdefiniowanych w sekcji <code>private</code>.

```C++
class Prostokat {
  int a;
  int b;

public:
  Prostokat(int a, int b) {
    this->a = a;
    this->b = b;
  }

  int pole() { return a * b; }
};

int main() {

  Prostokat prostokat(2, 3);
  auto pole = prostokat.pole(); // Ok. Mamy dostęp do pól publicznych.
  auto a = prostokat.a;         // Źle. Nie mamy dostępu do pól prywatnych.

  return 0;
}
```


### Wskaźnik na obiekt

Podobnie jak tworzyliśmy wskaźniki na typy wbudowane, możemy tworzyć wskaźniki na obiekty. Do pól obiektu, na który wskazuje wskaźnik, możemy się odwoływać za pomocą konstrukcji <code>*wsk.pole</code> lub <code>wsk->pole</code>.

```C++
#include <iostream>

class Foo {
  int bar;

public:
  Foo() { bar = 0; }

  void setBar(int bar) { this->bar = bar; }

  int getBar() { return bar; }
};

int main() {
  Foo foo;
  Foo *wsk = &foo;
  wsk->setBar(10);
  std::cout << wsk->getBar() << std::endl;
  return 0;
}
```

### Przeciążanie operatorów

C++ daje nam możliwość definiowania nowego znaczenia różnych operatorów dla definiowanych przez nas klas. W naszym przykładzie, definiujemy operator <code>+</code> dla klasy <code>Prostokąt</code>.

    operator + (Prostokąt &p1, Prostokąt &p2) {
      return Prostokąt(p1.a + p2.a, p1.b + p2.b);
    }
    operator + (Prostokąt &p1, int a) {
      return Prostokąt(p1.a + a, p1.b + a);
    }
    operator + (int a, Prostokąt &p1) {
      return Prostokąt(a + p1.a, a + p1.b);
    }

### Pola i metody statyczne

Istnieje specjalny typ pól oraz metod definiowanych w obrębie klasy, są to pola i metody statyczne. Tworzymy je umieszczając przed typem danej zmiennej lub przed typem zwracanym przez funkcję słowo kluczowe <code>static</code>. Do pól statycznych możemy się odwoływać za pomocą konstrukcji <code>*klasa::pole</code> lub <code>klasa::pole</code>. Nie wymagają one utworzenia obiektu klasy. Wartości pól statycznych są współdzielone przez wszystkie obiekty klasy.

```C++
#include <iostream>

class Prostokąt {
  static unsigned int liczbaProstokątów;

public:
  Prostokąt() { liczbaProstokątów++; }

  static int getLiczbaProstokątów() { return liczbaProstokątów; }
};

unsigned int Prostokąt::liczbaProstokątów = 0;

int main() {

  for (int i = 0; i < 10; i++) {
    Prostokąt prostokąt;
  }

  std::cout << Prostokąt::getLiczbaProstokątów() << std::endl; // 10
  return 0;
}
```

### Funkcje zaprzyjaźnione

Istnieje specjalna klasa funkcji, tak zwane funkcje zaprzyjaźnione. Są to zewnętrzne funkcje, które mają dostęp do prywatnych pól i metod klasy. Przykład dla klasy <code>Prostokąt</code>:

    friend void swap(Prostokąt &p1, Prostokąt &p2) {
      p1.a = p2.a;
      p1.b = p2.b;
    }

### Struktury

Struktura jest protoplastą klasy. W C struktury pozwalają na łączenie pod jedną nazwą danych różnego typu. W C nie ma jednak możliwości definiowania funkcji w obrębie struktury. C++ zmienia znaczenie tego pojęcia. W C++ struktury i klasy są dokładnie tym samym, z wyjątkiem tego, że domyślnie wszystkie pola struktur są publiczne, a pola klas prywatne (mamy więc możliwość definiowania metod).

Przykład w C:

```C
struct Foo {
  int bar;
};

int main() {
  struct Foo foo;
  foo.bar = 10;
  return 0;
}
```

W C nazwy struktur żyją we własnej przestrzeni nazw. Zmienną tego typu tworzymy, podając jako jej typ słowo kluczowe <code>struct</code>, nazwę struktury oraz nazwę zmiennej.

```C
struct Foo obiekt_foo;
```

W C++ możemy dalej używać tej składni, ale nie jest to konieczne. Możemy po prostu napisać:

```c++
Foo obiekt_foo;
```

### Pole bitowe

Możemy wskazać dokładną liczbę bitów, które chcemy zarezerwować dla danego pola struktury.

```c++
#include <iostream>

struct Data {
  unsigned int Rok : 13;    // 2^13 = 8192
  unsigned int Miesiac : 4; // 2^4 = 16
  unsigned int Dzien : 5;   // 2^5 = 32
};

void wypiszDate(Data d) {
  std::cout << "Mamy dziś: " << std::endl;
  std::cout << d.Dzien << "-" << d.Miesiac << "-" << d.Rok << std::endl;
}

int main() {
  Data d;
  d.Rok = 2020;
  d.Miesiac = 7;
  d.Dzien = 18;

  wypiszDate(d);

  return 0;
}
```

### Unie

Unie to inny sposób reprezentacji danych w pamięci.

```c++
#include <iostream>

union Przyklad {
  int a;
  int b;
};

int main() {
  Przyklad unia;
  unia.a = 10;
  unia.b = 20;

  std::cout << unia.a << std::endl; // 20
  std::cout << unia.b << std::endl; // 20

  return 0;
}
```

Mogłoby się wydawać, że unie są tym samym co struktury. Różnica polega na tym, że w danej chwili tylko jedno pole unii może przechowywać wartość. Z tego powodu Unie są lżejsze od struktur i unia zajmuje w pamięci tyle miejsca, ile wynosi rozmiar największego z jej pól.
