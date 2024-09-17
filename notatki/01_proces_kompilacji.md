## Proces kompilacji

Proces kompilacji to złożony ciąg etapów, który przekształca kod źródłowy napisany w języku wysokiego poziomu na kod maszynowy zrozumiały dla procesora. Kompilacja zapewnia, że kod jest poprawny pod względem składniowym i semantycznym, a także optymalizuje go pod kątem wydajności. Poniżej szczegółowo omówione są poszczególne etapy kompilacji.

### 1. Etap preprocesowania

Preprocesor jest pierwszym narzędziem, które działa na kodzie źródłowym przed właściwą kompilacją. Jego główne zadania to:

I. **Włączanie zawartości plików nagłówkowych**

Dyrektywy preprocesora takie jak `#include <nazwa_pliku.h>` lub `#include "nazwa_pliku.h"` służą do włączenia zawartości innych plików do bieżącego kodu. Dzięki temu możliwe jest korzystanie z deklaracji funkcji, klas czy zmiennych zdefiniowanych w innych plikach, co promuje modularność i reużywalność kodu.

**Przykład:**

```c
#include <stdio.h> // Załącza standardową bibliotekę wejścia/wyjścia
#include "moje_funkcje.h" // Załącza plik nagłówkowy zdefiniowany przez użytkownika
```

II. **Przetwarzanie makr**

Makra umożliwiają definiowanie stałych, funkcji makro oraz zastępowanie fragmentów kodu. Są one przetwarzane przez preprocesor i nie istnieją w skompilowanym kodzie.

**Przykład stałej:**

```c
#define PI 3.14159
```

**Przykład funkcji makro:**

```c
#define MAX(a,b) ((a) > (b) ? (a) : (b))
```

III. **Warunkowe kompilowanie**

Dyrektywy takie jak `#ifdef`, `#ifndef`, `#if`, `#else`, `#elif`, `#endif` pozwalają na kompilowanie fragmentów kodu tylko wtedy, gdy spełnione są określone warunki. Jest to użyteczne przy kompilacji kodu dla różnych platform lub konfiguracji.

**Przykład:**

```c
#ifdef DEBUG
printf("Wartość zmiennej x: %d\n", x);
#endif
```

IV. **Usuwanie komentarzy**

Preprocesor usuwa wszystkie komentarze (`//` oraz `/* */`), ponieważ nie są one potrzebne w dalszych etapach kompilacji i nie wpływają na działanie programu.

### 2. Analiza kodu źródłowego

Po preprocesowaniu kod trafia do właściwego kompilatora, który przeprowadza analizę w trzech głównych krokach:

I. **Analiza leksykalna (tokenizacja)**

Kod źródłowy jest dzielony na podstawowe jednostki zwane tokenami. Tokeny mogą być słowami kluczowymi (`if`, `while`), identyfikatorami (nazwy zmiennych i funkcji), literałami (np. liczby, łańcuchy znaków), operatorami (`+`, `-`, `*`, `/`) oraz znakami interpunkcyjnymi.

**Przykład:**

Kod:

```c
int suma = a + b;
```

Tokeny:

- `int`
- `suma`
- `=`
- `a`
- `+`
- `b`
- `;`

II. **Analiza składniowa (parsing)**

Na tym etapie kompilator sprawdza, czy sekwencja tokenów tworzy poprawne konstrukcje zgodne z gramatyką języka. Tworzone jest drzewo składniowe (AST - Abstract Syntax Tree), które reprezentuje hierarchiczną strukturę programu.

**Przykład drzewa składniowego dla `int suma = a + b;`:**

```
Deklaracja zmiennej
|
+-- Typ: int
+-- Nazwa: suma
+-- Inicjalizacja
    |
    +-- Wyrażenie arytmetyczne
        |
        +-- Operator: +
        +-- Operand lewy: a
        +-- Operand prawy: b
```

III. **Analiza semantyczna**: 

Sprawdzana jest poprawność semantyczna kodu, czyli czy wyrażenia mają sens w kontekście języka. Obejmuje to:

- Upewnienie się, że operacje są wykonywane na kompatybilnych typach danych (np. nie można dodać liczby całkowitej do wskaźnika bez odpowiedniej konwersji).
- Sprawdzenie, czy wszystkie użyte identyfikatory (zmienne, funkcje) zostały zadeklarowane wcześniej.
- Ustalanie, czy identyfikatory są używane w odpowiednim zakresie (lokalnym czy globalnym).
- Weryfikacja zgodności sygnatur funkcji, liczby i typów argumentów.

**Przykład błędu semantycznego:**

```c
int x = "tekst"; // Przypisanie łańcucha znaków do zmiennej typu int
```

