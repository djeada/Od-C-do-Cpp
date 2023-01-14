## Programowanie Obiektowe

Programowanie obiektowe polega na pisaniu programów, w których różne elementy programu, takie jak dane oraz funkcje, zostają zorganizowane w formie obiektów.

1. Klasa jest szablonem, w którym definiujemy pola (dane przechowywane przez obiekt) oraz metody (funkcje, które operują na polach). Na przykład, klasa Prostokat mogłaby mieć pola a i b (wymiary prostokątu) oraz metodę pole(), która zwraca pole tego prostokątu.

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

2. Obiekty to instancje klasy w programie. Przykład użycia powyższej klasy:

```C++
Prostokat p(3,4); // Tworzymy obiekt klasy Prostokat
std::cout << p.pole() << std::endl; // Wypisujemy pole tego prostokątu
```

Dlaczego warto korzystać z programowania obiektowego?

* Modularność: każda klasa ma jasno określony cel i wszystko, co z nią jest związane, jest zamknięte w tej klasie. Dzięki temu, łatwiej jest zrozumieć i utrzymać kod.
* Łatwość wielokrotnego użytku: możemy tworzyć (teoretycznie) nieskończoną ilość obiektów danej klasy, co pozwala na rozwiązanie różnych problemów.

### Konstruktor

Konstruktor jest funkcją, która jest wywoływana przy tworzeniu obiektu. Konstruktor ma taką samą nazwę jak klasa i nie posiada zwracanego typu, gdyż nigdy nie zwraca wartości. Istnieje kilka rodzajów konstruktorów:

* konstruktor domyślny (nie przyjmuje żadnych argumentów)
* konstruktor z parametami (przyjmuje argumenty, które służą do inicjalizacji pól obiektu)
* konstruktor kopiujący (tworzy nowy obiekt na podstawie istniejącego)
* konstruktor przenoszący (tworzy nowy obiekt na podstawie istniejącego, a następnie ustawia pola istniejącego obiektu na domyślne wartości)

Przykład użycia różnych typów konstruktorów dla klasy Prostokat:

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
    p.a = 0;
    p.b = 0;
  }
};
```

W przykładzie powyżej, tworzenie nowego obiektu klasy Prostokat bez podawania żadnych argumentów wywoła konstruktor domyślny, który ustawi pola `a` i `b` na 1. Tworzenie obiektu z podaniem dwóch argumentów wywoła konstruktor z parametrami, który ustawi pola `a` i `b` na podane wartości. Kopiowanie obiektu wywoła konstruktor kopiujący, a przenoszenie obiektu wywoła konstruktor przenoszący.

### Destruktor

Destruktor jest specjalnym typem metody, która jest wywoływana, gdy obiekt jest usuwany z pamięci. Jego nazwa jest taka sama jak nazwa klasy, ale poprzedzona znakiem `~`. Podobnie jak konstruktor, destruktor nie posiada zwracanego typu.

Destruktor jest przydatny w sytuacjach, gdy chcemy zwolnić zasoby zajmowane przez obiekt, takie jak pamięć czy otwarte pliki. Możemy też użyć destruktora do wywołania innych metod, które służą do kończenia działania obiektu.

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

* `public`: dostęp do pól i metod zdefiniowanych jako public jest zawsze możliwy, zarówno z poziomu klasy, jak i z poziomu obiektu.
* `private`: dostęp do pól i metod zdefiniowanych jako private jest możliwy tylko z poziomu klasy.
* `protected`: dostęp do pól i metod zdefiniowanych jako protected jest możliwy tylko dla klas pochodnych.

Poziom dostępu jest definiowany przy deklaracji pola lub metody. Domyślnie, pola i metody są prywatne.

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
  // auto a = prostokat.a;         // Źle. Nie mamy dostępu do pól prywatnych.

  return 0;
}
```

### Wskaźnik na obiekt

Podobnie jak tworzyliśmy wskaźniki na typy wbudowane, możemy tworzyć wskaźniki na obiekty. Do pól obiektu, na który wskazuje wskaźnik, możemy się odwoływać za pomocą konstrukcji `*wsk.pole` lub `wsk->pole`.

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

W powyższym przykładzie, tworzymy obiekt klasy `Foo` i przypisujemy adres tego obiektu do wskaźnika wsk. Następnie, wykorzystując operator `->`, ustawiamy wartość pola `ba`r na 10 oraz pobieramy jego wartość za pomocą metody `getBar()`.

Wskaźnik na obiekt jest przydatny w wielu sytuacjach, takich jak przekazywanie obiektów do funkcji jako argumentów, tworzenie tablic wskaźników na obiekty itp.

### Przeciążanie operatorów

C++ daje nam możliwość definiowania nowego znaczenia różnych operatorów dla definiowanych przez nas klas. W naszym przykładzie, definiujemy operator `+` dla klasy `Prostokat`.

