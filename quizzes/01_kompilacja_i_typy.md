# Kompilacja, preprocesor i typy danych — quiz

Notatki: [Proces kompilacji](../notatki/01_proces_kompilacji.md), [Preprocesor](../notatki/02_preprocesor.md), [Zmienne i typy danych](../notatki/03_zmienne_i_typy_danych.md), [Interakcja z konsolą](../notatki/04_interakcja_z_konsola.md)

Sprawdź, czy rozumiesz drogę od pliku źródłowego do programu, działanie preprocesora, podstawowe typy oraz wejście i wyjście w C i C++.

#### Q. Który etap budowania programu dopasowuje wywołania funkcji do ich definicji z innych plików obiektowych?

* [ ] Preprocesowanie
* [ ] Analiza składniowa
* [x] Linkowanie
* [ ] Generowanie kodu asemblera

> **Wyjaśnienie:** Linker łączy pliki obiektowe i biblioteki, dopasowując odwołania do symboli zdefiniowanych gdzie indziej. Preprocesor jedynie przetwarza dyrektywy `#`, a analiza składniowa sprawdza pojedynczą jednostkę translacji.

#### Q. Co robi opcja `-c` w poleceniu `g++ -std=c++20 -c powitanie.cpp -o powitanie.o`?

* [ ] Wypisuje na ekran wynik samego preprocesowania
* [x] Tworzy plik obiektowy bez etapu linkowania
* [ ] Zapisuje do pliku tekstowy kod asemblera
* [ ] Dodaje do programu informacje dla debugera

> **Wyjaśnienie:** `-c` kończy pracę na pliku obiektowym `.o`, który trzeba później zlinkować. Wynik preprocesowania daje `-E`, kod asemblera `-S`, a dane dla debugera `-g`.

#### Q. Projekt ma pliki `main.cpp` (wywołuje `wypisz_powitanie()`), `powitanie.hpp` (deklaracja) i `powitanie.cpp` (definicja). Co się stanie po poleceniu `g++ main.cpp -o program`?

* [x] Linker zgłosi brak definicji `wypisz_powitanie`
* [ ] Kompilator zgłosi nieznaną nazwę `wypisz_powitanie`
* [ ] Preprocesor nie znajdzie pliku `powitanie.hpp`
* [ ] Program powstanie, ale niczego nie wypisze

> **Wyjaśnienie:** Dzięki deklaracji z nagłówka `main.cpp` kompiluje się poprawnie, ale definicja funkcji jest w `powitanie.cpp`, którego nie podano. To typowy błąd linkowania („undefined reference”).

#### Q. Która opcja GCC zatrzymuje budowanie po preprocesowaniu i wypisuje przetworzony tekst?

* [x] `-E`
* [ ] `-S`
* [ ] `-c`
* [ ] `-g`

> **Wyjaśnienie:** `-E` pokazuje kod po rozwinięciu `#include`, makr i kompilacji warunkowej. `-S` zatrzymuje się na kodzie asemblera, a `-c` na pliku obiektowym.

#### Q. Na którym etapie zostanie wykryty błąd w instrukcji C++ `int liczba = "tekst";`?

* [ ] Podczas preprocesowania pliku
* [x] Podczas sprawdzania typów w kompilacji
* [ ] Podczas linkowania plików obiektowych
* [ ] Dopiero w czasie działania gotowego programu

> **Wyjaśnienie:** Składnia jest poprawna, ale napis nie jest wartością typu `int`. Kompilator wykrywa to, sprawdzając znaczenie kodu i zgodność typów, zanim powstanie plik obiektowy.

#### Q. Co zwykle przechowuje sekcja `.bss` pliku obiektowego?

* [ ] Kod maszynowy skompilowanych funkcji
* [x] Dane globalne i statyczne inicjalizowane zerem
* [ ] Dane globalne z niezerową wartością początkową
* [ ] Tablicę symboli używaną przez linker

> **Wyjaśnienie:** `.bss` służy danym globalnym i statycznym o początkowej wartości zero. Kod maszynowy trafia zwykle do `.text`, a dane z niezerową wartością początkową do `.data`.

#### Q. Jakiego pliku linker GNU szuka na Linuksie po podaniu opcji `-L. -lpowitanie`?

* [ ] `powitanie.o`
* [x] `libpowitanie.so` lub `libpowitanie.a`
* [ ] `lpowitanie.a`
* [ ] `powitanie.hpp`

