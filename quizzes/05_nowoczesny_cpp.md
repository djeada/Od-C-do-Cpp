# Nowoczesny C++: lambdy, szablony, wyjątki, STL i pliki — quiz

Notatki: [Lambdy](../notatki/20_lambdy.md), [Szablony](../notatki/21_szablony.md), [Wyjątki](../notatki/22_wyjatki.md), [STL](../notatki/23_stl.md), [Praca z plikami](../notatki/24_praca_z_plikami.md), [C vs C++](../notatki/25_c_vs_cpp.md)

Sprawdź, czy rozumiesz przechwytywanie w lambdach, instancjowanie szablonów, przepływ wyjątków, kontenery i algorytmy STL, pracę z plikami oraz najważniejsze różnice między C a C++.

#### Q. Co wypisze ten program w C++ z lambdami przechwytującymi przez wartość i przez referencję?

```cpp
#include <iostream>

int main() {
    int licznik = 10;
    auto kopia = [licznik] { return licznik; };
    auto odwolanie = [&licznik] { return licznik; };
    licznik = 20;
    std::cout << kopia() << ' ' << odwolanie() << '\n';
}
```

* [ ] `10 10`
* [ ] `20 20`
* [x] `10 20`
* [ ] `20 10`

> **Wyjaśnienie:** `[licznik]` kopiuje wartość do domknięcia w chwili tworzenia lambdy, więc późniejsza zmiana jej nie dotyczy. `[&licznik]` odwołuje się do istniejącej zmiennej i odczytuje bieżące 20.

#### Q. Co wypisze ten program w C++ z lambdą oznaczoną `mutable`?

```cpp
#include <iostream>

int main() {
    int n = 0;
    auto f = [n]() mutable { return ++n; };
    f();
    f();
    std::cout << f() << ' ' << n << '\n';
}
```

* [ ] `3 3`
* [x] `3 0`
* [ ] `1 0`
* [ ] `1 1`

> **Wyjaśnienie:** `mutable` pozwala zmieniać kopię przechowywaną w domknięciu, a ta sama lambda pamięta swój stan między wywołaniami. Pierwotna zmienna `n` pozostaje równa 0.

#### Q. Co można powiedzieć o wywołaniu lambdy zwróconej przez funkcję `stworz` w tym programie?

```cpp
#include <iostream>

auto stworz() {
    int lokalna = 7;
    return [&lokalna] { return lokalna; };
}

int main() {
    auto odczyt = stworz();
    std::cout << odczyt() << '\n';
}
```

* [ ] Zawsze zwróci `7`
* [x] Ma niezdefiniowane zachowanie
* [ ] Program się nie skompiluje
* [ ] Zawsze zwróci `0`

> **Wyjaśnienie:** Lambda przechowuje referencję do `lokalna`, która przestaje istnieć po wyjściu ze `stworz`. Przechwycenie przez referencję nie przedłuża życia zmiennej; tutaj należało skopiować wartość przez `[lokalna]`.

#### Q. Co wypisze ten program w C++ porównujący typy dwóch identycznie zapisanych lambd?

```cpp
#include <iostream>
#include <type_traits>

int main() {
    auto a = [](int x) { return x + 1; };
    auto b = [](int x) { return x + 1; };
    std::cout << std::is_same_v<decltype(a), decltype(b)> << ' ' << a(1) + b(1) << '\n';
}
```

* [ ] `1 4`
* [x] `0 4`
* [ ] `1 2`
* [ ] `0 2`

> **Wyjaśnienie:** Każde wyrażenie lambda tworzy własny, unikalny typ domknięcia, nawet przy identycznym zapisie. Obie lambdy działają tak samo, więc suma wyników to $2 + 2 = 4$.

#### Q. Co wypisze ten program w C++ z lambdą generyczną?

```cpp
#include <iostream>
#include <string>

int main() {
    auto suma = [](auto a, auto b) { return a + b; };
    std::cout << suma(2, 3) << ' ' << suma(std::string("a"), "b") << '\n';
}
```

* [x] `5 ab`
* [ ] `5 a`
* [ ] Błąd: `a` i `b` muszą mieć ten sam typ
* [ ] `23 ab`

