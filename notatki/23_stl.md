## STL (Standard Template Library)

STL to biblioteka szablonów w języku C++, która dostarcza gotowych do użycia implementacji wielu funkcji, algorytmów i struktur danych. Najważniejsze komponenty biblioteki STL to:

- `vector`
- `list`
- `map`
- `set`
- `queue`
- `stack`
- `algorithm`
- `iterator`
- `memory`

### Kolekcje w STL

Kolekcje w STL to zbiory implementacji struktur danych wraz z funkcjami operującymi na tych strukturach.

### STL (Standard Template Library)

STL to biblioteka szablonów w języku C++, która dostarcza gotowych do użycia implementacji wielu funkcji, algorytmów i struktur danych. Najważniejsze komponenty biblioteki STL to:

- `vector`
- `list`
- `map`
- `set`
- `unordered_map`
- `unordered_set`
- `priority_queue`
- `queue`
- `stack`
- `algorithm`
- `iterator`
- `memory`

Dodanie kolumny "Złożoność czasowa" do każdej tabeli może pomóc lepiej zrozumieć wydajność różnych operacji. Oto zaktualizowane tabele:

### Kolekcje w STL

Kolekcje w STL to zbiory implementacji struktur danych wraz z funkcjami operującymi na tych strukturach.

#### **vector**

`vector` to dynamiczna tablica, która może zmieniać swój rozmiar. Jest jednym z najczęściej używanych kontenerów w STL.

Operacje:

| Metoda              | Opis                                         | Przykład użycia                                           | Złożoność czasowa     |
|---------------------|----------------------------------------------|-----------------------------------------------------------|-----------------------|
| `push_back(value)`  | Dodaje element na końcu                      | `vec.push_back(10);`                                      | Amortyzowane O(1)     |
| `pop_back()`        | Usuwa element z końca                        | `vec.pop_back();`                                         | O(1)                  |
| `size()`            | Zwraca liczbę elementów                      | `auto s = vec.size();`                                    | O(1)                  |
| `empty()`           | Sprawdza, czy kontener jest pusty            | `if (vec.empty()) {}`                                     | O(1)                  |
| `clear()`           | Usuwa wszystkie elementy                     | `vec.clear();`                                            | O(n)                  |
| `insert(pos, value)`| Wstawia element na podanej pozycji           | `vec.insert(vec.begin() + 1, 20);`                        | O(n)                  |
| `erase(pos)`        | Usuwa element z podanej pozycji              | `vec.erase(vec.begin() + 1);`                             | O(n)                  |
| `at(index)`         | Zwraca referencję do elementu na podanym indeksie | `int val = vec.at(2);`                                | O(1)                  |
| `operator[]`        | Zwraca referencję do elementu na podanym indeksie | `int val = vec[2];`                                   | O(1)                  |
| `front()`           | Zwraca referencję do pierwszego elementu     | `int val = vec.front();`                                  | O(1)                  |
| `back()`            | Zwraca referencję do ostatniego elementu     | `int val = vec.back();`                                   | O(1)                  |
| `begin()`           | Zwraca iterator na początek                  | `auto it = vec.begin();`                                  | O(1)                  |
| `end()`             | Zwraca iterator na koniec                    | `auto it = vec.end();`                                    | O(1)                  |
| `reserve(n)`        | Rezerwuje miejsce na n elementów             | `vec.reserve(100);`                                       | O(n)                  |
| `resize(n)`         | Zmienia rozmiar wektora                      | `vec.resize(10);`                                         | O(n)                  |

Przykład:

```cpp
std::vector<int> vec = {1, 2, 3};
vec.push_back(4);
vec.insert(vec.begin() + 1, 10);
for(auto it = vec.begin(); it != vec.end(); ++it) {
std::cout << *it << " ";
}
```

#### **list**

`list` to dwukierunkowa lista wiązana, która umożliwia szybkie wstawianie i usuwanie elementów.

Operacje:

| Metoda               | Opis                                         | Przykład użycia                                           | Złożoność czasowa     |
|----------------------|----------------------------------------------|-----------------------------------------------------------|-----------------------|
| `push_back(value)`   | Dodaje element na końcu                      | `lst.push_back(10);`                                      | O(1)                  |
| `push_front(value)`  | Dodaje element na początku                   | `lst.push_front(5);`                                      | O(1)                  |
| `pop_back()`         | Usuwa element z końca                        | `lst.pop_back();`                                         | O(1)                  |
| `pop_front()`        | Usuwa element z początku                     | `lst.pop_front();`                                        | O(1)                  |
| `size()`             | Zwraca liczbę elementów                      | `auto s = lst.size();`                                    | O(1)                  |
| `empty()`            | Sprawdza, czy kontener jest pusty            | `if (lst.empty()) {}`                                     | O(1)                  |
| `clear()`            | Usuwa wszystkie elementy                     | `lst.clear();`                                            | O(n)                  |
| `insert(pos, value)` | Wstawia element na podanej pozycji           | `lst.insert(++lst.begin(), 20);`                          | O(1)                  |
| `erase(pos)`         | Usuwa element z podanej pozycji              | `lst.erase(++lst.begin());`                               | O(1)                  |
| `front()`            | Zwraca referencję do pierwszego elementu     | `int val = lst.front();`                                  | O(1)                  |
| `back()`             | Zwraca referencję do ostatniego elementu     | `int val = lst.back();`                                   | O(1)                  |
| `begin()`            | Zwraca iterator na początek                  | `auto it = lst.begin();`                                  | O(1)                  |
| `end()`              | Zwraca iterator na koniec                    | `auto it = lst.end();`                                    | O(1)                  |

Przykład:

```cpp
std::list<int> lst = {1, 2, 3};
lst.push_back(4);
lst.push_front(0);
lst.insert(++lst.begin(), 10);
for(auto it = lst.begin(); it != lst.end(); ++it) {
std::cout << *it << " ";
}
```

#### **map**

`map` to kontener asocjacyjny, który przechowuje pary klucz-wartość w uporządkowanej formie, wykorzystując drzewo czerwono-czarne.

Operacje:

| Metoda               | Opis                                         | Przykład użycia                                           | Złożoność czasowa     |
|----------------------|----------------------------------------------|-----------------------------------------------------------|-----------------------|
| `insert({key, value})`| Wstawia parę klucz-wartość                  | `mp.insert({1, "one"});`                                  | O(log n)              |
| `erase(key)`         | Usuwa element o podanym kluczu               | `mp.erase(1);`                                            | O(log n)              |
| `find(key)`          | Zwraca iterator na element o podanym kluczu  | `auto it = mp.find(1);`                                   | O(log n)              |
| `size()`             | Zwraca liczbę elementów                      | `auto s = mp.size();`                                     | O(1)                  |
| `empty()`            | Sprawdza, czy kontener jest pusty            | `if (mp.empty()) {}`                                      | O(1)                  |
| `clear()`            | Usuwa wszystkie elementy                     | `mp.clear();`                                             | O(n)                  |
| `operator[]`         | Zwraca referencję do wartości o podanym kluczu | `std::string val = mp[1];`                                | O(log n)              |
| `begin()`            | Zwraca iterator na początek                  | `auto it = mp.begin();`                                   | O(1)                  |
| `end()`              | Zwraca iterator na koniec                    | `auto it = mp.end();`                                     | O(1)                  |

Przykład:

```cpp
std::map<int, std::string> mp;
mp.insert({1, "one"});
mp[2] = "two";
mp.erase(1);
for(auto it = mp.begin(); it != mp.end(); ++it) {
std::cout << it->first << ": " << it->second << " ";
}
```

#### **unordered_map**

`unordered_map` to kontener asocjacyjny, który przechowuje pary klucz-wartość w nieuporządkowanej formie, wykorzystując tablicę mieszającą (hash table).

Operacje:

| Metoda               | Opis                                         | Przykład użycia                                           | Złożoność czasowa     |
|----------------------|----------------------------------------------|-----------------------------------------------------------|-----------------------|
| `insert({key, value})`| Wstawia parę klucz-wartość                  | `ump.insert({1, "one"});`                                 | O(1) amortyzowane     |
| `erase(key)`         | Usuwa element o podanym kluczu               | `ump.erase(1);`                                           | O(1) amortyzowane     |
| `find(key)`          | Zwraca iterator na element o podanym kluczu  | `auto it = ump.find(1);`                                  | O(1) amortyzowane     |
| `size()`             | Zwraca liczbę elementów                      | `auto s = ump.size();`                                    | O(1)                  |
| `empty()`            | Sprawdza, czy kontener jest pusty            | `if (ump.empty()) {}`                                     | O(1)                  |
| `clear()`            | Usuwa wszystkie elementy                     | `ump.clear();`                                            | O(n)                  |
| `operator[]`         | Zwraca referencję do wartości o podanym kluczu | `std::string val = ump[1];`                               | O(1) amortyzowane     |
| `begin()`            | Zwraca iterator na początek                  | `auto it = ump.begin();`                                  | O(1)                  |
| `end()`              | Zwraca iterator na koniec                    | `auto it = ump.end();`                                    | O(1)                  |

Przykład:

```cpp
std::unordered_map<int, std::string> ump;
ump.insert({1, "one"});
ump[2] = "two";
ump.erase(1);
for(auto it = ump.begin(); it != ump.end(); ++it) {
std::cout << it->first << ": " << it->second << " ";
}
```

#### **set**

`set` to kontener, który przechowuje unikalne elementy w uporządkowanej formie, wykorzystując drzewo czerwono-czarne.

Operacje:

Oto poprawiona tabela:

| Metoda               | Opis                                         | Przykład użycia                                           | Złożoność czasowa     |
|----------------------|----------------------------------------------|-----------------------------------------------------------|-----------------------|
| `insert(value)`      | Wstawia element                              | `st.insert(10);`                                          | O(log n)              |
| `erase(value)`       | Usuwa element                                | `st.erase(10);`                                           | O(log n)              |
| `find(value)`        | Zwraca iterator na element                   | `auto it = st.find(10);`                                  | O(log n)              |
| `size()`             | Zwraca liczbę elementów                      | `auto s = st.size();`                                     | O(1)                  |
| `empty()`            | Sprawdza, czy kontener jest pusty            | `if (st.empty()) {}`                                      | O(1)                  |
| `clear()`            | Usuwa wszystkie elementy                     | `st.clear();`                                             | O(n)                  |
| `begin()`            | Zwraca iterator na początek                  | `auto it = st.begin();`                                   | O(1)                  |
| `end()`              | Zwraca iterator na koniec                    | `auto it = st.end();`                                     | O(1)                  |

Przykład:

```cpp
std::set<int> st;
st.insert(10);
st.insert(20);
st.erase(10);
for(auto it = st.begin(); it != st.end(); ++it) {
std::cout << *it << " ";
}
```

#### **unordered_set**

`unordered_set` to kontener, który przechowuje unikalne elementy w nieuporządkowanej formie, wykorzystując tablicę mieszającą (hash table).

Operacje:

| Metoda               | Opis                                         | Przykład użycia                                           | Złożoność czasowa     |
|----------------------|----------------------------------------------|-----------------------------------------------------------|-----------------------|
| `insert(value)`      | Wstawia element                              | `ust.insert(10);`                                         | O(1) amortyzowane     |
| `erase(value)`       | Usuwa element                                | `ust.erase(10);`                                          | O(1) amortyzowane     |
| `find(value)`        | Zwraca iterator na element                   | `auto it = ust.find(10);`                                  | O(1) amortyzowane     |
| `size()`             | Zwraca liczbę elementów                      | `auto s = ust.size();`                                    | O(1)                  |
| `empty()`            | Sprawdza, czy kontener jest pusty            | `if (ust.empty()) {}`                                     | O(1)                  |
| `clear()`            | Usuwa wszystkie elementy                     | `ust.clear();`                                            | O(n)                  |
| `begin()`            | Zwraca iterator na początek                  | `auto it = ust.begin();`                                  | O(1)                  |
| `end()`              | Zwraca iterator na koniec                    | `auto it = ust.end();`                                    | O(1)                  |