> **Wyjaśnienie:** W opcji `-l` pomija się prefiks `lib` i rozszerzenie, więc `-lpowitanie` oznacza bibliotekę `libpowitanie` w wersji dynamicznej `.so` lub statycznej `.a`. `-L.` dodaje bieżący katalog do miejsc wyszukiwania.

#### Q. Co jest prawdą o bibliotece dynamicznej `libpowitanie.so`, z którą zlinkowano program?

* [ ] Jej kod zostaje na stałe skopiowany do programu
* [x] System musi ją znaleźć przy starcie programu
* [ ] Tworzy się ją poleceniem `ar rcs libpowitanie.so`
* [ ] Może z niej korzystać tylko jeden program naraz

> **Wyjaśnienie:** Biblioteka dynamiczna pozostaje osobnym plikiem, który system ładuje przy starcie programu i który może współdzielić wiele aplikacji. Kopiowanie kodu do programu dotyczy biblioteki statycznej `.a`, tworzonej przez `ar`.

#### Q. Jakimi znakami muszą być wcięte polecenia reguł w pliku `Makefile`?

* [ ] Czterema spacjami
* [x] Znakiem tabulacji
* [ ] Dowolnymi białymi znakami
* [ ] Dwiema spacjami

> **Wyjaśnienie:** `make` rozpoznaje polecenia reguły po wiodącym znaku tabulacji. Wcięcie spacjami zwykle kończy się błędem „missing separator”.

#### Q. Ile jednostek translacji przetworzy kompilator po poleceniu `g++ main.cpp powitanie.cpp -o program`, jeśli oba pliki dołączają `powitanie.hpp`?

* [ ] 1
* [x] 2
* [ ] 3
* [ ] 4

> **Wyjaśnienie:** Każdy plik `.cpp` jest preprocesowany osobno i razem z dołączonymi nagłówkami tworzy jedną jednostkę translacji. Nagłówek nie jest osobną jednostką — jego treść trafia do obu plików.

#### Q. Dlaczego w większym projekcie kompiluje się pliki osobno do plików `.o` (np. za pomocą `make`)?

* [ ] Gotowy program działa wtedy wyraźnie szybciej niż zwykle
* [x] Po zmianie pliku przebudowuje się tylko jego część
* [ ] Linker nie jest wtedy w ogóle potrzebny
* [ ] Kompilator nie zgłasza wtedy ostrzeżeń

> **Wyjaśnienie:** Pliki obiektowe niezmienionych źródeł można użyć ponownie, więc `make` uruchamia tylko nieaktualne kroki. Szybkość samego programu i potrzeba linkowania się nie zmieniają.

#### Q. Co wypisze ten program w C z makrem `KWADRAT`?

```c
#include <stdio.h>

#define KWADRAT(x) x * x

int main(void) {
    int a = 5;
    printf("%d\n", KWADRAT(a + 1));
    return 0;
}
```

* [ ] `36`
* [x] `11`
* [ ] `12`
* [ ] `25`

> **Wyjaśnienie:** Preprocesor wstawia tekst dosłownie: powstaje `a + 1 * a + 1`, czyli `5 + 5 + 1`. Nawiasy `((x) * (x))` w definicji makra dałyby oczekiwane `36`.

#### Q. Co wypisze ten program w C z dyrektywami `#ifdef` i `#if`?

```c
#include <stdio.h>

#define WERSJA 0

int main(void) {
#ifdef WERSJA
    puts("A");
#else
    puts("B");
#endif
#if WERSJA
    puts("C");
#else
    puts("D");
#endif
    return 0;
}
```

* [x] `A`, a w następnym wierszu `D`
* [ ] `B`, a w następnym wierszu `D`
* [ ] `A`, a w następnym wierszu `C`
* [ ] `B`, a w następnym wierszu `C`

> **Wyjaśnienie:** `#ifdef` sprawdza tylko, czy makro istnieje — `WERSJA` jest zdefiniowane, więc wybrane zostaje `A`. `#if` sprawdza wartość, a `0` oznacza fałsz, więc wybrane zostaje `D`.

#### Q. Jak preprocesor potraktuje warunek `#if WERSJA_ == 2`, jeśli makro `WERSJA_` nigdy nie zostało zdefiniowane?

* [ ] Zgłosi błąd o nieznanej nazwie
* [x] Podstawi `0`, więc warunek będzie fałszywy
* [ ] Podstawi `1`, więc warunek będzie prawdziwy
* [ ] Sprawdzi zmienną o tej nazwie podczas działania