> **Wyjaśnienie:** Parametry `auto` (C++14) tworzą szablonowy operator wywołania instancjowany osobno dla każdego zestawu typów. Dla `int` wyrażenie `a + b` dodaje liczby, a dla `std::string` i literału skleja tekst.

#### Q. Dlaczego komparator `[](int a, int b) { return a >= b; }` przekazany do `std::sort` jest błędny?

* [ ] Bo `std::sort` przyjmuje tylko funkcje, a nie lambdy
* [x] Bo dla równych elementów twierdzi, że element jest przed samym sobą
* [ ] Bo sortuje rosnąco zamiast malejąco
* [ ] Bo lambda bez przechwyceń nie może porównywać liczb

> **Wyjaśnienie:** Komparator musi spełniać ścisły słaby porządek: `comp(a, a)` musi być fałszywe. Do sortowania malejąco poprawny jest warunek `a > b`.

#### Q. Co wypisze ten program w C++ z funkcją zwracającą lambdę?

```cpp
#include <iostream>

auto stworzMnoznik(int mnoznik) {
    return [mnoznik](int x) { return x * mnoznik; };
}

int main() {
    auto razy3 = stworzMnoznik(3);
    std::cout << razy3(razy3(2)) << '\n';
}
```

* [ ] `6`
* [ ] `9`
* [x] `18`
* [ ] `12`

> **Wyjaśnienie:** Domknięcie przechowuje własną kopię `mnoznik == 3`, więc jest bezpieczne po zakończeniu funkcji. `razy3(2)` daje 6, a `razy3(6)` daje 18.

#### Q. Co przechwytuje lambda zapisana w metodzie klasy jako `[this] { return pole_; }`?

* [ ] Kopię całego bieżącego obiektu
* [x] Wskaźnik do bieżącego obiektu, bez kopii
* [ ] Tylko kopię składowej `pole_`
* [ ] Referencję do wszystkich zmiennych lokalnych

> **Wyjaśnienie:** `[this]` zachowuje wskaźnik, więc wywołanie lambdy po zniszczeniu obiektu użyje wiszącego `this`. Kopię obiektu daje od C++17 zapis `[*this]`.

#### Q. Co wypisze ten program w C++, w którym lambda z pustą listą przechwyceń używa zmiennej globalnej?

```cpp
#include <iostream>

int g = 1;

int main() {
    auto f = [] { return g * 10; };
    g = 5;
    std::cout << f() << '\n';
}
```

* [ ] `10`
* [x] `50`
* [ ] Błąd: `[]` nie pozwala użyć `g`
* [ ] `0`

> **Wyjaśnienie:** Przechwytuje się tylko zmienne automatyczne (lokalne). Zmienną globalną lambda odczytuje bezpośrednio w chwili wywołania, więc widzi już wartość 5.

#### Q. Co się stanie przy kompilacji tego programu w C++ z szablonem `max2` wywołanym dla `int` i `double`?

```cpp
template <typename T>
T max2(T a, T b) {
    return a < b ? b : a;
}

int main() {
    auto w = max2(1, 2.0);
    return static_cast<int>(w);
}
```

* [ ] `T` zostanie wywnioskowane jako `double`
* [ ] `T` zostanie wywnioskowane jako `int`
* [x] Błąd: sprzeczne typy wywnioskowane dla `T`
* [ ] Błąd dopiero podczas działania programu

> **Wyjaśnienie:** Pierwszy argument sugeruje `T = int`, a drugi `T = double`; wnioskowanie nie szuka „wspólnego” typu. Pomaga jawny zapis `max2<double>(1, 2.0)` lub dwa osobne parametry szablonu.

#### Q. Co wypisze ten program w C++ ze specjalizacją częściową szablonu?

```cpp
#include <iostream>

template <typename T>
struct CzyWskaznik {
    static constexpr bool wartosc = false;
};

template <typename T>
struct CzyWskaznik<T*> {
    static constexpr bool wartosc = true;
};

int main() {
    std::cout << CzyWskaznik<int*>::wartosc
              << CzyWskaznik<int>::wartosc
              << CzyWskaznik<int**>::wartosc << '\n';
}
```

* [x] `101`
* [ ] `100`
* [ ] `111`
* [ ] `001`

> **Wyjaśnienie:** `int*` pasuje do wzorca `T*` z `T = int`, a `int**` — z `T = int*`. Zwykłe `int` nie jest wskaźnikiem, więc wybierana jest ogólna wersja z wartością `false`.

