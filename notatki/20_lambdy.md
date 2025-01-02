## Funkcje Lambda

Funkcje lambda, wprowadzone w standardzie C++11, stanowią jedno z najbardziej przełomowych rozszerzeń języka, umożliwiając tworzenie funkcji anonimowych bezpośrednio w miejscu ich użycia. Pozwalają one na definiowanie funkcji w sposób zwięzły i elastyczny, co znacząco ułatwia programowanie funkcyjne w C++. W niniejszym opracowaniu przedstawimy szczegółowy opis funkcji lambda, ich składni, mechanizmów przechwytywania zmiennych oraz zastosowań w praktyce, z naciskiem na precyzję i formalizm matematyczny.

### Składnia funkcji lambda

Ogólna postać funkcji lambda w C++ jest następująca:

```cpp
[przechwycenie](parametry) -> typ_zwracany {
    // ciało funkcji
}
```

Elementy składni:

- **Przechwycenie (`[przechwycenie]`)** określa, które zmienne z zakresu otaczającego (en. *enclosing scope*) są dostępne wewnątrz lambdy oraz w jaki sposób są przechwytywane.
- Lista **parametrów (`(parametry)`)** funkcji, analogicznie jak w zwykłych funkcjach.
- **Specyfikator typu zwracanego (`-> typ_zwracany`)** opcjonalnie określa typ zwracany przez funkcję. Jeśli jest pominięty, kompilator próbuje go wywnioskować na podstawie `return` w ciele funkcji.
- **Ciało funkcji (`{ ... }`)** to blok kodu wykonywany przy wywołaniu lambdy.

Przykład prostej lambdy dodającej dwie liczby:

```cpp
auto suma = [](int a, int b) -> int {
    return a + b;
};
```

### Mechanizm przechwytywania zmiennych (Domknięcie)

Funkcje lambda w C++ posiadają zdolność do tworzenia **domknięć** (en. *closures*), co oznacza, że mogą przechwytywać i wykorzystywać zmienne z zakresu, w którym zostały zdefiniowane. Sposób przechwytywania zmiennych określa się w nawiasach kwadratowych `[]`.

Sposoby przechwytywania:

- `[]` — brak przechwytywania. Lambda nie ma dostępu do żadnych zmiennych spoza swojego zakresu.
- `[=]` — przechwytywanie wszystkich dostępnych zmiennych przez wartość. Zmienne są kopiowane do wnętrza lambdy.
- `[&]` — przechwytywanie wszystkich dostępnych zmiennych przez referencję. Lambda operuje na oryginalnych zmiennych.
- `[this]` — przechwytywanie wskaźnika `this`, umożliwiające dostęp do członków klasy.
- `[x, &y]` — selektywne przechwytywanie: `x` przez wartość, `y` przez referencję.

**Uwaga:** Przechwytywane zmienne są traktowane jako prywatne składowe anonimowej klasy generowanej przez kompilator dla lambdy.

### Typy funkcji lambda

Każda funkcja lambda jest obiektem funkcyjnym o unikalnym typie anonimowym, generowanym przez kompilator. Aby przechowywać lambdy o nieznanym z góry typie, można użyć:

- `auto` — do automatycznego wywnioskowania typu.
- `std::function` — do przechowywania lambd o określonej sygnaturze, kosztem narzutu związanego z dynamicznym wywołaniem.

Przykład użycia `std::function`:

```cpp
std::function<int(int, int)> dodaj = [](int a, int b) {
    return a + b;
};
```

### Klauzula `mutable`

Domyślnie lambdy przechwytujące zmienne przez wartość nie pozwalają na modyfikację tych zmiennych wewnątrz swojego ciała (są one traktowane jako `const`). Aby umożliwić modyfikację przechwyconych przez wartość zmiennych, należy użyć klauzuli `mutable`:

```cpp
int licznik = 0;
auto inkrementuj = [licznik]() mutable {
    licznik++;
    return licznik;
};
```

