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

- **Rekurencja w czasie kompilacji:** Struktura `Fibonacci` jest rekurencyjnie instancjonowana dla wartości `N`, aż do osiągnięcia przypadków bazowych dla `N=0` i `N=1`.
- **`static_assert`:** Używany do sprawdzenia warunków w czasie kompilacji.
- **`constexpr`:** Zapewnia, że wartość jest obliczana w czasie kompilacji.

### Analiza Matematyczna

Ciąg Fibonacciego jest zdefiniowany rekurencyjnie:

$$
F(0) = 0, \quad F(1) = 1, \quad F(N) = F(N-1) + F(N-2) \text{ dla } N \geq 2
$$

Implementacja za pomocą szablonów odwzorowuje tę definicję, pozwalając kompilatorowi na obliczenie wartości `F(N)` podczas kompilacji.

### Zastosowania Metaprogramowania Szablonowego

- **Optymalizacja:** Usuwanie narzutu czasowego przez przeniesienie obliczeń na etap kompilacji.
- **Generowanie Kodów Specjalizowanych:** Tworzenie kodu dostosowanego do konkretnych typów lub wartości.
- **Sprawdzanie Warunków w Czasie Kompilacji:** Użycie `static_assert` do weryfikacji założeń.

## Zastosowanie Szablonów w Praktyce

Szablony są integralną częścią języka C++ i stanowią podstawę wielu bibliotek oraz aplikacji komercyjnych. Ich zdolność do tworzenia kodu generycznego, który może działać z różnymi typami danych, sprawia, że są one niezbędne w nowoczesnym programowaniu. W tej sekcji przyjrzymy się, jak szablony są wykorzystywane w praktyce, skupiając się na standardowej bibliotece C++ (STL) oraz na innych popularnych bibliotekach, takich jak Boost czy Eigen.

### Standardowa Biblioteka Szablonów (STL)

STL (Standard Template Library) jest zestawem klas i funkcji szablonowych dostarczanych przez standardową bibliotekę C++. Zawiera ona kontenery, algorytmy oraz iteratory, które umożliwiają efektywne i elastyczne manipulowanie danymi.

#### Kontenery

Kontenery są klasami szablonowymi, które przechowują kolekcje obiektów. Dzięki szablonom mogą one przechowywać elementy dowolnego typu. Oto niektóre z najważniejszych kontenerów w STL:

- **`std::vector`**: Dynamiczna tablica o zmiennym rozmiarze.
- **`std::list`**: Lista dwukierunkowa.
- **`std::deque`**: Dwustronna kolejka.
- **`std::set`**: Zbiór unikalnych elementów, uporządkowanych.
- **`std::map`**: Asocjacyjny kontener przechowujący pary klucz-wartość.
- **`std::unordered_set`** i **`std::unordered_map`**: Kontenery nieuporządkowane, wykorzystujące tablice haszujące.

#### Algorytmy

Algorytmy w STL są funkcjami szablonowymi, które wykonują operacje na danych przechowywanych w kontenerach. Są one niezależne od konkretnych typów danych i kontenerów, o ile dostarczone są odpowiednie iteratory.

- **`std::sort`**: Sortowanie elementów w zakresie.
- **`std::find`**: Wyszukiwanie elementu w zakresie.
- **`std::accumulate`**: Sumowanie wartości w zakresie.
- **`std::copy`**: Kopiowanie elementów z jednego zakresu do drugiego.

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

- `typename T`: Typ przechowywanych elementów.
- `typename Allocator`: Typ alokatora używanego do zarządzania pamięcią (domyślnie `std::allocator<T>`).

**Przykłady użycia:**

```cpp
std::vector<int> vecInt;            // Wektor liczb całkowitych
std::vector<double> vecDouble;      // Wektor liczb zmiennoprzecinkowych
std::vector<std::string> vecString; // Wektor łańcuchów znaków
```

**Operacje na `std::vector`:**

I. **Dodawanie elementów:**

```cpp
vecInt.push_back(10);
vecInt.push_back(20);
vecInt.push_back(30);
```

II. **Dostęp do elementów:**

```cpp
int firstElement = vecInt[0];          // Dostęp za pomocą operatora []
int secondElement = vecInt.at(1);      // Dostęp z kontrolą zakresu
```

III. **Iterowanie po elementach:**

```cpp
for (size_t i = 0; i < vecInt.size(); ++i) {
  std::cout << vecInt[i] << " ";
}

for (auto it = vecInt.begin(); it != vecInt.end(); ++it) {
  std::cout << *it << " ";
}

for (const auto& value : vecInt) {
  std::cout << value << " ";
}
```

IV. **Modyfikacja elementów:**

```cpp
vecInt[0] = 100;
```

**Implementacja generyczna:**

Dzięki temu, że `std::vector` jest szablonem, możemy używać go z dowolnym typem, który jest kopiowalny lub przenośny. Oznacza to, że możemy przechowywać zarówno typy podstawowe, jak i złożone obiekty użytkownika.

**Przykład z typem użytkownika:**

```cpp
class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

std::vector<Point> points;
points.emplace_back(1, 2);
points.emplace_back(3, 4);
```

**Analiza matematyczna wydajności:**

Operacje na `std::vector` mają określone złożoności czasowe:

- **Dostęp do elementów:** O(1) - dzięki ciągłemu układowi pamięci.
- **Dodawanie elementu na końcu:** Amortyzowane O(1) - gdy wektor nie musi być realokowany.
- **Wstawianie/usuwanie elementów w środku:** O(n) - konieczność przesunięcia elementów.

**Zarządzanie pamięcią:**