#### Q. Czy `Tablica<int, 5>` i `Tablica<int, 6>`, utworzone z szablonu `template <typename T, std::size_t N> struct Tablica`, to ten sam typ?

* [ ] Tak — rozmiar ustala się dopiero w czasie działania
* [ ] Tak — liczy się tylko typ elementów `T`
* [x] Nie — wartość `N` jest częścią typu
* [ ] Nie — ale można je dowolnie przypisywać do siebie

> **Wyjaśnienie:** Parametr będący wartością musi być znany podczas kompilacji i należy do typu, tak jak w `std::array<int, 5>`. Różne `N` dają różne, niezależne instancje szablonu.

#### Q. Co wypisze ten program w C++17 z wyrażeniem zwijającym?

```cpp
#include <iostream>

template <typename... Args>
void wypisz(Args... args) {
    (std::cout << ... << args) << '\n';
}

int main() {
    wypisz(1, 'a', 2.5);
}
```

* [x] `1a2.5`
* [ ] `1 a 2.5`
* [ ] `1972.5`
* [ ] Błąd: argumenty mają różne typy

> **Wyjaśnienie:** Wyrażenie zwijające składa `std::cout << 1 << 'a' << 2.5`, bez dodatkowych separatorów. `char` jest wypisywany jako znak, a pakiet może zawierać argumenty różnych typów.

#### Q. Co się stanie przy wywołaniu `dodaj(1.5, 2.5)` dla szablonu `template <std::integral T> T dodaj(T a, T b)`?

* [ ] Zwróci `4.0`
* [ ] Zwróci `3` po obcięciu części ułamkowych
* [x] Błąd kompilacji: `double` nie spełnia `std::integral`
* [ ] Zgłosi wyjątek podczas działania programu

> **Wyjaśnienie:** Koncepcja `std::integral` (C++20) dopuszcza tylko typy całkowite, a z argumentów wynika `T = double`. Kompilator odrzuca wywołanie w miejscu użycia, z czytelnym komunikatem.

#### Q. Która deklaracja funkcji w C++20 wymaga, aby każde jej wywołanie zostało obliczone podczas kompilacji?

* [ ] `constexpr int f(int x);`
* [x] `consteval int f(int x);`
* [ ] `inline int f(int x);`
* [ ] `static int f(int x);`

> **Wyjaśnienie:** `consteval` oznacza funkcję natychmiastową, której wywołania muszą dać stałe wyrażenie. Funkcja `constexpr` może być obliczona podczas kompilacji, ale można ją też wywołać w czasie działania z argumentami nieznanymi wcześniej.

#### Q. Co wypisze ten program w C++ z domyślnymi argumentami szablonu?

```cpp
#include <array>
#include <cstddef>
#include <iostream>

template <typename T = int, std::size_t N = 10>
struct Bufor {
    std::array<T, N> elementy{};
};

int main() {
    Bufor<> domyslny;
    Bufor<double, 5> maly;
    std::cout << domyslny.elementy.size() << ' ' << maly.elementy.size() << '\n';
}
```

* [x] `10 5`
* [ ] `0 5`
* [ ] `10 10`
* [ ] Błąd: brak argumentów szablonu w `Bufor<>`

> **Wyjaśnienie:** Puste nawiasy `Bufor<>` oznaczają użycie wartości domyślnych, czyli `Bufor<int, 10>`. Drugi obiekt jawnie podaje `T = double` i `N = 5`.

#### Q. Co wypisze ten program w C++, w którym wyjątek przechodzi przez kilka funkcji?

```cpp
#include <iostream>
#include <stdexcept>

struct Slad {
    const char* n;
    ~Slad() { std::cout << '~' << n << ' '; }
};

void c() {
    Slad s{"c"};
    throw std::runtime_error("x");
}

void b() {
    Slad s{"b"};
    c();
    std::cout << "po_c ";
}

int main() {
    try {
        Slad s{"try"};
        b();
    } catch (const std::exception& e) {
        std::cout << "catch:" << e.what();
    }
    std::cout << '\n';
}
```

* [x] `~c ~b ~try catch:x`
* [ ] `catch:x ~c ~b ~try`
* [ ] `~try ~b ~c catch:x`
* [ ] `~c ~b po_c ~try catch:x`

