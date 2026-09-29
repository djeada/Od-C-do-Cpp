# Pętle

Instrukcje zapisane kilka razy można zastąpić pętlą. Pętla wykonuje swoje ciało, sprawdza, czy ma wykonać je ponownie, i kończy się, gdy warunek kontynuacji przestaje być spełniony. To ta sama logika warunków z poprzedniej lekcji, użyta do sterowania powtarzaniem.

W przykładach używamy C++ i `std::cout`/`std::cin`, więc programy dołączają `<iostream>`. Konstrukcje `for`, `while`, `do-while` oraz instrukcje `break` i `continue` działają w podobny sposób także w C; różni się tutaj głównie sposób obsługi konsoli.

## Pętla `for`: powtórz określoną liczbę razy

Gdy mamy licznik i wiemy, według jakiej reguły ma się zmieniać, wygodna jest pętla `for`:

```cpp
for (inicjalizacja; warunek; zmiana) {
    // ciało pętli
}
```

Części nagłówka mają stałą kolejność:

1. **Inicjalizacja** wykonuje się jeden raz przed pętlą, zwykle tworzy licznik.
2. **Warunek** jest sprawdzany przed każdą iteracją. Jeśli jest fałszywy, pętla kończy się.
3. **Ciało** wykonuje się, gdy warunek jest prawdziwy.
4. **Zmiana** następuje po ciele, a potem program wraca do sprawdzenia warunku.

Oto program, który pobiera górną granicę i wypisuje parzyste liczby od zera do tej granicy:

```cpp
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj nieujemną liczbę całkowitą: ";
    if (!(std::cin >> n) || n < 0) {
        std::cerr << "Oczekiwano liczby całkowitej nieujemnej.\n";
        return 1;
    }

    for (int i = 0; i <= n; ++i) {
        if (i % 2 == 0) {
            std::cout << i << '\n';
        }
    }

    return 0;
}
```

Dane wpisane przez użytkownika trafiają do `n`. Następnie pętla tworzy `i` z wartością `0`. Przy `n == 3` przebieg wygląda tak:

| `i` | Sprawdzenie `i <= n` | Działanie |
|---:|---|---|
| 0 | prawda | 0 jest parzyste, więc zostaje wypisane |
| 1 | prawda | liczba nie jest wypisywana |
| 2 | prawda | 2 zostaje wypisane |
| 3 | prawda | 3 nie jest wypisywane |
| 4 | fałsz | ciało pętli już się nie wykonuje |

Po każdym przebiegu `++i` zwiększa licznik o jeden. Gdy `i` wynosi `4`, warunek `4 <= 3` jest fałszywy i program kończy pętlę. Warunek `i <= n` obejmuje górną granicę; zapis `i < n` zakończyłby pętlę wcześniej.

Liczby zmiennoprzecinkowe nie są dobrym licznikiem pętli. Wielokrotne dodawanie `0.1` może przez zaokrąglenia nie dać dokładnie oczekiwanej wartości końcowej. Użyj licznika całkowitego, a wartość dziesiętną oblicz w ciele:

```cpp
#include <iostream>

int main() {
    for (int i = 0; i <= 10; ++i) {
        double wartosc = i / 10.0;
        std::cout << wartosc << ' ';
    }
    std::cout << '\n';
}
```

## Pętla `while`: powtarzaj, póki warunek jest prawdziwy

Pętla `while` sprawdza warunek przed ciałem. Może więc nie wykonać się ani razu. Używaj jej, gdy warunek czytelniej opisuje, kiedy kontynuować, niż liczba zapisana w nagłówku `for`.

```cpp
while (warunek) {
    // ciało pętli
}
```

Przykład sumuje liczby od `1` do podanej granicy. Wartość `i` jest stanem pętli: mówi, którą liczbę dodajemy teraz.

```cpp
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj liczbę całkowitą z zakresu 0–100000: ";
    if (!(std::cin >> n) || n < 0 || n > 100000) {
        std::cerr << "Oczekiwano liczby z zakresu 0–100000.\n";
        return 1;
    }

    int i = 1;
    long long suma = 0;
    while (i <= n) {
        suma += i;
        ++i;
    }

    std::cout << "Suma liczb od 1 do " << n << " wynosi " << suma << ".\n";
    return 0;
}
```

Dla `n == 3` pierwsze sprawdzenie `1 <= 3` pozwala wejść do ciała: program dodaje `1`, po czym zwiększa `i` do `2`. Następne obroty dodają `2` i `3`. Po ostatnim zwiększeniu `i` wynosi `4`; sprawdzenie `4 <= 3` jest fałszywe, więc pętla się kończy, a suma wynosi `6`. Dla `n == 0` warunek jest fałszywy od początku, więc ciało nie wykona się wcale.

