## Potrzeba korzystania z narzędzi automatyzującyc proces budowania programów.

Podczas pracy z językiem C, często pierwszym sposobem na kompilację, którego się uczymy, jest wywołanie kompilatora gcc wraz z odpowiednimi flagami w terminalu. Jednakże, kiedy lista plików źródłowych rośnie, a projekty stają się coraz bardziej złożone, korzystanie z ręcznych komend w terminalu staje się mniej praktyczne i trudne do utrzymania.

```cpp
gcc -Wall -Wextra -Werror -o program.exe main.c
```

Co mamy jednak zrobić, gdy lista plików z kodem źródłowym rośnie? Co jeśli używamy innych flag w dwóch projektach nad którymi pracujemy jednocześnie? Czy mamy zapisywać je w jakimś pliku?

Dlatego też, istnieją narzędzia automatyzujące proces budowania programów. W tym artykule skupimy się na narzędziu `make`, ale warto wiedzieć, że istnieją również inne narzędzia, takie jak `CMake` czy `Autotools`.

## Proces kompilacji programu w języku C

Przed omówieniem narzędzia make, warto krótko przypomnieć proces kompilacji programu w języku C. Proces ten można podzielić na pięć etapów:

1. Preprocesor - zajmuje się dyrektywami #include, #define itp. oraz usuwa komentarze.
2. Analiza - analizuje kod i znajduje w nim błędy.
3. Kompilacja - tłumaczy kod C na kod asemblerowy.
4. Assembler - tłumaczy kod asemblerowy na pliki obiektowe.
5. Linker - łączy pliki obiektowe i tworzy finalny plik wykonywalny.

Różne flagi kompilatora gcc pozwalają nam zatrzymać się na danym etapie kompilacji. Przykładowo, uruchomienie gcc z flagą `-E` zatrzyma kompilator na etapie analizy. Uruchomienie gcc z flagą `-S` zatrzyma kompilator na etapie kompilacji. Uruchomienie gcc z flagą `-c` zatrzyma kompilator na etapie linkowania. Uruchomienie gcc bez flagi, przejdzie przez wszystkie etapy kompilacji.

## Make
Make to narzędzie używane do budowy projektów i kompilacji pod systemami z rodziny Unix. Nie jest częścią języka C, ale może być wykorzystywane do budowania projektów napisanych w tym języku. Make jest szczególnie przydatne w pracy z wieloma plikami źródłowymi, ponieważ pozwala wybrać listę plików potrzebnych do kompilacji oraz ponownie kompiluje dany plik tylko wtedy, gdy zajdzie taka potrzeba.

Make pozwala również na automatyczne wywoływanie testów oraz budowanie dokumentacji. Ogólnie wygląda to tak, że tworzy się plik Makefile, za pomocą którego steruje się całym procesem.

```cpp
target: dependency_1 dependency_2 ... dependency_n
    command_1
    command_2
    ...
    command_n
```

## Struktura i budowa pliku Makefile

Plik Makefile jest plikiem tekstowym, który definiuje zależności między plikami źródłowymi oraz polecenia niezbędne do ich kompilacji i łączenia w gotowy program.

Makefile składa się z tzw. reguł, które określają, jakie pliki zależą od innych plików i jakie komendy należy wykonać, aby je skompilować i połączyć w całość.

Przykład reguły w Makefile:

```cpp
executable: main.o utils.o
    gcc -o executable main.o utils.o
```

* `executable` - nazwa pliku wyjściowego, który ma zostać utworzony
* `main.o` i `utils.o` - pliki zależne, od których zależy plik wyjściowy
* `gcc -o executable main.o utils.o` - polecenie, które należy wykonać, aby zbudować plik wyjściowy

Ponadto, Makefile może zawierać zmienne, funkcje i warunki logiczne, które pozwalają na definiowanie bardziej skomplikowanych zależności między plikami i dynamiczne generowanie komend.

Objaśnienie elementów Makefile:

```cpp
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

* `CC` - zmienna przechowująca nazwę kompilatora
* `CFLAGS` - zmienna przechowująca dodatkowe flagi kompilacji
* `SRC` - zmienna przechowująca nazwy plików źródłowych
* `OBJ` - zmienna przechowująca nazwy plików obiektowych, które mają zostać zbudowane
* `executable` - nazwa pliku wyjściowego
* `$(OBJ)` - zmienna zależności, określająca, że plik wyjściowy zależy od plików obiektowych
* `$(CC) -o $@ $^` - polecenie łączenia plików obiektowych w plik wyjściowy
* `%.o: %.c` - reguła, która mówi, jak zbudować plik obiektowy z pliku źródłowego
* `$(CC) $(CFLAGS) -c $< -o $@` - polecenie kompilacji pliku źródłowego do pliku obiektowego
* `clean` - reguła, która usuwa pliki tymczasowe
    
## Przykłady

### Przykład 1: Kompilacja jednego pliku źródłowego

```cpp
makefile

CC=gcc

executable: main.c
	$(CC) -o executable main.c
```

Kompilacja:

```cpp
make executable
```

### Przykład 2: Kompilacja wielu plików źródłowych

Załóżmy, że mamy projekt składający się z wielu plików źródłowych, na przykład main.c, file1.c i file2.c, i chcemy skompilować je do jednego pliku wykonywalnego. W pliku Makefile możemy zdefiniować zmienną OBJS, która zawiera nazwy wszystkich plików źródłowych, a następnie zdefiniować regułę dla pliku wykonywalnego, która odwołuje się do wszystkich plików źródłowych:

```cpp
CC=gcc
CFLAGS=-Wall -Wextra -Werror
OBJS=main.o file1.o file2.o

my_program: $(OBJS)
	$(CC) $(CFLAGS) -o my_program $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) my_program
```

W powyższym przykładzie używamy reguły `%.o: %.c`, która mówi, że każdy plik obiektowy (o rozszerzeniu .o) zależy od odpowiadającego mu pliku źródłowego (o rozszerzeniu .c) i można go skompilować za pomocą komendy `gcc -c`. Dzięki temu Makefile automatycznie skompiluje każdy plik źródłowy i zbuduje plik wykonywalny.

### Przykład 3: Kompilacja biblioteki

Często w projektach korzystamy z gotowych bibliotek, które muszą zostać skompilowane i połączone z naszym kodem. Możemy zdefiniować osobną regułę dla każdej biblioteki i następnie odwołać się do tych reguł w regule dla pliku wykonywalnego:

```cpp
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

W powyższym przykładzie dodaliśmy regułę my_library.o, która kompiluje plik źródłowy my_library.c i zapisuje wynik w pliku obiektowym my_library.o. W regule my_program odwołujemy się do pliku my_library.o, który jest wymagany do skompilowania pliku wykonywalnego, oraz do zmiennej `LIBS`, która zawiera listę bibliotek wymaganych do zlinkowania z kodem.

### Przykład 4: Wykonywanie testów

Oto przykładowy Makefile, który poza kompilacją programu, zawiera także regułę do automatycznego wykonywania testów:

```cpp
CC=gcc
CFLAGS=-Wall -Wextra -Werror

# lista plików źródłowych
SOURCES=main.c myfunc.c

# plik wykonywalny
EXECUTABLE=myprog

# pliki obiektowe
OBJECTS=$(SOURCES:.c=.o)

# reguła do kompilacji pliku wykonywalnego
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# reguła do kompilacji plików źródłowych
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# reguła do automatycznego wykonywania testów
test:
	./$(EXECUTABLE) < input.txt > output.txt
	diff -q output.txt expected_output.txt && echo "Tests passed!" || echo "Tests failed!"
	rm output.txt
```

Reguła test wykorzystuje program diff, który porównuje plik output.txt z plikiem expected_output.txt i zwraca wynik testów. W tym przykładzie, wejście do programu jest przekierowane z pliku input.txt, a wynik działania programu zapisywany jest do pliku output.txt. Na końcu reguły plik output.txt jest usuwany za pomocą polecenia rm.
