# Wskaźniki, tablice i napisy — quiz

Notatki: [Wskaźniki](../notatki/11_wskazniki.md), [Tablice](../notatki/12_tablice.md), [Napisy](../notatki/13_napisy.md), [Zaawansowane wskaźniki](../notatki/17_zaawansowane_wskazniki.md)

Sprawdź, czy rozumiesz adresy i dereferencję, czas życia obiektów, tablice i ich granice, napisy w C i C++ oraz inteligentne wskaźniki.

#### Q. Co wypisze ten program w C++ z zapisem przez wskaźnik?

```cpp
#include <iostream>

int main() {
    int a = 1;
    int* p = &a;
    *p = 5;
    int b = *p + 1;
    std::cout << a << ' ' << b << '\n';
}
```

* [ ] `1 6`
* [x] `5 6`
* [ ] `5 2`
* [ ] `1 2`

> **Wyjaśnienie:** `p` przechowuje adres `a`, więc `*p = 5` zmienia samą zmienną `a`. Następnie `*p + 1` odczytuje nową wartość 5 i daje 6.

#### Q. Jaki typ ma zmienna `q` po deklaracji `int* p, q;`?

* [ ] Wskaźnik na `int`
* [x] Zwykły `int`
* [ ] Referencja do `int`
* [ ] Wskaźnik na wskaźnik na `int`

> **Wyjaśnienie:** Gwiazdka w deklaracji odnosi się do konkretnej zmiennej, a nie do całego wiersza. Dlatego tylko `p` jest wskaźnikiem — czytelniej deklarować wskaźniki osobno.

#### Q. Który oznaczony wiersz tego programu w C++ ze wskaźnikami i `const` spowoduje błąd kompilacji?

```cpp
int main() {
    int x = 5;
    int y = 10;
    const int* a = &x;
    int* const b = &x;
    a = &y;      // (1)
    *b = 6;      // (2)
    *a = 7;      // (3)
    int z = *a;  // (4)
    return z;
}
```

* [ ] `(1)`
* [ ] `(2)`
* [x] `(3)`
* [ ] `(4)`

> **Wyjaśnienie:** `const int*` pozwala zmienić adres, ale zabrania zapisu przez wskaźnik, więc `*a = 7` jest błędem. `int* const` ma stały adres, lecz pozwala zmieniać wskazywany obiekt.

#### Q. Co można powiedzieć o tym programie w C++, który zwraca adres zmiennej lokalnej?

```cpp
#include <iostream>

int* utworz() {
    int lokalna = 7;
    return &lokalna;
}

int main() {
    int* p = utworz();
    std::cout << *p << '\n';
}
```

* [ ] Zawsze wypisze `7`
* [ ] Zawsze wypisze `0`
* [x] Ma niezdefiniowane zachowanie
* [ ] Nie da się go skompilować

> **Wyjaśnienie:** Zmienna `lokalna` przestaje istnieć po wyjściu z funkcji, więc `p` jest wskaźnikiem wiszącym, a jego dereferencja to niezdefiniowane zachowanie. Kompilator zwykle tylko ostrzega; program może wypisać cokolwiek albo ulec awarii.

#### Q. Co wypisze ten program w C++ z przeciążeniami dla `int` i `int*`?

```cpp
#include <iostream>

void show(int) { std::cout << "int "; }
void show(int*) { std::cout << "int* "; }

int main() {
    show(0);
    show(nullptr);
    std::cout << '\n';
}
```

* [ ] `int* int*`
* [x] `int int*`
* [ ] `int int`
* [ ] Błąd: niejednoznaczne wywołanie `show(0)`

> **Wyjaśnienie:** `0` jest literałem całkowitym, więc dokładnie pasuje do `show(int)`. `nullptr` ma typ wskaźnikowy i wybiera `show(int*)` — dlatego w C++ do pustego wskaźnika używa się `nullptr`, a nie `0` czy `NULL`.

#### Q. Co wypisze ten program w C++ ze wskaźnikiem na wskaźnik?

```cpp
#include <iostream>

int main() {
    int a = 1;
    int b = 2;
    int* p = &a;
    int** pp = &p;
    *pp = &b;
    **pp = 5;
    std::cout << a << ' ' << b << ' ' << (p == &b) << '\n';
}
```

* [ ] `5 2 0`
* [x] `1 5 1`
* [ ] `1 5 0`
* [ ] `5 5 1`

