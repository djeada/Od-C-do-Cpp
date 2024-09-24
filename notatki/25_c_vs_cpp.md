## C vs C++

C i C++ to dwa języki programowania o wspólnych korzeniach, które odgrywają kluczowe role w dziedzinie informatyki. Chociaż C++ jest często określany jako rozszerzenie C, różnice między nimi są na tyle znaczące, że warto je szczegółowo omówić. W poniższym tekście przedstawimy dogłębną analizę obu języków, zwracając uwagę na ich historię, zgodność, składnię, funkcjonalności oraz zastosowania, z naciskiem na rygor matematyczny i techniczny.

### Historia

#### Język C

Język C został opracowany na początku lat 70. XX wieku przez Dennisa Ritchiego w Bell Laboratories. Był on ewolucją wcześniejszych języków, takich jak B i BCPL. C powstał w celu stworzenia języka uniwersalnego, który umożliwiłby pisanie systemów operacyjnych oraz programów narzędziowych z wydajnością zbliżoną do asemblera, ale z wyższym poziomem abstrakcji.

Kluczowym momentem w historii C było napisanie systemu operacyjnego UNIX w tym języku, co przyczyniło się do jego szerokiej adopcji. Standaryzacja języka nastąpiła w 1989 roku wraz z publikacją standardu ANSI C (znanego również jako C89), a później w standardach ISO C90, C99, C11 i C18, które wprowadzały kolejne usprawnienia i funkcjonalności.

#### Język C++

C++ został stworzony przez Bjarne Stroustrupa w latach 80. XX wieku, również w Bell Laboratories. Początkowo nazywany "C z klasami", C++ miał na celu wprowadzenie do języka C mechanizmów programowania obiektowego, takich jak klasy, dziedziczenie i polimorfizm. Nazwa "C++" jest odniesieniem do operatora inkrementacji w C, sugerując, że C++ jest "następną wersją" C.

C++ przeszedł wiele etapów standaryzacji, począwszy od standardu C++98, poprzez C++03, C++11, C++14, C++17, aż po C++20 i C++23. Każda kolejna wersja wprowadzała nowe funkcjonalności, takie jak szablony (templates), inteligentne wskaźniki, wyrażenia lambda, koncepty (concepts) i wiele innych, czyniąc język coraz bardziej złożonym, ale jednocześnie potężnym narzędziem do tworzenia skomplikowanych systemów.

### Zgodność i Różnice

#### Zgodność Wsteczna

C++ został zaprojektowany tak, aby był w dużej mierze zgodny wstecz z C. Oznacza to, że wiele kodu napisanego w C można skompilować jako kod C++. Jednakże ta zgodność nie jest absolutna. Istnieją subtelne różnice w semantyce niektórych konstrukcji, co może prowadzić do nieprzewidywalnych zachowań podczas kompilacji kodu C jako C++.

Na przykład, w C deklaracje zmiennych muszą znajdować się na początku bloku kodu, podczas gdy w C++ można deklarować zmienne w dowolnym miejscu. Ponadto, C++ wprowadza nowe słowa kluczowe, które mogą kolidować z identyfikatorami używanymi w kodzie C.

#### Typowanie i Bezpieczeństwo

C++ wprowadza silniejsze mechanizmy typowania w porównaniu z C. Na przykład, w C istnieje większa swoboda w konwersji wskaźników między różnymi typami, co może prowadzić do błędów. C++ wymaga jawnych rzutowań i wprowadza zestaw operatorów rzutowania (`static_cast`, `dynamic_cast`, `reinterpret_cast`, `const_cast`), co zwiększa bezpieczeństwo typów.

#### Obsługa Pamięci

