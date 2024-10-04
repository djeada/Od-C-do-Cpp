# Szablony

Szablony (ang. *templates*) stanowią fundament nowoczesnego programowania w języku C++. Umożliwiają one tworzenie kodu generycznego, który może działać z różnymi typami danych bez konieczności jego duplikacji. Szablony są kluczowym elementem metaprogramowania w C++, pozwalając na wykonywanie obliczeń na etapie kompilacji i optymalizację kodu wynikowego.

## Wprowadzenie do Szablonów

Szablony w C++ są mechanizmem pozwalającym na tworzenie funkcji, klas, a nawet zmiennych, które są parametryzowane typami lub wartościami stałymi. Dzięki temu możemy pisać kod, który jest niezależny od konkretnego typu danych, co zwiększa jego reużywalność i elastyczność.

### Szablony Funkcji

Szablony funkcji pozwalają na definiowanie funkcji, które działają na różnych typach danych. Ogólna składnia definicji szablonu funkcji jest następująca:

```cpp
template <parametry_szablonu>
typ_zwracany nazwa_funkcji(argumenty) {
    // ciało funkcji
}
```

**Przykład:** Definicja generycznej funkcji `max2`, która zwraca większą z dwóch wartości:

```cpp
template <typename T>
T max2(T arg1, T arg2) {
    return arg1 > arg2 ? arg1 : arg2;
}
```

**Wyjaśnienie:**

- `template <typename T>` deklaruje szablon z parametrem typu `T`.
- Funkcja `max2` przyjmuje dwa argumenty typu `T` i zwraca wartość typu `T`.
- Operator `?:` zwraca `arg1` lub `arg2` w zależności od wyniku porównania `arg1 > arg2`.

**Użycie funkcji szablonowej:**

```cpp
int a = max2<int>(10, 20);            // Wynik: 20
double b = max2<double>(16.2, 3.14);  // Wynik: 16.2
char c = max2<char>('a', 'b');        // Wynik: 'b'
```

### Mechanizm Instancjacji

Podczas kompilacji, gdy funkcja szablonowa jest wywoływana z konkretnym typem, kompilator tworzy jej **instancję** dla tego typu. Proces ten nazywany jest **instancjacją szablonu**. Dzięki temu generowany kod jest zoptymalizowany pod kątem użytych typów, eliminując narzut wydajnościowy związany z polimorfizmem dynamicznym.

## Szablony Klas

Szablony klas umożliwiają definiowanie klas generycznych, które mogą operować na różnych typach danych. Składnia szablonu klasy jest podobna do szablonu funkcji.

**Przykład:** Definicja szablonu klasy `Box`:

```cpp
template <typename T>
class Box {
private:
    T content;

public:
    Box(T content) : content(content) {}
    T getContent() const { return content; }
};
```

**Wyjaśnienie:**

- `template <typename T>`: Deklaruje szablon klasy z parametrem typu `T`.
- `T content;`: Zmienna członkowska przechowująca zawartość typu `T`.
- Konstruktor i metoda `getContent()` operują na typie `T`.

**Tworzenie instancji szablonu klasy:**

```cpp
Box<int> intBox(42);
Box<std::string> stringBox("Witaj");
```

## Wielokrotne Parametry Szablonu

Szablony mogą przyjmować wiele parametrów, zarówno typów, jak i wartości stałych. Pozwala to na bardziej precyzyjne parametryzowanie kodu.

**Przykład:** Szablon klasy `Array` z dwoma parametrami:

```cpp
template <typename T, std::size_t Size>
class Array {
private:
    T elements[Size];

public:
    // Metody dostępu i modyfikacji elementów
};
```

**Użycie:**

```cpp
Array<int, 5> myArray;
```

## Specjalizacja Szablonu

Czasami istnieje potrzeba dostosowania zachowania szablonu dla konkretnego typu. W takich przypadkach używamy **specjalizacji szablonu**.

**Przykład:** Specjalizacja szablonu klasy `Box` dla typu `std::string`:

```cpp
template <>
class Box<std::string> {
private:
    std::string content;

public:
    Box(std::string content) : content(content) {}
    std::string getContent() const { return "Zawartość: " + content; }
};
```

**Wyjaśnienie:**

- `template <>`: Wskazuje pełną specjalizację szablonu.
- `class Box<std::string>`: Specjalizacja szablonu `Box` dla typu `std::string`.
- Metoda `getContent()` została zmodyfikowana, aby zwracać prefiksowany ciąg znaków.

## Typy Domyślne w Szablonach

Możemy definiować wartości domyślne dla parametrów szablonu, co zwiększa elastyczność ich użycia.

**Przykład:**

```cpp
template <typename T = int, std::size_t Size = 10>
class Array {
private:
    T elements[Size];

public:
    // Implementacja metod
};
```

