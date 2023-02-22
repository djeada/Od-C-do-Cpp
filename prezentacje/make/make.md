Potrzeba korzystania z narzędzi automatyzującyc proces budowania
programów.

Często zaczynając programować w C, pierwszym sposobem na kompilację,
którego się uczymy jest wywołanie gcc wraz z odpowiednimi flagami w
terminalu.

``` {.c++ language="C++"}
\begin{verbatim}
gcc -Wall -Wextra -Werror -o program.exe main.c
        \end{verbatim}
```

Co mamy jednak zrobić, gdy lista plików z kodem źródłowym rośnie? Co
jeśli używamy innych flag w dwóch projektach nad którymi pracujemy
jednocześnie? Czy mamy zapisywać je w jakimś pliku?

Proces kompilacji:

1.  preprocesor --- zajmuje się dyrektywami \#include, \#define itp.
    oraz usuwa komentarze.

2.  analiza --- analizuje kod i znajduje w nim błędy.

3.  kompilacja --- tłumaczy c na assembler.

4.  assembler --- tłumaczy assembler na pliki obiektowe.

5.  linker --- łączy pliki obiektowe.

Różne flagi kompilatora gcc, pozwalają nam zatrzymać się na danym etapie
kompilacji. Przykładowo uruchomienie gcc z flagą -E zatrzyma kompilator
na etapie analizy. Uruchomienie gcc z flagą -S zatrzyma kompilator na
etapie kompilacji. Uruchomienie gcc z flagą -c zatrzyma kompilator na
etapie linkowania. Uruchomienie gcc bez flag, przejdzie przez wszystkie
etapy kompilacji.

Make to narzędzie używane do budowy projektów i kompilacji pod systemami
z rodziny Unix.

-   nie jest częścią C;

-   przydatny w pracy z wieloma plikami źródłowymi;

-   pozwala wybrać listę plików potrzebnych do kompilacji;

-   ponownie kompiluje dany plik tylko, gdy zajdzie potrzeba;

-   może być wykorzystywany do automatycznego wywoływania testów i
    budowy dokumentacji;

Ogólnie wygląda to tak, tworzy się plik Makefile, za pomocą którego
steruje się całym procesem.

``` {.c++ language="C++"}
\begin{verbatim}
target: dependency_1 dependency_2 ... dependency_n
\tcommand_1
\tcommand_2
\t...
\tcommand_n
        \end{verbatim}
```

Prosty przykład użycia Makefile.

Powiedzmy, że mamy plik źródłowy main.c i chcemy go skompilować do pliku
wykonywalnego executable. Musimy wskazać nazwę pliku wykonywalnego oraz
od jakich plików źródłowych zależy. Dodatkowo wybieramy sposób, w jaki
jest kompilowany (np. przy użyciu gcc).

``` {.c++ language="C++"}
\begin{verbatim}
moj_program: main.c
\tgcc -Wall -Wextra -Werror -o executable main.c
        \end{verbatim}
```

Aby wykorzystać Makefile, musimy w otworzyć terminal w folderze, w
którym znajduje się nasz Makefile i użyć następującego polecenia:

``` {.c++ language="C++"}
\begin{verbatim}
make moj_program
        \end{verbatim}
```

Innymi przydatnymi funkcjami Makefile jest możliwość definiowania
zmiennych oraz reguła clean, dzięki której możemy automatycznie usuwać
pliki obiektowe po zakończeniu kompilacji.

``` {.c++ language="C++"}
\begin{verbatim}
CC=gcc

moj_program: main.o plik_1.o plik_2.o

main.o: main.c
\t$(CC) -Wall -Wextra -Werror -o main.o main.c

plik_1.o: plik_1.c
\t$(CC) -Wall -Wextra -Werror -o plik_1.o plik_1.c

plik_2.o: plik_2.c
\t$(CC) -Wall -Wextra -Werror -o plik_2.o plik_2.c

clean:
\trm -f *.o moj_program
        \end{verbatim}
```
