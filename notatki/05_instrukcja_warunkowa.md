# Instrukcje warunkowe

Do tej pory program mógł wypisać tekst lub odczytać dane, ale instrukcje wykonywały się zawsze w tej samej kolejności. Instrukcja warunkowa pozwala wybrać dalsze działanie na podstawie wartości danych: program oblicza warunek, a potem wykonuje odpowiednią gałąź.

W przykładach używamy C++, dlatego programy wypisujące tekst dołączają `<iostream>`. `if`, `else`, operatory porównań i logika wyboru występują również w C; różnice językowe, na przykład obsługa wejścia i wyjścia, opisujemy osobno.

## Najprostszy wybór: `if`

Instrukcja `if` wykonuje swój blok tylko wtedy, gdy warunek jest prawdziwy. Jeśli jest fałszywy, program omija blok i idzie dalej.

```cpp
#include <iostream>

int main() {
    int temperatura = 25;

    if (temperatura > 20) {
        std::cout << "Jest ciepło.\n";
    }

    std::cout << "Program działa dalej.\n";
    return 0;
}
```

Program porównuje `temperatura` z `20`. Ponieważ `25 > 20` jest prawdą, wypisuje „Jest ciepło.”. Następnie wykonuje instrukcję znajdującą się za blokiem `if`. Gdyby temperatura wynosiła `18`, ominąłby tylko komunikat o cieple; reszta programu nadal by się wykonała.

## Wybór jednej z dwóch dróg: `if` i `else`

Jeśli trzeba obsłużyć oba wyniki, dodaj `else`. Gdy warunek w `if` jest prawdziwy, wykona się pierwszy blok. W przeciwnym razie wykona się blok `else`.

```cpp
#include <iostream>

int main() {
    int liczba = 7;

    if (liczba % 2 == 0) {
        std::cout << "Liczba jest parzysta.\n";
    } else {
        std::cout << "Liczba jest nieparzysta.\n";
    }

    return 0;
}
```

Operator `%` daje resztę z dzielenia całkowitego. Liczba parzysta dzielona przez `2` ma resztę `0`, więc warunek `liczba % 2 == 0` rozstrzyga, który komunikat wybrać. W przykładzie reszta z dzielenia `7` przez `2` wynosi `1`, dlatego wykonywany jest blok `else`.

Nawiasy klamrowe `{}` wyznaczają zakres gałęzi. Nawet gdy w środku jest tylko jedna instrukcja, warto ich używać — wtedy łatwiej zauważyć, które instrukcje zależą od warunku.

## Więcej niż dwa przypadki: `else if`

Gdy możliwych jest kilka wyników, można połączyć `if`, jedno lub więcej `else if` oraz opcjonalne `else`. Warunki są sprawdzane po kolei. Program wykonuje pierwszy blok, którego warunek jest prawdziwy, po czym pomija pozostałe gałęzie.

```cpp
#include <iostream>

int main() {
    int wynik;
    std::cout << "Podaj wynik od 0 do 100: ";
    if (!(std::cin >> wynik)) {
        std::cerr << "Wynik musi być liczbą całkowitą.\n";
        return 1;
    }

    if (wynik < 0 || wynik > 100) {
        std::cout << "Wynik jest poza zakresem.\n";
    } else if (wynik >= 90) {
        std::cout << "Bardzo dobry wynik.\n";
    } else if (wynik >= 50) {
        std::cout << "Wynik zaliczający.\n";
    } else {
        std::cout << "Wynik poniżej progu zaliczenia.\n";
    }

    return 0;
}
```

Najpierw program sprawdza, czy liczba jest poza zakresem. Jeśli nie, sprawdza kolejno progi `90` i `50`. Dla wartości `75` pierwsze porównanie zakresu jest fałszywe, `75 >= 90` też jest fałszywe, ale `75 >= 50` jest prawdziwe — więc wykonywana jest gałąź „zaliczający”. Pozostałe gałęzie są już pomijane.

Kolejność progów ma znaczenie. Gdybyśmy najpierw sprawdzili `wynik >= 50`, wynik `95` także spełniłby ten warunek i nie dotarłby do sprawdzenia progu `90`. W łańcuchu `else if` umieszczaj najpierw warunki, które mają pierwszeństwo lub opisują wyższe progi.

Użyj osobnych instrukcji `if`, gdy decyzje nie wykluczają się wzajemnie i kilka działań może się wykonać. `if`–`else if` wybiera najwyżej jedną gałąź.

## Operatory porównania i wartości logiczne

Porównania tworzą wynik logiczny: prawdę albo fałsz. W C++ typem logicznym jest `bool`, a jego wartości zapisujemy jako `true` i `false`.

| Operator | Znaczenie |
|---|---|
| `==` | równe |
| `!=` | różne |
| `<` | mniejsze |
| `>` | większe |
| `<=` | mniejsze lub równe |
| `>=` | większe lub równe |

