## Programowanie Obiektowe 

Programowanie obiektowe (ang. **Object-Oriented Programming**, OOP) to obecnie jeden z najważniejszych i najpowszechniej stosowanych paradygmatów w inżynierii oprogramowania. Jego główne założenie polega na tym, aby w procesie tworzenia oprogramowania dzielić skomplikowane problemy na mniejsze, łatwiejsze do zrozumienia fragmenty, które reprezentujemy w postaci **obiektów**. Takie podejście prowadzi do tworzenia bardziej modularnych, czytelnych i łatwiejszych w utrzymaniu aplikacji, zwłaszcza w dużych projektach programistycznych. 

W języku C++ idea obiektowości jest mocno zakorzeniona; klasa czy obiekt to pojęcia pierwszoplanowe. Dzięki temu możliwe jest wykorzystanie takich mechanizmów jak dziedziczenie, polimorfizm czy enkapsulacja, co z kolei pozwala na efektywną organizację kodu. W niniejszych notatkach omówimy fundamentalne aspekty programowania obiektowego w C++ – od klas, obiektów i konstruktorów, przez destruktory, poziomy dostępu, aż po wskaźniki na obiekty i mechanizmy takie jak **przeciążanie operatorów**, **pola statyczne**, **funkcje zaprzyjaźnione**, **struktury**, **unie** i **pola bitowe**.  

Dzięki temu zestawowi informacji będziesz w stanie zrozumieć, jak poprawnie definiować klasy i obiekty w C++, jak zarządzać ich cyklem życia (tworzenie i usuwanie), oraz jakie są zasady rządzące dostępem do prywatnych (i chronionych) składników. Dodatkowo przekonasz się, jak można nadawać operatorom nowe znaczenia, jakie korzyści daje stosowanie pól i metod statycznych, a także kiedy warto sięgnąć po struktury, unie i pola bitowe.

### Klasy i Obiekty

**Klasa** to szablon definiujący strukturę i zachowanie obiektów, czyli zbiór pól (przechowujących dane) oraz metod (zapewniających zestaw operacji na tych danych). **Obiekt** to konkretny egzemplarz (instancja) klasy, posiadający własny stan, zależny od wartości pól. W C++ deklarację klasy rozpoczynamy słowem kluczowym `class` wraz z nazwą klasy, po której następują sekcje określające modyfikatory dostępu (`public`, `private`, `protected`) i odpowiadające im pola oraz metody.

**Przykład prostej klasy**

Poniższy przykład prezentuje klasę `Prostokat`, która posiada dwa pola (długości boków `a` i `b`), a także metodę `pole()` służącą do wyliczania pola prostokąta:

```cpp
class Prostokat {
private:
  int a;
  int b;

public:

  Prostokat(int a, int b) : a(a), b(b) {}

  int pole() const { 
    return a * b; 

  }

};
```

Możemy następnie tworzyć obiekty tej klasy i korzystać z metod, np.:

```cpp
Prostokat p(3, 4);
std::cout << p.pole() << std::endl; // Wyświetli: 12
```

**Zalety** tworzenia klas i obiektów:

- Kod staje się **bardziej zorganizowany** – różne elementy aplikacji mają swoje odpowiedzialności.
- Umożliwia tworzenie **wielu obiektów** na podstawie jednego projektu (klasy), przy czym każdy obiekt może mieć własny, unikalny stan.
- Zapewnia duże możliwości rozbudowy i modyfikacji kodu bez naruszania innych jego części.

### Dlaczego Programowanie Obiektowe?

Programowanie obiektowe wyróżnia się spośród innych paradygmatów (np. proceduralnego, funkcyjnego) przede wszystkim koncentracją na **modelowaniu rzeczywistości** za pomocą obiektów odzwierciedlających elementy świata lub abstrakcyjne koncepty. Do najważniejszych zalet należą:

1. **Enkapsulacja** (ang. *encapsulation*) – łączenie danych i metod w klasach oraz ukrywanie informacji wewnątrz obiektów. Zapobiega to bezpośredniej manipulacji stanem obiektu przez zewnętrzny kod, co ułatwia zachowanie spójności danych.
2. **Reużywalność kodu** (ang. *reusability*) – raz zdefiniowana klasa może być wykorzystywana w różnych częściach projektu, a także w innych projektach. Sprzyja to oszczędności czasu i nakładu pracy.
3. **Modularność** – rozbijanie problemu na mniejsze, bardziej zrozumiałe elementy. Każda klasa odpowiada za precyzyjnie zdefiniowaną część funkcjonalności.
4. **Polimorfizm** – możliwość tworzenia interfejsów, które są implementowane w różny sposób przez różne klasy pochodne. Ułatwia to rozbudowę i modyfikację istniejącego kodu.
5. **Dziedziczenie** – tworzenie nowych klas na bazie już istniejących, przy zachowaniu i możliwościach rozszerzania ich funkcjonalności. Sprzyja hierarchizacji i ponownemu wykorzystaniu wspólnych fragmentów.

