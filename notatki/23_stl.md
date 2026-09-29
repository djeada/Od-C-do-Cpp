# STL: kontenery, iteratory i algorytmy

Program często przechowuje wiele podobnych danych: oceny, nazwy produktów albo liczby wczytane z pliku. Można samodzielnie zbudować tablicę i napisać pętle wyszukujące czy sortujące, ale trzeba wtedy osobno pilnować pamięci, zakresów i poprawności operacji. Biblioteka standardowa C++ daje gotowe narzędzia do tych zadań.

Nazwa **STL** (Standard Template Library) tradycyjnie oznacza część biblioteki standardowej z kontenerami, iteratorami i algorytmami. Jej podstawowy pomysł jest prosty:

1. **Kontener** przechowuje dane, np. `std::vector<int>` przechowuje liczby całkowite.
2. **Iterator** wskazuje element kontenera i pozwala przejść do następnego.
3. **Algorytm** wykonuje operację na zakresie wskazanym iteratorami, np. szuka, zlicza albo sortuje elementy.

Dzięki temu `std::find` może szukać wartości zarówno w `vector`, jak i w `list`. Trzeba jednak dobrać kontener do potrzeb, bo nie każdy kontener pozwala na te same operacje.

W przykładach stosujemy nazwy ze `std::`, np. `std::vector`. Dzięki temu widać, że typ pochodzi z biblioteki standardowej i nie trzeba dodawać `using namespace std;`.

## Jak wybrać kontener?

Zacznij od pytania, jak będziesz używać danych. Czy potrzebujesz dostępu po indeksie? Wyszukiwania po kluczu? Zachowania kolejności? Częstych zmian na początku? Poniższa tabela pokazuje typowe punkty wyjścia.

| Potrzeba | Typowy wybór | Dlaczego |
|---|---|---|
| Sekwencja elementów, indeksowanie, iterowanie | `std::vector` | Elementy są ciągłe w pamięci; dostęp po indeksie jest szybki. To dobry wybór domyślny. |
| Częste dodawanie/usuwanie na obu końcach | `std::deque` | Szybko obsługuje początek i koniec, a także dostęp po indeksie. |
| Wstawianie/usuwanie w wielu miejscach, gdy iterator do miejsca już mamy | `std::list` | Zmiana położenia elementów nie wymaga przesuwania całej dalszej części listy. Za samo znalezienie miejsca nadal trzeba przejść elementy. |
| Wyszukiwanie wartości po kluczu i iterowanie w kolejności kluczy | `std::map` | Klucze są uporządkowane, wyszukiwanie trwa O(log n). |
| Wyszukiwanie po kluczu, kolejność nie ma znaczenia | `std::unordered_map` | Średnio szybkie wyszukiwanie przez tablicę haszującą. |
| Zbiór unikalnych wartości | `std::set` lub `std::unordered_set` | Wartości nie powtarzają się; wybierz `set` dla kolejności, `unordered_set` dla wyszukiwania haszującego. |
| Obsługa elementów w kolejności FIFO, LIFO lub według priorytetu | `std::queue`, `std::stack`, `std::priority_queue` | Udostępniają tylko operacje potrzebne danemu modelowi. |

Nie wybieraj `std::list` tylko dlatego, że w opisie ma szybkie wstawianie i usuwanie. Jeśli najpierw musisz znaleźć miejsce przez przejście listy, samo znalezienie trwa O(n). `std::vector` często działa szybciej przy zwykłym przechodzeniu po wszystkich elementach, bo dane leżą blisko siebie w pamięci.

## `std::vector`: sekwencja indeksowana

### Problem i intuicja

Użyjmy wektora, gdy mamy uporządkowaną sekwencję elementów i chcemy często odczytywać je po indeksie albo przechodzić po całej sekwencji. `std::vector` przypomina tablicę, ale może zwiększać rozmiar w trakcie działania programu.

### Przykład krok po kroku

