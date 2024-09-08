## Zaawansowane wskaźniki

Wskaźniki w C++ nie służą jedynie do przechowywania adresów zmiennych czy obiektów. Są one znacznie bardziej wszechstronne i umożliwiają wskaźnikom na funkcje, metody klasy czy składowe klas.

### Wskaźniki na funkcje

Wskaźniki na funkcje pozwalają na dynamiczne wywoływanie różnych funkcji w zależności od potrzeb. Jest to szczególnie przydatne, gdy chcemy przekazać operację jako argument do innej funkcji.

```c++
#include <iostream>

void funkcjaWysokopoziomowa(void (*f)(int), int a) { f(a); }

void zwieksz(int a) { std::cout << a + 1 << std::endl; }

void zmniejsz(int a) { std::cout << a - 1 << std::endl; }

int main() {
  funkcjaWysokopoziomowa(zwieksz, 10);
  funkcjaWysokopoziomowa(zmniejsz, 10);
  return 0;
}
```

### Wskaźniki do składowych klasy

Wskaźniki mogą również wskazywać na składowe klas, co pozwala na dynamiczny dostęp do różnych składowych obiektu.

```c++
#include <iostream>

class Foo {
public:
  int x;
  int y;

  Foo(int x, int y) : x(x), y(y) {}
};

int main() {
  Foo foo(10, 20);

  // wskazniki na zwykle pola
  int *x = &foo.x;
  int *y = &foo.y;
  *x = 100;
  *y = 200;
  std::cout << foo.x << std::endl;
  std::cout << foo.y << std::endl;

  return 0;
}
```

### Podsumowanie 'zwykłych' wskaźników

Wskaźniki są jednym z kluczowych elementów w języku C++, umożliwiając programistom na dynamiczne zarządzanie pamięcią, dostęp do funkcji oraz składowych klas. Poniżej znajduje się zestawienie różnych rodzajów wskaźników w C++.

| Kod                                  | Opis                                                           |
| ------------------------------------ | -------------------------------------------------------------- |
| `int *wsk;`                          | wskaźnik na zmienną typu int                                   |
| `int **wskNaWsk;`                    | wskaźnik na wskaźnik typu int                                  |
| `int (*wskNaTablice)[];`             | wskaźnik na tablicę intów                                      |
| `int (*wskNaFunkcje)();`             | wskaźnik na funkcję zwracającą int                             |
| `int *tab[];`                        | tablica wskaźników na int                                      |
| `int *fun();`                        | funkcja zwracająca wskaźnik na int                             |

Zrozumienie wskaźników i ich różnorodności jest kluczem do tworzenia efektywnych i optymalnych aplikacji w C++.

### Sprytne wskaźniki

W standardzie C++11 wprowadzono koncept sprytnych wskaźników (`smart pointers`). Te wskaźniki są bardziej zaawansowanymi wersjami tradycyjnych surowych wskaźników, oferując automatyczne zarządzanie pamięcią oraz inne dodatkowe funkcjonalności. Gdy sprytny wskaźnik jest niszczony (w momencie wywołania jego destruktora), automatycznie zwalnia on przydzieloną pamięć sterty, co eliminuje wiele problemów związanych z zarządzaniem pamięcią.

#### unique_ptr

`unique_ptr` to rodzaj sprytnego wskaźnika, który gwarantuje wyłączność posiadania przydzielonej pamięci. Oznacza to, że w każdym momencie tylko jeden `unique_ptr` może wskazywać na dany obszar pamięci. Gdy `unique_ptr` przestaje istnieć (np. wyjdzie poza zakres życia), automatycznie zwalnia on przydzieloną pamięć. Programista nie musi więc używać operatora `delete`, co zwiększa bezpieczeństwo kodu.

```
                                             +-------------------+
+-----------------------+                    |       Dane        |
|   unique_ptr          |                    |  +-------------+  |
|  +-----------------+  |                 |->|  |  Obiekt T   |  |
|  |  Wskaźnik na T  |  |-----------------|  |  +-------------+  | 
|  +-----------------+  |                    +-------------------+  
+-----------------------+
```

Aby utworzyć unikalny wskaźnik na wartość użyj:

```cpp
std::unique_ptr<int> unikalnyWsk = std::make_unique<int>(5);
std::cout << *unikalnyWsk << std::endl;  // wyświetli 5
```

Używanie `unique_ptr` wymaga jednak pewnej ostrożności. Jeżeli dwie instancje `unique_ptr` będą wskazywać na ten sam obszar pamięci, może to prowadzić do błędu zwolnienia tej samej pamięci wielokrotnie (tzw. double free).

```cpp
int *surowyWsk = new int(5);
std::unique_ptr<int> unikalnyWsk1(surowyWsk);
std::unique_ptr<int> unikalnyWsk2(surowyWsk); // błąd: double free
```

Dlatego zaleca się korzystanie z funkcji `std::make_unique` do tworzenia `unique_ptr`, ponieważ gwarantuje ona, że pamięć zostanie przydzielona jednokrotnie.