W C zarządzanie pamięcią odbywa się za pomocą funkcji `malloc`, `calloc`, `realloc` i `free`. W C++ wprowadzono operatory `new` i `delete`, które nie tylko przydzielają i zwalniają pamięć, ale także wywołują odpowiednie konstruktory i destruktory obiektów. Dodatkowo, C++ oferuje inteligentne wskaźniki (`std::unique_ptr`, `std::shared_ptr`), które automatyzują zarządzanie zasobami i pomagają uniknąć wycieków pamięci.

### Dyrektywy Preprocesora i Załączanie Bibliotek

W obu językach używa się dyrektywy `#include` do załączania plików nagłówkowych. Różnice pojawiają się jednak w sposobie organizacji bibliotek standardowych.

#### W C

W języku C pliki nagłówkowe standardowych bibliotek mają rozszerzenie `.h`. Przykłady:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
```

#### W C++

W C++ standardowe biblioteki są załączane bez rozszerzenia `.h`, a ich nazwy są zdefiniowane w przestrzeni nazw `std`. Dodatkowo, biblioteki C są dostępne z prefiksem `c` i bez rozszerzenia, np.:

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
// Biblioteki z C w C++
#include <cstdio>
#include <cstdlib>
#include <cstring>
```

Używając bibliotek C w C++, należy pamiętać, że ich funkcje są również umieszczone w przestrzeni nazw `std`.

### Słowa Kluczowe

#### Wspólne Słowa Kluczowe

Oba języki dzielą wiele słów kluczowych, które służą do sterowania przepływem programu, deklaracji zmiennych i typów danych:

```c
auto
break
case
char
const
continue
default
do
double
else
enum
extern
float
for
goto
if
int
long
register
return
short
signed
sizeof
static
struct
switch
typedef
union
unsigned
void
volatile
while
```

#### Dodatkowe Słowa Kluczowe w C++

C++ wprowadza szereg nowych słów kluczowych, które wspierają nowe funkcjonalności języka:

```cpp
alignas
alignof
asm
bool
catch
class
const_cast
constexpr
decltype
delete
dynamic_cast
explicit
export
false
friend
inline
mutable
namespace
new
noexcept
nullptr
operator
private
protected
public
reinterpret_cast
static_assert
static_cast
template
this
thread_local
throw
true
try
typeid
typename
using
virtual
wchar_t
```

Każde z tych słów kluczowych ma określoną rolę w języku, np. `class` i `struct` służą do definiowania nowych typów danych, `virtual` umożliwia polimorfizm, a `template` wprowadza programowanie ogólne.

### Zaawansowane Funkcjonalności C++

#### Programowanie Obiektowe

C++ jest językiem wieloparadygmatowym, który wspiera programowanie obiektowe (OOP). OOP wprowadza koncepcje takie jak:

- **Klasy i obiekty** stanowią podstawę programowania obiektowego, gdzie klasy działają jako szablony definiujące atrybuty i metody, z których tworzone są konkretne obiekty.
- **Dziedziczenie** pozwala na tworzenie nowych klas, które dziedziczą właściwości i metody z już istniejących klas, co umożliwia ponowne wykorzystanie kodu.
- **Polimorfizm** umożliwia korzystanie z wskaźników lub referencji do klasy bazowej, które mogą odnosić się do obiektów klas pochodnych, pozwalając na elastyczne zarządzanie różnymi typami obiektów.
- **Enkapsulacja** zapewnia kontrolę dostępu do składowych klasy poprzez ukrywanie szczegółów implementacyjnych i zastosowanie modyfikatorów dostępu, takich jak `private`, `protected` i `public`.

Przykład definicji klasy w C++:

```cpp
class Punkt {
private:
    double x;
    double y;

public:
    Punkt(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    double odlegloscOdPoczatku() const {
        return sqrt(x * x + y * y);
    }

    void przesun(double dx, double dy) {
        x += dx;
        y += dy;
    }
};
```

#### Szablony (Templates)

Szablony umożliwiają tworzenie funkcji i klas generycznych, które mogą działać z różnymi typami danych. Są one podstawą programowania ogólnego w C++.