**Użycie:**

```cpp
Array<> defaultArray;             // Typ T=int, Size=10
Array<double, 5> customArray;     // Typ T=double, Size=5
```

## Szablony Zmiennych

Od C++14 możliwe jest definiowanie szablonów zmiennych, co pozwala na tworzenie zmiennych parametryzowanych typem.

**Przykład:**

```cpp
template<typename T>
constexpr T pi = T(3.1415926535897932385);

auto floatPi = pi<float>;
auto doublePi = pi<double>;
```

**Wyjaśnienie:**

- `constexpr` oznacza, że wartość jest stała w czasie kompilacji.
- `pi<T>` jest zmienną szablonową parametryzowaną typem `T`.

## Aliasowanie Szablonów

C++11 wprowadził możliwość tworzenia aliasów szablonów za pomocą słowa kluczowego `using`. Ułatwia to pracę z złożonymi typami szablonowymi.

**Przykład:**

```cpp
template <typename T>
using Vec = std::vector<T>;

Vec<int> intVector;
Vec<double> doubleVector;
```

## Szablony Lambda

Od C++20 można tworzyć szablony funkcji lambda, co dodatkowo zwiększa możliwości programistyczne.

**Przykład:**

```cpp
auto lambda = []<typename T>(T a, T b) {
    return a + b;
};

auto sumInt = lambda(5, 3);           // Wynik: 8
auto sumDouble = lambda(2.5, 1.5);    // Wynik: 4.0
```

## Metaprogramowanie Szablonowe

Metaprogramowanie szablonowe to technika, która wykorzystuje szablony do wykonywania obliczeń na etapie kompilacji. Pozwala to na optymalizację kodu i wykonywanie skomplikowanych obliczeń bez narzutu w czasie wykonywania programu.

### Przykład: Obliczanie Liczby Fibonacciego

Obliczanie wartości ciągu Fibonacciego za pomocą szablonów:

```cpp
template<int N>
struct Fibonacci {
    static_assert(N >= 0, "N musi być nieujemne");
    static constexpr int value = Fibonacci<N - 1>::value + Fibonacci<N - 2>::value;
};

template<>
struct Fibonacci<0> {
    static constexpr int value = 0;
};

template<>
struct Fibonacci<1> {
    static constexpr int value = 1;
};

constexpr int fib10 = Fibonacci<10>::value; // Wynik: 55
```

**Wyjaśnienie:**

- **Rekurencja w czasie kompilacji** polega na tym, że struktura `Fibonacci` jest rekurencyjnie instancjonowana dla wartości `N`, aż do osiągnięcia przypadków bazowych, takich jak `N=0` i `N=1`, co pozwala na obliczenia w trakcie kompilacji.
- **`static_assert`** jest używany do sprawdzania warunków w czasie kompilacji, co pozwala na weryfikację poprawności kodu przed jego wykonaniem.
- **`constexpr`** zapewnia, że dana wartość zostanie obliczona w czasie kompilacji, co zwiększa efektywność i pozwala na lepszą optymalizację kodu.

### Analiza Matematyczna

Ciąg Fibonacciego jest zdefiniowany rekurencyjnie:

$$
F(0) = 0, \quad F(1) = 1, \quad F(N) = F(N-1) + F(N-2) \text{ dla } N \geq 2
$$

Implementacja za pomocą szablonów odwzorowuje tę definicję, pozwalając kompilatorowi na obliczenie wartości `F(N)` podczas kompilacji.

### Zastosowania Metaprogramowania Szablonowego

- **Optymalizacja** polega na usunięciu narzutu czasowego poprzez przeniesienie obliczeń z etapu wykonania programu na etap kompilacji, co przyspiesza działanie aplikacji.
- **Generowanie kodów specjalizowanych** umożliwia tworzenie kodu dostosowanego do konkretnych typów lub wartości, co poprawia wydajność i elastyczność aplikacji.
- **Sprawdzanie warunków w czasie kompilacji** odbywa się za pomocą `static_assert`, który pozwala na weryfikację założeń programu przed jego uruchomieniem, eliminując potencjalne błędy już na etapie kompilacji.

## Zastosowanie Szablonów w Praktyce

Szablony są integralną częścią języka C++ i stanowią podstawę wielu bibliotek oraz aplikacji komercyjnych. Ich zdolność do tworzenia kodu generycznego, który może działać z różnymi typami danych, sprawia, że są one niezbędne w nowoczesnym programowaniu. W tej sekcji przyjrzymy się, jak szablony są wykorzystywane w praktyce, skupiając się na standardowej bibliotece C++ (STL) oraz na innych popularnych bibliotekach, takich jak Boost czy Eigen.

### Standardowa Biblioteka Szablonów (STL)