Przykład: `wiek >= 18` jest prawdziwy, gdy `wiek` wynosi co najmniej 18. Granice przedziału zapisuj uważnie: `x < 10` nie obejmuje 10, natomiast `x <= 10` już tak.

W C++ wartość `bool` można bezpośrednio podać jako warunek. W warunku akceptowane są też inne typy, które można zamienić na `bool`: zero oznacza fałsz, a wartość różna od zera — prawdę. Zwykle czytelniej napisać `liczba != 0` niż samo `if (liczba)`, bo porównanie pokazuje, co sprawdzamy.

W C typem logicznym jest `_Bool`; nagłówek `<stdbool.h>` udostępnia wygodne nazwy `bool`, `true` i `false` w starszych standardach C. W obu językach warunek instrukcji `if` interpretuje wartość skalarną jako prawdę lub fałsz, ale typy i nazwy związane z wartością logiczną nie są identyczne we wszystkich wersjach języków.

## Łączenie warunków

Czasem decyzja zależy od kilku faktów naraz. Operatory logiczne pozwalają połączyć porównania:

- `&&` — „i”: oba warunki muszą być prawdziwe;
- `||` — „lub”: wystarczy, że prawdziwy jest co najmniej jeden;
- `!` — „nie”: odwraca wartość logiczną.

```cpp
#include <iostream>

int main() {
    int wiek = 20;
    bool maBilet = true;

    if (wiek >= 18 && maBilet) {
        std::cout << "Można wejść.\n";
    }

    if (wiek < 18 || !maBilet) {
        std::cout << "Wejście jest niedostępne.\n";
    }
    return 0;
}
```

W pierwszym warunku obie części muszą być prawdziwe. W drugim wystarczy, że osoba jest niepełnoletnia albo nie ma biletu. Operatory `&&` i `||` stosują krótkie spięcie: jeśli wynik jest już rozstrzygnięty przez lewą część, prawa część nie jest obliczana. Można na tym bezpiecznie polegać, na przykład sprawdzając mianownik przed dzieleniem:

```cpp
#include <iostream>

int main() {
    int mianownik = 3;
    int licznik = 10;

    if (mianownik != 0 && licznik / mianownik > 2) {
        std::cout << "Iloraz jest większy niż 2.\n";
    }
    return 0;
}
```

Nie łącz wielu trudnych porównań w jednym wierszu, jeśli utrudnia to zrozumienie. Podziel je na nazwane wartości logiczne:

```cpp
#include <iostream>

int main() {
    int a = 5;
    int b = 6;
    int c = 7;

    bool wszystkieDodatnie = a > 0 && b > 0 && c > 0;
    bool spelniaNierownosciTrojkata =
        a + b > c && a + c > b && b + c > a;

    if (wszystkieDodatnie && spelniaNierownosciTrojkata) {
        std::cout << "Liczby mogą być długościami boków trójkąta.\n";
    }
    return 0;
}
```

Jeżeli w jednym wyrażeniu mieszasz `&&` i `||`, dodaj nawiasy, aby jasno zaznaczyć grupowanie. Nawiasy ułatwiają czytanie i chronią przed pomyłką w kolejności działań.

## Krótki wybór wartości: operator `?:`

Operator warunkowy `?:` jest wyrażeniem, które wybiera jedną z dwóch wartości. Ma postać `warunek ? wartość_gdy_prawda : wartość_gdy_fałsz`.

```cpp
#include <iostream>

int main() {
    int x = 8;
    int y = 5;
    int wieksza = (x > y) ? x : y;

    std::cout << "Większa liczba: " << wieksza << '\n';
    return 0;
}
```

Najpierw sprawdzany jest warunek `x > y`. Ponieważ jest prawdziwy, całe wyrażenie ma wartość `x`, czyli `8`, a ta wartość zostaje przypisana do `wieksza`. Gdy warunek jest fałszywy, wybrane zostaje `y`. Ten zapis pasuje do krótkiego wyboru wartości; rozbudowane działania lepiej zapisać w zwykłym `if`–`else`.

## Typowe pomyłki

### Przypisanie `=` a porównanie `==`

Pojedynczy znak `=` przypisuje wartość do zmiennej. Podwójny `==` porównuje dwie wartości. Pomyłka może być poprawna składniowo, ale zmienia program:

```cpp
#include <iostream>

int main() {
    int x = 5;

    if (x = 10) { // Błędny warunek: zmienia x na 10.
        std::cout << "Ta gałąź się wykona, bo 10 oznacza prawdę.\n";
    }

    if (x == 10) { // Porównanie: nie zmienia x.
        std::cout << "x jest równe 10.\n";
    }
    return 0;
}
```

Wartość przypisania jest zarazem wartością całego wyrażenia. Ponieważ `10` oznacza prawdę w warunku, błędna gałąź się wykona. Kompilator często ostrzega o takim zapisie — nie ignoruj ostrzeżeń.

### Za szeroki warunek na początku

