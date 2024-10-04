# Programowanie Obiektowe

Programowanie obiektowe to paradygmat programowania, w którym skomplikowane problemy są dzielone na mniejsze części poprzez definiowanie obiektów. Każdy obiekt reprezentuje jakąś część problemu i zawiera dane oraz funkcje, które na nich operują. Oto kilka kluczowych pojęć związanych z programowaniem obiektowym:

## Klasy i Obiekty

- **Klasa** jest definicją obiektu, pełniąc rolę "szablonu", który określa, jakie dane (pola) oraz operacje (metody) będą dostępne dla obiektu, co pozwala na tworzenie struktur danych i logiki działania.
- **Obiekt** to instancja klasy, czyli konkretna realizacja klasy, która posiada własne egzemplarze pól oraz dostęp do metod zdefiniowanych w klasie.

Dla zobrazowania, załóżmy, że chcemy modelować prostokąt:

```C++
class Prostokat {
private:
  int a;
  int b;

public:
  Prostokat(int a, int b) : a(a), b(b) {}

  int pole() const { return a * b; }
};
```

Tworzenie i korzystanie z obiektu:

```C++
Prostokat p(3,4);
std::cout << p.pole() << std::endl;
```

### Dlaczego warto korzystać z programowania obiektowego?

- **Modularność** pozwala na lepsze zarządzanie skomplikowanymi programami, poprzez podział ich na mniejsze, dobrze zdefiniowane moduły, co ułatwia ich rozwój i utrzymanie.
- **Wielokrotnego użytku** oznacza, że dobrze zaprojektowana klasa może być wykorzystywana wielokrotnie w różnych częściach kodu lub nawet w innych projektach, co zwiększa efektywność pracy programisty.
- **Abstrakcja** w programowaniu obiektowym umożliwia ukrycie skomplikowanych szczegółów implementacyjnych, jednocześnie oferując prosty i jasny interfejs do korzystania z obiektu, co ułatwia jego obsługę.
   
###  Konstruktory
Konstruktor to specjalna funkcja klasy, która jest automatycznie wywoływana podczas tworzenia obiektu. Istnieje kilka rodzajów konstruktorów:

- Konstruktor **domyślny** nie przyjmuje żadnych argumentów i zazwyczaj inicjalizuje obiekt z wartościami domyślnymi dla jego pól.
- Konstruktor **z parametrami** przyjmuje argumenty, które są wykorzystywane do inicjalizacji pól obiektu, co pozwala na dostosowanie wartości już w momencie tworzenia instancji.
- Konstruktor **kopiujący** tworzy nowy obiekt jako dokładną kopię innego obiektu tej samej klasy, co pozwala na duplikowanie obiektów.
- Konstruktor **przenoszący** przyjmuje obiekt jako argument i "przenosi" jego dane do nowego obiektu, co jest bardziej efektywne niż kopiowanie, szczególnie w przypadku zasobów dynamicznych.

Przykład różnych konstruktorów:

```C++
class Prostokat {
private:
  int a;
  int b;

public:
  Prostokat() : a(1), b(1) {} 

  Prostokat(int a, int b) : a(a), b(b) {}

  Prostokat(const Prostokat &p) : a(p.a), b(p.b) {}

  Prostokat(Prostokat &&p) : a(p.a), b(p.b) {
    p.a = 0;
    p.b = 0;
  }
};
```

### Destruktor

Destruktor to specjalna metoda klasy, która jest automatycznie wywoływana, gdy obiekt jest usuwany z pamięci. Jego głównym zadaniem jest zwolnienie zasobów zajmowanych przez obiekt i wykonanie wszelkich niezbędnych operacji przed usunięciem obiektu.

Nazwa destruktora jest taka sama jak nazwa klasy, ale poprzedzona znakiem ~. Destruktor nie przyjmuje argumentów i nie zwraca wartości.

```C++
class Prostokat {
private:
  int a;
  int b;

public:
  Prostokat(int a, int b) : a(a), b(b) {}

  ~Prostokat() { std::cout << "Destruktor wywołany" << std::endl; }
};
```

### Poziomy dostępu w klasie

Klasy w C++ mają trzy podstawowe poziomy dostępu do swoich składników (pól i metod):