> **Wyjaśnienie:** `*pp` to sama zmienna `p`, więc `*pp = &b` przestawia `p` na `b`. Potem `**pp` oznacza `b`, które dostaje 5, a `a` pozostaje bez zmian.

#### Q. Co wypisze ten program w C++ z referencją?

```cpp
#include <iostream>

int main() {
    int a = 1;
    int b = 2;
    int& r = a;
    r = b;
    r = 3;
    std::cout << a << ' ' << b << '\n';
}
```

* [ ] `1 3`
* [x] `3 2`
* [ ] `2 3`
* [ ] `3 3`

> **Wyjaśnienie:** Referencji nie da się przepiąć: `r = b` nie wiąże `r` z `b`, tylko przypisuje wartość `b` do `a`. Kolejne `r = 3` znów zmienia `a`, a `b` pozostaje równe 2.

#### Q. Wskaźnik `p` wskazywał zmienną lokalną bloku, który już się zakończył. Jaki będzie wynik sprawdzenia `p != nullptr`?

* [ ] Fałsz, bo wskaźnik sam zmienił się w `nullptr`
* [x] Prawda, choć wskaźnika nie wolno dereferencjonować
* [ ] Błąd kompilacji, bo zmienna już nie istnieje
* [ ] Zgłoszenie wyjątku `std::bad_alloc`

> **Wyjaśnienie:** Zachowany adres nie zmienia się automatycznie w `nullptr`. Test `p != nullptr` wykrywa tylko pusty wskaźnik, nie wiszący — o czasie życia obiektu trzeba pamiętać samodzielnie.

#### Q. Co wypisze ten program w C++ z częściowo zainicjalizowaną tablicą?

```cpp
#include <iostream>

int main() {
    int t[5] = {1, 2};
    std::cout << sizeof(t) / sizeof(t[0]) << ' ' << t[4] << '\n';
}
```

* [ ] `2 0`
* [x] `5 0`
* [ ] `5` i nieokreślona wartość
* [ ] `2` i nieokreślona wartość

> **Wyjaśnienie:** Rozmiar tablicy to 5 elementów, a przy inicjalizacji listą brakujące elementy otrzymują wartość 0. Nieokreślone wartości miałaby tylko lokalna tablica bez żadnego inicjalizatora.

#### Q. Co wypisze ten program w C na typowej platformie 64-bitowej?

```c
#include <stdio.h>

void f(int t[10]) {
    printf("%zu\n", sizeof(t));
}

int main(void) {
    int dane[10] = {0};
    f(dane);
    return 0;
}
```

* [ ] `40`
* [x] `8`
* [ ] `10`
* [ ] `4`

> **Wyjaśnienie:** W parametrze funkcji `int t[10]` jest dostosowywane do `int* t`, więc `sizeof(t)` daje rozmiar wskaźnika — na typowej platformie 64-bitowej 8 bajtów. Rozmiar tablicy trzeba przekazać osobnym parametrem.

#### Q. Co wypisze ten program w C++ z arytmetyką wskaźników?

```cpp
#include <iostream>

int main() {
    int v[4] = {10, 20, 30, 40};
    int* p = v + 1;
    std::cout << *(p + 2) << ' ' << p[-1] << '\n';
}
```

* [ ] `30 10`
* [x] `40 10`
* [ ] `40 20`
* [ ] `30 20`

> **Wyjaśnienie:** `p` wskazuje `v[1]`. Dodanie liczby przesuwa wskaźnik o elementy, więc `*(p + 2)` to `v[3]`, czyli 40, a `p[-1]` oznacza `*(p - 1)`, czyli `v[0]`.

#### Q. Co można powiedzieć o pętli `for (int i = 0; i <= 3; ++i) t[i] = 0;` dla tablicy `int t[3];`?

* [ ] Zeruje dokładnie trzy elementy tablicy
* [x] Zapisuje poza tablicą — niezdefiniowane zachowanie
* [ ] Kompilator zawsze odrzuci taki kod
* [ ] Rzuca wyjątek `std::out_of_range` przy `i == 3`

> **Wyjaśnienie:** Prawidłowe indeksy to 0, 1 i 2, a przy `i == 3` następuje zapis za końcem tablicy. Wbudowana tablica nie sprawdza zakresu, więc błąd nie musi być od razu widoczny.

