## Szablony

Szablony (ang. *templates*) stanowią fundament nowoczesnego programowania w języku C++. Są jednym z najbardziej potężnych narzędzi oferowanych przez ten język, umożliwiając programistom pisanie bardziej elastycznego i wielokrotnego użytku kodu. Dzięki szablonom, można tworzyć funkcje i klasy, które działają z różnymi typami danych, co znacząco redukuje potrzebę duplikacji kodu oraz zwiększa jego czytelność i utrzymanie. Szablony odgrywają kluczową rolę w metaprogramowaniu w C++, pozwalając na wykonywanie obliczeń na etapie kompilacji oraz optymalizację kodu wynikowego. Poniżej przedstawiono szczegółowe omówienie różnych aspektów szablonów w C++, wraz z przykładami i wyjaśnieniami.

### Szablony Funkcji

Szablony funkcji pozwalają na definiowanie funkcji, które działają na różnych typach danych. Umożliwiają one tworzenie generycznego kodu, który jest bardziej uniwersalny i może być stosowany w szerokim zakresie zastosowań bez konieczności pisania osobnych wersji funkcji dla każdego typu danych. Ogólna składnia definicji szablonu funkcji jest następująca:

```cpp
template <parametry_szablonu>
typ_zwracany nazwa_funkcji(argumenty) {

    // ciało funkcji

}
```

**Przykład:** 

Definicja generycznej funkcji `max2`, która zwraca większą z dwóch wartości:

```cpp
template <typename T>
T max2(T arg1, T arg2) {
    return arg1 > arg2 ? arg1 : arg2;
}
```

- `template <typename T>` deklaruje szablon z parametrem typu `T`, który może być dowolnym typem danych (np. `int`, `double`, `std::string`).
- Funkcja `max2` przyjmuje dwa argumenty typu `T` i zwraca wartość typu `T`.
- Operator `?:` zwraca `arg1` lub `arg2` w zależności od wyniku porównania `arg1 > arg2`, co pozwala na elastyczne porównywanie różnych typów danych.

**Użycie funkcji szablonowej:**

Szablony funkcji są wykorzystywane poprzez ich instancjowanie z konkretnymi typami danych, co pozwala na ich wielokrotne użycie bez konieczności definiowania nowych funkcji dla każdego typu.

```cpp
int a = max2<int>(10, 20);            // Wynik: 20
double b = max2<double>(16.2, 3.14);  // Wynik: 16.2
char c = max2<char>('a', 'b');        // Wynik: 'b'
```

#### Mechanizm Instancjacji

Podczas kompilacji, gdy funkcja szablonowa jest wywoływana z konkretnym typem, kompilator tworzy jej **instancję** dla tego typu. Proces ten nazywany jest **instancjacją szablonu**. Dzięki temu generowany kod jest zoptymalizowany pod kątem użytych typów, eliminując narzut wydajnościowy związany z polimorfizmem dynamicznym. Instancjacja szablonów pozwala na tworzenie specjalizowanych wersji funkcji lub klas, które są dostosowane do specyficznych potrzeb aplikacji, co zwiększa efektywność i wydajność kodu.

### Szablony Klas

Szablony klas umożliwiają definiowanie klas generycznych, które mogą operować na różnych typach danych. Dzięki temu można tworzyć bardziej elastyczne i wielokrotnego użytku struktury danych oraz obiektów. Składnia szablonu klasy jest podobna do szablonu funkcji, co ułatwia zrozumienie i implementację.

**Przykład:** 

Definicja szablonu klasy `Box`:

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

- `template <typename T>`: Deklaruje szablon klasy z parametrem typu `T`, co pozwala na przechowywanie różnych typów danych w jednej klasie.
- `T content;`: Zmienna członkowska przechowująca zawartość typu `T`, co umożliwia elastyczne przechowywanie dowolnego typu danych.
- Konstruktor i metoda `getContent()` operują na typie `T`, co zapewnia, że klasa `Box` jest w pełni generyczna i może być używana z dowolnym typem danych.

**Tworzenie instancji szablonu klasy:**

Szablony klas są wykorzystywane poprzez określenie konkretnego typu danych podczas tworzenia obiektu.

