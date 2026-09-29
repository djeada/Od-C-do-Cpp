# Funkcje: wydzielanie kodu i przekazywanie danych

Poprzednia notatka pokazała, jak opisać możliwe kategorie za pomocą `enum class`. Gdy program ma wykonać działanie na danych — na przykład sklasyfikować wynik rzutu kostką — warto zamknąć tę czynność w **funkcji**. Funkcje pomagają nazwać zadanie, uniknąć powtarzania kodu i oddzielić szczegóły wykonania od miejsca, w którym korzystamy z wyniku.

## Z czego składa się funkcja?

Funkcja ma nazwę, typ wyniku i listę parametrów. **Parametry** są zmiennymi, które funkcja dostaje do pracy. Przy wywołaniu podajemy **argumenty** — konkretne wartości przekazywane do parametrów.

```cpp
int dodaj(int lewa, int prawa) {
    return lewa + prawa;
}
```

W tej definicji:

- `int` przed nazwą oznacza, że funkcja zwraca liczbę całkowitą;
- `dodaj` jest nazwą, pod którą można wywołać funkcję;
- `int lewa` i `int prawa` to parametry;
- `return lewa + prawa;` oblicza i przekazuje wynik z powrotem do miejsca wywołania.

Funkcję wywołujemy, podając argumenty w nawiasach:

```cpp
int suma = dodaj(4, 7);
```

Podczas tego wywołania parametr `lewa` otrzymuje wartość `4`, a parametr `prawa` — `7`. Funkcja oblicza `11`, a `return` przekazuje tę wartość do przypisania zmiennej `suma`. Typ argumentu musi być zgodny z typem parametru albo dać się do niego poprawnie skonwertować.

## Funkcja zwracająca wynik

Poniższy kompletny program pokazuje przepływ danych od zmiennych w `main`, przez argumenty i parametry, aż do wyniku zwróconego przez funkcję:

```cpp
#include <iostream>

int poleProstokata(int szerokosc, int wysokosc) {
    return szerokosc * wysokosc;
}

int main() {
    int szerokosc = 5;
    int wysokosc = 3;

    int pole = poleProstokata(szerokosc, wysokosc);
    std::cout << "Pole: " << pole << '\n';
}
```

Wynik programu to `Pole: 15`. W chwili wywołania `szerokosc` z `main` trafia jako argument do parametru `szerokosc` funkcji, a `wysokosc` — do parametru `wysokosc`. Funkcja zwraca iloczyn, który zostaje zapisany w zmiennej `pole` w `main`.

`return` kończy bieżące wywołanie funkcji. Nie kończy całego programu, chyba że wykonanie jest właśnie w `main`. Funkcja z typem wyniku innym niż `void` powinna zwrócić wartość zgodną z tym typem na każdej ścieżce wykonania. Jeśli na przykład funkcja może wejść w dwa różne warunki, trzeba sprawdzić, czy oba prowadzą do `return`.

## Funkcja `void`, czyli działanie bez wyniku

Czasem funkcja ma wykonać czynność, ale nie ma obliczać wartości do zwrócenia. Wtedy jej typem wyniku jest `void`:

```cpp
#include <iostream>
#include <string>

void wypiszImie(const std::string& imie) {
    std::cout << "Imię: " << imie << '\n';
}

int main() {
    std::string osoba = "Karol";
    wypiszImie(osoba);
}
```

Funkcja `wypiszImie` wykonuje wypisywanie, ale nie przekazuje wyniku do przypisania. W funkcji `void` można napisać samo `return;`, aby zakończyć ją wcześniej, na przykład po wykryciu sytuacji, w której dalsza praca nie ma sensu. Nie można natomiast zwrócić z niej wartości, takiej jak `return 5;`.

## Deklaracja a definicja

**Definicja** funkcji zawiera jej ciało, czyli instrukcje do wykonania. **Deklaracja** informuje kompilator o nazwie, typie wyniku i typach parametrów, ale nie zawiera ciała. Deklaracja przed `main` pozwala wywołać funkcję, której definicja znajduje się później:

```cpp
#include <iostream>

void przywitaj(); // deklaracja: funkcja nie przyjmuje argumentów i niczego nie zwraca

int main() {
    przywitaj(); // kompilator zna już jej deklarację
}

void przywitaj() { // definicja z ciałem funkcji
    std::cout << "Cześć!\n";
}
```

Bez wcześniejszej deklaracji kompilator nie wie, czym jest `przywitaj`, gdy napotyka wywołanie. W większym projekcie deklaracje umieszcza się zwykle w pliku nagłówkowym (`.h` lub `.hpp`), a definicje w pliku źródłowym (`.c` albo `.cpp`). Deklaracja w nagłówku i definicja w pliku źródłowym muszą opisywać tę samą funkcję.

