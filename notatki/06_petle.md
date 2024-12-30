## Pętle

Pętle to kluczowe konstrukcje w programowaniu, które pozwalają na wielokrotne wykonanie określonego fragmentu kodu w zależności od ustalonych warunków lub do momentu osiągnięcia konkretnego celu. Dzięki pętlom można automatyzować powtarzalne procesy, co znacznie przyspiesza działanie programów i ułatwia zarządzanie wieloma operacjami jednocześnie. Ich umiejętne wykorzystanie pozwala pisać kod nie tylko bardziej zwięzły, ale też zdecydowanie bardziej czytelny.

W języku C++ (jak i w wielu innych językach programowania) do najpopularniejszych rodzajów pętli należą:

1. **Pętla `for`** – najczęściej stosowana w sytuacjach, gdy z góry znamy liczbę iteracji lub planujemy przechodzić po zakresie liczb, np. indeksach tablicy.
2. **Pętla `while`** – wykorzystywana, gdy nie jesteśmy pewni, ile razy kod powinien zostać powtórzony, ale decydujemy na podstawie warunku logicznego.
3. **Pętla `do-while`** – podobna do `while`, z tą różnicą, że blok kodu wykona się przynajmniej raz, zanim zostanie sprawdzony warunek.

Każdy z tych rodzajów pętli posiada swoją charakterystykę i jest przydatny w nieco innych przypadkach. W praktyce programistycznej często będziesz wybierać rodzaj pętli w zależności od tego, czy warunek przetwarzania znany jest z góry, czy też zależy od zmieniających się w trakcie działania programu danych.

### Pętla `for`

Pętla `for` jest szczególnie przydatna, gdy znamy z góry liczbę powtórzeń danej operacji. Składa się z trzech głównych elementów: inicjalizacji, warunku i operacji po każdej iteracji (zwykle inkrementacji). Ten typ pętli ułatwia też czytelne utrzymanie i aktualizację licznika (zmiennej kontrolnej), ponieważ cały mechanizm liczenia iteracji zawiera się w pojedynczym wierszu.

#### Struktura pętli `for`

```c++
for (inicjalizacja; warunek; inkrementacja) {
    // kod do wykonania w każdej iteracji
}
```

- **inicjalizacja** – zwykle służy do zainicjalizowania zmiennej kontrolnej (np. `int i = 0;`).
- **warunek** – określa moment zakończenia pętli (np. `i < n;`).
- **inkrementacja** – zmiana wartości zmiennej kontrolnej (np. `i++`;).

#### Przykład: wypisanie wszystkich parzystych liczb od 0 do `n`.

```c++
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj liczbę: ";
    std::cin >> n;

    for (int i = 0; i <= n; i++) {
        if (i % 2 == 0)
            std::cout << i << std::endl;
    }

    return 0;
}
```

W powyższym kodzie korzystamy z klasycznego formatu pętli `for`. Pętla startuje od `i = 0` i trwa tak długo, jak długo `i <= n`. Po każdej iteracji wartość `i` zwiększa się o 1. Wewnątrz pętli sprawdzany jest warunek `if (i % 2 == 0)`, który filtruje liczby parzyste.

#### Pętla `for` z różnymi typami danych

```c++
#include <iostream>

int main() {
    for (char c = 'a'; c <= 'z'; c++) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    for (double d = 0.0; d <= 1.0; d += 0.1) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

W tym przykładzie pierwsza pętla przechodzi przez zakres znaków od `'a'` do `'z'`. Każda iteracja wyświetla jeden znak, co pozwala na wypisanie całego alfabetu. Druga pętla wykorzystuje zmienną typu `double`, inkrementując ją o `0.1` w każdej iteracji aż do osiągnięcia wartości `1.0`. Dzięki temu możliwe jest wykonywanie pętli z wartościami zmiennoprzecinkowymi, np. do obliczeń matematycznych lub generowania pewnych sekwencji liczb.

### Pętla `while`

Pętla `while` powtarza blok instrukcji, dopóki podany warunek jest prawdziwy. Jest ona szczególnie użyteczna, gdy nie wiemy z góry, ile razy blok kodu powinien się wykonać. Wystarczy opisać warunek, a pętla będzie działać do momentu, w którym warunek przestanie być spełniony.

#### Struktura pętli `while`

```c++
while (warunek) {
    // kod do wykonania w każdej iteracji
}
```

- **warunek** – wyrażenie logiczne, które musi być spełnione, aby kontynuować wykonywanie pętli. Gdy warunek przestaje być prawdziwy, pętla się kończy.

#### Przykład: wypisanie wszystkich liczb od 0 do n.

```c++
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj liczbę: ";
    std::cin >> n;
    
    int i = 0;
    while (i <= n) {
        std::cout << i << std::endl;
        i++;
    }

    return 0;
}
```

W tym przykładzie pętla będzie się wykonywać do momentu, w którym `i <= n`. Z każdą iteracją wartość `i` jest zwiększana o 1, dzięki czemu wykonujemy dokładnie tyle obrotów pętli, ile potrzeba do wypisania liczb z przedziału `[0, n]`.

### Pętla `do-while`

Pętla `do-while` jest podobna do pętli `while`, z tą różnicą, że warunek sprawdzany jest na końcu iteracji. Dlatego blok instrukcji wykona się przynajmniej raz, niezależnie od warunku. To oznacza, że `do-while` jest przydatne w sytuacjach, w których chcemy wykonać pewien fragment kodu co najmniej jeden raz, zanim w ogóle sprawdzimy warunek.

#### Struktura pętli `do-while`

```c++
do {
    // kod do wykonania w każdej iteracji
} while (warunek);
```

- Kod zawarty między `do { ... }` a `while (warunek);` wykona się **zawsze przynajmniej raz**, bez względu na początkową wartość warunku.

#### Przykład: Prośba o podanie liczby dodatniej przez użytkownika.

```c++
#include <iostream>

