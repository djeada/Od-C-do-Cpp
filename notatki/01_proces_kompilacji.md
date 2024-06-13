## Proces kompilacji

Kompilator to narzędzie przekształcające kod źródłowy napisany w danym języku programowania na kod maszynowy lub inny język niskiego poziomu, który może być bezpośrednio wykonany przez procesor. Proces ten składa się z kilku kluczowych etapów, z których każdy ma określoną funkcję i zadania do wykonania.

### 1. Etap preprocesowania
Na tym etapie działa preprocesor, który odpowiada za przekształcenia kodu przed jego właściwą kompilacją. Do głównych zadań preprocesora należą:

* **Włączanie zawartości plików nagłówkowych**: Dyrektywy takie jak `#include "plik.h"` pozwalają na dołączanie zewnętrznych plików, które zawierają deklaracje funkcji, zmiennych czy makr, co umożliwia modularność kodu.
* **Przetwarzanie makr**: Makra są instrukcjami umożliwiającymi definiowanie stałych lub fragmentów kodu, które mogą być wielokrotnie używane w różnych miejscach programu. Przykładem jest `#define PI 3.14`.
* **Usuwanie komentarzy**: Komentarze, które są dodawane dla lepszej czytelności kodu przez programistów, są usuwane, ponieważ nie są potrzebne w procesie kompilacji.

### 2. Analiza kodu źródłowego
Analiza kodu źródłowego to skomplikowany proces, który odbywa się w trzech głównych krokach:

* **Analiza leksykalna**: Ten etap polega na podziale kodu na najmniejsze jednostki, zwane tokenami. Tokeny to podstawowe elementy języka, takie jak słowa kluczowe, identyfikatory, literały czy operatory.
* **Analiza składniowa**: Na tym etapie sprawdzana jest zgodność kodu z gramatyką języka programowania. Proces ten polega na tworzeniu drzewa składniowego, które reprezentuje strukturalne relacje między tokenami.
* **Analiza semantyczna**: Sprawdzana jest poprawność typów i struktur w kodzie. Na przykład, czy zmienne są używane zgodnie z ich deklarowanymi typami oraz czy wywołania funkcji mają prawidłowe argumenty.

### 3. Generacja plików obiektowych
Po przejściu przez etapy analizy, kompilator generuje pliki obiektowe. Te pliki, zazwyczaj z rozszerzeniem `.o` lub `.obj`, zawierają kod w języku assembler, który jest pośrednią formą między kodem źródłowym a kodem maszynowym. Pliki obiektowe są niezależne i mogą być później łączone z innymi plikami obiektowymi lub bibliotekami.

### 4. Linkowanie
Linkowanie to końcowy etap kompilacji, w którym pliki obiektowe są łączone z kodem z zewnętrznych bibliotek, tworząc finalny, wykonywalny plik programu. Linker odpowiada za:

* **Łączenie symboli**: Znajdowanie definicji dla wszystkich deklaracji i referencji w plikach obiektowych.
* **Rozwiązanie referencji do bibliotek**: Integracja kodu z bibliotek zewnętrznych, zarówno statycznych (np. `.lib`) jak i dynamicznych (np. `.dll`).
* **Tworzenie pliku wykonywalnego**: Generowanie pliku, który może być uruchomiony przez system operacyjny.

## Dlaczego nie piszemy bezpośrednio w assemblerze?

Pisanie bezpośrednio w assemblerze jest rzadko praktykowane z kilku powodów:

* **Wielość dialektów**: Różne procesory mają różne zestawy instrukcji i dialekty języka assemblera. Pisanie kodu w assemblerze ogranicza jego przenośność pomiędzy różnymi architekturami sprzętowymi.
* **Automatyczna optymalizacja**: Kompilatory są zdolne do automatycznej optymalizacji kodu, co często prowadzi do bardziej wydajnego wykonania niż kod napisany ręcznie w assemblerze.
* **Wyższy poziom abstrakcji**: Języki wyższego poziomu, takie jak C++, Java czy Python, oferują zaawansowane struktury i abstrakcje, które ułatwiają zarządzanie dużymi projektami programistycznymi i pozwalają na szybsze tworzenie i utrzymywanie kodu.
* **Łatwość debugowania i utrzymania**: Kod napisany w językach wysokiego poziomu jest bardziej czytelny i łatwiejszy do debugowania. Dzięki temu programiści mogą szybciej znajdować i naprawiać błędy.

