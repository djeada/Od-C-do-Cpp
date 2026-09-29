# Interakcja z konsolą

Program często musi pokazać użytkownikowi wynik albo poprosić go o dane. Konsola jest jednym ze sposobów takiej komunikacji. Warto myśleć o niej jak o dwóch kierunkach przepływu informacji: program wysyła tekst na zewnątrz, a dane wpisane przez użytkownika trafiają do programu.

System udostępnia programowi trzy standardowe strumienie:

- `stdin` — standardowe wejście; zwykle znaki wpisane przez użytkownika;
- `stdout` — standardowe wyjście; zwykłe komunikaty programu;
- `stderr` — wyjście przeznaczone na błędy i ostrzeżenia.

Strumienie mogą być powiązane z terminalem, ale mogą też zostać przekierowane, na przykład do pliku. Dzięki temu program nie musi wiedzieć, czy jego wynik ogląda człowiek, czy zapisuje go inne narzędzie.

## Wejście i wyjście w C

W C funkcje obsługujące standardowe wejście i wyjście są zadeklarowane w nagłówku `<stdio.h>`. Najczęściej na początku nauki spotkasz `printf` do wypisywania i `scanf` do odczytywania.

### Wypisywanie wartości przez `printf`

`printf` składa tekst z dwóch części: zwykłych znaków oraz specyfikatorów formatu, takich jak `%d`. Każdy specyfikator mówi, jak wypisać odpowiadający mu argument.

```c
#include <stdio.h>

int main(void) {
    int liczba = 12;
    double cena = 3.5;
    char znak = 'A';

    printf("Liczba: %d, cena: %.2f, znak: %c\n", liczba, cena, znak);
    return 0;
}
```

W tym wywołaniu `%d` zastępuje wartość `liczba`, `%.2f` wypisuje `cena` z dwiema cyframi po kropce, a `%c` wstawia znak. `\n` kończy wiersz. Specyfikatory i argumenty muszą do siebie pasować i występować w tej samej kolejności. Niezgodny typ może prowadzić do błędnego wyniku, a w C nawet do niezdefiniowanego działania programu.

Najczęściej używane specyfikatory:

| Specyfikator | `printf` — argument | `scanf` — adres zmiennej |
|---|---|---|
| `%d` | `int` | `int *` |
| `%u` | `unsigned int` | `unsigned int *` |
| `%ld` | `long` | `long *` |
| `%lld` | `long long` | `long long *` |
| `%f` | `float` jest przekazywany jako `double` | `float *` |
| `%lf` | `double` (w `printf` działa jak `%f`) | `double *` |
| `%Lf` | `long double` | `long double *` |
| `%c` | znak przekazany jako `int` | `char *` |
| `%s` | tablica znaków zakończona `\0` | miejsce na tablicę znaków |

Istotna różnica dotyczy liczb zmiennoprzecinkowych: do `printf` zarówno `float`, jak i `double` wypisujemy przez `%f`; do `scanf` dla `float` używamy `%f`, a dla `double` — `%lf`.

### Odczytywanie wartości przez `scanf`

`scanf` próbuje odczytać znaki ze standardowego wejścia i zamienić je na wskazane typy. Żeby funkcja mogła zapisać wynik do zmiennej, dla zwykłych zmiennych przekazujemy jej adres, zapisany operatorem `&`.

```c
#include <stdio.h>

int main(void) {
    int wiek;
    double wzrost;
    char pierwszaLitera;
    char miasto[50];

    printf("Podaj wiek: ");
    if (scanf("%d", &wiek) != 1) {
        fprintf(stderr, "Nie udało się odczytać wieku.\n");
        return 1;
    }

    printf("Podaj wzrost w metrach: ");
    if (scanf("%lf", &wzrost) != 1) {
        fprintf(stderr, "Nie udało się odczytać wzrostu.\n");
        return 1;
    }

    printf("Podaj pierwszą literę imienia: ");
    if (scanf(" %c", &pierwszaLitera) != 1) {
        fprintf(stderr, "Nie udało się odczytać znaku.\n");
        return 1;
    }

    printf("Podaj nazwę miasta bez spacji: ");
    if (scanf("%49s", miasto) != 1) {
        fprintf(stderr, "Nie udało się odczytać nazwy miasta.\n");
        return 1;
    }

    printf("Wiek: %d, wzrost: %.2f m, litera: %c, miasto: %s\n",
           wiek, wzrost, pierwszaLitera, miasto);
    return 0;
}
```

