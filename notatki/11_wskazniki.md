## Wskaźniki

Wskaźnik w języku C++ to specjalny typ zmiennej, który przechowuje adres innego miejsca w pamięci. Dzięki wskaźnikom można nie tylko odczytywać, ale także modyfikować wartości przechowywane pod tym adresem. Operowanie na wskaźnikach jest kluczowe dla efektywnego zarządzania pamięcią i dynamicznego alokowania zasobów.

### Deklaracja wskaźników

Wskaźnik deklaruje się poprzez umieszczenie operatora `*` przed nazwą zmiennej podczas deklaracji. Typ wskaźnika musi odpowiadać typowi zmiennej, której adres będzie przechowywał. Deklaracja wskaźnika nie rezerwuje pamięci dla zmiennej, na którą wskaźnik będzie wskazywał, tylko dla samego wskaźnika.

```c++
int *ptrInt;             // wskaźnik do zmiennej typu int
double *ptrDouble;       // wskaźnik do zmiennej typu double
std::string *ptrString;  // wskaźnik do zmiennej typu std::string
```

### Inicjalizacja wskaźników

Wskaźniki inicjalizuje się poprzez przypisanie im adresu zmiennej za pomocą operatora `&`. Wskaźnik przechowuje wtedy adres pamięci zmiennej, co umożliwia dostęp do niej i manipulowanie jej wartością za pośrednictwem wskaźnika.

```c++
int number = 42;
int *ptr = &number;
```

### Dereferencja wskaźników

Dereferencja wskaźnika polega na uzyskaniu dostępu do wartości zmiennej, na którą wskazuje wskaźnik. Wykorzystuje się do tego operator `*`. Dereferencja pozwala na odczyt i modyfikację wartości zmiennej przechowywanej pod adresem, na który wskazuje wskaźnik.

```c++
int number = 5;
int *ptr = &number;
*ptr = 10;  // modyfikuje wartość zmiennej number na 10
```

Przykład:

```c++
#include <iostream>

int main() {
    int a = 20;
    int *ptrA = &a;

    std::cout << "Adres zmiennej a: " << &a << std::endl;
    std::cout << "Wartość wskaźnika ptrA: " << ptrA << std::endl;
    std::cout << "Wartość na którą wskazuje ptrA: " << *ptrA << std::endl;

    // Modyfikowanie wartości zmiennej przez wskaźnik
    *ptrA = 30;
    std::cout << "Nowa wartość zmiennej a: " << a << std::endl;

    return 0;
}
```

Uwaga: Operując na wskaźnikach, zawsze należy pamiętać o ich inicjalizacji. Używanie niezainicjalizowanych wskaźników może prowadzić do nieprzewidywalnych zachowań programu, ponieważ mogą one zawierać przypadkowe wartości.

### Wskaźnik na wskaźnik

Wskaźniki w języku C++ mogą wskazywać na inne wskaźniki, tworząc tym samym wskaźniki wielopoziomowe. Aby zadeklarować wskaźnik na wskaźnik, dodajemy dodatkowy operator `*` przed nazwą zmiennej. Wskaźniki wielopoziomowe są używane w złożonych strukturach danych oraz przy dynamicznej alokacji pamięci.

```c++
int main() {
    int i = 20;
    int *j = &i;        // j to wskaźnik na zmienną i
    int **k = &j;       // k to wskaźnik na wskaźnik j
    int ***l = &k;      // l to wskaźnik na wskaźnik k

    std::cout << "Wartość zmiennej i przez **k: " << **k << std::endl;
    // Jest to równoważne z: std::cout << "Wartość zmiennej i przez *j: " << *j << std::endl;

    return 0;
}
```
### NULL i nullptr

`NULL` to specjalna wartość wskaźnika, która wskazuje na brak obiektu. Jest używana w wielu sytuacjach, takich jak oznaczanie końca listy połączonej lub sygnalizowanie problemów z alokacją pamięci. `NULL` jest zdefiniowany jako `0` w standardowych nagłówkach C i C++, co może prowadzić do pewnych niejednoznaczności, szczególnie w kontekście przeciążania funkcji.

#### Problemy z NULL

W starszych wersjach C++ użycie `NULL` może prowadzić do niejasności, ponieważ `NULL` jest zdefiniowany jako `0`, co może być mylące, gdy funkcja jest przeciążona dla różnych typów argumentów.

```c++
void foo(void *wsk);
void foo(int liczba);

// Przy wywołaniu:
foo(NULL); // Wywołuje foo(int liczba)
```

#### Rozwiązanie: nullptr