Każda pętla `while` powinna mieć drogę do zakończenia. Jeśli zapomnisz zmienić `i`, a warunek pozostanie prawdziwy, program będzie bez końca dodawał tę samą wartość. W każdej iteracji sprawdź, co zmienia stan używany w warunku.

### Odczytywanie danych aż do wartości kończącej

Czasem z góry nie wiadomo, ile danych poda użytkownik. Można wtedy powtarzać odczyt, aż pojawi się umówiona wartość, na przykład `0`:

```cpp
#include <iostream>

int main() {
    int liczba;
    int suma = 0;

    std::cout << "Podawaj liczby całkowite; 0 kończy: ";
    while (std::cin >> liczba && liczba != 0) {
        suma += liczba;
        std::cout << "Kolejna liczba (0 kończy): ";
    }

    if (!std::cin) {
        std::cerr << "Nie udało się odczytać liczby.\n";
        return 1;
    }

    std::cout << "Suma podanych liczb: " << suma << '\n';
    return 0;
}
```

Przed każdym obrotem `std::cin >> liczba` próbuje zapisać kolejną wartość do zmiennej. Warunek po `&&` jest sprawdzany tylko wtedy, gdy odczyt się powiódł. Jeśli liczba wynosi `0`, warunek jest fałszywy i ciało nie wykona się dla zera. W przeciwnym razie liczba zostaje dodana, a program prosi o następną. Napis zamiast liczby powoduje błąd odczytu; ten przykład zgłasza go i kończy działanie.

## Pętla `do-while`: wykonaj ciało przynajmniej raz

W pętli `do-while` ciało wykonuje się przed sprawdzeniem warunku. Przydaje się to, gdy pierwsza czynność ma nastąpić niezależnie od wartości początkowej — na przykład gdy program musi najpierw zadać pytanie.

```cpp
do {
    // ciało pętli
} while (warunek);
```

Zwróć uwagę na średnik po `while (warunek)`. W odróżnieniu od `while` i `for` jest on częścią składni `do-while`.

```cpp
#include <iostream>

int main() {
    int n;

    do {
        std::cout << "Podaj dodatnią liczbę całkowitą: ";
        if (!(std::cin >> n)) {
            std::cerr << "Oczekiwano liczby całkowitej.\n";
            return 1;
        }
    } while (n <= 0);

    std::cout << "Dziękuję, podano " << n << ".\n";
    return 0;
}
```

Ciało wykona się co najmniej raz i zapisze odpowiedź w `n`. Jeśli użytkownik wpisze `-2`, warunek `n <= 0` będzie prawdziwy i pytanie pojawi się ponownie. To samo stanie się po wpisaniu `0`. Po wpisaniu `4` warunek będzie fałszywy i program przejdzie za pętlę. W przykładzie błędny tekst kończy program, ponieważ po nieudanym odczycie nie wolno bez dodatkowej obsługi ponawiać sprawdzania starej wartości `n`.

## `break` i `continue`

Dwie instrukcje pozwalają zmienić zwykły przebieg pętli:

- `break` natychmiast kończy najbliższą otaczającą pętlę;
- `continue` pomija resztę bieżącego obrotu i rozpoczyna następny.

Poniższy przykład używa `continue`, aby pominąć liczby nieparzyste:

```cpp
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj nieujemną liczbę całkowitą: ";
    if (!(std::cin >> n) || n < 0) {
        std::cerr << "Oczekiwano liczby całkowitej nieujemnej.\n";
        return 1;
    }

    for (int i = 0; i <= n; ++i) {
        if (i % 2 != 0) {
            continue;
        }
        std::cout << i << '\n';
    }
    return 0;
}
```

Gdy `i` wynosi `3`, warunek `i % 2 != 0` jest prawdziwy. `continue` pomija `std::cout`, więc `3` nie zostaje wypisane. W pętli `for` po `continue` nadal wykonywana jest część zmieniająca licznik (`++i`), a potem ponownie sprawdzany jest warunek pętli. W `while` program wróci bezpośrednio do sprawdzenia warunku, dlatego zmiana licznika musi nastąpić przed `continue`, jeśli od niej zależy zakończenie pętli.

`break` przydaje się, gdy znamy warunek wcześniejszego zakończenia:

```cpp
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj nieujemną liczbę całkowitą: ";
    if (!(std::cin >> n) || n < 0) {
        std::cerr << "Oczekiwano liczby całkowitej nieujemnej.\n";
        return 1;
    }

    for (int i = 0; i <= n; ++i) {
        if (i == 3) {
            break;
        }
        std::cout << i << '\n';
    }
    return 0;
}
```

