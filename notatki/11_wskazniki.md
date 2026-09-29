# Wskaźniki

**Wskaźnik jest osobną zmienną, której wartością jest adres innego obiektu.** Jeśli obiekt `number` przechowuje liczbę `42`, wskaźnik `pointer` może przechowywać adres tego obiektu. Operator `*` pozwala wtedy dotrzeć do obiektu pod tym adresem.

W tej lekcji rozdzielamy trzy pojęcia, które łatwo pomylić:

1. obiekt `number` i jego wartość, np. `42`;
2. adres obiektu, pobierany przez `&number`;
3. wskaźnik `pointer`, który przechowuje ten adres.

## Deklaracja, adres i dereferencja

`int* pointer` oznacza: „`pointer` jest wskaźnikiem do obiektu typu `int`”. Samo zadeklarowanie wskaźnika nie tworzy obiektu typu `int`, do którego mógłby wskazywać.

```cpp
#include <iostream>

int main() {
    int number = 42;
    int* pointer = &number;  // pointer przechowuje adres number

    std::cout << "number: " << number << '\n';       // wartość obiektu: 42
    std::cout << "pointer: " << pointer << '\n';     // sam adres
    std::cout << "*pointer: " << *pointer << '\n';   // wartość pod tym adresem: 42

    *pointer = 50;            // zapis przez wskaźnik zmienia number
    std::cout << number << '\n';  // 50
}
```

Można wyobrazić to sobie tak:

| Wyrażenie | Co oznacza w przykładzie |
| --- | --- |
| `number` | obiekt, którego wartością jest `42`, a później `50` |
| `&number` | adres obiektu `number` |
| `pointer` | osobny obiekt przechowujący adres `number` |
| `*pointer` | dostęp do obiektu `number` pod zapisanym adresem |

Wypisany adres zależy od uruchomienia i środowiska. Nie należy oczekiwać konkretnego zapisu ani traktować go jak liczby do ręcznego obliczania. Najważniejsze jest to, że `pointer` przechowuje adres `number`, a `*pointer` daje dostęp do samego obiektu.

Operator `&` w wyrażeniu, jak w `&number`, pobiera adres. Operator `*` w deklaracji, jak w `int* pointer`, oznacza typ wskaźnika; operator `*` w wyrażeniu, jak w `*pointer`, oznacza dereferencję, czyli dostęp do obiektu pod adresem.

Jeśli wskaźnik wskazuje na żywy obiekt, `*pointer` jest L-wartością: można tę wartość odczytać i — jeśli obiekt nie jest stały — zmienić. To łączy wskaźniki z poprzednią lekcją o L-wartościach i referencjach.

### Deklarowanie i inicjalizowanie

Przy wielu deklaracjach gwiazdka odnosi się do konkretnej zmiennej, dlatego czytelniej deklarować wskaźniki osobno:

```cpp
int* first = nullptr;
int* second = nullptr;

// int* p, q;  // p jest wskaźnikiem do int, q jest zwykłym int
```

Lokalny wskaźnik, któremu nie przypisano początkowej wartości, nie jest bezpieczny do użycia. Nie odczytuj jego wartości ani go nie dereferencjonuj. Przed użyciem zainicjalizuj go adresem żywego obiektu albo wartością `nullptr`.

## Pusty wskaźnik i `nullptr`

`nullptr` oznacza, że wskaźnik nie wskazuje na żaden obiekt. Można sprawdzić tę wartość przed dereferencją:

```cpp
#include <iostream>

int main() {
    int* pointer = nullptr;

    if (pointer != nullptr) {
        std::cout << *pointer << '\n';
    } else {
        std::cout << "Brak wskazywanego obiektu\n";
    }
}
```

Pusty wskaźnik i wskaźnik wiszący oznaczają różne sytuacje. `nullptr` jawnie oznacza brak wskazywanego obiektu. Wskaźnik wiszący wcześniej wskazywał na obiekt, który już przestał istnieć. Obu nie wolno dereferencjonować, ale sprawdzenie `pointer != nullptr` nie wykrywa wskaźnika wiszącego.

`nullptr` wprowadzono w C++11. Jest lepszy od historycznego `NULL` i zera, bo ma jednoznaczne znaczenie wskaźnikowe, a nie całkowitoliczbowe. Różnicę widać przy przeciążonych funkcjach:

```cpp
#include <iostream>

void show(int) {
    std::cout << "int\n";
}

void show(int*) {
    std::cout << "int*\n";
}

int main() {
    show(0);        // wybiera wersję przyjmującą int
    show(nullptr);  // wybiera wersję przyjmującą int*
}
```

Makro `NULL` może zależnie od środowiska być zdefiniowane w sposób prowadzący do wybrania przeciążenia całkowitoliczbowego. W nowym kodzie C++ używaj `nullptr`.

## Czas życia obiektu i wskaźnik wiszący

Wskaźnik nie przedłuża czasu życia obiektu. Gdy wykonanie opuszcza zakres zmiennej lokalnej, ta zmienna przestaje istnieć. Zachowany adres nie zmienia się automatycznie w `nullptr`:

```cpp
int main() {
    int* pointer = nullptr;

    {
        int local = 7;
        pointer = &local;  // local istnieje wewnątrz tego bloku
        // W tym miejscu *pointer ma wartość 7.
    }                      // local przestaje istnieć

    // pointer jest teraz wiszący: nie wolno go dereferencjonować
}
```

