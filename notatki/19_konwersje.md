## Konwersje

Konwersje typów danych są kluczowym elementem programowania zarówno w języku C, jak i C++. Pozwalają na przekształcanie wartości jednego typu na inny, co jest niezbędne w wielu sytuacjach, takich jak operacje arytmetyczne między różnymi typami, interakcja z funkcjami bibliotecznymi czy manipulacja danymi na niskim poziomie. Chociaż podstawowe mechanizmy konwersji są dostępne w obu językach, C++ wprowadza bardziej zaawansowane i bezpieczne narzędzia. Zrozumienie różnic między konwersjami w C i C++ oraz umiejętne ich stosowanie jest kluczowe dla pisania efektywnego i bezpiecznego kodu.

### Rzutowanie w C

Rzutowanie w języku C jest mechanizmem pozwalającym na jawne przekształcenie jednej wartości na inny typ danych. Jest to szczególnie przydatne, gdy chcemy wymusić określone zachowanie kompilatora lub gdy pracujemy z interfejsami wymagającymi konkretnych typów danych. Jednak niewłaściwe użycie rzutowania może prowadzić do nieoczekiwanych rezultatów, trudnych do wykrycia błędów oraz niezdefiniowanego zachowania programu. Dlatego ważne jest zrozumienie zasad i ograniczeń rzutowania w C.

#### Podstawowe rzutowanie

Podstawowe rzutowanie w C pozwala na konwersję między typami arytmetycznymi, takimi jak `int`, `float`, `double`, `char` itp. Rzutowanie może być wykorzystywane do:

- Konwersji między typami całkowitymi i zmiennoprzecinkowymi, np. z `int` na `double`.
- Zmiany rozmiaru typu, np. z `int` na `short`.
- Wymuszenia określonego typu w operacjach arytmetycznych, aby uniknąć automatycznej promocji typów.

Ogólny schemat rzutowania:

```c
(typ_docelowy)wartość;
```

**Przykład rzutowania zmiennej typu `int` na `double`:**

```c
int a = 10;
double b = (double)a;
```

W tym przypadku wartość zmiennej `a` jest konwertowana na typ `double` i przypisywana do zmiennej `b`. Ponieważ konwersja z `int` na `double` jest poszerzająca (ang. *widening conversion*), nie występuje utrata danych.

**Przykład rzutowania z utratą danych:**

```c
double x = 3.14159;
int y = (int)x;  // y będzie równe 3
```

Tutaj część ułamkowa liczby `x` zostaje odrzucona, co może prowadzić do błędów, jeśli nie jest to zamierzone działanie.

##### Zasady konwersji arytmetycznych

- Typy takie jak `char` i `short` są automatycznie promowane do `int` podczas operacji arytmetycznych.
- W operacjach mieszanych typ całkowity jest konwertowany na zmiennoprzecinkowy.
- W operacjach z udziałem różnych typów zmiennoprzecinkowych (`float`, `double`, `long double`), niższy typ jest konwertowany na wyższy.

##### Potencjalne problemy

- Rzutowanie z typu o większym zakresie do typu o mniejszym zakresie może prowadzić do utraty danych.
- Przy konwersjach między typami o różnych zakresach wartości może dojść do przepełnienia lub niedomiaru, co skutkuje niezdefiniowanym zachowaniem.
- Rzutowanie między typami ze znakiem i bez znaku (`signed` i `unsigned`) może prowadzić do nieoczekiwanych wyników.

**Zalecenia:**

- Zawsze analizuj, czy rzutowanie jest bezpieczne i nie prowadzi do utraty istotnych informacji.
- Unikaj niejawnych konwersji między typami o różnych zakresach i precyzji.
- W razie wątpliwości korzystaj z jawnego rzutowania, aby zaznaczyć intencje.

#### Rzutowanie wskaźników

Rzutowanie wskaźników w C jest bardziej złożone i niesie ze sobą większe ryzyko błędów. Wskaźniki reprezentują adresy w pamięci, a nieprawidłowe ich użycie może prowadzić do naruszenia pamięci (ang. *segmentation fault*) lub innych poważnych błędów.

W języku C istnieje wskaźnik typu `void *`, który jest ogólnym wskaźnikiem mogącym przechowywać adres dowolnego typu danych. Jest on często używany w funkcjach biblioteki standardowej, takich jak `malloc()`, `qsort()`, `bsearch()`, gdzie typ danych jest nieznany lub może się różnić.