```cpp
std::unique_ptr<Foo> unikalnyWsk = std::make_unique<Foo>(1.0, 2.0);
```

Warto podkreślić, że `unique_ptr` nie jest kopiowalny. Nie możemy więc przypisać jednego `unique_ptr` do drugiego ani przekazać go do funkcji przez wartość. Możemy jednak przenosić własność pamięci za pomocą semantyki przenoszenia (move semantics).

```cpp
std::unique_ptr<Foo> unikalnyWsk1 = std::make_unique<Foo>();
std::unique_ptr<Foo> unikalnyWsk2 = std::move(unikalnyWsk1);   // poprawne przeniesienie własności

void func(std::unique_ptr<Foo> wsk) {}
func(std::move(unikalnyWsk2));  // poprawne przekazanie przez przeniesienie
```

#### shared_ptr

`shared_ptr` to kolejny rodzaj sprytnego wskaźnika dostępnego w C++. Charakteryzuje się tym, że pozwala wielu wskaźnikom `shared_ptr` współdzielić własność jednego obiektu. Gdy ostatni `shared_ptr` wskazujący na dany obiekt jest niszczony, pamięć zajmowana przez ten obiekt jest zwalniana.

```
                                             +-------------------+
+-----------------------+                    |       Dane        |
|   shared_ptr A        |                    |  +-------------+  |
|  +-----------------+  |                 |->|  |  Obiekt T   |  |
|  |  Wskaźnik na T  |  |-----------------|  |  +-------------+  | 
|  +-----------------+  |                 |  +-------------------+  
|  |  Wskaźnik na    |  |           |-----|
|  |  Blok Kontrolny |  |--------   |             +-------------------------------+
|  +-----------------+  |       |   |             |      Blok Kontrolny           |
+-----------------------+       |   |             |  +-------------------------+  |
                                |---|-------|->-->|  |  Licznik Referencji: 2  |  |
+-----------------------+           |       |     |  +-------------------------+  |
|   shared_ptr B        |           |       |     |  |  Licznik Słabych        |  |
|  +-----------------+  |           |       |     |  |  Wskaźników: 0          |  |
|  |  Wskaźnik na T  |  |-----------|       |     |  +-------------------------+  |
|  +-----------------+  |                   |     |  |  Niestandardowy Deleter |  |
|  |  Wskaźnik na    |  |                   |     |  |  Alokator, itp.         |  |
|  |  Blok Kontrolny |  |-------------------|     |  +-------------------------+  |
|  +-----------------+  |                         +-------------------------------+
+-----------------------+ 
```

W odróżnieniu od `unique_ptr`, `shared_ptr` jest kopiowalny, co umożliwia jego przekazywanie jako argument do funkcji.

```cpp
std::shared_ptr<Foo> wspolnyWsk1 = std::make_shared<Foo>();
std::shared_ptr<Foo> wspolnyWsk2 = wspolnyWsk1;

void func(std::shared_ptr<Foo> wsk) {}
func(wspolnyWsk2); // poprawne
```

Chociaż `shared_ptr` ma wiele zalet, warto być ostrożnym. Nieumiejętne używanie wielu `shared_ptr`-ów może prowadzić do cyklicznych referencji, gdzie dwa obiekty nawzajem na siebie wskazują, uniemożliwiając ich zwolnienie.

#### weak_ptr

Gdy potrzebujemy wskaźnika na blok pamięci, ale nie chcemy przejmować jego własności, `weak_ptr` jest idealnym rozwiązaniem. `weak_ptr` działa w tandemie z `shared_ptr`. Jego główną cechą jest to, że pozwala obserwować obiekt wskazywany przez `shared_ptr`, ale nie wpływa na licznik odniesień (ang. reference count) tego obiektu. Dzięki temu, `weak_ptr` nie zapobiega destrukcji obiektu, gdy wszystkie `shared_ptr`-y wskazujące na ten obiekt zostaną zniszczone.

```
                                             +-------------------+
+-----------------------+                    |       Dane        |
|   shared_ptr A        |                    |  +-------------+  |
|  +-----------------+  |                 |->|  |  Obiekt T   |  |
|  |  Wskaźnik na T  |  |-----------------|  |  +-------------+  | 
|  +-----------------+  |                 |  +-------------------+  
|  |  Wskaźnik na    |  |           |-----|
|  |  Blok Kontrolny |  |--------   |             +-------------------------------+
|  +-----------------+  |       |   |             |      Blok Kontrolny           |
+-----------------------+       |   |             |  +-------------------------+  |
                                |---|-------|->-->|  |  Licznik Referencji: 2  |  |
+-----------------------+           |       |     |  +-------------------------+  |
|   shared_ptr B        |           |       |     |  |  Licznik Słabych        |  |
|  +-----------------+  |           |       |     |  |  Wskaźników: 1          |  |<---|
|  |  Wskaźnik na T  |  |-----------|       |     |  +-------------------------+  |    |
|  +-----------------+  |                   |     |  |  Niestandardowy Deleter |  |    |
|  |  Wskaźnik na    |  |                   |     |  |  Alokator, itp.         |  |    |
|  |  Blok Kontrolny |  |-------------------|     |  +-------------------------+  |    |
|  +-----------------+  |                         +-------------------------------+    |
+-----------------------+                                                              |
                                                                                       |
                                                                                       |
+-----------------------+                                                              |
|   weak_ptr            |                                                              |
|  +-----------------+  |                                                              |
|  |  Wskaźnik na    |  |---------------------------------------------------------------
|  |  Blok Kontrolny |  |
|  +-----------------+  |
+-----------------------+
```