> **Wyjaśnienie:** W wyrażeniu `#if` niezdefiniowana nazwa jest traktowana jak `0`. Dlatego literówka w nazwie makra może po cichu wybrać inną gałąź; samo istnienie makra sprawdza się przez `#ifdef` lub `defined(...)`.

#### Q. Przed czym chroni strażnik nagłówka (`#ifndef` / `#define` / `#endif`)?

* [ ] Przed dołączeniem tego nagłówka do więcej niż jednego pliku `.cpp`
* [x] Przed ponownym przetworzeniem w tej samej jednostce translacji
* [ ] Przed linkowaniem dwóch definicji tej samej funkcji
* [ ] Przed użyciem makr z nagłówka w innych plikach

> **Wyjaśnienie:** Strażnik sprawia, że przy kolejnym dołączeniu w tej samej jednostce translacji makro jest już zdefiniowane i treść zostaje pominięta. Każdy plik `.cpp` nadal dołącza nagłówek osobno.

#### Q. Co wypisze ten program skompilowany poleceniem `gcc -std=c11 -DNDEBUG prog.c`?

```c
#include <stdio.h>

int main(void) {
#ifndef NDEBUG
    puts("Diagnostyka");
#endif
    puts("Program działa");
    return 0;
}
```

* [ ] `Diagnostyka`, a potem `Program działa`
* [x] Tylko `Program działa`
* [ ] Tylko `Diagnostyka`
* [ ] Nic — kompilacja zakończy się błędem

> **Wyjaśnienie:** `-DNDEBUG` definiuje makro `NDEBUG`, więc warunek `#ifndef NDEBUG` jest fałszywy i preprocesor usuwa wiersz diagnostyczny, zanim kod trafi do kompilatora.

#### Q. Co wypisze ten program w C z makrem `__LINE__`?

```c
#include <stdio.h>

int main(void) {
    printf("%d\n", __LINE__);
    return 0;
}
```

* [ ] `1`
* [ ] `3`
* [x] `4`
* [ ] `0`

> **Wyjaśnienie:** `__LINE__` to predefiniowana nazwa rozwijana do numeru bieżącego wiersza pliku źródłowego. Wywołanie `printf` znajduje się w czwartym wierszu.

#### Q. Co jest prawdą o dyrektywie `#pragma once`?

* [ ] Jest wymagana przez standard C++20 w każdym nagłówku
* [x] Jest powszechnie obsługiwana, ale niestandardowa
* [ ] Działa tylko w plikach C, a w C++ jest ignorowana
* [ ] Dołącza nagłówek tylko raz w całym programie

> **Wyjaśnienie:** Popularne kompilatory obsługują `#pragma once`, lecz nie jest to standardowy, przenośny mechanizm. Klasyczne strażniki `#ifndef` są w pełni standardowe; oba sposoby działają w obrębie jednej jednostki translacji.

#### Q. Co wypisze ten program w C, w którym makro zdefiniowano wewnątrz funkcji `f`?

```c
#include <stdio.h>

void f(void) {
#define LIMIT 10
}

int main(void) {
    printf("%d\n", LIMIT);
    return 0;
}
```

* [ ] Błąd kompilacji: `LIMIT` jest niezadeklarowane w `main`
* [x] `10`
* [ ] `0`
* [ ] Nic, bo `f` nie została wywołana

> **Wyjaśnienie:** Preprocesor nie zna funkcji ani zakresów — makro obowiązuje od miejsca `#define` do końca jednostki translacji lub do `#undef`. W `main` nazwa `LIMIT` zostaje więc zastąpiona tekstem `10`.

#### Q. Dlaczego makro `#define KWADRAT(x) ((x) * (x))` nadal nie jest bezpiecznym zamiennikiem funkcji?

* [ ] Nawiasy zmieniają priorytet mnożenia
* [x] Argument może zostać obliczony dwa razy
* [ ] Makro działa wyłącznie dla typu `int`
* [ ] Makro jest rozwijane w czasie działania

> **Wyjaśnienie:** Argument pojawia się w rozwinięciu dwukrotnie, więc wyrażenie z efektem ubocznym, np. `KWADRAT(i++)`, zmienia zmienną dwa razy. Funkcja obliczyłaby argument raz i sprawdziłaby jego typ.

#### Q. Co robi dyrektywa `#error "Musisz zdefiniować WERSJA"`, gdy preprocesor do niej dotrze?

