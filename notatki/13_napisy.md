# Napisy w C i C++

Program często pobiera tekst, przechowuje go, porównuje i wyświetla. Zanim wybierzesz funkcję do pracy z tekstem, trzeba rozróżnić trzy rzeczy: **znak** (np. `A`), jego **zapis w pamięci** (jeden lub kilka bajtów) oraz **napis** (ciąg znaków w określonej reprezentacji). To rozróżnienie wyjaśnia, dlaczego długość tablicy nie zawsze jest długością tekstu i dlaczego C oraz C++ oferują różne narzędzia.

## Napis w C: znaki, bufor i terminator

W C nie ma wbudowanego osobnego typu napisu. Napis C to umowa: funkcja otrzymuje adres pierwszego elementu tablicy `char`, a koniec tekstu rozpoznaje po bajcie o wartości zero, zapisywanym jako `\0`. Taki ciąg nazywa się **napisem zakończonym zerem** (C-string).

```c
char napis[] = "Ala ma kota";
const char *literał = "Ala ma kota";
```

Pierwsza deklaracja tworzy tablicę i kopiuje do niej znaki literału razem z terminatorem. Tekst `Ala ma kota` ma 11 bajtów w zwykłym kodowaniu ASCII/UTF-8, a tablica ma **12 elementów**: 11 bajtów tekstu oraz końcowy `\0`. Można zmieniać elementy tablicy `napis`, dopóki nowa zawartość nadal mieści się w jej rozmiarze i zachowuje terminator. Druga deklaracja tworzy wskaźnik do literału; literału nie wolno modyfikować.

Pamiętaj o różnicy między **długością** a **pojemnością bufora**:

- długość napisu to liczba bajtów przed pierwszym `\0`;
- pojemność bufora to liczba wszystkich elementów tablicy, jakie można zapisać;
- zapis tekstu o długości `n` wymaga miejsca na `n + 1` elementów, bo trzeba jeszcze zapisać terminator.

Na przykład, dla napisu `"kot"` `strlen` zwraca `3`, ale tablica musi mieć co najmniej `4` elementy: `'k'`, `'o'`, `'t'`, `\0`. Jeśli funkcja szuka terminatora, a go nie znajduje w dostępnej tablicy, może czytać dalej poza jej granicami. To nie jest tylko błędny wynik — program może odczytać cudze dane albo ulec awarii.

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char napis[] = "kot";
    printf("Tekst: %s\n", napis);
    printf("Długość: %zu bajty\n", strlen(napis));
    printf("Pojemność tablicy: %zu elementy\n", sizeof napis);
    return 0;
}
```

Wyniki długości i pojemności to odpowiednio `3` i `4`. `sizeof napis` działa tu dlatego, że `napis` jest tablicą w tym samym zakresie. Gdy tablica zostanie przekazana do funkcji, jako argument zamieni się na wskaźnik i `sizeof` wskaźnika nie poda rozmiaru bufora. Rozmiar trzeba wtedy przekazać osobno.

### Literał, tablica i wskaźnik to różne rzeczy

Literał tekstowy można skopiować do modyfikowalnej tablicy, ale wskaźnik nie tworzy takiej kopii:

```c
char modyfikowalny[] = "Ala";       /* tablica: 'A', 'l', 'a', '\0' */
const char *tylko_odczyt = "Ala";   /* wskaźnik do literału */

