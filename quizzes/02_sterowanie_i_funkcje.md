# Sterowanie przepływem, funkcje i operacje bitowe — quiz

Notatki: [Instrukcja warunkowa](../notatki/05_instrukcja_warunkowa.md), [Pętle](../notatki/06_petle.md), [Liczby losowe](../notatki/07_liczby_losowe.md), [Typ wyliczeniowy](../notatki/08_typ_wyliczeniowy.md), [Funkcje](../notatki/09_funkcje.md), [L-wartości i R-wartości](../notatki/10_l_wartosci_r_wartosci.md), [Operacje bitowe](../notatki/14_operacje_bitowe.md)

Sprawdź, czy potrafisz przewidzieć działanie warunków i pętli, korzystać z `<random>`, `enum class` i funkcji oraz operować na bitach.

#### Q. Co wypisze ten program w C++ z przypisaniem w warunku `if`?

```cpp
#include <iostream>

int main() {
    int x = 5;
    if (x = 10) {
        std::cout << "tak ";
    }
    std::cout << x << '\n';
}
```

* [x] `tak 10`
* [ ] `5`
* [ ] `tak 5`
* [ ] `10`

> **Wyjaśnienie:** `x = 10` to przypisanie, a nie porównanie: zmienia `x` na 10, a wartość całego wyrażenia (10) oznacza w warunku prawdę. Kompilator z `-Wall` ostrzega przed takim zapisem.

#### Q. Co wypisze ten program w C++ ze średnikiem tuż po warunku `if`?

```cpp
#include <iostream>

int main() {
    int liczba = -2;
    if (liczba > 0);
    {
        std::cout << "dodatnia\n";
    }
}
```

* [x] `dodatnia`
* [ ] Nic
* [ ] Błąd kompilacji: pusty `if`
* [ ] `-2`

> **Wyjaśnienie:** Średnik jest pustą instrukcją, którą steruje `if`. Blok w klamrach jest osobną instrukcją wykonywaną zawsze, niezależnie od wartości `liczba`.

#### Q. Co wypisze ten program w C++ z łańcuchem `else if`?

```cpp
#include <iostream>

int main() {
    int wynik = 95;
    if (wynik >= 50) {
        std::cout << "zaliczony\n";
    } else if (wynik >= 90) {
        std::cout << "bardzo dobry\n";
    } else {
        std::cout << "niezaliczony\n";
    }
}
```

* [x] `zaliczony`
* [ ] `bardzo dobry`
* [ ] `zaliczony`, a potem `bardzo dobry`
* [ ] `niezaliczony`

> **Wyjaśnienie:** Warunki są sprawdzane po kolei i wykonuje się tylko pierwsza prawdziwa gałąź. `95 >= 50` jest prawdą, więc próg 90 nigdy nie zostanie sprawdzony — wyższy próg należy umieścić wcześniej.

#### Q. Co wypisze ten program w C++ z instrukcją `switch` bez części `break`?

```cpp
#include <iostream>

int main() {
    int dzien = 2;
    switch (dzien) {
        case 1:
            std::cout << "A";
        case 2:
            std::cout << "B";
        case 3:
            std::cout << "C";
            break;
        default:
            std::cout << "D";
    }
    std::cout << '\n';
}
```

* [ ] `B`
* [x] `BC`
* [ ] `BCD`
* [ ] `ABC`

> **Wyjaśnienie:** Wykonanie zaczyna się od pasującej etykiety `case 2`. Bez `break` przechodzi dalej do instrukcji `case 3`, a `break` po `C` kończy `switch`, zanim dotrze do `default`.

#### Q. Co wypisze ten program w C++ korzystający z krótkiego spięcia `&&` i `||`?

```cpp
#include <iostream>

int main() {
    int licznik = 0;
    if (false && ++licznik > 0) {}
    if (true || ++licznik > 0) {}
    if (true && ++licznik > 0) {}
    std::cout << licznik << '\n';
}
```