| Modyfikator | Opis                                                                                          |
|-------------|------------------------------------------------------------------------------------------------------|
| `public`    | Składniki deklarowane jako publiczne są dostępne zarówno z wewnątrz klasy, jak i z zewnątrz. To jest najbardziej otwarty poziom dostępu. |
| `private`   | Składniki deklarowane jako prywatne są dostępne tylko wewnątrz klasy. Jest to sposób na ukrycie wewnętrznych danych i operacji klasy przed światem zewnętrznym. |
| `protected` | Składniki deklarowane jako chronione są dostępne wewnątrz klasy oraz dla klas pochodnych (dziedziczenie). |

Warto zaznaczyć, że jeśli nie określimy poziomu dostępu, domyślnie składniki klasy są prywatne.

```C++
class Prostokat {
private:
  int a;
  int b;

public:
  Prostokat(int a, int b) : a(a), b(b) {}

  int pole() const { return a * b; }
};

int main() {

  Prostokat prostokat(2, 3);
  auto pole = prostokat.pole(); // Działa, ponieważ metoda `pole` jest publiczna.
  // auto a = prostokat.a;         // Błąd! Nie mamy dostępu do pól prywatnych.

  return 0;
}
```

### Wskaźnik na obiekt

Wskaźniki na obiekty działają podobnie jak wskaźniki na zwykłe typy danych. Dzięki nim można dynamicznie alokować pamięć na obiekty, odwoływać się do obiektów czy przekazywać obiekty do funkcji. Aby odwołać się do składników obiektu poprzez wskaźnik, używamy operatora `->`.

```C++
#include <iostream>

class Foo {
private:
  int bar;

public:
  Foo() : bar(0) {}

  void setBar(int value) { bar = value; }
  int getBar() const { return bar; }
};

int main() {
  Foo fooInstance;
  Foo *fooPointer = &fooInstance;
  
  fooPointer->setBar(10);
  std::cout << fooPointer->getBar() << std::endl;

  return 0;
}
```

W powyższym kodzie, wskaźnik fooPointer wskazuje na obiekt fooInstance klasy Foo. Dzięki temu możemy manipulować danymi fooInstance za pomocą wskaźnika.

### Przeciążanie operatorów

Przeciążanie operatorów pozwala nadawać operatorom nowe znaczenie w kontekście naszych klas, co czyni język bardziej ekspresyjnym i zwięzłym.

Przykładem może być przeciążenie operatora + dla klasy Prostokat:

```C++
class Prostokat {
private:
  int a;
  int b;

public:
  Prostokat(int width, int height) : a(width), b(height) {}

  Prostokat operator + (const Prostokat &other) const {
    return Prostokat(a + other.a, b + other.b);
  }
  
  void display() const {
    std::cout << "Prostokat(" << a << ", " << b << ")" << std::endl;
  }
};

int main() {
  Prostokat rect1(2, 3);
  Prostokat rect2(4, 5);
  
  Prostokat rectSum = rect1 + rect2;
  rectSum.display();  // Wyświetla: Prostokat(6, 8)

  return 0;
}
```

W powyższym kodzie, operator + został przeciążony w taki sposób, aby mógł dodawać dwa obiekty klasy Prostokat. W wyniku tej operacji tworzony jest nowy obiekt klasy Prostokat o wymiarach będących sumą wymiarów dodawanych obiektów.

### Pola i metody statyczne

Pola i metody statyczne są elementami klasy, które są niezależne od konkretnych instancji tej klasy. Dzięki nim możliwe jest przechowywanie danych czy wykonywanie działań, które dotyczą całej klasy, a nie tylko pojedynczego obiektu. Do odwołania się do pól i metod statycznych, nie trzeba tworzyć instancji klasy - można korzystać z nich poprzez nazwę klasy.

```C++
#include <iostream>

class Prostokat {
private:
  static int liczbaProstokatow;

public:
  Prostokat() { liczbaProstokatow++; }
  ~Prostokat() { liczbaProstokatow--; }

  static int getLiczbaProstokatow() { return liczbaProstokatow; }
};

int Prostokat::liczbaProstokatow = 0;

int main() {
  {
    Prostokat p1;
    Prostokat p2;
    Prostokat p3;
    std::cout << Prostokat::getLiczbaProstokatow() << std::endl; // 3
  }
  std::cout << Prostokat::getLiczbaProstokatow() << std::endl; // 0
  return 0;
}
```