Wprowadzony w C++11, `nullptr` jest nowym literałem wskaźnikowym, który rozwiązuje problemy związane z `NULL`. `nullptr` ma jednoznaczny typ `std::nullptr_t`, co eliminuje niejednoznaczności w kontekście przeciążania funkcji.

```c++
foo(nullptr); // Wywołuje foo(void *wsk)
```

#### Przykłady użycia nullptr

W praktyce, `nullptr` jest bardziej zalecany ze względu na swoją jednoznaczność i bezpieczeństwo typów. Oto przykłady użycia `nullptr` w różnych kontekstach:

##### Sprawdzanie, czy wskaźnik jest pusty

```c++
int *ptr = nullptr;
if (ptr == nullptr) {
    std::cout << "Wskaźnik ptr jest pusty." << std::endl;
}
```

##### Inicjalizacja wskaźnika do obiektu klasy

```c++
class A {};
A *a_ptr = nullptr;
if (a_ptr == nullptr) {
    std::cout << "Wskaźnik a_ptr jest pusty." << std::endl;
}
```

#### Zalety użycia nullptr

1. **Jednoznaczność:** `nullptr` nie może być mylony z żadną liczbą całkowitą, co czyni kod bardziej czytelnym i bezpiecznym.
2. **Bezpieczeństwo typów:** `nullptr` ma typ `std::nullptr_t`, co pozwala na łatwiejsze przeciążanie funkcji i redukcję błędów kompilacji.
3. **Lepsze wsparcie kompilatora:** Kompilatory mogą lepiej optymalizować kod i wykrywać błędy, gdy używany jest `nullptr` zamiast `NULL`.

### Stałe wskaźniki i wskażniki na stałe

W C++ możemy zdefiniować różnego rodzaju stałe wskaźniki. Istnieją dwie główne kategorie stałych wskaźników: wskaźniki na stałą wartość oraz stałe wskaźniki.

1. **Wskaźniki na stałą wartość**:
    Te wskaźniki wskazują na wartość, której nie możemy zmienić poprzez wskaźnik, ale możemy przestawiać wskaźnik na inny adres.

    ```c++
    const int *a;
    int const *a; // Jest równoważne poprzedniemu przykładowi
    ```

2. **Stałe wskaźniki**:
    Jest to wskaźnik, którego adres nie może być zmieniony po inicjalizacji, ale wartość, na którą wskazuje, może być zmieniana.

    ```c++
    int *const b;
    ```

Przykład użycia:

```c++
#include <iostream>

int main() {
    int x = 5;
    int y = 10;
    int* const ptr1 = &x; // stały wskaźnik na zmienną x
    const int* ptr2 = &y; // wskaźnik na stałą y
    
    std::cout << "Wartość x: " << x << std::endl;
    std::cout << "Wartość y: " << y << std::endl;
    std::cout << "Wartość wskazywana przez ptr1: " << *ptr1 << std::endl;
    std::cout << "Wartość wskazywana przez ptr2: " << *ptr2 << std::endl;
    
    *ptr1 = 7; // poprawne, możemy zmienić wartość wskazywaną przez stały wskaźnik
    ptr2 = &x; // poprawne, możemy zmienić adres, na który wskazuje wskaźnik na stałą
    // *ptr2 = 7; // niepoprawne, nie możemy zmienić wartości wskazywanej przez wskaźnik na stałą
    // ptr1 = &y; // niepoprawne, nie możemy zmienić adresu, na który wskazuje stały wskaźnik

    std::cout << "Wartość x po zmianie: " << x << std::endl;
    std::cout << "Wartość y po zmianie: " << y << std::endl;
    std::cout << "Wartość wskazywana przez ptr1 po zmianie: " << *ptr1 << std::endl;
    std::cout << "Wartość wskazywana przez ptr2 po zmianie: " << *ptr2 << std::endl;
    
    return 0;
}
```

### Wskaźniki na funkcje

Wskaźniki na funkcje w języku C++ pozwalają na przechowywanie adresów funkcji i ich późniejsze wywoływanie. Są one szczególnie przydatne w implementacji callbacków, dynamicznego wyboru funkcji, oraz w programowaniu zorientowanym na zdarzenia.

### Deklaracja wskaźnika na funkcję

Deklaracja wskaźnika na funkcję wymaga określenia typu zwracanego przez funkcję oraz typów jej parametrów. Wskaźnik na funkcję różni się od wskaźnika na zmienną tym, że po nazwie wskaźnika umieszczamy nawiasy oraz wskazanie na typ funkcji.

```c++
int (*ptrFunc)(int, int);
```

Powyższa deklaracja oznacza wskaźnik na funkcję zwracającą `int` i przyjmującą dwa argumenty typu `int`.