* [ ] `0`
* [x] `1`
* [ ] `2`
* [ ] `3`

> **Wyjaśnienie:** Prawa strona `&&` i `||` jest obliczana tylko wtedy, gdy lewa nie przesądza wyniku. W dwóch pierwszych warunkach `++licznik` się nie wykona; w trzecim tak, więc licznik wynosi 1.

#### Q. Co wypisze ten program w C++ z operatorem `x++` w warunku?

```cpp
#include <iostream>

int main() {
    int x = 5;
    if (x++ > 5) {
        std::cout << "T ";
    }
    std::cout << x << '\n';
}
```

* [x] `6`
* [ ] `T 6`
* [ ] `T 5`
* [ ] `5`

> **Wyjaśnienie:** `x++` daje starą wartość (5), a dopiero potem zwiększa zmienną. Porównanie `5 > 5` jest fałszywe, ale `x` i tak ma już wartość 6 — dlatego efekty uboczne w warunkach są mylące.

#### Q. Co wypisze ten program w C++ na typowej platformie z liczbami zmiennoprzecinkowymi IEEE 754?

```cpp
#include <iostream>

int main() {
    double suma = 0.1 + 0.2;
    if (suma == 0.3) {
        std::cout << "równe\n";
    } else {
        std::cout << "różne\n";
    }
}
```

* [ ] `równe`
* [x] `różne`
* [ ] Błąd kompilacji: nie wolno porównywać `double`
* [ ] Wynik zmienia się przy każdym uruchomieniu

> **Wyjaśnienie:** `0.1`, `0.2` i `0.3` nie mają dokładnej reprezentacji binarnej, więc suma różni się minimalnie od `0.3`. Wyniki obliczeń porównuje się z tolerancją, np. `std::abs(suma - 0.3) < 1e-9`.

#### Q. Wyrażenia którego typu nie można bezpośrednio użyć jako wyrażenia sterującego instrukcji `switch` w C++?

* [ ] `int`
* [ ] `char`
* [ ] `enum class`
* [x] `std::string`

> **Wyjaśnienie:** `switch` porównuje wartość typu całkowitego, znakowego lub wyliczeniowego ze stałymi etykietami. Tekstu `std::string` ani przedziałów nie da się tak sprawdzić — służy do tego `if`.

#### Q. Co wypisze ten program w C++ z instrukcją `break` w zagnieżdżonych pętlach?

```cpp
#include <iostream>

int main() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (j == 1) {
                break;
            }
            std::cout << i << j << ' ';
        }
    }
    std::cout << '\n';
}
```

* [x] `00 10 20`
* [ ] `00`
* [ ] `00 01 02`
* [ ] `00 11 22`

> **Wyjaśnienie:** `break` kończy tylko najbliższą otaczającą pętlę, czyli wewnętrzną. Zewnętrzna pętla działa dalej, więc dla każdego `i` wypisywana jest tylko para z `j == 0`.

#### Q. Co wypisze ten program w C++ z pętlą `do-while`, której warunek od początku jest fałszywy?

```cpp
#include <iostream>

int main() {
    int n = 10;
    do {
        std::cout << n << ' ';
        ++n;
    } while (n < 5);
    std::cout << '\n';
}
```

* [ ] Nic
* [x] `10`
* [ ] `10 11 12 13 14`
* [ ] Pętla nigdy się nie skończy

> **Wyjaśnienie:** W `do-while` ciało wykonuje się przed pierwszym sprawdzeniem warunku, więc co najmniej raz. Po wypisaniu `10` warunek `11 < 5` jest fałszywy i pętla się kończy.

#### Q. Co wypisze ten program w C++ ze średnikiem tuż po nagłówku pętli `for`?

```cpp
#include <iostream>

int main() {
    int i;
    int suma = 0;
    for (i = 0; i < 3; ++i);
    {
        suma += i;
    }
    std::cout << suma << '\n';
}
```