int main() {
    int n;

    do {
        std::cout << "Podaj liczbę dodatnią: ";
        std::cin >> n;
    } while (n <= 0);

    std::cout << "Dziękuję! Podana liczba to: " << n << std::endl;

    return 0;
}
```

W tym kodzie użytkownik jest proszony o podanie liczby co najmniej raz. Nawet gdyby początkowo `n` miało wartość mniejszą od zera, pętla uruchomi się i umożliwi wprowadzenie liczby. Dopiero po wykonaniu bloku następuje sprawdzenie, czy `n <= 0`. Jeśli tak, cała sekwencja się powtarza, dopóki nie zostanie wprowadzona wartość dodatnia.

### Pętla nieskończona

Pętla nieskończona to pętla, która teoretycznie nigdy się nie kończy, ponieważ jej warunek zawsze pozostaje prawdziwy. Zwykle jest kontrolowana za pomocą zewnętrznych warunków, np. dodatkowych instrukcji `if` czy mechanizmu obsługi zdarzeń, dzięki którym możemy ręcznie przerwać jej działanie. Pętla nieskończona bywa używana w aplikacjach systemowych i serwerach, które muszą nieustannie nasłuchiwać zdarzeń i nie powinny się kończyć w sposób „naturalny”.

```c++
#include <iostream>