> **Wyjaśnienie:** Podczas rozwijania stosu niszczone są obiekty lokalne kolejnych opuszczanych funkcji i bloku `try`, zanim zacznie działać `catch`. Instrukcja po `c()` nie wykonuje się, bo wyjątek przerwał `b`.

#### Q. Co wypisze ten program w C++ z dwoma blokami `catch`?

```cpp
#include <iostream>
#include <stdexcept>
#include <string>

class BladFormatu : public std::runtime_error {
public:
    explicit BladFormatu(const std::string& opis) : std::runtime_error(opis) {}
};

int main() {
    try {
        throw BladFormatu("zły nagłówek");
    } catch (const std::exception&) {
        std::cout << "std::exception\n";
    } catch (const BladFormatu&) {
        std::cout << "BladFormatu\n";
    }
}
```

* [x] `std::exception`
* [ ] `BladFormatu`
* [ ] Oba napisy, każdy w osobnym wierszu
* [ ] Błąd kompilacji: nieosiągalny blok `catch`

> **Wyjaśnienie:** Bloki `catch` są sprawdzane po kolei, a `std::exception&` pasuje także do typu pochodnego. Bardziej szczegółowe typy umieszcza się przed bazowymi — kompilator tylko ostrzega o nieosiągalnym bloku.

#### Q. W bloku `try { int z = 10 / zero; }` z `catch (...)` zmienna `zero` typu `int` ma wartość 0. Co się stanie?

* [ ] `catch (...)` przechwyci wyjątek `std::domain_error`
* [ ] Zmienna `z` otrzyma wartość 0
* [x] Niezdefiniowane zachowanie — C++ nie zgłasza tu wyjątku
* [ ] Zmienna `z` otrzyma wartość „nieskończoność”

> **Wyjaśnienie:** C++ nie zamienia automatycznie błędów, takich jak całkowite dzielenie przez zero, w wyjątki. Aby obsłużyć ten przypadek wyjątkiem, trzeba najpierw sprawdzić dzielnik i samodzielnie wykonać `throw`.

#### Q. Co wypisze ten program w C++, który ponownie zgłasza wyjątek zapisem `throw e;`?

```cpp
#include <iostream>
#include <stdexcept>
#include <string>

class BladFormatu : public std::runtime_error {
public:
    explicit BladFormatu(const std::string& opis) : std::runtime_error(opis) {}
};

int main() {
    try {
        try {
            throw BladFormatu("f");
        } catch (const std::exception& e) {
            throw e;
        }
    } catch (const BladFormatu&) {
        std::cout << "format\n";
    } catch (const std::exception&) {
        std::cout << "ogólny\n";
    }
}
```

* [ ] `format`
* [x] `ogólny`
* [ ] `format`, a potem `ogólny`
* [ ] Program kończy się przez `std::terminate()`

> **Wyjaśnienie:** `throw e;` tworzy nowy wyjątek na podstawie statycznego typu `e`, czyli `std::exception`, więc informacja o typie pochodnym ginie. Samo `throw;` przekazałoby dalej oryginalny `BladFormatu`.

#### Q. Co się stanie, gdy wyjątek opuści funkcję `main` i nigdzie nie zostanie przechwycony?

* [ ] `main` zwróci kod 0
* [ ] Wyjątek zostanie zignorowany
* [x] Program zakończy się przez `std::terminate()`
* [ ] Program uruchomi `main` ponownie

> **Wyjaśnienie:** Nieobsłużony wyjątek kończy program wywołaniem `std::terminate()`. Nie należy zakładać, że po takim zdarzeniu program działa dalej ani że destruktory wszystkich obiektów zostały wywołane.

#### Q. Co wypisze ten program w C++ konwertujący tekst funkcją `std::stoi`?

```cpp
#include <iostream>
#include <stdexcept>
#include <string>

int main() {
    try {
        int v = std::stoi("abc");
        std::cout << v << '\n';
    } catch (const std::invalid_argument&) {
        std::cout << "zły format\n";
    } catch (const std::out_of_range&) {
        std::cout << "poza zakresem\n";
    }
}
```

* [ ] `0`
* [x] `zły format`
* [ ] `poza zakresem`
* [ ] Nieokreśloną liczbę

