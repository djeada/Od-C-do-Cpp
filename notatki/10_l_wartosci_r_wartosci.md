## L-wartości i R-wartości

W języku C++ pojęcia **L-wartości** (ang. *l-value*) i **R-wartości** (ang. *r-value*) są fundamentalne dla zrozumienia mechanizmów przypisywania, przekazywania argumentów do funkcji, zarządzania pamięcią oraz optymalizacji kodu. Precyzyjne rozróżnienie między tymi kategoriami wartości jest kluczowe dla pisania efektywnego i bezpiecznego kodu. W nowoczesnym C++ (od C++11 i wyżej) znaczenie tych pojęć jest dodatkowo rozszerzone o tzw. *prvalue*, *xvalue* i *glvalue*, co ma wpływ na semantykę przenoszenia i elastyczne przekazywanie obiektów do funkcji. Jednak w praktyce programistycznej, szczególnie na poziomie podstawowym i średniozaawansowanym, wystarczy dobrze rozumieć różnicę między L-wartościami a R-wartościami, aby prawidłowo korzystać z możliwości języka.

T&	lvalue reference
T&&	rvalue reference

### L-wartości

L-wartości to wyrażenia, które reprezentują obiekty mające **trwałe miejsce w pamięci** (czyli posiadają adres). Są to obiekty, do których możemy się odwołać po ich utworzeniu i które mogą być umieszczone po lewej stronie operatora przypisania. Termin "L-wartość" pochodzi od "left value", czyli wartości mogącej wystąpić po lewej stronie przypisania. Innymi słowy, L-wartość to taki byt w programie, który istnieje w dłuższym horyzoncie czasowym – dopóki program się nie zakończy lub dopóki nie zniknie zasięg, w którym ta wartość jest zdefiniowana.

#### Właściwości L-wartości

I. **Trwały adres pamięci**  

L-wartości **mają adres pamięci**, co oznacza, że można pobrać ich adres za pomocą operatora `&`. Dzięki temu możliwa jest manipulacja za pomocą wskaźników, referencji do L-wartości i innych mechanizmów języka, które operują na adresach.

II. **Modyfikowalność lub niemodyfikowalność**  

L-wartości mogą być zarówno **modyfikowalne** (np. zwykła zmienna typu `int`) jak i **niemodyfikowalne** (np. stała typu `const int`). Jeśli L-wartość jest `const`, nie można zmieniać jej wartości poprzez przypisania. Natomiast modyfikowalna L-wartość (czyli niezadeklarowana jako `const`) może być aktualizowana po jej zainicjalizowaniu.

III. **Strona operatora przypisania**  

Modyfikowalne L-wartości mogą być używane zarówno po lewej, jak i prawej stronie operatora przypisania. Niemodyfikowalne L-wartości mogą znaleźć się tylko po prawej stronie przypisania (nie można im przypisywać nowych wartości).

#### Przykłady L-wartości

```c++
int main() {
    int i = 3;        // 'i' jest modyfikowalną L-wartością
    const int ci = 5; // 'ci' jest niemodyfikowalną L-wartością

    int *pi = &i;     // '&i' zwraca adres, a 'pi' jest L-wartością (wskaźnikiem)
    int &ri = i;      // 'ri' jest referencją do L-wartości 'i'

    i = 10;           // Przypisanie do L-wartości 'i'

    // ci = 6;        // Błąd! 'ci' jest niemodyfikowalną L-wartością

    return 0;

}
```

W powyższym przykładzie `i` to L-wartość modyfikowalna, co oznacza, że możemy przypisać jej nowe wartości. Z kolei `ci` to L-wartość niemodyfikowalna, więc nie wolno zmieniać jej po inicjalizacji. Operator `&` (adres) zwraca wskaźnik (będący też L-wartością, tyle że innego typu), a referencja `ri` wiąże się z istniejącą L-wartością `i`.

#### Uwaga na temat L-wartości i operatorów

Istnieją operatory, które zwracają L-wartości, pozwalając na ich bezpośrednie modyfikowanie w kodzie. Do często spotykanych należą:

- **Operator indeksowania `[]`** umożliwia dostęp do elementu w tablicy lub obiekcie, który przeciąża ten operator, zwracając L-wartość. Dzięki temu możliwe jest przypisywanie wartości, np. `arr[0] = 10;`.
- **Operator dereferencji `*`** zwraca L-wartość, jeśli wskaźnik ma typ `T*`. Umożliwia to modyfikację zawartości pamięci, na którą wskazuje, np. `*ptr = 20;`.
- **Operator inkrementacji i dekrementacji w formie prefiksowej (`++i`, `--i`)** zwraca L-wartość, co pozwala na łączenie tych operacji z innymi działaniami na tym samym obiekcie, np. `++i += 5;`.

```c++
int arr[5];
arr[0] = 10;     // 'arr[0]' jest L-wartością
*(arr + 1) = 20; // '*(arr + 1)' jest L-wartością

int i = 2;
int j = ++i;     // '++i' zwraca L-wartość
```

### R-wartości

R-wartości to wyrażenia, które **nie mają trwałego miejsca w pamięci** i nie można pobrać ich adresu w sposób bezpośredni. Są to tymczasowe wartości, które zazwyczaj istnieją tylko w trakcie ewaluacji wyrażenia. Nazwa "R-wartość" pochodzi od "right value", co jest związane z tym, że najczęściej pojawiają się one po prawej stronie operatora przypisania. Typowe R-wartości to różne wyrażenia tymczasowe, jak np. wynik dodawania, dosłowna wartość liczbowa (tzw. *literal*), czy wywołanie funkcji zwracającej obiekt przez wartość.

#### Właściwości R-wartości

I. **Brak trwałego adresu pamięci**  

Nie można bezpośrednio pobrać adresu R-wartości, gdyż jest to coś, co najczęściej istnieje tylko chwilowo, np. w trakcie obliczania wyrażenia.

II. **Niemodyfikowalność**  

Nie można przypisać do R-wartości (np. nie można zapisać `(i + 4) = 10;`). Oznacza to, że jeśli coś jest R-wartością, jest na ogół tylko do odczytu w miejscu, w którym występuje.

III. **Czas życia**  

Ich czas życia jest krótkotrwały – zazwyczaj ogranicza się do pojedynczego wyrażenia. Przykład: `i + 4` „istnieje” jedynie podczas wyliczania wyniku dodawania.

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

W powyższym przykładzie liczba `3` oraz wyrażenie `i + 4` to R-wartości. W szczególności nie możemy zrobić `&(i + 4)`, ponieważ nie ma bezpiecznego i trwałego adresu związanego z wynikiem tego wyrażenia.

#### Funkcje zwracające R-wartości

Funkcje, które zwracają wartości przez kopię (czyli zwracają zwykły obiekt typu `T`, a nie np. `T&`), zwracają R-wartości. Otrzymany wynik jest tymczasowy i może być przypisany do jakiejś L-wartości lub wykorzystany w dalszych operacjach.

```c++
int add(int a, int b) {
    return a + b; // 'a + b' jest R-wartością
}

int main() {
    int result = add(5, 7); // 'add(5, 7)' jest R-wartością
    return 0;
}
```

### L-wartości vs R-wartości – Podsumowanie

| Typ wartości  | Trwały adres w pamięci       | Modyfikowalność                       | Strona operatora przypisania                  |
|---------------|------------------------------|---------------------------------------|-----------------------------------------------|
| **L-wartości** | Tak                          | Modyfikowalne lub niemodyfikowalne     | Mogą być po lewej (i prawej) stronie przypisania |
| **R-wartości** | Nie                          | Niemodyfikowalne (z zasady)            | Mogą być tylko po prawej stronie przypisania  |

#### Przykłady użycia

```c++
int x = 5;     // 'x' jest L-wartością, '5' jest R-wartością
int y = x + 2; // 'x + 2' jest R-wartością

x = y;         // Przypisanie do L-wartości 'x' wartości R-wartości 'y'
```

### R-wartości i L-wartości w kontekście funkcji

#### Przekazywanie argumentów przez wartość

Przy przekazywaniu argumentów przez wartość do funkcji przekazywana jest kopia argumentu. Możemy przekazywać zarówno L-wartości, jak i R-wartości, ponieważ dla funkcji pracującej na kopii nie ma znaczenia, czy oryginalne wyrażenie żyje dłużej (L-wartość), czy jest tymczasowe (R-wartość).

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