* [ ] Rzuca wyjątek podczas działania programu
* [ ] Wypisuje ostrzeżenie i kontynuuje kompilację
* [x] Przerywa kompilację z podanym komunikatem
* [ ] Definiuje makro `WERSJA` z pustą wartością

> **Wyjaśnienie:** `#error` zatrzymuje przetwarzanie już na etapie preprocesowania i wyświetla komunikat. Zwykle umieszcza się ją w gałęzi kompilacji warunkowej, np. po `#ifndef WERSJA`.

#### Q. Co wypisze ten program w C++ z dzieleniem liczb?

```cpp
#include <iostream>

int main() {
    int a = 9 / 4;
    double b = 9 / 4;
    double c = 9.0 / 4;
    std::cout << a << ' ' << b << ' ' << c << '\n';
}
```

* [x] `2 2 2.25`
* [ ] `2 2.25 2.25`
* [ ] `2.25 2.25 2.25`
* [ ] `2 2.0 2.25`

> **Wyjaśnienie:** `9 / 4` dzieli dwie liczby całkowite i daje `2`; przypisanie do `double` nie zmienia typu działania wstecz. Dopiero `9.0` sprawia, że dzielenie jest zmiennoprzecinkowe. `std::cout` wypisuje `double` o wartości 2 jako `2`.

#### Q. Jak standard C++ traktuje inicjalizację `int pelne{cena};`, gdy `cena` jest zmienną typu `double`?

* [ ] Jako poprawną: część ułamkowa zostaje po cichu obcięta
* [x] Jako błąd: klamry zabraniają konwersji zawężającej
* [ ] Jako poprawną: wartość zostaje zaokrąglona
* [ ] Jako błąd: `int` nie może mieć inicjalizatora

> **Wyjaśnienie:** Inicjalizacja klamrowa odrzuca konwersje mogące utracić dane, np. z `double` do `int`. GCC zgłasza to domyślnie jako ostrzeżenie `-Wnarrowing`, ale według standardu taki kod jest niepoprawny.

#### Q. Co wypisze ten program w C++ z lokalną zmienną `static`?

```cpp
#include <iostream>

void pokaz_licznik() {
    static int licznik{0};
    ++licznik;
    std::cout << licznik << ' ';
}

int main() {
    pokaz_licznik();
    pokaz_licznik();
    pokaz_licznik();
    std::cout << '\n';
}
```

* [ ] `1 1 1`
* [x] `1 2 3`
* [ ] `0 1 2`
* [ ] `3 3 3`

> **Wyjaśnienie:** Lokalna zmienna `static` jest inicjalizowana raz i istnieje przez cały czas działania programu, więc zachowuje wartość między wywołaniami. Jej nazwa pozostaje jednak widoczna tylko w funkcji.

#### Q. Które zdanie poprawnie opisuje różnicę między `const` a `constexpr` w C++?

* [ ] `const` wymaga wartości znanej podczas kompilacji, a `constexpr` nie
* [x] `constexpr` wymaga wartości z kompilacji, `const` tylko zakazuje zmian
* [ ] Oba słowa znaczą to samo i można je dowolnie zamieniać
* [ ] `constexpr` pozwala zmieniać wartość, a `const` nie pozwala

> **Wyjaśnienie:** `constexpr` wymaga wartości obliczalnej podczas kompilacji i zawsze oznacza stałą. `const` tylko zabrania późniejszego przypisania — wartość może pochodzić np. z danych wczytanych w czasie działania.

#### Q. Która z tych nazw nie może być nazwą zmiennej w C ani w C++?

* [ ] `liczba_dni`
* [ ] `sredniaTemperatura`
* [x] `2gi_wynik`
* [ ] `wynik2`

> **Wyjaśnienie:** Nazwa może zawierać litery, cyfry i podkreślenie, ale nie może zaczynać się od cyfry. Cyfra na końcu, jak w `wynik2`, jest dozwolona.

#### Q. Co wypisze ten program w C++ z wartością typu `bool`?

```cpp
#include <iostream>

int main() {
    bool pelnoletnia = 20 >= 18;
    std::cout << pelnoletnia << ' ' << std::boolalpha << pelnoletnia << '\n';
}
```

* [x] `1 true`
* [ ] `true true`
* [ ] `1 1`
* [ ] `true 1`

> **Wyjaśnienie:** Domyślnie `std::cout` wypisuje `bool` jako `1` lub `0`. Manipulator `std::boolalpha` przełącza strumień na słowa `true` i `false` dla kolejnych wartości.

