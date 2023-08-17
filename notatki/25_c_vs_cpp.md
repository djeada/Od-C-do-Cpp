## C vs C++

C i C++ to dwa języki programowania, które mają wiele wspólnego, ale różnią się w kluczowych aspektach, wpływając na ich zastosowanie, wydajność i składnię.

### Historia

* **C**: Język C został stworzony w 1970 roku przez Dennisa Ritchiego w Bell Labs jako rozwinięcie języka B. Zaprojektowany był jako język do programowania systemów, a jego popularność rosła dzięki Unixowi, który został napisany w C.

* **C++**: Język C++ został stworzony w latach 80. XX wieku przez Bjarnego Stroustrupa, również w Bell Labs. C++ początkowo był nazywany "C z klasami" i miał na celu połączenie języka C z koncepcjami programowania obiektowego. Przez lata ewoluował, dodając wiele nowych funkcji, takich jak szablony czy wyjątki.

### Zgodność

* **C jako podstawa C++**: C++ jest uważany za rozszerzenie języka C, co oznacza, że większość kodu napisanego w C jest (teoretycznie) poprawnym kodem w C++. Jednakże ze względu na pewne subtelne różnice w zachowaniu i semantyce, nie wszystkie programy C działają poprawnie w C++ bez modyfikacji.

* **Rozszerzenia C++**:  C++ wprowadza wiele nowych funkcji i koncepcji, takich jak klasy, przeciążanie funkcji, przekazywanie zmiennych przez referencję, szablony, przestrzenie nazw i wiele innych.

Warto zauważyć, że oba języki, chociaż mają wiele wspólnego, są optymalizowane do różnych zastosowań. C jest często preferowany w programowaniu niskopoziomowym, takim jak systemy wbudowane, ze względu na jego prostotę i wydajność. C++ jest z kolei bardziej odpowiedni do większych aplikacji i systemów, które korzystają z jego bogatych funkcji i koncepcji programowania obiektowego.

### Dyrektywy #include

W obu językach, aby załączyć bibliotekę standardową, używamy dyrektywy `#include`. 

