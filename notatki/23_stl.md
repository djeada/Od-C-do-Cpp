## STL (Standard Template Library)

Standard Template Library (STL) to jedna z najważniejszych części języka C++, która znacząco ułatwia programowanie dzięki dostępowi do gotowych, wydajnych i elastycznych struktur danych oraz algorytmów. STL jest biblioteką szablonów, co oznacza, że jej komponenty są generyczne i mogą pracować z różnymi typami danych bez konieczności pisania dodatkowego kodu. Dzięki STL programiści mogą skupić się na logice aplikacji, zamiast na implementacji podstawowych struktur danych i algorytmów.

STL została zaprojektowana tak, aby wspierać trójskładnikowy model: **algorytmy**, **kontenery** i **iteratory**. Algorytmy operują na danych przechowywanych w kontenerach, a iteratory służą do przechodzenia przez te dane. Ta modularność pozwala na łatwe łączenie różnych komponentów STL w celu tworzenia złożonych operacji na danych.

### Główne komponenty biblioteki STL

STL dostarcza szerokiego wachlarza kontenerów i algorytmów, które można dostosować do różnych potrzeb programistycznych. Najważniejsze komponenty biblioteki STL to:

- **Kontenery sekwencyjne**: `vector`, `list`, `deque`
- **Kontenery asocjacyjne**: `map`, `set`, `unordered_map`, `unordered_set`
- **Kontenery kolejki**: `queue`, `priority_queue`, `stack`
- **Algorytmy**: funkcje do sortowania, wyszukiwania, modyfikowania danych
- **Iteratory**: narzędzia do przechodzenia przez elementy kontenerów

Każdy z tych komponentów jest zoptymalizowany pod kątem określonych operacji, co pozwala na efektywne zarządzanie danymi w różnych scenariuszach.

### Kolekcje w STL

Kolekcje w STL to zbiory implementacji struktur danych wraz z funkcjami operującymi na tych strukturach. STL oferuje różnorodne kontenery, które można wykorzystać w zależności od specyficznych wymagań aplikacji. Wybór odpowiedniego kontenera jest kluczowy dla osiągnięcia optymalnej wydajności i efektywności pamięciowej. Poniżej przedstawione są najczęściej używane kontenery w STL wraz z ich podstawowymi operacjami, przykładami użycia oraz analizą złożoności czasowej.

#### **vector**

`vector` to dynamiczna tablica, która może zmieniać swój rozmiar w trakcie działania programu. Jest jednym z najczęściej używanych kontenerów w STL ze względu na swoją prostotę i wydajność w większości przypadków. `vector` przechowuje elementy w sposób ciągły w pamięci, co umożliwia szybki dostęp do dowolnego elementu poprzez indeks.

Operacje:

| Metoda                | Opis                                                      | Przykład użycia                                           | Złożoność czasowa     |
|-----------------------|-----------------------------------------------------------|-----------------------------------------------------------|-----------------------|
| `push_back(value)`    | Dodaje element na końcu                                   | `vec.push_back(10);`                                      | Amortyzowane O(1)     |
| `pop_back()`          | Usuwa element z końca                                     | `vec.pop_back();`                                         | O(1)                  |
| `size()`              | Zwraca liczbę elementów                                   | `auto s = vec.size();`                                    | O(1)                  |
| `empty()`             | Sprawdza, czy kontener jest pusty                         | `if (vec.empty()) {}`                                     | O(1)                  |
| `clear()`             | Usuwa wszystkie elementy                                  | `vec.clear();`                                            | O(n)                  |
| `insert(pos, value)`  | Wstawia element na podanej pozycji                        | `vec.insert(vec.begin() + 1, 20);`                        | O(n)                  |
| `erase(pos)`          | Usuwa element z podanej pozycji                           | `vec.erase(vec.begin() + 1);`                             | O(n)                  |
| `at(index)`           | Zwraca referencję do elementu na podanym indeksie         | `int val = vec.at(2);`                                     | O(1)                  |
| `operator[]`          | Zwraca referencję do elementu na podanym indeksie         | `int val = vec[2];`                                        | O(1)                  |
| `front()`             | Zwraca referencję do pierwszego elementu                  | `int val = vec.front();`                                   | O(1)                  |
| `back()`              | Zwraca referencję do ostatniego elementu                  | `int val = vec.back();`                                    | O(1)                  |
| `begin()`             | Zwraca iterator na początek                               | `auto it = vec.begin();`                                   | O(1)                  |
| `end()`               | Zwraca iterator na koniec                                 | `auto it = vec.end();`                                     | O(1)                  |
| `reserve(n)`          | Rezerwuje miejsce na n elementów                          | `vec.reserve(100);`                                        | O(n)                  |
| `resize(n)`           | Zmienia rozmiar wektora                                   | `vec.resize(10);`                                          | O(n)                  |

`vector` jest idealnym wyborem, gdy potrzebujemy dynamicznej tablicy z szybkim dostępem do elementów przez indeks. Dzięki ciągłemu rozmieszczeniu w pamięci, operacje takie jak iterowanie czy dostęp losowy są bardzo wydajne. Jednak wstawianie lub usuwanie elementów w środku `vector` może być kosztowne ze względu na konieczność przesuwania innych elementów.

