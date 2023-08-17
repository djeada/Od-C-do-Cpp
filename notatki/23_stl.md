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

1. **unordered_map**

    Kontener `unordered_map` implementuje tablicę mieszającą (hash table).

    | Operacja        | Złożoność czasowa |
    |-----------------|-------------------|
    | Wyszukiwanie    | O(1)              |
    | Wstawianie      | O(1)              |
    | Usuwanie        | O(1)              |

2. **map**

    Kontener `map` implementuje drzewo czerwono-czarne.

    | Operacja        | Złożoność czasowa |
    |-----------------|-------------------|
    | Wyszukiwanie    | O(log n)          |
    | Wstawianie      | O(log n)          |
    | Usuwanie        | O(log n)          |

3. **priority_queue**

    Kontener `priority_queue` implementuje kopiec binarny.

    | Operacja        | Złożoność czasowa |
    |-----------------|-------------------|
    | Wstawianie      | O(log n)          |
    | Zdejmowanie     | O(log n)          |
    | Wierzchołek     | O(1)              |

4. **list**

    Kontener `list` implementuje dwukierunkową listę wiązaną.

    | Operacja        | Złożoność czasowa |
    |-----------------|-------------------|
    | Wyszukiwanie    | O(n)              |
    | Wstawianie      | O(1)              |
    | Usuwanie        | O(1)              |

5. **vector**

    Kontener `vector` implementuje dynamiczną tablicę.

    | Operacja               | Złożoność czasowa |
    |------------------------|-------------------|
    | Dodawanie na koniec    | O(1) (amortyzowana)|
    | Usuwanie z końca       | O(1)              |
    | Dodawanie (ogólnie)    | O(n)              |
    | Usuwanie (ogólnie)     | O(n)              |
    | Wyszukiwanie           | O(n)              |

6. **unordered_set**

    Kontener `unordered_set` implementuje tablicę mieszającą.

    | Operacja        | Złożoność czasowa |
    |-----------------|-------------------|
    | Wyszukiwanie    | O(1)              |
    | Wstawianie      | O(1)              |
    | Usuwanie        | O(1)              |

7. **set**

    Kontener `set` implementuje drzewo czerwono-czarne.

    | Operacja        | Złożoność czasowa |
    |-----------------|-------------------|
    | Wyszukiwanie    | O(log n)          |
    | Wstawianie      | O(log n)          |
    | Usuwanie        | O(log n)          |

### Iteratory

Iteratory w języku C++ to obiekty umożliwiające sekwencyjny dostęp do elementów kontenerów. Dzięki nim możliwe jest jednolite przeglądanie zawartości różnych typów kolekcji, niezależnie od ich wewnętrznej implementacji.

Podstawowe operacje na iteratorach:
- Inicjalizacja iteratora początkowym elementem kontenera: `kontener.begin()`
- Inicjalizacja iteratora elementem za ostatnim w kontenerze: `kontener.end()`
- Odwołanie do elementu, na który wskazuje iterator: `*it`
- Przesunięcie iteratora do następnego elementu: `++it`
- Wstawienie elementu w miejscu wskazywanym przez iterator: `it = kontener.insert(it, wartość)`
- Usunięcie elementu w miejscu wskazywanym przez iterator: `it = kontener.erase(it)`

Przykład użycia iteratora do przeglądania i modyfikowania zawartości wektora:

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
    std::cout << "Znaleziono element o wartości 3" << std::endl;

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
  // wynik: [16, 6, 10, 2, 4, 8, 12, 14]

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

Powyższy kod wykorzystuje `count_if()` do zliczenia parzystych elementów w wektorze.