* W **C**, przy załączaniu bibliotek standardowych, zazwyczaj dodajemy rozszerzenie '.h' po nazwie biblioteki:

    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    ```

* W **C++**, standardowe biblioteki C++ są dostępne bez rozszerzenia ".h", a biblioteki C są dostępne z prefiksem "c":

    ```cpp
    #include <iostream>
    #include <vector>
    #include <string>
    // Biblioteki z C w C++
    #include <cstdio>
    #include <cstdlib>
    #include <cstring>
    ```

### Słowa kluczowe

Oba języki posiadają wiele wspólnych słów kluczowych takich jak:

```c++
auto
break
case
char
const
continue
default
do
double
else
enum
extern
float
for
goto
if
int
long
register
return
short
signed
sizeof
static
struct
switch
typedef
union
unsigned
void
volatile
while
```

C++ posiada również kilka słów kluczowych, które nie są dostępne w C, takich jak:

```c++
static_cast
dynamic_cast
const_cast
reinterpret_cast
bool
explicit
namespace
protected
throw
using
catch
false
new
public
true
virtual
class
friend
operator
template
try
delete
inline
private
this
typename
```

### Funkcjonalności dostępne jedynie w C++

1. **Programowanie Obiektowe:** W przeciwieństwie do języka C, który jest językiem proceduralnym, C++ oferuje pełne wsparcie dla programowania obiektowego. Pozwala to na definiowanie klas, dziedziczenie, polimorfizm oraz enkapsulację.

2. **Standardowa Biblioteka C++ (STL):** Biblioteka ta dostarcza zestaw gotowych do użycia struktur danych (np. wektory, listy, mapy) oraz algorytmów. STL znacząco przyspiesza rozwój aplikacji dzięki reużywalnym komponentom.

3. **Zarządzanie Pamięcią:** Zarówno C, jak i C++ wymagają świadomego zarządzania pamięcią. Niemniej jednak, C++ oferuje dodatkowe narzędzia takie jak konstruktory, destruktory oraz inteligentne wskaźniki, które pomagają w zarządzaniu cyklem życia obiektów.

4. **Mechanizm Wyjątków:** W C++ dostępny jest zaawansowany mechanizm wyjątków do obsługi błędów. Dzięki niemu można definiować bloki `try`, `catch` i `throw` do przechwytywania i obsługi wyjątków. W C obsługa błędów opiera się głównie na wartościach zwracanych przez funkcje i globalnej zmiennej `errno`.

5. **Przeciążanie Funkcji:** C++ pozwala na definiowanie wielu funkcji o tej samej nazwie, ale o różnych sygnaturach. To oznacza, że można tworzyć różne wersje funkcji do różnych typów danych.

6. **Przekazywanie przez Referencję:** W C++ istnieje możliwość przekazywania zmiennych do funkcji przez referencję, co pozwala na modyfikację oryginalnej zmiennej bez konieczności używania wskaźników.

7. **Inicjalizacja Zmiennych:** C++ oferuje różne sposoby inicjalizacji zmiennych, w tym przy użyciu nawiasów okrągłych, np. `int x(5);`.

8. **Domyślne Wartości Parametrów:** W C++ można definiować domyślne wartości dla parametrów funkcji, co pozwala na pominięcie niektórych argumentów podczas wywołania funkcji, jeśli chcemy skorzystać z wartości domyślnych.

### Dlaczego C?

* **Minimalizm:** Język C został zaprojektowany z myślą o minimalizmie. Składa się z niewielkiej liczby kluczowych słów i prostych struktur, co czyni go idealnym narzędziem do nauki podstaw programowania i zrozumienia, jak działa komputer na niższym poziomie.
  
* **Kontrola:** C daje programistom bezpośredni dostęp do niskopoziomowych zasobów komputera, takich jak pamięć i rejestry procesora. To sprawia, że język jest nieoceniony w przypadku tworzenia systemów operacyjnych, sterowników urządzeń czy aplikacji dla systemów wbudowanych.

* **Prostota:** Mechanizmy języka są jasno zdefiniowane i niezależne od siebie, co pozwala na łatwiejsze debugowanie i utrzymanie kodu.

* **Elastyczność:** Brak rozbudowanej standardowej biblioteki może wydawać się wadą, ale dla wielu jest zaletą. Programiści mają pełną kontrolę nad tym, jakie narzędzia i biblioteki chcą wykorzystać, co daje im swobodę w projektowaniu własnych rozwiązań.

* **Przenośność:** Kod napisany w C można łatwo przenosić między różnymi platformami i architekturami sprzętowymi dzięki standardowi ANSI C.

### Dlaczego C++?

* **OOP:** Wprowadzenie paradygmatu programowania obiektowego sprawia, że projektowanie, implementacja i testowanie skomplikowanych systemów staje się bardziej zarządzalne. Klasy, dziedziczenie i polimorfizm to tylko niektóre z funkcji, które przyczyniają się do modularności i reużywalności kodu.

* **Abstrakcja:** C++ pozwala na tworzenie bardziej zaawansowanych poziomów abstrakcji, co ułatwia modelowanie rzeczywistych problemów i ukrywanie niepotrzebnych szczegółów implementacyjnych.

* **Rozbudowane funkcjonalności:** C++ wnosi wiele udogodnień i funkcji, które przyspieszają pisanie kodu i zwiększają jego czytelność, takich jak przeciążanie funkcji, referencje, inicjalizacja listowa czy domyślne argumenty funkcji.

* **Wsparcie dla STL:** Standardowa biblioteka szablonów (STL) oferuje bogaty zestaw gotowych do użycia struktur danych i algorytmów. Kontenery takie jak `vector`, `list` czy `map` oraz algorytmy sortujące czy wyszukujące znacząco przyspieszają rozwój aplikacji.

* **Zgodność z C:** C++ zachowuje dużą zgodność wsteczną z językiem C, co oznacza, że większość kodów napisanych w C można skompilować w kompilatorze C++ z niewielkimi modyfikacjami.

* **Biblioteki i frameworki:** C++ posiada bogaty ekosystem bibliotek i frameworków, które pomagają w tworzeniu aplikacji od grafiki komputerowej po rozwój gier czy systemy baz danych.