##### Przykład użycia wskaźnika `void *`:

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = malloc(sizeof(int));  // Alokacja pamięci dla typu int
    if (ptr == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int *int_ptr = (int *)ptr;  // Rzutowanie wskaźnika void* na int*
    *int_ptr = 42;
    printf("Wartość: %d\n", *int_ptr);

    free(ptr);  // Zwolnienie pamięci
    return 0;
}
```

W powyższym przykładzie:

- Funkcja `malloc()` zwraca wskaźnik typu `void *`.
- Rzutujemy go na `int *`, aby móc pracować z nim jako ze wskaźnikiem na `int`.
- Przypisujemy wartość do zaalokowanej pamięci i wyświetlamy ją.

##### Niebezpieczeństwa związane z rzutowaniem wskaźników

- Rzutowanie wskaźnika na nieodpowiedni typ może prowadzić do odczytywania lub zapisywania nieprawidłowych danych.
- Niektóre architektury wymagają, aby dane były wyrównane do określonych granic pamięci. Rzutowanie wskaźnika na typ o innym wymaganym wyrównaniu może prowadzić do błędów.
- Kompilatory zakładają, że wskaźniki różnego typu nie wskazują na ten sam obszar pamięci. Naruszenie tej zasady może prowadzić do niezdefiniowanego zachowania.

**Przykład błędnego rzutowania wskaźników:**

```c
float f = 3.14f;
int *int_ptr = (int *)&f;
printf("Wartość int: %d\n", *int_ptr);
```

Tutaj interpretujemy bajty reprezentujące liczbę zmiennoprzecinkową jako liczbę całkowitą, co zazwyczaj nie ma sensu i może prowadzić do nieprzewidywalnych wyników.

##### Bezpieczne praktyki

- Jeśli to możliwe, trzymaj się oryginalnych typów.
- Upewnij się, że rzutowane wskaźniki spełniają wymagania wyrównania dla docelowego typu.
- Korzystaj z `void *` ostrożnie**, używaj go tylko wtedy, gdy jest to konieczne i zawsze rzutuj z powrotem na właściwy typ przed użyciem.

### Konwersja w C++

Język C++ wprowadza bardziej zaawansowane mechanizmy konwersji, które mają na celu zwiększenie bezpieczeństwa i czytelności kodu. W przeciwieństwie do C, gdzie rzutowanie jest proste, ale potencjalnie niebezpieczne, C++ oferuje zestaw operatorów rzutowania, które są bardziej restrykcyjne i precyzyjne w swoim działaniu. Pozwalają one na wyraźne określenie intencji programisty i redukują ryzyko błędów wynikających z niejawnych lub niezamierzonych konwersji.

#### static_cast

`static_cast` jest jednym z operatorów konwersji w C++, służącym do przeprowadzania konwersji między typami, których konwersja jest znana i sprawdzana w czasie kompilacji. Jest to najbardziej ogólny i najczęściej używany operator rzutowania w C++. Pozwala na:

- Konwersje między typami arytmetycznymi, np. z `int` na `double` i odwrotnie.
- Rzutowanie wskaźników w hierarchii dziedziczenia klas, upcasting i downcasting bez kontroli bezpieczeństwa w czasie wykonania.
- Konwersje między typami wskaźników i referencji, pod warunkiem, że istnieje odpowiednia ścieżka konwersji.

**Przykłady:**

I. **Konwersja między typami arytmetycznymi:**

```c++
int i = 42;
double d = static_cast<double>(i);  // d = 42.0
```

II. **Upcasting w hierarchii klas:**

```c++
class Base {};
class Derived : public Base {};

Derived *d = new Derived();
Base *b = static_cast<Base *>(d);  // Bezpieczne - upcasting
```

III. **Downcasting (niezalecane z `static_cast`):**

```c++
Base *b = new Derived();
Derived *d = static_cast<Derived *>(b);  // Niebezpieczne - brak kontroli w czasie wykonania
```

W powyższym przykładzie, jeśli `b` nie wskazuje na obiekt typu `Derived`, wynik może być niezdefiniowany. Dlatego do downcastingu zaleca się używanie `dynamic_cast`.

##### Ograniczenia `static_cast`

- Nie sprawdza poprawności rzutowania podczas działania programu.
- Nie pozwala na usuwanie kwalifikatora `const` lub `volatile`; do tego służy `const_cast`.
- Nie można go użyć do rzutowania między wskaźnikami na niepowiązane typy.

##### Zalety `static_cast`

- Jest bardziej bezpieczny niż tradycyjne rzutowanie w stylu C, ponieważ jest bardziej restrykcyjny.
- Poprawia czytelność kodu, jasno wskazując intencje programisty.
- Łatwiejszy do zlokalizowania podczas przeglądania kodu lub analiz statycznych.

#### dynamic_cast

`dynamic_cast` to operator konwersji, który służy do bezpiecznego rzutowania wskaźników i referencji w hierarchii dziedziczenia klas polimorficznych (tj. takich, które zawierają co najmniej jedną wirtualną funkcję). Poprawność tej konwersji jest sprawdzana w czasie działania programu, co oznacza, że program sprawdzi podczas wykonania, czy rzutowanie jest właściwe.

##### Zastosowanie `dynamic_cast`

Najczęstszym zastosowaniem `dynamic_cast` jest **downcasting**, czyli rzutowanie wskaźnika lub referencji z klasy bazowej na klasę pochodną, gdy nie mamy pewności co do rzeczywistego typu obiektu.

**Przykład:**

```c++
#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void specificFunction() {
        std::cout << "Funkcja specyficzna dla klasy Derived\n";
    }
};