modyfikowalny[0] = 'O';             /* poprawne: teraz "Ola" */
/* tylko_odczyt[0] = 'O'; */        /* nie wolno modyfikować literału */
```

`const` informuje kompilator i czytelnika, że przez ten wskaźnik nie należy zmieniać znaków. To ważne, bo zapis do literału ma niezdefiniowane zachowanie. Z kolei samo `char napis[] = "Ala";` tworzy własną tablicę, którą można zmieniać.

### Długość tekstu a kodowanie

`strlen` liczy bajty przed `\0`, a nie litery widoczne dla człowieka. W UTF-8 wiele liter spoza podstawowego zestawu ASCII zajmuje więcej niż jeden bajt. Na przykład polskie `ą` jest zapisane jako dwa bajty UTF-8. Dlatego dla tekstu `"ą"` `strlen` może zwrócić `2`, mimo że użytkownik widzi jedną literę. Podobnie długość `std::string` oznacza liczbę bajtów, nie liczbę znaków Unicode ani grafemów.

## Funkcje biblioteki C

Standardowe funkcje do napisów są zadeklarowane w `<string.h>`. Przyjmują wskaźniki, więc programista odpowiada za to, by wskazywały na pamięć o właściwym rozmiarze i zawierały poprawnie zakończone napisy.

| Funkcja | Co robi i co trzeba zapewnić |
|---|---|
| `strlen(s)` | Liczy bajty przed `\0`. `s` musi być poprawnym napisem. |
| `strcmp(a, b)` | Porównuje teksty znak po znaku; zwraca liczbę ujemną, zero albo dodatnią. Równość sprawdza się przez `== 0`, nie przez oczekiwanie konkretnej wartości ujemnej lub dodatniej. |
| `strchr(s, c)` | Zwraca wskaźnik do pierwszego wystąpienia znaku `c` albo `NULL`. |
| `strrchr(s, c)` | Zwraca wskaźnik do ostatniego wystąpienia znaku `c` albo `NULL`. |
| `strstr(s, fragment)` | Wyszukuje podnapis i zwraca wskaźnik do jego początku albo `NULL`. |
| `strncmp(a, b, n)` | Porównuje najwyżej `n` początkowych bajtów; nie zastępuje walidacji długości ani kodowania tekstu. |
| `strcpy(dst, src)` | Kopiuje także końcowe `\0`. `dst` musi mieć co najmniej `strlen(src) + 1` elementów, a obszary nie mogą się nakładać. |
| `strcat(dst, src)` | Dopisuje `src` za istniejącym tekstem w `dst`, a potem zapisuje `\0`. Bufor `dst` musi pomieścić oba teksty i terminator; obszary źródła i celu nie mogą się nakładać. |
| `strncpy(dst, src, n)` | Kopiuje najwyżej `n` bajtów. Gdy źródło ma co najmniej `n` bajtów, wynik może nie mieć `\0`; gdy jest krótsze, reszta bufora jest dopełniana zerami. Nie jest to automatycznie bezpieczna wersja `strcpy`. |
| `strncat(dst, src, n)` | Dopisuje najwyżej `n` bajtów ze źródła i dodaje własne `\0`. `dst` musi mieć jeszcze miejsce na istniejący tekst, dopisywany fragment i terminator. |

Przykładowo `strcmp("kot", "kot") == 0`, natomiast wynik dla różnych napisów zależy od pierwszej różniącej się wartości znaku. Nie porównuj wskaźników `a == b`, jeśli chcesz sprawdzić, czy dwa teksty mają tę samą treść: porównanie wskaźników sprawdza, czy wskazują to samo miejsce w pamięci.

Kopiowanie i dopisywanie dobrze pokazują, dlaczego pojemność jest ważna:

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char powitanie[32] = "Witaj, ";
    const char *adresat = "Ala";

    /* 32 elementy wystarczą na oba fragmenty i końcowe '\0'. */
    strcat(powitanie, adresat);
    puts(powitanie); /* Witaj, Ala */
    return 0;
}
```

`strcat` najpierw szuka końcowego `\0` w `powitanie`, a potem kopiuje za nim tekst `adresat` razem z jego terminatorem. Gdyby tablica `powitanie` była za mała, funkcja zapisałaby dane poza nią. Z tego powodu przed kopiowaniem lub dopisywaniem trzeba znać i sprawdzić pojemność bufora. Samo użycie wariantu z literą `n` nie usuwa tego obowiązku.

### Odczyt tekstu do ograniczonego bufora

`fgets` przyjmuje rozmiar tablicy, więc nie zapisze więcej niż się w niej mieści i zakończy wczytany tekst znakiem `\0`. Może jednak wczytać tylko początek dłuższej linii. Poniżej usuwamy znak nowej linii, jeśli został wczytany, i składamy komunikat przez `snprintf`:

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char imie[32];
    if (fgets(imie, sizeof imie, stdin) == NULL) {
        return 1; /* koniec wejścia albo błąd */
    }

    /* strcspn znajduje pozycję '\n'; jeśli jej nie ma, zwraca strlen(imie). */
    imie[strcspn(imie, "\n")] = '\0';

    char komunikat[64];
    int zapisano_by = snprintf(komunikat, sizeof komunikat,
                               "Witaj, %s!", imie);
    if (zapisano_by < 0 || (size_t)zapisano_by >= sizeof komunikat) {
        return 1; /* błąd formatowania albo tekst nie mieści się w buforze */
    }

    puts(komunikat);
    return 0;
}
```

Wartość zwrócona przez `snprintf` to liczba znaków, które powstałyby bez ograniczenia bufora, bez końcowego `\0`. Jeśli ta liczba jest równa lub większa od pojemności tablicy, komunikat został obcięty. W programie produkcyjnym trzeba też rozpoznać zbyt długą linię wczytaną przez `fgets` — na przykład gdy bufor nie zawiera `\n`, mimo że wejście nie dobiegło końca. Funkcja `gets` nie przyjmuje rozmiaru bufora i nie powinna być używana.

### Znaki i konwersja liczb

Funkcje `isdigit`, `isspace`, `toupper` i podobne pochodzą z `<ctype.h>`. Ich argumentem może być `EOF` albo wartość, którą da się zapisać jako `unsigned char`. Zwykły `char` może być ujemny, więc przy przekazaniu go bezpośrednio wynik może być nieokreślony. Bezpieczny wzorzec to:

```c
#include <ctype.h>