Przykład:

```cpp
std::unordered_set<int> ust;
ust.insert(10);
ust.insert(20);
ust.erase(10);
for(auto it = ust.begin(); it != ust.end(); ++it) {
std::cout << *it << " ";
}
```

#### **priority_queue**

`priority_queue` to kontener, który implementuje kopiec binarny i pozwala na szybkie wyciąganie największego (lub najmniejszego) elementu.

Operacje:

| Metoda               | Opis                                         | Przykład użycia                                           | Złożoność czasowa     |
|----------------------|----------------------------------------------|-----------------------------------------------------------|-----------------------|
| `push(value)`        | Dodaje element                               | `pq.push(10);`                                            | O(log n)              |
| `pop()`              | Usuwa największy element                     | `pq.pop();`                                               | O(log n)              |
| `top()`              | Zwraca referencję do największego elementu   | `int val = pq.top();`                                     | O(1)                  |
| `size()`             | Zwraca liczbę elementów                      | `auto s = pq.size();`                                     | O(1)                  |
| `empty()`            | Sprawdza, czy kontener jest pusty            | `if (pq.empty()) {}`                                      | O(1)                  |

Przykład:

```cpp
std::priority_queue<int> pq;
pq.push(10);
pq.push(20);
pq.push(5);
std::cout << pq.top() << " "; // wyświetli 20
pq.pop();
std::cout << pq.top() << " "; // wyświetli 10
```

#### **queue**

`queue` to kontener, który implementuje kolejkę FIFO (First In, First Out).

Operacje:

| Metoda               | Opis                                         | Przykład użycia                                           | Złożoność czasowa     |
|----------------------|----------------------------------------------|-----------------------------------------------------------|-----------------------|
| `push(value)`        | Dodaje element                               | `q.push(10);`                                             | O(1)                  |
| `pop()`              | Usuwa element z początku                     | `q.pop();`                                                | O(1)                  |
| `front()`            | Zwraca referencję do pierwszego elementu     | `int val = q.front();`                                    | O(1)                  |
| `back()`             | Zwraca referencję do ostatniego elementu     | `int val = q.back();`                                     | O(1)                  |
| `size()`             | Zwraca liczbę elementów                      | `auto s = q.size();`                                      | O(1)                  |
| `empty()`            | Sprawdza, czy kontener jest pusty            | `if (q.empty()) {}`                                       | O(1)                  |

Przykład:

```cpp
std::queue<int> q;
q.push(10);
q.push(20);
std::cout << q.front() << " "; // wyświetli 10
q.pop();
std::cout << q.front() << " "; // wyświetli 20
```

#### **stack**

`stack` to kontener, który implementuje stos LIFO (Last In, First Out).

Operacje:

| Metoda               | Opis                                         | Przykład użycia                                           | Złożoność czasowa     |
|----------------------|----------------------------------------------|-----------------------------------------------------------|-----------------------|
| `push(value)`        | Dodaje element                               | `st.push(10);`                                            | O(1)                  |
| `pop()`              | Usuwa element z końca                        | `st.pop();`                                               | O(1)                  |
| `top()`              | Zwraca referencję do ostatniego elementu     | `int val = st.top();`                                     | O(1)                  |
| `size()`             | Zwraca liczbę elementów                      | `auto s = st.size();`                                     | O(1)                  |
| `empty()`            | Sprawdza, czy kontener jest pusty            | `if (st.empty()) {}`                                      | O(1)                  |

Przykład:

```cpp
std::stack<int> st;
st.push(10);
st.push(20);
std::cout << st.top() << " "; // wyświetli 20
st.pop();
std::cout << st.top() << " "; // wyświetli 10
```

### Iteratory

Iteratory w języku C++ to obiekty umożliwiające sekwencyjny dostęp do elementów kontenerów. Dzięki nim możliwe jest jednolite przeglądanie zawartości różnych typów kolekcji, niezależnie od ich wewnętrznej implementacji. Iteratory pełnią podobną rolę do wskaźników, ale są bardziej elastyczne i bezpieczne w użyciu.

#### Rodzaje iteratorów

