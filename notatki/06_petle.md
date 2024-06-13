## Pętle

Pętle to kluczowe konstrukcje w programowaniu, które pozwalają na wielokrotne wykonanie określonego fragmentu kodu. Istnieją różne typy pętli: `for`, `while` oraz `do-while`.

### Pętla `for`

Pętla `for` jest szczególnie przydatna, gdy znamy z góry liczbę powtórzeń danej operacji. Składa się z trzech głównych elementów: inicjalizacji, warunku i operacji po każdej iteracji (zwykle inkrementacji).

#### Struktura pętli `for`

```c++
for (inicjalizacja; warunek; inkrementacja) {
    // kod do wykonania w każdej iteracji
}
```

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

### Pętla `while`

Pętla `while` powtarza blok instrukcji, dopóki podany warunek jest prawdziwy.

#### Struktura pętli `while`

```c++
while (warunek) {
    // kod do wykonania w każdej iteracji
}
```

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

### Pętla `do-while`

Pętla `do-while` jest podobna do pętli `while`, z tą różnicą, że warunek sprawdzany jest na końcu iteracji. Dlatego blok instrukcji wykona się przynajmniej raz, niezależnie od warunku.

#### Struktura pętli `do-while`

```c++
do {
    // kod do wykonania w każdej iteracji
} while (warunek);
```

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

### Pętla nieskończona

Pętla nieskończona to pętla, która nigdy się nie kończy, zwykle kontrolowana jest za pomocą zewnętrznych warunków.

```c++
#include <iostream>

int main() {
    while (true) {
        std::cout << "To jest pętla nieskończona. Naciśnij Ctrl+C, aby zakończyć." << std::endl;
    }

    return 0;
}
```

### Zagnieżdżone pętle

Zagnieżdżone pętle to konstrukcja, w której jedna pętla jest umieszczona wewnątrz innej pętli. Są one często używane do operacji na danych wielowymiarowych, takich jak tablice dwuwymiarowe (macierze). Każda iteracja pętli zewnętrznej uruchamia pełny cykl iteracji pętli wewnętrznej.

#### Struktura zagnieżdżonej pętli

Zagnieżdżenie pętli może być dowolnie głębokie, jednak im więcej poziomów zagnieżdżenia, tym trudniej zrozumieć i debugować kod. Ogólna struktura wygląda następująco:

```c++
for (inicjalizacja1; warunek1; inkrementacja1) {
    // Kod pętli zewnętrznej
    for (inicjalizacja2; warunek2; inkrementacja2) {
        // Kod pętli wewnętrznej
    }
}
```

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

W tym przykładzie, dla każdej wartości `i` w pętli zewnętrznej, pętla wewnętrzna wykonuje pełny cykl iteracji dla wartości `j`, co pozwala na wypisanie wyników mnożenia `i * j` w formacie tablicy.

#### Zagnieżdżone pętle `while`

Podobnie jak pętle `for`, możemy również zagnieżdżać pętle `while`. Poniżej znajduje się przykład, który osiąga ten sam efekt co powyższy, ale przy użyciu pętli `while`.

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

#### Na co uważać przy zagnieżdżonych pętlach

1. **Złożoność obliczeniowa**: Zagnieżdżone pętle mogą prowadzić do dużej liczby iteracji, co może wpłynąć na wydajność programu, zwłaszcza przy dużych wartościach zmiennych kontrolnych.
2. **Czytelność kodu**: Zagnieżdżone pętle mogą szybko stać się trudne do zrozumienia. Warto zadbać o odpowiednie komentarze i nazewnictwo zmiennych.
3. **Unikanie niekończących się pętli**: Należy upewnić się, że warunki zakończenia każdej pętli są poprawnie zdefiniowane, aby uniknąć nieskończonych pętli.
4. **Indeksowanie tablic**: Przy pracy z tablicami wielowymiarowymi, należy upewnić się, że indeksy są poprawnie zdefiniowane, aby uniknąć błędów wykraczania poza zakres tablicy.

### Continue

Instrukcja continue umożliwia natychmiastowe przejście do następnej iteracji pętli, pomijając pozostałe instrukcje w bieżącym cyklu.

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

### Break

Instrukcja `break` pozwala na zakończenie wykonywania pętli przedwcześnie, nie czekając na spełnienie warunku zakończenia.

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