W powyższym przykładzie `licznik` jest lokalną kopią zmiennej przechwyconej przez wartość, którą możemy modyfikować wewnątrz lambdy.

### Przykłady praktyczne

#### Przechwytywanie zmiennych

Rozważmy zmienne `a` i `b` w zewnętrznym zakresie:

```cpp
int a = 5;
int b = 10;

auto suma = [=]() {
    return a + b;
};

auto mnoznik = [&]() {
    a *= 2;
    b *= 2;
};
```

- W lambdzie `suma` zmienne `a` i `b` są przechwycone przez wartość. Modyfikacje `a` i `b` wewnątrz lambdy nie wpłyną na oryginalne zmienne.
- W lambdzie `mnoznik` zmienne są przechwycone przez referencję. Modyfikacje wewnątrz lambdy wpływają na oryginalne zmienne.

#### Użycie z algorytmami STL

Funkcje lambda są szczególnie użyteczne w połączeniu z algorytmami biblioteki standardowej.

**Przykład sortowania z własnym kryterium:**

```cpp
std::vector<int> liczby = {3, 1, 4, 1, 5, 9, 2, 6};
std::sort(liczby.begin(), liczby.end(), [](int a, int b) {
    return a > b;  // Sortowanie malejące
});
```

**Przykład filtrowania elementów:**

```cpp
std::vector<int> liczby = {1, 2, 3, 4, 5};
auto it = std::find_if(liczby.begin(), liczby.end(), [](int n) {
    return n % 2 == 0;  // Szukanie pierwszej liczby parzystej
});
```

### Teoretyczne podstawy funkcji lambda

Funkcje lambda w C++ są inspirowane rachunkiem lambda, formalnym systemem logicznym opracowanym przez Alonzo Churcha w latach 30. XX wieku. Rachunek lambda jest podstawą matematycznej teorii funkcji i stanowi fundament dla języków funkcyjnych.

W kontekście C++, funkcje lambda umożliwiają traktowanie funkcji jako obiektów pierwszej klasy, co oznacza, że mogą być przekazywane jako argumenty, zwracane z funkcji oraz przechowywane w zmiennych.

### Mechanizm działania lambd w C++

Podczas kompilacji lambdy są przekształcane na obiekty funkcyjne (funktory). Kompilator generuje anonimową klasę z przeciążonym operatorem wywołania funkcyjnego `operator()`. Przechwycone zmienne stają się prywatnymi składowymi tej klasy.

**Przykład lambdy i jej odpowiednika jako funktor:**

Lambda:

```cpp
auto suma = [x](int y) {
    return x + y;
};
```

Odpowiednik jako klasa:

```cpp
class AnonimowaLambda {
private:
    int x;
public:
    AnonimowaLambda(int x) : x(x) {}
    int operator()(int y) const {
        return x + y;
    }
};

AnonimowaLambda suma(x);
```

### Zaawansowane zastosowania

#### Generatory funkcji

Funkcje lambda mogą być zwracane z funkcji, co pozwala na tworzenie fabryk funkcji:

```cpp
auto stworz_mnoznik(int mnoznik) {
    return [mnoznik](int x) {
        return x * mnoznik;
    };
}

auto podwajaj = stworz_mnoznik(2);
std::cout << podwajaj(5);  // Wyświetli 10
```

#### Rekursja w lambdach

Ze względu na anonimowość, lambdy nie posiadają nazwy, co utrudnia implementację rekurencji. Można to obejść, używając wskaźnika na samą lambdę:

```cpp
std::function<int(int)> silnia = [](int n) {
    return n <= 1 ? 1 : n * silnia(n - 1);
};
```

Lub poprzez przekazanie samej siebie jako argumentu:

```cpp
auto silnia = [](auto self, int n) -> int {
    return n <= 1 ? 1 : n * self(self, n - 1);
};

std::cout << silnia(silnia, 5);  // Wyświetli 120
```