* [ ] `0`
* [x] `3`
* [ ] `6`
* [ ] `2`

> **Wyjaśnienie:** Średnik tworzy pustą pętlę, która tylko zwiększa `i` do 3. Blok w klamrach nie należy do pętli i wykonuje się raz, dodając 3 do `suma`.

#### Q. Dlaczego w pętli `while` instrukcja zmieniająca licznik musi znaleźć się przed `continue`, gdy od niej zależy zakończenie pętli?

* [ ] Bo `continue` w pętli `while` kończy całą pętlę
* [x] Bo `continue` wraca prosto do warunku i pomija resztę ciała
* [ ] Bo `continue` w `while` jest dozwolone tylko na początku ciała
* [ ] Bo `continue` automatycznie zeruje licznik pętli

> **Wyjaśnienie:** W `for` po `continue` wykonuje się jeszcze część zmieniająca licznik, np. `++i`. W `while` takiej części nie ma, więc pominięcie zmiany licznika może utknąć na tej samej wartości.

#### Q. Co wypisze ten program w C++ liczący wykonania zagnieżdżonej pętli?

```cpp
#include <iostream>

int main() {
    int licznik = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < i; ++j) {
            ++licznik;
        }
    }
    std::cout << licznik << '\n';
}
```

* [ ] `16`
* [ ] `10`
* [x] `6`
* [ ] `4`

> **Wyjaśnienie:** Wewnętrzna pętla wykonuje się `i` razy dla każdego `i`: $0 + 1 + 2 + 3 = 6$. Gdyby obie pętle miały granicę 4, ciało wykonałoby się 16 razy.

#### Q. Co wypisze ten program w C++ porównujący dwa silniki `std::mt19937`?

```cpp
#include <iostream>
#include <random>

int main() {
    std::mt19937 a(42);
    std::mt19937 b(42);
    bool rowne = true;
    for (int i = 0; i < 5; ++i) {
        if (a() != b()) {
            rowne = false;
        }
    }
    std::cout << (rowne ? "takie same" : "różne") << '\n';
}
```

* [x] `takie same`
* [ ] `różne`
* [ ] Wynik zależy od uruchomienia
* [ ] Błąd kompilacji: silnik nie ma `operator()`

> **Wyjaśnienie:** Silnik pseudolosowy jest deterministyczny: z tym samym ziarnem i przy tych samych wywołaniach wytwarza tę samą sekwencję. Na tym opiera się odtwarzalność symulacji.

#### Q. Jakie wartości może zwrócić `std::uniform_int_distribution<int> kostka(1, 6)`?

* [x] Liczby całkowite od 1 do 6 włącznie
* [ ] Liczby całkowite od 1 do 5 włącznie
* [ ] Liczby całkowite od 0 do 6 włącznie
* [ ] Liczby całkowite od 0 do 5 włącznie

> **Wyjaśnienie:** Całkowity rozkład jednostajny obejmuje oba końce zakresu, więc każda z sześciu wartości ma prawdopodobieństwo $\frac{1}{6}$. Inaczej działa rozkład rzeczywisty, który wyklucza górną granicę.

#### Q. Z jakiego przedziału pochodzą wyniki `std::uniform_real_distribution<double> odcinek(0.0, 1.0)`?

* [ ] `[0.0, 1.0]` — oba końce włącznie
* [x] `[0.0, 1.0)` — z 0.0, bez 1.0
* [ ] `(0.0, 1.0)` — bez obu końców
* [ ] `(0.0, 1.0]` — bez 0.0, z 1.0

> **Wyjaśnienie:** Rozkład rzeczywisty w bibliotece C++ zwraca wartości z przedziału `[a, b)`: dolna granica jest włączona, górna wyłączona. Całkowity `uniform_int_distribution` obejmuje natomiast oba końce.

#### Q. Co wypisze ten program w C++, który tworzy silnik wewnątrz pętli?