Przykład:

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3};
    vec.push_back(4);
    vec.insert(vec.begin() + 1, 10);
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    return 0;
}
```

W powyższym przykładzie tworzymy `vector` z trzema elementami, dodajemy czwarty element za pomocą `push_back`, wstawiamy nowy element na drugą pozycję za pomocą `insert`, a następnie iterujemy przez wszystkie elementy i je wyświetlamy.

#### **list**

`list` to dwukierunkowa lista wiązana, która umożliwia szybkie wstawianie i usuwanie elementów w dowolnym miejscu listy. W przeciwieństwie do `vector`, `list` nie zapewnia ciągłego rozmieszczenia w pamięci, co sprawia, że dostęp do elementów przez indeks jest mniej wydajny, ale operacje wstawiania i usuwania są bardzo szybkie.

Operacje:

| Metoda                | Opis                                                      | Przykład użycia                                           | Złożoność czasowa     |
|-----------------------|-----------------------------------------------------------|-----------------------------------------------------------|-----------------------|
| `push_back(value)`    | Dodaje element na końcu                                   | `lst.push_back(10);`                                      | O(1)                  |
| `push_front(value)`   | Dodaje element na początku                                | `lst.push_front(5);`                                      | O(1)                  |
| `pop_back()`          | Usuwa element z końca                                     | `lst.pop_back();`                                         | O(1)                  |
| `pop_front()`         | Usuwa element z początku                                  | `lst.pop_front();`                                        | O(1)                  |
| `size()`              | Zwraca liczbę elementów                                   | `auto s = lst.size();`                                    | O(1)                  |
| `empty()`             | Sprawdza, czy kontener jest pusty                         | `if (lst.empty()) {}`                                     | O(1)                  |
| `clear()`             | Usuwa wszystkie elementy                                  | `lst.clear();`                                            | O(n)                  |
| `insert(pos, value)`  | Wstawia element na podanej pozycji                        | `lst.insert(++lst.begin(), 20);`                          | O(1)                  |
| `erase(pos)`          | Usuwa element z podanej pozycji                           | `lst.erase(++lst.begin());`                               | O(1)                  |
| `front()`             | Zwraca referencję do pierwszego elementu                  | `int val = lst.front();`                                   | O(1)                  |
| `back()`              | Zwraca referencję do ostatniego elementu                  | `int val = lst.back();`                                    | O(1)                  |
| `begin()`             | Zwraca iterator na początek                               | `auto it = lst.begin();`                                   | O(1)                  |
| `end()`               | Zwraca iterator na koniec                                 | `auto it = lst.end();`                                     | O(1)                  |

`list` jest idealnym wyborem, gdy potrzebujemy częstych operacji wstawiania i usuwania elementów w różnych miejscach kolekcji. Ze względu na brak ciągłego rozmieszczenia w pamięci, iterowanie przez listę jest nieco mniej wydajne niż w przypadku `vector`, ale korzyści płynące z szybkich operacji wstawiania i usuwania często przeważają w zastosowaniach wymagających dynamicznej modyfikacji danych.

Przykład:

```cpp
#include <iostream>
#include <list>