```cpp
Box<int> intBox(42);

Box<std::string> stringBox("Witaj");
```

#### Wielokrotne Parametry Szablonu

Szablony mogą przyjmować wiele parametrów, zarówno typów, jak i wartości stałych. Pozwala to na bardziej precyzyjne parametryzowanie kodu, co zwiększa jego elastyczność i umożliwia tworzenie bardziej zaawansowanych struktur danych oraz algorytmów.

**Przykład:** 

Szablon klasy `Array` z dwoma parametrami:

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

W tym przykładzie, szablon klasy `Array` przyjmuje zarówno typ danych `T`, jak i stałą `Size`, co pozwala na tworzenie tablic o dynamicznie określonym rozmiarze i typie danych.

#### Specjalizacja Szablonu

Czasami istnieje potrzeba dostosowania zachowania szablonu dla konkretnego typu. W takich przypadkach używamy **specjalizacji szablonu**, co pozwala na definiowanie unikalnych implementacji dla wybranych typów danych, zachowując jednocześnie ogólność szablonu dla innych typów.

**Przykład:** 

Specjalizacja szablonu klasy `Box` dla typu `std::string`:

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

- `template <>`: Wskazuje pełną specjalizację szablonu, co oznacza, że ta definicja jest unikalna dla określonego typu.
- `class Box<std::string>`: Specjalizacja szablonu `Box` dla typu `std::string` umożliwia dostosowanie zachowania klasy do specyfiki tego typu danych.
- Metoda `getContent()` została zmodyfikowana, aby zwracać prefiksowany ciąg znaków, co jest specyficzne dla typu `std::string` i nie byłoby konieczne dla innych typów.

### Typy Domyślne w Szablonach

Możemy definiować wartości domyślne dla parametrów szablonu, co zwiększa elastyczność ich użycia. Dzięki wartościom domyślnym, programista może tworzyć instancje szablonów bez konieczności podawania wszystkich parametrów, co upraszcza kod i poprawia jego czytelność.

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

W tym przykładzie, szablon klasy `Array` ma zdefiniowane wartości domyślne dla parametrów `T` i `Size`, co pozwala na tworzenie instancji z domyślnymi ustawieniami lub z niestandardowymi parametrami w zależności od potrzeb.

### Szablony Zmiennych

Od C++14 możliwe jest definiowanie szablonów zmiennych, co pozwala na tworzenie zmiennych parametryzowanych typem. Szablony zmiennych są szczególnie przydatne w przypadku stałych wartości, które mogą być różne w zależności od typu danych.

**Przykład:**

```cpp
template<typename T>
constexpr T pi = T(3.1415926535897932385);

auto floatPi = pi<float>;
auto doublePi = pi<double>;
```

**Wyjaśnienie:**

- `constexpr` oznacza, że wartość jest stała w czasie kompilacji, co pozwala na optymalizację i redukcję kosztów czasowych w czasie wykonywania programu.
- `pi<T>` jest zmienną szablonową parametryzowaną typem `T`, co umożliwia tworzenie precyzyjnych wersji stałej `pi` dla różnych typów danych, takich jak `float` czy `double`.

### Aliasowanie Szablonów

C++11 wprowadził możliwość tworzenia aliasów szablonów za pomocą słowa kluczowego `using`. Aliasowanie szablonów ułatwia pracę z złożonymi typami szablonowymi, poprawiając czytelność kodu oraz zmniejszając jego złożoność.

**Przykład:**

```cpp
template <typename T>
using Vec = std::vector<T>;

Vec<int> intVector;
Vec<double> doubleVector;
```

W tym przykładzie, alias `Vec` jest używany do reprezentowania `std::vector<T>`, co upraszcza deklarację wektorów różnych typów i poprawia czytelność kodu.

### Szablony Lambda

Od C++20 można tworzyć szablony funkcji lambda, co dodatkowo zwiększa możliwości programistyczne. Szablony lambda pozwalają na definiowanie anonimowych funkcji generycznych, które mogą być wykorzystywane w różnych kontekstach bez potrzeby definiowania osobnych funkcji.

**Przykład:**