Załóżmy, że użytkownik wpisze kolejno `20`, `1.75`, `A` i `Krakow`. Wywołanie `scanf("%d", &wiek)` odczyta pierwszą liczbę i zapisze ją pod adresem zmiennej `wiek`. Kolejne wywołania wypełnią pozostałe zmienne. Funkcja zwraca liczbę poprawnie odczytanych wartości — dlatego sprawdzenie `!= 1` wykrywa sytuację, w której konwersja jednej wartości się nie udała.

W nazwie tablicy `miasto` nie ma `&`: w tym wywołaniu nazwa tablicy przekazuje adres jej pierwszego elementu. Szerokość `%49s` ogranicza zapis do 49 znaków, zostawiając miejsce na końcowy znak `\0` w tablicy o rozmiarze 50. `%s` kończy odczyt na pierwszym białym znaku, więc ta wersja nie wczyta nazwy zawierającej spacje.

Spacja przed `%c` jest celowa. Po wcześniejszym wpisaniu liczby w strumieniu zwykle zostaje znak końca wiersza. Samo `%c` odczytałoby ten znak, a format `" %c"` najpierw pomija białe znaki, a potem pobiera właściwy znak.

### Odczytywanie całego wiersza w C

Jeśli tekst może zawierać spacje, samo `%s` nie wystarczy. Do wczytania wiersza można użyć `fgets`. Funkcja zapisuje w buforze najwyżej `rozmiar - 1` znaków i dodaje końcowe `\0`.

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    char imie[100];

    printf("Podaj imię i nazwisko: ");
    if (fgets(imie, sizeof imie, stdin) == NULL) {
        fprintf(stderr, "Nie udało się odczytać tekstu.\n");
        return 1;
    }

    imie[strcspn(imie, "\n")] = '\0';
    printf("Witaj, %s!\n", imie);
    return 0;
}
```

`fgets` może zapisać również znak nowego wiersza, jeśli zmieści się w buforze. `strcspn` znajduje jego pozycję, a przypisanie `\0` usuwa go z tekstu. Jeśli wiersz jest dłuższy niż bufor, odczytany zostanie tylko jego początek; większy lub dowolnie długi tekst wymaga dodatkowej obsługi.

### Dlaczego warto sprawdzać wynik odczytu

Zmienne lokalne, którym nie przypisano wartości, nie zawierają bezpiecznej wartości domyślnej. Jeżeli odczyt się nie powiedzie, a program mimo to użyje takiej zmiennej, wynik może być błędny. `scanf` zwraca liczbę poprawnych konwersji, a `fgets` zwraca `NULL`, gdy nie udało się odczytać wiersza. Sprawdź te wyniki przed dalszym użyciem danych.

Gdy `scanf` nie potrafi zamienić tekstu na oczekiwany typ, błędny fragment zwykle pozostaje w strumieniu. Samo ponowne wywołanie `scanf` może wtedy natrafić na ten sam fragment. Powyższe krótkie programy kończą działanie po błędzie; program, który ma ponawiać pytanie, musi dodatkowo usunąć błędny wiersz i dopiero wtedy poprosić o dane ponownie.

## Wejście i wyjście w C++

W C++ do standardowej obsługi wejścia i wyjścia służy nagłówek `<iostream>`. Wypisujemy przez `std::cout`, odczytujemy przez `std::cin`, a komunikaty o błędach kierujemy zwykle do `std::cerr`. Przed nazwami umieszczamy `std::`, ponieważ te obiekty należą do przestrzeni nazw `std`.

Operator `<<` przekazuje wartość do strumienia wyjściowego. Operator `>>` pobiera wartość ze strumienia wejściowego i próbuje zapisać ją w zmiennej. Typ zmiennej określa, jaką wartość ma odczytać.

```cpp
#include <iostream>
#include <string>