int main() {
    std::list<int> lst = {1, 2, 3};
    lst.push_back(4);
    lst.push_front(0);
    lst.insert(++lst.begin(), 10);
    for(auto it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    return 0;
}
```

W tym przykładzie tworzymy listę z trzema elementami, dodajemy element na końcu i na początku, wstawiamy nowy element na drugą pozycję, a następnie iterujemy przez wszystkie elementy i je wyświetlamy.

#### **map**

`map` to kontener asocjacyjny, który przechowuje pary klucz-wartość w uporządkowanej formie, wykorzystując drzewo czerwono-czarne. Dzięki temu `map` zapewnia szybki dostęp do wartości na podstawie klucza oraz automatyczne utrzymanie porządku elementów.

Operacje:

| Metoda                    | Opis                                                      | Przykład użycia                                           | Złożoność czasowa     |
|---------------------------|-----------------------------------------------------------|-----------------------------------------------------------|-----------------------|
| `insert({key, value})`    | Wstawia parę klucz-wartość                                 | `mp.insert({1, "one"});`                                  | O(log n)              |
| `erase(key)`              | Usuwa element o podanym kluczu                              | `mp.erase(1);`                                            | O(log n)              |
| `find(key)`               | Zwraca iterator na element o podanym kluczu                 | `auto it = mp.find(1);`                                   | O(log n)              |
| `size()`                  | Zwraca liczbę elementów                                    | `auto s = mp.size();`                                     | O(1)                  |
| `empty()`                 | Sprawdza, czy kontener jest pusty                          | `if (mp.empty()) {}`                                      | O(1)                  |
| `clear()`                 | Usuwa wszystkie elementy                                   | `mp.clear();`                                             | O(n)                  |
| `operator[]`              | Zwraca referencję do wartości o podanym kluczu              | `std::string val = mp[1];`                                | O(log n)              |
| `begin()`                 | Zwraca iterator na początek                                | `auto it = mp.begin();`                                   | O(1)                  |
| `end()`                   | Zwraca iterator na koniec                                  | `auto it = mp.end();`                                     | O(1)                  |

`map` jest niezwykle przydatny, gdy potrzebujemy przechowywać dane w sposób, który umożliwia szybki dostęp do wartości na podstawie unikalnego klucza. Dzięki utrzymaniu uporządkowanego porządku elementów, iterowanie przez `map` pozwala na przeglądanie danych w sposób logiczny i przewidywalny. `map` automatycznie sortuje elementy według kluczy, co ułatwia wykonywanie operacji takich jak przeszukiwanie zakresów czy sortowanie.

Przykład:

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> mp;
    mp.insert({1, "one"});
    mp[2] = "two";
    mp.erase(1);
    for(auto it = mp.begin(); it != mp.end(); ++it) {
        std::cout << it->first << ": " << it->second << " ";
    }
    return 0;
}
```

W tym przykładzie tworzymy `map` z kluczami typu `int` i wartościami typu `std::string`. Wstawiamy parę klucz-wartość za pomocą `insert`, dodajemy kolejną parę za pomocą operatora `[]`, usuwamy element o kluczu `1`, a następnie iterujemy przez wszystkie elementy i je wyświetlamy.

#### **unordered_map**

`unordered_map` to kontener asocjacyjny, który przechowuje pary klucz-wartość w nieuporządkowanej formie, wykorzystując tablicę mieszającą (hash table). Dzięki temu `unordered_map` oferuje bardzo szybki dostęp do elementów na podstawie klucza, zazwyczaj w czasie stałym.

Operacje:

| Metoda                    | Opis                                                      | Przykład użycia                                           | Złożoność czasowa     |
|---------------------------|-----------------------------------------------------------|-----------------------------------------------------------|-----------------------|
| `insert({key, value})`    | Wstawia parę klucz-wartość                                 | `ump.insert({1, "one"});`                                 | O(1) amortyzowane     |
| `erase(key)`              | Usuwa element o podanym kluczu                              | `ump.erase(1);`                                           | O(1) amortyzowane     |
| `find(key)`               | Zwraca iterator na element o podanym kluczu                 | `auto it = ump.find(1);`                                   | O(1) amortyzowane     |
| `size()`                  | Zwraca liczbę elementów                                    | `auto s = ump.size();`                                    | O(1)                  |
| `empty()`                 | Sprawdza, czy kontener jest pusty                          | `if (ump.empty()) {}`                                     | O(1)                  |
| `clear()`                 | Usuwa wszystkie elementy                                   | `ump.clear();`                                            | O(n)                  |
| `operator[]`              | Zwraca referencję do wartości o podanym kluczu              | `std::string val = ump[1];`                               | O(1) amortyzowane     |
| `begin()`                 | Zwraca iterator na początek                                | `auto it = ump.begin();`                                  | O(1)                  |
| `end()`                   | Zwraca iterator na koniec                                  | `auto it = ump.end();`                                    | O(1)                  |

`unordered_map` jest doskonałym wyborem, gdy potrzebujemy bardzo szybkiego dostępu do danych na podstawie klucza, bez konieczności utrzymywania uporządkowanego porządku elementów. Jest idealny do implementacji słowników, buforów pamięci podręcznej i innych struktur, które wymagają szybkiego wyszukiwania. Jednak w przeciwieństwie do `map`, `unordered_map` nie zapewnia uporządkowanego przechowywania elementów, co może być wadą w niektórych zastosowaniach.

Przykład:

```cpp
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    std::unordered_map<int, std::string> ump;
    ump.insert({1, "one"});
    ump[2] = "two";
    ump.erase(1);
    for(auto it = ump.begin(); it != ump.end(); ++it) {
        std::cout << it->first << ": " << it->second << " ";
    }
    return 0;
}
```

W tym przykładzie tworzymy `unordered_map` z kluczami typu `int` i wartościami typu `std::string`. Wstawiamy parę klucz-wartość za pomocą `insert`, dodajemy kolejną parę za pomocą operatora `[]`, usuwamy element o kluczu `1`, a następnie iterujemy przez wszystkie elementy i je wyświetlamy.

#### **set**

`set` to kontener, który przechowuje unikalne elementy w uporządkowanej formie, wykorzystując drzewo czerwono-czarne. `set` zapewnia szybkie wyszukiwanie, wstawianie i usuwanie elementów, utrzymując jednocześnie elementy w uporządkowanym porządku.

Operacje:

| Metoda               | Opis                                                      | Przykład użycia                                           | Złożoność czasowa     |
|----------------------|-----------------------------------------------------------|-----------------------------------------------------------|-----------------------|
| `insert(value)`      | Wstawia element                                            | `st.insert(10);`                                          | O(log n)              |
| `erase(value)`       | Usuwa element                                              | `st.erase(10);`                                           | O(log n)              |
| `find(value)`        | Zwraca iterator na element                                | `auto it = st.find(10);`                                  | O(log n)              |
| `size()`             | Zwraca liczbę elementów                                    | `auto s = st.size();`                                     | O(1)                  |
| `empty()`            | Sprawdza, czy kontener jest pusty                          | `if (st.empty()) {}`                                      | O(1)                  |
| `clear()`            | Usuwa wszystkie elementy                                   | `st.clear();`                                             | O(n)                  |
| `begin()`            | Zwraca iterator na początek                                | `auto it = st.begin();`                                   | O(1)                  |
| `end()`              | Zwraca iterator na koniec                                  | `auto it = st.end();`                                     | O(1)                  |

`set` jest użyteczny, gdy potrzebujemy przechowywać zbiór unikalnych elementów i często wykonywać operacje takie jak sprawdzanie obecności elementu, wstawianie czy usuwanie. Utrzymanie uporządkowanego porządku elementów umożliwia efektywne iterowanie w określonej kolejności oraz wykonywanie operacji zakresowych.

Przykład:

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> st;
    st.insert(10);
    st.insert(20);
    st.erase(10);
    for(auto it = st.begin(); it != st.end(); ++it) {
        std::cout << *it << " ";
    }
    return 0;
}
```

W tym przykładzie tworzymy `set` z elementami typu `int`, wstawiamy kilka elementów, usuwamy jeden z nich, a następnie iterujemy przez wszystkie pozostałe elementy i je wyświetlamy.

#### **unordered_set**

`unordered_set` to kontener, który przechowuje unikalne elementy w nieuporządkowanej formie, wykorzystując tablicę mieszającą (hash table). Dzięki temu `unordered_set` oferuje bardzo szybkie operacje wyszukiwania, wstawiania i usuwania elementów, zazwyczaj w czasie stałym.

Operacje:

| Metoda               | Opis                                                      | Przykład użycia                                           | Złożoność czasowa     |
|----------------------|-----------------------------------------------------------|-----------------------------------------------------------|-----------------------|
| `insert(value)`      | Wstawia element                                            | `ust.insert(10);`                                         | O(1) amortyzowane     |
| `erase(value)`       | Usuwa element                                              | `ust.erase(10);`                                          | O(1) amortyzowane     |
| `find(value)`        | Zwraca iterator na element                                | `auto it = ust.find(10);`                                 | O(1) amortyzowane     |
| `size()`             | Zwraca liczbę elementów                                    | `auto s = ust.size();`                                     | O(1)                  |
| `empty()`            | Sprawdza, czy kontener jest pusty                          | `if (ust.empty()) {}`                                     | O(1)                  |
| `clear()`            | Usuwa wszystkie elementy                                   | `ust.clear();`                                            | O(n)                  |
| `begin()`            | Zwraca iterator na początek                                | `auto it = ust.begin();`                                   | O(1)                  |
| `end()`              | Zwraca iterator na koniec                                  | `auto it = ust.end();`                                     | O(1)                  |

`unordered_set` jest idealnym wyborem, gdy potrzebujemy przechowywać unikalne elementy i wykonywać szybkie operacje wyszukiwania bez konieczności utrzymywania uporządkowanego porządku. Jest szczególnie przydatny w sytuacjach, gdzie kolejność elementów nie ma znaczenia, a kluczowa jest szybkość dostępu do danych.

Przykład:

```cpp
#include <iostream>
#include <unordered_set>

