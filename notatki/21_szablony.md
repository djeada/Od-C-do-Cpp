# Szablony

Szablon jest przepisem na funkcję lub typ, który działa dla wielu typów albo wartości. Zamiast pisać osobną funkcję `max2_int`, `max2_double` i `max2_string`, zapisujemy wspólną regułę raz, a kompilator tworzy potrzebną wersję, gdy szablon jest użyty.

Szablon nie oznacza, że program sprawdza typ w czasie działania. Kompilator podstawia konkretne argumenty szablonu i sprawdza wynikowy kod podczas kompilacji. To pozwala zachować informacje o typach, ale oznacza też, że wymagania dla typu muszą być spełnione, a błędy często pojawiają się dopiero przy użyciu szablonu.

## Szablon funkcji: definicja, wnioskowanie i instancjowanie

Rozważmy funkcję wybierającą większą z dwóch wartości:

```cpp
template <typename T>
T max2(T a, T b) {
    return a < b ? b : a;
}

int liczba = max2(10, 20);
double pomiar = max2<double>(16.2, 3.14);
```

Czytamy to w trzech krokach:

1. `template <typename T>` mówi, że `T` jest parametrem typu. Zapis `class T` byłby w tym miejscu równoważny.
2. W `max2(T a, T b)` typ obu parametrów zależy od `T`. Funkcja ma zwracać wartość tego samego typu.
3. Przy `max2(10, 20)` oba argumenty mają typ `int`, więc kompilator wnioskuje `T = int` i sprawdza wersję odpowiadającą `int max2(int, int)`. Przy `max2<double>(...)` argument szablonu jest podany jawnie: `T = double`.

To tworzenie wersji dla konkretnych argumentów nazywa się **instancjowaniem** szablonu. Kompilator nie tworzy automatycznie wersji dla wszystkich możliwych typów, tylko dla tych, których używa program i których kod da się poprawnie utworzyć.

### Dlaczego różne typy argumentów mogą dać błąd

To wywołanie jest błędne:

```cpp
// auto wynik = max2(1, 2.0);
```

Pierwszy argument sugeruje `T = int`, a drugi `T = double`. Kompilator najpierw próbuje wywnioskować jeden typ szablonu wspólny dla obu parametrów; nie wybiera samodzielnie `double` tylko dlatego, że zwykłe dodawanie `int` i `double` jest możliwe.

Jeśli chcemy, by oba argumenty były traktowane jako `double`, możemy podać typ jawnie:

```cpp
double wynik = max2<double>(1, 2.0);  // int 1 zostaje przekonwertowane na double
```

Możemy też zaprojektować szablon tak, by miał osobny parametr dla każdego argumentu. Wtedy trzeba określić, jaki typ ma mieć wynik i czy oba typy w ogóle można porównać. Wnioskowanie argumentów szablonu nie jest tym samym co automatyczne znalezienie „najlepszego wspólnego typu”.

### Jakie wymagania ma typ T

W szablonie `max2` kompilator sprawdza, czy:

- wyrażenie `a < b` jest poprawne i jego wynik da się użyć jako warunku;
- argumenty można przekazać przez wartość jako `T` (dla argumentu będącego l-wartością może być potrzebne kopiowanie);
- wybrana wartość (`a` albo `b`) może zostać zwrócona jako `T`.

Dla `int` te warunki są spełnione. W tym konkretnym kodzie `a < b ? b : a` wybiera jedną z dwóch nazwanych zmiennych typu `T`, a wyrażenie warunkowe zachowuje typ `T`. Funkcja zwraca wynik przez wartość, więc kopiuje wybrany parametr. Dlatego `T` musi umożliwiać takie kopiowanie; dla własnej klasy bez operatora `<` instancjowanie również zakończy się błędem. Jeśli typ jest kosztowny do kopiowania, przekazywanie i zwracanie przez wartość może być niepożądane. Zmiana parametrów na referencje może ograniczyć kopie, ale zwrócenie referencji do lokalnej zmiennej stworzyłoby wiszącą referencję. Sam zapis szablonu nie gwarantuje, że każdy typ ma potrzebne operacje ani że ich znaczenie jest takie, jakiego oczekuje autor.