Zaczynamy od danych `{1, 2, 3}`. Dodajemy `4` na końcu, a potem wstawiamy `10` przed elementem o indeksie `1`:

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> liczby{1, 2, 3};
    liczby.push_back(4);
    liczby.insert(liczby.begin() + 1, 10);

    for (int liczba : liczby) {
        std::cout << liczba << ' ';
    }
    std::cout << '\n';
}
```

Po `push_back` dane to `{1, 2, 3, 4}`. `begin()` wskazuje pierwszy element, więc `begin() + 1` wskazuje miejsce przed drugim elementem. Po `insert` wektor zawiera `{1, 10, 2, 3, 4}`. Program wypisze:

```text
1 10 2 3 4
```

### Koszt i częsta pomyłka

Dostęp `liczby[i]` trwa O(1), czyli nie rośnie wraz z liczbą elementów. `push_back` ma koszt **amortyzowany** O(1): większość dodawań jest tania, ale czasem wektor musi przydzielić większy obszar pamięci i przenieść wszystkie elementy. Wstawienie lub usunięcie w środku kosztuje O(n), bo trzeba przesunąć elementy za zmienianą pozycją.

`reserve(n)` rezerwuje pojemność na co najmniej `n` elementów, lecz **nie tworzy** tych elementów i nie zmienia `size()`. `resize(n)` zmienia liczbę elementów. Częsta pomyłka to wywołać `reserve(10)`, a następnie zapisać do `wektor[0]`: rozmiar nadal może wynosić zero, więc indeks nie wskazuje istniejącego elementu. W takim przypadku użyj `push_back` albo najpierw `resize`.

## Pozostałe kontenery sekwencyjne

### `std::deque`

Gdy dane trzeba często dodawać i usuwać na początku **oraz** na końcu, `std::deque` (double-ended queue) jest wygodniejszy od `vector`. Obsługuje `push_front`, `push_back` i indeksowanie. Wstawianie w środku nadal wymaga przesuwania elementów, a elementy nie są przechowywane jako jeden ciągły obszar pamięci.

### `std::list`

`std::list` to lista dwukierunkowa. Każdy element przechowuje połączenia z sąsiadami. Jeśli mamy już iterator do miejsca, `insert` i `erase` zmieniają tylko powiązania listy i nie przesuwają pozostałych elementów.

```cpp
#include <iostream>
#include <list>
#include <iterator>

int main() {
    std::list<int> liczby{1, 2, 3};
    auto miejsce = std::next(liczby.begin()); // Iterator wskazuje 2.
    liczby.insert(miejsce, 10);

    for (int liczba : liczby) {
        std::cout << liczba << ' ';
    }
    std::cout << '\n';
}
```

Początkowo lista to `{1, 2, 3}`. `std::next(begin())` przechodzi od pierwszego elementu do drugiego, więc `10` zostaje wstawione przed `2`. Wynik to `1 10 2 3`. Lista nie ma szybkiego dostępu przez `liczby[2]`; żeby dotrzeć do trzeciego elementu, trzeba przejść przez wcześniejsze. Dlatego sama operacja „wstaw przy iteratorze” jest O(1), ale wyszukanie iteratora może kosztować O(n).

## Kontenery z kluczami: `map`, `set` i wersje haszujące

### `map` i zliczanie wystąpień

Załóżmy, że chcemy policzyć, ile razy występuje każde słowo. W `std::map` klucz jest powiązany z wartością, a klucze są iterowane w kolejności sortowania:

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> wystapienia;
    ++wystapienia["kot"];
    ++wystapienia["pies"];
    ++wystapienia["kot"];

    for (const auto& para : wystapienia) {
        std::cout << para.first << ": " << para.second << '\n';
    }
}
```

Trzy dodane słowa to: `kot`, `pies`, `kot`. `wystapienia["kot"]` zwraca wartość przypisaną kluczowi `kot`; jeśli klucz nie istnieje, operator `[]` najpierw wstawia go z wartością domyślną typu `int`, czyli `0`. Kolejne `++` zwiększają licznik. Program wypisze:

```text
kot: 2
pies: 1
```

`std::map` utrzymuje klucze w porządku, a wyszukiwanie, wstawianie i usuwanie kosztuje O(log n). Złożoność nie oznacza czasu w sekundach; opisuje, jak liczba kroków rośnie wraz z liczbą elementów.

**Uwaga:** `mapa[klucz]` zmienia kontener, gdy klucza nie było. Do sprawdzenia, czy klucz już istnieje, użyj `find`, `contains` (C++20) lub odpowiedniej metody wyszukiwania. To częsty błąd: samo „sprawdzenie” przez `[]` może niepostrzeżenie dodać nowy klucz.