Przekazywanie argumentów przez referencję do L-wartości (`&`) umożliwia funkcji operowanie na oryginalnym obiekcie. Funkcja taka może modyfikować zmienną wejściową wywołującego, ale może być wywołana tylko z obiektami, które mają dłuższy czas życia (czyli L-wartościami).

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

Wprowadzone w C++11 referencje do R-wartości (`&&`) pozwalają na przechwytywanie R-wartości, co jest kluczowe dla implementacji **semantyki przenoszenia** (ang. *move semantics*). Dzięki temu możemy pisać funkcje, które przyjmują obiekty tymczasowe albo wyraźnie przekazane do przeniesienia (za pomocą `std::move`), a następnie efektywnie przejmować ich zasoby.

```c++
void func(int &&x) {
    x = x * 2;  // Modyfikujemy tymczasową wartość
}

int main() {
    // int a = 10;
    // func(a);          // Błąd! 'a' jest L-wartością
    func(20);           // '20' jest R-wartością
    // Jednak można wymusić R-wartość:
    int b = 10;
    func(std::move(b)); // 'std::move(b)' zamienia 'b' w R-wartość
    return 0;
}
```

Funkcja `std::move` z biblioteki `<utility>` konwertuje L-wartość na R-wartość, umożliwiając przeniesienie zasobów. W praktyce powszechnie wykorzystuje się to w konstruktorach i operatorach przenoszących, by uniknąć kosztownych kopii dużych obiektów.

### Semantyka przenoszenia (Move Semantics)

Semantyka przenoszenia w C++11 umożliwia efektywne przenoszenie zasobów (np. pamięci, uchwytów do plików) z obiektów tymczasowych lub tych, które nie są już potrzebne, do nowych obiektów, bez kosztownego kopiowania. Jest to szczególnie przydatne w sytuacjach, w których obiekt alokuje duże zasoby, a jego kopia byłaby kosztowna. Dzięki semantyce przenoszenia można uniknąć nadmiarowych operacji kopiowania, co znacznie przyspiesza działanie programów.

#### Konstruktor przenoszący i operator przypisania przenoszącego

Aby klasa mogła korzystać z semantyki przenoszenia, powinna zdefiniować:

- **Konstruktor przenoszący** przyjmujący argument w postaci `Type&&`.
- **Operator przypisania przenoszącego** także przyjmujący argument w postaci `Type&&`.

Wewnątrz tych funkcji należy przenieść zasoby z obiektu źródłowego do docelowego, najczęściej wykorzystując `std::move`.

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

**Wyjaśnienie działania:**

- **Konstruktor przenoszący** pozwala na efektywne przejęcie zasobów z innego obiektu, zamiast ich kopiowania. Przykładowo, wektor `data` z obiektu `other` jest przenoszony do `this->data`, co eliminuje konieczność alokacji i kopiowania elementów.
- **Operator przypisania przenoszącego** umożliwia przeniesienie zasobów z obiektu `other` do `this`. Po wykonaniu tej operacji `other.data` zazwyczaj zostaje ustawione w stan „moved-from”, czyli pusty lub neutralny.
- Deklaracja **`noexcept`** informuje kompilator, że funkcja przenosząca nie zgłasza wyjątków. Dzięki temu kontenery standardowe, takie jak `std::vector`, mogą wykonywać optymalizacje, np. podczas realokacji, oczekując, że przenoszenie nie spowoduje wyjątku.

#### Zalety semantyki przenoszenia

I. **Wydajność**  

Przenoszenie zasobów jest szybsze niż kopiowanie, ponieważ zazwyczaj wymaga przepisania tylko kilku wskaźników lub uchwytów, bez konieczności głębokiej kopii. Dla dużych struktur danych (np. kontenerów z biblioteki standardowej przechowujących tysiące elementów) zyski wydajnościowe mogą być ogromne.

II. **Lepsze wykorzystanie zasobów**  

Dzięki semantyce przenoszenia można uniknąć zduplikowanych alokacji czy blokad zasobów, przenosząc je tam, gdzie będą w rzeczywistości potrzebne.

III. **Optymalizacje kompilatora**  

Kompilator ma więcej możliwości do zastosowania optymalizacji, zwłaszcza jeśli pewne funkcje (np. konstruktory przenoszące) są zadeklarowane jako `noexcept`. Kod staje się bardziej efektywny i w wielu sytuacjach nie wymaga pisania ręcznych trików optymalizacyjnych.