int main() {
    while (true) {
        std::cout << "To jest pętla nieskończona. Naciśnij Ctrl+C, aby zakończyć." << std::endl;
    }

    return 0;
}
```

Przykład ten obrazuje niekończące się wypisywanie komunikatu na ekran. W praktyce zamiast samych komunikatów w pętli nieskończonej mogłyby się znaleźć np. operacje obsługi zadań w tle, komunikacja z innymi procesami czy reagowanie na zdarzenia z systemu operacyjnego.

---

### Zagnieżdżone pętle

Zagnieżdżone pętle to konstrukcja, w której jedna pętla jest umieszczona wewnątrz innej pętli. Są one często używane do operacji na danych wielowymiarowych, takich jak tablice dwuwymiarowe (macierze). Każda iteracja pętli zewnętrznej uruchamia pełny cykl iteracji pętli wewnętrznej. Zagnieżdżenie pętli może być dowolnie głębokie, choć w praktyce więcej niż trzy poziomy zagnieżdżenia znacząco utrudniają czytelność i mogą świadczyć o konieczności refaktoryzacji kodu.

#### Struktura zagnieżdżonej pętli

```c++
for (inicjalizacja1; warunek1; inkrementacja1) {
    // Kod pętli zewnętrznej
    for (inicjalizacja2; warunek2; inkrementacja2) {
        // Kod pętli wewnętrznej
    }
}
```

Możemy łączyć różne typy pętli, np. pętlę `for` jako zewnętrzną i pętlę `while` jako wewnętrzną, jednak warto wtedy zachować szczególną ostrożność w zakresie kontrolowania warunków ich zakończenia.

#### Przykład: Wypisanie tablicy mnożenia

Poniżej znajduje się przykład programu, który używa zagnieżdżonych pętli do wypisania tablicy mnożenia dla liczb od 1 do `n`.

```c++
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj rozmiar tablicy mnożenia: ";
    std::cin >> n;

    // Pętla zewnętrzna iteruje po wierszach
    for (int i = 1; i <= n; i++) {
        // Pętla wewnętrzna iteruje po kolumnach
        for (int j = 1; j <= n; j++) {
            std::cout << i * j << "\t";
        }
        std::cout << std::endl;
    }

    return 0;
}
```

W tym przykładzie, dla każdej wartości `i` w pętli zewnętrznej, pętla wewnętrzna wykonuje pełny cykl iteracji dla wartości `j`. Dzięki temu uzyskujemy wszystkie iloczyny postaci `i * j`, co pozwala na wypisanie tablicy mnożenia o wymiarach `n x n`.

#### Zagnieżdżone pętle `while`

Zagnieżdżenie pętli nie dotyczy wyłącznie `for`. Poniżej przykład osiągający ten sam efekt co powyżej, ale przy użyciu pętli `while`.

```c++
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj rozmiar tablicy mnożenia: ";
    std::cin >> n;

    int i = 1;
    while (i <= n) {
        int j = 1;
        while (j <= n) {
            std::cout << i * j << "\t";
            j++;
        }
        std::cout << std::endl;
        i++;
    }

    return 0;
}
```

Kod działania jest bardzo podobny: pętla zewnętrzna (kontrolująca `i`) uruchamia się od 1 do `n`, a w jej obrębie pętla wewnętrzna przechodzi przez wartości `j` od 1 do `n`. Wynik jest identyczny – tablica mnożenia rozmiaru `n x n`.

#### Na co uważać przy zagnieżdżonych pętlach

- Zagnieżdżone pętle mogą prowadzić do **dużej liczby iteracji** i w efekcie do wzrostu złożoności obliczeniowej. Przy dużych wartościach zmiennych kontrolnych może to znacząco wydłużyć działanie programu.
- **Czytelność kodu** może ulec pogorszeniu, gdy używane są wielopoziomowe zagnieżdżenia. Dlatego warto stosować czytelne nazwy zmiennych i ewentualnie dzielić kod na mniejsze funkcje pomocnicze.
- Aby uniknąć **niekończących się pętli**, należy zwrócić szczególną uwagę na poprawne zdefiniowanie warunków zakończenia oraz poprawnie pisać inkrementacje lub dekrementacje zmiennych kontrolnych.
- W przypadku pracy z tablicami wielowymiarowymi, istotne jest **poprawne indeksowanie tablic**, by nie wyjść poza zakres, co może prowadzić do trudnych do wykrycia błędów i uszkodzeń pamięci programu.

### Continue

Instrukcja `continue` umożliwia natychmiastowe przejście do następnej iteracji pętli, pomijając pozostałe instrukcje w bieżącym cyklu. Jest ona przydatna, gdy chcemy zignorować pewne przypadki i nie wykonywać dalszego kodu w danej iteracji, ale nie chcemy przerywać całej pętli.

Przykład użycia `continue` do wypisania wszystkich parzystych liczb od 0 do n:

```c++
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj liczbę: " << std::endl;
    std::cin >> n;

    for (int i = 0; i <= n; i++) {
        if (i % 2 != 0)
            continue;
        std::cout << i << std::endl;
    }

    return 0;
}
```

W powyższym kodzie, gdy `i` jest nieparzyste (`i % 2 != 0`), instrukcja `continue` powoduje pominięcie wszystkiego, co jest poniżej w ciele pętli, i przejście do kolejnej iteracji. Dzięki temu wyświetlane są wyłącznie liczby parzyste.

### Break

Instrukcja `break` pozwala na zakończenie wykonywania pętli przedwcześnie, nie czekając na spełnienie warunku zakończenia (w przypadku `while` i `for`) czy warunku zapisanego w pętli `do-while`. Może to być przydatne np. wtedy, gdy znaleźliśmy już to, czego szukaliśmy, i dalsze iteracje są zbędne, albo w sytuacji kontrolowania jakichś wyjątkowych stanów.

Przykład: Wypisz wszystkie liczby od 0 do n lub zakończ pętlę po napotkaniu pierwszej nieparzystej liczby:

```c++
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj liczbę: " << std::endl;
    std::cin >> n;

    for (int i = 0; i <= n; i++) {
        if (i % 2 != 0)
            break;
        std::cout << i << std::endl;
    }

    return 0;
}
```

W powyższym kodzie pętla zakończy się natychmiast, gdy `i` przyjmie wartość nieparzystą. Dzięki temu nie będą drukowane kolejne liczby, nawet jeśli do końca zakresu (do `n`) zostało jeszcze wiele potencjalnych iteracji.
