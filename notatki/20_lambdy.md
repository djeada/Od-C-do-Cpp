# Wyrażenia lambda

Lambda to zapis zachowania w miejscu, w którym jest potrzebne. Najczęściej przekazujemy ją do algorytmu jako kryterium sortowania, wyszukiwania lub przekształcania elementów. Zamiast tworzyć osobną nazwaną funkcję, zapisujemy krótką operację obok jej użycia. Jej parametry działają jak parametry zwykłej funkcji: typy argumentów i ewentualne konwersje nadal mają znaczenie.

Lambda nie jest zwykłą funkcją bez nazwy. Jest wyrażeniem, które tworzy **obiekt funkcyjny**: obiekt wywoływalny jak funkcja. Kompilator nadaje mu unikalny typ domknięcia i zapisuje w tym obiekcie przechwycone wartości lub odwołania. Ten model pomaga zrozumieć, skąd lambda bierze dane i jak długo może z nich bezpiecznie korzystać.

## Składnia i pierwsze wywołanie

```cpp
[przechwycenia](parametry) -> typ_wyniku {
    // ciało lambdy
}
```

Lista parametrów działa jak w zwykłej funkcji. Typ po `->` można pominąć, jeśli kompilator może go wywnioskować z instrukcji `return`.

```cpp
auto dodaj = [](int a, int b) {
    return a + b;
};

int wynik = dodaj(2, 3);  // operator() lambdy dostaje a == 2 i b == 3; wynik to 5
```

W `[]` określamy przechwycenia; pusta lista oznacza, że lambda nie korzysta z lokalnych zmiennych otaczającego zakresu. `auto` pozwala przechować obiekt bez nazywania jego niejawnego typu. Po prawej stronie `=` lambda jest tworzona, a średnik kończy deklarację zmiennej `dodaj`.

## Jak działa domknięcie

Każda lambda ma własny typ, inny niż typ każdej innej lambdy. Można myśleć o niej jak o obiekcie klasy wygenerowanej przez kompilator z operatorem `operator()`. Poniższa lambda:

```cpp
int poprawka = 3;
auto dodajPoprawke = [poprawka](int x) {
    return x + poprawka;
};
```

zachowuje się w przybliżeniu jak obiekt z polem przechowującym kopię `poprawka` oraz metodą wywołania. To tylko model wyjaśniający — dokładny układ obiektu jest szczegółem implementacji. Gdy lambda powstaje, do jej domknięcia trafia wartość `3`. Wywołanie `dodajPoprawke(4)` używa parametru `x == 4` i przechwyconej kopii `poprawka == 3`, więc zwraca `7`. Późniejsza zmiana pierwotnej zmiennej nie zmienia kopii w domknięciu.

## Przechwytywanie zmiennych

Lista przechwytywania określa, jak lambda korzysta ze **zmiennych automatycznych** widocznych w miejscu jej utworzenia — zwykle są to zmienne lokalne. Najważniejsza różnica: przechwycenie przez wartość przechowuje kopię, a przez referencję odwołuje się do istniejącego obiektu.

| Zapis | Znaczenie |
|---|---|
| `[]` | Brak przechwyconych zmiennych lokalnych. |
| `[x]` | Przechwycenie `x` przez wartość, czyli kopia. |
| `[&x]` | Przechwycenie `x` przez referencję. |
| `[=]` | Domyślne przechwytywanie użytych zmiennych lokalnych przez wartość. |
| `[&]` | Domyślne przechwytywanie użytych zmiennych lokalnych przez referencję. |
| `[x, &y]` | `x` jest kopiowane, a `y` używane przez referencję. |

Zmienne globalne i statyczne nie są przechwytywane — lambda może się do nich odwołać bezpośrednio. Domyślne przechwycenie nie oznacza kopiowania całego zakresu, tylko tych zmiennych lokalnych, których lambda używa.

### Kopia i referencja w praktyce

```cpp
int licznik = 10;
auto kopia = [licznik] { return licznik; };
auto odwolanie = [&licznik] { return licznik; };

licznik = 20;
int a = kopia();       // 10: domknięcie zachowało wcześniejszą kopię
int b = odwolanie();   // 20: lambda odczytała bieżący obiekt licznik
```

Referencja bywa wygodna, gdy lambda działa od razu, na przykład wewnątrz algorytmu wywoływanego synchronicznie. Trzeba jednak pilnować czasu życia obiektu, do którego się odwołuje. Lambda może przeżyć zmienną, którą przechwyciła:

```cpp
auto stworzOdczyt = [] {
    int lokalna = 7;
    return [&lokalna] { return lokalna; };  // Błąd projektu: lokalna przestaje istnieć
};
```

Zapis funkcji z wnioskowanym typem zwracanym wymaga C++14. Samo przechwycenie przez referencję działa już w C++11, ale nie przedłuża życia `lokalna`.