## Przekazywanie przez wartość

Domyślnie parametr jest przekazywany **przez wartość**: funkcja dostaje własną kopię argumentu. Zmiana parametru nie zmienia zmiennej, z której pochodził argument.

```cpp
#include <iostream>

void pomnozLokalnaKopie(int liczba, int mnoznik) {
    liczba = liczba * mnoznik;
    std::cout << "W funkcji: " << liczba << '\n';
}

int main() {
    int wynik = 2;
    pomnozLokalnaKopie(wynik, 3);
    std::cout << "Po powrocie: " << wynik << '\n';
}
```

Funkcja wypisze `W funkcji: 6`, a `main` potem `Po powrocie: 2`. Parametr `liczba` jest kopią wartości `wynik`, więc przypisanie w funkcji dotyczy tylko kopii. Przekazywanie przez wartość jest prostym i dobrym wyborem dla małych typów, takich jak `int`, gdy funkcja nie ma zmieniać zmiennej wywołującego.

## Referencja w C++: praca na oryginalnej zmiennej

Jeśli funkcja ma zmienić zmienną wywołującego, w C++ może przyjąć parametr przez **referencję**. Znak `&` przy typie parametru oznacza, że parametr jest inną nazwą dla przekazanego obiektu, a nie jego kopią:

```cpp
#include <iostream>

void pomnoz(int& liczba, int mnoznik) {
    liczba = liczba * mnoznik;
}

int main() {
    int wynik = 2;
    pomnoz(wynik, 3);
    std::cout << wynik << '\n'; // 6
}
```

Wywołanie wygląda prawie tak samo jak dla wartości, ale zmiana `liczba` zmienia `wynik`, bo oba zapisy odnoszą się do tego samego obiektu. Używaj takiej referencji, gdy zmiana argumentu jest częścią zadania funkcji; zaznacz to w nazwie lub opisie, żeby efekt wywołania był jasny.

Jeśli funkcja ma tylko odczytać większy obiekt, można przekazać go przez **stałą referencję** `const T&`. Unika się wtedy kopiowania, a `const` nie pozwala tej funkcji zmieniać obiektu przez ten parametr:

```cpp
#include <string>

void wypiszTekst(const std::string& tekst) {
    // Można odczytywać tekst, ale nie można zmienić go przez parametr tekst.
}
```

Dla małych typów, takich jak `int`, przekazanie przez wartość zwykle jest czytelniejsze. Stała referencja jest szczególnie przydatna dla większych obiektów, takich jak `std::string` czy `std::vector`.

## Jak przekazać argument, który ma zostać zmieniony w C?

C nie ma referencji C++ ani składni `int&`. Zamiast niej przekazuje się **wskaźnik** na zmienną. Funkcja otrzymuje adres, a przez `*` odczytuje lub zmienia wartość znajdującą się pod tym adresem:

```c
#include <stdio.h>

void pomnoz(int *liczba, int mnoznik) {
    *liczba = *liczba * mnoznik;
}

int main(void) {
    int wynik = 2;
    pomnoz(&wynik, 3); // &wynik oznacza adres zmiennej wynik
    printf("%d\n", wynik); // 6
    return 0;
}
```

W C parametr `liczba` sam jest przekazywany przez wartość — kopiowany jest adres. Kopia adresu nadal wskazuje jednak na tę samą zmienną `wynik`, więc zapis `*liczba = ...` zmienia oryginalną wartość. Przy funkcjach przyjmujących wskaźniki trzeba umówić się, czy `NULL` jest dozwolony i co wtedy robi funkcja; wskaźnika nie wolno dereferencjonować, jeśli nie wskazuje na prawidłowy obiekt.

## Parametry domyślne w C++

C++ pozwala przypisać parametrowi wartość domyślną. Wywołujący może wtedy pominąć ten argument:

```cpp
int pomnoz(int liczba, int mnoznik = 3) {
    return liczba * mnoznik;
}

int main() {
    int a = pomnoz(4, 5); // podano oba argumenty: wynik 20
    int b = pomnoz(4);    // użyto mnożnika domyślnego: wynik 12
}
```

Parametry z wartościami domyślnymi muszą znajdować się na końcu listy. Gdy jeden parametr ma wartość domyślną, każdy parametr po nim też musi ją mieć, bo argumenty przy wywołaniu podaje się kolejno od lewej. W większym projekcie wartość domyślną zapisuje się zwykle w deklaracji widocznej dla wywołujących, a nie ponownie w definicji. C nie obsługuje domyślnych argumentów — w C trzeba napisać osobną funkcję albo jawnie przekazać wszystkie argumenty.