#### Q. Co wypisze ten program w C++, w którym funkcja zmienia elementy przekazanej tablicy?

```cpp
#include <iostream>

void podwoj(int t[], int n) {
    for (int i = 0; i < n; ++i) {
        t[i] *= 2;
    }
}

int main() {
    int dane[3] = {1, 2, 3};
    podwoj(dane, 3);
    std::cout << dane[0] << ' ' << dane[1] << ' ' << dane[2] << '\n';
}
```

* [ ] `1 2 3`
* [x] `2 4 6`
* [ ] `2 2 3`
* [ ] Błąd kompilacji: tablicy nie można przekazać

> **Wyjaśnienie:** Funkcja dostaje kopię adresu pierwszego elementu, a nie kopię tablicy. Zapis `t[i] *= 2` zmienia więc elementy tablicy `dane` w `main`.

#### Q. Macierz $3 \times 4$ przechowujesz w jednym `std::vector<int>` wiersz po wierszu (`columns == 4`). Pod jakim indeksem leży element z wiersza 2 i kolumny 1, licząc od zera?

* [x] `9`
* [ ] `5`
* [ ] `7`
* [ ] `12`

> **Wyjaśnienie:** Przy układzie wierszami indeks to `row * columns + column`, czyli $2 \cdot 4 + 1 = 9$. Wynik 5 dałoby błędne zamienienie ról wiersza i kolumny.

#### Q. Jaki jest rzeczywisty typ parametru `const int matrix[][3]` w deklaracji funkcji C++?

* [ ] `const int**`
* [ ] `const int* [3]`
* [x] `const int (*)[3]`
* [ ] `const int[3][3]`

> **Wyjaśnienie:** Pierwszy wymiar zamienia się we wskaźnik, więc parametr to wskaźnik do wiersza złożonego z trzech `int`. To inny typ i inny układ danych niż `int**`, dlatego takiej tablicy nie przekazuje się jako `int**`.

#### Q. Jak poprawnie zwolnić pamięć przydzieloną instrukcją `int* d = new int[5];`?

* [ ] `delete d;`
* [x] `delete[] d;`
* [ ] `free(d);`
* [ ] `d = nullptr;`

> **Wyjaśnienie:** Pamięć z `new[]` zwalnia się dokładnie raz przez `delete[]`. Zwykłe `delete` lub `free` to błąd, a samo przypisanie `nullptr` powoduje wyciek.

#### Q. Co wypisze ten program w C++ odczytujący element `std::array` metodą `at`?

```cpp
#include <array>
#include <iostream>
#include <stdexcept>

int main() {
    std::array<int, 3> a{10, 20, 30};
    try {
        std::cout << a.at(3) << '\n';
    } catch (const std::out_of_range&) {
        std::cout << "poza zakresem\n";
    }
}
```

* [ ] `30`
* [ ] `0`
* [x] `poza zakresem`
* [ ] Nieokreśloną wartość spoza tablicy

> **Wyjaśnienie:** `at` sprawdza indeks i dla wartości spoza zakresu `0`–`2` zgłasza `std::out_of_range`. Operator `[]` nie sprawdza granic — `a[3]` byłoby niezdefiniowanym zachowaniem.

#### Q. Co wypisze ten program w C z tablicą `char` większą niż napis?

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char t[10] = "kot";
    printf("%zu %zu\n", sizeof t, strlen(t));
    return 0;
}
```

* [ ] `4 3`
* [x] `10 3`
* [ ] `10 4`
* [ ] `3 3`

> **Wyjaśnienie:** `sizeof` podaje pojemność całej tablicy (10 bajtów), a `strlen` liczy bajty przed pierwszym `'\0'` (3). Długość napisu i pojemność bufora to różne wartości.

#### Q. Co wypisze ten program w C porównujący dwie tablice z napisem `"kot"`?

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char a[] = "kot";
    char b[] = "kot";
    printf("%d %d\n", a == b, strcmp(a, b) == 0);
    return 0;
}
```

* [ ] `1 1`
* [x] `0 1`
* [ ] `1 0`
* [ ] `0 0`

> **Wyjaśnienie:** `a == b` porównuje adresy dwóch różnych tablic, więc daje 0. Treść napisów porównuje `strcmp`, który dla równych tekstów zwraca 0.

#### Q. Co można powiedzieć o tym fragmencie w C: `char *p = "Ala"; p[0] = 'O';`?