Szablon funkcji najczęściej umieszcza się w nagłówku razem z definicją. Kompilator musi zwykle widzieć ciało w miejscu, w którym instancjuje wersję dla nowego typu. Istnieją jawne instancjowania i inne organizacje kodu, ale dla typowych szablonów bibliotecznych nagłówek jest najprostszym rozwiązaniem.

## Jawne ograniczenia: koncepcje w C++20

Koncepcja nazywa wymagania dla parametru szablonu. Przykład ogranicza T do typów całkowitych:

```cpp
#include <concepts>

template <std::integral T>
T dodaj(T a, T b) {
    return a + b;
}
```

Próba wywołania `dodaj(1.5, 2.5)` nie spełnia ograniczenia `std::integral`. Koncepcja pomaga kompilatorowi zgłosić błąd w miejscu użycia i opisuje zamierzony zakres funkcji.

Ograniczenie opisuje kategorię typu, ale nie gwarantuje poprawności każdej wartości. Na przykład dodanie dwóch `int` nadal może przepełnić zakres typu ze znakiem, co w C++ prowadzi do niezdefiniowanego zachowania. Koncepcje nie zastępują sprawdzania zakresów ani dokumentowania wymagań semantycznych.

## Szablony klas

Szablon może opisywać własny typ parametryzowany typem. Poniższe pudełko przechowuje wartość typu T:

```cpp
#include <string>

template <typename T>
class Pudelko {
public:
    explicit Pudelko(const T &wartosc) : wartosc_(wartosc) {}

    const T &pobierz() const {
        return wartosc_;
    }

private:
    T wartosc_;
};

Pudelko<int> liczba{42};
Pudelko<std::string> tekst{"Witaj"};
```

`Pudelko<int>` i `Pudelko<std::string>` to różne, konkretne typy utworzone z jednego przepisu. Pierwszy przechowuje `int`, drugi `std::string`. Ten szablon wymaga, by `T` można było skopiować z `const T&`, bo konstruktor kopiuje parametr do pola `wartosc_`. Jeśli użyjemy typu, którego nie można tak skopiować, instancjowanie konstruktora nie powiedzie się.

Od C++17 kompilator potrafi w wielu sytuacjach wywnioskować argument szablonu klasy z argumentów konstruktora:

```cpp
Pudelko calkowite{42};  // C++17: wniosek Pudelko<int>
```

Jawny zapis `Pudelko<int>` nadal bywa czytelniejszy, zwłaszcza gdy typ nie wynika jasno z konstruktora.

## Parametry będące wartościami

Parametrem szablonu może być również wartość znana podczas kompilacji, np. rozmiar tablicy:

```cpp
#include <array>
#include <cstddef>

template <typename T, std::size_t N>
struct Tablica {
    std::array<T, N> elementy{};
};

Tablica<int, 5> liczby;
```

W Tablica<int, 5> parametrem typu jest T = int, a parametrem wartości N = 5. Kompilator tworzy typ zawierający std::array<int, 5>. N nie jest rozmiarem, który można zmienić w czasie działania programu; jest częścią typu i musi być znany podczas kompilacji. std::array<T, N> obsługuje także N == 0.

Parametrom szablonu klasy można przypisać wartości domyślne:

```cpp
#include <array>
#include <cstddef>

template <typename T = int, std::size_t N = 10>
struct Bufor {
    std::array<T, N> elementy{};
};

Bufor<> domyslny;            // Bufor<int, 10>
Bufor<double, 5> maly;       // Bufor<double, 5>
```

Nawiasy `<>` przy `Bufor<>` oznaczają tu: użyj wartości domyślnych. Wartości parametrów szablonu podlegają regułom języka; `std::size_t` z rozmiarem tablicy jest typowym przykładem parametru całkowitoliczbowego.

## Specjalizacje

Czasem ogólna reguła nie pasuje do jednego typu albo rodziny typów. **Specjalizacja** podaje dla nich odrębną definicję.