| Typ iteratora                | Opis                                                                                 |
|------------------------------|---------------------------------------------------------------------------------------|
| **Input Iterator**            | Służy do odczytu danych z kontenera.                                                  |
| **Output Iterator**           | Służy do zapisu danych do kontenera.                                                  |
| **Forward Iterator**          | Łączy możliwości iteratorów input i output, może przemieszczać się tylko do przodu.   |
| **Bidirectional Iterator**    | Umożliwia przemieszczanie się zarówno do przodu, jak i do tyłu.                       |
| **Random Access Iterator**    | Oferuje wszystkie możliwości Bidirectional Iterator oraz umożliwia dostęp do dowolnego elementu kontenera w stałym czasie. |

#### Podstawowe operacje na iteratorach

- Inicjalizacja iteratora początkowym elementem kontenera: `kontener.begin()`
- Inicjalizacja iteratora elementem za ostatnim w kontenerze: `kontener.end()`
- Odwołanie do elementu, na który wskazuje iterator: `*it`
- Przesunięcie iteratora do następnego elementu: `++it`
- Przesunięcie iteratora do poprzedniego elementu: `--it` (dla Bidirectional Iterator)
- Przesunięcie iteratora o określoną liczbę pozycji: `it += n` lub `it -= n` (dla Random Access Iterator)
- Wstawienie elementu w miejscu wskazywanym przez iterator: `it = kontener.insert(it, wartość)`
- Usunięcie elementu w miejscu wskazywanym przez iterator: `it = kontener.erase(it)`

#### Przykład użycia iteratora

Poniższy przykład ilustruje operacje na wektorze `std::vector` typu `std::string`. Najpierw tworzy i inicjalizuje wektor trzema elementami: "ala", "ma", "kota", a następnie wyświetla jego zawartość za pomocą iteratora. Następnie dodaje nowy element "nie" przed drugim elementem wektora, czyli przed "ma". Po tym usuwa pierwszy element wektora, którym jest "ala". Na koniec, program ponownie wyświetla zmodyfikowaną zawartość wektora.

```c++
#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> v = {"ala", "ma", "kota"};

    // Wyświetlenie zawartości wektora przy użyciu iteratora
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << std::endl;
    }

    // Dodanie nowego elementu przed "ma"
    auto it = v.begin() + 1;
    v.insert(it, "nie");

    // Usunięcie słowa "ala"
    it = v.begin();
    v.erase(it);

    std::cout << "\nPo modyfikacjach:\n";
    for (const auto& word : v) {
        std::cout << word << std::endl;
    }

    return 0;
}
```

Warto pamiętać, że po niektórych operacjach, takich jak insert czy erase, używane wcześniej iteratory mogą stać się nieaktualne i ich dalsze użycie może prowadzić do niezdefiniowanego zachowania programu.

### Algorytmy w Standardowej Bibliotece C++ (STL)

Biblioteka `algorithm` w standardowej bibliotece C++ (STL) dostarcza bogaty zestaw funkcji szablonowych, które służą do manipulacji i analizy danych przechowywanych w kontenerach. Algorytmy te są zaprojektowane w sposób generyczny, co oznacza, że mogą działać z różnymi typami danych i kontenerami, pod warunkiem spełnienia określonych wymagań. W tej sekcji przyjrzymy się kilku kluczowym algorytmom, ich implementacji, zastosowaniu oraz analizie matematycznej wydajności.

#### Wprowadzenie do Algorytmów STL

Algorytmy w STL są zaimplementowane jako funkcje szablonowe, co pozwala na ich użycie z różnymi typami danych i kontenerami. Działają one na zakresach określonych przez iteratory, co zapewnia elastyczność i niezależność od konkretnego typu kontenera. Dzięki temu możliwe jest pisanie kodu, który jest jednocześnie uniwersalny i wydajny.

#### Klasyfikacja Algorytmów

Algorytmy STL można podzielić na kilka kategorii:

| Kategoria algorytmów                    | Przykłady                                                                 |
|-----------------------------------------|---------------------------------------------------------------------------|
| **Algorytmy modyfikujące**              | `std::copy`, `std::fill`, `std::transform`                                |
| **Algorytmy przeszukujące**             | `std::find`, `std::count`, `std::search`                                  |
| **Algorytmy sortujące i porządkujące**  | `std::sort`, `std::stable_sort`, `std::partial_sort`                      |
| **Algorytmy numeryczne**                | `std::accumulate`, `std::inner_product`, `std::partial_sum`               |
| **Algorytmy usuwające**                 | `std::remove`, `std::unique`, `std::remove_if`                            |

#### `std::sort()`

Funkcja `std::sort()` służy do sortowania elementów w określonym zakresie. Jest to jeden z najczęściej używanych algorytmów w STL. Wykorzystuje algorytm sortowania introspektywnego (introsort), który łączy zalety sortowania szybkiego (quick sort), sortowania kopcowego (heap sort) i sortowania przez wstawianie (insertion sort).

**Prototyp:**

```cpp
template< class RandomIt >
void sort( RandomIt first, RandomIt last );

template< class RandomIt, class Compare >
void sort( RandomIt first, RandomIt last, Compare comp );
```

- `RandomIt`: Typ iteratora losowego dostępu.
- `Compare`: Funkcja lub funktor służący do porównywania elementów.

**Wymagania:**

- Elementy muszą być porównywalne za pomocą operatora `<` lub funkcji `Compare`.
- Iteratory muszą być iteratorami losowego dostępu (np. z `std::vector`, `std::array`).

**Przykład Użycia:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> wektor{8, 3, 5, 1, 2, 4, 6, 7};
    auto kopia = wektor;

    // Sortowanie pierwszych trzech elementów
    std::sort(wektor.begin(), wektor.begin() + 3);

    // Sortowanie całego wektora
    std::sort(kopia.begin(), kopia.end());

    // Wyświetlanie wyników
    std::cout << "Wektor po częściowym sortowaniu: ";
    for (const auto& val : wektor) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    std::cout << "Wektor po pełnym sortowaniu: ";
    for (const auto& val : kopia) {
        std::cout << val << " ";
    }

    return 0;
}
```

**Analiza Matematyczna:**

- **Złożoność czasowa** dla tego algorytmu wynosi średnio $O(nlogn)$, co jest charakterystyczne dla wydajnych algorytmów sortowania.
- W najgorszym przypadku złożoność czasowa również wynosi $O(nlog)$, ponieważ algorytm wykorzystuje introsort, który automatycznie przełącza się na sortowanie kopcowe, gdy wykryje niekorzystny podział danych.
- **Złożoność pamięciowa** tego algorytmu wymaga $O(logn)$ dodatkowej pamięci, głównie na stos rekurencji, co czyni go efektywnym pod względem użycia zasobów pamięci.

**Dostosowywanie Kryterium Sortowania:**

Możemy dostarczyć własną funkcję porównującą:

```cpp
std::sort(wektor.begin(), wektor.end(), [](int a, int b) {
    return a > b; // Sortowanie malejące
});
```

**Uwagi:**

- **Stabilność** algorytmu `std::sort()` nie jest zagwarantowana, co oznacza, że kolejność równych elementów może się zmienić. W przypadku, gdy stabilność jest wymagana, należy skorzystać z funkcji `std::stable_sort()`.
- Typ elementów musi być **zgodny** z wymaganiami funkcji porównującej, co zapewnia poprawność działania algorytmu.

#### `std::find()`

Algorytm `std::find()` przeszukuje zakres w poszukiwaniu pierwszego wystąpienia określonej wartości. Zwraca iterator wskazujący na znaleziony element lub na koniec zakresu, jeśli element nie został znaleziony.

**Prototyp:**

```cpp
template< class InputIt, class T >
InputIt find( InputIt first, InputIt last, const T& value );
```

- `InputIt`: Typ iteratora wejściowego.
- `T`: Typ poszukiwanej wartości.

**Przykład Użycia:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> wektor{8, 3, 5, 1, 2, 4, 6, 7};

    auto it = std::find(wektor.begin(), wektor.end(), 3);

    if (it != wektor.end())
        std::cout << "Znaleziono element o wartości 3 na pozycji "
                  << std::distance(wektor.begin(), it) << "\n";
    else
        std::cout << "Nie znaleziono elementu o wartości 3\n";

    return 0;
}
```