* [ ] Zmienia napis na `"Ola"`
* [ ] Nie kompiluje się w C
* [x] Ma niezdefiniowane zachowanie
* [ ] Zmienia tylko kopię literału

> **Wyjaśnienie:** `p` wskazuje bezpośrednio na literał, a zapis do literału ma niezdefiniowane zachowanie. Modyfikowalną kopię daje `char t[] = "Ala";`, a wskaźnik do literału warto deklarować jako `const char *`.

#### Q. Co może się stać po wywołaniu `strncpy(dst, src, n)`, gdy `src` ma co najmniej `n` bajtów?

* [x] W `dst` może zabraknąć kończącego `'\0'`
* [ ] `dst` zostanie powiększony do potrzebnego rozmiaru
* [ ] Funkcja zwróci `NULL` i nic nie skopiuje
* [ ] Reszta `src` zostanie dopisana przy kolejnym wywołaniu

> **Wyjaśnienie:** `strncpy` kopiuje najwyżej `n` bajtów i nie dopisuje terminatora, jeśli źródło jest co najmniej tak długie. Nie jest więc automatycznie bezpieczną wersją `strcpy`.

#### Q. Co wypisze ten program w C z funkcją `snprintf` i zbyt małym buforem?

```c
#include <stdio.h>

int main(void) {
    char buf[5];
    int n = snprintf(buf, sizeof buf, "%s", "abcdefgh");
    printf("%d %s\n", n, buf);
    return 0;
}
```

* [ ] `4 abcd`
* [x] `8 abcd`
* [ ] `5 abcde`
* [ ] `8 abcdefgh`

> **Wyjaśnienie:** `snprintf` zapisuje najwyżej 4 znaki i `'\0'`, ale zwraca długość, jaką miałby pełny tekst (8). Wynik większy lub równy rozmiarowi bufora oznacza obcięcie.

#### Q. Co wypisze ten program w C z funkcją `strtol`?

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *tekst = "123abc";
    char *koniec;
    long liczba = strtol(tekst, &koniec, 10);
    printf("%ld %s\n", liczba, koniec);
    return 0;
}
```

* [x] `123 abc`
* [ ] `0 123abc`
* [ ] `123` i pusty napis
* [ ] `123abc abc`

> **Wyjaśnienie:** `strtol` odczytuje początkową liczbę 123 i ustawia `koniec` na pierwszy nieprzetworzony znak, czyli `a`. Sprawdzenie `*koniec != '\0'` pozwala wykryć dodatkowe znaki po liczbie.

#### Q. Co wypisze ten program w C, jeśli plik źródłowy i kodowanie wykonania to UTF-8 (domyślnie w GCC na Linuksie)?

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    printf("%zu\n", strlen("ą"));
    return 0;
}
```

* [ ] `1`
* [x] `2`
* [ ] `3`
* [ ] `0`

> **Wyjaśnienie:** `strlen` liczy bajty przed `'\0'`, a nie litery widoczne dla człowieka. W UTF-8 polska litera `ą` zajmuje dwa bajty.

#### Q. Co wypisze ten program w C++ z metodą `substr`?

```cpp
#include <iostream>
#include <string>

int main() {
    std::string s = "programowanie";
    std::cout << s.substr(3, 4) << '\n';
}
```

* [x] `gram`
* [ ] `gra`
* [ ] `ogra`
* [ ] `gramo`

> **Wyjaśnienie:** `substr(pozycja, liczba)` zaczyna od bajtu o indeksie 3 (licząc od zera: `p`, `r`, `o`, `g`) i bierze 4 znaki. Drugi argument to długość, a nie indeks końca.

#### Q. Co wypisze ten program w C++ z bajtem `'\0'` wewnątrz `std::string`?

```cpp
#include <cstring>
#include <iostream>
#include <string>

int main() {
    std::string s("ab\0cd", 5);
    std::cout << s.size() << ' ' << std::strlen(s.c_str()) << '\n';
}
```

* [x] `5 2`
* [ ] `2 2`
* [ ] `5 5`
* [ ] `6 2`

> **Wyjaśnienie:** `std::string` pamięta pełną długość, więc przechowuje wszystkie 5 bajtów. Funkcje C, takie jak `strlen`, kończą napis na pierwszym `'\0'` i widzą tylko `ab`.

