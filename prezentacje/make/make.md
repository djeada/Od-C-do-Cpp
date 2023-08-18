## Automatyzacja procesu budowania w programowaniu

Podczas pracy nad projektami programistycznymi, szczególnie w językach jak C lub C++, bezpośrednie wywoływanie kompilatora z terminala może być początkowo wystarczające. Jednak z rosnącą złożonością projektu, większą ilością plików źródłowych, modułów oraz zależnościami, potrzeba zastosowania narzędzi automatyzujących proces budowania staje się kluczowa.

```bash
gcc -Wall -Wextra -Werror -o program.exe main.c
```

Pojawia się pytanie: Jak zarządzać kompilacją w skomplikowanych projektach z wieloma plikami, flagami i opcjami? Oto kilka wyzwań, które mogą się pojawić:

- Zarządzanie zależnościami między plikami.
- Kompilacja tylko tych plików, które zostały zmienione.
- Zastosowanie różnych flag dla różnych części projektu.
- Generowanie dokumentacji.
- Uruchamianie testów automatycznych.

Aby sprostać tym wyzwaniom, programiści korzystają z narzędzi takich jak make, CMake, Autotools i innych.

### Proces kompilacji w języku C

Każdy program napisany w języku C przechodzi przez kilka etapów przetwarzania przed stworzeniem ostatecznego pliku wykonywalnego:

- **Preprocesor**: Obsługuje dyrektywy takie jak #include czy #define oraz eliminuje komentarze.
- **Analiza**: Sprawdza poprawność składni kodu, szuka błędów.
- **Kompilacja**: Konwertuje kod źródłowy na kod maszynowy.
- **Assembler**: Tworzy plik obiektowy z kodu maszynowego.
- **Linker**: Łączy różne pliki obiektowe i tworzy jeden plik wykonywalny.

Różne flagi kompilatora, takie jak `-E`, `-S` czy `-c`, pozwalają kontrolować, na którym z tych etapów kompilator powinien się zatrzymać.

### Make - narzędzie do automatyzacji procesu budowania

Make to popularne narzędzie, które pozwala automatyzować proces budowania projektów. Jego główną zaletą jest zdolność do wykrywania, które części programu wymagają ponownej kompilacji, co przyspiesza proces budowy.

Aby korzystać z Make, należy stworzyć specjalny plik o nazwie Makefile, który zawiera instrukcje dotyczące budowy projektu. 

Plik Makefile jest specyficznym plikiem tekstowym używanym przez narzędzie `make`, który określa zależności między plikami źródłowymi a poleceniami niezbędnymi do ich kompilacji i łączenia w gotowy program lub bibliotekę.

Podstawowym elementem w Makefile są reguły, które wskazują, jakie pliki zależą od innych i jakie polecenia należy wykonać, aby wygenerować te zależności.

Typowa reguła w Makefile ma następującą postać:

```makefile
target: dependencies
    recipe

    target - cel, który ma zostać utworzony.
    dependencies - lista plików, od których zależy cel.
    recipe - polecenia, które należy wykonać, aby zbudować cel.
```

Przykład struktury Makefile

```makefile
CC=gcc
CFLAGS=-Wall -Wextra -Werror
SRC=main.c utils.c
OBJ=$(SRC:.c=.o)

executable: $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o executable
```

Opis elementów w powyższym przykładzie:

- `CC` - zmienna określająca używany kompilator.
- `CFLAGS` - flagi, które zostaną przekazane do kompilatora.
- `SRC` - lista plików źródłowych projektu.
- `OBJ` - lista plików obiektowych wygenerowanych na podstawie SRC.
- `executable` - cel główny pliku wyjściowego.
- `$(OBJ)` - zmienna reprezentująca pliki obiektowe.
- `$(CC) -o $@ $^` - polecenie linkera do utworzenia pliku wykonywalnego.
- `%.o: %.c` - wzorzec reguły mówiący, jak zbudować plik obiektowy z pliku źródłowego.
- `$(CC) $(CFLAGS) -c $< -o $@` - polecenie kompilacji pliku źródłowego.
- `clean` - cel specjalny, który pozwala na usunięcie plików tymczasowych i pliku wykonywalnego.