Aby utworzyć słaby wskaźnik ze wspólnego wskaźnika, użyj:

```cpp
std::shared_ptr<Foo> wspolnyWsk = std::make_shared<Foo>();
std::weak_ptr<Foo> slabyWsk = wspolnyWsk;
```

Aby uzyskać dostęp do obiektu wskazywanego przez `weak_ptr`, należy przekształcić go w `shared_ptr` za pomocą metody `lock()`. Jeżeli obiekt wciąż istnieje (tj. jest na niego jakiś `shared_ptr`), `lock()` zwróci ważny `shared_ptr`. W przeciwnym razie zwróci pusty wskaźnik.

```cpp
std::shared_ptr<Foo> tempWsk = slabyWsk.lock();
if(tempWsk)
{
    // mamy dostęp do obiektu
}
else
{
    // obiekt już nie istnieje
}
```

Dzięki `weak_ptr`, można unikać problemów z cyklicznymi referencjami w `shared_ptr`, ponieważ `weak_ptr` nie zwiększa licznika odniesień obiektu. Gdy obiekt przestaje być potrzebny (wszystkie `shared_ptr`-y zostaną zniszczone), pamięć zostaje zwolniona, nawet jeśli istnieją `weak_ptr`-y wskazujące na ten obiekt.

#### Inne aspekty sprytnych wskaźników

##### Kontrola cyklu życia obiektów

Sprytne wskaźniki pozwalają na precyzyjną kontrolę cyklu życia obiektów, eliminując problemy z zarządzaniem pamięcią, takie jak wycieki pamięci czy błędy typu double-free. Dzięki automatycznemu zwalnianiu zasobów, kod jest bardziej niezawodny i łatwiejszy do utrzymania.

##### Wydajność

Chociaż sprytne wskaźniki wprowadzają pewien narzut związany z zarządzaniem pamięcią (np. zarządzanie licznikiem odniesień w `shared_ptr`), to narzut ten jest zazwyczaj niewielki w porównaniu do korzyści, jakie przynoszą. Dodatkowo, stosowanie sprytnych wskaźników pozwala na lepsze wykrywanie i zapobieganie wyciekom pamięci podczas fazy testowania.

##### Integracja z innymi mechanizmami C++

Sprytne wskaźniki dobrze integrują się z innymi mechanizmami języka C++, takimi jak RAII (Resource Acquisition Is Initialization), co pozwala na efektywne zarządzanie zasobami. Dzięki temu, sprytne wskaźniki stają się podstawowym narzędziem w nowoczesnym programowaniu w C++.

#### Podsumowanie

Oto tabela podsumowująca metody dostępne dla każdego ze sprytnych wskaźników (`unique_ptr`, `shared_ptr`, `weak_ptr`) w C++:

| **Metoda/Funkcja**           | **unique_ptr**               | **shared_ptr**                | **weak_ptr**                   |
|------------------------------|------------------------------|------------------------------|-------------------------------|
| **Tworzenie**                | `std::make_unique<T>(...)`   | `std::make_shared<T>(...)`   | `std::weak_ptr<T>()`          |
|                              | `unique_ptr<T> p(new T(...))`| `shared_ptr<T> p(new T(...))`|                               |
| **Destrukcja**               | Automatyczna przy wyjściu z zakresu | Automatyczna przy wyjściu z zakresu | Automatyczna przy wyjściu z zakresu |
| **reset()**                  | `p.reset()`                  | `p.reset()`                  | `p.reset()`                   |
|                              | `p.reset(new T(...))`        | `p.reset(new T(...))`        |                               |
| **release()**                | `p.release()`                | N/A                          | N/A                           |
| **swap()**                   | `p.swap(other)`              | `p.swap(other)`              | `p.swap(other)`               |
| **get()**                    | `p.get()`                    | `p.get()`                    | `p.lock().get()`              |
| **operator*()**              | `*p`                         | `*p`                         | `*(p.lock())`                 |
| **operator->()**             | `p->`                        | `p->`                        | `p.lock()->`                  |
| **operator bool()**          | `if (p)`                     | `if (p)`                     | `if (p.lock())`               |
| **use_count()**              | N/A                          | `p.use_count()`              | `p.use_count()`               |
| **unique()**                 | N/A                          | `p.unique()`                 | N/A                           |
| **owner_before()**           | N/A                          | `p.owner_before(other)`      | `p.owner_before(other)`       |
| **lock()**                   | N/A                          | N/A                          | `p.lock()`                    |