### `unordered_map`, `set` i `unordered_set`

`std::unordered_map` także przechowuje pary klucz–wartość i nie pozwala na powtórzenie klucza, ale nie zachowuje kolejności elementów. Wyszukiwanie, wstawianie i usuwanie są średnio O(1), a w niekorzystnym przypadku mogą być O(n). To dobry wybór, kiedy kolejność nie jest potrzebna, a ważne jest częste wyszukiwanie.

`std::set` przechowuje unikalne wartości w kolejności sortowania. `std::unordered_set` przechowuje unikalne wartości bez gwarantowanej kolejności. Przykład: jeśli z wejściowych słów `kot`, `pies`, `kot` utworzymy `set`, zbiór będzie zawierać tylko `kot` i `pies`.

W kontenerach haszujących nie zakładaj określonej kolejności wypisywania. Gdy kontener zwiększa liczbę kubełków (rehash), jego iteratory przestają być ważne. Dlatego nie zachowuj iteratora przez operację, która może spowodować rehash.

## Adaptery: kolejka, stos i kolejka priorytetowa

Adapter nie jest nową strukturą danych do dowolnego przeglądania. Udostępnia wąski zestaw operacji, żeby wymusić określony sposób użycia:

- `std::queue` — FIFO: pierwszy wstawiony element jest pierwszym zdejmowanym;
- `std::stack` — LIFO: ostatni wstawiony element jest pierwszym zdejmowanym;
- `std::priority_queue` — najpierw zwraca element o najwyższym priorytecie; dla liczb domyślnie jest to największa wartość.

```cpp
#include <iostream>
#include <queue>
#include <stack>

int main() {
    std::queue<int> kolejka;
    kolejka.push(10);
    kolejka.push(20);
    std::cout << kolejka.front() << '\n'; // 10
    kolejka.pop();

    std::stack<int> stos;
    stos.push(10);
    stos.push(20);
    std::cout << stos.top() << '\n'; // 20
    stos.pop();

    std::priority_queue<int> priorytety;
    priorytety.push(10);
    priorytety.push(30);
    priorytety.push(20);
    std::cout << priorytety.top() << '\n'; // 30
}
```

Po dodaniu `10` i `20` kolejka pokazuje `10`, bo ten element dodano pierwszy; stos pokazuje `20`, bo dodano go ostatni. Kolejka priorytetowa pokazuje `30`, bo to największa z dodanych liczb. `pop()` usuwa element, ale go nie zwraca — najpierw odczytaj go przez `front()` lub `top()`. Przed użyciem tych metod sprawdź `empty()`, bo odczyt pustego adaptera jest niepoprawny.

## Iteratory: zakres i przechodzenie po elementach

Iterator działa podobnie do wskaźnika: `*it` odczytuje wskazywany element, a `++it` przechodzi do następnego. Para iteratorów przekazywana algorytmowi zwykle opisuje zakres półotwarty `[poczatek, koniec)`: początek należy do zakresu, koniec już nie.

Jeśli wektor zawiera `{4, 7, 9}`, `begin()` wskazuje `4`, a `end()` oznacza pozycję tuż za `9`. Algorytm kończy pracę po dojściu do `end()`. Nie wolno odczytywać `*end()`, ponieważ iterator ten nie wskazuje elementu. Taki zapis ułatwia też opis pustego zakresu: dla pustego kontenera `begin() == end()`.

Różne algorytmy wymagają różnych możliwości iteratorów:

| Możliwość iteratora | Co może zrobić algorytm | Typowe przykłady |
|---|---|---|
| Wejściowy | Czytać elementy, przechodząc naprzód. | Iteratory wejściowe i strumieniowe. |
| Wyjściowy | Zapisywać elementy, przechodząc naprzód. | `std::back_inserter`. |
| Forward | Wielokrotnie przechodzić naprzód. | `std::forward_list`. |
| Dwukierunkowy | Iść naprzód i wstecz. | `std::list`, `std::map`. |
| Dostępu swobodnego | Skakać o dowolną liczbę pozycji, używać indeksowania. | `std::vector`, `std::deque`. |
| Ciągły | Jak wyżej, a elementy leżą w ciągłym obszarze pamięci. | `std::vector`, `std::array`. |