```cpp
auto lambda = []<typename T>(T a, T b) {
    return a + b;
};

auto sumInt = lambda(5, 3);           // Wynik: 8
auto sumDouble = lambda(2.5, 1.5);    // Wynik: 4.0
```

W tym przykładzie, lambda jest szablonem funkcji, który może przyjmować różne typy danych `T` i wykonywać na nich operację dodawania, co czyni ją niezwykle elastyczną i wielokrotnego użytku.

### Metaprogramowanie Szablonowe

Metaprogramowanie szablonowe to technika, która wykorzystuje szablony do wykonywania obliczeń na etapie kompilacji. Pozwala to na optymalizację kodu oraz wykonywanie skomplikowanych obliczeń bez narzutu w czasie wykonywania programu. Metaprogramowanie szablonowe jest szczególnie przydatne w przypadkach, gdzie wydajność jest kluczowa, a obliczenia mogą być przeprowadzone wcześniej, podczas kompilacji.

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

- **Rekurencja w czasie kompilacji** polega na tym, że struktura `Fibonacci` jest rekurencyjnie instancjonowana dla wartości `N`, aż do osiągnięcia przypadków bazowych, takich jak `N=0` i `N=1`, co pozwala na obliczenia w trakcie kompilacji.
- **`static_assert`** jest używany do sprawdzania warunków w czasie kompilacji, co pozwala na weryfikację poprawności kodu przed jego wykonaniem. W tym przypadku, zapewnia, że `N` jest nieujemne.
- **`constexpr`** zapewnia, że dana wartość zostanie obliczona w czasie kompilacji, co zwiększa efektywność i pozwala na lepszą optymalizację kodu.

#### Analiza Matematyczna

Ciąg Fibonacciego jest zdefiniowany rekurencyjnie:

$$
F(0) = 0, \quad F(1) = 1, \quad F(N) = F(N-1) + F(N-2) \text{ dla } N \geq 2
$$

Implementacja za pomocą szablonów odwzorowuje tę definicję, pozwalając kompilatorowi na obliczenie wartości `F(N)` podczas kompilacji. Dzięki temu, wartości ciągu Fibonacciego są dostępne w czasie kompilacji, co może być użyteczne w różnych optymalizacjach i zastosowaniach.

##### Zastosowania Metaprogramowania Szablonowego

- **Optymalizacja** polega na usunięciu narzutu czasowego poprzez przeniesienie obliczeń z etapu wykonania programu na etap kompilacji, co przyspiesza działanie aplikacji. Dzięki temu, program może działać szybciej, ponieważ wiele obliczeń zostało już wykonanych przed jego uruchomieniem.
- **Generowanie kodów specjalizowanych** umożliwia tworzenie kodu dostosowanego do konkretnych typów lub wartości, co poprawia wydajność i elastyczność aplikacji. Szablony mogą automatycznie generować różne wersje funkcji lub klas, zoptymalizowane pod kątem specyficznych potrzeb.
- **Sprawdzanie warunków w czasie kompilacji** odbywa się za pomocą `static_assert`, który pozwala na weryfikację założeń programu przed jego uruchomieniem, eliminując potencjalne błędy już na etapie kompilacji. Dzięki temu, programista może szybko zidentyfikować i naprawić błędy, zanim program zostanie uruchomiony.

### Zastosowanie Szablonów w Praktyce

Szablony są integralną częścią języka C++ i stanowią podstawę wielu bibliotek oraz aplikacji komercyjnych. Ich zdolność do tworzenia kodu generycznego, który może działać z różnymi typami danych, sprawia, że są one niezbędne w nowoczesnym programowaniu. W tej sekcji przyjrzymy się, jak szablony są wykorzystywane w praktyce, skupiając się na standardowej bibliotece C++ (STL) oraz na innych popularnych bibliotekach, takich jak Boost czy Eigen.

#### Standardowa Biblioteka Szablonów (STL)

STL (Standard Template Library) jest zestawem klas i funkcji szablonowych dostarczanych przez standardową bibliotekę C++. Została ona zaprojektowana w celu zapewnienia programistom gotowych do użycia struktur danych oraz algorytmów, które są zarówno wydajne, jak i łatwe w użyciu. STL jest szeroko stosowana w różnych aplikacjach, od prostych programów konsolowych po zaawansowane systemy o dużej skali.

