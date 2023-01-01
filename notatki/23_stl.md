
## STL

STL (Standard Template Library) jest biblioteką, która implementuje wiele przydatnych funkcji, algorytmów i struktur danych. W skład STL wchodzą między innymi:

    <vector>
    <list>
    <map>
    <set>
    <queue>
    <stack>
    <algorithm>
    <iterator>
    <memory>

### Kolekcje

Kolekcje to implementacje struktur danych wraz z wieloma funkcjami, przeznaczonymi do pracy z nimi.

1. unordered_map

Kontener unordered_map implementuje tablicę mieszającą.

| operacja | złożoność czasowa |
|---|---|
| wyszukiwanie | O(1) |
| wstawianie | O(1) | 
| usuwanie | O(1) | 

2. map

Kontener map implementuje drzewo czerwono-czarne.

| operacja | złożoność czasowa |
|---|---|
| wyszukiwanie | O(log n) |
| wstawianie | O(log n) | 
| usuwanie | O(log n) | 

3. priority_queue

Kontener priority_queue implementuje kopiec.

| operacja | złożoność czasowa |
|---|---|
| wstawianie | O(log n) |
| zdejmowanie | O(log n) | 
| wierzchołek | O(1) | 

4. list

Kontener list implementuje listę dwukierunkową.

| operacja | złożoność czasowa |
|---|---|
| wyszukiwanie | O(n) |
| wstawianie | O(n) | 
| usuwanie | O(n) | 

5. vector

Kontener vector implementuje tablicę dynamiczną.

| operacja | złożoność czasowa |
|---|---|
| dostawianie na koniec | O(1) |
| usuwanie z końca | O(1) | 
| dostawianie (ogólnie) | O(n) | 
| usuwanie (ogólnie) | O(n) | 
| wyszukiwanie | O(n) | 

6. unordered_set

Struktura unordered_set implementuje tablicę mieszającą.

| operacja | złożoność czasowa |
|---|---|
| wyszukiwanie | O(1) |
| wstawianie | O(1) | 
| usuwanie | O(1) | 

7. set

Struktura set implementuje drzewo czerwono-czarne.

| operacja | złożoność czasowa |
|---|---|
| wyszukiwanie | O(log n) |
| wstawianie | O(log n) | 
| usuwanie | O(log n) | 

### Iteratory

Iteratory to konstrukcje, które umożliwiają jednolitą iterację po elementach kolekcji. Dzięki temu nie musimy zapoznawać się z osobnymi mechanizmami dla każdej kolekcji, możemy zawsze użyć iteratorów.

W poniższym przykładzie wykorzystano iterator do wyświetlenia elementów wektora:

```c++
#include <iostream>
#include <string>
#include <vector>

int main() {
  vector<string> v;
  v.push_back("ala");
  v.push_back("ma");
  v.push_back("kota");

  for (auto it = v.begin(); it != v.end(); ++it)
    std::cout << *it << std::endl;

  return 0;
}
```

Iterator do pierwszego elementu kolekcji to:

    kontener.begin()

Iterator do następnego elementu za ostatnim to:

    kontener.end()

Wartość na którą wskazuje iterator <code>it</code> to:

    *it

Dodanie elementu poprzez iterator <code>it</code>:

    it = kontener.insert(it, "ala");

Usunięcie elementu poprzez iterator <code>it</code>:

    it = kontener.erase(it);

### Algorytmy

Biblioteka <code>algorithm</code> zawiera wiele funkcji, które mogą być użyte do pracy z kolekcjami. Przyjrzyjmy się teraz kilku przykładom.

#### sort()

Dzięki funkcji <code>sort()</code> możemy posortować częściowo lub całkowicie kolekcję. Pierwszym argumentem jest iterator od którego mamy zacząć sortowanie, a drugim to iterator na którym mamy zakończyć sortowanie.

```c++
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

### find()

Funkcja <code>find()</code> zwróci nam iterator odpowiadający szukanemu elementowi. Pierwszym argumentem jest iterator, od którego mamy zacząć szukanie, drugim jest iterator, na którym mamy zakończyć szukanie, a trzecim jest szukany element.

```c++
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

### for_each()

Jeśli chcemy jakąś operację wykonać na każdym elemencie kolekcji, możemy użyć funkcji <code>for_each()</code>. Pierwszym argumentem jest iterator, od którego mamy zacząć wykonywanie operacji, drugim jest iterator, na którym mamy zakończyć wykonywanie operacji, a trzecim jest funkcja, która będzie wywoływana na każdym elemencie.

```c++
#include <vector>
#include <algorithm>

int main() {

  std::vector<int> wektor{8, 3, 5, 1, 2, 4, 6, 7};
  std::for_each(wektor.begin(), wektor.end(), [](int &x) { x *= 2; });
  // wynik: [16, 6, 10, 2, 4, 8, 12, 14]

  return 0;
}
```
