# Operacje bitowe w C i C++

Poprzednia notatka pokazała, że tekst i inne dane są przechowywane w pamięci jako bajty. Bajt składa się z bitów — najmniejszych jednostek, które mają wartość `0` albo `1`. Operacje bitowe pozwalają sprawdzić lub zmienić wybrane bity liczby. Najczęściej używa się ich do flag, masek, pól protokołów i danych sprzętowych.

Do pracy z maskami wybieraj typy całkowite **bez znaku**, np. `uint8_t` lub `uint32_t` z nagłówka `<stdint.h>`. Wartości bez znaku mają przewidywalną reprezentację binarną modulo rozmiaru typu. Dokładne typy takie jak `uint32_t` są dostępne wtedy, gdy implementacja ma typ o dokładnie takiej szerokości.

## Jak czytać zapis binarny

W zapisie binarnym każda pozycja odpowiada potędze dwójki. Czytamy od prawej: pozycje mają wagi `1`, `2`, `4`, `8` i tak dalej. Na przykład ośmiobitowy zapis liczby 13 wygląda tak:

```text
pozycja:  7 6 5 4 3 2 1 0
waga:    128 64 32 16 8 4 2 1
wartość:   0  0  0  0 1 1 0 1  = 8 + 4 + 1 = 13
```

Pozycję bitu liczymy zwykle od zera, zaczynając od prawej strony — to **najmniej znaczący bit**. Wartość `13` ma więc ustawione bity `0`, `2` i `3`.

## AND, OR i XOR na przykładzie

Operatory działają na odpowiadających sobie parach bitów. W tym przykładzie zapisujemy wartości na czterech pozycjach, aby dało się zobaczyć każdą z nich:

```text
           0101   (5)
           0011   (3)
AND  (&)   0001   (1)   jedynka zostaje tylko tam, gdzie obie liczby mają 1
OR   (|)   0111   (7)   jedynka jest tam, gdzie co najmniej jedna liczba ma 1
XOR  (^)   0110   (6)   jedynka jest tam, gdzie liczby mają różne bity
```

Zasada dla pojedynczego bitu jest następująca:

| `a` | `b` | `a & b` | `a \| b` | `a ^ b` |
|---:|---:|---:|---:|---:|
| 0 | 0 | 0 | 0 | 0 |
| 0 | 1 | 0 | 1 | 1 |
| 1 | 0 | 0 | 1 | 1 |
| 1 | 1 | 1 | 1 | 0 |

AND (`&`) wybiera wspólne jedynki, dlatego nadaje się do sprawdzania i izolowania bitów. OR (`|`) łączy ustawione bity, więc nadaje się do włączania flag. XOR (`^`) zmienia bit na przeciwny tylko tam, gdzie maska ma `1`.

Operatory bitowe nie są tym samym co logiczne. `&&`, `||` i `!` służą do wyrażeń prawda/fałsz i zwracają wynik logiczny. `&`, `|` i `^` działają na każdym bicie liczb całkowitych. Zapis `a & b` może więc dać np. `1`, `4` lub `0`, a nie wyłącznie prawdę/fałsz.

## Negacja bitowa: dlaczego trzeba znać szerokość

Operator `~` odwraca **wszystkie** bity typu: każdą jedynkę zmienia w zero, a każde zero w jedynkę. Nie można więc zapisać po prostu „negacją `0101` jest `1010`” bez określenia szerokości. Dla ośmiu bitów:

```text
x       = 00000101
~x      = 11111010
```

W kodzie C/C++ `~` odwraca bity całej wartości typu, a nie tylko tych, które akurat narysowaliśmy. Na przykład `~UINT32_C(5)` ma 32 bity: `11111111 11111111 11111111 11111010`. Przy maskowaniu interesuje nas zwykle skutek operacji, a nie samodzielne wypisanie negowanej maski.

## Maska: wybór i zmiana bitu