##### Kontenery

Kontenery są klasami szablonowymi, które przechowują kolekcje obiektów. Dzięki szablonom mogą one przechowywać elementy dowolnego typu, co czyni je niezwykle elastycznymi i wielokrotnego użytku. Kontenery w STL są zoptymalizowane pod kątem różnych operacji, takich jak dodawanie, usuwanie czy wyszukiwanie elementów, co pozwala na efektywne zarządzanie danymi.

Oto niektóre z najważniejszych kontenerów w STL:

| Kontener                   | Opis                                                                  |
|----------------------------|-----------------------------------------------------------------------|
| **`std::vector`**           | Dynamiczna tablica o zmiennym rozmiarze.                              |
| **`std::list`**             | Lista dwukierunkowa.                                                  |
| **`std::deque`**            | Dwustronna kolejka.                                                   |
| **`std::set`**              | Zbiór unikalnych elementów, uporządkowanych.                          |
| **`std::map`**              | Asocjacyjny kontener przechowujący pary klucz-wartość.                |
| **`std::unordered_set`**    | Nieuporządkowany zbiór wykorzystujący tablice haszujące.              |
| **`std::unordered_map`**    | Nieuporządkowana mapa wykorzystująca tablice haszujące do par klucz-wartość. |

Każdy z tych kontenerów ma swoje specyficzne zastosowania i jest zoptymalizowany pod kątem różnych operacji, co pozwala programistom na wybór najbardziej odpowiedniego kontenera dla ich potrzeb.

##### Algorytmy

Algorytmy w STL są funkcjami szablonowymi, które wykonują operacje na danych przechowywanych w kontenerach. Są one niezależne od konkretnych typów danych i kontenerów, o ile dostarczone są odpowiednie iteratory. Algorytmy w STL obejmują szeroki zakres operacji, takich jak sortowanie, wyszukiwanie, modyfikowanie czy transformowanie danych, co pozwala na efektywne i elastyczne manipulowanie kolekcjami danych.

| Funkcja                   | Opis                                                           |
|---------------------------|----------------------------------------------------------------|
| **`std::sort`**            | Sortowanie elementów w zakresie.                               |
| **`std::find`**            | Wyszukiwanie elementu w zakresie.                              |
| **`std::accumulate`**      | Sumowanie wartości w zakresie.                                 |
| **`std::copy`**            | Kopiowanie elementów z jednego zakresu do drugiego.            |

Algorytmy te są zoptymalizowane pod kątem wydajności i mogą być stosowane do różnych typów danych, co czyni je niezwykle wszechstronnymi narzędziami w arsenale programisty C++.

##### Iteratory

Iteratory są abstrakcją wskaźników, które pozwalają na jednolite interfejsy do przeglądania elementów w kontenerach. Są one zaimplementowane jako szablony, dzięki czemu mogą działać z różnymi typami kontenerów. Iteratory umożliwiają programistom pisanie bardziej generycznego i elastycznego kodu, który może działać z dowolnym kontenerem, który wspiera dany typ iteratora.

#### Przykład: Kontener `std::vector`

`std::vector` jest jednym z najczęściej używanych kontenerów w STL. Reprezentuje dynamiczną tablicę, która może zmieniać swój rozmiar w czasie wykonywania programu. Dzięki wykorzystaniu szablonów, `std::vector` może przechowywać elementy dowolnego typu, co czyni go niezwykle elastycznym narzędziem do zarządzania dynamicznymi kolekcjami danych.

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

W tym przykładzie, `std::vector` jest używany do przechowywania różnych typów danych, co pokazuje jego elastyczność i wszechstronność. Dzięki szablonom, można łatwo tworzyć wektory dla dowolnego typu danych, co znacznie ułatwia zarządzanie dynamicznymi kolekcjami.

#### Biblioteka Boost

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

#### Biblioteka Eigen

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

#### Koncepty (C++20)

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

### Zaawansowane Techniki z Szablonami