### Wydajność i optymalizacja

Funkcje lambda w C++ są zazwyczaj kompilowane do wydajnego kodu maszynowego, porównywalnego z kodem napisanym za pomocą tradycyjnych funkcji czy funktorów. Jednakże nadmierne użycie `std::function` może wprowadzać narzut związany z dynamicznym wywołaniem funkcji.

Aby zapewnić maksymalną wydajność:

- Unikaj używania `std::function`, jeśli nie jest to konieczne.
- Przechwytuj zmienne przez referencję, jeśli kopiowanie jest kosztowne.
- Używaj `constexpr` lambd, gdy jest to możliwe (od C++17).

### Nowości w nowszych standardach C++

Standard C++ jest dynamicznie rozwijany, a każda nowa wersja wprowadza istotne ulepszenia, które zwiększają możliwości języka, poprawiają wydajność oraz ułatwiają programowanie. W tej sekcji omówimy kluczowe nowości związane z lambdami oraz innymi funkcjami wprowadzonymi w standardach C++14, C++17 i C++20.

#### C++14: Generowane typy zwracane

W C++14 wprowadzono możliwość pominięcia specyfikatora typu zwracanego w lambdach, co pozwala na bardziej zwięzły i czytelny kod, szczególnie w przypadku złożonych wyrażeń.

**Przykład:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> liczby = {1, 2, 3, 4, 5};

    // Lambda bez określonego typu zwracanego
    auto suma = [](auto a, auto b) {
        return a + b;
    };

    int wynik = suma(10, 20);
    std::cout << "Suma: " << wynik << std::endl; // Wyświetli 30

    return 0;
}
```

**Zalety:**

- Skrócony zapis lambd sprawia, że kod jest bardziej przejrzysty.
- Automatyczne dedukowanie typu zwracanego pozwala na użycie lambd z różnymi typami danych bez konieczności ręcznego określania typu.

#### C++17: Domyślne szablony zmiennych w lambdach

C++17 wprowadził możliwość definiowania lambd z parametrami szablonowymi, co pozwala na większą elastyczność i ponowne używanie lambd w różnych kontekstach typów.

**Przykład:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Lambda z parametrami szablonowymi
    auto suma = []<typename T>(T a, T b) {
        return a + b;
    };

    std::cout << "Suma int: " << suma(10, 20) << std::endl;       // Wyświetli 30
    std::cout << "Suma double: " << suma(10.5, 20.3) << std::endl; // Wyświetli 30.8

    return 0;
}
```

**Zalety:**

- Lambdy mogą działać z różnymi typami danych bez potrzeby definiowania osobnych lambd dla każdego typu.
- Możliwość stosowania lambd w różnych kontekstach typów zwiększa reużywalność kodu.

#### C++20: Lambdy odświeżone (constexpr lambdas)

C++20 wprowadza lambdy oznaczone jako `constexpr`, co umożliwia ich użycie w kontekstach wymagających stałych wyrażeń, takich jak `static_assert` czy inicjalizatory stałych zmiennych.

**Przykład:**

```cpp
#include <iostream>
#include <array>

int main() {
    // Lambda constexpr
    constexpr auto kwadrat = [](int x) constexpr {
        return x * x;
    };

    static_assert(kwadrat(5) == 25, "Kwadrat 5 powinien być 25");

    constexpr std::array<int, 3> tablica = { kwadrat(2), kwadrat(3), kwadrat(4) };
    
    for (const auto& val : tablica) {
        std::cout << val << " "; // Wyświetli 4 9 16
    }
    
    return 0;
}
```

**Zalety:**

- Stałe wyrażenia mogą być przetwarzane podczas kompilacji, co prowadzi do optymalizacji czasu wykonania.
- Możliwość sprawdzania poprawności wyrażeń w czasie kompilacji za pomocą `static_assert`.