int main() {
    Base *b = new Derived();

    Derived *d = dynamic_cast<Derived *>(b);
    if (d != nullptr) {
        d->specificFunction();
    } else {
        std::cout << "Rzutowanie nie powiodło się.\n";
    }

    delete b;
    return 0;
}
```

- Tworzymy obiekt klasy `Derived`, ale przechowujemy go we wskaźniku typu `Base *`.
- Używamy `dynamic_cast` do sprawdzenia, czy `b` rzeczywiście wskazuje na obiekt typu `Derived`.
- Jeśli rzutowanie się powiedzie, możemy bezpiecznie wywołać funkcje specyficzne dla `Derived`.

##### Rzutowanie referencji

Przy rzutowaniu referencji, jeśli rzutowanie się nie powiedzie, zostanie rzucony wyjątek `std::bad_cast`:

```c++
try {
    Base &refBase = *b;
    Derived &refDerived = dynamic_cast<Derived &>(refBase);
    refDerived.specificFunction();
} catch (const std::bad_cast &e) {
    std::cout << "Rzutowanie nie powiodło się: " << e.what() << '\n';
}
```

##### Wymagania dla `dynamic_cast`

- Klasa bazowa musi zawierać przynajmniej jedną wirtualną funkcję (najczęściej jest to wirtualny destruktor).
- Mechanizm RTTI (Run-Time Type Information) musi być włączony w kompilatorze (domyślnie jest włączony).

##### Zalety i wady

**Zalety**:

- Zapewnia poprawność rzutowania w czasie wykonania.
- Ułatwia pracę z hierarchiami klas polimorficznych.

**Wady**:

- Sprawdzanie typu w czasie wykonania może być kosztowne.
- Nadużywanie może prowadzić do trudnego w utrzymaniu kodu.

#### const_cast

`const_cast` to operator rzutowania używany do dodawania lub usuwania kwalifikatorów `const` lub `volatile` z typu danych. Jest to jedyny operator rzutowania, który może zmieniać kwalifikatory typu.

##### Przykłady użycia

1. **Usunięcie kwalifikatora `const`:**

```c++
const int a = 10;
int *p = const_cast<int *>(&a);
*p = 20;  // Niezdefiniowane zachowanie!
```

Modyfikacja obiektu pierwotnie zadeklarowanego jako `const` prowadzi do niezdefiniowanego zachowania. Nawet jeśli kompilator nie zgłosi błędu, wynik może być nieprzewidywalny.

2. **Bezpieczne użycie `const_cast`:**

```c++
void printMessage(char *msg) {
   // ... przetwarzanie wiadomości
}

int main() {
   const char *text = "Witaj świecie!";
   printMessage(const_cast<char *>(text));
   return 0;
}
```

Jeśli jesteśmy pewni, że funkcja `printMessage` nie modyfikuje przekazanego tekstu, możemy bezpiecznie usunąć kwalifikator `const`. Lepszym rozwiązaniem byłoby jednak poprawienie sygnatury funkcji, aby przyjmowała `const char *`.

##### Zastosowania `const_cast`

- Gdy funkcje nie używają kwalifikatorów `const`, a my chcemy przekazać im stałe dane.
- Możemy również użyć `const_cast` do dodania kwalifikatora `const`, chociaż rzadko jest to potrzebne.

##### Ostrzeżenia

- Modyfikacja obiektu pierwotnie zadeklarowanego jako `const` jest zabroniona.
- Używaj `const_cast` tylko wtedy, gdy masz pewność, że nie naruszasz zasad bezpieczeństwa i integralności danych.
- Zamiast usuwać `const`, lepiej dostosować funkcje, aby akceptowały stałe argumenty.

#### reinterpret_cast

`reinterpret_cast` to najbardziej "brutalny" sposób konwersji w C++. Pozwala na reinterpretację bitów obiektu jako innego typu bez jakiejkolwiek konwersji danych. Jest to przydatne w sytuacjach niskopoziomowych, ale niesie ze sobą duże ryzyko błędów.

##### Przykłady użycia

1. **Konwersja wskaźnika na typ całkowity:**

```c++
void *ptr = malloc(10);
std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(ptr);
std::cout << "Adres: " << addr << '\n';
```

2. **Rzutowanie między niepowiązanymi typami wskaźników:**

```c++
class A { /* ... */ };
class B { /* ... */ };

