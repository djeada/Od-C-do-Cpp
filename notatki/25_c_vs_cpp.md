## C vs Cpp
C i C++ to dwa języki programowania, które mają wiele podobieństw, ale również kilka istotnych różnic. 

* C został stworzony w 1970 roku przez Dennisa Ritchiego, zaś C++ został stworzony w 1985 roku przez Bjarnego Stroustrupa. 
* C++ jest (prawie) nadzbiorem C, co oznacza, że większość kodu napisanego w C jest również poprawnym kodem w C++. 
* C++ posiada dodatkowe funkcjonalności, takie jak przeciążanie funkcji, przekazywanie zmiennych przez referencję, inicjalizacja zmiennych przy użyciu nawiasów okrągłych oraz domyślne wartości dla parametrów funkcji.

### Dyrektywy #include

W C i C++, aby załączyć bibliotekę standardową, używamy dyrektywy "#include", jednak w C, przy załączaniu bibliotek standardowych, dodajemy rozszerzenie '.h' po nazwie biblioteki. W C++ nie ma takiej konieczności. Przykłady załączania bibliotek w C:

Przykłady załączania bibliotek w C:

```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```

Przykłady załączania bibliotek w C++:

```c++
#include <iostream>
#include <vector>
#include <string>
```

W C++ również można załączać biblioteki z C przy użyciu dyrektywy "#include" z dodatkiem "c" przed nazwą biblioteki:

```c++
#include <cstdlib>
#include <cstring>
#include <cmath>
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

* Przeciążanie funkcji
* Przekazywanie zmiennych przez referencję
* Inicjalizacja zmiennych przy użyciu nawiasów okrągłych `int x(5);`.
* Domyślne wartości dla parametrów funkcji

### Dlaczego C?

* Minimalizm - C jest językiem, który zawiera tylko to, co jest niezbędne do napisania programu, co ułatwia naukę i zrozumienie języka.
* Kontrola - C pozwala na pełną kontrolę nad systemem operacyjnym oraz sprzętem, co jest szczególnie przydatne przy programowaniu systemów operacyjnych, sterowników, aplikacji embedded, itp.
* Prostota - Mechanizmy języka są niezależne od siebie nawzajem, co pozwala na łatwiejsze zrozumienie i implementację kodu.
* Elastyczność - C posiada małą standardową bibliotekę, co oznacza, że napotkane problemy można rozwiązać samodzielnie, dokładnie tak, jak się chce.

### Dlaczego C++?

* OOP - C++ jest językiem obiektowym, co pozwala na organizację kodu w klasach i obiektach, co jest przydatne przy tworzeniu skomplikowanych programów.
* Abstrakcja - C++ posiada wiele narzędzi do abstrakcji, takich jak funkcje wirtualne, dziedziczenie, itp.
* Dodatkowe funkcjonalności - C++ posiada dodatkowe funkcjonalności, takie jak przeciążanie funkcji, przekazywanie zmiennych przez referencję, inicjalizacja zmiennych przy użyciu nawiasów okrągłych oraz domyślne wartości dla parametrów funkcji, co ułatwia pisanie kodu i zwiększa jego czytelność.
* Wsparcie dla STL - C++ posiada wbudowany standardowy zestaw kontenerów (STL) i algorytmów, co pozwala na łatwiejszą pracę z danymi.
