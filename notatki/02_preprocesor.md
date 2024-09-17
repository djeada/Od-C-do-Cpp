## Preprocesor

Preprocesor to specjalne narzędzie, które działa na kodzie źródłowym przed właściwym procesem kompilacji. W kontekście języków programowania takich jak C i C++, preprocesor jest integralną częścią kompilatora, która przekształca kod źródłowy na podstawie specjalnych dyrektyw. Dyrektywy preprocesora rozpoczynają się od znaku `#` i są przetwarzane przed analizą składniową przez kompilator. Dzięki temu programista może modyfikować kod źródłowy w sposób dynamiczny, kontrolować kompilację warunkową, definiować makra i zarządzać załączaniem plików nagłówkowych.

Dyrektywy preprocesora mogą być umieszczone w dowolnym miejscu w kodzie źródłowym, jednak dla zachowania czytelności i dobrej organizacji kodu zazwyczaj umieszcza się je na początku pliku lub przed fragmentami kodu, których dotyczą.

### Funkcje preprocesora

Dyrektywy preprocesora pełnią różne funkcje, w tym:

### 1. Załączanie bibliotek

Dyrektywa `#include` służy do włączania zawartości innych plików do naszego kodu źródłowego. Jest to kluczowe dla modularności kodu oraz ponownego wykorzystania istniejących funkcji i definicji. Załączane pliki mogą zawierać deklaracje funkcji, klasy, zmienne globalne oraz inne dyrektywy preprocesora.

Są dwa sposoby użycia dyrektywy `#include`:

**Załączanie bibliotek standardowych**:

```c++
#include <iostream>
```

Gdy używamy nawiasów ostrokątnych `< >`, preprocesor szuka pliku nagłówkowego `iostream` w standardowych katalogach kompilatora przeznaczonych na pliki nagłówkowe biblioteki standardowej. W tym przypadku dołączamy standardową bibliotekę wejścia/wyjścia, która zawiera deklaracje dla strumieni takich jak `std::cin`, `std::cout`.

**Załączanie plików lokalnych**:

```c++
#include "moj_plik.h"
```

Gdy używamy cudzysłowów `" "`, preprocesor najpierw szuka pliku `moj_plik.h` w bieżącym katalogu (czyli tam, gdzie znajduje się plik źródłowy), a następnie w standardowych katalogach kompilatora. Ten sposób jest używany do załączania własnych plików nagłówkowych projektu.

**Przykład działania:**

Załóżmy, że mamy plik `funkcje.h` z deklaracją funkcji:

```c++
// funkcje.h
void wypisz_powitanie();
```

I plik `funkcje.cpp` z definicją funkcji:

```c++
// funkcje.cpp
#include "funkcje.h"
#include <iostream>

void wypisz_powitanie() {
    std::cout << "Witaj, świecie!" << std::endl;
}
```

W pliku `main.cpp` możemy załączyć `funkcje.h` i użyć funkcji `wypisz_powitanie()`:

```c++
// main.cpp
#include "funkcje.h"

int main() {
    wypisz_powitanie();
    return 0;
}
```

Dzięki dyrektywie `#include` nasz kod jest czytelny i dobrze zorganizowany.

### 2. Definiowanie stałych i makr

Dyrektywa `#define` pozwala na tworzenie makr preprocesora, które mogą być używane do zastępowania tekstu w kodzie źródłowym. Makra mogą być prostymi stałymi, które zastępują określony identyfikator określoną wartością, lub mogą być bardziej złożone i przyjmować argumenty, działając podobnie do funkcji.

**Definiowanie stałych tekstowych lub liczbowych**:

```c++
#define PI 3.141592653589793
#define NAZWA "Jan Kowalski"
```

Tutaj `PI` zostanie zastąpione przez wartość `3.141592653589793` wszędzie tam, gdzie występuje w kodzie, a `NAZWA` przez tekst `"Jan Kowalski"`.

**Uwaga:** Makra nie są ograniczone typami danych i nie są sprawdzane pod względem typów przez kompilator, co może prowadzić do błędów, jeśli nie są używane ostrożnie.

**Definiowanie makr z parametrami (makra funkcji)**:

```c++
#define MAX(x, y) ((x) > (y) ? (x) : (y))
```

To makro porównuje dwie wartości i zwraca większą z nich. Należy zwrócić uwagę na umieszczanie parametrów i całego wyrażenia w nawiasach, aby uniknąć błędów wynikających z nieoczekiwanej kolejności wykonywania operacji.

**Przykład problemu z makrami bez nawiasów:**

```c++
#define SQR(x) x * x

int a = 5;
int b = SQR(a + 1); // Oczekiwany wynik: 36, faktyczny wynik: 11
```

Makro zostanie zastąpione jako:

```c++
int b = a + 1 * a + 1;
```

Co daje:

```c++
int b = a + (1 * a) + 1;
```

Czyli dla `a = 5`, `b = 5 + 5 + 1 = 11`.

Poprawne makro powinno być zdefiniowane jako:

```c++
#define SQR(x) ((x) * (x))
```

### 3. Warunkowa kompilacja

Dyrektywy preprocesora pozwalają na kompilację określonych fragmentów kodu w zależności od spełnienia określonych warunków. Jest to niezwykle użyteczne w przypadku pisania kodu przenośnego, który musi działać na różnych platformach, lub włączania dodatkowych funkcji podczas debugowania.

**Dyrektywy warunkowe**:

- `#if` ... `#endif`
- `#ifdef` ... `#endif`
- `#ifndef` ... `#endif`
- `#else`
- `#elif`

**Przykład użycia `#ifdef` i `#ifndef`:**

```c++
#ifndef NDEBUG
#define DEBUG
#endif

#ifdef DEBUG
std::cout << "Debugowanie włączone" << std::endl;
#endif
```

W powyższym przykładzie, jeśli symbol `NDEBUG` nie jest zdefiniowany, zostanie zdefiniowany symbol `DEBUG`, a następnie kod wewnątrz `#ifdef DEBUG` zostanie skompilowany.

**Użycie `#if` i wyrażeń logicznych:**

```c++
#define WERSJA 2

#if WERSJA == 1
// Kod dla wersji 1
#elif WERSJA == 2
// Kod dla wersji 2
#else
// Kod dla innych wersji
#endif
```

Preprocesor może wykonywać proste operacje arytmetyczne i logiczne na wartościach zdefiniowanych przez `#define`.

**Kompilacja warunkowa w zależności od platformy:**

```c++
#ifdef _WIN32
// Kod specyficzny dla Windows
#elif __linux__
// Kod specyficzny dla Linuxa
#elif __APPLE__
// Kod specyficzny dla macOS
#else
// Kod dla innych platform
#endif
```

Symbole takie jak `_WIN32`, `__linux__`, `__APPLE__` są predefiniowane przez kompilatory i pozwalają na pisanie przenośnego kodu.

### 4. Usuwanie definicji

Dyrektywa `#undef` służy do usuwania wcześniej zdefiniowanych makr lub stałych. Jest to przydatne, gdy chcemy redefiniować makro lub upewnić się, że dane makro nie jest już aktywne w dalszej części kodu.

**Przykład użycia `#undef`:**

```c++
#define BUFOR 1024

// Kod używający BUFOR

#undef BUFOR

#define BUFOR 2048

// Kod używający nowej wartości BUFOR
```

W tym przypadku najpierw definiujemy `BUFOR` jako `1024`, następnie go usuwamy za pomocą `#undef`, a potem redefiniujemy jako `2048`.

**Uwaga:** Należy być ostrożnym z używaniem `#undef`, aby nie wprowadzić niejasności w kodzie.

### 5. Inne dyrektywy preprocesora

**Dyrektywa `#pragma`**:

Dyrektywa `#pragma` jest używana do przekazywania specjalnych instrukcji do kompilatora. Konkretne znaczenie `#pragma` może się różnić w zależności od kompilatora, dlatego jest ona często używana w sposób przenośny z rozwagą.

**Przykład:**

```c++
#pragma once
```

Dyrektywa `#pragma once` zapewnia, że plik nagłówkowy zostanie dołączony tylko raz podczas kompilacji, nawet jeśli zostanie załączony wielokrotnie w różnych miejscach. Jest to alternatywa dla tradycyjnych strażników nagłówków (`include guards`):

```c++
#ifndef NAZWA_PLIKU_H
#define NAZWA_PLIKU_H

// Zawartość pliku nagłówkowego

#endif
```

**Dyrektywa `#error`**:

Dyrektywa `#error` pozwala na wygenerowanie błędu kompilacji z określonym komunikatem. Jest to użyteczne do wykrywania niepożądanych warunków podczas preprocesowania.

**Przykład:**

```c++
#ifndef WERSJA
#error "Makro WERSJA musi być zdefiniowane"
#endif
```

Jeśli `WERSJA` nie jest zdefiniowane, kompilacja zostanie przerwana z komunikatem błędu.

**Dyrektywa `#warning`** (w niektórych kompilatorach):

Niektóre kompilatory obsługują dyrektywę `#warning`, która generuje ostrzeżenie podczas kompilacji.

```c++
#warning "Ta funkcja jest przestarzała"
```

To ostrzeżenie informuje programistę o potencjalnych problemach.

**Predefiniowane makra preprocesora:**

Preprocesor definiuje również kilka standardowych makr, które mogą być używane w kodzie:

- `__FILE__` – nazwa bieżącego pliku źródłowego
- `__LINE__` – numer linii w bieżącym pliku źródłowym
- `__DATE__` – data kompilacji
- `__TIME__` – czas kompilacji
- `__func__` – nazwa bieżącej funkcji (C99 i nowsze)

**Przykład użycia:**

```c++
std::cout << "Błąd w pliku " << __FILE__ << " w linii " << __LINE__ << std::endl;
```

Ta linia kodu wypisze informację o miejscu wystąpienia błędu, co jest pomocne podczas debugowania.