### 3. Generacja plików obiektowych

Po pomyślnym przejściu analiz, kompilator przystępuje do generowania kodu pośredniego:

I. **Generacja kodu pośredniego (Intermediate Representation - IR)**

- Kompilator tworzy kod w wewnętrznym, niezależnym od maszyny formacie, który ułatwia optymalizacje i dalsze przetwarzanie.
- Na poziomie IR kompilator może przeprowadzać różne optymalizacje, takie jak eliminacja martwego kodu, rozwijanie pętli czy optymalizacja dostępu do pamięci.
- IR jest przekształcany w kod maszynowy specyficzny dla docelowej architektury procesora.

II. **Tworzenie plików obiektowych**

Wynikowy kod maszynowy wraz z informacjami o symbolach i sekcjach jest zapisywany w plikach obiektowych (`.o`, `.obj`). Pliki te zawierają również informacje potrzebne do linkowania, takie jak tablice symboli i informacje o relokacji.

**Struktura pliku obiektowego:**

- **Sekcje kodu (`.text`)** zawierają kod wykonywalny programu.
- **Sekcje danych (`.data`, `.bss`)** przechowują zainicjalizowane i niezainicjalizowane zmienne globalne i statyczne.
- **Tablica symboli** to lista wszystkich symboli (funkcji, zmiennych) z ich adresami i atrybutami.
- **Informacje o relokacji** to dane potrzebne do prawidłowego połączenia adresów podczas linkowania.

### 4. Linkowanie

Linker jest narzędziem, które łączy wiele plików obiektowych i bibliotek w jeden plik wykonywalny:

I. **Łączenie symboli**

Linker przegląda tablice symboli wszystkich plików obiektowych, aby zmapować wywołania funkcji i odwołania do zmiennych na ich rzeczywiste definicje.

**Przykład:**

Jeśli funkcja `void funkcja()` jest zadeklarowana w `plik1.o`, a wywoływana w `plik2.o`, linker połączy te referencje.

II. **Rozwiązanie referencji do bibliotek**:

- Kod z bibliotek statycznych (`.a`, `.lib`) jest kopiowany bezpośrednio do pliku wykonywalnego. Powoduje to zwiększenie rozmiaru pliku wykonywalnego, ale nie wymaga obecności bibliotek podczas uruchamiania programu.
- Linker tworzy odwołania do bibliotek dynamicznych (`.so`, `.dll`), które są ładowane do pamięci w czasie uruchamiania programu. Umożliwia to współdzielenie kodu biblioteki między różnymi programami i zmniejsza rozmiar pliku wykonywalnego.

III. **Relokacja**

Linker dostosowuje adresy pamięci w kodzie, aby odzwierciedlić rzeczywiste rozmieszczenie kodu i danych w pamięci.

IV. **Tworzenie pliku wykonywalnego**

Po zakończeniu wszystkich powyższych kroków, linker generuje finalny plik wykonywalny, który zawiera skompilowany kod gotowy do uruchomienia przez system operacyjny.

**Dodatkowe aspekty linkowania:**

- Linker musi rozwiązać zarówno symbole globalne (dostępne dla innych modułów), jak i lokalne (prywatne dla modułu).
- Jeśli dwa moduły definiują symbole o tej samej nazwie, może dojść do konfliktu. Dlatego ważne jest stosowanie unikalnych nazw lub specyfikatorów dostępu.
- Linker tworzy mapę pamięci programu, określając, gdzie w pamięci zostaną umieszczone poszczególne sekcje kodu i danych.

## Dlaczego nie piszemy bezpośrednio w assemblerze?

Choć assembler daje pełną kontrolę nad sprzętem i pozwala na pisanie bardzo wydajnego kodu, programowanie w nim jest niepraktyczne dla większości zastosowań z kilku kluczowych powodów:

- Pisanie kodu w assemblerze jest skomplikowane i czasochłonne. Nawet proste operacje wymagają wielu instrukcji, co sprawia, że tworzenie i utrzymanie dużych aplikacji jest nieefektywne.
- Kod assemblera jest specyficzny dla architektury procesora. Oznacza to, że kod napisany dla jednej architektury (np. x86) nie będzie działał na innej (np. ARM) bez znaczących modyfikacji.
- Kod assemblera jest trudniejszy do zrozumienia i utrzymania. Brakuje w nim abstrakcji dostępnych w językach wysokiego poziomu, co utrudnia zarządzanie złożonymi strukturami danych i logiką biznesową.
- Języki wysokiego poziomu oferują zaawansowane funkcje, takie jak zarządzanie pamięcią, programowanie obiektowe, wyjątki czy generyki, które upraszczają tworzenie skomplikowanych aplikacji.
- Nowoczesne kompilatory potrafią generować bardzo wydajny kod maszynowy, często lepiej zoptymalizowany niż kod pisany ręcznie w assemblerze. Kompilatory korzystają z zaawansowanych technik optymalizacyjnych, analizując kod na poziomie całego programu.
- Pisanie w assemblerze zwiększa ryzyko popełnienia błędów, takich jak błędy zarządzania pamięcią (np. wycieki pamięci, przepełnienia bufora), które mogą prowadzić do luk bezpieczeństwa.
- W środowisku zespołowym łatwiej jest współpracować nad kodem napisanym w języku wysokiego poziomu, który jest bardziej czytelny i zrozumiały dla większej liczby programistów.