W miarę rozwoju języka C++, szablony stały się nie tylko narzędziem do tworzenia generycznego kodu, ale także platformą do implementacji zaawansowanych technik programistycznych. W tej sekcji omówimy kilka z tych zaawansowanych technik, które pozwalają na jeszcze większą elastyczność i moc w tworzeniu aplikacji. Skoncentrujemy się na szablonach o zmiennej liczbie argumentów, wyrażeniach `constexpr` w szablonach, szablonach wewnętrznych (CRTP), a także na omówieniu ograniczeń i wyzwań związanych z ich używaniem. Dodatkowo, przedstawimy praktyczne wskazówki, które pomogą w efektywnym wykorzystaniu tych technik w codziennym programowaniu.

#### Szablony o Zmiennej Liczbie Argumentów

Szablony o zmiennej liczbie argumentów, znane również jako *variadic templates*, zostały wprowadzone w standardzie C++11 i stanowią potężne rozszerzenie tradycyjnych szablonów. Umożliwiają one definiowanie funkcji i klas, które mogą przyjmować dowolną liczbę parametrów, co jest niezwykle przydatne w sytuacjach, gdy liczba argumentów nie jest znana z góry lub może się dynamicznie zmieniać.

**Przykład:** Funkcja `print` wyświetlająca dowolną liczbę argumentów:

```cpp
#include <iostream>

template<typename... Args>
void print(Args... args) {
    (std::cout << ... << args) << std::endl;
}

int main() {
    print(1, 2, 3);                 // Wyświetla: 123
    print("Witaj, ", "świecie!");   // Wyświetla: Witaj, świecie!
    return 0;
}
```

- `template<typename... Args>`: Deklaruje szablon z pakietem typów `Args`. Operator `...` oznacza, że `Args` może reprezentować dowolną liczbę typów.
- `Args... args`: Pakiet argumentów funkcji. Podobnie jak powyżej, `...` wskazuje na zmienną liczbę argumentów.
- `(std::cout << ... << args)`: Fold expression, dostępne od C++17, które umożliwia składanie wyrażeń binarnych. W tym przypadku, łączy wszystkie argumenty za pomocą operatora `<<` i wypisuje je na standardowe wyjście.

**Zastosowanie:**

Szablony o zmiennej liczbie argumentów są niezwykle przydatne w tworzeniu funkcji, które muszą obsługiwać dynamiczną liczbę parametrów, takich jak funkcje logujące, formatowania czy tworzenia kontenerów o zmiennym rozmiarze.

#### Wyrażenia `constexpr` w Szablonach

Słowo kluczowe `constexpr` zostało wprowadzone w C++11 i pozwala na wykonywanie obliczeń w czasie kompilacji. W połączeniu z szablonami, `constexpr` umożliwia tworzenie funkcji, które zwracają stałe wartości zależne od parametrów szablonu, co może prowadzić do znacznych optymalizacji kodu.

**Przykład:** Funkcja `square` obliczająca kwadrat liczby:

```cpp
#include <iostream>

template<typename T>
constexpr T square(T x) {
    return x * x;
}

int main() {
    constexpr int squareOfFive = square(5); // Wynik: 25
    std::cout << "Kwadrat 5 to: " << squareOfFive << std::endl;
    return 0;
}
```

- `template<typename T>`: Deklaruje szablon funkcji z parametrem typu `T`.
- `constexpr T square(T x)`: Funkcja oznaczona jako `constexpr`, co oznacza, że może być oceniona w czasie kompilacji, jeśli argumenty są znane w tym czasie.
- `constexpr int squareOfFive = square(5);`: Inicjalizuje stałą `squareOfFive` wynikiem funkcji `square(5)`, który jest obliczany w czasie kompilacji.

**Zastosowanie:**

Funkcje `constexpr` są użyteczne w przypadkach, gdzie potrzebne są stałe wartości obliczane na podstawie parametrów szablonu, co może prowadzić do bardziej wydajnego kodu dzięki wstępnej ocenie wyrażeń.

##### Szablony Wewnętrzne (Curiously Recurring Template Pattern - CRTP)

