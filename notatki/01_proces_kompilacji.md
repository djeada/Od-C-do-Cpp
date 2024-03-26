## Proces kompilacji

Kompilator to narzędzie przekształcające kod źródłowy napisany w danym języku programowania na kod maszynowy lub inny język niskiego poziomu. Proces ten składa się z kilku etapów:

### 1. Etap preprocesowania 
Na tym etapie wchodzi w grę preprocesor, który odpowiada za:

* Włączanie zawartości plików nagłówkowych, np. przez dyrektywę `#include "plik.h"`.
* Przetwarzanie makr, które są instrukcjami umożliwiającymi m.in. definiowanie stałych.
* Usuwanie zakomentowanego kodu.

### 2. Analiza składni
Analiza kodu źródłowego odbywa się w trzech krokach:

* **Analiza leksykalna** - dzieli kod na najmniejsze jednostki, tzw. tokeny.
* **Analiza składniowa** - sprawdza zgodność kodu z gramatyką języka.
* **Analiza semantyczna** - weryfikuje poprawność typów i struktur w kodzie.

### 3. Generacja plików obiektowych
Na tym etapie kompilator tworzy pliki obiektowe (często z rozszerzeniem `.o` lub `.obj`), które są reprezentacją kodu w postaci języka assembler.

### 4. Linkowanie
Pliki obiektowe łączone są z kodem z zewnętrznych bibliotek, tworząc finalny, wykonywalny plik programu.

## Dlaczego nie piszemy bezpośrednio w assemblerze?

* **Wielość dialektów** - różne procesory mają różne instrukcje, a kompilatory pozwalają tłumaczyć kod na różne architektury.
* **Automatyczna optymalizacja** - kompilatory mogą optymalizować kod, czyniąc go wydajniejszym.
* **Wyższy poziom abstrakcji** - języki wyższego poziomu, takie jak C++ czy Java, oferują struktury ułatwiające pisanie kodu.

## Dyrektywy preprocesora
Dyrektywy rozpoczynające się od znaku `#` służą do instruowania preprocesora. Typowe przykłady to:

* `#include` - załączanie plików
* `#define` - definiowanie makr
* `#ifdef` - warunkowe kompilowanie kodu

Zwykle dyrektywy umieszcza się na początku pliku, dla przejrzystości.

## Kompilacja z wiersza poleceń

Aby skompilować kod w C przy użyciu `gcc`, można użyć:

```bash
gcc -std=c99 main.c -o exe
```

Natomiast kompilacja programu napisanego w języku C++ przy użyciu kompilatora g++ może wyglądać następująco:

```
g++ -pedantic -std=c++98 main.cpp -o exe
```

lub:

```
g++-10 -Wall -Wextra -std=c++20 main.cpp -o exe
```

Dodatkowo, możemy użyć narzędzia clang-format do poprawy formatowania naszego kodu. Przykładowo, poniższe polecenie znajduje wszystkie pliki z rozszerzeniem .c, .cpp, .h, .hpp, .cu i wykonuje na nich formatowanie zgodnie z ustalonym stylem:

```
find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;
```

Można dostosować opcje kompilacji do konkretnych potrzeb projektu.