A *a = new A();
B *b = reinterpret_cast<B *>(a);  // Niebezpieczne!
```

Taki kod jest potencjalnie niebezpieczny i może prowadzić do niezdefiniowanego zachowania.

##### Zastosowania `reinterpret_cast`

- Konwersja obiektu do ciągu bajtów i odwrotnie.
- Dostęp do rejestrów sprzętowych lub specjalnych obszarów pamięci.
- Manipulacja pamięcią na niskim poziomie, np. w implementacji własnego alokatora pamięci.

##### Ostrzeżenia i dobre praktyki

- Rzutowanie wskaźników na niepowiązane typy i ich używanie może prowadzić do niezdefiniowanego zachowania.
- Wynik działania `reinterpret_cast` może różnić się w zależności od platformy, kompilatora i architektury.
- Stosuj `reinterpret_cast` tylko wtedy, gdy nie ma innej możliwości i jesteś świadomy ryzyka.
- Jeśli potrzebujesz konwersji między typami wskaźników w hierarchii klas, użyj `static_cast` lub `dynamic_cast`. Do konwersji typów arytmetycznych stosuj `static_cast`.

#### Własne konwersje

C++ pozwala na definiowanie własnych konwersji typów poprzez przeciążanie operatorów konwersji oraz konstruktorów konwersji. Pozwala to na elastyczne i intuicyjne przekształcanie obiektów jednego typu na inny.

##### Operatory konwersji

Operator konwersji to specjalna funkcja składowa klasy, która umożliwia przekształcenie obiektu klasy na inny typ.

**Składnia:**

```c++
operator typ_docelowy() const;
```

**Przykład:**

```c++
#include <cmath>

class Complex {
public:
    double real, imag;
    Complex(double r, double i) : real(r), imag(i) {}

    // Konwersja na double - zwracamy moduł liczby zespolonej
    operator double() const {
        return sqrt(real * real + imag * imag);
    }
};

int main() {
    Complex c(3.0, 4.0);
    double magnitude = c;  // używa operatora konwersji
    std::cout << "Moduł: " << magnitude << '\n';  // wyświetli 5.0
    return 0;
}
```

##### Konstruktor konwersji

Konstruktor, który przyjmuje jeden argument, może służyć jako konstruktor konwersji, umożliwiający tworzenie obiektu danej klasy z innego typu.

**Przykład:**

```c++
class Fraction {
private:
    int numerator;
    int denominator;
public:
    Fraction(int n, int d) : numerator(n), denominator(d) {}

    // Konstruktor konwersji z int
    Fraction(int wholeNumber) : numerator(wholeNumber), denominator(1) {}
};

int main() {
    Fraction f = 5;  // Używa konstruktora konwersji
    return 0;
}
```

##### Słowo kluczowe `explicit`

Aby uniknąć niejawnych konwersji, które mogą prowadzić do nieoczekiwanych wyników, można użyć słowa kluczowego `explicit`:

```c++
class Fraction {
public:
    explicit Fraction(int wholeNumber) : numerator(wholeNumber), denominator(1) {}
    // ...
};

int main() {
    Fraction f1 = 5;            // Błąd kompilacji
    Fraction f2(5);             // Poprawne
    Fraction f3 = Fraction(5);  // Poprawne
    return 0;
}
```

##### Dobre praktyki

- Definiuj tylko te konwersje, które mają sens w kontekście Twojej klasy i nie wprowadzają dwuznaczności.
- Stosuj `explicit`, aby zapobiec niezamierzonym konwersjom, które mogą prowadzić do błędów.
- Upewnij się, że konwersje są intuicyjne dla innych programistów i poprawiają czytelność kodu.

##### Potencjalne problemy

- Zbyt wiele możliwych konwersji może prowadzić do konfliktów i utrudniać kompilację.
- Niejawne konwersje mogą prowadzić do wywoływania niewłaściwych funkcji przeciążonych lub operatorów.
- Używaj operatorów konwersji z rozwagą i tylko wtedy, gdy jest to uzasadnione.
- Preferuj jawne konwersje za pomocą konstruktorów i słowa kluczowego `explicit`.
- Zawsze rozważ wpływ na czytelność i utrzymanie kodu.