**Maska** to liczba, w której jedynki wskazują bity, na których chcemy wykonać operację. Maska dla bitu numer `n` to jedynka przesunięta w lewo o `n` pozycji: `1 << n`. Dla przykładu, maska bitu numer 2 w ośmiobitowym widoku to `00000100`.

Rozważmy `flags = 5`, czyli `00000101`. To mogą być flagi stanu, w których bity `0` i `2` są włączone. Poniższy kod sprawdza, włącza, wyłącza i przełącza flagę. Wypisanie jest szesnastkowe, ale obok każdej operacji rozpisano jej sens na ośmiu bitach.

```c
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    uint32_t flags = UINT32_C(5);       /* dolne bity: 00000101 */
    uint32_t maska_bitu_2 = UINT32_C(1) << 2; /* 00000100 */

    /* Sprawdzenie: 00000101 & 00000100 = 00000100, więc bit jest ustawiony. */
    if ((flags & maska_bitu_2) != 0) {
        puts("Bit 2 jest ustawiony.");
    }

    /* Ustawienie bitu 1: 00000101 | 00000010 = 00000111. */
    flags |= UINT32_C(1) << 1;
    printf("Po ustawieniu bitu 1: 0x%08" PRIX32 "\n", flags);

    /* Wyzerowanie bitu 2: 00000111 & 11111011 = 00000011. */
    flags &= ~maska_bitu_2;
    printf("Po wyzerowaniu bitu 2: 0x%08" PRIX32 "\n", flags);

    /* Przełączenie bitu 0: 00000011 ^ 00000001 = 00000010. */
    flags ^= UINT32_C(1);
    printf("Po przełączeniu bitu 0: 0x%08" PRIX32 "\n", flags);
    return 0;
}
```

Każdy zapis ma określoną rolę:

- `(flags & maska) != 0` sprawdza, czy co najmniej jeden bit wskazany maską jest włączony. Dla maski jednego bitu jest to sprawdzenie tego bitu.
- `flags |= maska` włącza bity z maski, nie wyłączając pozostałych.
- `flags &= ~maska` wyłącza bity z maski. Negacja daje jedynki poza wskazanymi miejscami, a AND zachowuje pozostałe bity `flags`.
- `flags ^= maska` przełącza wskazane bity: `0` staje się `1`, a `1` staje się `0`.

To są wzorce aktualizacji flag. Przed użyciem maski trzeba wiedzieć, ile bitów ma typ i czy numer bitu mieści się w tym zakresie.

## Przesunięcia bitowe i typowe pułapki

Przesunięcie w lewo `x << n` przenosi bity `x` o `n` miejsc w stronę bardziej znaczących pozycji, wprowadzając z prawej zera. Dla wartości bez znaku `5` na czterech bitach:

```text
00000101 << 2  = 00010100
5 * 4          = 20
```

Przesunięcie w prawo wartości bez znaku usuwa najmniej znaczące bity, a z lewej wprowadza zera. Dla nieujemnych liczb całkowitych `20 >> 2` daje `5`. Można to rozumieć jako dzielenie całkowite przez `2^n`, o ile mówimy o wartości bez znaku.

Nie używaj przesunięcia jako „sprytnego mnożenia” bez powodu — współczesny kompilator potrafi zoptymalizować zwykłe mnożenie. Przesunięcie jest przede wszystkim sposobem budowania i rozpakowywania pól bitowych.

W C i C++ liczba przesunięć musi być nieujemna i mniejsza od szerokości typu po całkowitych promocjach. Przesunięcie o szerokość typu lub więcej ma niezdefiniowane zachowanie. Nie przesuwaj też dodatniej liczby ze znakiem w lewo tak, by wynik nie mieścił się w typie. Do masek twórz jedynkę jako bez znaku, na przykład `UINT32_C(1) << n`, a przed przesunięciem sprawdzaj `n < 32`.

Przesunięcia wartości ujemnych ze znakiem są mniej przenośne i bywają zależne od typu oraz standardu. Jeśli operujesz na bitach, przechowuj dane w typie bez znaku. W ten sposób unikniesz mylenia reprezentacji liczby ujemnej z regułami arytmetycznymi.