Warto zauważyć, że w Makefile używane są specjalne zmienne, takie jak $@ (reprezentująca cel), $^ (reprezentująca wszystkie zależności) i $< (reprezentująca pierwszą zależność). Dzięki nim, Makefile jest bardziej elastyczny i czytelny.

### Przykład 1: Kompilacja jednego pliku źródłowego

Poniżej przedstawiono podstawowy plik Makefile do kompilacji jednego pliku źródłowego:

```makefile
CC=gcc

executable: main.c
	$(CC) -o executable main.c
```

Aby przeprowadzić kompilację, wystarczy użyć komendy:

```bash
make executable
```

### Przykład 2: Kompilacja wielu plików źródłowych

Jeśli pracujemy z projektem złożonym z wielu plików źródłowych, takich jak `main.c`, `file1.c` i `file2.c`, możemy skorzystać z Makefile do automatycznego kompilowania i łączenia tych plików w jeden plik wykonywalny.

Oto przykład takiego pliku Makefile:

```makefile
CC=gcc
CFLAGS=-Wall -Wextra -Werror
SRC=main.c file1.c file2.c
OBJS=$(SRC:.c=.o)

my_program: $(OBJS)
	$(CC) $(CFLAGS) -o my_program $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) my_program
```

W tym przypadku:

- Utworzono listę plików źródłowych w zmiennej `SRC`.
- Użyto zastępowania tekstu (`$(SRC:.c=.o)`) do automatycznego generowania odpowiednich nazw plików obiektowych na podstawie plików źródłowych.
- Reguła`%.o: %.c` definiuje, jak skompilować plik obiektowy z danego pliku źródłowego.
- Cel clean pozwala na szybkie usunięcie plików obiektowych i wykonywalnego, jeśli chcemy oczyścić katalog projektu.

Aby zbudować cały projekt, wystarczy uruchomić:

```bash
make my_program
```

A do usunięcia wszystkich skompilowanych plików:

```bash
make clean
```

### Przykład 3: Kompilacja biblioteki

Kiedy korzystamy z zewnętrznych bibliotek, niezbędne jest ich skompilowanie i połączenie z naszym głównym kodem. Możemy określić dedykowane reguły dla każdej z bibliotek, a następnie odwołać się do nich w regule głównego pliku wykonywalnego:

```makefile
CC=gcc
CFLAGS=-Wall -Wextra -Werror
LIBS=-lm
OBJS=main.o my_library.o

my_library.o: my_library.c my_library.h
	$(CC) $(CFLAGS) -c my_library.c -o my_library.o

my_program: $(OBJS)
	$(CC) $(CFLAGS) -o my_program $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) my_program
```

W powyższym przypadku, dodaliśmy regułę `my_library.o` odpowiedzialną za kompilację kodu źródłowego `my_library.c` do pliku obiektowego `my_library.o`. W regule my_program, odnosimy się do `my_library.o` oraz zmiennej `LIBS`, które są niezbędne do zlinkowania z głównym kodem.

### Przykład 4: Wykonywanie testów

Poniżej znajduje się Makefile umożliwiający nie tylko kompilację programu, ale także automatyczne wykonanie zestawu testów:

```makefile
CC=gcc
CFLAGS=-Wall -Wextra -Werror

# Lista plików źródłowych
SOURCES=main.c myfunc.c

# Plik wykonywalny
EXECUTABLE=myprog

# Pliki obiektowe
OBJECTS=$(SOURCES:.c=.o)

# Reguła do kompilacji pliku wykonywalnego
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# Reguła do kompilacji plików źródłowych
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Reguła do automatycznego wykonywania testów
test:
	./$(EXECUTABLE) < input.txt > output.txt
	diff -q output.txt expected_output.txt && echo "Tests passed!" || echo "Tests failed!"
	rm output.txt
```

Reguła test korzysta z narzędzia diff, które porównuje wynikowy plik `output.txt` z oczekiwanym wynikiem `expected_output.txt`. Jeśli pliki są identyczne, testy przechodzą pomyślnie. Wejście dla testowanego programu jest pobierane z pliku `input.txt`, a wyniki zapisywane są do `output.txt`. Po zakończeniu testów, `output.txt` zostaje usunięty.
