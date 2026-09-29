# Automatyzacja budowania z Make

Przy jednym pliku wystarczy wywołać kompilator ręcznie. Gdy projekt rośnie, potrzebujemy sposobu na opisanie zależności między plikami i wykonywanie tylko tych kroków, które są konieczne. Do tego służy `make`.

## Cele

Po tej prezentacji powinieneś umieć:

- wyjaśnić, po co używa się systemu budowania,
- napisać prostą regułę w `Makefile`,
- używać zmiennych automatycznych `$@`, `$^` i `$<`,
- zbudować projekt z wielu plików,
- dodać cele `clean` i `test`.

## Od kodu źródłowego do programu

Uproszczony przepływ dla C/C++:

1. **Preprocessing** — rozwinięcie `#include`, `#define` i kompilacji warunkowej.
2. **Kompilacja** — analiza programu i wygenerowanie kodu asemblerowego lub wewnętrznej reprezentacji prowadzącej do kodu maszynowego.
3. **Asemblacja** — utworzenie pliku obiektowego, np. `main.o`.
4. **Linkowanie** — połączenie plików obiektowych i bibliotek w plik wykonywalny.

Przydatne opcje GCC/Clang:

```bash
gcc -E main.c              # tylko preprocessing
gcc -S main.c              # zatrzymaj się na kodzie asemblerowym
gcc -c main.c -o main.o    # utwórz plik obiektowy
gcc main.o -o program      # linkowanie
```

## Po co Make?

Dla projektu:

```text
main.c
parser.c
parser.h
io.c
io.h
```

nie chcemy za każdym razem kompilować wszystkiego. `make` porównuje zależności i czasy modyfikacji plików, a następnie przebudowuje potrzebne cele.

## Reguła w Makefile

Podstawowa postać:

```makefile
cel: zaleznosci
<TAB>polecenie
```

Przykład:

```makefile
main.o: main.c parser.h
	$(CC) $(CFLAGS) -c main.c -o main.o
```

**Ważne:** polecenie w klasycznym Makefile zaczyna się znakiem tabulacji, a nie spacjami.

## Zmienne

```makefile
CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic
```

Użycie:

```makefile
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
```

Często spotykane grupy flag:

- `CPPFLAGS` — opcje preprocessora, np. `-Iinclude`,
- `CFLAGS` — opcje kompilatora C,
- `CXXFLAGS` — opcje kompilatora C++,
- `LDFLAGS` — opcje linkera,
- `LDLIBS` — biblioteki, np. `-lm`.

## Zmienne automatyczne

W przepisie reguły można używać:

| Zmienna | Znaczenie |
| --- | --- |
| `$@` | nazwa celu |
| `$^` | wszystkie zależności |
| `$<` | pierwsza zależność |

Przykład:

```makefile
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
```

## Projekt z wielu plików

```makefile
CC := gcc
CPPFLAGS :=
CFLAGS := -Wall -Wextra -Wpedantic -O2

TARGET := program
SRC := main.c parser.c io.c
OBJ := $(SRC:.c=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET) < input.txt > output.txt
	diff -u expected_output.txt output.txt

clean:
	rm -f $(OBJ) $(TARGET) output.txt
```

Teraz:

```bash
make
make test
make clean
```

## Cele pozorne i `.PHONY`

Cele takie jak `clean` lub `test` nie reprezentują plików. Warto oznaczać je jako `.PHONY`:

```makefile
.PHONY: clean test
```

Dzięki temu przypadkowy plik o nazwie `clean` nie zablokuje wykonania celu.

## Automatyczne zależności nagłówków

Ręczne dopisywanie każdego nagłówka łatwo prowadzi do błędów. GCC i Clang mogą generować pliki zależności:

```makefile
CFLAGS += -MMD -MP
DEPS := $(OBJ:.o=.d)

-include $(DEPS)
```

Przy kompilacji powstaną pliki `.d`, które opisują zależności plików obiektowych od nagłówków.

Wtedy warto rozszerzyć `clean`:

```makefile
clean:
	rm -f $(OBJ) $(DEPS) $(TARGET)
```

## Make a CMake

`make` wykonuje reguły zapisane w Makefile. CMake to generator systemów budowania — może wygenerować m.in. Makefile lub pliki dla Ninja i IDE.

W praktyce:

- mały projekt lub ćwiczenie → ręczny Makefile jest świetny do nauki zależności,
- większy wieloplatformowy projekt → często wygodniejszy jest CMake, Meson lub inny wyższy poziom.

## Najczęstsze pułapki

- Brak zależności od nagłówka może spowodować użycie starego pliku obiektowego.
- `make` nie analizuje semantyki C/C++; opiera się na grafie zależności i plikach.
- `-Werror` bywa użyteczne w CI, ale nie zawsze warto wymuszać je podczas każdej lokalnej kompilacji.
- Kolejność bibliotek przy linkowaniu może mieć znaczenie.
- Komenda `clean` powinna usuwać wyłącznie artefakty generowane.

## Podsumowanie

Najważniejsza idea Make to:

> **cel zależy od innych plików, a przepis mówi, jak go odtworzyć.**

Dobrze napisany Makefile skraca czas budowania, dokumentuje proces kompilacji i daje jeden powtarzalny sposób uruchamiania testów oraz innych zadań projektu.