> **Wyjaśnienie:** Gdy tekst nie zaczyna się od liczby, `std::stoi` zgłasza `std::invalid_argument`. `std::out_of_range` pojawiłby się dla liczby spoza zakresu `int`.

#### Q. Co wypisze ten program w C++ modyfikujący `std::vector`?

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3};
    v.insert(v.begin() + 1, 10);
    v.push_back(4);
    v.erase(v.begin());
    for (int x : v) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}
```

* [ ] `1 10 2 3`
* [x] `10 2 3 4`
* [ ] `1 2 3 4`
* [ ] `10 1 2 3 4`

> **Wyjaśnienie:** `insert` przed indeksem 1 daje `{1, 10, 2, 3}`, `push_back` dopisuje 4, a `erase(v.begin())` usuwa pierwszy element. Zostaje `{10, 2, 3, 4}`.

#### Q. Co wypisze ten program w C++ z metodami `reserve` i `resize`?

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v;
    v.reserve(10);
    std::cout << v.size() << ' ' << (v.capacity() >= 10) << ' ';
    v.resize(3);
    std::cout << v.size() << ' ' << v[2] << '\n';
}
```

* [ ] `10 1 3 0`
* [x] `0 1 3 0`
* [ ] `0 1 13 0`
* [ ] `10 1 10 0`

> **Wyjaśnienie:** `reserve` zwiększa tylko pojemność i nie tworzy elementów, więc rozmiar wciąż wynosi 0. Dopiero `resize(3)` tworzy trzy elementy z wartością 0.

#### Q. Co wypisze ten program w C++ sprawdzający klucz w `std::map` operatorem `[]`?

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> m;
    if (m["kot"] == 0) {
        std::cout << "brak ";
    }
    std::cout << m.size() << ' ' << m.count("pies") << '\n';
}
```

* [ ] `brak 0 0`
* [x] `brak 1 0`
* [ ] `1 0`
* [ ] `brak 1 1`

> **Wyjaśnienie:** Gdy klucza nie ma, `m["kot"]` wstawia go z wartością domyślną 0, więc mapa ma już jeden element. `count` (podobnie jak `find` i `contains`) tylko sprawdza i niczego nie dodaje.

#### Q. Co wypisze ten program w C++ iterujący po `std::map`?

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> m{{"pies", 1}, {"kot", 2}, {"ara", 3}};
    for (const auto& para : m) {
        std::cout << para.first << ' ';
    }
    std::cout << '\n';
}
```

* [ ] `pies kot ara`
* [x] `ara kot pies`
* [ ] `pies ara kot`
* [ ] Kolejność nie jest określona

> **Wyjaśnienie:** `std::map` utrzymuje klucze w porządku sortowania, więc iteracja przebiega alfabetycznie. Kolejności wstawiania nie gwarantuje ani `map`, ani `unordered_map`, który nie zachowuje żadnego porządku.

#### Q. Co wypisze ten program w C++ z algorytmem `std::remove_if` bez `erase`?

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    auto nowy_koniec = std::remove_if(v.begin(), v.end(),
                                      [](int x) { return x % 2 == 0; });
    std::cout << v.size() << ' ' << (nowy_koniec - v.begin()) << ' '
              << v[0] << v[1] << v[2] << '\n';
}
```

* [ ] `3 3 135`
* [x] `6 3 135`
* [ ] `6 6 123`
* [ ] `3 6 135`

> **Wyjaśnienie:** `remove_if` przesuwa elementy do zachowania na początek i zwraca nowy koniec, ale nie zmienia rozmiaru kontenera. Końcówkę usuwa dopiero `v.erase(nowy_koniec, v.end())`.

#### Q. Co wypisze ten program w C++ z adapterami `queue`, `stack` i `priority_queue`?

```cpp
#include <iostream>
#include <queue>
#include <stack>