Na przykład `std::sort` musi móc szybko przeskakiwać po elementach, dlatego wymaga iteratorów dostępu swobodnego. Działa z `vector`, lecz nie z `list`. Lista ma własną metodę `sort()`. Nie próbuj też używać `begin() + 2` dla `list`: jej iterator nie obsługuje takiego skoku. Do przejścia kilku elementów można użyć `std::next`, ale dla listy przejście jest krok po kroku.

## Unieważnianie iteratorów

Iterator jest ważny tylko wtedy, gdy nadal wskazuje element istniejący w kontenerze. Niektóre operacje zmieniające kontener mogą przenieść elementy albo je usunąć, przez co zachowany iterator nie nadaje się już do użycia.

| Kontener i operacja | Co może przestać być ważne |
|---|---|
| `vector`: dodanie elementu powoduje realokację | Wszystkie iteratory, wskaźniki i referencje do elementów. |
| `vector`: `insert` bez realokacji | Iteratory i referencje wskazujące pozycję wstawienia lub dalsze. |
| `vector`: `erase` | Iterator usuniętego elementu i wszystkie dalsze. |
| `list`: `insert` | Iteratory do dotychczasowych elementów pozostają ważne. |
| `list`: `erase` | Przestaje być ważny iterator do usuniętego elementu. |
| `map`: wstawienie | Iteratory do pozostałych elementów pozostają ważne. |
| `unordered_map`: rehash | Iteratory zostają unieważnione. |

Dokładne zasady zależą od kontenera. Szczególnie w `vector` nie zakładaj, że iterator przeżyje dodanie kolejnego elementu: jeśli wektorowi zabraknie pojemności, może przenieść całą zawartość w inne miejsce.

Przy usuwaniu elementów z `vector` użyj iteratora zwróconego przez `erase`. Przykład: dla `{1, 2, 3, 4, 5, 6}` chcemy usunąć liczby parzyste. Po usunięciu iterator do kolejnego elementu zwraca `erase`, więc pętla może kontynuować bez używania unieważnionego iteratora:

```cpp
for (auto it = liczby.begin(); it != liczby.end();) {
    if (*it % 2 == 0) {
        it = liczby.erase(it);
    } else {
        ++it;
    }
}
```

Przetwarzane będą kolejno `1`, `2`, `3`, `4`, `5`, `6`, a po pętli wektor będzie zawierał `{1, 3, 5}`. Częsta pomyłka to wykonać `erase(it)` i zaraz potem `++it`: iterator przekazany do `erase` jest już nieważny, a ponadto można wtedy pominąć następny element.

## Algorytmy: wspólne operacje na zakresach

Algorytmy znajdują się głównie w `<algorithm>`. Zwykle dostają dwa iteratory określające zakres. Nie muszą wiedzieć, czy dane są w wektorze, tablicy czy innym kontenerze — korzystają z możliwości udostępnionych przez iteratory.

| Algorytm | Co robi | Typowy koszt |
|---|---|---|
| `std::find(poczatek, koniec, wartosc)` | Zwraca iterator do pierwszej znalezionej wartości lub `koniec`. | O(n) porównań. |
| `std::count_if(poczatek, koniec, warunek)` | Zlicza elementy, dla których warunek jest prawdziwy. | O(n) sprawdzeń. |
| `std::sort(poczatek, koniec)` | Sortuje zakres w miejscu. Wymaga iteratorów dostępu swobodnego. | O(n log n) porównań. |
| `std::transform(poczatek, koniec, wyjscie, operacja)` | Przekształca każdy element i zapisuje wynik do zakresu wyjściowego. | O(n) wywołań operacji. |
| `std::accumulate(poczatek, koniec, wartosc_poczatkowa)` | Łączy elementy, np. sumuje je; jest w `<numeric>`. | O(n) operacji łączenia. |
| `std::remove_if(poczatek, koniec, warunek)` | Przesuwa elementy do zachowania na początek i zwraca nowy koniec zakresu. Sam nie zmniejsza rozmiaru kontenera. | O(n) sprawdzeń. |

W zapisie O(n), `n` oznacza liczbę elementów. O(n) oznacza, że przy dwa razy większej liczbie elementów algorytm wykona w przybliżeniu dwa razy więcej kroków. O(log n) rośnie wolniej, zaś O(n log n) jest typowym kosztem sortowania. To opis wzrostu liczby operacji, nie czasu w sekundach; szczegóły zależą też od kontenera i rodzaju pracy.