Przykład szablonu funkcji:

```cpp
template<typename T>
T maksimum(T a, T b) {
    return (a > b) ? a : b;
}
```

Szablon klasy:

```cpp
template<typename T>
class Wektor {
private:
    std::vector<T> dane;

public:
    void dodaj(const T& element) {
        dane.push_back(element);
    }

    T pobierz(int indeks) const {
        return dane[indeks];
    }
};
```

#### Obsługa Wyjątków

C++ wprowadza mechanizm obsługi wyjątków, który pozwala na kontrolowane zarządzanie błędami podczas wykonywania programu.

Przykład użycia wyjątków:

```cpp
double dziel(double a, double b) {
    if (b == 0.0) {
        throw std::runtime_error("Dzielenie przez zero!");
    }
    return a / b;
}

int main() {
    try {
        double wynik = dziel(10.0, 0.0);
    } catch (const std::exception& e) {
        std::cerr << "Wystąpił błąd: " << e.what() << std::endl;
    }
    return 0;
}
```

#### Przeciążanie Funkcji i Operatorów

C++ pozwala na definiowanie wielu funkcji o tej samej nazwie, ale różnych sygnaturach (typach i liczbie argumentów). Przeciążanie operatorów umożliwia definiowanie zachowania operatorów dla obiektów własnych klas.

Przykład przeciążania funkcji:

```cpp
int suma(int a, int b) {
    return a + b;
}

double suma(double a, double b) {
    return a + b;
}
```

Przykład przeciążania operatora:

```cpp
class Liczba {
private:
    int wartosc;

public:
    Liczba(int wartosc) : wartosc(wartosc) {}

    Liczba operator+(const Liczba& inna) const {
        return Liczba(this->wartosc + inna.wartosc);
    }
};
```

#### Referencje

C++ wprowadza referencje, które są alternatywą dla wskaźników i pozwalają na przekazywanie argumentów do funkcji przez referencję, umożliwiając modyfikację oryginalnych danych bez konieczności użycia wskaźników.

Przykład:

```cpp
void zwieksz(int& liczba) {
    liczba++;
}

int main() {
    int x = 5;
    zwieksz(x);
    // x == 6
    return 0;
}
```

### Porównanie Zastosowań i Wydajności

#### Zastosowania Języka C

- **Programowanie systemowe** obejmuje tworzenie systemów operacyjnych, sterowników urządzeń oraz kompilatorów, gdzie wymagana jest niska kontrola nad sprzętem i wydajność.
- **Systemy wbudowane** dotyczą programowania mikrokontrolerów oraz urządzeń IoT, gdzie zasoby są ograniczone, a wydajność kluczowa.
- **Aplikacje o wysokiej wydajności** korzystają z minimalnego narzutu oraz pełnej kontroli nad zarządzaniem pamięcią, co pozwala na maksymalizację wydajności.
- **Nauka podstaw programowania** jest uproszczona dzięki prostocie języka, co ułatwia zrozumienie fundamentalnych konceptów informatyki.

#### Zastosowania Języka C++

- **Aplikacje wielkoskalowe**, takie jak systemy bankowe i aplikacje biznesowe, korzystają z programowania obiektowego, które ułatwia zarządzanie złożonością dużych systemów.
- **Gry i grafika komputerowa** czerpią korzyści z wydajności C++ oraz dostępnych bibliotek, takich jak Unreal Engine, co sprawia, że C++ jest idealnym wyborem w tej dziedzinie.
- **Aplikacje z wymaganiami real-time** mogą korzystać z C++ dzięki możliwości optymalizacji i pełnej kontroli nad zasobami, co jest kluczowe dla tych systemów.
- **Biblioteki i frameworki** tworzone w C++ pozwalają na wykorzystanie szablonów i programowania ogólnego, co umożliwia budowanie uniwersalnych i wydajnych narzędzi.

