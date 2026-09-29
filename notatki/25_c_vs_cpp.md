# C i C++: podobne początki, różne języki

C i C++ są ze sobą spokrewnione. W obu językach spotkasz typy takie jak `int`, instrukcje `if`, pętle `for` i funkcje zapisane w podobny sposób. Dlatego na początku kod może wyglądać niemal identycznie.

Podobieństwo składni nie oznacza jednak, że są to dwa warianty tego samego języka. C i C++ mają osobne standardy, biblioteki i reguły. Program napisany zgodnie ze standardem C może wymagać zmian, zanim będzie poprawnym programem C++.

Ta notatka pokazuje, co oba języki mają wspólnego, gdzie różnią się w praktyce i jak te różnice wpływają na sposób pisania programów.

## Skąd wzięły się C i C++?

C powstał na początku lat 70. XX wieku w Bell Laboratories. Dennis Ritchie rozwijał go jako język przydatny do pisania oprogramowania systemowego; ważnym przykładem jest system UNIX. Język został ustandaryzowany pod koniec lat 80.

C++ rozwijał Bjarne Stroustrup, również w Bell Laboratories. Prace rozpoczęły się w latach 70., a wczesna nazwa „C with Classes” opisywała główny pomysł: zachować wiele znanych konstrukcji C i dodać klasy. C++ później rozwinął się w osobny język z własnym standardem i biblioteką.

Dlatego wiele prostych fragmentów kodu jest wspólnych, ale reguły obu języków z czasem rozeszły się. Znajomość jednego pomaga w nauce drugiego, lecz nie zastępuje poznania jego zasad.

## 1. Wspólny zapis nie oznacza wspólnych reguł

Prosta funkcja może wyglądać tak samo w C i C++:

```c
int podwoj(int liczba) {
    return liczba * 2;
}
```

Funkcja przyjmuje liczbę całkowitą, mnoży ją przez dwa i zwraca wynik. W takim przykładzie oba języki używają tej samej składni.

Różnice stają się widoczne przy bardziej zaawansowanych elementach. Na przykład w C można przypisać wskaźnik `void *` do wskaźnika na konkretny typ bez rzutowania. C++ wymaga jawnego wskazania konwersji:

```c
/* C */
int liczba = 10;
void *adres = &liczba;
int *wskaznik = adres;
```

```cpp
// C++
int liczba = 10;
void *adres = &liczba;
int *wskaznik = static_cast<int *>(adres);
```

W obu przykładach `adres` przechowuje adres zmiennej `liczba`. Wskaźnik `wskaznik` ma wskazywać na tę samą zmienną. Różni się reguła przypisania: C wykonuje tę konwersję niejawnie, a C++ wymaga jawnego zapisu.

To nie znaczy, że każde rzutowanie w C++ jest bezpieczne. Programista nadal musi wiedzieć, jaki obiekt znajduje się pod danym adresem. Rzutowania i wskaźniki opisują osobne notatki: [konwersje i rzutowania](19_konwersje.md) oraz [wskaźniki](11_wskazniki.md).

Różnicę mogą ujawnić także słowa kluczowe. C++ zarezerwował nazwy takie jak `class` i `template`, których C nie używa jako słów kluczowych. Dlatego nazwa zmiennej dopuszczalna w C może kolidować ze składnią C++:

```c
int class = 3; /* class może być identyfikatorem w C */
```

Ten zapis nie jest poprawny w C++, bo `class` rozpoczyna tam deklarację klasy. Przy przenoszeniu kodu warto sprawdzić nie tylko instrukcje, ale też nazwy użyte przez program.

## 2. Typy i funkcje

Oba języki mają podstawowe typy, takie jak `char`, `int`, `float` i `double`. C++ oferuje między innymi referencje, klasy, przeciążanie funkcji i szablony. C ma inne sposoby wyrażania części tych idei.

### Przeciążanie funkcji

W C++ można zdefiniować kilka funkcji o tej samej nazwie, jeśli różnią się parametrami:

```cpp
int suma(int a, int b) {
    return a + b;
}

double suma(double a, double b) {
    return a + b;
}

int liczba = suma(2, 3);        // wywołuje wersję dla int
double ulamek = suma(2.5, 3.1); // wywołuje wersję dla double
```

Kompilator wybiera wersję na podstawie typów argumentów. W C nie można zdefiniować w ten sposób dwóch funkcji `suma`; trzeba użyć innych nazw, na przykład `suma_int` i `suma_double`.

### Referencje i wskaźniki

Referencja w C++ jest inną nazwą dla istniejącej zmiennej. Można jej użyć, aby funkcja zmieniła argument bez kopiowania go:

```cpp
void zwieksz(int &liczba) {
    ++liczba;
}

int main() {
    int wynik = 5;
    zwieksz(wynik);
    // wynik ma teraz wartość 6
}
```

Znak `&` w parametrze oznacza, że funkcja pracuje na oryginalnej zmiennej. W C podobny efekt osiąga się przez przekazanie wskaźnika:

```c
void zwieksz(int *liczba) {
    ++*liczba;
}

int main(void) {
    int wynik = 5;
    zwieksz(&wynik);
    /* wynik ma teraz wartość 6 */
}
```

Wersja C przekazuje adres jawnie za pomocą `&wynik`, a funkcja odczytuje lub zmienia wartość pod tym adresem przez `*liczba`. Wersja C++ zapisuje ten sam zamiar przez referencję. Referencja nie zastępuje wskaźników we wszystkich sytuacjach: wskaźnik może na przykład nie wskazywać na żaden obiekt (`nullptr`), a referencja musi być związana z obiektem.

### Klasy i szablony

C++ pozwala łączyć dane i operacje na tych danych w klasach. Klasa może ukrywać szczegóły, których użytkownik obiektu nie musi znać:

```cpp
class Licznik {
public:
    void zwieksz() {
        ++wartosc_;
    }

    int odczytaj() const {
        return wartosc_;
    }

private:
    int wartosc_ = 0;
};
```

Użytkownik klasy może wywołać `zwieksz()` i `odczytaj()`, ale nie może bezpośrednio zmienić pola `wartosc_`, bo jest ono prywatne. Dzięki temu klasa kontroluje sposób modyfikowania swojego stanu. Klasy i obiekty omawia notatka [programowanie obiektowe](15_programowanie_obietkowe.md).

Szablon pozwala napisać funkcję, której typ argumentów nie jest ustalony z góry:

```cpp
template <typename T>
T maksimum(T a, T b) {
    return a < b ? b : a;
}

int m = maksimum(3, 8);
double d = maksimum(2.5, 1.7);
```

Kompilator tworzy wersję funkcji odpowiednią dla użytego typu. Ten przykład działa dla typów, które można porównywać operatorem `<` i których wartość można zwrócić. Szablony są ważną częścią C++, między innymi dlatego, że biblioteka standardowa używa ich do tworzenia kontenerów i algorytmów. C nie ma szablonów wbudowanych w język.

Operator `+` można też przeciążyć dla własnego typu. Dzięki temu zapis dodawania może odpowiadać temu, co działanie znaczy w danej dziedzinie:

```cpp
struct Punkt {
    double x;
    double y;
};

Punkt operator+(Punkt a, Punkt b) {
    return {a.x + b.x, a.y + b.y};
}

int main() {
    Punkt p{1.0, 2.0};
    Punkt q{3.0, 4.0};
    Punkt suma = p + q; // (4.0, 6.0)
}
```

Wyrażenie `p + q` wywołuje tu funkcję, która dodaje osobno współrzędne punktów. W C trzeba użyć nazwanej funkcji, na przykład `dodaj_punkty(p, q)`, bo nie można zmienić znaczenia operatora dla własnego typu. Operator warto przeciążać tylko wtedy, gdy jego znaczenie będzie naturalne dla czytelnika. Więcej przykładów jest w notatce o [przeciążaniu](18_przeciazanie.md).

## 3. Biblioteki i wejście-wyjście

Oba języki korzystają z dyrektywy `#include`, ale często dołączają inne nagłówki i używają innych narzędzi.