if (isdigit((unsigned char)znak)) {
    /* znak jest cyfrą rozpoznawaną w bieżącej lokalizacji */
}
```

Do zamiany tekstu na liczbę używaj raczej `strtol` z `<stdlib.h>` niż `atoi`. `atoi` nie informuje, czy konwersja się nie udała lub czy wynik przekroczył zakres. `strtol` daje dwa sposoby kontroli: `koniec` wskazuje, gdzie kończy się odczytana liczba, a `errno` informuje m.in. o przekroczeniu zakresu.

```c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *tekst = "123abc";
    char *koniec;

    errno = 0;
    long liczba = strtol(tekst, &koniec, 10);

    if (tekst == koniec) {
        puts("Nie znaleziono liczby.");
    } else if (errno == ERANGE) {
        puts("Liczba nie mieści się w typie long.");
    } else if (*koniec != '\0') {
        printf("Po liczbie zostały dodatkowe znaki: %s\n", koniec);
    } else {
        printf("Odczytano: %ld\n", liczba);
    }
}
```

W przykładzie `strtol` odczytuje `123`, a `koniec` wskazuje na `a`. Program nie uznaje więc całego wejścia za liczbę. Jeśli oczekujesz wyłącznie liczby, sprawdzenie `*koniec == '\0'` jest równie ważne jak znalezienie początku liczby. `strtok` dzieli tekst, zastępując separatory znakiem `\0`; modyfikuje więc bufor i przechowuje stan między wywołaniami. Nie wolno stosować jej do literału ani do danych, których nie można zmienić.

## Napis w C++: `std::string`

W C++ najczęściej przechowuje się tekst w `std::string` z nagłówka `<string>`. To obiekt, który pamięta długość i sam zarządza buforem. Kiedy dopisujemy tekst, `std::string` w razie potrzeby powiększa pamięć; programista nie musi ręcznie liczyć miejsca na końcowy `\0`.

```cpp
#include <cstddef>
#include <iostream>
#include <string>

int main() {
    std::string imie = "Ala";
    std::string komunikat = "Witaj, " + imie + "!";

    std::cout << komunikat << '\n';
    std::cout << "Liczba bajtów: " << komunikat.size() << '\n';

    std::size_t pozycja = komunikat.find("Ala");
    if (pozycja != std::string::npos) {
        std::string imie_znalezione = komunikat.substr(pozycja, 3);
        std::cout << "Znaleziono: " << imie_znalezione << '\n';
        komunikat.replace(pozycja, 3, "Ola");
    }
    std::cout << komunikat << '\n';
}
```

W przykładzie `+` tworzy nowy napis, a `find` szuka fragmentu. Jeśli go znajdzie, zwraca pozycję pierwszego bajtu fragmentu. Jeśli go nie znajdzie, zwraca specjalną wartość `std::string::npos`. Dlatego wynik `find` należy sprawdzić przed użyciem. `replace(pozycja, 3, "Ola")` zastępuje trzy bajty od znalezionej pozycji.

`std::string` jest wygodniejszy i zwykle bezpieczniejszy od ręcznie zarządzanej tablicy, lecz nie oznacza to, że każdy dostęp jest sprawdzany. `tekst[i]` wymaga prawidłowego indeksu; `tekst.at(i)` zgłasza wyjątek `std::out_of_range`, gdy indeks jest poza zakresem. `size()` i `length()` zwracają liczbę przechowywanych bajtów. Dla UTF-8 nie muszą zwracać liczby widocznych liter.

`std::string` potrafi przechowywać także bajt `\0` wewnątrz tekstu i nadal pamięta pełną długość. C-string nie ma takiej możliwości w zwykłym użyciu: pierwsze `\0` kończy napis, więc funkcje takie jak `strlen` nie zobaczą dalszej części tablicy. To ważna różnica, gdy przetwarzasz dane binarne — do nich nie używaj funkcji oczekujących C-stringa.

### Konwersje i współpraca z kodem C

W C++11 i nowszym można użyć `std::to_string`, aby zamienić liczbę na napis, a `std::stoi` — aby rozpocząć konwersję z napisu na liczbę. `std::stoi` może zgłosić wyjątek, gdy tekstu nie da się przekonwertować albo liczba wykracza poza zakres `int`. Domyślnie akceptuje też poprawny początek liczby, nawet jeśli po nim zostają inne znaki; gdy wymagany jest cały napis, sprawdź opcjonalny parametr `pos` i upewnij się, że wskazuje koniec tekstu.

```cpp
#include <iostream>
#include <string>