### Konstruktory

Konstruktory to specjalne metody wywoływane **automatycznie** w chwili tworzenia nowego obiektu klasy. Odpowiadają za **inicjalizację** pól i przygotowanie obiektu do użycia. Wyróżniamy kilka rodzajów konstruktorów:

- **Konstruktor domyślny** – nie przyjmuje argumentów; tworzy obiekt z założonymi wartościami początkowymi.
- **Konstruktor z parametrami** – pozwala przekazać wartości początkowe dla pól. 
- **Konstruktor kopiujący** – tworzy nowy obiekt będący kopią już istniejącego obiektu tej samej klasy.
- **Konstruktor przenoszący** – optymalizuje proces tworzenia obiektu z innego, tymczasowego obiektu, zwłaszcza gdy obiekt zarządza **zasobami dynamicznymi** (np. dużą tablicą w pamięci).

**Przykład klas z różnymi konstruktorami**

```cpp
class Prostokat {
private:
  int a;
  int b;

public:

  // Konstruktor domyślny

  Prostokat() : a(1), b(1) {} 

  // Konstruktor z parametrami

  Prostokat(int a, int b) : a(a), b(b) {}

  // Konstruktor kopiujący

  Prostokat(const Prostokat &p) : a(p.a), b(p.b) {}

  // Konstruktor przenoszący

  Prostokat(Prostokat &&p) : a(p.a), b(p.b) {
    p.a = 0;
    p.b = 0;

  }

};
```

W powyższym przykładzie pokazano wszystkie cztery rodzaje konstruktorów. Dzięki nim możemy tworzyć obiekty zarówno z domyślnymi wartościami (np. `(1,1)`), jak i z wartościami przekazanymi podczas tworzenia, a także kopiować i przenosić obiekty w bardziej zaawansowanych scenariuszach.

### Destruktor

Destruktor to specjalna metoda klasy, wywoływana **automatycznie** w momencie niszczenia obiektu, np. gdy wychodzi on poza zakres widoczności lub gdy używamy operatora `delete`. Jej nazwa pokrywa się z nazwą klasy, ale jest poprzedzona znakiem `~` (tylda). Głównym zadaniem destruktora jest **zwalnianie zasobów** przydzielonych w trakcie życia obiektu oraz wykonywanie innych niezbędnych operacji porządkowych.

**Przykład użycia destruktora**

```cpp
class Prostokat {
private:
  int a;
  int b;

public:
  Prostokat(int a, int b) : a(a), b(b) {}

  ~Prostokat() { 
    std::cout << "Destruktor wywołany" << std::endl; 
  }
};

int main() {
  {
    Prostokat p(2,3);
    // W tym bloku p istnieje 
  }
  // Po zakończeniu bloku p zostaje zniszczony i wywołany destruktor
  return 0;
}
```

Gdy obiekt `p` zostanie zniszczony, na ekranie zostanie wyświetlony komunikat. W sytuacjach, kiedy klasa zarządza zasobami (np. pamięcią dynamicznie przydzieloną przez `new`), w destruktorze należy zadbać o ich prawidłowe zwolnienie.

### Poziomy Dostępu w Klasie

W C++ dostęp do członków klasy (pól i metod) regulują trzy modyfikatory:

I. **public**  

Składniki publiczne są dostępne dla wszystkich, również spoza klasy. Zazwyczaj deklarujemy tutaj metody, które tworzą zewnętrzny interfejs klasy (np. `pole()`).

II. **private**  

Składniki prywatne są dostępne wyłącznie dla metod wewnątrz tej samej klasy (oraz dla funkcji zaprzyjaźnionych). Używamy tego poziomu, by ukryć „wnętrzności” klasy przed kodem zewnętrznym.

III. **protected**  

Składniki chronione są widoczne w klasie bazowej i wszystkich klasach pochodnych (w dziedziczeniu), lecz nie są dostępne dla innych klas czy funkcji spoza hierarchii dziedziczenia.

Domyślnie, jeśli nie określimy modyfikatora, składniki klasy w C++ są **prywatne**. 