W C prosty tekst można wypisać funkcją `printf` z nagłówka `<stdio.h>`:

```c
#include <stdio.h>

int main(void) {
    printf("Witaj!\n");
    return 0;
}
```

`#include <stdio.h>` udostępnia deklarację `printf`. Zapis `\n` oznacza znak nowego wiersza, a `return 0` informuje system, że program zakończył się poprawnie.

W C++ można użyć strumienia `std::cout` z nagłówka `<iostream>`:

```cpp
#include <iostream>

int main() {
    std::cout << "Witaj!\n";
}
```

Operator `<<` przekazuje tekst do strumienia wyjściowego. Nazwa `std::cout` składa się z `cout` oraz `std::`, które wskazuje, że element należy do przestrzeni nazw biblioteki standardowej C++.

C++ ma też nagłówki odpowiadające wielu nagłówkom C. Na przykład dla funkcji wejścia-wyjścia z C można dołączyć `<cstdio>` i zapisać `std::printf`. W nowym kodzie C++ często wybiera się jednak narzędzia biblioteki C++, takie jak strumienie, kontenery i algorytmy.

## 4. Pamięć i czas życia zasobów

Programy często potrzebują pamięci lub innych zasobów, na przykład otwartego pliku. Ważne jest nie tylko uzyskanie zasobu, ale też zwolnienie go we właściwym momencie.

### Ręczne zarządzanie w C

Funkcja `malloc` prosi o blok pamięci. Zwraca adres początku bloku albo `NULL`, gdy przydział się nie powiedzie:

```c
#include <stdlib.h>

int main(void) {
    int *wartosc = malloc(sizeof *wartosc);
    if (wartosc == NULL) {
        return EXIT_FAILURE;
    }

    *wartosc = 42;
    /* tutaj program może używać wartości */

    free(wartosc);
    return EXIT_SUCCESS;
}
```

`sizeof *wartosc` oblicza rozmiar obiektu, na który wskazuje `wartosc`, czyli rozmiar typu `int`. Ten zapis pozostaje poprawny, nawet jeśli później zmieni się typ wskaźnika. Po zakończeniu pracy `free` zwalnia pamięć. Brak `free` może powodować wyciek pamięci; zwolnienie tego samego bloku więcej niż raz albo dalsze używanie go po zwolnieniu to błędy.

### Zarządzanie czasem życia w C++

C++ ma `new` i `delete`, ale w nowoczesnym kodzie zwykle wybiera się obiekty, które same pilnują czasu życia zasobów:

```cpp
#include <memory>

int main() {
    auto wartosc = std::make_unique<int>(42);
    // wartosc wskazuje na int o wartości 42
}
```

`std::make_unique` (dostępne od C++14) tworzy obiekt i zwraca wskaźnik z wyłączną własnością. Gdy zmienna `wartosc` przestaje istnieć, obiekt jest automatycznie usuwany. Nie trzeba w tym przykładzie pamiętać o osobnym `delete`.

To podejście nazywa się RAII: obiekt przejmuje odpowiedzialność za zasób i zwalnia go, gdy kończy się jego czas życia. W praktyce często nie trzeba nawet tworzyć pojedynczego obiektu dynamicznie. Jeśli potrzebna jest kolekcja liczb, `std::vector<int>` sam zarządza pamięcią potrzebną na elementy.

`malloc` i `free` nie są zamiennikami `new` i `delete` w C++. `new` tworzy obiekt i uruchamia jego konstruktor, a `delete` uruchamia destruktor. Funkcje `malloc` i `free` zarządzają surową pamięcią i nie wykonują tych czynności dla obiektów C++.

## 5. Zgłaszanie i obsługa błędów

W C wiele funkcji sygnalizuje błąd przez wartość zwrotną. Wywołujący sprawdza wynik i sam podejmuje dalsze działanie. Przykładem jest sprawdzenie, czy `malloc` zwrócił `NULL`.

C++ także korzysta z wartości zwrotnych, ale ma dodatkowo wyjątki. Funkcja może zgłosić wyjątek przez `throw`, a kod, który potrafi obsłużyć błąd, przechwytuje go przez `catch`:

```cpp
#include <iostream>
#include <stdexcept>

int podziel(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Dzielnik nie może być zerem");
    }
    return a / b;
}

int main() {
    try {
        std::cout << podziel(10, 0) << '\n';
    } catch (const std::invalid_argument &blad) {
        std::cerr << "Nie można wykonać działania: " << blad.what() << '\n';
    }
}
```

Funkcja `podziel` wykrywa przypadek, którego nie może obsłużyć, i zgłasza wyjątek. Wykonanie przechodzi wtedy do pasującego bloku `catch`; linia wypisująca wynik nie zostaje wykonana. W C++ wyjątki nie są obowiązkowe — wiele funkcji nadal zwraca kody błędów lub wartości opisujące brak wyniku. C nie ma mechanizmu `try`/`catch` wbudowanego w język.

## 6. Czy C++ zawsze jest szybszy?

Nie. Zarówno C, jak i C++ mogą być kompilowane do kodu maszynowego, a o szybkości konkretnego programu decydują między innymi algorytm, sposób użycia pamięci, kompilator i jego ustawienia. Sam wybór języka nie gwarantuje przewagi.

C++ udostępnia mechanizmy, które mogą wiązać się z dodatkową pracą lub pamięcią, na przykład funkcje wirtualne. Jednocześnie abstrakcje takie jak `std::vector` mogą być równie wydajne jak dobrze napisany kod ręczny. Koszt zależy od użycia i kompilatora, więc gdy wydajność ma znaczenie, mierzy się działający program.

Oba języki spotyka się w systemach operacyjnych, oprogramowaniu wbudowanym, bibliotekach i aplikacjach wymagających wysokiej wydajności. Często wybór zależy od istniejącego kodu, dostępnych bibliotek, platformy oraz doświadczenia zespołu, a nie od jednej uniwersalnej reguły.

## 7. Standardy i kompilatory

Standard opisuje reguły języka i bibliotekę standardową. Określenia C17, C23, C++20 i C++23 oznaczają różne wydania standardów. Kompilator może obsługiwać kilka z nich, ale obsługa konkretnej funkcji zależy od jego wersji.

| Język | Ważne wydania | Przykładowe nowości |
| --- | --- | --- |
| C | C89/C90, C99, C11, C17/C18, [C23](https://committee.iso.org/standard/82075.html) | C99 dodał między innymi deklaracje w pętli `for`; C11 wprowadził między innymi atomiki; C17 zawiera głównie poprawki; najnowsze opublikowane wydanie ISO to C23 / ISO/IEC 9899:2024. |
| C++ | C++98/03, C++11, C++14, C++17, C++20, [C++23](https://www.iso.org/standard/83626.html) | C++11 dodał między innymi lambdy i inteligentne wskaźniki; C++17 dodał między innymi `std::optional`; C++20 dodał koncepty i zakresy; najnowsze opublikowane wydanie ISO to C++23 / ISO/IEC 14882:2024. |

Opcja kompilatora może wskazać wybrany standard, na przykład `-std=c17` dla C albo `-std=c++20` dla C++. Nazwa opcji zależy od używanego kompilatora, a starszy kompilator może nie obsługiwać wszystkich elementów danego standardu.

## Jak zapamiętać różnicę?

C jest językiem proceduralnym z niewielkim zestawem podstawowych mechanizmów i dużą kontrolą nad szczegółami działania programu. C++ zachowuje wiele znanych konstrukcji C, a do tego oferuje klasy, referencje, szablony, wyjątki i rozbudowaną bibliotekę standardową. Można w nim pisać proceduralnie, ale można też korzystać z programowania obiektowego i generycznego.

Najważniejsza praktyczna zasada brzmi: traktuj C i C++ jako osobne języki. Używaj kompilatora i biblioteki odpowiednich dla języka pliku, a przy przenoszeniu kodu sprawdzaj reguły zamiast zakładać, że skoro składnia wygląda znajomo, program zadziała tak samo.
