# Tablice

Wbudowana tablica C++ przechowuje **ustaloną liczbę elementów tego samego typu**. Elementy leżą kolejno w pamięci, a indeksy zaczynają się od zera. Tablica zawiera wiele elementów; wskaźnik jest osobną zmienną, która może przechowywać adres jednego z nich.

Ta lekcja łączy dwie poprzednie: wyrażenie `values[1]` oznacza konkretny element (L-wartość), a w wielu kontekstach nazwa tablicy `values` zamienia się na wskaźnik do pierwszego elementu. Ta konwersja nie oznacza, że tablica i wskaźnik są tym samym typem.

## Deklarowanie i inicjalizowanie tablicy

Rozmiar wbudowanej tablicy musi być znany w czasie kompilacji:

```cpp
int main() {
    constexpr int size = 3;
    int numbers[size];                // 3 inty, jeszcze niezainicjalizowane
    int values[3] = {10, 20, 30};     // elementy mają podane wartości
    int more[] = {4, 5, 6, 7};        // kompilator wyznacza rozmiar: 4
    int zeroes[5]{};                  // wszystkie elementy mają wartość 0
    int partlyFilled[5] = {1, 2};     // pozostałe elementy mają wartość 0
}
```

Lokalna tablica `numbers` bez inicjalizacji zawiera elementy o nieokreślonych wartościach. Nie odczytuj ich przed przypisaniem im wartości. Puste nawiasy klamrowe, jak w `zeroes`, inicjalizują wszystkie elementy zerami.

Dla tablicy `values[3]` prawidłowe indeksy to `0`, `1` i `2`. Numer elementu i jego indeks różnią się o jeden: pierwszy element ma indeks zero, a ostatni — `rozmiar - 1`.

## Odczyt i zmiana elementów

Operator indeksowania `[]` daje dostęp do pojedynczego elementu. Można go odczytać albo zmienić:

```cpp
#include <iostream>

int main() {
    int values[3] = {10, 20, 30};

    values[1] = 25;  // zmieniamy drugi element
    std::cout << values[0] << ' ';  // 10
    std::cout << values[1] << ' ';  // 25
    std::cout << values[2] << '\n'; // 30
}
```

Indeks poza zakresem nie jest automatycznie sprawdzany dla wbudowanej tablicy. W tablicy trzyelementowej `values[3]` leży już poza końcem — ostatni element to `values[2]`. Taki dostęp powoduje **niezdefiniowane zachowanie**: program może się wysypać, odczytać błędną wartość albo uszkodzić inne dane. Nie ma gwarancji, że błąd będzie od razu widoczny.

Częsta pomyłka to użycie `<=` zamiast `<` w warunku pętli:

```cpp
// Poprawnie dla tablicy o rozmiarze 3:
for (int i = 0; i < 3; ++i) {
    // indeksy: 0, 1, 2
}

// BŁĄD: przy i == 3 pętla wyjdzie poza tablicę
// for (int i = 0; i <= 3; ++i) { ... }
```

## Przechodzenie po tablicy pętlą

W pętli indeks `i` powinien przyjmować wartości od zera do liczby elementów minus jeden. Dlatego używa się warunku `i < size`:

```cpp
#include <iostream>

int main() {
    constexpr int size = 5;
    int values[size]{};

    for (int i = 0; i < size; ++i) {
        values[i] = (i + 1) * 10;
    }

    for (int i = 0; i < size; ++i) {
        std::cout << "values[" << i << "] = " << values[i] << '\n';
    }
}
```

Pierwsza pętla kolejno zapisuje `10`, `20`, `30`, `40` i `50`. Druga je wypisuje. Gdy `i` osiąga `size`, warunek `i < size` jest fałszywy i pętla kończy się przed próbą dostępu do `values[size]`.

## Tablica a wskaźnik: konwersja na wskaźnik

W większości wyrażeń nazwa wbudowanej tablicy zamienia się na wskaźnik do jej pierwszego elementu. Nazywa się to konwersją tablicy na wskaźnik (*array-to-pointer conversion*, czasem *array decay*):

```cpp
#include <iostream>

int main() {
    int values[3] = {10, 20, 30};
    int* pointer = values;  // jak &values[0]

    std::cout << values[0] << '\n';  // 10
    std::cout << *pointer << '\n';  // 10
    std::cout << pointer[1] << '\n';// 20
}
```