int main() {
    std::unordered_set<int> ust;
    ust.insert(10);
    ust.insert(20);
    ust.erase(10);
    for(auto it = ust.begin(); it != ust.end(); ++it) {
        std::cout << *it << " ";
    }
    return 0;
}
```

W tym przykładzie tworzymy `unordered_set` z elementami typu `int`, wstawiamy kilka elementów, usuwamy jeden z nich, a następnie iterujemy przez wszystkie pozostałe elementy i je wyświetlamy.

#### **priority_queue**

`priority_queue` to kontener, który implementuje kopiec binarny i pozwala na szybkie wyciąganie największego (lub najmniejszego) elementu. `priority_queue` jest przydatny w zastosowaniach, gdzie potrzebujemy dynamicznie utrzymywać zbiór elementów w taki sposób, aby zawsze mieć szybki dostęp do najwyższego priorytetu.

Operacje:

| Metoda               | Opis                                                      | Przykład użycia                                           | Złożoność czasowa     |
|----------------------|-----------------------------------------------------------|-----------------------------------------------------------|-----------------------|
| `push(value)`        | Dodaje element                                             | `pq.push(10);`                                            | O(log n)              |
| `pop()`              | Usuwa największy element                                   | `pq.pop();`                                               | O(log n)              |
| `top()`              | Zwraca referencję do największego elementu                | `int val = pq.top();`                                     | O(1)                  |
| `size()`             | Zwraca liczbę elementów                                    | `auto s = pq.size();`                                     | O(1)                  |
| `empty()`            | Sprawdza, czy kontener jest pusty                          | `if (pq.empty()) {}`                                      | O(1)                  |

`priority_queue` jest użyteczny w algorytmach takich jak Dijkstra czy Huffman, gdzie konieczne jest szybkie wyciąganie elementów o najwyższym priorytecie. Dzięki strukturze kopca binarnego, `priority_queue` zapewnia efektywne zarządzanie elementami i szybki dostęp do najbardziej istotnych danych.

Przykład:

```cpp
#include <iostream>
#include <queue>