Za każdym razem, gdy tworzony jest obiekt klasy Prostokat, pole liczbaProstokatow jest zwiększane. Dzięki destruktorowi jest ono również dekrementowane przy usuwaniu obiektu.

### Funkcje zaprzyjaźnione

Funkcje zaprzyjaźnione umożliwiają pewnym zewnętrznym funkcjom dostęp do prywatnych składników klasy. Są to funkcje, które nie są metodami tej klasy, ale zostały przez nią upoważnione do dostępu do jej wewnętrznych składników.

```C++
#include <iostream>

class Prostokat {
private:
  int a;
  int b;

public:
  Prostokat(int width, int height) : a(width), b(height) {}

  // Funkcja zaprzyjaźniona
  friend void swap(Prostokat &p1, Prostokat &p2);
};

void swap(Prostokat &p1, Prostokat &p2) {
  std::swap(p1.a, p2.a);
  std::swap(p1.b, p2.b);
}

int main() {
  Prostokat p1(1, 2);
  Prostokat p2(3, 4);
  swap(p1, p2);
  // Aby pokazać wynik, musielibyśmy dodać metody dostępowe lub kolejne funkcje zaprzyjaźnione.
  return 0;
}
```

Dzięki funkcji swap, która jest funkcją zaprzyjaźnioną z klasą Prostokat, możliwe jest zamienienie wartości pól a i b dwóch różnych obiektów klasy Prostokat.

### Struktury

Struktura w języku C służy głównie do grupowania zmiennych różnych typów w jednym bloku. W C++, struktura funkcjonuje niemalże identycznie jak klasa, z tym że domyślnie wszystkie jej składniki są publiczne, podczas gdy w klasie są one prywatne.

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

W C++, poza tradycyjnym tworzeniem struktury poprzez struct Foo obiekt_foo;, można również korzystać z bardziej zwięzłej notacji:

```c++
Foo obiekt_foo;
```

### Unie

Unie to specjalny typ danych, który pozwala na przechowywanie różnych typów danych w jednym miejscu pamięci. Dzięki uniom, można oszczędzić miejsce w pamięci, ale ważne jest, aby pamiętać, że w danej chwili tylko jeden składnik unii może zawierać wartość.

Przykład:

```c++
#include <iostream>

union Przyklad {
  int a;
  float b;
};

int main() {
  Przyklad unia;
  unia.a = 10;
  std::cout << unia.a << std::endl; // 10

  unia.b = 3.14;
  std::cout << unia.b << std::endl; // 3.14
  // unia.a jest teraz niezdefiniowana

  return 0;
}
```

W powyższym przykładzie, wartość unia.b nadpisuje wartość unia.a, więc po przypisaniu wartości do unia.b, wartość unia.a staje się nieokreślona.

### Pole bitowe

Pola bitowe to bardzo przydatne narzędzie, które pozwala oszczędzić miejsce w pamięci poprzez precyzyjne określenie liczby bitów przeznaczonych na przechowywanie wartości danego pola.

Przykład:

```c++
#include <iostream>

struct Data {
  unsigned int Rok : 13;    // Zakres: 0-8191
  unsigned int Miesiac : 4; // Zakres: 0-15
  unsigned int Dzien : 5;   // Zakres: 0-31
};

void wypiszDate(const Data& d) {
  std::cout << "Mamy dziś: " << d.Dzien << "-" << d.Miesiac << "-" << d.Rok << std::endl;
}

int main() {
  Data d;
  d.Rok = 2023;
  d.Miesiac = 8;
  d.Dzien = 17;

  wypiszDate(d);

  return 0;
}
```

W powyższym kodzie, pole Rok zajmuje 13 bitów, co pozwala na przechowywanie wartości w zakresie od 0 do 8191. Analogicznie, pola Miesiac i Dzien mają odpowiednio 4 i 5 bitów, co pozwala na przechowywanie wartości w zakresach od 0 do 15 oraz od 0 do 31.