`values` nadal jest tablicą trzech elementów. `pointer` jest osobną zmienną przechowującą adres pierwszego elementu. Zapis `pointer[1]` działa, bo indeksowanie wskaźnika oznacza to samo co `*(pointer + 1)`. Zmiana wartości zmiennej `pointer` nie zmienia samej tablicy.

### Przekazywanie tablicy do funkcji

W parametrze funkcji zapis `int values[]` jest dostosowywany do `int* values`. Funkcja dostaje kopię adresu pierwszego elementu, a nie kopię całej tablicy. Z tego powodu rozmiar trzeba przekazać osobno:

```cpp
#include <iostream>

void printArray(const int values[], int size) {
    // Parametr jest w praktyce typu const int*.
    for (int i = 0; i < size; ++i) {
        std::cout << values[i] << ' ';
    }
    std::cout << '\n';
}

void setFirst(int values[], int size, int newValue) {
    if (size > 0) {
        values[0] = newValue;  // zmienia element tablicy wywołującego
    }
}

int main() {
    int data[3] = {2, 4, 8};

    printArray(data, 3);  // 2 4 8
    setFirst(data, 3, 9);
    printArray(data, 3);  // 9 4 8
}
```

W `printArray` parametr wskazuje na elementy stałe: funkcja może je czytać, ale nie może ich zmienić przez `values`. W `setFirst` elementy są zmienne, więc przypisanie `values[0] = newValue` modyfikuje oryginalną tablicę. W obu przypadkach sam adres przekazywany jest przez wartość: funkcja otrzymuje własną kopię wskaźnika, który prowadzi do tych samych elementów.

To wywołujący odpowiada za podanie właściwego rozmiaru. Jeśli poda liczbę większą niż pojemność tablicy, funkcja również wyjdzie poza bufor — parametr `size` nie pozwala funkcji samodzielnie sprawdzić, ile elementów istnieje.

### Dlaczego `sizeof` nie zawsze daje rozmiar tablicy

Tam, gdzie `values` jest rzeczywistą tablicą, można policzyć liczbę elementów tak:

```cpp
#include <iostream>

int main() {
    int values[3] = {10, 20, 30};
    int count = sizeof(values) / sizeof(values[0]);

    int* pointer = values;
    std::cout << count << '\n';       // 3 elementy
    std::cout << sizeof(pointer);     // rozmiar wskaźnika w bajtach
}
```

W funkcji `printArray` `sizeof(values)` daje rozmiar wskaźnika, bo parametr `values` jest tam wskaźnikiem. Nie otrzymujemy rozmiaru tablicy przez sam adres — przekazujemy go osobno albo używamy kontenera przechowującego rozmiar, takiego jak `std::array` i `std::vector`.

Konwersja tablicy na wskaźnik nie zachodzi w każdym kontekście: na przykład operand `sizeof(values)` odnosi się do rozmiaru całej tablicy. Na początek zapamiętaj praktyczną regułę: **po przekazaniu wbudowanej tablicy do zwykłej funkcji parametr nie przechowuje jej długości**.

## Arytmetyka wskaźników i granica bufora

Dodanie liczby do wskaźnika przesuwa go o tyle **elementów wskazywanego typu**, a nie bajtów. Dla `int*` wyrażenie `pointer + 1` wskazuje następny `int`. Można poruszać się w obrębie jednej tablicy i utworzyć wskaźnik wskazujący tuż za jej końcem:

```cpp
#include <iostream>

int main() {
    int values[4] = {10, 20, 30, 40};
    int* begin = values;
    int* end = values + 4;  // granica za ostatnim elementem; nie dereferencjonuj

    std::cout << *(begin + 2) << '\n'; // 30, czyli values[2]
    std::cout << end - begin << '\n';  // 4 elementy
}
```

`end` jest przydatny jako granica pętli, ale nie wskazuje elementu do odczytu. Nie wolno go dereferencjonować ani użyć do zapisu. Różnicę wolno obliczyć tylko między wskaźnikami do tej samej tablicy lub do pozycji tuż za jej końcem.

Dla bufora o pojemności `capacity` dostęp jest dozwolony tylko dla indeksów od `0` do `capacity - 1`. Surowy wskaźnik nie pamięta pojemności, więc programista musi sam pilnować rozmiaru i sprawdzać dane wejściowe.

## Tablice o stałym i zmiennym rozmiarze

Jeśli liczba elementów jest znana w czasie kompilacji, w C++ często wygodniej użyć `std::array`. Przechowuje elementy o stałym rozmiarze i pamięta ich liczbę:

```cpp
#include <array>
#include <iostream>

int main() {
    std::array<int, 3> values = {10, 20, 30};

    std::cout << values.size() << '\n';  // 3
    std::cout << values.at(1) << '\n';   // 20; at sprawdza zakres
}
```

Jeśli rozmiar poznajesz dopiero podczas działania programu albo kolekcja ma rosnąć, zwykle wybierz `std::vector`. Kontener przechowuje rozmiar i sam zarządza pamięcią:

```cpp
#include <cstddef>
#include <iostream>
#include <vector>

int main() {
    int count;
    if (!(std::cin >> count) || count < 0) {
        return 1;  // dane nie są poprawną nieujemną liczbą elementów
    }

    std::vector<int> values(static_cast<std::size_t>(count));
    for (int i = 0; i < count; ++i) {
        if (!(std::cin >> values[i])) {
            std::cerr << "Nie udało się odczytać elementu tablicy.\n";
            return 1;
        }
    }

    std::cout << "Liczba elementów: " << values.size() << '\n';
    if (!values.empty()) {
        std::cout << "Pierwszy element: " << values.at(0) << '\n';
    }
}
```

Rzutowanie do `std::size_t` wykonujemy dopiero po sprawdzeniu, że `count` nie jest ujemne. W przeciwnym razie ujemna liczba zamieniona na typ bez znaku może stać się bardzo dużą liczbą. `std::vector::at` zgłasza wyjątek, gdy indeks jest poza zakresem; operator `[]` nie sprawdza granic, więc nadal trzeba ich pilnować.

### Ręczna alokacja przez `new[]`

`new[]` rezerwuje tablicę w czasie działania programu i zwraca wskaźnik do pierwszego elementu. Wskaźnik nadal nie przechowuje rozmiaru. Dla każdej takiej alokacji trzeba dokładnie raz użyć `delete[]`:

```cpp
#include <iostream>

int main() {
    constexpr int size = 3;
    int* data = new int[size]{};  // nowa tablica: 0, 0, 0

    data[0] = 10;
    data[1] = 20;
    data[2] = 30;

    std::cout << data[1] << '\n'; // 20

    delete[] data;  // zwalnia tablicę utworzoną przez new[]
    data = nullptr; // zaznacza, że tego wskaźnika nie wolno już używać
}
```

Nie zamieniaj `delete[]` na `delete`, nie zwalniaj tej samej tablicy dwa razy i nie używaj wskaźnika po zwolnieniu pamięci. Pominięcie `delete[]` powoduje wyciek. Jeżeli program zakończy działanie wcześniej albo wystąpi wyjątek przed zwolnieniem, także można utracić kontrolę nad pamięcią. W nowym kodzie `std::vector` zwykle jest bezpieczniejszym i prostszym wyborem.

## Zwracanie kolekcji z funkcji

Wbudowanej tablicy nie można zwrócić z funkcji przez wartość. Nie zwracaj też adresu lokalnej tablicy: jej czas życia kończy się przy wyjściu z funkcji, więc zwrócony wskaźnik byłby wiszący.

Dla stałego rozmiaru zwróć `std::array`, a dla zmiennego — `std::vector`:

```cpp
#include <array>
#include <cstddef>
#include <vector>

std::array<int, 3> makeFixedValues() {
    return {10, 20, 30};
}

std::vector<int> makeValues(std::size_t count) {
    std::vector<int> values(count);
    for (std::size_t i = 0; i < count; ++i) {
        values[i] = static_cast<int>(i + 1);
    }
    return values;  // kontener trafia do wywołującego
}

int main() {
    std::array<int, 3> fixed = makeFixedValues();
    std::vector<int> dynamic = makeValues(4);
}
```

`fixed` ma dokładnie trzy elementy, a `dynamic` cztery. Zwrócone kontenery same zarządzają swoim czasem życia — nie trzeba zwracać wskaźnika do lokalnej tablicy ani pamiętać o `delete[]`.

## Tablice dwuwymiarowe

Wbudowana tablica dwuwymiarowa jest tablicą wierszy, a każdy wiersz jest tablicą kolumn. Pierwszy indeks wybiera wiersz, drugi element w tym wierszu:

```cpp
int main() {
    int matrix[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int value = matrix[1][2];  // drugi wiersz, trzecia kolumna: 6
}
```

Dla `matrix` prawidłowe indeksy wierszy to `0` i `1`, a kolumn — `0`, `1` i `2`. Elementy wbudowanej tablicy dwuwymiarowej leżą kolejno w pamięci, wiersz po wierszu.