int main() {
    std::queue<int> q;
    std::stack<int> s;
    std::priority_queue<int> p;
    for (int x : {3, 1, 2}) {
        q.push(x);
        s.push(x);
        p.push(x);
    }
    std::cout << q.front() << ' ' << s.top() << ' ' << p.top() << '\n';
}
```

* [x] `3 2 3`
* [ ] `2 3 3`
* [ ] `3 2 1`
* [ ] `1 2 3`

> **Wyjaśnienie:** Kolejka (FIFO) pokazuje pierwszy wstawiony element, stos (LIFO) ostatni, a `priority_queue` domyślnie największy. Stąd kolejno 3, 2 i 3.

#### Q. Dlaczego wywołanie `std::sort(lista.begin(), lista.end())` dla `std::list<int> lista` się nie skompiluje?

* [ ] Bo `std::list` nie przechowuje liczb całkowitych
* [x] Bo `std::sort` wymaga iteratorów dostępu swobodnego
* [ ] Bo `std::sort` działa tylko na tablicach wbudowanych
* [ ] Bo lista musi być najpierw pusta

> **Wyjaśnienie:** Iterator listy jest dwukierunkowy i nie pozwala skakać o dowolną liczbę pozycji, czego potrzebuje `std::sort`. Listę sortuje się jej własną metodą `lista.sort()`.

#### Q. Dlaczego w pętli po `std::vector` po wywołaniu `v.erase(it)` nie wolno wykonać `++it`?

* [ ] Bo `erase` przesuwa `it` na koniec wektora
* [x] Bo `it` jest unieważniony; trzeba użyć `it = v.erase(it)`
* [ ] Bo `++it` działa tylko dla `std::list`
* [ ] Bo `erase` usuwa wszystkie elementy za `it`

> **Wyjaśnienie:** Po `erase` iterator do usuniętego elementu i dalszych przestaje być ważny. `erase` zwraca iterator do następnego elementu, więc pętla przypisuje go do `it` i nie wykonuje wtedy `++it`.

#### Q. Co wypisze ten program w C++ z algorytmem `std::accumulate`?

```cpp
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::vector<double> v{1.5, 2.5};
    std::cout << std::accumulate(v.begin(), v.end(), 0) << ' '
              << std::accumulate(v.begin(), v.end(), 0.0) << '\n';
}
```

* [ ] `4 4`
* [x] `3 4`
* [ ] `4 3`
* [ ] `3 3`

> **Wyjaśnienie:** Typ sumy wyznacza wartość początkowa. Dla `0` (typ `int`) każdy pośredni wynik jest obcinany: `0 + 1.5 → 1`, `1 + 2.5 → 3`. Dla `0.0` suma jest liczona jako `double` i wynosi 4.

#### Q. Który tryb `fopen` dopisuje dane na końcu pliku i tworzy plik, gdy ten nie istnieje?

* [ ] `"r"`
* [ ] `"w"`
* [x] `"a"`
* [ ] `"r+"`

> **Wyjaśnienie:** Tryb `"a"` zapisuje na końcu i nie kasuje wcześniejszej zawartości. `"w"` tworzy lub czyści plik, a `"r"` i `"r+"` wymagają istniejącego pliku.

#### Q. Dlaczego wynik `fgetc` zapisuje się w zmiennej typu `int`, a nie `char`?

* [ ] Bo `fgetc` zwraca numer wiersza w pliku
* [x] Bo `int` musi odróżnić każdy znak od wartości `EOF`
* [ ] Bo `char` nie może przechować liter
* [ ] Bo `int` przyspiesza odczyt pliku

> **Wyjaśnienie:** `fgetc` zwraca każdy możliwy bajt jako nieujemną wartość albo osobny znacznik `EOF`. Po zapisaniu wyniku w `char` jakiś bajt mógłby zostać pomylony z `EOF` (albo `EOF` nigdy nie zostać rozpoznany).

#### Q. Dlaczego pętla `while (!plik.eof()) { plik >> liczba; suma += liczba; }` jest błędna?

* [ ] Bo `eof()` zawsze zwraca prawdę przed pierwszym odczytem
* [x] Bo flaga końca pojawia się dopiero po nieudanym odczycie
* [ ] Bo `>>` nie działa dla strumieni plikowych
* [ ] Bo `eof()` zamyka plik po pierwszym wywołaniu

> **Wyjaśnienie:** `eof()` staje się prawdą dopiero po próbie czytania za końcem, więc ostatni obieg może użyć starej wartości `liczba`. Odczyt umieszcza się w warunku: `while (plik >> liczba)`.

#### Q. Co wypisze ten program w C++, który trzy razy otwiera ten sam plik do zapisu?

```cpp
#include <fstream>
#include <iostream>
#include <string>