#### Q. Dlaczego funkcja `std::string_view nazwa() { std::string s = "Ala"; return s; }` jest błędna?

* [ ] `std::string_view` nie przechowuje krótkich napisów
* [ ] Konwersja `std::string` na `std::string_view` jest zabroniona
* [x] Zwrócony widok wskazuje na znaki zniszczonego napisu
* [ ] Widok kopiuje cały napis, co jest zbyt kosztowne

> **Wyjaśnienie:** `std::string_view` nie jest właścicielem znaków — przechowuje tylko adres i długość. Lokalny `s` znika po wyjściu z funkcji, więc widok staje się wiszący.

#### Q. Co wypisze ten program w C++ z funkcją `std::stoi` i parametrem `pos`?

```cpp
#include <cstddef>
#include <iostream>
#include <string>

int main() {
    std::size_t pos = 0;
    int v = std::stoi("42abc", &pos);
    std::cout << v << ' ' << pos << '\n';
}
```

* [x] `42 2`
* [ ] `42 5`
* [ ] `0 0`
* [ ] Program kończy się wyjątkiem `std::invalid_argument`

> **Wyjaśnienie:** `std::stoi` akceptuje poprawny początek liczby i zapisuje w `pos` liczbę przetworzonych znaków. Wyjątek pojawiłby się dopiero, gdyby tekst nie zaczynał się od liczby; `pos != tekst.size()` wykrywa nadmiarowe znaki.

#### Q. Co wypisze ten program w C++ ze wskaźnikiem na funkcję?

```cpp
#include <iostream>

int dodaj(int a, int b) { return a + b; }
int pomnoz(int a, int b) { return a * b; }

int main() {
    int (*op)(int, int) = dodaj;
    int x = op(2, 3);
    op = pomnoz;
    std::cout << x << ' ' << op(2, 3) << '\n';
}
```

* [ ] `5 5`
* [x] `5 6`
* [ ] `6 6`
* [ ] `6 5`

> **Wyjaśnienie:** `op` najpierw wskazuje `dodaj`, więc `x` dostaje 5. Po przypisaniu `op = pomnoz` to samo wywołanie `op(2, 3)` uruchamia mnożenie i daje 6.

#### Q. Co oznacza deklaracja `int* tab[3];`?

* [x] Tablicę trzech wskaźników na `int`
* [ ] Wskaźnik na tablicę trzech wartości `int`
* [ ] Funkcję zwracającą wskaźnik na `int`
* [ ] Wskaźnik na wskaźnik na `int`

> **Wyjaśnienie:** Bez nawiasów `[3]` wiąże się z nazwą `tab`, więc `tab` jest tablicą, a jej elementy mają typ `int*`. Wskaźnik na tablicę trzech `int` zapisuje się jako `int (*tab)[3]`.

#### Q. Co deklaruje zapis `void *operacja(int);`?

* [ ] Wskaźnik na funkcję przyjmującą `int` i zwracającą `void`
* [x] Funkcję przyjmującą `int` i zwracającą `void*`
* [ ] Wskaźnik typu `void*` zainicjalizowany liczbą
* [ ] Tablicę wskaźników `void*` o rozmiarze `int`

> **Wyjaśnienie:** Bez nawiasów wokół `*operacja` gwiazdka należy do typu wyniku. Wskaźnik na funkcję wymaga zapisu `void (*operacja)(int);`.

#### Q. Co wypisze ten program w C++ ze wskaźnikiem do składowej klasy?

```cpp
#include <iostream>

struct Punkt {
    int x;
    int y;
};

int main() {
    Punkt p{1, 2};
    int Punkt::* pole = &Punkt::y;
    p.*pole = 7;
    Punkt* w = &p;
    w->*pole += 1;
    std::cout << p.x << ' ' << p.y << '\n';
}
```

* [x] `1 8`
* [ ] `8 2`
* [ ] `1 7`
* [ ] `7 2`

> **Wyjaśnienie:** `pole` wskazuje, którą składową wybrać (`y`), ale nie konkretny obiekt. `p.*pole` i `w->*pole` odnoszą się do `p.y`: najpierw 7, potem 8.

#### Q. Co wypisze ten program w C++ przenoszący `std::unique_ptr`?

