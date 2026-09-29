# L-wartości i R-wartości w C++

Ta lekcja rozdziela trzy pojęcia: **wartość obiektu**, **kategorię wyrażenia** i **referencję**. Ma to znaczenie przy przypisywaniu do zmiennych, przekazywaniu argumentów funkcjom i przenoszeniu obiektów.

## Wartość obiektu a kategoria wyrażenia

Zmienna `x` może przechowywać liczbę `10`. To jest wartość zmiennej. Wyrażenie `x` ma natomiast kategorię wartości, która mówi, jak można użyć tego wyrażenia.

- **L-wartość** (*lvalue*) oznacza konkretny obiekt.
- **R-wartość** (*rvalue*) zwykle dostarcza wynik obliczenia albo wartość tymczasową.

```cpp
int x = 10;       // x oznacza istniejący obiekt
x = 20;           // zmieniamy wartość tego obiektu

int y = x + 5;    // x + 5 jest wynikiem obliczenia: 25
```

Po tych instrukcjach `x` przechowuje `20`, a `y` przechowuje `25`. Wyrażenie `x` oznacza obiekt, w którym przechowywane jest `x`, natomiast `x + 5` daje nowy wynik. Dlatego `x` jest L-wartością, a `x + 5` jest R-wartością.

Nazwa może mylić: **L-wartość nie oznacza po prostu wyrażenia po lewej stronie `=`**. Stała także jest L-wartością, choć nie można jej zmienić:

```cpp
const int limit = 100;
// limit = 200;  // błąd: obiekt jest stały
```

Kategoria wyrażenia i możliwość modyfikacji to dwie różne sprawy. O zapisie do obiektu decyduje również jego typ, na przykład kwalifikator `const`.

## L-wartości: wyrażenia oznaczające obiekt

Zmienna, element tablicy i dereferencja poprawnego wskaźnika są typowymi L-wartościami:

```cpp
int main() {
    int x = 10;
    int numbers[3] = {4, 5, 6};
    int* pointer = &x;

    x = 11;             // x oznacza obiekt x
    numbers[1] = 50;    // numbers[1] oznacza drugi element tablicy
    *pointer = 12;      // *pointer oznacza obiekt x

    // x ma teraz 12, a numbers[1] ma 50
}
```

Operator `&` pobiera adres obiektu. Operator `*` użyty przed wskaźnikiem daje dostęp do obiektu pod zapisanym adresem. Ponieważ `pointer` przechowuje adres `x`, wyrażenia `*pointer` i `x` odnoszą się do tego samego obiektu. Wskaźniki omówimy dokładniej w następnej lekcji.

Prefiksowy operator zwiększania także daje dostęp do obiektu, który zmienia:

```cpp
int x = 1;
++x = 10;  // poprawne, ale nieczytelne: ++x oznacza nadal obiekt x
```

W zwykłym kodzie lepiej napisać po prostu `x = 10`. Ten przykład pokazuje, że nazwa „L-wartość” nie jest tylko opisem lewej strony przypisania.

## R-wartości: wyniki i wartości tymczasowe

Literały i wyniki zwykłych działań arytmetycznych są typowymi R-wartościami:

```cpp
int x = 5;
int a = 42;        // 42 jest R-wartością
int b = x + 1;     // x + 1 jest R-wartością
// (x + 1) = 10;   // błąd: wyniku obliczenia nie można tak zmienić
// int* p = &(x + 1); // błąd: nie można pobrać adresu takiego wyniku
```

Funkcja zwracająca wynik przez wartość również zwykle daje R-wartość:

```cpp
int add(int left, int right) {
    return left + right;
}

int main() {
    int result = add(2, 3);  // wywołanie dostarcza wynik 5
}
```

To jest użyteczna intuicja, ale nie cała reguła C++. W dokładniejszym podziale R-wartości obejmują *prvalue* oraz *xvalue*. Nie każda R-wartość jest więc „wartością bez obiektu”: na przykład `std::move(x)` odnosi się do istniejącego `x`, ale pozwala wybrać operację przenoszącą. Na początek zapamiętaj typowe przykłady: nazwa zmiennej `x` jest L-wartością, a `42` i `x + 1` są R-wartościami.

## Referencja jest aliasem obiektu

Referencja to druga nazwa istniejącego obiektu. Nie tworzy kopii:

```cpp
int main() {
    int original = 5;
    int& alias = original;  // alias odnosi się do tego samego obiektu

    alias = 8;              // zmienia original
    // original ma teraz 8
}
```

Referencję trzeba powiązać z obiektem przy deklaracji. Nie można później przepiąć jej na inny obiekt. Wskaźnik jest inny: to osobna zmienna przechowująca adres i może mieć wartość `nullptr`. Porównanie referencji ze wskaźnikiem znajduje się w następnej lekcji.

## Parametry funkcji: kopia czy ten sam obiekt?

### Przekazanie przez wartość: `T`

Parametr `T value` jest osobną zmienną funkcji. Zmiana parametru nie zmienia argumentu wywołującego:

```cpp
#include <iostream>

void setToZero(int value) {
    value = 0;  // zmieniamy lokalną kopię
}

int main() {
    int score = 7;
    setToZero(score);
    std::cout << score << '\n';  // 7
}
```