## Dyrektywy preprocesora
Dyrektywy rozpoczynające się od znaku `#` służą do instruowania preprocesora. Typowe przykłady to:

* `#include` - załączanie plików
* `#define` - definiowanie makr
* `#ifdef` - warunkowe kompilowanie kodu

Zwykle dyrektywy umieszcza się na początku pliku, dla przejrzystości.

## Kompilacja z wiersza poleceń

Kompilacja z wiersza poleceń jest podstawową umiejętnością każdego programisty, która pozwala na przekształcenie kodu źródłowego w plik wykonywalny bez potrzeby korzystania z zintegrowanego środowiska programistycznego (IDE). W tym celu najczęściej używane są narzędzia takie jak `gcc` dla języka C oraz `g++` dla języka C++. Poniżej znajduje się szczegółowy opis jak przeprowadzić kompilację oraz dodatkowe kroki, które mogą poprawić jakość i wydajność kodu.

### Kompilacja kodu w C przy użyciu `gcc`

`gcc` (GNU Compiler Collection) to popularny kompilator dla języka C. Aby skompilować program napisany w C, można użyć następującej komendy:

```bash
gcc -std=c99 main.c -o exe
```

**Opis opcji:**
- `-std=c99`: Określa standard języka C, w tym przypadku C99.
- `main.c`: Plik źródłowy, który ma być skompilowany.
- `-o exe`: Nazwa pliku wykonywalnego, który zostanie utworzony.

Dodatkowe opcje kompilacji mogą obejmować:

- `-Wall`: Włącza wszystkie ostrzeżenia kompilatora, co pomaga w wykrywaniu potencjalnych błędów.
- `-Wextra`: Włącza dodatkowe ostrzeżenia.
- `-O2`: Optymalizuje kod pod kątem wydajności.

Przykładowa komenda z dodatkowymi opcjami mogłaby wyglądać tak:

```bash
gcc -std=c99 -Wall -Wextra -O2 main.c -o exe
```

### Kompilacja programu w C++ przy użyciu `g++`

Dla języka C++ używamy kompilatora `g++`, który oferuje podobne opcje jak `gcc`, ale dostosowane do C++. Przykładowe komendy:

```bash
g++ -pedantic -std=c++98 main.cpp -o exe
```

lub dla nowszego standardu C++20 z bardziej rygorystycznymi opcjami:

```bash
g++-10 -Wall -Wextra -std=c++20 main.cpp -o exe
```

**Opis opcji:**
- `-pedantic`: Wymusza pełną zgodność ze standardem języka.
- `-std=c++98`: Określa standard języka C++, w tym przypadku C++98.
- `-std=c++20`: Określa standard języka C++, w tym przypadku C++20.
- `main.cpp`: Plik źródłowy w C++.
- `-o exe`: Nazwa pliku wykonywalnego.

### Formatowanie kodu przy użyciu `clang-format`

Dobre formatowanie kodu jest kluczowe dla czytelności i konserwacji. `clang-format` to narzędzie, które automatycznie formatuje kod zgodnie z określonymi regułami. Można je użyć do formatowania plików z różnymi rozszerzeniami (.c, .cpp, .h, .hpp, .cu). Przykładowa komenda:

```bash
find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;
```

**Opis komendy:**
- `find .`: Przeszukuje bieżący katalog i jego podkatalogi.
- `-regex '.*\.\(cpp\|hpp\|cu\|c\|h\)'`: Znajduje pliki z określonymi rozszerzeniami.
- `-exec clang-format -style=file -i {} \;`: Wykonuje `clang-format` na każdym znalezionym pliku, używając stylu zdefiniowanego w pliku konfiguracyjnym `.clang-format`.

### Dostosowywanie opcji kompilacji

Opcje kompilacji można dostosować do specyficznych potrzeb projektu. Oto kilka przykładów dodatkowych opcji:

- **Debugowanie**: Aby wygenerować dodatkowe informacje potrzebne do debugowania, można użyć opcji `-g`:
  ```bash
  gcc -std=c99 -g main.c -o exe
  ```

- **Profilowanie**: Aby umożliwić profilowanie wydajności aplikacji, można dodać opcję `-pg`:
  ```bash
  gcc -std=c99 -pg main.c -o exe
  ```

- **Użycie bibliotek zewnętrznych**: Aby skompilować kod korzystający z zewnętrznych bibliotek, można użyć opcji `-l` i `-L`:
  ```bash
  gcc -std=c99 main.c -o exe -L/path/to/library -lnameoflibrary
  ```