Częstą odmianą tego błędu jest zwrócenie z funkcji adresu jej zmiennej lokalnej. Zmienna lokalna jest niszczona przy wyjściu z funkcji, więc zwrócony wskaźnik nie prowadzi już do żywego obiektu. Jeśli wynik ma żyć dłużej, zwróć obiekt przez wartość albo użyj kontenera lub inteligentnego wskaźnika.

Przed dereferencją muszą być spełnione dwa warunki: wskaźnik nie jest pusty **i** wskazywany obiekt nadal istnieje. Sam test `pointer != nullptr` nie wystarcza do sprawdzenia czasu życia obiektu.

## Wskaźnik a referencja

Referencja poznana w poprzedniej lekcji i wskaźnik mogą dawać dostęp do tego samego obiektu, ale zachowują się inaczej:

| Cecha | Referencja `T&` | Wskaźnik `T*` |
| --- | --- | --- |
| Powiązanie z obiektem | musi być powiązana przy deklaracji | można ustawić lub zmienić później |
| Brak obiektu docelowego | nie ma zwykłej pustej referencji | można zapisać `nullptr` |
| Dostęp do wartości | używa się nazwy referencji, np. `ref` | dereferencja, np. `*pointer` |
| Zmiana obiektu docelowego | referencji nie przepina się | wskaźnik można skierować na inny obiekt |

```cpp
int main() {
    int first = 10;
    int second = 20;

    int& reference = first;  // druga nazwa obiektu first
    int* pointer = &first;   // osobna zmienna przechowująca adres first

    reference = 11;          // zmienia first
    pointer = &second;       // teraz wskaźnik wskazuje na second
    *pointer = 21;           // zmienia second

    // first ma 11, second ma 21
}
```

## Wskaźnik na wskaźnik

Wskaźnik może przechowywać adres innego wskaźnika. Każda dodatkowa gwiazdka oznacza kolejny poziom dostępu:

```cpp
#include <iostream>

int main() {
    int value = 20;
    int* pointer = &value;                 // pointer przechowuje adres value
    int** pointerToPointer = &pointer;      // przechowuje adres zmiennej pointer

    std::cout << *pointer << '\n';           // 20: dostęp do value
    std::cout << *pointerToPointer << '\n';  // adres przechowywany przez pointer
    std::cout << **pointerToPointer << '\n'; // 20: przejście przez oba poziomy
}
```

Pierwsze `*` zastosowane do `pointerToPointer` daje zmienną `pointer`. Drugie przechodzi z `pointer` do obiektu `value`. Taka konstrukcja przydaje się, gdy funkcja ma zmienić sam wskaźnik przekazany przez wywołującego. W nowoczesnym C++ często czytelniej przekazać referencję do wskaźnika albo użyć typu, który jawnie zarządza własnością.

## Stały obiekt i stały wskaźnik

Położenie `const` określa, co jest stałe. Czytaj deklarację od nazwy:

```cpp
int main() {
    int x = 5;
    int y = 10;

    const int* readOnly = &x;            // można zmienić adres, nie można pisać przez readOnly
    int* const fixed = &x;               // adres stały, można zmieniać x przez fixed
    const int* const fixedReadOnly = &x; // stały adres i tylko odczyt przez ten wskaźnik

    readOnly = &y;         // OK
    // *readOnly = 6;      // błąd: zapis przez readOnly zabroniony
    *fixed = 6;            // OK: x ma teraz 6
    // fixed = &y;         // błąd: fixed nie może zmienić adresu
    // *fixedReadOnly = 7; // błąd
}
```

`const int*` oznacza tylko, że przez ten wskaźnik nie wolno modyfikować obiektu. Jeżeli sam obiekt nie jest stały, inny kod nadal może zmienić go przez inną drogę.

## Wskaźnik na funkcję

Wskaźnik może przechowywać adres funkcji o określonych typach parametrów i wyniku. Alias `using` ułatwia czytanie deklaracji:

```cpp
#include <iostream>

int add(int left, int right) {
    return left + right;
}

using Operation = int (*)(int, int);

int main() {
    Operation operation = add;
    std::cout << operation(2, 3) << '\n';  // 5
}
```

`Operation` oznacza wskaźnik do funkcji, która przyjmuje dwa argumenty typu `int` i zwraca `int`. Wywołanie przez wskaźnik wygląda tak samo jak wywołanie funkcji. Wskaźniki do funkcji można spotkać w prostych callbackach; współczesny kod często używa również `std::function` lub obiektów funkcyjnych.

## Własność pamięci

Sam typ surowego wskaźnika nie mówi, czy wskaźnik jest właścicielem wskazywanego obiektu. Nie zakładaj, że wskaźnik automatycznie zwolni pamięć albo przedłuży czas życia.

- Dla kolekcji o zmiennym rozmiarze zwykle wybierz `std::vector`.
- Dla pojedynczego obiektu z wyłączną własnością rozważ `std::unique_ptr` z nagłówka `<memory>`.
- Surowy wskaźnik często służy do obserwowania obiektu, którego czasem życia zarządza inny kod.

Następna lekcja użyje tablic, by pokazać, jak wskaźnik przechodzi po elementach, dlaczego sam nie przechowuje rozmiaru i skąd bierze się błąd wyjścia poza bufor.
