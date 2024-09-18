## L-wartości i R-wartości

W języku C++ pojęcia L-wartości (ang. *l-value*) i R-wartości (ang. *r-value*) są fundamentalne dla zrozumienia mechanizmów przypisywania, przekazywania argumentów do funkcji, zarządzania pamięcią oraz optymalizacji kodu. Precyzyjne rozróżnienie między tymi kategoriami wartości jest kluczowe dla pisania efektywnego i bezpiecznego kodu.

### L-wartości

L-wartości to wyrażenia, które reprezentują obiekty mające **trwałe miejsce w pamięci** (czyli posiadają adres). Są to obiekty, do których możemy się odwołać po ich utworzeniu i które mogą być umieszczone po lewej stronie operatora przypisania. Termin "L-wartość" pochodzi od "left value", czyli wartości mogącej wystąpić po lewej stronie przypisania.

#### Właściwości L-wartości

- **Mają adres pamięci**: Możemy pobrać adres L-wartości za pomocą operatora `&`.
- Mogą być **modyfikowalne** lub **niemodyfikowalne**:
- **Modyfikowalne L-wartości** (ang. *modifiable l-values*) to takie, które można zmienić (nie są `const`).
- **Niemodyfikowalne L-wartości** to takie, które są oznaczone jako `const` i nie można ich zmienić po inicjalizacji.
- Mogą być używane po **lewej** i **prawej** stronie operatora przypisania (o ile są modyfikowalne).

#### Przykłady L-wartości

```c++
int main() {
    int i = 3;        // 'i' jest modyfikowalną L-wartością
    const int ci = 5; // 'ci' jest niemodyfikowalną L-wartością

    int *pi = &i;     // '&i' zwraca adres, 'pi' jest L-wartością
    int &ri = i;      // 'ri' jest referencją do L-wartości 'i'

    i = 10;           // Przypisanie do L-wartości 'i'
    // ci = 6;        // Błąd! 'ci' jest niemodyfikowalną L-wartością

    return 0;
}
```

#### Uwaga na temat L-wartości i operatorów

Niektóre operatory w C++ zwracają L-wartości, np. operator indeksowania `[]`, operator dereferencji `*` czy operator inkrementacji/dekrementacji w formie prefiksowej.

```c++
int arr[5];
arr[0] = 10;     // 'arr[0]' jest L-wartością
*(arr + 1) = 20; // '*(arr + 1)' jest L-wartością

int j = ++i;     // '++i' zwraca L-wartość
```

### R-wartości

R-wartości to wyrażenia, które **nie mają trwałego miejsca w pamięci**, czyli nie można pobrać ich adresu w sposób bezpośredni. Są to tymczasowe wartości, które zazwyczaj istnieją tylko w trakcie ewaluacji wyrażenia. Nazwa "R-wartość" pochodzi od "right value", ponieważ najczęściej pojawiają się po prawej stronie operatora przypisania.

#### Właściwości R-wartości

- Nie można bezpośrednio pobrać adresu R-wartości (wyjątkiem są L-wartości przenoszalne od C++11).
- Nie można przypisać do R-wartości.
- Ich czas życia jest zazwyczaj krótki i ogranicza się do pojedynczego wyrażenia.

#### Przykłady R-wartości

```c++
int main() {
    int i = 3;         // '3' jest R-wartością
    int sum = i + 4;   // 'i + 4' jest R-wartością

    // int *p = &(i + 4); // Błąd! Nie można pobrać adresu R-wartości
    // (i + 4) = 10;      // Błąd! Nie można przypisać do R-wartości

    return 0;
}
```

#### Funkcje zwracające R-wartości

Funkcje, które zwracają wartości przez kopię, zwracają R-wartości.

```c++
int add(int a, int b) {
    return a + b; // 'a + b' jest R-wartością
}

int main() {
    int result = add(5, 7); // 'add(5, 7)' jest R-wartością
    return 0;
}
```

### L-wartości vs R-wartości

| Typ wartości  | Trwały adres w pamięci       | Modyfikowalność           | Strona operatora przypisania          |
|---------------|------------------------------|---------------------------|---------------------------------------|
| **L-wartości** | Tak                          | Modyfikowalne lub niemodyfikowalne | Mogą być po lewej stronie operatora przypisania |
| **R-wartości** | Nie                          | Niemodyfikowalne           | Mogą być tylko po prawej stronie operatora przypisania |

#### Przykłady użycia

```c++
int x = 5;     // 'x' jest L-wartością, '5' jest R-wartością
int y = x + 2; // 'x + 2' jest R-wartością

x = y;         // Przypisanie do L-wartości 'x' wartości R-wartości 'y'
```

### R-wartości i L-wartości w kontekście funkcji

#### Przekazywanie argumentów przez wartość

