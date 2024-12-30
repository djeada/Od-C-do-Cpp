## Preprocesor

Preprocesor to specjalne narzędzie, które działa na kodzie źródłowym przed właściwym procesem kompilacji. W kontekście języków programowania takich jak C i C++, preprocesor jest integralną częścią kompilatora, która przekształca kod źródłowy na podstawie specjalnych dyrektyw. Dyrektywy preprocesora rozpoczynają się od znaku `#` i są przetwarzane przed analizą składniową przez kompilator. Dzięki temu programista może modyfikować kod źródłowy w sposób dynamiczny, kontrolować kompilację warunkową, definiować makra i zarządzać załączaniem plików nagłówkowych. Preprocesor nie jest samodzielnym narzędziem działającym w pełnej izolacji – większość nowoczesnych kompilatorów uruchamia go automatycznie jako pierwszy etap procesu kompilacji, co z punktu widzenia programisty wygląda, jakby było zintegrowane w jednym pakiecie.

Dyrektywy preprocesora mogą być umieszczone w dowolnym miejscu w kodzie źródłowym, jednak dla zachowania czytelności i dobrej organizacji kodu zazwyczaj umieszcza się je na początku pliku lub przed fragmentami kodu, których dotyczą. W dużych projektach często spotyka się pliki nagłówkowe zawierające tylko makra i dyrektywy warunkowe, co sprzyja modularności i łatwiejszemu zarządzaniu konfiguracją kompilacji.

### Funkcje preprocesora

Dyrektywy preprocesora pełnią różne funkcje, w tym:

#### 1. Załączanie bibliotek

Dyrektywa `#include` służy do włączania zawartości innych plików do naszego kodu źródłowego. Jest to kluczowe dla modularności kodu oraz ponownego wykorzystania istniejących funkcji i definicji. Załączane pliki mogą zawierać deklaracje funkcji, klasy, zmienne globalne oraz inne dyrektywy preprocesora. W efekcie, gdy plik nagłówkowy jest załączany w wielu miejscach, unikamy powtarzalności tych samych definicji – wystarczy zmodyfikować kod raz w pliku nagłówkowym, a wszystkie miejsca, w których go dołączamy, otrzymują nowe definicje.

Są dwa sposoby użycia dyrektywy `#include`:

**Załączanie bibliotek standardowych**:

```c++
#include <iostream>
```

Gdy używamy nawiasów ostrokątnych `< >`, preprocesor szuka pliku nagłówkowego `iostream` w standardowych katalogach kompilatora przeznaczonych na pliki nagłówkowe biblioteki standardowej. W tym przypadku dołączamy standardową bibliotekę wejścia/wyjścia, która zawiera deklaracje dla strumieni takich jak `std::cin` i `std::cout`. Po włączeniu biblioteki standardowej zyskujemy dostęp do predefiniowanych klas, funkcji oraz innych elementów niezbędnych do podstawowej funkcjonalności języka.

**Załączanie plików lokalnych**:

```c++
#include "moj_plik.h"
```

Gdy używamy cudzysłowów `" "`, preprocesor najpierw szuka pliku `moj_plik.h` w bieżącym katalogu (czyli tam, gdzie znajduje się plik źródłowy), a następnie w standardowych katalogach kompilatora. Ten sposób jest używany do załączania własnych plików nagłówkowych projektu. Dzięki temu programista może tworzyć wiele małych, wyspecjalizowanych plików `.h`, które zawierają tylko deklaracje potrzebnych funkcji, klas czy zmiennych, i rozdzielać logikę na mniejsze moduły.

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

Dzięki dyrektywie `#include` nasz kod jest czytelny i dobrze zorganizowany. Inaczej musielibyśmy wielokrotnie wstawiać definicję funkcji czy deklaracje zmiennych, co skutkowałoby bałaganem i trudnościami w utrzymaniu projektu.

#### 2. Definiowanie stałych i makr

Dyrektywa `#define` pozwala na tworzenie makr preprocesora, które mogą być używane do zastępowania tekstu w kodzie źródłowym. Makra mogą być prostymi stałymi, które zastępują określony identyfikator określoną wartością, lub mogą być bardziej złożone i przyjmować argumenty, działając podobnie do funkcji. Mechanizm ten bywa przydatny do definiowania nazw skrótowych dla długich, powtarzających się wyrażeń lub wstawiania stałych, które nie mają narzuconego konkretnego typu (np. liczby czy łańcuchy znaków).

**Definiowanie stałych tekstowych lub liczbowych**:

```c++
#define PI 3.141592653589793
#define NAZWA "Jan Kowalski"
```

Tutaj `PI` zostanie zastąpione przez wartość `3.141592653589793` wszędzie tam, gdzie występuje w kodzie, a `NAZWA` przez tekst `"Jan Kowalski"`. W praktyce takie stałe często definiuje się jako `constexpr` lub `const` w C++, dzięki czemu zyskujemy lepszą kontrolę nad typem, ale makra wciąż bywają przydatne w kodzie pisanym w stylu C lub w sytuacjach, gdy zależy nam na szybkim „tekstem za tekst”.

**Uwaga:** Makra nie są ograniczone typami danych i nie są sprawdzane pod względem typów przez kompilator, co może prowadzić do błędów, jeśli nie są używane ostrożnie. Kompilator po prostu zastępuje tekst. Dla nowoczesnych projektów w C++ bardziej zalecane jest stosowanie stałych (`const` lub `constexpr`) oraz szablonów, aby zapewnić lepszą kontrolę typów.

**Definiowanie makr z parametrami (makra funkcji)**:

```c++
#define MAX(x, y) ((x) > (y) ? (x) : (y))
```

To makro porównuje dwie wartości i zwraca większą z nich. Należy zwrócić uwagę na umieszczanie parametrów i całego wyrażenia w nawiasach, aby uniknąć błędów wynikających z nieoczekiwanej kolejności wykonywania operacji i minimalizować ryzyko rozbudowanych wyrażeń wstawianych bez kontroli. 

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

Dzięki temu każda wstawka `SQR(a + 1)` zostanie przetworzona jako `((a + 1) * (a + 1))`.

#### 3. Warunkowa kompilacja

Dyrektywy preprocesora pozwalają na kompilację określonych fragmentów kodu w zależności od spełnienia określonych warunków. Jest to niezwykle użyteczne w przypadku pisania kodu przenośnego, który musi działać na różnych platformach, lub włączania dodatkowych funkcji podczas debugowania. Kompilacja warunkowa sprawdza się również, gdy zależnie od środowiska czy wersji biblioteki pewne fragmenty muszą zostać włączone bądź wyłączone.

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

W powyższym przykładzie, jeśli symbol `NDEBUG` nie jest zdefiniowany, zostanie zdefiniowany symbol `DEBUG`, a następnie kod wewnątrz `#ifdef DEBUG` zostanie skompilowany. W efekcie programista może włączyć lub wyłączyć komunikaty debugowania, definiując bądź nie definiując `NDEBUG`.

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

Preprocesor może wykonywać proste operacje arytmetyczne i logiczne na wartościach zdefiniowanych przez `#define`. Na przykład, jeśli `WERSJA` wynosi 2, zostanie skompilowany kod tylko z sekcji `#elif WERSJA == 2`.

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

Symbole takie jak `_WIN32`, `__linux__`, `__APPLE__` są predefiniowane przez kompilatory i pozwalają na pisanie przenośnego kodu. Jest to szczególnie przydatne w aplikacjach wieloplatformowych, gdy pewne funkcje czy biblioteki są dostępne tylko na danej platformie.

#### 4. Usuwanie definicji

Dyrektywa `#undef` służy do usuwania wcześniej zdefiniowanych makr lub stałych. Jest to przydatne, gdy chcemy redefiniować makro lub upewnić się, że dane makro nie jest już aktywne w dalszej części kodu. W niektórych sytuacjach może być wymagane, żeby o to samo makro nie „konkurowały” różne sekcje kodu.

**Przykład użycia `#undef`:**

```c++
#define BUFOR 1024

// Kod używający BUFOR

#undef BUFOR

#define BUFOR 2048

// Kod używający nowej wartości BUFOR
```

W tym przypadku najpierw definiujemy `BUFOR` jako `1024`, następnie go usuwamy za pomocą `#undef`, a potem redefiniujemy jako `2048`. Zmiana wartości makra w trakcie procesu preprocesora bywa rzadko stosowana, jednak w specyficznych przypadkach potrafi być przydatna.

**Uwaga:** Należy być ostrożnym z używaniem `#undef`, aby nie wprowadzić niejasności w kodzie, szczególnie w dużych projektach, gdzie wiele modułów może oczekiwać określonej wartości makra.

### 5. Inne dyrektywy preprocesora

**Dyrektywa `#pragma`**:

Dyrektywa `#pragma` jest używana do przekazywania specjalnych instrukcji do kompilatora. Konkretne znaczenie `#pragma` może się różnić w zależności od kompilatora, dlatego jest ona często używana w sposób przenośny z rozwagą. Niektóre kompilatory mogą ignorować nieznane `#pragma`, inne mogą generować ostrzeżenia. 

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

W nowoczesnym C++ i w większości popularnych kompilatorów `#pragma once` jest bardzo szeroko wspierana i pozwala uprościć pliki nagłówkowe.

**Dyrektywa `#error`**:

Dyrektywa `#error` pozwala na wygenerowanie błędu kompilacji z określonym komunikatem. Jest to użyteczne do wykrywania niepożądanych warunków podczas preprocesowania. Jeśli podczas kompilacji okaże się, że mamy niewłaściwą konfigurację lub kluczowe makro nie jest zdefiniowane, można wywołać `#error` z komunikatem, co przerwie kompilację i zwróci uwagę programisty na problem.

**Przykład:**

```c++
#ifndef WERSJA
#error "Makro WERSJA musi być zdefiniowane"
#endif
```

Jeśli `WERSJA` nie jest zdefiniowane, kompilacja zostanie przerwana z komunikatem błędu. Jest to skuteczny sposób na upewnienie się, że środowisko kompilacji zostało prawidłowo skonfigurowane.

**Dyrektywa `#warning`** (w niektórych kompilatorach):

Niektóre kompilatory obsługują dyrektywę `#warning`, która generuje ostrzeżenie podczas kompilacji. Jest to wygodne, gdy chcemy przekazać informację dla innych programistów (lub samego siebie w przyszłości), że pewna funkcjonalność jest eksperymentalna, przestarzała lub wymaga dodatkowej uwagi.

```c++
#warning "Ta funkcja jest przestarzała"
```

To ostrzeżenie informuje programistę o potencjalnych problemach, ale nie przerywa kompilacji.

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

Ta linia kodu wypisze informację o miejscu wystąpienia błędu, co jest pomocne podczas debugowania. W połączeniu ze stosowaniem makr warunkowych można tworzyć inteligentne mechanizmy logowania czy śledzenia działania programu (tzw. logging lub tracing), które w finalnej wersji można wyłączyć, by nie spowalniać działania aplikacji.