#### Q. Co wypisze ten program w C z odejmowaniem wartości `unsigned int`?

```c
#include <stdio.h>

int main(void) {
    unsigned int a = 3;
    unsigned int b = 5;
    if (a - b < 10) {
        puts("mała");
    } else {
        puts("duża");
    }
    return 0;
}
```

* [ ] `mała`
* [x] `duża`
* [ ] Program nie skompiluje się
* [ ] Nic — zachowanie jest niezdefiniowane

> **Wyjaśnienie:** Arytmetyka bez znaku jest wykonywana modulo zakres typu, więc `3 - 5` nie daje `-2`, tylko bardzo dużą dodatnią wartość (`UINT_MAX - 1`). To zachowanie dobrze zdefiniowane, ale łatwo o pomyłkę.

#### Q. Co standard C i C++ mówi o rozmiarze typu `int`?

* [ ] Zawsze zajmuje dokładnie 4 bajty
* [ ] Zawsze ma tyle bajtów co wskaźnik
* [x] Zależy od implementacji; ustalono tylko minimalny zakres
* [ ] Zawsze zajmuje dokładnie 2 bajty

> **Wyjaśnienie:** Rozmiary typów całkowitych zależą od implementacji, a standard określa wymagania minimalne. Na typowych platformach 64-bitowych `int` ma 4 bajty, ale nie wolno zakładać tego wszędzie — sprawdzisz to przez `sizeof(int)`.

#### Q. Co można powiedzieć o odczycie lokalnej zmiennej `int wynik;`, której nie przypisano żadnej wartości?

* [ ] Zawsze ma wartość `0`
* [ ] Zawsze ma wartość `-1`
* [x] Nie ma wartości, której można bezpiecznie użyć
* [ ] Kompilator zawsze odrzuci taki program

> **Wyjaśnienie:** Lokalna zmienna bez inicjalizacji nie otrzymuje wartości domyślnej, a jej odczyt jest błędem programu. Kompilator może o tym ostrzec, ale nie musi; najlepiej od razu pisać np. `int wynik{0};`.

#### Q. Co wypisze ten program w C++ z dwiema zmiennymi o nazwie `x`?

```cpp
#include <iostream>

int main() {
    int x = 1;
    {
        int x = 2;
        std::cout << x << ' ';
    }
    std::cout << x << '\n';
}
```

* [x] `2 1`
* [ ] `2 2`
* [ ] `1 1`
* [ ] Błąd kompilacji: powtórzona nazwa `x`

> **Wyjaśnienie:** Wewnętrzny blok tworzy nową zmienną `x`, która przesłania zewnętrzną tylko do końca bloku. Po nim nazwa `x` znów oznacza zmienną z wartością `1`.

#### Q. Czym w C++ różni się zapis `'A'` od zapisu `"A"`?

* [ ] Niczym — oba oznaczają pojedynczy znak
* [x] `'A'` to jeden `char`, a `"A"` to tablica znaków z `'\0'`
* [ ] `'A'` to tekst, a `"A"` to kod ASCII litery
* [ ] `"A"` to `std::string`, a `'A'` to liczba `int`

> **Wyjaśnienie:** Apostrofy tworzą pojedynczy znak, a cudzysłów literał tekstowy: tablicę zawierającą `'A'` i końcowe `'\0'`. Literał można zapisać w `std::string`, ale sam nie jest obiektem tej klasy.

#### Q. Którego specyfikatora należy użyć w `scanf`, aby wczytać wartość do zmiennej typu `double`?

* [ ] `%f`
* [x] `%lf`
* [ ] `%Lf`
* [ ] `%d`

> **Wyjaśnienie:** W `scanf` `%f` oczekuje adresu `float`, `%lf` adresu `double`, a `%Lf` adresu `long double`. W `printf` oba typy wypisuje się przez `%f`, bo `float` jest tam przekazywany jako `double`.

#### Q. Co wypisze ten program w C, gdy użytkownik wpisze `12 abc`?

```c
#include <stdio.h>

int main(void) {
    int a = 0;
    int b = 0;
    int ile = scanf("%d %d", &a, &b);
    printf("%d %d\n", ile, a);
    return 0;
}
```

* [ ] `2 12`
* [x] `1 12`
* [ ] `0 0`
* [ ] `-1 12`

> **Wyjaśnienie:** `scanf` zwraca liczbę udanych konwersji. Pierwsza liczba została odczytana, a przy `abc` konwersja `%d` się nie powiodła, więc wynik to `1`. `EOF` (`-1`) oznaczałby brak danych przed pierwszą konwersją.