int main() {
    std::priority_queue<int> pq;
    pq.push(10);
    pq.push(20);
    pq.push(5);
    std::cout << pq.top() << " "; // wyświetli 20
    pq.pop();
    std::cout << pq.top() << " "; // wyświetli 10
    return 0;
}
```

W tym przykładzie tworzymy `priority_queue` z elementami typu `int`, dodajemy kilka elementów, a następnie wyciągamy i wyświetlamy największy element za pomocą `top` oraz `pop`.

#### **queue**

`queue` to kontener, który implementuje kolejkę FIFO (First In, First Out). `queue` jest idealny do sytuacji, gdzie kolejność przetwarzania elementów jest istotna, na przykład w symulacjach systemów kolejkowych czy zarządzaniu zadaniami.

Operacje:

| Metoda               | Opis                                                      | Przykład użycia                                           | Złożoność czasowa     |
|----------------------|-----------------------------------------------------------|-----------------------------------------------------------|-----------------------|
| `push(value)`        | Dodaje element                                             | `q.push(10);`                                             | O(1)                  |
| `pop()`              | Usuwa element z początku                                   | `q.pop();`                                                | O(1)                  |
| `front()`            | Zwraca referencję do pierwszego elementu                  | `int val = q.front();`                                    | O(1)                  |
| `back()`             | Zwraca referencję do ostatniego elementu                  | `int val = q.back();`                                     | O(1)                  |
| `size()`             | Zwraca liczbę elementów                                    | `auto s = q.size();`                                      | O(1)                  |
| `empty()`            | Sprawdza, czy kontener jest pusty                          | `if (q.empty()) {}`                                       | O(1)                  |

`queue` jest prostym i efektywnym narzędziem do zarządzania danymi w sposób kolejnościowy. Dzięki temu kontenerowi możemy łatwo implementować mechanizmy przetwarzania danych, gdzie pierwszy element w kolejce jest przetwarzany jako pierwszy, a ostatni jako ostatni.

Przykład:

```cpp
#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;
    q.push(10);
    q.push(20);
    std::cout << q.front() << " "; // wyświetli 10
    q.pop();
    std::cout << q.front() << " "; // wyświetli 20
    return 0;
}
```

W tym przykładzie tworzymy `queue` z elementami typu `int`, dodajemy kilka elementów, a następnie wyciągamy i wyświetlamy pierwszy element za pomocą `front` oraz `pop`.

#### **stack**

`stack` to kontener, który implementuje stos LIFO (Last In, First Out). `stack` jest użyteczny w sytuacjach, gdzie potrzebujemy struktury danych działającej na zasadzie ostatniego przyjętego elementu jako pierwszego do przetworzenia, na przykład w algorytmach rekurencyjnych czy przetwarzaniu wyrażeń.

Operacje:

| Metoda               | Opis                                                      | Przykład użycia                                           | Złożoność czasowa     |
|----------------------|-----------------------------------------------------------|-----------------------------------------------------------|-----------------------|
| `push(value)`        | Dodaje element                                             | `st.push(10);`                                            | O(1)                  |
| `pop()`              | Usuwa element z końca                                      | `st.pop();`                                               | O(1)                  |
| `top()`              | Zwraca referencję do ostatniego elementu                  | `int val = st.top();`                                     | O(1)                  |
| `size()`             | Zwraca liczbę elementów                                    | `auto s = st.size();`                                     | O(1)                  |
| `empty()`            | Sprawdza, czy kontener jest pusty                          | `if (st.empty()) {}`                                      | O(1)                  |

`stack` jest doskonałym wyborem, gdy potrzebujemy prostego mechanizmu do przechowywania danych w odwrotnej kolejności. Dzięki swojej prostocie i wydajności, `stack` znajduje zastosowanie w wielu algorytmach, takich jak przetwarzanie wyrażeń matematycznych, czy implementacja funkcji rekurencyjnych.

Przykład:

```cpp
#include <iostream>
#include <stack>