**Przykład:**

Dodanie dwóch liczb w C:

```c
int a = 5;
int b = 10;
int c = a + b;
```

Dodanie dwóch liczb w Asemblerze (dla architektury x86):

```assembly
section .data
    a dd 5        ; zmienna a = 5
    b dd 10       ; zmienna b = 10
    c dd 0        ; zmienna c = 0, tutaj zostanie zapisany wynik

section .text
    global _start

_start:
    mov eax, [a]   ; załaduj wartość zmiennej a do rejestru eax
    add eax, [b]   ; dodaj wartość zmiennej b do eax
    mov [c], eax   ; zapisz wynik do zmiennej c

    ; zakończenie programu (system call exit)
    mov eax, 1     ; kod systemowy dla exit
    xor ebx, ebx   ; kod powrotu 0
    int 0x80       ; wywołanie systemu
```


**Zastosowania assemblera:**

- Niskopoziomowe operacje na sprzęcie, sterowniki urządzeń czy systemy wbudowane o ograniczonych zasobach.
- W niektórych przypadkach kluczowe fragmenty kodu wymagają ręcznej optymalizacji.
- Nauka działania procesora, architektury komputerów i systemów operacyjnych.

## Kompilacja z wiersza poleceń

Kompilacja z wiersza poleceń daje programiście pełną kontrolę nad procesem kompilacji i pozwala na dostosowanie opcji kompilatora do specyficznych potrzeb projektu.

### Kompilacja kodu w C przy użyciu `gcc`

`gcc` jest potężnym narzędziem, które oferuje wiele opcji:

Podstawowa kompilacja:

```bash
gcc main.c -o program
```

Opcje kompilatora:

I. **Standard języka (`-std`)**: Określa, który standard języka C ma być użyty (np. `c89`, `c99`, `c11`).

```bash
gcc -std=c11 main.c -o program
```

II. **Ostrzeżenia (`-Wall`, `-Wextra`, `-Werror`)**:

- `-Wall`: Włącza podstawowy zestaw ostrzeżeń.
- `-Wextra`: Włącza dodatkowe ostrzeżenia.
- `-Werror`: Traktuje ostrzeżenia jako błędy.

**Przykład:**

```bash
gcc -Wall -Wextra -Werror main.c -o program
```

III. **Optymalizacje (`-O`, `-O1`, `-O2`, `-O3`, `-Os`)**:

- `-O1`: Podstawowe optymalizacje.
- `-O2`: Zalecany poziom optymalizacji dla większości programów.
- `-O3`: Maksymalne optymalizacje (może zwiększyć rozmiar kodu).
- `-Os`: Optymalizacja pod kątem rozmiaru kodu.

**Przykład:**

```bash
gcc -O2 main.c -o program
```

IV. **Debugowanie (`-g`)**: Dodaje informacje debugowania, które są niezbędne podczas używania debugerów takich jak `gdb`.

**Przykład:**

```bash
gcc -g main.c -o program
```

V. **Definiowanie makr (`-D`)**: Pozwala na definiowanie makr z poziomu kompilacji.

**Przykład:**

```bash
gcc -DDEBUG main.c -o program
```

VI. **Ścieżki do plików nagłówkowych (`-I`)**: Dodaje dodatkowe ścieżki, w których kompilator szuka plików nagłówkowych.

**Przykład:**

```bash
gcc -I./include main.c -o program
```

VII. **Linkowanie z bibliotekami (`-l`, `-L`)**:

- `-l`: Określa nazwę biblioteki do linkowania (np. `-lm` dla biblioteki matematycznej).
- `-L`: Dodaje ścieżkę do poszukiwania bibliotek.

**Przykład:**

```bash
gcc main.c -o program -L./lib -lmojabiblioteka
```

**Kompilacja wielu plików:**

Jeśli projekt składa się z wielu plików źródłowych:

```bash
gcc plik1.c plik2.c plik3.c -o program
```

**Kompilacja etapowa:**

I. Kompilacja do plików obiektowych:
   
```bash
gcc -c plik1.c -o plik1.o
gcc -c plik2.c -o plik2.o
```

II. Linkowanie plików obiektowych:

```bash
gcc plik1.o plik2.o -o program
```

### Kompilacja programu w C++ przy użyciu `g++`

`g++` działa podobnie do `gcc`, ale jest przeznaczony dla języka C++.

Podstawowa kompilacja:

```bash
g++ main.cpp -o program
```

Opcje kompilatora:

I. **Standard języka (`-std`)**: Dostępne standardy to m.in. `c++98`, `c++03`, `c++11`, `c++14`, `c++17`, `c++20`.

```bash
g++ -std=c++17 main.cpp -o program
```

II. **Ostrzeżenia i rygorystyczność (`-Wall`, `-Wextra`, `-pedantic`)**:

Przykład:

```bash
g++ -Wall -Wextra -pedantic main.cpp -o program
```

III. **Optymalizacje, debugowanie, definiowanie makr, ścieżki do plików nagłówkowych i bibliotek**: Działają analogicznie jak w `gcc`.

Przykład z wieloma opcjami:

```bash
g++ -std=c++20 -O2 -Wall -Wextra -g -I./include -L./lib -lmojabiblioteka main.cpp -o program
```

### Formatowanie kodu przy użyciu `clang-format`

`clang-format` to narzędzie do automatycznego formatowania kodu zgodnie z określonym stylem. Dzięki temu kod jest spójny i czytelny dla wszystkich członków zespołu.

Konfiguracja stylu:

- Plik konfiguracyjny `.clang-format` można umieścić w katalogu głównym projektu.
- Styl można określić jako jeden z predefiniowanych (`LLVM`, `Google`, `Chromium`, `Mozilla`, `WebKit`) lub zdefiniować własny.

Przykład pliku `.clang-format`:

```yaml
BasedOnStyle: LLVM
IndentWidth: 4
ColumnLimit: 100
```

Formatowanie plików:

I. Formatowanie pojedynczego pliku:

```bash
clang-format -i plik.cpp
```

II. Automatyczne formatowanie wszystkich plików w projekcie:
  
```bash
find . -regex '.*\.\(cpp\|hpp\|c\|h\)' -exec clang-format -style=file -i {} \;
```

### Dostosowywanie opcji kompilacji

I. **Profilowanie wydajności (`-pg`):**

Dodaje informacje potrzebne do profilowania programu narzędziami takimi jak `gprof`.

```bash
gcc -pg main.c -o program
```

II. **Analiza statyczna:**

Narzędzia takie jak `cppcheck` pozwalają na statyczną analizę kodu w celu wykrycia potencjalnych błędów.

Przykład:

```bash
cppcheck --enable=all --inconclusive --std=c11 main.c
```

III. **Tworzenie bibliotek:**

**Biblioteki statyczne (`.a`):**

1. Kompilacja plików obiektowych:

```bash
gcc -c plik1.c -o plik1.o
gcc -c plik2.c -o plik2.o
```

2. Utworzenie biblioteki:

```bash
ar rcs libmojabiblioteka.a plik1.o plik2.o
```

3. Użycie biblioteki podczas kompilacji programu:

```bash
gcc main.c -L. -lmojabiblioteka -o program
```

**Biblioteki dynamiczne (`.so`):**

1. Kompilacja z opcją tworzenia kodu współdzielonego:

```bash
gcc -fPIC -c plik1.c -o plik1.o
gcc -fPIC -c plik2.c -o plik2.o
```

2. Utworzenie biblioteki:

```bash
gcc -shared -o libmojabiblioteka.so plik1.o plik2.o
```

3. Użycie biblioteki podczas kompilacji programu:

```bash
gcc main.c -L. -lmojabiblioteka -o program
```

4. Ustawienie zmiennej środowiskowej `LD_LIBRARY_PATH`:

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.
```

**Korzystanie z `make` i `Makefile`:**

Automatyzacja procesu kompilacji przy użyciu narzędzia `make`.

Przykład prostego `Makefile`:

```make
CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -O2
LDFLAGS=

SOURCES=main.c plik1.c plik2.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=program

all: $(TARGET)

$(TARGET): $(OBJECTS)
  $(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
  $(CC) $(CFLAGS) -c -o $@ $<

clean:
  rm -f $(OBJECTS) $(TARGET)
```

Uruchomienie kompilacji:
  
```bash
make
```

Usunięcie plików obiektowych i wykonywalnych:

```bash
make clean
```