**Przykład ilustrujący poziomy dostępu**

```cpp
class Prostokat {
private:
  int a;
  int b;

public:

  Prostokat(int a, int b) : a(a), b(b) {}

  int pole() const { 
    return a * b; 

  }

};

int main() {

  Prostokat prostokat(2, 3);
  std::cout << prostokat.pole() << std::endl; // OK, metoda publiczna

  // std::cout << prostokat.a << std::endl;  // Błąd! 'a' jest prywatne
  return 0;

}
```

Powyższy przykład obrazuje, że do `pole()` mamy pełny dostęp, natomiast bezpośrednie odczytanie pola `a` jest niemożliwe spoza klasy.

### Wskaźnik na Obiekt

Wskaźniki (ang. *pointers*) to jeden z podstawowych elementów C++. Możemy za ich pomocą stworzyć wskaźnik na obiekt konkretnej klasy. Umożliwia to m.in. dynamiczne tworzenie obiektów w trakcie działania programu, przekazywanie obiektów do funkcji „po referencji” czy zarządzanie tablicami obiektów.

**Przykład wykorzystania wskaźnika**

```cpp
#include <iostream>

class Foo {
private:
  int bar;

public:
  Foo() : bar(0) {}

  void setBar(int value) { 
    bar = value; 
  }
  int getBar() const { 
    return bar; 
  }
};

int main() {
  Foo fooInstance;
  Foo* fooPointer = &fooInstance;  // wskaźnik na istniejący obiekt
  
  fooPointer->setBar(10);
  std::cout << fooPointer->getBar() << std::endl; // Wyświetli 10

  return 0;
}
```

W powyższym kodzie operator `->` pozwala wywołać metodę `setBar()` i odczytać wartość `getBar()` na obiekcie wskazywanym przez `fooPointer`. Wskaźniki pozwalają także na manualne zarządzanie pamięcią, np. przy użyciu operatora `new`.

### Przeciążanie Operatorów

Przeciążanie operatorów (ang. *operator overloading*) umożliwia zdefiniowanie, jak dany **operator** (np. `+`, `-`, `*`, `==`, `<<`, `()`, `[]`) powinien zachować się w kontekście obiektów naszej klasy. W efekcie możemy pisać kod bliższy naturalnej notacji matematycznej lub poprawiający czytelność.

**Przykład przeciążenia operatora `+`**

```cpp
class Prostokat {
private:
  int a;
  int b;

public:

  Prostokat(int width, int height) : a(width), b(height) {}

  // Przeciążenie operatora +

  Prostokat operator+(const Prostokat &other) const {
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
  rectSum.display();  // Wyświetli: Prostokat(6, 8)

  return 0;

}
```

Dzięki przeciążeniu operatora `+`, zapis `rect1 + rect2` staje się intuicyjny, a jednocześnie zwraca nowy obiekt o odpowiednio obliczonych wymiarach.

### Pola i Metody Statyczne

Pola i metody **statyczne** (ang. *static*) związane są z całą klasą, a nie z konkretnymi jej egzemplarzami. Oznacza to, że istnieje **jedna wspólna kopia** takiego pola dla wszystkich obiektów danej klasy. Metody statyczne mogą być wywoływane niezależnie od istnienia konkretnych instancji, używając składni `NazwaKlasy::nazwaMetody()`.

**Przykład pola statycznego liczącego obiekty**

```cpp
#include <iostream>

class Prostokat {
private:
  static int liczbaProstokatow; // Statyczne pole klasy

public:
  Prostokat() { 
    liczbaProstokatow++; 
  }
  ~Prostokat() { 
    liczbaProstokatow--; 
  }

  static int getLiczbaProstokatow() { 
    return liczbaProstokatow; 
  }
};

// Inicjalizacja pola statycznego
int Prostokat::liczbaProstokatow = 0;

int main() {
  {
    Prostokat p1;
    Prostokat p2;
    Prostokat p3;
    std::cout << "Aktualna liczba obiektów: "
              << Prostokat::getLiczbaProstokatow() << std::endl;  // 3
  }
  std::cout << "Aktualna liczba obiektów: "
            << Prostokat::getLiczbaProstokatow() << std::endl;    // 0

  return 0;
}
```

Dzięki polom statycznym możemy łatwo śledzić, ile obiektów danej klasy zostało stworzonych w danej chwili. W niektórych zastosowaniach (np. zarządzanie ograniczonymi zasobami) taka informacja może być kluczowa.

### Funkcje Zaprzyjaźnione