Dla `n >= 3` program wypisze `0`, `1` i `2`. Gdy `i` osiągnie `3`, `break` natychmiast opuści pętlę; liczby `3` i większe nie zostaną wypisane. `break` kończy tylko najbliższą pętlę. Jeśli pętle są zagnieżdżone, nie oznacza to automatycznie wyjścia ze wszystkich poziomów. W konstrukcji `switch` `break` kończy z kolei najbliższy `switch`.

## Pętla nieskończona i sposób jej zakończenia

Pętla nieskończona to taka, której warunek nigdy nie staje się fałszywy albo której w ogóle nie zapisano. Bywa przydatna, gdy program ma stale czekać na zdarzenia, ale potrzebuje jasno określonego sposobu zakończenia.

```cpp
#include <iostream>

int main() {
    int polecenie;

    while (true) {
        std::cout << "Podaj 0, aby zakończyć, albo inną liczbę, aby kontynuować: ";
        if (!(std::cin >> polecenie)) {
            std::cerr << "Nie udało się odczytać polecenia.\n";
            return 1;
        }

        if (polecenie == 0) {
            break;
        }
        std::cout << "Kontynuuję.\n";
    }

    std::cout << "Koniec programu.\n";
    return 0;
}
```

Warunek `true` sam nie zakończy pętli. Po każdym odczycie program sprawdza polecenie; przy `0` instrukcja `break` opuszcza pętlę. Bez takiego warunku zakończenia program czekałby na kolejne dane bez końca. W C zamiast literału `true` można użyć warunku `1`.

## Pętle zagnieżdżone

Pętla może znajdować się wewnątrz innej pętli. Każdy obrót pętli zewnętrznej uruchamia pełny cykl pętli wewnętrznej. Ten układ pasuje na przykład do przetwarzania wierszy i kolumn.

```cpp
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj rozmiar tablicy mnożenia: ";
    if (!(std::cin >> n) || n < 1) {
        std::cerr << "Rozmiar musi być dodatnią liczbą całkowitą.\n";
        return 1;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            std::cout << i * j << '\t';
        }
        std::cout << '\n';
    }
    return 0;
}
```

Dla `n == 2` pętla zewnętrzna ustawia `i` na `1`. Wtedy wewnętrzna pętla przechodzi przez `j == 1` i `j == 2`, wypisując `1` i `2`. Po zakończeniu całego wewnętrznego cyklu program kończy wiersz. Następnie `i` zmienia się na `2`, a wewnętrzna pętla zaczyna nowy cykl od `j == 1`; wypisuje `2` i `4`. Wynik to dwuwierszowa tablica:

```text
1    2
2    4
```

Zmienna `j` jest inicjalizowana od nowa przy każdym nowym wierszu, ponieważ cały nagłówek wewnętrznej pętli wykonuje się dla każdej wartości `i`. Dwie pętle po `n` elementów wykonują łącznie `n * n` obrotów ciała wewnętrznego. Zbyt głębokie zagnieżdżenia utrudniają śledzenie programu i mogą zwiększać liczbę obliczeń.

Ten sam schemat można zapisać za pomocą `while`. Wtedy trzeba jawnie zainicjalizować oba liczniki i pamiętać o ich zmianie:

```cpp
#include <iostream>

int main() {
    int n = 3;
    int i = 1;
    while (i <= n) {
        int j = 1; // nowy wiersz: zacznij kolumny od początku
        while (j <= n) {
            std::cout << i * j << '\t';
            ++j;
        }
        std::cout << '\n';
        ++i;
    }
    return 0;
}
```

Wersja `while` pokazuje szczególnie wyraźnie, że po wewnętrznej pętli należy zwiększyć `i`, a w jej ciele — `j`. Brak którejkolwiek zmiany może sprawić, że warunek pozostanie prawdziwy i pętla nie będzie się kończyć.

## Typowe błędy przy pętlach

- **Brak zmiany licznika.** Jeśli warunek zależy od `i`, a `i` się nie zmienia, pętla może nigdy się nie zakończyć.
- **Błędna granica.** `i < n` i `i <= n` oznaczają inny zakres. Przed uruchomieniem prześledź pierwszą i ostatnią wartość licznika.
- **Średnik po `while` lub `for`.** Zapis `while (warunek);` tworzy pustą pętlę. W przypadku `do-while` średnik na końcu jest natomiast wymagany.
- **Nieprawidłowe miejsce `continue`.** W `while` pominięcie instrukcji zmieniającej licznik może utknąć na tej samej wartości.
- **Zagnieżdżenie bez potrzeby.** Każda dodatkowa pętla zwiększa liczbę wykonań jej ciała; używaj czytelnych nazw liczników i sprawdź, czy wszystkie poziomy są potrzebne.
