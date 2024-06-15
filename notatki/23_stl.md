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

1. **Input Iterator**: Służy do odczytu danych z kontenera.
2. **Output Iterator**: Służy do zapisu danych do kontenera.
3. **Forward Iterator**: Łączy możliwości iteratorów input i output, może przemieszczać się tylko do przodu.
4. **Bidirectional Iterator**: Umożliwia przemieszczanie się zarówno do przodu, jak i do tyłu.
5. **Random Access Iterator**: Oferuje wszystkie możliwości Bidirectional Iterator oraz umożliwia dostęp do dowolnego elementu kontenera w stałym czasie.

#### Podstawowe operacje na iteratorach

- Inicjalizacja iteratora początkowym elementem kontenera: `kontener.begin()`
- Inicjalizacja iteratora elementem za ostatnim w kontenerze: `kontener.end()`
- Odwołanie do elementu, na który wskazuje iterator: `*it`
- Przesunięcie iteratora do następnego elementu: `++it`
- Przesunięcie iteratora do poprzedniego elementu: `--it` (dla Bidirectional Iterator)
- Przesunięcie iteratora o określoną liczbę pozycji: `it += n` lub `it -= n` (dla Random Access Iterator)
- Wstawienie elementu w miejscu wskazywanym przez iterator: `it = kontener.insert(it, wartość)`
- Usunięcie elementu w miejscu wskazywanym przez iterator: `it = kontener.erase(it)`

#### Przykład użycia iteratora do przeglądania i modyfikowania zawartości wektora

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

### Algorytmy

Biblioteka `algorithm` dostarcza bogaty zestaw funkcji, które służą do manipulacji i analizy kolekcji. Oto kilka przykładów najbardziej popularnych algorytmów z tej biblioteki:

#### sort()

Funkcja `sort()` służy do sortowania elementów kolekcji. Jej podstawowe użycie polega na przekazaniu dwóch iteratorów: początkowego i końcowego, określających zakres sortowania.

```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> wektor{8, 3, 5, 1, 2, 4, 6, 7};
    auto kopia = wektor;

    std::sort(wektor.begin(), wektor.begin() + 3); // posortowane zostaną pierwsze 3 elementy
    std::sort(kopia.begin(), kopia.end());         // posortowane zostaną wszystkie elementy

    for (const auto& val : wektor) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    for (const auto& val : kopia) {
        std::cout << val << " ";
    }

    return 0;
}
```

#### find()

Algorytm `find()` przeszukuje kolekcję w poszukiwaniu określonego elementu i zwraca iterator wskazujący na pierwsze wystąpienie tego elementu.

```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> wektor{8, 3, 5, 1, 2, 4, 6, 7};

    auto it = std::find(wektor.begin(), wektor.end(), 3);

    if (it != wektor.end())
        std::cout << "Znaleziono element o wartości 3 na pozycji " << std::distance(wektor.begin(), it) << std::endl;
    else
        std::cout << "Nie znaleziono elementu o wartości 3" << std::endl;

    return 0;
}
```

#### for_each()

Funkcja `for_each()` pozwala na wykonanie określonej operacji na każdym elemencie kolekcji. Operacja ta jest określana za pomocą funkcji lub wyrażenia lambda.

```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> wektor{8, 3, 5, 1, 2, 4, 6, 7};
    std::for_each(wektor.begin(), wektor.end(), [](int &x) { x *= 2; });

    for (const auto& val : wektor) {
        std::cout << val << " ";
    }

    return 0;
}
```

#### count_if()

Algorytm `count_if()` pozwala zliczyć, ile razy spełniony jest określony warunek w kolekcji.

```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> wektor{8, 3, 5, 1, 2, 4, 6, 7};
    int parzyste = std::count_if(wektor.begin(), wektor.end(), [](int x) { return x % 2 == 0; });

    std::cout << "Liczba parzystych elementów: " << parzyste << std::endl;

    return 0;
}
```

Powyższy kod wykorzystuje `count_if()` do zliczenia parzystych elementów w wektorze. Algorytmy w STL są potężnym narzędziem umożliwiającym efektywne i wygodne operacje na kontenerach, minimalizując ilość kodu potrzebnego do wykonania złożonych zadań.