**Funkcje zaprzyjaźnione** (ang. *friend functions*) to funkcje lub całe klasy, którym dana klasa „ufa” na tyle, że zezwala im na dostęp do swoich **prywatnych** i **chronionych** pól i metod. Stosuje się je w sytuacjach, gdy dwie (lub więcej) struktur danych muszą bardzo ściśle ze sobą współpracować albo gdy potrzebna jest specjalna funkcja naruszająca normalne reguły enkapsulacji, ale nadal mająca uzasadnienie projektowe.

**Przykład funkcji zaprzyjaźnionej `swap`**

```cpp

#include <iostream>

class Prostokat {
private:
  int a;
  int b;

public:

  Prostokat(int width, int height) : a(width), b(height) {}

  // Deklaracja funkcji zaprzyjaźnionej
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

  // Aby potwierdzić zamianę, można by dodać metody getA() czy getB() i je wywołać
  return 0;

}
```

W powyższym kodzie funkcja `swap` może bezpośrednio modyfikować prywatne pola `a` i `b`, ponieważ klasa `Prostokat` zadeklarowała ją jako zaprzyjaźnioną. 

### Struktury

W C++ **struktura** (ang. *struct*) jest bardzo zbliżona do klasy. Kluczowa różnica polega na tym, że domyślny poziom dostępu w strukturze to **public**, a w klasie – **private**. Struktury, podobnie jak klasy, mogą zawierać zarówno pola, jak i metody czy konstruktory.

#### Struktury w stylu C  

W języku C, `struct` służyła głównie do grupowania danych. Przykład:

```c
struct Foo {
  int bar;
};

int main() {
  struct Foo foo;
  foo.bar = 10;
  return 0;
}
```

#### Struktury w C++  

W C++ struktura może wyglądać i zachowywać się niemal tak samo jak klasa:

```cpp
struct Foo {
  int bar;

  Foo(int val) : bar(val) {}
  void wyswietl() {
    std::cout << bar << std::endl;

  }

};

int main() {

  Foo obiekt_foo(10);
  obiekt_foo.wyswietl();  // Wyświetli 10
  return 0;

}
```

Z racji braku domyślnego `private`, struktury są często stosowane jako **agregaty danych** (tzn. publiczne „paczki” informacji), natomiast do bardziej zaawansowanego modelowania z reguły wybierane są klasy.

### Unie

**Unie** (ang. *unions*) to szczególny typ danych, w którym wszystkie pola współdzielą ten sam obszar pamięci. Przeznaczone są do sytuacji, w których w jednym miejscu przechowujemy kilka typów danych, ale w danym momencie aktywne jest tylko jedno z tych pól. Umożliwiają oszczędność pamięci, ale trzeba ostrożnie z nich korzystać, ponieważ zapis do jednego pola „nadpisuje” pamięć używaną przez pozostałe pola.

**Przykład unii**

```cpp
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

Po zapisaniu wartości do `unia.b` nie możemy liczyć na to, że `unia.a` będzie zachowywać dotychczasową wartość. Ten sam obszar pamięci służy aktualnie do przechowywania liczby zmiennoprzecinkowej.

### Pola Bitowe

**Pola bitowe** (ang. *bit fields*) to cecha języka C i C++, umożliwiająca zdefiniowanie w strukturze lub klasie pól zajmujących ściśle określoną liczbę bitów. Umożliwia to wydajniejsze wykorzystanie pamięci w sytuacjach, gdy pola mogą przyjmować jedynie ograniczony zakres wartości.

**Przykład pól bitowych**

```cpp

#include <iostream>

struct Data {
  unsigned int Rok : 13;    // Zakres: 0–8191
  unsigned int Miesiac : 4; // Zakres: 0–15
  unsigned int Dzien : 5;   // Zakres: 0–31

};

void wypiszDate(const Data& d) {
  std::cout << "Mamy dziś: " 

            << d.Dzien << "-" 

            << d.Miesiac << "-" 

            << d.Rok << std::endl;

}

int main() {

  Data d;
  d.Rok = 2023;
  d.Miesiac = 8;
  d.Dzien = 17;

  wypiszDate(d); // Wyświetli: Mamy dziś: 17-8-2023
  return 0;

}
```

Tutaj `Rok` zajmuje tylko 13 bitów, `Miesiac` – 4, a `Dzien` – 5, co w zupełności wystarcza, aby przechowywać rok z pewnego przedziału, miesiąc (1–12) i dzień (1–31). To rozwiązanie jest szczególnie przydatne w systemach wbudowanych lub w sytuacjach, w których liczy się każda jednostka pamięci.

