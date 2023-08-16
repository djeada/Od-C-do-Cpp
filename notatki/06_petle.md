## Pętle

Pętle to kluczowe konstrukcje w programowaniu, które pozwalają na wielokrotne wykonanie określonego fragmentu kodu. Istnieją różne typy pętli: `for`, `while` oraz `do-while`.

### Pętla `for`

Pętla `for` jest szczególnie przydatna, gdy znamy z góry liczbę powtórzeń danej operacji. Składa się z trzech głównych elementów: inicjalizacji, warunku i operacji po każdej iteracji (zwykle inkrementacji).

Przykład: wypisanie wszystkich parzystych liczb od 0 do `n`.

```c++
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj liczbe: " << std::endl;
    std::cin >> n;

    for (int i = 0; i <= n; i++) {
        if (i % 2 == 0)
            std::cout << i << std::endl;
    }

    return 0;
}
```

### Pętla while

Pętla `while` powtarza blok instrukcji, dopóki podany warunek jest prawdziwy.

Przykład: wypisanie wszystkich liczb od 0 do n.

```c++
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj liczbe: " << std::endl;
    std::cin >> n;
    
    int i = 0;
    while (i <= n) {
        std::cout << i << std::endl;
        i++;
    }

    return 0;
}
```

### Pętla do-while

Pętla `do-while` jest podobna do pętli `while`, z tą różnicą, że warunek sprawdzany jest na końcu iteracji. Dlatego blok instrukcji wykona się przynajmniej raz, niezależnie od warunku.

Przykład: Prośba o podanie liczby dodatniej przez użytkownika.

```c++
#include <iostream>

int main() {
    int n;

    do {
        std::cout << "Podaj liczbe dodatnia: " << std::endl;
        std::cin >> n;
    } while (n <= 0);

    std::cout << "Dziękuję! Podana liczba to: " << n << std::endl;

    return 0;
}
```

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
