## Szablony

Szablony są jednym z kluczowych aspektów metaprogramowania w C++. Umożliwiają pisanie generycznych funkcji i klas, które adaptują się do różnych typów danych, bez konieczności duplikowania kodu. Zapewniają one wydajność kodu zapisanego ręcznie dla konkretnego typu, zachowując jednocześnie elastyczność.

### Szablon funkcji

Aby zdefiniować szablon funkcji, używamy słowa kluczowego `template`, po którym następuje lista parametrów szablonu w nawiasach trójkątnych `<>`.

Przykład generycznej funkcji `max2`:

```c++
template <typename T> 
T max2(T arg1, T arg2) {
    return arg1 > arg2 ? arg1 : arg2;
}
```

Podczas korzystania z funkcji szablonowej, kompilator tworzy odpowiednią specjalizację funkcji dla użytego typu:

```c++
max2<int>(10, 20);       // 20
max2<double>(16.2, 3.14); // 16.2
max2<char>('a', 'b');     // 'b'
```

### Szablon klasy

Szablon klasy pozwala na zdefiniowanie generycznej klasy, która może operować na różnych typach danych:

```c++
template <typename T> 
class Box {
    T content;

public:
    Box(T content) : content(content) {}
    T getContent() const { return content; }
};
```

Tworzenie instancji klasy szablonowej:

```c++
Box<int> intBox(42);
Box<std::string> stringBox("Hello");
```

### Wielokrotne parametry szablonu

Możemy również definiować szablony z wieloma parametrami:

```c++
template <typename T, int size> 
class Array {
    T elements[size];
    // ...
};
```

Użycie:

```c++
Array<int, 5> myArray;
```

### Specjalizacja szablonu

Czasami chcemy, aby dla konkretnego typu szablon działał w inny sposób. Możemy to osiągnąć, definiując specjalizację szablonu:

```c++
template <>
class Box<std::string> {
    std::string content;
    
public:
    Box(std::string content) : content(content) {}
    std::string getContent() const { return "Content: " + content; }
};
```

Teraz, gdy użyjemy `Box<std::string>`, metoda `getContent()` zwróci nieco inną wartość niż w ogólnym przypadku.

### Typy domyślne w szablonach

Możemy określić typy domyślne dla parametrów szablonu:

```c++
template <typename T = int, int size = 10> 
class Array {
    T elements[size];
    // ...
};
```

Użycie:

```c++
Array<> defaultArray;
Array<double, 5> customArray;
```

W powyższym przykładzie `defaultArray` będzie instancją `Array` z domyślnymi parametrami (`int` i `10`), natomiast `customArray` będzie instancją z typem `double` i rozmiarem `5`.

### Szablony zmiennych

C++14 wprowadził możliwość definiowania szablonów zmiennych. Umożliwia to definiowanie zmiennych w sposób generyczny:

```c++
template<typename T>
constexpr T pi = T(3.1415926535897932385);

auto floatPi = pi<float>;
auto doublePi = pi<double>;
```

### Szablony aliasów

C++11 wprowadził aliasy szablonów, które upraszczają użycie złożonych typów. Pozwala to na tworzenie aliasów dla szablonów typów:

```c++
template <typename T>
using Vec = std::vector<T>;

Vec<int> intVector;
Vec<double> doubleVector;
```

### Szablony funkcji lambda

Od C++20 możemy tworzyć szablony funkcji lambda, co dodatkowo zwiększa elastyczność:

```c++
auto lambda = []<typename T>(T a, T b) {
    return a + b;
};

auto sum = lambda(5, 3);       // 8
auto sumDouble = lambda(2.5, 1.5); // 4.0
```

### Zaawansowane techniki z szablonami

#### Szablony zmiennych o zmiennej liczbie argumentów

C++11 wprowadził szablony zmiennych o zmiennej liczbie argumentów, co pozwala na definiowanie funkcji i klas, które mogą przyjmować dowolną liczbę argumentów:

