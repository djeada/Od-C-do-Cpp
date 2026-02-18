## L-wartości i R-wartości w C++ (wreszcie “po ludzku”)

W C++ bardzo dużo rzeczy kręci się wokół pytania: **czy dane wyrażenie wskazuje na „konkretny obiekt w pamięci”**, czy jest tylko **tymczasowym wynikiem obliczeń**. Z tego biorą się L-wartości (*lvalues*) i R-wartości (*rvalues*). Zrozumienie tego tematu odblokowuje m.in.:

* dlaczego raz możesz przekazać zmienną do `T&`, a raz nie,
* kiedy kompilator kopiuje, a kiedy może **przenieść** obiekt,
* czemu `std::move` istnieje i co naprawdę robi.

Na start — dwa najważniejsze typy referencji:

* `T&`  → **lvalue reference** (referencja do L-wartości)
* `T&&` → **rvalue reference** (referencja do R-wartości)

### Intuicja: “czy ma nazwę i adres?”

Najprostsza (praktyczna) heurystyka:

* **L-wartość**: zwykle ma **nazwę**, **da się wskazać jej adres** (`&x`) i “żyje dłużej niż chwilę”.
* **R-wartość**: zwykle jest **tymczasowa** (wynik wyrażenia, literal, wartość zwracana przez funkcję przez wartość) i nie możesz jej sensownie traktować jako trwałego obiektu.

> Uwaga: w nowoczesnym C++ są jeszcze pojęcia `prvalue`, `xvalue`, `glvalue` — ale do większości codziennych przypadków wystarczy solidnie opanować “lvalue vs rvalue”.

### L-wartości (lvalues)

**L-wartość** to wyrażenie, które identyfikuje **konkretny obiekt** (z miejscem w pamięci). Klasycznie: coś, co **może** stać po lewej stronie `=` (jeśli jest modyfikowalne).

#### Najprostsze przykłady

```cpp
int x = 10;      // x jest L-wartością
x = 20;          // OK: przypisanie do L-wartości

int* px = &x;    // OK: można pobrać adres L-wartości
```

#### L-wartość może być modyfikowalna lub nie

```cpp
int x = 1;            // modyfikowalna L-wartość
const int cx = 2;     // niemodyfikowalna L-wartość

x = 5;                // OK
// cx = 6;            // BŁĄD: const, nie wolno zmieniać
```

#### Operatory, które często “dają L-wartość”

**Indeksowanie `[]`** – zwraca element, który zwykle jest L-wartością:

```cpp
int a[3] = {0, 0, 0};
a[1] = 7;     // a[1] jest L-wartością
```

**Dereferencja `*`** – wynik jest L-wartością (jeśli wskaźnik wskazuje na obiekt):

```cpp
int x = 10;
int* p = &x;

*p = 99;      // *p jest L-wartością
```

**Prefiksowe `++x`** zwraca L-wartość:

```cpp
int x = 1;
++x = 10;     // działa (choć rzadko tak się pisze)
```

### R-wartości (rvalues)

**R-wartość** to wyrażenie, które jest zwykle **tymczasową wartością** — “wynikiem obliczeń”. Najczęściej pojawia się po prawej stronie przypisania.

#### Typowe przykłady

```cpp
int x = 3;        // 3 to R-wartość (literal)
int y = x + 4;    // (x + 4) to R-wartość (wynik wyrażenia)
```

#### Czego nie wolno z R-wartością?

Nie możesz przypisywać “do wyniku obliczenia”:

```cpp
int x = 5;
// (x + 1) = 10;   // BŁĄD: (x + 1) jest R-wartością
```

Zwykle nie pobierzesz też adresu tymczasowej R-wartości:

```cpp
int x = 5;
// int* p = &(x + 1); // BŁĄD: nie bierze się adresu R-wartości
```

#### Funkcja zwracająca przez wartość → rvalue

```cpp
int add(int a, int b) {
    return a + b;      // zwraca tymczasowy wynik
}

int main() {
    int r = add(2, 3); // add(2,3) jest R-wartością
}
```

### Podsumowanie: L vs R w jednym miejscu