Curiously Recurring Template Pattern (CRTP) to idiom programistyczny, w którym klasa dziedziczy po szablonie swojej własnej klasy. Technika ta pozwala na osiągnięcie statycznego polimorfizmu oraz umożliwia implementację funkcji, które są specyficzne dla klasy pochodnej, bez użycia wirtualnych metod.

**Przykład:**

```cpp
#include <iostream>

// Szablon bazowej klasy wykorzystujący CRTP
template<typename Derived>
class Base {
public:
    void interface() {
        // Wywołuje implementację specyficzną dla klasy pochodnej
        static_cast<Derived*>(this)->implementation();
    }

    void commonFunction() {
        std::cout << "Funkcja wspólna w klasie Base." << std::endl;
    }
};

// Klasa pochodna dziedzicząca po Base za pomocą CRTP
class DerivedClass : public Base<DerivedClass> {
public:
    void implementation() {
        std::cout << "Implementacja specyficzna dla DerivedClass." << std::endl;
    }
};

int main() {
    DerivedClass obj;
    obj.interface();         // Wywołuje DerivedClass::implementation()
    obj.commonFunction();    // Wywołuje Base::commonFunction()
    return 0;
}
```

- `template<typename Derived>`: Szablon bazowej klasy przyjmujący typ klasy pochodnej.
- `static_cast<Derived*>(this)->implementation()`: Rzutowanie wskaźnika `this` na typ klasy pochodnej i wywołanie jej metody `implementation()`.
- `DerivedClass : public Base<DerivedClass>`: Klasa pochodna dziedziczy po bazowej klasie szablonowej, przekazując siebie jako parametr szablonu.

**Zastosowania:**

- **Statyczny polimorfizm** umożliwia polimorfizm bez kosztów związanych z dynamicznym wiązaniem, co zwiększa wydajność.
- **Klasy mixin** pozwalają na dodawanie funkcjonalności do klas pochodnych w sposób modułowy i wielokrotnego użytku.

#### Ograniczenia i Wyzwania

Mimo że szablony oferują ogromne możliwości, ich użycie wiąże się również z pewnymi ograniczeniami i wyzwaniami, które programiści powinni mieć na uwadze:

- Błędy w kodzie szablonowym często generują długie i trudne do zrozumienia komunikaty kompilatora, co utrudnia diagnozowanie problemów.
- Intensywne użycie szablonów może znacznie wydłużyć czas kompilacji, szczególnie w dużych projektach.
- Szablony mogą wprowadzać zależności, które nie są od razu widoczne, co może prowadzić do trudnych do zidentyfikowania błędów lub problemów z kompatybilnością.
- Nadmierne korzystanie ze szablonów może uczynić kod mniej czytelnym i trudniejszym do utrzymania, zwłaszcza dla programistów nieznających zaawansowanych technik szablonowych.

#### Praktyczne Wskazówki

Aby skutecznie wykorzystać zaawansowane techniki szablonowe i uniknąć typowych pułapek, warto przestrzegać kilku praktycznych zasad:

- Jeśli to możliwe, używaj konceptów do jasno określenia wymagań dla parametrów szablonu. Pozwala to na lepszą czytelność kodu oraz wcześniejsze wykrywanie błędów.
  
```cpp
#include <concepts>

template<std::integral T>
T add(T a, T b) {
  return a + b;
}
```
  
- Dokumentuj, jakie cechy lub interfejsy muszą posiadać typy używane jako parametry szablonu. Ułatwia to zrozumienie kodu oraz jego prawidłowe użycie.
- Staraj się nie komplikować kodu szablonowego bardziej niż to konieczne. Złożone szablony mogą być trudne do zrozumienia i utrzymania, co zwiększa ryzyko błędów.
- Projektuj szablony w sposób modularny, aby mogły być łatwo reużywane w różnych kontekstach. To zwiększa ich wartość i ułatwia integrację z innymi komponentami systemu.
- Monitoruj czas kompilacji i optymalizuj użycie szablonów, aby uniknąć znacznego wydłużenia procesu kompilacji. Można to osiągnąć poprzez stosowanie technik takich jak prekompilowane nagłówki lub ograniczenie głębokości rekurencji szablonów.