Specjalizacja pełna dotyczy dokładnie wskazanego typu:

```cpp
#include <string>

template <typename T>
struct CzyTekst {
    static constexpr bool wartosc = false;
};

template <>
struct CzyTekst<std::string> {
    static constexpr bool wartosc = true;
};

static_assert(!CzyTekst<int>::wartosc, "int nie jest tekstem");
static_assert(CzyTekst<std::string>::wartosc, "std::string jest tekstem");
```

Ogólna wersja ustawia `wartosc` na `false`; dla dokładnego typu `std::string` wybierana jest specjalizacja pełna i wartość wynosi `true`.

Specjalizacja częściowa opisuje rodzinę typów, na przykład wszystkie wskaźniki:

```cpp
template <typename T>
struct CzyWskaznik {
    static constexpr bool wartosc = false;
};

template <typename T>
struct CzyWskaznik<T *> {
    static constexpr bool wartosc = true;
};

static_assert(!CzyWskaznik<int>::wartosc, "int nie jest wskaznikiem");
static_assert(CzyWskaznik<int *>::wartosc, "int* jest wskaznikiem");
```

`CzyWskaznik<int *>` dopasowuje się do wzorca `T *` z `T = int`, dlatego wybiera wersję częściową. Specjalizację należy zadeklarować przed użyciem wymagającym tej konkretnej wersji.

Szablonów funkcji nie specjalizuje się częściowo. Gdy zachowanie funkcji ma zależeć od wariantu argumentów, zwykle używa się przeciążenia funkcji — temat przeciążania pojawił się w poprzedniej notatce.

## Aliasy i zmienne szablonowe

Alias szablonu (C++11) nadaje krótszą nazwę typowi zależnemu od parametru:

```cpp
#include <vector>

template <typename T>
using Wektor = std::vector<T>;

Wektor<int> liczby;
```

Szablon zmiennej (C++14) pozwala definiować wartość zależną od typu:

```cpp
template <typename T>
constexpr T pi = static_cast<T>(3.14159265358979323846L);

double promien = pi<double>;
```

Tutaj `pi<double>` oznacza wartość typu `double`. Konwersja do typu `T` może ograniczyć precyzję; szablon zmiennej nie tworzy jednej uniwersalnej wartości o identycznej dokładności dla wszystkich typów.

## Szablony w bibliotece standardowej

W standardowej bibliotece szablony pozwalają używać tych samych kontenerów i algorytmów z różnymi typami. Na przykład `std::vector<int>` i `std::vector<std::string>` są różnymi typami, ale korzystają z tej samej rodziny szablonów. Algorytm `std::sort` również jest szablonem i może przyjąć lambdę jako komparator. Jej typ domknięcia jest znany podczas kompilacji, więc typowa lambda może być przekazana bez opakowywania jej w `std::function`.

To łączy szablony z poprzednią notatką o lambdach: szablon pozwala algorytmowi przyjąć obiekt dowolnego typu, o ile ten obiekt spełnia wymagania algorytmu.

## Szablony o zmiennej liczbie argumentów

Szablon wariadyczny przyjmuje pakiet argumentów, którego liczba i typy mogą być różne. Od C++17 można użyć wyrażenia zwijającego (*fold expression*) do połączenia operacji dla wszystkich argumentów:

```cpp
#include <iostream>

template <typename... Args>
void wypisz(Args... args) {
    (std::cout << ... << args) << '\n';
}

int main() {
    wypisz(1, 2, 3);  // wypisuje 123 i koniec wiersza
    return 0;
}
```

`typename... Args` nazywa pakiet typów, a `Args... args` odpowiadający mu pakiet parametrów funkcji. Fold expression (`std::cout << ... << args`) składa operator `<<` dla wszystkich argumentów. Ten przykład wymaga co najmniej jednego argumentu; pakiet pusty nie ma tu wartości początkowej. Można dodać osobną wersję dla zera argumentów, jeśli ma być obsługiwana.