int main() {
    std::stack<int> st;
    st.push(10);
    st.push(20);
    std::cout << st.top() << " "; // wyświetli 20
    st.pop();
    std::cout << st.top() << " "; // wyświetli 10
    return 0;
}
```

W tym przykładzie tworzymy `stack` z elementami typu `int`, dodajemy kilka elementów, a następnie wyciągamy i wyświetlamy ostatni dodany element za pomocą `top` oraz `pop`.

### Iteratory

Iteratory w języku C++ są fundamentem, który umożliwia efektywną i elastyczną pracę z różnorodnymi kontenerami dostarczanymi przez Standard Template Library (STL). Iteratory to obiekty, które umożliwiają sekwencyjny dostęp do elementów kontenerów, takich jak `vector`, `list`, `map` i inne. Dzięki nim możliwe jest pisanie generycznego kodu, który działa niezależnie od konkretnego typu kontenera, co znacznie zwiększa reużywalność i elastyczność kodu.

Podobnie jak wskaźniki, iteratory mogą być dereferencjonowane, aby uzyskać dostęp do wartości przechowywanych w kontenerze, oraz mogą być inkrementowane lub dekrementowane, aby przechodzić do następnych lub poprzednich elementów. Jednak iteratory oferują więcej możliwości i bezpieczeństwa, ponieważ są zaprojektowane tak, aby współpracować bezpośrednio z kontenerami STL, zapewniając zgodność typów i chroniąc przed nieprawidłowymi operacjami.

Iteratory są niezbędne do korzystania z algorytmów STL, które operują na zakresach określonych przez iteratory. Dzięki temu można łatwo przetwarzać dane w kontenerach za pomocą gotowych funkcji, bez konieczności implementowania własnych pętli czy struktur kontrolnych.

#### Rodzaje iteratorów

W STL istnieje kilka kategorii iteratorów, z których każda oferuje różne możliwości i jest przeznaczona do określonych zastosowań. Znajomość tych rodzajów iteratorów pozwala na lepsze zrozumienie, jak efektywnie korzystać z kontenerów i algorytmów STL.

| Typ iteratora                | Opis                                                                                 |
|------------------------------|---------------------------------------------------------------------------------------|
| **Input Iterator**           | Służy do odczytu danych z kontenera. Można go używać do jednorazowego przechodzenia przez elementy w jednym kierunku. Idealny do przetwarzania danych w sekwencji bez modyfikacji. |
| **Output Iterator**          | Służy do zapisu danych do kontenera. Pozwala na jednorazowe przechodzenie przez elementy i modyfikowanie ich wartości. |
| **Forward Iterator**         | Łączy możliwości iteratorów input i output. Może przemieszczać się tylko do przodu, ale może zarówno czytać, jak i pisać dane. |
| **Bidirectional Iterator**   | Umożliwia przemieszczanie się zarówno do przodu, jak i do tyłu. Przydatny w kontenerach, które wspierają dwukierunkowy dostęp, takich jak `list`. |
| **Random Access Iterator**   | Oferuje wszystkie możliwości Bidirectional Iterator oraz umożliwia dostęp do dowolnego elementu kontenera w stałym czasie. Pozwala na operacje arytmetyczne na iteratorach, takie jak przesunięcie o określoną liczbę pozycji. Idealny dla kontenerów takich jak `vector` czy `deque`. |

#### Podstawowe operacje na iteratorach

Praca z iteratorami obejmuje kilka podstawowych operacji, które umożliwiają manipulowanie i przeglądanie elementów kontenerów. Poniżej przedstawiono najważniejsze z nich:

- **Inicjalizacja iteratora początkowym elementem kontenera:** Aby rozpocząć iterację, należy zainicjalizować iterator na początku kontenera za pomocą `kontener.begin()`. To pozwala na dostęp do pierwszego elementu.
  
  ```cpp
  auto it = kontener.begin();
  ```

- **Inicjalizacja iteratora elementem za ostatnim w kontenerze:** Iterator `kontener.end()` wskazuje na element za ostatnim elementem w kontenerze. Jest to przydatne do oznaczania końca zakresu podczas iteracji.
  
  ```cpp
  auto it_end = kontener.end();
  ```

- **Odwołanie do elementu, na który wskazuje iterator:** Używając operatora dereferencji `*`, możemy uzyskać dostęp do wartości przechowywanej w elemencie, na który wskazuje iterator.
  
  ```cpp
  auto element = *it;
  ```

- **Przesunięcie iteratora do następnego elementu:** Operator `++` umożliwia przejście do kolejnego elementu w kontenerze.
  
  ```cpp
  ++it;
  ```

- **Przesunięcie iteratora do poprzedniego elementu:** Operator `--` pozwala na powrót do poprzedniego elementu. Jest dostępny tylko dla iteratorów dwukierunkowych i iteratorów o losowym dostępie.
  
  ```cpp
  --it;
  ```

- **Przesunięcie iteratora o określoną liczbę pozycji:** Dla iteratorów o losowym dostępie, możemy przesuwać iterator o określoną liczbę pozycji za pomocą operatorów arytmetycznych.
  
  ```cpp
  it += n; // Przesunięcie do przodu o n pozycji
  it -= n; // Przesunięcie do tyłu o n pozycji
  ```

- **Wstawienie elementu w miejscu wskazywanym przez iterator:** Metoda `insert` umożliwia dodanie nowego elementu przed pozycją wskazywaną przez iterator.
  
  ```cpp
  it = kontener.insert(it, wartość);
  ```

- **Usunięcie elementu w miejscu wskazywanym przez iterator:** Metoda `erase` pozwala na usunięcie elementu na pozycji wskazywanej przez iterator i zwraca iterator do następnego elementu.
  
  ```cpp
  it = kontener.erase(it);
  ```

#### Przykład użycia iteratora

Poniższy przykład ilustruje podstawowe operacje na iteratorech w kontekście kontenera `std::vector` typu `std::string`. Program tworzy wektor z trzema elementami, wyświetla jego zawartość przy użyciu iteratora, dodaje nowy element przed drugim elementem, usuwa pierwszy element, a następnie ponownie wyświetla zmodyfikowaną zawartość wektora.

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> v = {"ala", "ma", "kota"};

    // Wyświetlenie zawartości wektora przy użyciu iteratora
    std::cout << "Zawartość wektora przed modyfikacjami:\n";
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

**Wyjście programu:**
```
Zawartość wektora przed modyfikacjami:
ala
ma
kota

