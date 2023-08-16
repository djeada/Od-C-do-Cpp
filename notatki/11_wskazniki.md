## Wskaźniki

Wskaźnik w języku C++ to specjalny typ zmiennej, który przechowuje adres innego miejsca w pamięci. Dzięki wskaźnikom można nie tylko odczytywać, ale także modyfikować wartości przechowywane pod tym adresem.

### Deklaracja wskaźników

Wskaźnik deklaruje się poprzez umieszczenie operatora `*` przed nazwą zmiennej podczas deklaracji. Typ wskaźnika musi odpowiadać typowi zmiennej, której adres będzie przechowywał.

```c++
int *ptrInt;             // wskaźnik do zmiennej typu int
double *ptrDouble;       // wskaźnik do zmiennej typu double
std::string *ptrString;  // wskaźnik do zmiennej typu std::string
```

### Inicjalizacja wskaźników

Wskaźniki inicjalizuje się poprzez przypisanie im adresu zmiennej za pomocą operatora `&`.

```c++
int number = 42;
int *ptr = &number;
```

### Dereferencja wskaźników

Dereferencja wskaźnika polega na uzyskaniu dostępu do wartości zmiennej, na którą wskazuje wskaźnik. Wykorzystuje się do tego operator `*`.

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

Uwaga: Operując na wskaźnikach, zawsze należy pamiętać o ich inicjalizacji.

### Wskaźnik na wskaźnik

Wskaźniki w języku C++ mogą wskazywać na inne wskaźniki, tworząc tym samym wskaźniki wielopoziomowe. Aby zadeklarować wskaźnik na wskaźnik, dodajemy dodatkowy operator `*` przed nazwą zmiennej.

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

### NULL i nullptr w C++

`NULL` to specjalna wartość wskaźnika, wskazująca na brak obiektu. Jest używana w wielu sytuacjach, np. do oznaczania końca listy połączonej czy sygnalizowania problemów z alokacją pamięci.

Chociaż `NULL` jest używane w wielu miejscach w kodzie C++, w nowszych wersjach C++ zaleca się korzystanie z `nullptr` ze względu na jego jednoznaczność w kontekście przeciążania funkcji.

```c++
void foo(void *wsk);
void foo(int liczba);

// Przy wywołaniu:
foo(NULL); // Wywołuje foo(int liczba)
```

Użycie `nullptr` eliminuje powyższą niejednoznaczność:

```c++
foo(nullptr); // Wywołuje foo(void *wsk)
```

Przykładowe użycie:

```c++
int *ptr = nullptr;
if (ptr == nullptr) {
    std::cout << "Wskaźnik ptr jest pusty." << std::endl;
}

class A {};
A *a_ptr = nullptr;
if (a_ptr == nullptr) {
    std::cout << "Wskaźnik a_ptr jest pusty." << std::endl;
}
```

### Stałe wskaźniki w C++

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