## Bajty i tablica bitowa

Osiem flag logicznych można przechować w jednym bajcie. W większej tablicy numer bitu rozbijamy na dwie wartości: `indeks / 8` wskazuje bajt, a `indeks % 8` — bit wewnątrz tego bajtu.

```c
#include <stdint.h>
#include <stdio.h>

#define LICZBA_BITOW 1024

int main(void) {
    uint8_t bity[LICZBA_BITOW / 8] = {0};
    unsigned indeks = 100;

    if (indeks >= LICZBA_BITOW) {
        return 1; /* nie wolno wyjść poza tablicę */
    }

    unsigned numer_bajtu = indeks / 8;   /* 100 / 8 = 12 */
    unsigned pozycja = indeks % 8;       /* 100 % 8 = 4 */
    uint8_t maska = (uint8_t)(1u << pozycja); /* 00010000 */

    bity[numer_bajtu] |= maska; /* ustaw bit 4 w bajcie nr 12 */
    if ((bity[numer_bajtu] & maska) != 0) {
        puts("Bit 100 jest ustawiony.");
    }
    return 0;
}
```

Indeks `100` oznacza tu bit numer `4` w trzynastym bajcie, bo liczenie bajtów zaczyna się od zera. Sama tablica zajmuje `1024 / 8 = 128` bajtów. Najpierw sprawdzamy zakres indeksu, bo poprawne obliczenie maski nie ochroni przed dostępem poza tablicę.

## Jedna ustawiona jedynka: potęga dwójki

Dodatnia potęga dwójki ma dokładnie jeden bit ustawiony: `1` to `0001`, `2` to `0010`, `4` to `0100`, `8` to `1000`. Wyrażenie `x & (x - 1)` zeruje najmniej znaczący ustawiony bit. Dla `x = 8`:

```text
x       = 1000
x - 1   = 0111
x & (x - 1) = 0000
```

Jeśli `x` miało więcej niż jedną jedynkę, po wyzerowaniu jednej zostanie jeszcze inna. Dlatego dla wartości bez znaku wynik równy zero oznacza, że niezerowe `x` jest potęgą dwójki:

```c
#include <stdbool.h>
#include <stdint.h>

bool czy_potega_dwojki(uint32_t x) {
    return x != 0 && (x & (x - 1)) == 0;
}
```

Warunek `x != 0` jest konieczny: zero także spełniałoby samo równanie `x & (x - 1) == 0`, ale zero nie jest dodatnią potęgą dwójki.

## Kiedy operacje bitowe są przydatne

Flagi są użyteczne, gdy wiele niezależnych informacji logicznych trzeba trzymać razem, np. stany połączenia: „aktywny”, „zaszyfrowany”, „oczekuje na potwierdzenie”. Maski służą do odczytu lub zmiany wybranej informacji bez zmieniania pozostałych. Tablice bitowe oszczędzają pamięć, gdy trzeba przechować tysiące wartości prawda/fałsz. Protokoły i formaty plików również często opisują znaczenie poszczególnych bitów bajtu.

Operacje XOR spotyka się w prostych sumach kontrolnych, ale taka suma nie jest skrótem kryptograficznym: nie chroni danych przed celowym fałszerstwem. Nie twórz własnych funkcji kryptograficznych przez składanie kilku operatorów bitowych. Do bezpieczeństwa używaj sprawdzonych bibliotek.

## Od bajtów do obiektów

Operacje bitowe opisują, jak odczytać lub zmienić reprezentację liczby, a nie co ta liczba oznacza w programie. Jeśli bajty i flagi mają tworzyć jeden sensowny element, np. wiadomość z treścią, statusem i operacjami zmiany statusu, warto ująć je w typ złożony. W C może to być `struct`, a w C++ klasa może dodatkowo ukryć szczegóły reprezentacji i udostępnić tylko poprawne operacje. To przejście — od surowych wartości do danych z odpowiedzialnością i regułami — jest tematem następnej notatki.