Po modyfikacjach:
ma
nie
kota
```

Warto pamiętać, że po niektórych operacjach, takich jak `insert` czy `erase`, używane wcześniej iteratory mogą stać się nieaktualne i ich dalsze użycie może prowadzić do niezdefiniowanego zachowania programu. Dlatego zaleca się ponowne inicjalizowanie iteratorów po modyfikacji kontenera.

### Algorytmy w Standardowej Bibliotece C++ (STL)

Biblioteka `algorithm` w standardowej bibliotece C++ (STL) dostarcza bogaty zestaw funkcji szablonowych, które służą do manipulacji i analizy danych przechowywanych w kontenerach. Algorytmy te są zaprojektowane w sposób generyczny, co oznacza, że mogą działać z różnymi typami danych i kontenerami, pod warunkiem spełnienia określonych wymagań. W tej sekcji przyjrzymy się kilku kluczowym algorytmom, ich implementacji, zastosowaniu oraz analizie matematycznej wydajności.

#### Wprowadzenie do Algorytmów STL

Algorytmy w STL są zaimplementowane jako funkcje szablonowe, co pozwala na ich użycie z różnymi typami danych i kontenerami. Działają one na zakresach określonych przez iteratory, co zapewnia elastyczność i niezależność od konkretnego typu kontenera. Dzięki temu możliwe jest pisanie kodu, który jest jednocześnie uniwersalny i wydajny.

Algorytmy STL są zoptymalizowane pod kątem wydajności oraz zgodności z różnymi typami iteratorów. Pozwalają na wykonywanie złożonych operacji na danych w sposób zwięzły i czytelny, redukując potrzebę pisania własnych implementacji podstawowych funkcji przetwarzania danych.

#### Klasyfikacja Algorytmów

Algorytmy STL można podzielić na kilka kategorii, w zależności od rodzaju operacji, które wykonują na danych:

| Kategoria algorytmów                    | Przykłady                                                                 |
|-----------------------------------------|---------------------------------------------------------------------------|
| **Algorytmy modyfikujące**              | `std::copy`, `std::fill`, `std::transform`                                |
| **Algorytmy przeszukujące**             | `std::find`, `std::count`, `std::search`                                  |
| **Algorytmy sortujące i porządkujące**  | `std::sort`, `std::stable_sort`, `std::partial_sort`                      |
| **Algorytmy numeryczne**                | `std::accumulate`, `std::inner_product`, `std::partial_sum`               |
| **Algorytmy usuwające**                 | `std::remove`, `std::unique`, `std::remove_if`                            |

Każda z tych kategorii obejmuje algorytmy, które są zoptymalizowane do wykonywania specyficznych operacji na danych, co pozwala na efektywne zarządzanie i przetwarzanie informacji w aplikacjach.

#### `std::sort()`

Funkcja `std::sort()` służy do sortowania elementów w określonym zakresie. Jest to jeden z najczęściej używanych algorytmów w STL ze względu na swoją uniwersalność i wydajność. `std::sort()` wykorzystuje algorytm sortowania introspektywnego (introsort), który łączy zalety sortowania szybkiego (quick sort), sortowania kopcowego (heap sort) i sortowania przez wstawianie (insertion sort).

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

**Wyjście programu:**
```
Wektor po częściowym sortowaniu: 3 5 8 1 2 4 6 7 
Wektor po pełnym sortowaniu: 1 2 3 4 5 6 7 8 
```

**Analiza Matematyczna:**

- **Złożoność czasowa** dla tego algorytmu wynosi średnio $O(n \log n)$, co jest charakterystyczne dla wydajnych algorytmów sortowania.
- W najgorszym przypadku złożoność czasowa również wynosi $O(n \log n)$, ponieważ algorytm wykorzystuje introsort, który automatycznie przełącza się na sortowanie kopcowe, gdy wykryje niekorzystny podział danych.
- **Złożoność pamięciowa** tego algorytmu wymaga $O(\log n)$ dodatkowej pamięci, głównie na stos rekurencji, co czyni go efektywnym pod względem użycia zasobów pamięci.

**Dostosowywanie Kryterium Sortowania:**

Możemy dostarczyć własną funkcję porównującą, aby zmienić domyślne kryterium sortowania. Na przykład, aby posortować elementy w kolejności malejącej:

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

**Wyjście programu:**
```
Znaleziono element o wartości 3 na pozycji 1
```

**Analiza Matematyczna:**

- **Złożoność czasowa** wynosi $O(n)$, gdzie n oznacza liczbę elementów w przetwarzanym zakresie, co sprawia, że algorytm działa liniowo względem liczby danych.
- **Złożoność pamięciowa** wynosi $O(1)$, co oznacza, że algorytm nie wymaga dodatkowej pamięci poza tą używaną przez same dane.

**Uwagi:**

- Algorytm przeszukuje liniowo zakres od `first` do `last`, co oznacza, że w najgorszym przypadku musi sprawdzić każdy element.
- Możemy użyć `std::find_if()` lub `std::find_if_not()` do przeszukiwania z warunkiem predykatu, co pozwala na bardziej elastyczne wyszukiwanie w oparciu o złożone kryteria.

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

**Wyjście programu:**
```
Wektor po modyfikacji: 16 6 10 2 4 8 12 14 
```

**Analiza Matematyczna:**

- **Złożoność czasowa** wynosi **O(n)**, ponieważ funkcja jest wywoływana dokładnie n razy, co oznacza liniowy wzrost liczby operacji w zależności od liczby elementów.
- **Złożoność pamięciowa** wynosi **O(1)**, gdyż algorytm nie wymaga dodatkowej pamięci poza ewentualnymi zmiennymi lokalnymi w funkcji.

**Uwagi:**

- Funkcja `UnaryFunction` jest przekazywana przez wartość, więc jeśli potrzebujemy zachować stan między wywołaniami, należy użyć referencji lub obiektu zewnętrznego.
- Zwracana jest kopia funkcji `UnaryFunction` po ostatnim wywołaniu, co może być użyte do akumulacji wyników.
- `std::for_each()` może być używany do wykonywania różnych operacji na elementach kontenera, takich jak modyfikowanie ich wartości, wyświetlanie, czy zbieranie informacji.

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

**Wyjście programu:**
```
Liczba parzystych elementów: 4
```

**Analiza Matematyczna:**

- **Złożoność czasowa** wynosi **O(n)**, ponieważ predykat jest wywoływany dokładnie n razy, co sprawia, że liczba operacji rośnie liniowo w zależności od liczby elementów.
- **Złożoność pamięciowa** wynosi **O(1)**, co oznacza, że algorytm nie wymaga dodatkowej pamięci poza zmiennymi lokalnymi.

**Uwagi:**

- Jeśli chcemy zliczyć wystąpienia konkretnej wartości, możemy użyć `std::count()`, co jest bardziej efektywne i czytelne w takim przypadku.
- `std::count_if()` jest szczególnie przydatny, gdy potrzebujemy zliczyć elementy spełniające bardziej złożone warunki niż prosty równość.

#### Inne Ważne Algorytmy

##### `std::accumulate()`

Funkcja `std::accumulate()` służy do obliczenia sumy wartości w zakresie, z opcjonalnym początkowym akumulatorem i funkcją operacji.

**Prototyp:**

```cpp
template< class InputIt, class T >
T accumulate( InputIt first, InputIt last, T init );