## Różnice między funkcjami w C i C++

| Możliwość | C | C++ |
| --- | --- | --- |
| Funkcja zwracająca wartość lub `void` | tak | tak |
| Przekazywanie argumentu przez referencję (`T&`) | nie; do modyfikacji używa się wskaźnika (`T*`) | tak |
| Domyślne wartości parametrów | nie | tak |
| Kilka funkcji o tej samej nazwie i różnych parametrach (przeciążanie) | nie | tak |

W obu językach przed wywołaniem funkcji kompilator musi znać jej deklarację. Przenośny zapis funkcji bez parametrów w C to `void funkcja(void);`. W C++ `void funkcja();` oznacza funkcję bez parametrów. W starszych wersjach C `void funkcja();` nie określało listy parametrów, dlatego jawne `void` w nawiasach jest dobrym wyborem, jeśli kod C ma działać także ze starszymi standardami.

Przeciążanie pokazane w tabeli oznacza, że w C++ można zdefiniować kilka funkcji o tej samej nazwie, ale z innymi listami parametrów. Kompilator wybiera wersję pasującą do argumentów:

```cpp
int podwoj(int liczba) {
    return liczba * 2;
}

double podwoj(double liczba) {
    return liczba * 2.0;
}

int main() {
    int calkowity = podwoj(3); // wybiera wersję przyjmującą int
    double rzeczywisty = podwoj(1.5); // wybiera wersję przyjmującą double
}
```

Sama różnica w typie zwracanym nie wystarcza do przeciążenia — kompilator musi móc rozpoznać właściwą wersję na podstawie parametrów. C nie obsługuje przeciążania, więc trzeba użyć różnych nazw, na przykład `podwojInt` i `podwojDouble`.

## Typowe pomyłki

- **Oczekiwanie, że zmiana parametru wartości zmieni argument.** Parametr jest kopią; w C++ użyj referencji, a w C wskaźnika, jeśli taka zmiana ma być zamierzona.
- **Brak `return` w funkcji zwracającej wynik.** Zadbaj o zwrócenie poprawnej wartości na każdej ścieżce wykonania.
- **Mylenie parametrów z argumentami.** Parametry zapisujemy w deklaracji/definicji, a argumenty podajemy w wywołaniu. Typów zwykle nie zapisujemy przy wywołaniu, np. `dodaj(4, 7)`, a nie `dodaj(int 4, int 7)`.
- **Przekazywanie przez niepotrzebną modyfikowalną referencję.** Referencja `T&` pozwala zmienić obiekt; jeśli funkcja tylko go czyta, rozważ `const T&` albo przekazanie małego typu przez wartość.
- **Podanie wartości domyślnej tylko dla wcześniejszego parametru.** Argumenty pomija się od prawej strony, dlatego parametry z wartościami domyślnymi muszą tworzyć końcowy ciąg listy.

## Połączenie generatora, `enum class` i funkcji

W poprzednich notatkach poznaliśmy generator oraz nazwane kategorie. Poniższy przykład łączy te elementy: generator losuje liczbę oczek, funkcja otrzymuje tę liczbę i zwraca jej kategorię, a `enum class` nazywa możliwe kategorie.

```cpp
#include <iostream>
#include <random>

enum class KategoriaRzutu { Niska, Wysoka };

KategoriaRzutu sklasyfikujRzut(int oczka) {
    if (oczka <= 3) {
        return KategoriaRzutu::Niska;
    }
    return KategoriaRzutu::Wysoka;
}

int main() {
    std::mt19937 silnik(12345);
    std::uniform_int_distribution<int> kostka(1, 6);

    int oczka = kostka(silnik); // losowanie dostarcza liczbę od 1 do 6
    KategoriaRzutu kategoria = sklasyfikujRzut(oczka);

    std::cout << "Wypadlo: " << oczka << '\n';
    switch (kategoria) {
        case KategoriaRzutu::Niska:
            std::cout << "To niski wynik.\n";
            break;
        case KategoriaRzutu::Wysoka:
            std::cout << "To wysoki wynik.\n";
            break;
    }
}
```

`sklasyfikujRzut` dostaje `oczka` przez wartość, bo nie musi zmieniać liczby w `main`. Zwraca jedną z nazwanych kategorii, więc jej wywołujący nie musi pamiętać, że na przykład `0` oznacza „niski”, a `1` — „wysoki”. Generator odpowiada za losowanie, enum za znaczenie kategorii, a funkcja za regułę klasyfikacji. Każdy element ma jedno wyraźne zadanie.