**Analiza Matematyczna:**

- **Złożoność czasowa** wynosi $O(n)$, gdzie n oznacza liczbę elementów w przetwarzanym zakresie, co sprawia, że algorytm działa liniowo względem liczby danych.
- **Złożoność pamięciowa** wynosi $O(1)$, co oznacza, że algorytm nie wymaga dodatkowej pamięci poza tą używaną przez same dane.

**Uwagi:**

- Algorytm przeszukuje liniowo zakres od `first` do `last`.
- Możemy użyć `std::find_if()` lub `std::find_if_not()` do przeszukiwania z warunkiem predykatu.

#### `std::for_each()`

Funkcja `std::for_each()` stosuje podaną funkcję lub funktor do każdego elementu w zakresie. Jest to alternatywa dla pętli `for` i pozwala na bardziej funkcyjne podejście do iteracji.

**Prototyp:**

```cpp
template< class InputIt, class UnaryFunction >
UnaryFunction for_each( InputIt first, InputIt last, UnaryFunction f );
```

- `InputIt`: Typ iteratora wejściowego.
- `UnaryFunction`: Typ funkcji lub funktora akceptującego element typu dereferowanego iteratora.

**Przykład Użycia:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> wektor{8, 3, 5, 1, 2, 4, 6, 7};

    // Modyfikacja każdego elementu przez jego podwojenie
    std::for_each(wektor.begin(), wektor.end(), [](int &x) { x *= 2; });

    // Wyświetlanie wyników
    std::cout << "Wektor po modyfikacji: ";
    for (const auto& val : wektor) {
        std::cout << val << " ";
    }

    return 0;
}
```

**Analiza Matematyczna:**

- **Złożoność czasowa** wynosi **O(n)**, ponieważ funkcja jest wywoływana dokładnie n razy, co oznacza liniowy wzrost liczby operacji w zależności od liczby elementów.
- **Złożoność pamięciowa** wynosi **O(1)**, gdyż algorytm nie wymaga dodatkowej pamięci poza ewentualnymi zmiennymi lokalnymi w funkcji.

**Uwagi:**

- Funkcja `UnaryFunction` jest przekazywana przez wartość, więc jeśli potrzebujemy zachować stan między wywołaniami, należy użyć referencji lub obiektu zewnętrznego.
- Zwracana jest kopia funkcji `UnaryFunction` po ostatnim wywołaniu, co może być użyte do akumulacji wyników.

#### `std::count_if()`

Algorytm `std::count_if()` zlicza liczbę elementów w zakresie, dla których predykat jest spełniony.

**Prototyp:**

```cpp
template< class InputIt, class UnaryPredicate >
typename iterator_traits<InputIt>::difference_type
count_if( InputIt first, InputIt last, UnaryPredicate p );
```

- `InputIt`: Typ iteratora wejściowego.
- `UnaryPredicate`: Funkcja lub funktor zwracający wartość logiczną.

**Przykład Użycia:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> wektor{8, 3, 5, 1, 2, 4, 6, 7};

    // Zliczanie parzystych elementów
    int parzyste = std::count_if(wektor.begin(), wektor.end(), [](int x) { return x % 2 == 0; });

    std::cout << "Liczba parzystych elementów: " << parzyste << "\n";

    return 0;
}
```

**Analiza Matematyczna:**

- **Złożoność czasowa** wynosi **O(n)**, ponieważ predykat jest wywoływany dokładnie n razy, co sprawia, że liczba operacji rośnie liniowo w zależności od liczby elementów.
- **Złożoność pamięciowa** wynosi **O(1)**, co oznacza, że algorytm nie wymaga dodatkowej pamięci poza zmiennymi lokalnymi.

**Uwagi:**

- Jeśli chcemy zliczyć wystąpienia konkretnej wartości, możemy użyć `std::count()`.

#### Inne Ważne Algorytmy

##### `std::accumulate()`