```C++
class Prostokat {
  int a;
  int b;
  public:
  Prostokat(int a, int b) {
    this->a = a;
    this->b = b;
  }
  Prostokat operator + (Prostokat &p1) {
    return Prostokat(a + p1.a, b + p1.b);
  }
};
```

W powyższym przykładzie, operator `+` został zdefiniowany jako metoda składowa klasy `Prostokat`, która przyjmuje jako argument obiekt klasy `Prostokat` i zwraca obiekt klasy `Prostokat`, którego pola `a` oraz `b` są sumą odpowiadających pól obiektów. Dzięki temu, możemy stosować operator `+` dla obiektów klasy `Prostokat` tak jak roblibyśmy to ze zwykłymi liczbami.

```C++
Prostokat p1(2,3);
Prostokat p2(4,5);
Prostokat p3 = p1+p2; 
```

### Pola i metody statyczne

Istnieje specjalny typ pól oraz metod definiowanych w obrębie klasy, są to pola i metody statyczne. Tworzymy je umieszczając przed typem danej zmiennej lub przed typem zwracanym przez funkcję słowo kluczowe `static`. Do pól statycznych możemy się odwoływać za pomocą konstrukcji `*klasa::pole` lub `klasa::pole`. Nie wymagają one utworzenia obiektu klasy. Wartości pól statycznych są współdzielone przez wszystkie obiekty klasy.

```C++
class Prostokat {
  static int liczbaProstokatow;
  public:
  Prostokat() { liczbaProstokatow++; }
  static int getLiczbaProstokatow() { return liczbaProstokatow; }
};
int Prostokat::liczbaProstokatow = 0;
int main() {
  Prostokat p1;
  Prostokat p2;
  Prostokat p3;
  cout<<Prostokat::getLiczbaProstokatow()<<endl; //3
  return 0;
}
```

Jak widzimy, pole `liczbaProstokatow` jest współdzielone przez wszystkie obiekty klasy `Prostokat`.

### Funkcje zaprzyjaźnione

Funkcje zaprzyjaźnione są to zewnętrzne funkcje, które mają dostęp do prywatnych pól i metod klasy. Przykład dla klasy `Prostokat`:

```C++
class Prostokat {
  int a;
  int b;
  public:
  Prostokat(int a, int b) {
    this->a = a;
    this->b = b;
  }
  friend void swap(Prostokat &p1, Prostokat &p2) {
    int tmp = p1.a;
    p1.a = p2.a;
    p2.a = tmp;
    tmp = p1.b;
    p1.b = p2.b;
    p2.b = tmp;
  }
};

int main() {
  Prostokat p1(1, 2);
  Prostokat p2(3, 4);
  swap(p1, p2);
  cout<<p1.a<<" "<<p1.b<<endl; // 3 4
  cout<<p2.a<<" "<<p2.b<<endl; // 1 2
  return 0;
}
```

Dzięki funkcji zaprzyjaźnionej `swap`, która ma dostęp do prywatnych pól klasy `Prostokat`, możemy zamienić wartości pól dwóch obiektów.

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

### Unie

Unie to inny sposób reprezentacji danych w pamięci. Unie pozwalają na przechowywanie różnych typów danych w tym samym bloku pamięci. W przeciwieństwie do struktur, w uniach w danej chwili tylko jedno pole unii może przechowywać wartość. Z tego powodu unie są lżejsze od struktur i unia zajmuje w pamięci tyle miejsca, ile wynosi rozmiar największego z jej pól.

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

W powyższym przykładzie tworzona jest unia o nazwie "Przyklad", która posiada dwa pola "a" i "b" typu int. W mainie następuje przypisanie wartości 10 do pola "a" oraz wartości 20 do pola "b". Następnie wypisywane są wartości obu pól, jednak obie wartości są równe 20, ponieważ unia ma tylko jedno pole aktywne w danej chwili, a przypisanie do pola "b" nadpisuje wartość pola "a".

Unie mogą być używane w sytuacjach, gdy potrzebujemy oszczędzić miejsce w pamięci, a także gdy potrzebujemy dostępu do danych za pomocą różnych typów. Przykładami zastosowania unii mogą być:

* Interpretacja bajtów w pamięci jako różnego typu danych (np. liczby całkowitej, znaków, itp.)
* Przechowywanie danych o różnym typie w tablicy bez konieczności tworzenia kilku tablic
* Przechowywanie danych o różnym typie w strukturze bez konieczności tworzenia kilku pol różnego typu.
    
### Pole bitowe

Pola bitowe pozwalają na zdefiniowanie dokładnej liczby bitów, które chcemy zarezerwować dla danego pola struktury lub unii. Możemy to zrobić poprzez użycie operatora : po nazwie pola oraz podanie liczby bitów. W przykładzie poniżej, pole `Rok` zajmuje 13 bitów, pole `Miesiac` 4 bity, a pole `Dzien` 5 bitów.

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