int main() {
    int liczba = 42;
    std::string opis = "Wynik: " + std::to_string(liczba);

    std::string tekst = "123";
    int wartosc = std::stoi(tekst);

    std::cout << opis << '\n';       // Wynik: 42
    std::cout << wartosc + 1 << '\n'; // 124
}
```

Biblioteka C może potrzebować wskaźnika do znaków zakończonych `\0`. `c_str()` daje taki wskaźnik:

```cpp
std::string tekst = "Ala";
const char *dane_dla_c = tekst.c_str();
```

Można go przekazać funkcji C, która tylko odczytuje napis. Nie wolno przez ten wskaźnik zmieniać znaków. Wskaźnik może stracić ważność po zmianie lub zniszczeniu obiektu `tekst`; funkcja C nie powinna przechowywać go dłużej, niż żyje i pozostaje niezmieniony ten obiekt.

### `std::string_view` — widok bez kopii (C++17)

`std::string_view` opisuje fragment już istniejących danych: w uproszczeniu przechowuje adres pierwszego znaku i liczbę znaków. Dzięki temu funkcja może przyjąć tekst do odczytu bez kopiowania całego `std::string`. Widok nie jest właścicielem znaków i nie wydłuża ich czasu życia.

```cpp
#include <iostream>
#include <string>
#include <string_view>

void wypisz(std::string_view tekst) {
    std::cout << tekst << '\n';
}

int main() {
    std::string caly = "To jest napis";
    wypisz(std::string_view(caly).substr(3, 4)); // "jest"
}
```

To wywołanie jest bezpieczne: `caly` istnieje przez całe wywołanie `wypisz`. Nie zwracaj ani nie zapisuj widoku do lokalnego napisu, jeśli napis zaraz przestanie istnieć. Wtedy widok wskazywałby na zwolnioną pamięć.

## Wzorce tekstu i Unicode

Jeśli trzeba szukać tekstu pasującego do wzorca, C++ udostępnia bibliotekę `<regex>`. Wzorzec poniżej szuka wyrażenia „słowo, spacja, `ma`, spacja, słowo”; nawiasy tworzą grupy przechwytywania, które można odczytać jako dopasowane fragmenty:

```cpp
#include <iostream>
#include <regex>
#include <string>

int main() {
    const std::string tekst = "Ala ma kota i psa";
    const std::regex wzorzec(R"((\w+) ma (\w+))");
    std::smatch dopasowanie;

    if (std::regex_search(tekst, dopasowanie, wzorzec)) {
        std::cout << "Osoba: " << dopasowanie[1] << '\n';
        std::cout << "Zwierzę: " << dopasowanie[2] << '\n';
    }
}
```

`regex_search` sprawdza, czy wzorzec występuje gdziekolwiek w napisie; `regex_match` wymagałoby dopasowania całego napisu. Składnia i wydajność wyrażeń regularnych mogą być trudniejsze niż zwykłe `find`, więc do prostego szukania podnapisu wybieraj prostszą metodę.

Kodowanie tekstu jest osobnym zagadnieniem od typu kontenera. `std::string` przechowuje bajty, często UTF-8, ale sam nie wie, gdzie kończy się litera złożona z kilku bajtów. `std::u16string` przechowuje jednostki kodowe UTF-16, a `std::u32string` — jednostki UTF-32; ich `size()` także nie jest ogólną metodą liczenia widocznych znaków. Poprawne dzielenie tekstu na litery, sortowanie językowe i normalizację Unicode zapewniają wyspecjalizowane biblioteki, np. ICU, nie sama klasa `std::string`.

## Jak te pojęcia łączą się z kolejnymi tematami

Tekst w pamięci ma postać bajtów. W C tablica `char` zawiera bajty i terminator `\0`; w C++ `std::string` przechowuje bajty wraz z ich długością. Operacje bitowe z następnej notatki mogą wybrać lub zmienić bity konkretnego bajtu, ale nie zastępują zasad kodowania tekstu. Klasa z notatki o programowaniu obiektowym może z kolei przechowywać `std::string` jako część swojego stanu i udostępniać operacje, które pilnują, jak ten tekst jest używany.