int main() {
    {
        std::ofstream p("log.txt");
        p << "A\n";
    }
    {
        std::ofstream p("log.txt", std::ios::out | std::ios::app);
        p << "B\n";
    }
    {
        std::ofstream p("log.txt");
        p << "C\n";
    }
    std::ifstream we("log.txt");
    std::string linia;
    while (std::getline(we, linia)) {
        std::cout << linia;
    }
    std::cout << '\n';
}
```

* [ ] `ABC`
* [x] `C`
* [ ] `BC`
* [ ] `AC`

> **Wyjaśnienie:** Domyślnie `std::ofstream` tworzy lub czyści plik. Tryb `app` dopisał `B` do `A`, ale trzecie otwarcie bez `app` skasowało całą wcześniejszą zawartość.

#### Q. Co wypisze ten program w C++ odczytujący liczby z pliku zawierającego `10 abc 30`?

```cpp
#include <fstream>
#include <iostream>

int main() {
    {
        std::ofstream p("liczby.txt");
        p << "10 abc 30\n";
    }
    std::ifstream we("liczby.txt");
    int liczba;
    int suma = 0;
    while (we >> liczba) {
        suma += liczba;
    }
    std::cout << suma << ' ' << we.eof() << '\n';
}
```

* [ ] `40 1`
* [x] `10 0`
* [ ] `10 1`
* [ ] `40 0`

> **Wyjaśnienie:** Odczyt zatrzymuje się na `abc`, którego nie da się zamienić na `int`: ustawia się `failbit`, ale koniec pliku nie został osiągnięty. Dlatego `30` nie jest dodane, a `eof()` zwraca fałsz.

#### Q. Jak C i C++ traktują instrukcję `int *p = malloc(sizeof *p);` (z dołączonym `<stdlib.h>`)?

* [x] W C jest poprawna, w C++ to błąd kompilacji
* [ ] W C to błąd kompilacji, w C++ jest poprawna
* [ ] W obu językach jest poprawna
* [ ] W obu językach to błąd kompilacji

> **Wyjaśnienie:** W C wynik `void *` można przypisać do `int *` bez rzutowania. C++ nie wykonuje tej konwersji niejawnie; wymagałby `static_cast<int *>`, a w nowym kodzie i tak lepiej użyć `std::vector` lub `std::make_unique`.

#### Q. Dlaczego deklaracja `int class = 3;` jest poprawna w C, ale nie w C++?

* [ ] Bo w C++ zmienne nie mogą mieć typu `int`
* [x] Bo `class` jest w C++ słowem kluczowym
* [ ] Bo w C++ wszystkie nazwy muszą zaczynać się od `_`
* [ ] Bo C++ wymaga słowa `auto` przed nazwą

> **Wyjaśnienie:** C++ zarezerwował nazwy takie jak `class` i `template`, których C nie używa jako słów kluczowych. Przenosząc kod z C do C++, trzeba sprawdzić także nazwy identyfikatorów.

#### Q. Jaki wynik daje `sizeof('A')` w C i w C++ na typowej platformie 64-bitowej (`gcc` i `g++`)?

* [ ] 1 w obu językach
* [x] 4 w C i 1 w C++
* [ ] 1 w C i 4 w C++
* [ ] 4 w obu językach

> **Wyjaśnienie:** W C stała znakowa `'A'` ma typ `int` (zwykle 4 bajty), a w C++ typ `char`, którego rozmiar zawsze wynosi 1. To przykład kodu o tej samej składni, ale innym znaczeniu w obu językach.

#### Q. Czym w C++ różni się `new Klasa` od `malloc(sizeof(Klasa))`?

* [ ] Niczym — oba przydzielają tę samą pamięć
* [x] `new` tworzy obiekt i wywołuje konstruktor
* [ ] `malloc` dodatkowo wywołuje konstruktor domyślny
* [ ] `new` nie wymaga później zwolnienia pamięci

> **Wyjaśnienie:** `malloc` daje tylko surową pamięć, a `new` tworzy w niej obiekt i uruchamia konstruktor; `delete` wywołuje destruktor, czego nie robi `free`. W nowoczesnym C++ zwykle używa się `std::make_unique` lub kontenerów.