int main() {
    std::string imie;
    int wiek;
    double wzrost;

    std::cout << "Podaj imię i nazwisko: ";
    if (!std::getline(std::cin, imie)) {
        std::cerr << "Nie udało się odczytać imienia.\n";
        return 1;
    }

    std::cout << "Podaj wiek: ";
    if (!(std::cin >> wiek)) {
        std::cerr << "Wiek musi być liczbą całkowitą.\n";
        return 1;
    }

    std::cout << "Podaj wzrost w metrach: ";
    if (!(std::cin >> wzrost)) {
        std::cerr << "Wzrost musi być liczbą.\n";
        return 1;
    }

    std::cout << imie << ", wiek: " << wiek
              << ", wzrost: " << wzrost << " m\n";
    return 0;
}
```

`std::getline(std::cin, imie)` odczytuje cały wiersz, więc imię i nazwisko mogą zawierać spację. Z kolei `std::cin >> wiek` pomija początkowe białe znaki i odczytuje wartość pasującą do typu `int`. W wyrażeniu `if (!(std::cin >> wiek))` program najpierw próbuje odczytać liczbę, a następnie sprawdza, czy operacja się powiodła. Jeśli użytkownik wpisze na przykład słowo zamiast liczby, program wypisze błąd na `std::cerr` i zakończy działanie.

### Różnica między `>>` a `getline`

Operator `>>` jest wygodny dla pojedynczych wartości i słów, ale zatrzymuje odczyt tekstu na białym znaku. `std::getline` pobiera cały wiersz aż do znaku nowego wiersza. Połączenie tych metod wymaga uwagi: po `std::cin >> wiek` znak końca wiersza pozostaje w strumieniu. Bez jego pominięcia następujące `getline` może od razu odczytać pusty tekst.

```cpp
#include <iostream>
#include <limits>
#include <string>

int main() {
    int wiek;
    std::string imie;

    std::cout << "Podaj wiek: ";
    if (!(std::cin >> wiek)) {
        std::cerr << "Wiek musi być liczbą całkowitą.\n";
        return 1;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Podaj imię i nazwisko: ";
    std::getline(std::cin, imie);

    std::cout << "Witaj, " << imie << "!\n";
    return 0;
}
```

`ignore` odrzuca znaki aż do końca bieżącego wiersza. `<limits>` jest potrzebny do użycia `std::numeric_limits<std::streamsize>::max()`, czyli maksymalnej liczby znaków, które chcemy pominąć. Nie jest to ogólna metoda „czyszczenia bufora” po każdym wejściu — przydaje się konkretnie wtedy, gdy po odczycie wartości przez `>>` chcemy przejść do odczytu kolejnego wiersza.

### Formatowanie liczb

Nagłówek `<iomanip>` udostępnia manipulatory formatujące. `std::fixed` wybiera zapis dziesiętny o stałej liczbie cyfr po kropce, a `std::setprecision(2)` w tym trybie ustawia dwie cyfry po kropce.

```cpp
#include <iostream>
#include <iomanip>

int main() {
    double cena = 12.5;

    std::cout << "Domyślnie: " << cena << '\n';
    std::cout << "Do dwóch miejsc: "
              << std::fixed << std::setprecision(2) << cena << '\n';
    return 0;
}
```

Manipulatory takie jak `std::fixed` pozostają aktywne dla kolejnych wartości wypisywanych do tego samego strumienia. Jeśli później potrzebujesz innego formatu, ustaw go jawnie.

## Co jest wspólne, a co różni C i C++?

Oba języki korzystają ze standardowych strumieni wejścia i wyjścia, ale udostępniają inne podstawowe interfejsy. W C typ i sposób zapisu danych określamy specyfikatorem formatu funkcji `printf` lub `scanf`. W C++ operatory strumieniowe dobierają obsługę do typu wartości, a tekst wygodnie przechowujemy w `std::string`. Nie mieszaj tych interfejsów bez konkretnego powodu — łatwiej wtedy zrozumieć, skąd pochodzą dane i jak są formatowane.

## Kolorowanie tekstu — temat dodatkowy

Niektóre terminale rozpoznają kody ANSI. Poniższy kod prosi terminal o czerwony tekst, a następnie przywraca domyślny styl:

```cpp
#include <iostream>

int main() {
    std::cout << "\033[1;31mCzerwony tekst\033[0m\n";
    return 0;
}
```

Obsługa kodów zależy od terminala i systemu. Na Windows istnieje też systemowe API (nagłówek `<windows.h>`), ale jest ono specyficzne dla tej platformy. Kolor nie należy do podstawowej obsługi wejścia i wyjścia — program powinien pozostać zrozumiały również wtedy, gdy terminal nie obsługuje kolorów.