#### Wydajność

Ogólnie rzecz biorąc, zarówno C, jak i C++ są językami kompilowanymi do kodu maszynowego, co zapewnia wysoką wydajność. Jednakże:

- **Narzut abstrakcji** może wystąpić w C++ w przypadku korzystania z funkcji takich jak wirtualne funkcje, wyjątki czy RTTI, co może prowadzić do dodatkowego narzutu czasowego i pamięciowego.
- **Optymalizacje kompilatora** w nowoczesnych kompilatorach pozwalają na skuteczne optymalizowanie kodu C++, co może znacznie poprawić wydajność aplikacji.
- **Kontrola nad zasobami** w C++ daje możliwość rezygnacji z pewnych funkcji języka, takich jak polimorfizm, w celu osiągnięcia lepszej wydajności, co pozwala na bardziej precyzyjne zarządzanie zasobami.

### Standardy i Rozwój Języków

#### Standardy C

| Standard     | Rok  | Nowości                                                                                           |
|--------------|------|---------------------------------------------------------------------------------------------------|
| **C89/C90**  | 1989 | Pierwszy standard języka, ustanawiający podstawy.                                                  |
| **C99**      | 1999 | Nowe typy całkowite (`stdint.h`), pętle `for` o zmiennym zakresie, funkcje zmiennowymiarowe, komentarze stylu `//`. |
| **C11**      | 2011 | Dodaje obsługę wielowątkowości, anonimowe struktury i unie.                                        |
| **C18**      | 2018 | Głównie poprawki do C11.                                                                           |

#### Standardy C++

| Standard     | Rok  | Nowości                                                                                           |
|--------------|------|---------------------------------------------------------------------------------------------------|
| **C++98/C++03** | 1998/2003 | Pierwsze standardy, wprowadzające szablony, przestrzenie nazw, wyjątki.                     |
| **C++11**       | 2011      | Znaczące rozszerzenia: wyrażenia lambda, `auto`, `nullptr`, inteligentne wskaźniki.         |
| **C++14**       | 2014      | Drobne usprawnienia C++11.                                                                  |
| **C++17**       | 2017      | Nowe biblioteki, `std::optional`, `std::variant`, składnia `if constexpr`.                  |
| **C++20**       | 2020      | Koncepty, moduły, zakresy (ranges), korutyny.                                               |

### Matematyczne Aspekty Języków

#### Typy Danych i Arytmetyka

Oba języki oferują podstawowe typy danych, takie jak `int`, `float`, `double`, `char`. Jednak C++ wprowadza dodatkowe typy, np. `bool` (w C typ logiczny jest symulowany za pomocą `int`).

Arytmetyka w obu językach podlega tym samym regułom, ale C++ umożliwia przeciążanie operatorów, co pozwala na definiowanie własnych typów numerycznych z zachowaniem naturalnej składni.

Przykład przeciążania operatorów dla liczb zespolonych:

```cpp
class Zespolona {
private:
    double re, im;

public:
    Zespolona(double re = 0.0, double im = 0.0) : re(re), im(im) {}

    Zespolona operator+(const Zespolona& z) const {
        return Zespolona(re + z.re, im + z.im);
    }

    Zespolona operator*(const Zespolona& z) const {
        return Zespolona(re * z.re - im * z.im, re * z.im + im * z.re);
    }
};
```

#### Programowanie Generyczne i Koncepty

C++ umożliwia tworzenie algorytmów generycznych za pomocą szablonów, co jest zbliżone do parametrów typów w matematyce. Wprowadzenie konceptów w C++20 pozwala na definiowanie wymagań dla parametrów szablonów, co zwiększa bezpieczeństwo i czytelność kodu.

Przykład konceptu:

```cpp
template<typename T>
concept Liczba = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
    { a / b } -> std::convertible_to<T>;
};

template<Liczba T>
T suma(T a, T b) {
    return a + b;
}
```