Służy do obliczenia sumy wartości w zakresie, z opcjonalnym początkowym akumulatorem i funkcją operacji.

**Prototyp:**

```cpp
template< class InputIt, class T >
T accumulate( InputIt first, InputIt last, T init );

template< class InputIt, class T, class BinaryOperation >
T accumulate( InputIt first, InputIt last, T init, BinaryOperation op );
```

**Przykład:**

```cpp
int suma = std::accumulate(wektor.begin(), wektor.end(), 0);
```

##### `std::transform()`

Stosuje funkcję do każdego elementu w zakresie i zapisuje wynik w innym zakresie.

**Prototyp:**

```cpp
template< class InputIt, class OutputIt, class UnaryOperation >
OutputIt transform( InputIt first1, InputIt last1, OutputIt d_first, UnaryOperation unary_op );
```

**Przykład:**

```cpp
std::vector<int> wyniki(wektor.size());
std::transform(wektor.begin(), wektor.end(), wyniki.begin(), [](int x) { return x * x; });
```

#### Kompatybilność z Iteratorami

Algorytmy STL są zaprojektowane tak, aby działać z różnymi kategoriami iteratorów:

| Kategoria          | Przykłady Algorytmów               |
|--------------------|------------------------------------|
| Iteratory wejściowe  | `std::find`, `std::count_if`       |
| Iteratory wyjściowe  | `std::copy`, `std::fill`           |
| Iteratory jedno kierunkowe | `std::for_each`, `std::remove`      |
| Iteratory dwukierunkowe | `std::reverse`, `std::rotate`     |
| Iteratory losowego dostępu | `std::sort`, `std::nth_element` |

#### Zastosowanie Algorytmów w Praktyce

Algorytmy STL pozwalają na pisanie kodu o wysokim poziomie abstrakcji, co zwiększa czytelność i redukuje ryzyko błędów. Dzięki generyczności i wykorzystaniu szablonów, algorytmy te są niezwykle elastyczne i mogą być stosowane w szerokim zakresie zastosowań.

**Przykład: Analiza Danych Finansowych**

Załóżmy, że mamy wektor reprezentujący dzienne zmiany cen akcji i chcemy przeprowadzić analizę:

```cpp
std::vector<double> zmianyCen = { -0.5, 1.2, 0.3, -0.7, 0.8, -1.0, 0.6 };

// Obliczenie sumarycznej zmiany cen
double sumaZmian = std::accumulate(zmianyCen.begin(), zmianyCen.end(), 0.0);

// Zliczenie dni ze wzrostem cen
int dniWzrostu = std::count_if(zmianyCen.begin(), zmianyCen.end(), [](double x) { return x > 0; });

// Znalezienie największego spadku
auto it = std::min_element(zmianyCen.begin(), zmianyCen.end());

// Wyświetlenie wyników
std::cout << "Sumaryczna zmiana cen: " << sumaZmian << "\n";
std::cout << "Liczba dni ze wzrostem cen: " << dniWzrostu << "\n";
std::cout << "Największy spadek: " << *it << "\n";
```

#### Optymalizacja za Pomocą Algorytmów

Korzystanie z algorytmów STL może prowadzić do bardziej wydajnego kodu, ponieważ są one zazwyczaj dobrze zoptymalizowane i wykorzystują najlepsze praktyki implementacyjne. Ponadto, kompilatory mogą dokonywać dodatkowych optymalizacji, gdy używane są standardowe algorytmy.

**Przykład: Porównanie z Pętlą `for`**

Rozważmy zliczanie elementów spełniających określony warunek:

**Tradycyjna pętla `for`:**

```cpp
int licznik = 0;
for (size_t i = 0; i < wektor.size(); ++i) {
  if (wektor[i] % 2 == 0) {
      ++licznik;
  }
}
```

**Użycie `std::count_if()`:**

```cpp
int licznik = std::count_if(wektor.begin(), wektor.end(), [](int x) { return x % 2 == 0; });
```

Korzystanie z `std::count_if()` nie tylko skraca kod, ale również zwiększa jego czytelność i potencjalnie wydajność.