W łańcuchu `else if` późniejsze warunki mogą stać się nieosiągalne:

```cpp
#include <iostream>

int main() {
    int x = 10;

    if (x > 5) {
        std::cout << "x jest większe niż 5.\n";
    } else if (x > 8) {
        std::cout << "x jest większe niż 8.\n";
    }
    return 0;
}
```

Jeżeli gałęzie opisują progi, sprawdzaj najpierw próg wyższy. Jeżeli warunki są niezależne, zamiast `else if` użyj osobnych `if`.

### Średnik po `if`

Nie wstawiaj średnika bezpośrednio po warunku. Średnik sam jest pustą instrukcją, więc poniższy `if` nie steruje blokiem w nawiasach klamrowych:

```cpp
#include <iostream>

int main() {
    int liczba = -2;

    if (liczba > 0); // Ta instrukcja kończy się tutaj.
    {
        std::cout << "Ten blok wykona się niezależnie od liczby.\n";
    }
    return 0;
}
```

Blok `{ ... }` jest osobnym blokiem, a nie częścią `if`. Zostaw warunek bez średnika i obejmij nawiasami klamrowymi dokładnie te instrukcje, które mają zależeć od jego wyniku.

### Porównywanie liczb zmiennoprzecinkowych

Liczby `float` i `double` są przechowywane z ograniczoną precyzją. Obliczenie, które matematycznie powinno dać na przykład `0.3`, może mieć minimalnie inną reprezentację. Dlatego równość `==` bywa niewłaściwa do sprawdzania wyniku obliczeń zmiennoprzecinkowych. Często sprawdza się, czy różnica mieści się w tolerancji:

```cpp
#include <cmath>
#include <iostream>

int main() {
    double suma = 0.1 + 0.2;
    const double tolerancja = 1e-9;

    if (std::abs(suma - 0.3) < tolerancja) {
        std::cout << "Suma jest w przybliżeniu równa 0.3.\n";
    }
}
```

Tolerancję dobiera się do skali i znaczenia obliczeń; `1e-9` nie jest uniwersalną wartością dla każdego programu.

### Zmiana wartości ukryta w warunku

Wyrażenie `x++` zwraca najpierw starą wartość `x`, a potem zwiększa zmienną. Taki efekt uboczny w warunku jest trudny do zauważenia:

```cpp
#include <iostream>

int main() {
    int x = 5;
    if (x++ > 5) {
        std::cout << "Warunek jest prawdziwy.\n";
    }
    std::cout << "x ma teraz wartość " << x << ".\n";
    return 0;
}
```

W prostych instrukcjach czytelniej jest oddzielić zmianę zmiennej od sprawdzania warunku.

## Wybór spośród stałych przypadków: `switch`

`switch` przydaje się, gdy porównujemy jedną wartość z kilkoma konkretnymi stałymi. W C++ wyrażenie `switch` może mieć typ całkowity, znakowy albo wyliczeniowy; nie służy do bezpośredniego sprawdzania przedziałów ani tekstu `std::string`.

```cpp
#include <iostream>

int main() {
    int dzien;
    std::cout << "Podaj numer dnia (1-7): ";
    if (!(std::cin >> dzien)) {
        std::cerr << "Numer dnia musi być liczbą całkowitą.\n";
        return 1;
    }

    switch (dzien) {
        case 1:
            std::cout << "Poniedziałek\n";
            break;
        case 2:
            std::cout << "Wtorek\n";
            break;
        case 3:
            std::cout << "Środa\n";
            break;
        case 4:
            std::cout << "Czwartek\n";
            break;
        case 5:
            std::cout << "Piątek\n";
            break;
        case 6:
            std::cout << "Sobota\n";
            break;
        case 7:
            std::cout << "Niedziela\n";
            break;
        default:
            std::cout << "Numer musi być z zakresu 1-7.\n";
    }

    return 0;
}
```

Program porównuje `dzien` z kolejnymi etykietami `case`. Po znalezieniu pasującej wartości wykonuje instrukcje tej gałęzi. `break` kończy `switch`; bez niego wykonanie przechodzi dalej, także do instrukcji pod następnym `case`. `default` jest opcjonalną gałęzią dla wartości, które nie pasują do żadnego przypadku. Do sprawdzania przedziału, takiego jak „od 1 do 7”, użyj `if`.

## Wspólna część po wyborze

Jeżeli po wybraniu gałęzi program ma wykonać tę samą czynność, umieść ją po całym `if`–`else`, zamiast kopiować ją do obu bloków:

```cpp
#include <iostream>

int main() {
    int x = 12;
    if (x > 10) {
        std::cout << "x jest większe niż 10\n";
    } else {
        std::cout << "x nie jest większe niż 10\n";
    }

    std::cout << "Ten komunikat pojawi się w obu przypadkach.\n";
    return 0;
}
```

W ten sposób decyzja wybiera tylko różny komunikat, a wspólna instrukcja uruchamia się po niej niezależnie od wyniku.