| Cecha                                  | L-wartość         | R-wartość                                 |
| -------------------------------------- | ----------------- | ----------------------------------------- |
| “Ma własny obiekt / miejsce w pamięci” | zazwyczaj tak     | zazwyczaj nie (tymczasowa)                |
| Adres `&`                              | zwykle można      | zwykle nie                                |
| Może stać po lewej stronie `=`         | jeśli nie-const   | nie                                       |
| Przykłady                              | `x`, `a[i]`, `*p` | `42`, `x+1`, `f()` (zwraca przez wartość) |

### L/R w kontekście funkcji i referencji

Tu robi się naprawdę praktycznie.

#### Przekazanie przez wartość

Funkcja dostaje kopię, więc może przyjąć i L-wartość, i R-wartość:

```cpp
void f(int v) { }

int main() {
    int x = 10;
    f(x);    // L-wartość OK
    f(20);   // R-wartość OK
}
```

#### `T&` — referencja do L-wartości

Taka funkcja wymaga **czegoś trwałego** (L-wartości), bo chce “podpiąć się” pod istniejący obiekt.

```cpp
void g(int& v) {
    v *= 2;
}

int main() {
    int x = 10;
    g(x);     // OK (L-wartość)

    // g(20); // BŁĄD (R-wartość nie pasuje do int&)
}
```

#### `const T&` — ważny wyjątek

To jest bardzo częsty wzorzec: **można podać i L-wartość, i R-wartość**, bo nie modyfikujesz argumentu, a kompilator może bezpiecznie “przedłużyć życie” tymczasowego obiektu na czas wywołania.

```cpp
void h(const int& v) { }

int main() {
    int x = 10;
    h(x);     // OK
    h(20);    // OK
}
```

#### `T&&` — referencja do R-wartości (C++11+)

Pozwala przechwytywać tymczasowe obiekty **albo** obiekty, które jawnie “oddajesz do przeniesienia”.

```cpp
#include <utility>

void k(int&& v) {
    // v to nazwana zmienna, ale związana z R-wartością
}

int main() {
    k(20);          // OK: literal to R-wartość

    int x = 10;
    // k(x);        // BŁĄD: x jest L-wartością
    k(std::move(x)); // OK: “traktuj x jak R-wartość”
}
```

**Co robi `std::move`?**
Nie przenosi samo z siebie. To tylko **rzutowanie** (konwersja) mówiące: *“od teraz możesz traktować ten obiekt jak R-wartość (czyli wolno z niego ‘zabrać’ zasoby)”*.

### Semantyka przenoszenia (move semantics) — krótko i konkretnie

Przenoszenie ma sens wtedy, gdy obiekt posiada zasób (np. bufor w pamięci). Zamiast kopiować cały zasób, można “przepiąć” wskaźniki/uchwyty.

Najczytelniej widać to na `std::vector`, `std::string`, itp.

#### Minimalny przykład z logowaniem kopii i przeniesienia

```cpp
#include <iostream>
#include <utility>
#include <vector>

struct Box {
    std::vector<int> data;

    Box() = default;

    Box(const Box& other) : data(other.data) {
        std::cout << "COPY\n";
    }

    Box(Box&& other) noexcept : data(std::move(other.data)) {
        std::cout << "MOVE\n";
    }
};

int main() {
    Box a;
    a.data = {1,2,3};

    Box b = a;             // COPY (a jest L-wartością)
    Box c = std::move(a);  // MOVE (a “oddane” do przeniesienia)
}
```

#### Co z obiektem “po przeniesieniu”?

Obiekt źródłowy (np. `a`) jest w stanie **moved-from**: ma być poprawny (da się go zniszczyć, przypisać mu nową wartość), ale jego zawartość jest zwykle “pusta/neutralna”. Dla `std::vector` najczęściej będzie pusty.

### Najczęstsze błędy i proste reguły

* Jeśli funkcja ma **modyfikować** argument: użyj `T&`.
* Jeśli funkcja ma tylko **czytać** i chcesz przyjąć także tymczasowe: `const T&`.
* Jeśli funkcja ma **przejąć zasoby** (np. zapisać w środku) i chcesz wykorzystać przenoszenie: `T&&` (lub przeciążenia / forwarding).
* `std::move(x)` nie przenosi “magicznie” — tylko pozwala wybrać ścieżkę przenoszącą (konstruktor/operatory move).