Funkcja może przyjąć L-wartość i R-wartość, bo w obu przypadkach tworzy własny parametr. Dla małych typów, takich jak `int`, przekazanie przez wartość jest zwykle dobrym wyborem.

### Niestała referencja: `T&`

Parametr `T&` wiąże się z L-wartością. Funkcja może zmienić ten sam obiekt, który przekazał wywołujący:

```cpp
#include <iostream>

void addOne(int& value) {
    ++value;  // value jest inną nazwą argumentu
}

int main() {
    int score = 7;
    addOne(score);
    std::cout << score << '\n';  // 8
    // addOne(7);                // błąd: int& nie wiąże się z R-wartością
}
```

Użyj `T&`, gdy zmiana argumentu jest częścią zadania funkcji. Nie używaj go tylko po to, by uniknąć kopiowania małej liczby.

### Referencja do stałej: `const T&`

`const T&` pozwala czytać obiekt bez tworzenia kopii i nie pozwala zmieniać go przez tę referencję. Może też przyjąć wartość tymczasową:

```cpp
#include <iostream>
#include <string>

void print(const std::string& text) {
    std::cout << text << '\n';
}

int main() {
    std::string message = "Cześć";
    print(message);                 // referencja do istniejącego obiektu
    print(std::string("Witaj"));    // obiekt tymczasowy żyje przez wywołanie
}
```

Tymczasowy argument do parametru funkcji istnieje do końca wyrażenia zawierającego wywołanie. Nie zachowuj referencji ani wskaźnika do takiego argumentu na później: po zakończeniu wywołania obiekt może już nie istnieć.

### Referencja R-wartości: `T&&`

Parametr `T&&` może wiązać się z R-wartością. Przydaje się między innymi w funkcjach i konstruktorach przenoszących:

```cpp
#include <iostream>
#include <utility>

void acceptTemporary(int&& value) {
    std::cout << value << '\n';
}

int main() {
    int x = 10;
    acceptTemporary(20);            // 20 jest R-wartością
    // acceptTemporary(x);          // błąd: x jest L-wartością
    acceptTemporary(std::move(x));  // jawnie traktujemy x jako R-wartość
}
```

Wewnątrz funkcji parametr `value` ma nazwę, więc samo wyrażenie `value` jest L-wartością — mimo że jego typ to `int&&`. To ważna reguła przy implementowaniu przenoszenia.

## `std::move` i przenoszenie

`std::move` z nagłówka `<utility>` samo nie przenosi danych. Pozwala potraktować obiekt jako R-wartość. Dopiero konstruktor lub operator przypisania typu obiektu może wykonać przeniesienie.

```cpp
#include <iostream>
#include <string>
#include <utility>

struct Message {
    std::string text;

    explicit Message(std::string value)
        : text(std::move(value)) {}

    Message(const Message& other)
        : text(other.text) {
        std::cout << "kopiowanie\n";
    }

    Message(Message&& other)
        : text(std::move(other.text)) {
        std::cout << "przenoszenie\n";
    }
};

int main() {
    Message first("długi tekst");
    Message copy = first;                // kopiuje napis
    Message moved = std::move(first);    // wybiera konstruktor przenoszący

    std::cout << copy.text << '\n';
    std::cout << moved.text << '\n';
}
```

Przy `copy` powstaje niezależna kopia `first.text`. Przy `moved` wyrażenie `std::move(first)` pozwala wybrać konstruktor `Message(Message&&)`, który przekazuje napis do przenoszącego konstruktora `std::string`. Szczegóły przejęcia zasobu zależą od implementacji `std::string`.

Po przeniesieniu `first` nadal jest poprawnym obiektem: można go zniszczyć albo przypisać mu nową wartość. Jego poprzednia zawartość może się zmienić; dla `std::string` jest poprawna, ale nieokreślona przez ogólną regułę języka. Nie zakładaj, że zawsze będzie pusty. Przenoszenie jest przydatne głównie dla obiektów zarządzających zasobami, takich jak napisy i wektory; dla `int` zwykle niczego nie zyskujemy.

## Jak wybrać parametr

| Zapis | Co otrzymuje funkcja | Typowe zastosowanie |
| --- | --- | --- |
| `T value` | własną kopię | małe wartości |
| `T& value` | dostęp do zmiennego obiektu wywołującego | funkcja ma zmienić argument |
| `const T& value` | dostęp tylko do odczytu, także do wartości tymczasowej | odczyt większego obiektu bez kopii |
| `T&& value` | dostęp do R-wartości | implementacja przenoszenia lub API przyjmujące tymczasowe obiekty |

## Najważniejsze wnioski

- Kategoria wyrażenia i możliwość modyfikacji obiektu to odrębne sprawy: L-wartość może być stała.
- `x`, `tab[0]` i `*pointer` to typowe L-wartości; `42`, `x + 1` i wynik funkcji zwracany przez wartość to typowe R-wartości.
- Referencja jest aliasem, a nie kopią ani wskaźnikiem.
- Nazwany parametr jest L-wartością wewnątrz funkcji, także gdy zadeklarowano go jako `T&&`.
- `std::move(x)` nie przenosi samo z siebie. Umożliwia wybranie operacji przenoszącej, która może zmienić stan `x`.