template< class InputIt, class T, class BinaryOperation >
T accumulate( InputIt first, InputIt last, T init, BinaryOperation op );
```

**Przykład Użycia:**

```cpp
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> wektor{1, 2, 3, 4, 5};

    // Obliczenie sumy elementów
    int suma = std::accumulate(wektor.begin(), wektor.end(), 0);
    std::cout << "Suma elementów: " << suma << "\n";

    // Obliczenie iloczynu elementów
    int iloczyn = std::accumulate(wektor.begin(), wektor.end(), 1, std::multiplies<int>());
    std::cout << "Iloczyn elementów: " << iloczyn << "\n";

    return 0;
}
```

**Wyjście programu:**
```
Suma elementów: 15
Iloczyn elementów: 120
```

**Uwagi:**

- `std::accumulate()` może być używany nie tylko do sumowania wartości, ale także do wykonywania bardziej złożonych operacji, takich jak obliczanie iloczynu, łączenie stringów czy budowanie innych struktur danych.
- Funkcja `BinaryOperation` pozwala na zdefiniowanie dowolnej operacji akumulującej, co zwiększa elastyczność `std::accumulate()`.

##### `std::transform()`

Funkcja `std::transform()` stosuje podaną funkcję do każdego elementu w zakresie i zapisuje wynik w innym zakresie.

**Prototyp:**

```cpp
template< class InputIt, class OutputIt, class UnaryOperation >
OutputIt transform( InputIt first1, InputIt last1, OutputIt d_first, UnaryOperation unary_op );

template< class InputIt1, class InputIt2, class OutputIt, class BinaryOperation >
OutputIt transform( InputIt1 first1, InputIt1 last1,
                   InputIt2 first2, OutputIt d_first, BinaryOperation binary_op );
```

**Przykład Użycia:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> wektor{1, 2, 3, 4, 5};
    std::vector<int> wyniki(wektor.size());

    // Stosowanie funkcji lambda do podwojenia każdego elementu
    std::transform(wektor.begin(), wektor.end(), wyniki.begin(), [](int x) { return x * 2; });

    // Wyświetlanie wyników
    std::cout << "Wyniki po transformacji: ";
    for (const auto& val : wyniki) {
        std::cout << val << " ";
    }

    return 0;
}
```

**Wyjście programu:**
```
Wyniki po transformacji: 2 4 6 8 10 
```

**Uwagi:**

- `std::transform()` jest niezwykle użyteczny do przekształcania danych w kontenerach, bez konieczności tworzenia dodatkowych pętli czy tymczasowych zmiennych.
- Może być używany zarówno do jednoczesnego przetwarzania jednego, jak i dwóch zakresów, co pozwala na tworzenie bardziej złożonych operacji przekształcania danych.

#### Kompatybilność z Iteratorami

Algorytmy STL są zaprojektowane tak, aby działać z różnymi kategoriami iteratorów, co zapewnia ich szeroką kompatybilność z różnymi typami kontenerów. Poniżej przedstawiono, które kategorie iteratorów są obsługiwane przez poszczególne klasy algorytmów:

| Kategoria          | Przykłady Algorytmów               |
|--------------------|------------------------------------|
| Iteratory wejściowe  | `std::find`, `std::count_if`       |
| Iteratory wyjściowe  | `std::copy`, `std::fill`           |
| Iteratory jedno kierunkowe | `std::for_each`, `std::remove`      |
| Iteratory dwukierunkowe | `std::reverse`, `std::rotate`     |
| Iteratory losowego dostępu | `std::sort`, `std::nth_element` |

**Przykładowa Implementacja:**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    std::vector<int> wektor{1, 2, 3, 4, 5};

    // Użycie std::for_each z iteratorami jedno kierunkowymi
    std::for_each(wektor.begin(), wektor.end(), [](int &x) { x += 10; });

    // Użycie std::find z iteratorami wejściowymi
    auto it = std::find(wektor.begin(), wektor.end(), 13);
    if (it != wektor.end())
        std::cout << "Znaleziono element: " << *it << "\n";
    else
        std::cout << "Element nie został znaleziony.\n";

    // Użycie std::sort z iteratorami losowego dostępu
    std::vector<int> wektor2 = {5, 3, 1, 4, 2};
    std::sort(wektor2.begin(), wektor2.end());

    std::cout << "Posortowany wektor2: ";
    for (const auto& val : wektor2) {
        std::cout << val << " ";
    }

    return 0;
}
```

**Wyjście programu:**
```
Znaleziono element: 13
Posortowany wektor2: 1 2 3 4 5 
```

#### Zastosowanie Algorytmów w Praktyce

Algorytmy STL pozwalają na pisanie kodu o wysokim poziomie abstrakcji, co zwiększa czytelność i redukuje ryzyko błędów. Dzięki generyczności i wykorzystaniu szablonów, algorytmy te są niezwykle elastyczne i mogą być stosowane w szerokim zakresie zastosowań.

**Przykład: Analiza Danych Finansowych**

Załóżmy, że mamy wektor reprezentujący dzienne zmiany cen akcji i chcemy przeprowadzić analizę:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
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

    return 0;
}
```

**Wyjście programu:**

```
Sumaryczna zmiana cen: -0.3
Liczba dni ze wzrostem cen: 4
Największy spadek: -1
```

W tym przykładzie wykorzystujemy różne algorytmy STL do przeprowadzenia analizy danych finansowych:
- `std::accumulate()` oblicza sumę wszystkich zmian cen.
- `std::count_if()` zlicza liczbę dni, w których cena wzrosła.
- `std::min_element()` znajduje największy spadek w cenach.

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

**Porównanie:**

Korzystanie z `std::count_if()` nie tylko skraca kod, ale również zwiększa jego czytelność i potencjalnie wydajność. Algorytm STL może być zoptymalizowany lepiej niż ręcznie napisane pętle, a dodatkowo kod staje się bardziej zwięzły i łatwy do zrozumienia.