```c++
template<typename... Args>
void print(Args... args) {
    (std::cout << ... << args) << std::endl;
}

print(1, 2, 3);             // 123
print("Hello, ", "world!"); // Hello, world!
```

#### Wyrażenia constexpr w szablonach

Możemy używać wyrażeń `constexpr` w szablonach, aby definiować wartości stałe podczas kompilacji:

```c++
template<typename T>
constexpr T square(T x) {
    return x * x;
}

constexpr int squareOfFive = square(5); // 25
```

#### Metaprogramowanie szablonowe

Metaprogramowanie szablonowe to technika programistyczna w językach takich jak C++, która pozwala na wykonywanie obliczeń na etapie kompilacji. Dzięki temu możliwe jest tworzenie bardziej efektywnego kodu, optymalizowanego już podczas kompilacji, a także zwiększenie elastyczności i reużywalności kodu.

Jednym z klasycznych przykładów metaprogramowania szablonowego jest obliczanie wartości ciągu Fibonacciego. Poniżej znajduje się przykład, który ilustruje, jak to działa:

```c++
template<int N>
struct Fibonacci {
    static constexpr int value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};

template<>
struct Fibonacci<0> {
    static constexpr int value = 0;
};

template<>
struct Fibonacci<1> {
    static constexpr int value = 1;
};

constexpr int fib10 = Fibonacci<10>::value; // 55
```

##### Co to jest metaprogramowanie szablonowe?

Metaprogramowanie szablonowe to technika, w której używa się szablonów (ang. templates) do generowania kodu podczas kompilacji. Szablony są mechanizmem pozwalającym na pisanie kodu ogólnego, który może działać z różnymi typami danych. C++ umożliwia tworzenie szablonów klas, funkcji, a także szablonów zmiennych.

##### Jak działa metaprogramowanie szablonowe?

Metaprogramowanie szablonowe działa poprzez rekurencyjne instancjonowanie szablonów podczas kompilacji. Oznacza to, że kompilator rozwija szablony, generując kod specyficzny dla podanych parametrów szablonu.

W powyższym przykładzie, szablon `Fibonacci` jest instancjonowany dla kolejnych wartości `N`, aż do osiągnięcia przypadków bazowych `Fibonacci<0>` i `Fibonacci<1>`. Kompilator rozwija ten kod w sposób rekurencyjny, obliczając wartość `Fibonacci<10>` jako sumę wartości `Fibonacci<9>` i `Fibonacci<8>`, i tak dalej, aż do wartości bazowych.

##### Dlaczego używać metaprogramowania szablonowego?

1. **Wydajność**: Obliczenia wykonywane podczas kompilacji mogą zwiększyć wydajność programu, eliminując potrzebę wykonywania tych obliczeń podczas uruchomienia.
2. **Bezpieczeństwo typów**: Metaprogramowanie szablonowe pozwala na tworzenie kodu, który jest bardziej bezpieczny typowo, ponieważ wiele błędów może być wykrywanych na etapie kompilacji.
3. **Elastyczność**: Szablony pozwalają na pisanie bardziej elastycznego i reużywalnego kodu, który może działać z różnymi typami danych.
4. **Redukcja powtarzalności kodu**: Szablony pozwalają na zredukowanie powtarzalności kodu, co ułatwia jego utrzymanie i rozwój.

##### Praktyczne zastosowania

Metaprogramowanie szablonowe znajduje szerokie zastosowanie w wielu dziedzinach programowania:

- **Biblioteki standardowe**: Wiele funkcji i klas w standardowej bibliotece C++ (STL) korzysta z metaprogramowania szablonowego.
- **Optymalizacja kodu**: Dzięki obliczeniom na etapie kompilacji można tworzyć wysoko zoptymalizowany kod.
- **Generowanie kodu**: Automatyczne generowanie kodu specyficznego dla danego problemu, co może uprościć implementację skomplikowanych algorytmów.