### Inicjalizacja wskaźnika na funkcję

Wskaźnik na funkcję inicjalizuje się przypisując mu adres funkcji za pomocą jej nazwy.

```c++
int add(int a, int b) {
    return a + b;
}

int (*ptrFunc)(int, int) = &add;
```

Można również pominąć operator `&` podczas przypisywania, ponieważ nazwa funkcji jest automatycznie traktowana jako wskaźnik.

```c++
int (*ptrFunc)(int, int) = add;
```

### Wywoływanie funkcji za pomocą wskaźnika

Aby wywołać funkcję za pomocą wskaźnika, używamy operatora dereferencji `*` lub bezpośrednio nazwy wskaźnika.

```c++
int result = (*ptrFunc)(5, 3); // Wywołanie przez dereferencję
int result2 = ptrFunc(5, 3);   // Wywołanie bezpośrednie
```

### Przykład

Poniżej znajduje się kompletny przykład użycia wskaźników na funkcje w C++.

```c++
#include <iostream>

// Definicje funkcji
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

// Funkcja przyjmująca wskaźnik na funkcję jako argument
void computeAndPrint(int (*func)(int, int), int x, int y) {
    std::cout << "Wynik: " << func(x, y) << std::endl;
}

int main() {
    // Deklaracja wskaźników na funkcje
    int (*ptrAdd)(int, int) = add;
    int (*ptrSubtract)(int, int) = subtract;
    int (*ptrMultiply)(int, int) = multiply;

    // Wywoływanie funkcji przez wskaźniki
    std::cout << "Dodawanie: " << ptrAdd(10, 5) << std::endl;
    std::cout << "Odejmowanie: " << ptrSubtract(10, 5) << std::endl;
    std::cout << "Mnożenie: " << ptrMultiply(10, 5) << std::endl;

    // Przekazywanie wskaźników na funkcje do innej funkcji
    computeAndPrint(add, 20, 10);
    computeAndPrint(subtract, 20, 10);
    computeAndPrint(multiply, 20, 10);

    return 0;
}
```

#### Zalety użycia wskaźników na funkcje

1. **Elastyczność:** Pozwalają na dynamiczne wybieranie i wywoływanie funkcji w czasie wykonania programu.
2. **Reużywalność:** Umożliwiają tworzenie ogólnych funkcji, które mogą pracować z różnymi operacjami.
3. **Efektywność:** Redukują potrzebę używania wielu instrukcji warunkowych.

### Podusmowanie

Poniżej przedstawiamy podsumowanie różnych typów wskaźników oraz ich znaczenie, użycie i przykłady.

| Typ wskaźnika                          | Definicja                                             | Opis                                                                             | Przykład                                 |
|----------------------------------------|-------------------------------------------------------|----------------------------------------------------------------------------------|------------------------------------------|
| **Wskaźnik**                           | `int *ptr`                                            | Przechowuje adres zmiennej.                                                      | `int a = 10; int *ptr = &a;`             |
| **Stały wskaźnik**                     | `int *const ptr`                                      | Wskaźnik, który nie może być zmieniony po inicjalizacji.                         | `int a = 10; int *const ptr = &a;`       |
| **Wskaźnik na stałą**                  | `const int *ptr`                                      | Wskaźnik na wartość, której nie można zmieniać przez ten wskaźnik.               | `const int *ptr = &a;`                   |
| **Stały wskaźnik na stałą**            | `const int *const ptr`                                | Wskaźnik, który nie może być zmieniony i wskazuje na stałą wartość.              | `const int *const ptr = &a;`             |
| **Wskaźnik na wskaźnik**               | `int **ptr`                                           | Wskaźnik, który przechowuje adres innego wskaźnika.                              | `int *p; int **ptr = &p;`                |
| **Wskaźnik na stały wskaźnik**         | `int *const *ptr`                                     | Wskaźnik na wskaźnik, który nie może być zmieniony po inicjalizacji.             | `int *const *ptr = &p;`                  |
| **Wskaźnik na wskaźnik na stałą**      | `const int **ptr`                                     | Wskaźnik na wskaźnik, który wskazuje na stałą wartość.                           | `const int **ptr = &p;`                  |
| **Stały wskaźnik na wskaźnik na stałą**| `const int *const *ptr`                               | Stały wskaźnik na wskaźnik, który wskazuje na stałą wartość.                     | `const int *const *ptr = &p;`            |
| **Wskaźnik na funkcję**                | `int (*ptr)(int, int)`                                | Wskaźnik na funkcję, która przyjmuje dwa argumenty typu `int` i zwraca `int`.    | `int (*ptr)(int, int) = &funkcja;`       |

