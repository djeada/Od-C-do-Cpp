## Przeciążanie

Przeciążanie (ang. *overloading*) to mechanizm programistyczny umożliwiający definiowanie wielu funkcji lub operatorów o tej samej nazwie, ale różniących się sygnaturą, czyli listą parametrów i ich typami. Dzięki temu kompilator potrafi wybrać odpowiednią wersję funkcji lub operatora na podstawie kontekstu wywołania i przekazanych argumentów. Przeciążanie jest szeroko stosowane w językach programowania takich jak C++, C# czy Java, w celu zwiększenia elastyczności, czytelności oraz reużywalności kodu.

Mechanizm przeciążania pozwala programistom na tworzenie interfejsów, które są bardziej intuicyjne i spójne, ponieważ umożliwiają użycie tej samej nazwy dla operacji logicznie ze sobą powiązanych, ale działających na różnych typach danych. Jest to szczególnie przydatne w programowaniu obiektowym, gdzie polimorfizm i abstrakcja odgrywają kluczową rolę.

### Przeciążanie funkcji

Przeciążanie funkcji (ang. *function overloading*) pozwala na definiowanie wielu wersji funkcji o tej samej nazwie, ale różniących się listą parametrów. Kompilator na podstawie sygnatury funkcji, czyli liczby, typów i kolejności parametrów, decyduje, którą wersję funkcji wywołać w danym momencie.

#### Zasady przeciążania funkcji

Podczas przeciążania funkcji należy przestrzegać kilku istotnych zasad:

1. Każda przeciążona funkcja musi mieć unikalną sygnaturę. Różnice mogą dotyczyć liczby parametrów, ich typów lub kolejności typów parametrów.
2. Różnica jedynie w typie zwracanym funkcji nie jest wystarczająca do jej przeciążenia. Kompilator nie jest w stanie rozróżnić funkcji tylko na podstawie typu zwracanego.
3. Należy unikać sytuacji, w których kompilator nie może jednoznacznie wybrać odpowiedniej funkcji, np. gdy używane są domyślne wartości argumentów w sposób powodujący konflikt.

#### Przykład przeciążania funkcji

Poniższy kod w języku C++ ilustruje przeciążanie funkcji:

```cpp
#include <iostream>

// Funkcja przyjmująca int
void f(int a) {
    std::cout << "Wywołano f(int a) z a = " << a << std::endl;
}

// Funkcja przyjmująca double
void f(double a) {
    std::cout << "Wywołano f(double a) z a = " << a << std::endl;
}

// Funkcja przyjmująca int i double
void f(int a, double b) {
    std::cout << "Wywołano f(int a, double b) z a = " << a << ", b = " << b << std::endl;
}

int main() {
    int x = 5;
    double y = 3.14;

    f(x);          // Wywołuje f(int a)
    f(y);          // Wywołuje f(double a)
    f(x, y);       // Wywołuje f(int a, double b)

    return 0;
}
```

W powyższym przykładzie zdefiniowano trzy funkcje o tej samej nazwie `f`, ale różniące się listą parametrów. Kompilator na podstawie przekazanych argumentów decyduje, którą wersję funkcji wywołać.

#### Problemy z domyślnymi wartościami argumentów

Użycie domyślnych wartości argumentów w przeciążanych funkcjach może prowadzić do niejednoznaczności. Rozważmy następujący przykład:

```cpp
#include <iostream>

// Funkcja z jednym parametrem int
void f(int a) {
    std::cout << "Wywołano f(int a) z a = " << a << std::endl;
}

// Funkcja z dwoma parametrami, drugi ma wartość domyślną
void f(int a, double b = 0.0) {
    std::cout << "Wywołano f(int a, double b) z a = " << a << ", b = " << b << std::endl;
}

int main() {
    f(10);  // Błąd: niejednoznaczne wywołanie

    return 0;
}
```

W tym przypadku kompilator nie jest w stanie jednoznacznie określić, którą funkcję wywołać dla `f(10)`, ponieważ oba prototypy funkcji mogą pasować: `f(int a)` oraz `f(int a, double b = 0.0)`.

Aby uniknąć takich sytuacji, należy ostrożnie używać domyślnych wartości argumentów w przeciążanych funkcjach i unikać nakładania się sygnatur.

#### Rozwiązywanie konfliktów

Jeśli występuje konflikt, można go rozwiązać na kilka sposobów:

- Tak, aby sygnatury były jednoznaczne i nie powodowały konfliktów.
- W przypadku, gdy domyślne wartości powodują niejednoznaczność.
- Podczas wywołania funkcji można zastosować rzutowanie, aby wymusić wywołanie konkretnej wersji funkcji.

### Przeciążanie operatorów

Przeciążanie operatorów to cecha języka C++, która umożliwia redefiniowanie działania standardowych operatorów dla typów zdefiniowanych przez użytkownika (klas i struktur). Pozwala to na intuicyjne użycie operatorów takich jak `+`, `-`, `*`, `/`, `==`, `!=` itp., w kontekście obiektów klas użytkownika.

#### Zasady przeciążania operatorów

- Przeciążany operator musi mieć przynajmniej jeden operand będący obiektem klasy lub struktury zdefiniowanej przez użytkownika.
- Można przeciążać tylko istniejące operatory. Nie można definiować nowych symboli operatorów.
- Liczba operandów operatora musi pozostać taka sama jak w wersji wbudowanej.
- Priorytet i wiązanie operatora pozostają niezmienione.