Pętla zewnętrzna wybiera wiersz, a wewnętrzna przechodzi po jego kolumnach:

```cpp
#include <iostream>

int main() {
    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};

    for (int row = 0; row < 2; ++row) {
        for (int column = 0; column < 3; ++column) {
            std::cout << matrix[row][column] << ' ';
        }
        std::cout << '\n';
    }
}
```

### Przekazywanie wbudowanej tablicy dwuwymiarowej

Przy przekazaniu do funkcji pierwszy wymiar zamienia się w parametr wskaźnikowy, ale liczba kolumn musi pozostać znana w typie:

```cpp
#include <iostream>

void printMatrix(const int matrix[][3], int rows) {
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < 3; ++column) {
            std::cout << matrix[row][column] << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    int data[2][3] = {{1, 2, 3}, {4, 5, 6}};
    printMatrix(data, 2);
}
```

Parametr `const int matrix[][3]` jest w praktyce wskaźnikiem do wiersza złożonego z trzech elementów: `const int (*)[3]`. Liczbę wierszy przekazujemy osobno; szerokość wiersza wynika z typu. Nie można przekazać tej tablicy jako `int**` — to inny typ i inny układ danych.

### Wymiary znane dopiero podczas działania programu

Dla macierzy o wymiarach poznanych podczas działania programu prostym wyborem jest wektor wektorów:

```cpp
#include <vector>

int main() {
    int rows = 2;
    int columns = 3;
    std::vector<std::vector<int>> matrix(
        rows, std::vector<int>(columns, 0)
    );

    matrix[1][2] = 7;
}
```

Tutaj `matrix[1][2]` oznacza drugi wiersz i trzecią kolumnę. Każdy wiersz jest osobnym `std::vector`, więc wiersze nie muszą leżeć obok siebie w jednym bloku pamięci.

Jeśli potrzebny jest jeden ciągły blok elementów, można użyć pojedynczego wektora i zamienić parę indeksów na jeden indeks:

```cpp
#include <vector>

int main() {
    const int rows = 2;
    const int columns = 3;
    std::vector<int> cells(rows * columns);

    int row = 1;
    int column = 2;
    cells[row * columns + column] = 7; // indeks 1*3+2, czyli 5
}
```

Dla bardzo dużych lub zewnętrznych wymiarów trzeba dodatkowo sprawdzić, czy iloczyn `rows * columns` mieści się w obsługiwanym rozmiarze.

### Starszy wariant z `int**`

W starszym kodzie macierz o rozmiarze ustalanym podczas działania bywa tworzona przez tablicę wskaźników i osobną alokację każdego wiersza:

```cpp
#include <iostream>

int main() {
    const int rows = 2;
    const int columns = 3;

    int** matrix = new int*[rows];          // tablica wskaźników do wierszy
    for (int row = 0; row < rows; ++row) {
        matrix[row] = new int[columns]{};   // osobna tablica dla tego wiersza
    }

    matrix[1][2] = 7;
    std::cout << matrix[1][2] << '\n';      // 7

    for (int row = 0; row < rows; ++row) {
        delete[] matrix[row];               // najpierw zwolnij każdy wiersz
    }
    delete[] matrix;                        // na końcu tablicę wskaźników
}
```

`matrix` jest tu wskaźnikiem do wskaźnika (`int**`), a nie wskaźnikiem do jednego ciągłego bloku wszystkich liczb. Trzeba zwolnić każdy wiersz, a dopiero potem tablicę wskaźników. Pominięcie kroku powoduje wyciek. Jeśli alokacja któregoś wiersza się nie powiedzie, ręczne sprzątanie staje się bardziej skomplikowane. Do nowego kodu wybieraj raczej `std::vector`, który automatycznie zarządza pamięcią.

## Jak te trzy lekcje łączą się ze sobą

- **L-wartość** mówi, że wyrażenie takie jak `values[1]` oznacza konkretny element, który można zmienić.
- **Wskaźnik** przechowuje adres. `pointer` jest wartością adresową, a `*pointer` daje dostęp do obiektu pod tym adresem.
- **Tablica** przechowuje wiele elementów i ma ustalony rozmiar. Wskaźnik do pierwszego elementu tego rozmiaru nie pamięta.

Przed odczytem lub zapisem sprawdź, że obiekt nadal istnieje, wskaźnik nie jest pusty, a indeks mieści się w zakresie. Dla rozmiaru zmiennego `std::vector` zwykle upraszcza te sprawy: przechowuje elementy, pamięta ich liczbę i zarządza czasem życia pamięci.