Przy przekazywaniu argumentów przez wartość do funkcji przekazywana jest kopia argumentu. Możemy przekazywać zarówno L-wartości, jak i R-wartości.

```c++
void func(int x) {
    // 'x' jest lokalną kopią przekazanego argumentu
}

int main() {
    int a = 10;
    func(a);    // 'a' jest L-wartością
    func(20);   // '20' jest R-wartością
    return 0;
}
```

#### Przekazywanie argumentów przez referencję do L-wartości

Przekazywanie argumentów przez referencję do L-wartości (`&`) umożliwia funkcji operowanie na oryginalnym obiekcie.

```c++
void func(int &x) {
    x = x * 2;  // Modyfikujemy oryginalną wartość
}

int main() {
    int a = 10;
    func(a);    // 'a' jest L-wartością
    // func(20); // Błąd! '20' jest R-wartością, nie można przekazać do 'int &'
    return 0;
}
```

#### R-wartościowe referencje (C++11 i nowsze)

Wprowadzone w C++11 referencje do R-wartości (`&&`) pozwalają na przechwytywanie R-wartości, co jest kluczowe dla implementacji semantyki przenoszenia.

```c++
void func(int &&x) {
    x = x * 2;  // Modyfikujemy tymczasową wartość
}

int main() {
    // int a = 10;
    // func(a);     // Błąd! 'a' jest L-wartością
    func(20);      // '20' jest R-wartością
    func(std::move(a)); // 'std::move(a)' zamienia 'a' w R-wartość
    return 0;
}
```

#### Uwaga na temat `std::move`

Funkcja `std::move` z biblioteki `<utility>` konwertuje L-wartość na R-wartość, umożliwiając przeniesienie zasobów.

```c++
#include <utility>

int main() {
    std::string str = "Hello";
    std::string newStr = std::move(str); // Przeniesienie zawartości 'str' do 'newStr'
    // 'str' jest teraz pusty lub w stanie "moved-from"
    return 0;
}
```

### Semantyka przenoszenia (Move Semantics)

Semantyka przenoszenia w C++11 umożliwia efektywne przenoszenie zasobów (np. pamięci, uchwytów do plików) z obiektów tymczasowych lub tych, które nie są już potrzebne, do nowych obiektów, bez kosztownego kopiowania.

#### Konstruktor przenoszący i operator przypisania przenoszącego

Aby klasa mogła korzystać z semantyki przenoszenia, powinna zdefiniować:

- **Konstruktor przenoszący** przyjmuje `Type&&` jako argument.
- **Operator przypisania przenoszącego** przyjmuje `Type&&` jako argument.

#### Przykład klasy z semantyką przenoszenia

```c++
#include <iostream>
#include <vector>

class MoveExample {
public:
    std::vector<int> data;

    // Konstruktor domyślny
    MoveExample() = default;

    // Konstruktor kopiujący
    MoveExample(const MoveExample &other) : data(other.data) {
        std::cout << "Konstruktor kopiujący\n";
    }

    // Konstruktor przenoszący
    MoveExample(MoveExample &&other) noexcept : data(std::move(other.data)) {
        std::cout << "Konstruktor przenoszący\n";
    }

    // Operator przypisania kopiującego
    MoveExample& operator=(const MoveExample &other) {
        std::cout << "Operator przypisania kopiującego\n";
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    // Operator przypisania przenoszącego
    MoveExample& operator=(MoveExample &&other) noexcept {
        std::cout << "Operator przypisania przenoszącego\n";
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

    // Funkcja do wyświetlania zawartości
    void display() const {
        for (int i : data) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    MoveExample me1;
    me1.data = {1, 2, 3, 4, 5};

    MoveExample me2 = me1;            // Wywołanie konstruktora kopiującego
    MoveExample me3 = std::move(me1); // Wywołanie konstruktora przenoszącego

    me2.display(); // Wyświetla: 1 2 3 4 5
    me3.display(); // Wyświetla: 1 2 3 4 5

    me2 = me3;             // Wywołanie operatora przypisania kopiującego
    me2 = MoveExample();   // Wywołanie operatora przypisania przenoszącego

    return 0;
}
```

#### Wyjaśnienie działania

- **Konstruktor przenoszący** przejmuje zasoby od obiektu źródłowego, minimalizując kopiowanie.
- **Operator przypisania przenoszącego** przenosi zasoby z obiektu źródłowego do docelowego.
- **`noexcept`** to deklaracja, że funkcja nie rzuca wyjątków; ważne dla optymalizacji.

#### Zalety semantyki przenoszenia

- Przenoszenie zasobów jest szybsze niż kopiowanie.
- Pozwala kompilatorowi na lepsze optymalizacje, szczególnie w przypadku obiektów tymczasowych.