`std::vector` zarządza pamięcią dynamicznie. Gdy wektor osiąga swoją maksymalną pojemność, automatycznie alokuje większy blok pamięci i kopiuje istniejące elementy. Domyślnie pojemność jest podwajana, co zapewnia amortyzowaną złożoność O(1) dla operacji dodawania na końcu.

### Przykład: Algorytm `std::sort`

Algorytm `std::sort` jest funkcją szablonową, która sortuje elementy w zakresie określonym przez dwa iteratory.

**Definicja:**

```cpp
template <class RandomIt>
void sort(RandomIt first, RandomIt last);
```

**Wymagania:**

- Typ elementów musi być porównywalny za pomocą operatora `<`.
- Iteratory muszą być iteratorami losowego dostępu (np. z `std::vector` lub tablicy).

**Przykład użycia:**

```cpp
std::vector<int> data = {5, 2, 9, 1, 5, 6};
std::sort(data.begin(), data.end());
```

**Dostosowywanie kryterium sortowania:**

Możemy dostarczyć własną funkcję porównującą:

```cpp
std::sort(data.begin(), data.end(), [](int a, int b) {
    return a > b; // Sortowanie malejące
});
```

**Złożoność czasowa:**

- Średnia: O(n log n)
- Najgorszy przypadek: O(n log n) - w implementacji wykorzystującej zabezpieczenia przed złym rozkładem danych.

### Przykład: Kontener `std::map`

`std::map` jest kontenerem asocjacyjnym, który przechowuje pary klucz-wartość w uporządkowany sposób.

**Definicja:**

```cpp
template <
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>
>
class map {
    // Implementacja wewnętrzna
};
```

**Parametry szablonu:**

- `class Key`: Typ klucza.
- `class T`: Typ wartości.
- `class Compare`: Funkcja lub funktor do porównywania kluczy.
- `class Allocator`: Alokator pamięci.

**Przykład użycia:**

```cpp
std::map<std::string, int> wordCounts;
wordCounts["apple"] = 3;
wordCounts["banana"] = 5;
wordCounts["orange"] = 2;
```

**Operacje:**

- **Wstawianie elementów:**

  ```cpp
  wordCounts.insert({"grape", 4});
  ```

- **Dostęp do wartości:**

  ```cpp
  int count = wordCounts["banana"]; // count == 5
  ```

- **Iterowanie:**

  ```cpp
  for (const auto& pair : wordCounts) {
      std::cout << pair.first << ": " << pair.second << "\n";
  }
  ```

**Właściwości:**

- Elementy są przechowywane w uporządkowany sposób według klucza.
- Wyszukiwanie, wstawianie i usuwanie mają złożoność O(log n) dzięki wewnętrznej implementacji drzewa czerwono-czarnego.

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

**Właściwości:**

- **Statyczne rozmiary:** Gdy rozmiary macierzy są znane w czasie kompilacji, Eigen może generować bardzo wydajny kod.
- **Szablony wyrażeniowe:** Wykorzystanie techniki *Expression Templates* pozwala na optymalizację obliczeń i unikanie niepotrzebnych kopii danych.

**Analiza wydajności:**

- **Unikanie alokacji pamięci:** Dzięki szablonom i inliningowi, Eigen może wykonywać operacje bez dodatkowych alokacji pamięci.
- **Wektorowe instrukcje procesora:** Eigen automatycznie wykorzystuje instrukcje SIMD (Single Instruction, Multiple Data), jeśli są dostępne na danej platformie.

### Wpływ Szablonów na Projektowanie Bibliotek

Szablony umożliwiają tworzenie bibliotek, które są zarówno elastyczne, jak i wydajne. Oto kilka kluczowych aspektów:

- **Polimorfizm statyczny:** W przeciwieństwie do polimorfizmu dynamicznego (przez klasy bazowe i wskaźniki), polimorfizm szablonowy odbywa się w czasie kompilacji, co eliminuje narzut czasu wykonywania.
- **Silne typowanie:** Błędy typów są wykrywane w czasie kompilacji, co zwiększa bezpieczeństwo kodu.
- **Optymalizacje kompilatora:** Kompilator może generować specjalizowany kod dla konkretnych typów, co pozwala na agresywne optymalizacje.

### Koncepty (C++20)

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

- **Poprawa czytelności błędów kompilacji:** Kompilator może dostarczyć bardziej precyzyjne komunikaty o błędach.
- **Dokumentacja wymagań:** Koncepty jasno określają, jakie wymagania musi spełniać typ parametrów szablonu.

### Zaawansowane Techniki z Użyciem Szablonów

#### Metaprogramowanie Szablonowe

Metaprogramowanie szablonowe pozwala na wykonywanie obliczeń w czasie kompilacji.

**Przykład: Generowanie listy typów**

```cpp
template<typename... Types>
struct TypeList {};

using MyTypes = TypeList<int, double, std::string>;
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

**Zastosowania:**

- **Statyczne polimorfizmy** pozwala na osiągnięcie polimorfizmu bez narzutu dynamicznego wiązania.
- **Mixin Classes** umożliwiają wstrzykiwanie funkcjonalności do klasy pochodnej.

### Ograniczenia i Wyzwania

- Błędy w kodzie szablonowym mogą generować długie i trudne do zrozumienia komunikaty.
- Intensywne użycie szablonów może znacząco wydłużyć czas kompilacji.
- Szablony mogą wprowadzać zależności, które nie są oczywiste na pierwszy rzut oka.

### Praktyczne Wskazówki

- W miarę możliwości korzystaj z konceptów, aby jasno określić wymagania dla parametrów szablonu.
- Wyjaśniaj założenia i oczekiwania wobec typów parametrów.
- Staraj się nie komplikować kodu szablonowego bardziej niż to konieczne.
