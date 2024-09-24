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

Szablony są szeroko wykorzystywane w standardowej bibliotece C++ (STL) oraz w nowoczesnych bibliotekach, takich jak Boost czy Eigen. Pozwalają one na tworzenie kontenerów, algorytmów i innych narzędzi, które są elastyczne i wydajne.

### Przykład: Kontener `std::vector`

`std::vector` jest szablonem klasy, który reprezentuje dynamicznie rozmiarową tablicę:

```cpp
std::vector<int> vecInt;
std::vector<double> vecDouble;
```

**Implementacja generyczna** pozwala na użycie `std::vector` z dowolnym typem, co zwiększa jego wszechstronność.