```cpp
#include <iostream>
#include <memory>
#include <utility>

int main() {
    auto pierwszy = std::make_unique<int>(5);
    auto drugi = std::move(pierwszy);
    std::cout << *drugi << ' ' << static_cast<bool>(pierwszy) << '\n';
}
```

* [ ] `5 1`
* [x] `5 0`
* [ ] `0 1`
* [ ] Błąd kompilacji: `unique_ptr` nie da się przenieść

> **Wyjaśnienie:** `unique_ptr` nie można kopiować, ale można przenieść własność. Po przeniesieniu właścicielem jest `drugi`, a `pierwszy` jest pusty, więc konwersja na `bool` daje `false`.

#### Q. Co wypisze ten program w C++ z licznikiem właścicieli `std::shared_ptr`?

```cpp
#include <iostream>
#include <memory>

int main() {
    auto a = std::make_shared<int>(5);
    std::cout << a.use_count();
    {
        auto b = a;
        std::cout << ' ' << a.use_count();
    }
    std::cout << ' ' << a.use_count() << '\n';
}
```

* [ ] `1 1 1`
* [x] `1 2 1`
* [ ] `1 2 2`
* [ ] `0 1 0`

> **Wyjaśnienie:** Kopia `shared_ptr` dodaje współwłaściciela, więc w bloku jest ich dwóch. Po wyjściu z bloku `b` znika, licznik wraca do 1, a obiekt nadal istnieje.

#### Q. Co wypisze ten program w C++ z `std::weak_ptr`?

```cpp
#include <iostream>
#include <memory>

int main() {
    std::weak_ptr<int> obserwator;
    {
        auto wlasciciel = std::make_shared<int>(42);
        obserwator = wlasciciel;
        if (auto dostep = obserwator.lock()) {
            std::cout << *dostep << ' ';
        }
    }
    if (auto dostep = obserwator.lock()) {
        std::cout << *dostep << '\n';
    } else {
        std::cout << "brak\n";
    }
}
```

* [ ] `42 42`
* [x] `42 brak`
* [ ] `brak brak`
* [ ] `42 0`

> **Wyjaśnienie:** `weak_ptr` nie przedłuża życia obiektu. Po zniszczeniu ostatniego `shared_ptr` obiekt znika, a `lock()` zwraca pusty wskaźnik, więc wykonuje się gałąź `else`.

#### Q. Obiekt A przechowuje `std::shared_ptr` do B, a B przechowuje `std::shared_ptr` do A. Co się stanie, gdy znikną wszystkie inne wskaźniki do nich?

* [ ] Oba obiekty zostaną od razu zniszczone
* [x] Żaden nie zostanie zniszczony, bo liczniki nie spadną do zera
* [ ] Program zakończy się wyjątkiem `std::bad_weak_ptr`
* [ ] Zostanie zniszczony tylko obiekt utworzony wcześniej

> **Wyjaśnienie:** W cyklu każdy obiekt utrzymuje drugi przy życiu, więc liczba współwłaścicieli nigdy nie spada do zera i pamięć wycieka. Jeden kierunek powiązania powinien być obserwowany przez `std::weak_ptr`.

#### Q. Co się stanie, gdy z tego samego surowego adresu z `new int(5)` utworzysz dwa obiekty `std::unique_ptr<int>`?

* [ ] Drugi wskaźnik automatycznie zostanie pusty
* [ ] Kompilator zgłosi błąd: kopiowanie `unique_ptr`
* [x] Oba spróbują usunąć ten sam obiekt — niezdefiniowane zachowanie
* [ ] Powstanie współdzielona własność jak w `shared_ptr`

> **Wyjaśnienie:** Każdy z nich uważa się za jedynego właściciela i w destruktorze wywoła `delete`, więc obiekt zostanie usunięty dwa razy. Dlatego obiekt i właściciela tworzy się razem przez `std::make_unique`.

#### Q. Funkcja ma tylko odczytać istniejący obiekt typu `Dane`, bez przejmowania własności. Jaki typ parametru jest najlepszy?

* [ ] `std::unique_ptr<Dane>`
* [ ] `std::shared_ptr<Dane>`
* [x] `const Dane&`
* [ ] `std::weak_ptr<Dane>`

> **Wyjaśnienie:** Referencja do stałej gwarantuje istnienie obiektu podczas wywołania, unika kopii i nie mówi nic o własności. Inteligentny wskaźnik przez wartość sugerowałby przejęcie lub współdzielenie własności.