STL (Standard Template Library) jest zestawem klas i funkcji szablonowych dostarczanych przez standardową bibliotekę C++. Zawiera ona kontenery, algorytmy oraz iteratory, które umożliwiają efektywne i elastyczne manipulowanie danymi.

#### Kontenery

Kontenery są klasami szablonowymi, które przechowują kolekcje obiektów. Dzięki szablonom mogą one przechowywać elementy dowolnego typu. Oto niektóre z najważniejszych kontenerów w STL:

| Kontener                   | Opis                                                                  |
|----------------------------|-----------------------------------------------------------------------|
| **`std::vector`**           | Dynamiczna tablica o zmiennym rozmiarze.                              |
| **`std::list`**             | Lista dwukierunkowa.                                                  |
| **`std::deque`**            | Dwustronna kolejka.                                                   |
| **`std::set`**              | Zbiór unikalnych elementów, uporządkowanych.                          |
| **`std::map`**              | Asocjacyjny kontener przechowujący pary klucz-wartość.                |
| **`std::unordered_set`**    | Nieuporządkowany zbiór wykorzystujący tablice haszujące.              |
| **`std::unordered_map`**    | Nieuporządkowana mapa wykorzystująca tablice haszujące do par klucz-wartość. |

#### Algorytmy

Algorytmy w STL są funkcjami szablonowymi, które wykonują operacje na danych przechowywanych w kontenerach. Są one niezależne od konkretnych typów danych i kontenerów, o ile dostarczone są odpowiednie iteratory.

| Funkcja                   | Opis                                                           |
|---------------------------|----------------------------------------------------------------|
| **`std::sort`**            | Sortowanie elementów w zakresie.                               |
| **`std::find`**            | Wyszukiwanie elementu w zakresie.                              |
| **`std::accumulate`**      | Sumowanie wartości w zakresie.                                 |
| **`std::copy`**            | Kopiowanie elementów z jednego zakresu do drugiego.            |

#### Iteratory

Iteratory są abstrakcją wskaźników, które pozwalają na jednolite interfejsy do przeglądania elementów w kontenerach. Są one zaimplementowane jako szablony, dzięki czemu mogą działać z różnymi typami kontenerów.

### Przykład: Kontener `std::vector`

`std::vector` jest jednym z najczęściej używanych kontenerów w STL. Reprezentuje dynamiczną tablicę, która może zmieniać swój rozmiar w czasie wykonywania programu. Dzięki wykorzystaniu szablonów, `std::vector` może przechowywać elementy dowolnego typu.

**Definicja szablonu `std::vector`:**

W uproszczeniu, `std::vector` jest zdefiniowany następująco:

```cpp
template <typename T, typename Allocator = std::allocator<T>>
class vector {
    // Implementacja wewnętrzna
};
```

**Parametry szablonu:**

- **`typename T`** określa typ przechowywanych elementów, co pozwala na tworzenie szablonów, które mogą działać z różnymi typami danych.
- **`typename Allocator`** definiuje typ alokatora używanego do zarządzania pamięcią, z domyślną wartością `std::allocator<T>`, co umożliwia elastyczne zarządzanie pamięcią dla elementów.

**Przykłady użycia:**

```cpp
std::vector<int> vecInt;            // Wektor liczb całkowitych
std::vector<double> vecDouble;      // Wektor liczb zmiennoprzecinkowych
std::vector<std::string> vecString; // Wektor łańcuchów znaków
```

### Biblioteka Boost

Boost to zestaw bibliotek C++ rozszerzających funkcjonalność standardowej biblioteki. Wiele z nich jest proponowanych do włączenia do standardu C++. Szablony są intensywnie wykorzystywane w celu zapewnienia elastyczności i wydajności.

**Przykład: `boost::shared_ptr`**

Przed wprowadzeniem `std::shared_ptr` w C++11, `boost::shared_ptr` był szeroko stosowanym inteligentnym wskaźnikiem zarządzającym życiem obiektu.

**Definicja:**

```cpp
template<typename T>
class shared_ptr {
    // Implementacja wewnętrzna
};
```

**Użycie:**

```cpp
boost::shared_ptr<MyClass> ptr(new MyClass());
```

**Zalety:**

- Automatyczne zarządzanie pamięcią poprzez licznik referencji.
- Bezpieczeństwo w środowiskach wielowątkowych (z odpowiednią synchronizacją).

### Biblioteka Eigen

Eigen to szablonowa biblioteka C++ do algebry liniowej, zoptymalizowana pod kątem wysokiej wydajności.

**Definicja szablonu macierzy:**

```cpp
template<typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime>
class Matrix {
    // Implementacja wewnętrzna
};
```

**Przykład użycia:**

```cpp
Eigen::Matrix<float, 3, 3> matA;
Eigen::Matrix<float, 3, 1> vecB;

matA << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;

vecB << 1,
         2,
         3;

Eigen::Matrix<float, 3, 1> result = matA * vecB;
```