Po wyjściu ze `stworzOdczyt` zmienna `lokalna` już nie istnieje. Wywołanie zwróconej lambdy próbuje wtedy odczytać nieistniejący obiekt — zachowanie programu jest niezdefiniowane. Jeśli lambda ma przeżyć bieżący zakres, przechwyć potrzebną wartość przez kopię:

```cpp
auto stworzOdczyt = [] {
    int lokalna = 7;
    return [lokalna] { return lokalna; };  // Domknięcie przechowuje własne 7
};

auto odczytaj = stworzOdczyt();
int wartosc = odczytaj();  // 7
```

Kopia wskaźnika nie kopiuje wskazywanego obiektu ani nie przedłuża jego życia. Podobnie skopiowanie obiektu zawierającego referencję nie przedłuża życia celu. Dlatego samo `[=]` nie gwarantuje bezpieczeństwa czasu życia — trzeba znać to, co przechowywana wartość faktycznie wskazuje.

### Przechwytywanie `this`

W metodzie klasy lambda może korzystać ze składowych obiektu. Przechwycenie `[this]` zachowuje wskaźnik do bieżącego obiektu, nie jego kopię. Jeśli lambda będzie wywołana po zniszczeniu obiektu, `this` będzie wiszącym wskaźnikiem. Od C++17 zapis `[*this]` kopiuje bieżący obiekt do domknięcia, o ile jego kopiowanie jest dozwolone.

W starszym kodzie `[=]` użyte w metodzie mogło niejawnie przechwycić `this`; nie kopiowało wtedy całego obiektu. To niejawne przechwytywanie jest przestarzałe od C++20. Gdy lambda korzysta ze składowej klasy, zapisz intencję wprost (`[this]` lub `[*this]`) i sprawdź, czy wybrany czas życia jest właściwy.

## Modyfikowanie przechwyconej kopii: `mutable`

Domyślnie operator wywołania lambdy nie zmienia stanu przechwyconych przez wartość kopii. Słowo `mutable` pozwala modyfikować ten stan. Nie powoduje jednak zapisu do pierwotnej zmiennej:

```cpp
int licznik = 0;
auto nastepny = [licznik]() mutable {
    return ++licznik;
};

int pierwszy = nastepny();  // 1; kopia wewnątrz domknięcia zmienia się z 0 na 1
int drugi = nastepny();     // 2; to samo domknięcie pamięta poprzedni stan
// licznik nadal wynosi 0
```

`mutable` nie służy do modyfikowania oryginału. Do tego potrzebne jest przechwycenie przez referencję (`[&licznik]`), co ponownie wymaga zadbania o czas życia zmiennej. Ponieważ `mutable` zmienia operator wywołania tak, by mógł modyfikować stan, taka lambda nie jest wywoływalna przez obiekt lambdy oznaczony jako `const`.

## Lambdy i algorytmy biblioteki standardowej

Algorytm przyjmuje lambdę jako argument i wywołuje ją dla elementów zakresu. Dzięki temu mechanizm sortowania lub wyszukiwania pozostaje ogólny, a kryterium jest zapisane obok konkretnego użycia. Poniższy przykład wymaga `<algorithm>` i `<vector>`; używa C++11:

```cpp
#include <algorithm>
#include <vector>

std::vector<int> liczby{3, 1, 4, 1, 5, 9};

int main() {
    std::sort(liczby.begin(), liczby.end(),
              [](int a, int b) { return a > b; });  // Porządek malejący

    int granica = 4;
    auto znaleziony = std::find_if(liczby.begin(), liczby.end(),
                                   [granica](int n) { return n > granica; });
    if (znaleziony != liczby.end()) {
        int wartosc = *znaleziony;
    }
    return 0;
}
```

`std::sort` wielokrotnie pyta komparator, czy pierwszy argument ma znaleźć się przed drugim. Dla liczb warunek `a > b` ustawia większe wartości wcześniej. Komparator musi spełniać regułę ścisłego słabego porządku; na przykład `a >= b` jest błędne, bo dla `a == b` twierdzi, że element jest przed samym sobą.

`std::find_if` sprawdza elementy po kolei, wywołując predykat z wartością `n`. Lambda zachowała kopię `granica == 4`, więc szuka pierwszej liczby większej od 4. Wynikiem jest iterator do znalezionego elementu albo `liczby.end()`, jeśli żadnego nie znaleziono. W pełnym kodzie należy porównać iterator z `end()` przed dereferencją.

Ponieważ algorytm kończy pracę przed wyjściem z tego zakresu, przechwycenie `[&granica]` byłoby tu również bezpieczne pod względem czasu życia. Kopia `[granica]` wyraźniej pokazuje, że predykat potrzebuje tylko wartości i nie zmienia zewnętrznej zmiennej. W przypadku algorytmu uruchamianego asynchronicznie referencja mogłaby przeżyć zmienną — wtedy ten sam zapis nie byłby bezpieczny.