#### Przykład przeciążania operatorów

Rozważmy klasę `Kompleks`, reprezentującą liczby zespolone:

```cpp
#include <iostream>

class Kompleks {
private:
    double re;
    double im;

public:
    Kompleks(double re = 0.0, double im = 0.0) : re(re), im(im) {}

    // Przeciążenie operatora dodawania
    Kompleks operator+(const Kompleks& other) const {
        return Kompleks(re + other.re, im + other.im);
    }

    // Przeciążenie operatora mnożenia
    Kompleks operator*(const Kompleks& other) const {
        return Kompleks(re * other.re - im * other.im, re * other.im + im * other.re);
    }

    // Przeciążenie operatora wyjścia <<
    friend std::ostream& operator<<(std::ostream& os, const Kompleks& k) {
        os << "(" << k.re << " + " << k.im << "i)";
        return os;
    }
};

int main() {
    Kompleks k1(1.0, 2.0);
    Kompleks k2(3.0, 4.0);

    Kompleks suma = k1 + k2;         // Użycie operatora +
    Kompleks iloczyn = k1 * k2;      // Użycie operatora *

    std::cout << "Suma: " << suma << std::endl;
    std::cout << "Iloczyn: " << iloczyn << std::endl;

    return 0;
}
```

W powyższym przykładzie przeciążono operator `+` do dodawania liczb zespolonych oraz operator `*` do ich mnożenia. Dodatkowo przeciążono operator `<<` w celu wygodnego wyświetlania obiektów klasy `Kompleks`.

#### Przeciążanie operatorów inkrementacji i dekrementacji

Operatory inkrementacji (`++`) i dekrementacji (`--`) mogą być przeciążane w wersjach przedrostkowych i przyrostkowych. Wersje te różnią się sygnaturą:

- **Operator przedrostkowy** jest przeciążany jako metoda bez parametrów.
- **Operator przyrostkowy** jest przeciążany jako metoda z fikcyjnym parametrem typu `int`.

Przykład:

```cpp
class Licznik {
private:
    int wartość;

public:
    Licznik(int wartość = 0) : wartość(wartość) {}

    // Operator przedrostkowy ++x
    Licznik& operator++() {
        ++wartość;
        return *this;
    }

    // Operator przyrostkowy x++
    Licznik operator++(int) {
        Licznik temp(*this);
        ++wartość;
        return temp;
    }

    int getWartość() const {
        return wartość;
    }
};

int main() {
    Licznik licznik;

    ++licznik;  // Wywołuje operator przedrostkowy
    licznik++;  // Wywołuje operator przyrostkowy

    std::cout << "Wartość licznika: " << licznik.getWartość() << std::endl;

    return 0;
}
```

#### Ograniczenia przeciążania operatorów

Nie wszystkie operatory mogą być przeciążane. Do operatorów niepodlegających przeciążeniu należą:

| Nazwa                    | Operator | Opis                                                                 |
|--------------------------|----------|----------------------------------------------------------------------|
| **Operator zakresu**      | `::`     | Używany do uzyskania dostępu do członków klasy lub przestrzeni nazw.  |
| **Operator członkowski**  | `.`      | Używany do uzyskania dostępu do elementów obiektu.                    |
| **Operator rzutowania typu** | `sizeof` | Zwraca rozmiar typu lub obiektu w bajtach.                           |
| **Operator warunkowy**    | `?:`     | Używany do wyrażenia warunkowego (skrócona forma instrukcji `if`).    |

Ponadto, nie można zmieniać liczby operandów ani priorytetów operatorów.

#### Dobre praktyki przy przeciążaniu operatorów

- Przeciążone operatory powinny działać w sposób zgodny z ich pierwotnym znaczeniem. Np. operator `+` powinien reprezentować jakąś formę dodawania.
- Operatory powinny być przeciążane w sposób przewidywalny, bez wprowadzania nieoczekiwanych efektów ubocznych.
- Kod wykorzystujący przeciążone operatory powinien być czytelny dla innych programistów.

### Zalety i Wady Przeciążania

#### Zalety

1. Umożliwia użycie naturalnej składni dla operacji na typach zdefiniowanych przez użytkownika, co zwiększa zrozumiałość kodu.
2. Pozwala na dostosowanie zachowania operatorów do specyficznych potrzeb aplikacji.
3. Dzięki przeciążaniu funkcji można tworzyć uniwersalne interfejsy obsługujące różne typy danych.
4. Wykorzystuje mechanizmy polimorfizmu na poziomie kompilacji, co może prowadzić do optymalizacji wydajnościowych.

#### Wady

1. Nadmierne przeciążanie może skomplikować proces kompilacji i zwiększyć czas kompilacji.
2. Może prowadzić do sytuacji, w których kompilator nie jest w stanie jednoznacznie wybrać odpowiedniej funkcji lub operatora.
3. Zwiększa złożoność kodu, co może utrudniać jego analizę i debugowanie.
4. Nieodpowiedzialne przeciążanie operatorów może prowadzić do kodu trudnego do zrozumienia i utrzymania.
5. Użycie przeciążania w sposób nieintuicyjny może wprowadzać zamieszanie i utrudniać zrozumienie kodu przez innych programistów.