Właściwości:

- **Statyczne rozmiary** macierzy, gdy są znane w czasie kompilacji, pozwalają bibliotece Eigen na generowanie wysoce wydajnego kodu, co zwiększa efektywność obliczeń.
- **Szablony wyrażeniowe** (*Expression Templates*) umożliwiają optymalizację obliczeń, minimalizując tworzenie niepotrzebnych kopii danych, co poprawia wydajność działania programu.

Analiza wydajności:

- **Unikanie alokacji pamięci** jest możliwe dzięki zastosowaniu szablonów i mechanizmu inlining, co pozwala bibliotece Eigen na wykonywanie operacji bez potrzeby dodatkowych alokacji pamięci, co zwiększa wydajność.
- **Wektorowe instrukcje procesora** są automatycznie wykorzystywane przez Eigen, dzięki wsparciu dla instrukcji SIMD (Single Instruction, Multiple Data), jeśli są one dostępne na danej platformie, co przyspiesza operacje matematyczne.

## Koncepty (C++20)

Koncepty wprowadzają możliwość definiowania wymagań dla parametrów szablonu, co ułatwia tworzenie bardziej czytelnego i bezpiecznego kodu.

**Przykład:**

```cpp
template<typename T>
concept Number = std::is_arithmetic_v<T>;

template<Number T>
T multiply(T a, T b) {
    return a * b;
}
```

**Zalety:**

- **Poprawa czytelności błędów kompilacji** wynika z zastosowania konceptów, które umożliwiają kompilatorowi dostarczenie bardziej precyzyjnych i zrozumiałych komunikatów o błędach, co ułatwia debugowanie.
- **Dokumentacja wymagań** jest naturalnym efektem użycia konceptów, ponieważ jasno określają one, jakie wymagania musi spełniać typ parametrów szablonu, co poprawia zrozumiałość i użyteczność kodu.

## Zaawansowane Techniki z Szablonami

### Szablony o Zmiennej Liczbie Argumentów

C++11 wprowadził **szablony o zmiennej liczbie argumentów** (ang. *variadic templates*), które pozwalają na definiowanie funkcji i klas przyjmujących dowolną liczbę parametrów.

**Przykład:** Funkcja `print` wyświetlająca dowolną liczbę argumentów:

```cpp
template<typename... Args>
void print(Args... args) {
    (std::cout << ... << args) << std::endl;
}

print(1, 2, 3);                 // Wyświetla: 123
print("Witaj, ", "świecie!");   // Wyświetla: Witaj, świecie!
```

**Wyjaśnienie:**

- `template<typename... Args>`: Deklaruje szablon z pakietem typów `Args`.
- `Args... args`: Pakiet argumentów funkcji.
- `(std::cout << ... << args)`: Fold expression, dostępne od C++17, które składa wyrażenia binarne.

### Wyrażenia `constexpr` w Szablonach

`constexpr` pozwala na wykonywanie obliczeń w czasie kompilacji. Gdy używamy go w szablonach, możemy tworzyć funkcje, które zwracają stałe wartości zależne od parametrów szablonu.

**Przykład:** Funkcja `square` obliczająca kwadrat liczby:

```cpp
template<typename T>
constexpr T square(T x) {
    return x * x;
}

constexpr int squareOfFive = square(5); // Wynik: 25
```

#### Szablony Wewnętrzne (Curiously Recurring Template Pattern - CRTP)

CRTP to idiom programistyczny, w którym klasa dziedziczy po szablonie swojej własnej klasy.

**Przykład:**

```cpp
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
};

class DerivedClass : public Base<DerivedClass> {
public:
    void implementation() {
        // Implementacja specyficzna dla klasy pochodnej
    }
};
```

Zastosowania:

- **Statyczny polimorfizm** pozwala na osiągnięcie polimorfizmu w czasie kompilacji, eliminując narzut związany z dynamicznym wiązaniem, co zwiększa wydajność.
- **Klasy mixin** umożliwiają wstrzykiwanie dodatkowej funkcjonalności do klasy pochodnej, co ułatwia tworzenie modularnych i wielokrotnego użytku komponentów.

### Ograniczenia i Wyzwania

- Błędy w kodzie szablonowym mogą generować długie i trudne do zrozumienia komunikaty.
- Intensywne użycie szablonów może znacząco wydłużyć czas kompilacji.
- Szablony mogą wprowadzać zależności, które nie są oczywiste na pierwszy rzut oka.

### Praktyczne Wskazówki

- W miarę możliwości korzystaj z konceptów, aby jasno określić wymagania dla parametrów szablonu.
- Wyjaśniaj założenia i oczekiwania wobec typów parametrów.
- Staraj się nie komplikować kodu szablonowego bardziej niż to konieczne.