### Jeden przykład na konkretnych danych

Wejściowy wektor to `{7, 2, 5, 2, 8}`. Wykonamy na nim wyszukiwanie, zliczanie, sumowanie, przekształcenie, sortowanie i usuwanie:

```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> liczby{7, 2, 5, 2, 8};

    auto znaleziony = std::find(liczby.begin(), liczby.end(), 5);
    if (znaleziony != liczby.end()) {
        std::cout << "Znaleziono: " << *znaleziony << '\n';
    }

    int parzyste = std::count_if(
        liczby.begin(), liczby.end(), [](int x) { return x % 2 == 0; });
    long long suma = std::accumulate(liczby.begin(), liczby.end(), 0LL);

    std::vector<int> podwojone;
    std::transform(liczby.begin(), liczby.end(),
                   std::back_inserter(podwojone),
                   [](int x) { return 2 * x; });

    std::sort(liczby.begin(), liczby.end());

    auto nowy_koniec = std::remove_if(
        liczby.begin(), liczby.end(), [](int x) { return x % 2 == 0; });
    liczby.erase(nowy_koniec, liczby.end());

    std::cout << "Parzystych: " << parzyste << '\n';
    std::cout << "Suma: " << suma << '\n';
    std::cout << "Podwojone: ";
    for (int x : podwojone) std::cout << x << ' ';
    std::cout << "\nPo sortowaniu i usunięciu parzystych: ";
    for (int x : liczby) std::cout << x << ' ';
    std::cout << '\n';
}
```

Dla podanych danych program wypisze:

```text
Znaleziono: 5
Parzystych: 3
Suma: 24
Podwojone: 14 4 10 4 16
Po sortowaniu i usunięciu parzystych: 5 7
```

`find` przechodzi od początku i zatrzymuje się na `5`; dlatego przed `*znaleziony` sprawdzamy, czy iterator nie jest równy `end()`. `count_if` sprawdza każdy element, a warunek `x % 2 == 0` jest prawdziwy dla `2`, `2` i `8`, stąd wynik `3`. `accumulate` dodaje liczby: `7 + 2 + 5 + 2 + 8 = 24`. Wartość początkowa `0LL` powoduje, że suma ma typ `long long`.

`transform` nie zmienia wejściowego wektora. Wstawia dwukrotność każdej liczby do `podwojone`; `std::back_inserter` dopisuje wyniki na końcu, więc nie trzeba wcześniej ustalać rozmiaru wektora wynikowego. `sort` zmienia kolejność w `liczby` na `{2, 2, 5, 7, 8}`.

Na końcu `remove_if` przesuwa elementy, których **nie** chcemy usunąć, na początek zakresu i zwraca iterator za tymi elementami. Nie zmniejsza rozmiaru `vector`. Dopiero `erase(nowy_koniec, liczby.end())` usuwa pozostałą końcówkę, dlatego końcowa zawartość to `{5, 7}`. Częsta pomyłka to oczekiwać, że samo `remove_if` zmieni rozmiar kontenera.

### Dodatkowe uwagi o algorytmach

- `std::sort` sortuje elementy w miejscu, czyli zmienia ich kolejność w podanym kontenerze. Dwa elementy uznane za równoważne mogą zmienić kolejność; jeśli jej zachowanie jest wymagane, rozważ `std::stable_sort`.
- Aby sortować malejąco, można podać komparator, np. `std::greater<int>{}` z nagłówka `<functional>`, albo własną lambdę.
- `std::for_each` wywołuje podaną operację dla każdego elementu. Do zwykłego wypisania lub przetworzenia elementów czytelna bywa też pętla zakresowa `for`.
- Algorytm musi otrzymać zakres pasujący do jego wymagań. `std::sort` nie zadziała bezpośrednio na `std::list`; użyj `lista.sort()` albo skopiuj dane do kontenera obsługującego iteratory dostępu swobodnego.
- Nagłówek dołączaj dla funkcji, której używasz: np. `<algorithm>` dla `find`, `count_if`, `sort`, `transform`, `<numeric>` dla `accumulate`, a `<iterator>` dla `back_inserter`.