```cpp
#include <iostream>
#include <random>

int main() {
    int wyniki[3];
    for (int i = 0; i < 3; ++i) {
        std::mt19937 silnik(12345);
        std::uniform_int_distribution<int> kostka(1, 6);
        wyniki[i] = kostka(silnik);
    }
    std::cout << (wyniki[0] == wyniki[1] && wyniki[1] == wyniki[2]) << '\n';
}
```

* [x] `1`
* [ ] `0`
* [ ] `3`
* [ ] Wynik jest inny przy każdym uruchomieniu

> **Wyjaśnienie:** Każdy obieg tworzy nowy silnik z tym samym ziarnem, więc za każdym razem losowanie zaczyna się od pierwszego elementu tej samej sekwencji. Silnik tworzy się raz, przed pętlą.

#### Q. Czy `std::mt19937` nadaje się do generowania haseł i kluczy kryptograficznych?

* [ ] Tak, bo ma bardzo długi okres
* [ ] Tak, jeśli ziarno pochodzi z `std::random_device`
* [x] Nie, bo nie jest generatorem kryptograficznym
* [ ] Nie, bo zwraca tylko liczby z zakresu 1–6

> **Wyjaśnienie:** Mersenne Twister ma dobre własności statystyczne i długi okres, ale jego kolejne wartości da się przewidzieć. Do sekretów służą funkcje kryptograficzne systemu lub sprawdzone biblioteki.

#### Q. Jaka jest główna wada losowania rzutu kostką wyrażeniem `rand() % 6 + 1`?

* [ ] Może zwrócić wartość 0
* [ ] Może zwrócić wartość 7
* [x] Wyniki mogą mieć nierówne szanse
* [ ] Nie kompiluje się w C++

> **Wyjaśnienie:** Jeśli liczba możliwych wyników `rand()` nie dzieli się przez 6, niektóre reszty wypadają częściej. Zakres `1–6` jest zachowany, ale rozkład nie musi być równy; w C++ lepiej użyć `std::uniform_int_distribution`.

#### Q. Który oznaczony wiersz tego programu w C++ z `enum class` spowoduje błąd kompilacji?

```cpp
enum class Tryb { Wylaczony, Wlaczony };

int main() {
    Tryb t = Tryb::Wlaczony;          // (1)
    int a = static_cast<int>(t);      // (2)
    int b = t;                        // (3)
    bool c = (t == Tryb::Wylaczony);  // (4)
    return a + b + c;
}
```

* [ ] `(1)`
* [ ] `(2)`
* [x] `(3)`
* [ ] `(4)`

> **Wyjaśnienie:** Elementów `enum class` nie da się niejawnie zamienić na liczbę, więc `int b = t;` jest błędem. Jawne `static_cast<int>` i porównanie dwóch wartości tego samego typu są poprawne.

#### Q. Co wypisze ten program w C++ z ręcznie przypisaną wartością w `enum class`?

```cpp
#include <iostream>

enum class Wielkosc { Mala, Srednia = 5, Duza };

int main() {
    std::cout << static_cast<int>(Wielkosc::Mala) << ' '
              << static_cast<int>(Wielkosc::Duza) << '\n';
}
```

* [ ] `0 2`
* [x] `0 6`
* [ ] `1 6`
* [ ] `0 5`

> **Wyjaśnienie:** Pierwszy element bez podanej wartości dostaje 0, a każdy kolejny bez jawnej wartości — wartość poprzedniego plus jeden. Po `Srednia = 5` element `Duza` otrzymuje 6.

#### Q. Dlaczego deklaracje `enum Kolor { Czerwony, Zielony };` i `enum Sygnal { Zielony, Czerwony };` w jednym zakresie się nie skompilują?

* [ ] Bo dwa typy wyliczeniowe nie mogą mieć po dwa elementy
* [x] Bo nazwy elementów klasycznego `enum` trafiają do zakresu otaczającego
* [ ] Bo klasyczny `enum` wymaga jawnego typu bazowego
* [ ] Bo elementy w drugim typie mają inną kolejność