Każdy typ argumentu musi obsługiwać wypisywanie przez `std::cout << argument`. Parametry są tu przekazywane przez wartość, więc dla dużych obiektów może to oznaczać niepotrzebne kopiowanie; w ogólnym kodzie sposób przekazywania argumentów dobiera się do ich typów i czasu życia.

Szablony wariadyczne przydają się m.in. przy przekazywaniu argumentów dalej i budowaniu narzędzi ogólnego przeznaczenia. Ponieważ każdy zestaw typów tworzy inną instancję, wiele różnorodnych wywołań może wydłużyć kompilację.

## Co naprawdę dzieje się podczas kompilacji

Szablony są sprawdzane i instancjowane przez kompilator, ale samo użycie szablonu nie oznacza, że programowe obliczenie wykona się podczas kompilacji. Funkcja szablonowa może zostać instancjowana, a następnie wywoływana w czasie działania programu.

Do obliczeń, które *mogą* być wykonane podczas kompilacji, służy m.in. `constexpr`:

```cpp
constexpr int kwadrat(int x) {
    return x * x;
}

static_assert(kwadrat(5) == 25, "kwadrat 5 ma wartosc 25");  // Wynik musi być znany podczas kompilacji

int obliczWynik(int wejscie) {
    return kwadrat(wejscie);      // Wynik oblicza program podczas działania
}
```

`constexpr` pozwala wywołać funkcję w kontekście stałego wyrażenia, jeśli argumenty i całe obliczenie spełniają wymagania. Nie oznacza, że każde jej wywołanie musi nastąpić podczas kompilacji. Tutaj `static_assert` wymaga wyniku znanego podczas kompilacji, a parametr `wejscie` może mieć wartość znaną dopiero podczas działania programu, więc wynik wywołania `obliczWynik` jest obliczany w czasie działania. Zwykłe ograniczenia typu nadal obowiązują: mnożenie zbyt dużych wartości `int` może przepełnić zakres. Od C++20 `consteval` służy do funkcji, których wywołania muszą być obliczane podczas kompilacji.

### Rekurencyjne metaprogramowanie szablonowe

Starszym, edukacyjnym sposobem obliczania wartości podczas kompilacji jest rekurencyjne instancjowanie szablonu:

```cpp
template <unsigned N>
struct Silnia {
    static constexpr unsigned long long wartosc =
        N * Silnia<N - 1>::wartosc;
};

template <>
struct Silnia<0> {
    static constexpr unsigned long long wartosc = 1;
};

static_assert(Silnia<5>::wartosc == 120, "silnia 5 ma wartosc 120");
```

Aby ustalić `Silnia<5>::wartosc`, kompilator potrzebuje `Silnia<4>`, potem `Silnia<3>`, aż do `Silnia<0>`. Specjalizacja dla zera jest przypadkiem bazowym, który kończy rekurencję. Dla dużego `N` takie podejście może wyczerpać limit instancjowania kompilatora. Ponadto `unsigned long long` ma ograniczony zakres: przepełnienie jest zawijane modulo zakres typu i przestaje oznaczać matematyczną silnię. W zwykłym kodzie czytelniejsza funkcja `constexpr` często jest lepsza niż rekurencyjne metaprogramowanie.

## Ograniczenia i dobre zastosowania

- Błąd wymaganej operacji, np. brak `operator<`, ujawnia się dopiero wtedy, gdy kompilator instancjuje szablon dla typu, który jej nie obsługuje.
- Każdy potrzebny zestaw argumentów tworzy instancję; wiele kombinacji może zwiększyć czas kompilacji i rozmiar programu.
- Warto jasno opisać operacje i zachowanie wymagane od parametrów. Koncepcje C++20 mogą wyrazić część tych wymagań w kodzie.
- Korzystaj z szablonu, gdy jedna reguła ma działać dla wielu typów. Jeśli typów jest niewiele albo warianty zachowania są różne, przeciążenia mogą być czytelniejsze.
- Szablony są podstawą kontenerów i algorytmów biblioteki standardowej, ale nie są automatyczną optymalizacją. Koszt i jakość wygenerowanego programu zależą od implementacji oraz użycia.