## Typ lambdy, `auto` i `std::function`

Typ domknięcia jest unikalny i nie ma nazwy, dlatego typowym sposobem przechowania lambdy jest `auto`:

```cpp
auto podwajaj = [](int x) { return 2 * x; };
```

Dwie lambdy zapisane identycznie w dwóch miejscach nadal mają różne typy. Z tego powodu zmienna `auto` nie może później dostać dowolnej innej lambdy. Gdy potrzebujemy przechowywać różne, kopiowalne obiekty wywoływalne o tej samej sygnaturze, można użyć `std::function` z nagłówka `<functional>`:

```cpp
#include <functional>

int main() {
    std::function<int(int)> operacja = [](int x) { return 2 * x; };
    operacja = [](int x) { return x + 1; };  // Inny typ lambdy, ta sama sygnatura
    int wynik = operacja(3);  // 4
    return 0;
}
```

`std::function<int(int)>` obiecuje, że przechowywany obiekt da się wywołać z `int` i wynikiem wywołania jest `int`. Opakowanie ukrywa konkretny typ domknięcia, może jednak dodawać koszt pośredniego wywołania lub alokacji i wymaga, by przechowywany obiekt był kopiowalny. Jeśli typ jest znany w miejscu użycia, zwykle prostsze jest `auto`; jeśli funkcja ma przyjmować dowolny typ wywoływalny, często nadaje się parametr szablonowy (temat następnej notatki).

## Zwracanie i uogólnianie lambd

### Zwracanie lambdy

Typ domknięcia jest niejawny, ale od C++14 kompilator może wywnioskować typ zwracany funkcji, która zwraca lambdę:

```cpp
auto stworzMnoznik(int mnoznik) {
    return [mnoznik](int x) { return x * mnoznik; };
}

auto podwajaj = stworzMnoznik(2);
int wynik = podwajaj(5);  // Domknięcie przechowuje 2; wynik to 10
```

Wartość `mnoznik` została skopiowana do zwróconego domknięcia, więc lambda nie odwołuje się do zmiennej lokalnej po zakończeniu `stworzMnoznik`.

### Lambdy generyczne

Od C++14 parametr lambdy może mieć typ `auto`. Wtedy kompilator tworzy szablonowy operator wywołania, który może być instancjowany dla różnych typów:

```cpp
auto suma = [](auto a, auto b) { return a + b; };

int calkowita = suma(2, 3);       // Jedno wywołanie: a i b są int
double zmiennoprzecinkowa = suma(2.5, 3.5);  // Inne wywołanie: a i b są double
```

To nie oznacza, że dowolne dwa typy będą działały. Dla każdego wywołania wyrażenie `a + b` musi być poprawne i jego wynik musi pasować do kontekstu. Od C++20 można zapisać parametry szablonu lambdy jawnie, np. `[]<typename T>(T x) { ... }`.

### Rekurencja

Lambda nie może odwołać się po nazwie do zmiennej, której inicjalizacja właśnie trwa. Od C++14 można obejść to ograniczenie, przekazując obiekt lambdy jako argument `self`:

```cpp
auto silnia = [](auto self, unsigned n) -> unsigned long long {
    return n < 2 ? 1 : n * self(self, n - 1);
};

auto wynik = silnia(silnia, 5);  // 5 * 4 * 3 * 2 * 1 == 120
```

Pierwsze wywołanie przekazuje lambdę jako jej własny argument. Przy `n == 5` ciało wywołuje `self(self, 4)`, potem `self(self, 3)` i tak dalej aż do przypadku bazowego `n < 2`. Użycie typu bez znaku uniemożliwia przekazanie wartości ujemnej, ale wynik nadal ma ograniczony zakres; dla dużego `n` może nastąpić zawinięcie wartości bez znaku. Silnia jest tu przykładem rekurencji, nie gotową funkcją do dowolnie dużych danych.

## Wersje standardu

- **C++11:** podstawowe lambdy, jawne przechwycenia, `std::function`.
- **C++14:** parametry `auto`, inicjalizowane przechwycenia, np. `[kopia = wyrazenie]`, oraz wnioskowanie typu zwracanego funkcji zwracającej lambdę. Jeśli inicjalizator używa `std::move`, potrzebny jest nagłówek `<utility>`.
- **C++17:** możliwość używania lambdy jako `constexpr`, jeśli spełnia odpowiednie wymagania; przechwycenie kopii bieżącego obiektu przez `[*this]`.
- **C++20:** jawne listy parametrów szablonu lambdy, np. `[]<typename T>(T x)`, oraz przestarzałość niejawnego przechwycenia `this` przez `[=]`.

Lambdy najczęściej przekazuje się do algorytmów albo funkcji szablonowych bez opakowania w `std::function`. Dzięki temu kod może przyjmować różne typy wywoływalne, zachowując ich typy i przechwycony stan — szablony z następnej notatki są jednym z mechanizmów, które to umożliwiają.