> **Wyjaśnienie:** W klasycznym `enum` nazwy `Zielony` i `Czerwony` są widoczne bez prefiksu w otaczającym zakresie, więc drugi typ próbuje je zdefiniować ponownie. `enum class` rozwiązuje to zapisem `Kolor::Zielony`.

#### Q. Program wczytuje liczbę `n` z pliku i wykonuje `static_cast<Kolor>(n)`. Co sprawdza ta konwersja?

* [ ] Czy `n` odpowiada któremuś elementowi `Kolor`
* [x] Nic — nie weryfikuje, czy wartość jest dozwolona
* [ ] Czy `n` jest nieujemne
* [ ] Czy `n` mieści się w typie `int`

> **Wyjaśnienie:** `static_cast` jedynie zamienia liczbę na typ wyliczeniowy i nie sprawdza, czy istnieje element o tej wartości. Dane z zewnątrz trzeba zweryfikować osobno, np. w `switch` z obsługą nieznanych wartości.

#### Q. Co wypisze ten program w C++ z parametrem przekazanym przez wartość i przez referencję?

```cpp
#include <iostream>

void zmien(int a, int& b) {
    a = 10;
    b = 20;
}

int main() {
    int x = 1;
    int y = 2;
    zmien(x, y);
    std::cout << x << ' ' << y << '\n';
}
```

* [ ] `10 20`
* [x] `1 20`
* [ ] `1 2`
* [ ] `10 2`

> **Wyjaśnienie:** Parametr `a` jest kopią `x`, więc jego zmiana nie wpływa na wywołującego. `b` jest referencją, czyli inną nazwą zmiennej `y`, dlatego przypisanie zmienia oryginał.

#### Q. Która deklaracja funkcji z parametrami domyślnymi jest niepoprawna w C++?

* [ ] `int f(int a, int b = 2);`
* [ ] `int f(int a = 1, int b = 2);`
* [x] `int f(int a = 1, int b);`
* [ ] `int f(int a, int b);`

> **Wyjaśnienie:** Parametry z wartościami domyślnymi muszą tworzyć końcowy fragment listy, bo argumenty pomija się od prawej. Po parametrze z wartością domyślną każdy kolejny także musi ją mieć.

#### Q. Czy w C++ można w jednym zakresie zdefiniować `int oblicz(int x)` oraz `double oblicz(int x)`?

* [ ] Tak, kompilator wybierze wersję po typie zmiennej wynikowej
* [ ] Tak, ale tylko gdy obie funkcje są `inline`
* [x] Nie, funkcje różniące się tylko typem wyniku są błędem
* [ ] Nie, bo w C++ nie istnieje przeciążanie funkcji

> **Wyjaśnienie:** Przeciążenia muszą różnić się parametrami — liczbą, typami lub ich kolejnością. Typ zwracany nie wystarcza, bo kompilator wybiera funkcję na podstawie argumentów wywołania.

#### Q. Co wypisze ten program w C z funkcją przyjmującą wskaźnik?

```c
#include <stdio.h>

void zeruj(int *p) {
    *p = 0;
    p = NULL;
}

int main(void) {
    int x = 7;
    int *w = &x;
    zeruj(w);
    printf("%d %d\n", x, w != NULL);
    return 0;
}
```

* [ ] `7 1`
* [x] `0 1`
* [ ] `0 0`
* [ ] `7 0`

> **Wyjaśnienie:** Funkcja dostaje kopię adresu: zapis przez `*p` zmienia `x`, ale przypisanie `p = NULL` zmienia tylko lokalną kopię wskaźnika. W `main` wskaźnik `w` nadal wskazuje na `x`.

#### Q. Co oznacza deklaracja `void f();` w C++, a co w C przed standardem C23?

* [x] W C++ funkcję bez parametrów, w starszym C nieokreśloną listę parametrów
* [ ] W obu językach funkcję bez parametrów
* [ ] W C++ funkcję z dowolną liczbą argumentów, w C funkcję bez parametrów
* [ ] W obu językach funkcję z nieokreśloną listą parametrów