#### Q. Po co w wywołaniu `scanf(" %c", &litera)` umieszcza się spację przed `%c`?

* [x] Aby pominąć białe znaki, np. pozostały znak nowego wiersza
* [ ] Aby odczytać dokładnie jedną spację przed literą
* [ ] Aby zabezpieczyć bufor przed przepełnieniem
* [ ] Aby zamienić literę na wielką

> **Wyjaśnienie:** Po wcześniejszym odczycie liczby w strumieniu zwykle zostaje `'\n'`, które samo `%c` odczytałoby jako znak. Spacja w formacie każe najpierw pominąć dowolną liczbę białych znaków.

#### Q. Co wypisze ten program w C, gdy użytkownik wpisze `Ala` i naciśnie Enter?

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char bufor[100];
    if (fgets(bufor, sizeof bufor, stdin) == NULL) {
        return 1;
    }
    size_t przed = strlen(bufor);
    bufor[strcspn(bufor, "\n")] = '\0';
    printf("%zu %zu\n", przed, strlen(bufor));
    return 0;
}
```

* [ ] `3 3`
* [x] `4 3`
* [ ] `4 4`
* [ ] `3 2`

> **Wyjaśnienie:** `fgets` zapisuje także znak nowego wiersza, jeśli zmieści się w buforze, więc początkowo tekst ma 4 znaki. `strcspn` znajduje pozycję `'\n'`, a wpisanie tam `'\0'` skraca tekst do 3 znaków.

#### Q. Co wypisze ten program w C++, gdy użytkownik wpisze `20`, naciśnie Enter, a potem wpisze `Jan Kowalski` i naciśnie Enter?

```cpp
#include <iostream>
#include <string>

int main() {
    int wiek;
    std::string imie;
    std::cin >> wiek;
    std::getline(std::cin, imie);
    std::cout << '[' << imie << "]\n";
}
```

* [x] `[]`
* [ ] `[Jan Kowalski]`
* [ ] `[Jan]`
* [ ] `[20]`

> **Wyjaśnienie:** `std::cin >> wiek` zostawia w strumieniu znak końca wiersza, więc `getline` od razu odczytuje pusty wiersz. Przed `getline` trzeba pominąć resztę wiersza, np. przez `std::cin.ignore(...)`.

#### Q. Co wypisze ten program w C++ z manipulatorami `<iomanip>`?

```cpp
#include <iomanip>
#include <iostream>

int main() {
    std::cout << std::fixed << std::setprecision(2) << 12.5 << ' ';
    std::cout << 3.0 << '\n';
}
```

* [ ] `12.50 3`
* [x] `12.50 3.00`
* [ ] `12.5 3`
* [ ] `12.50 3.0`

> **Wyjaśnienie:** `std::fixed` i `std::setprecision(2)` pozostają aktywne dla kolejnych wartości wypisywanych do tego samego strumienia. Dlatego także `3.0` zostaje wypisane z dwiema cyframi po kropce.

#### Q. Program uruchomiono poleceniem `./program > wynik.txt`. Gdzie trafi tekst wypisany przez `std::cerr`?

* [ ] Do pliku `wynik.txt`
* [x] Na terminal, bo przekierowano tylko `stdout`
* [ ] Nigdzie, bo `stderr` zostaje zamknięte
* [ ] Do pliku `wynik.txt.err`

> **Wyjaśnienie:** Operator `>` przekierowuje standardowe wyjście (`stdout`, czyli `std::cout`). `std::cerr` pisze do osobnego strumienia `stderr`, który nadal jest powiązany z terminalem.

#### Q. Co wypisze ten program w C, gdy użytkownik wpisze `Nowy Targ`?

```c
#include <stdio.h>

int main(void) {
    char miasto[50];
    if (scanf("%49s", miasto) != 1) {
        return 1;
    }
    printf("[%s]\n", miasto);
    return 0;
}
```

* [ ] `[Nowy Targ]`
* [x] `[Nowy]`
* [ ] `[Targ]`
* [ ] `[Nowy Targ` bez nawiasu zamykającego

> **Wyjaśnienie:** `%s` kończy odczyt na pierwszym białym znaku, więc do tablicy trafia tylko `Nowy`. Szerokość `49` chroni bufor o rozmiarze 50, zostawiając miejsce na `'\0'`; do całego wiersza służy `fgets`.