> **Wyjaśnienie:** W C++ puste nawiasy oznaczają brak parametrów. W starszych wersjach C nie określały listy parametrów, dlatego przenośny zapis w C to `void f(void);`.

#### Q. Które z tych wyrażeń jest L-wartością, jeśli `x` to `int`, `tab` to `int tab[3]`, a `add` zwraca `int` przez wartość?

* [ ] `x + 1`
* [ ] `42`
* [ ] `add(2, 3)`
* [x] `tab[1]`

> **Wyjaśnienie:** `tab[1]` oznacza konkretny, istniejący element tablicy, więc jest L-wartością. Literał, wynik działania arytmetycznego i wynik funkcji zwracany przez wartość są R-wartościami.

#### Q. Która funkcja w C++ przyjmie jako argument zarówno zmienną `int x`, jak i literał `5`?

* [ ] `void f(int& v)`
* [ ] `void f(int&& v)`
* [x] `void f(const int& v)`
* [ ] `void f(int* v)`

> **Wyjaśnienie:** Referencja do stałej wiąże się z L-wartością i z obiektem tymczasowym. `int&` nie przyjmie R-wartości `5`, `int&&` nie przyjmie L-wartości `x`, a `int*` wymaga adresu.

#### Q. Co wypisze ten program w C++ z przeciążeniami dla `int&` i `int&&`?

```cpp
#include <iostream>
#include <utility>

void g(int&) { std::cout << "L "; }
void g(int&&) { std::cout << "R "; }

void f(int&& v) {
    g(v);
    g(std::move(v));
}

int main() {
    f(5);
    std::cout << '\n';
}
```

* [ ] `R R`
* [x] `L R`
* [ ] `R L`
* [ ] `L L`

> **Wyjaśnienie:** Parametr `v` ma typ `int&&`, ale jako nazwane wyrażenie jest L-wartością, więc pierwsze wywołanie wybiera `g(int&)`. Dopiero `std::move(v)` pozwala potraktować go jako R-wartość.

#### Q. Co wypisze ten program w C++ z konstruktorem kopiującym i przenoszącym?

```cpp
#include <iostream>
#include <utility>

struct M {
    M() {}
    M(const M&) { std::cout << "kopia "; }
    M(M&&) { std::cout << "przeniesienie "; }
};

int main() {
    M a;
    M b = a;
    M c = std::move(a);
    std::cout << '\n';
}
```

* [ ] `kopia kopia`
* [x] `kopia przeniesienie`
* [ ] `przeniesienie przeniesienie`
* [ ] `przeniesienie kopia`

> **Wyjaśnienie:** `a` jest L-wartością, więc `M b = a;` wybiera konstruktor kopiujący. `std::move(a)` sam niczego nie przenosi — tylko pozwala wybrać konstruktor przenoszący `M(M&&)`.

#### Q. Co wiadomo o napisie `first` po instrukcji `std::string second = std::move(first);`?

* [ ] Na pewno jest pustym napisem
* [x] Jest poprawny, ale ma nieokreśloną zawartość
* [ ] Został zniszczony i nie wolno go używać
* [ ] Na pewno zachował dawną zawartość

> **Wyjaśnienie:** Obiekt po przeniesieniu nadal istnieje: można go zniszczyć albo przypisać mu nową wartość. Ogólna reguła nie określa jednak jego zawartości, więc nie wolno zakładać, że jest pusty.

#### Q. Co wypisze ten program w C z operatorami `&`, `|` i `^`?

```c
#include <stdio.h>

int main(void) {
    unsigned a = 5;
    unsigned b = 3;
    printf("%u %u %u\n", a & b, a | b, a ^ b);
    return 0;
}
```

* [x] `1 7 6`
* [ ] `1 6 7`
* [ ] `7 1 6`
* [ ] `0 7 6`

> **Wyjaśnienie:** `0101 & 0011 = 0001` (1), `0101 | 0011 = 0111` (7), a `0101 ^ 0011 = 0110` (6). XOR ustawia jedynkę tam, gdzie bity się różnią.

#### Q. Co wypisze ten program w C, który zeruje i przełącza bity maską?

```c
#include <stdio.h>

int main(void) {
    unsigned flags = 7;
    flags &= ~(1u << 1);
    flags ^= 1u << 3;
    printf("%u\n", flags);
    return 0;
}
```

* [ ] `5`
* [x] `13`
* [ ] `15`
* [ ] `6`

> **Wyjaśnienie:** `7` to `0111`; `&= ~(1u << 1)` zeruje bit 1 i daje `0101` (5). Następnie `^= 1u << 3` przełącza bit 3 na jedynkę: `1101`, czyli 13.

#### Q. Co wypisze ten program w C z wyrażeniem `x & (x - 1)`?

```c
#include <stdio.h>

int main(void) {
    unsigned x = 12;
    printf("%u\n", x & (x - 1));
    return 0;
}
```

* [ ] `11`
* [ ] `4`
* [x] `8`
* [ ] `0`

> **Wyjaśnienie:** `x & (x - 1)` zeruje najmniej znaczący ustawiony bit: `1100 & 1011 = 1000`. Wynik 0 oznaczałby, że niezerowe `x` jest potęgą dwójki.

#### Q. Co wypisze ten program w C porównujący `&&` z `&`?

```c
#include <stdio.h>

int main(void) {
    int a = 2;
    int b = 1;
    printf("%d %d\n", a && b, a & b);
    return 0;
}
```

* [ ] `1 1`
* [x] `1 0`
* [ ] `0 0`
* [ ] `2 1`

> **Wyjaśnienie:** `&&` sprawdza, czy obie wartości są niezerowe, i daje wynik logiczny 1. `&` działa na bitach: `10 & 01 = 00`, czyli 0 — mimo że obie liczby są „prawdziwe”.

#### Q. Na platformie, na której `int` i `uint32_t` mają po 32 bity, co można powiedzieć o wyrażeniu `x << 32` dla `uint32_t x = 1;`?

* [ ] Daje `0`, bo jedynka wypada poza typ
* [ ] Daje `1`, bo przesunięcie zawija się modulo 32
* [x] Ma niezdefiniowane zachowanie
* [ ] Daje `4294967296`

> **Wyjaśnienie:** Liczba przesunięć musi być mniejsza od szerokości typu po promocjach. Przesunięcie o 32 lub więcej bitów 32-bitowej wartości jest niezdefiniowane, dlatego przed `1u << n` sprawdza się `n < 32`.

#### Q. W tablicy bitowej złożonej z bajtów `uint8_t` w którym bajcie i na której pozycji leży bit o indeksie 21?

* [x] Bajt 2, bit 5
* [ ] Bajt 5, bit 2
* [ ] Bajt 3, bit 5
* [ ] Bajt 2, bit 6

> **Wyjaśnienie:** Numer bajtu to `21 / 8 = 2`, a pozycja w bajcie to `21 % 8 = 5`. Bajty i bity liczy się od zera, więc to bit 5 w trzecim bajcie tablicy.

#### Q. Co wypisze ten program w C++20 z negacją bitową wartości `uint8_t`?

```cpp
#include <cstdint>
#include <iostream>

int main() {
    std::uint8_t x = 5;
    std::uint8_t y = ~x;
    std::cout << static_cast<unsigned>(y) << '\n';
}
```

* [ ] `10`
* [x] `250`
* [ ] `-6`
* [ ] `5`

> **Wyjaśnienie:** `~` odwraca wszystkie bity wartości po promocji do `int`; zapis wyniku do `uint8_t` zostawia dolne 8 bitów: `11111010`, czyli 250. Szerokość typu decyduje o wyniku negacji.
