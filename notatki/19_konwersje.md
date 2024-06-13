## Konwersje

Zarówno w języku C, jak i w języku C++ istnieją mechanizmy umożliwiające konwersję wartości z jednego typu na inny. Chociaż niektóre z tych mechanizmów są wspólne dla obu języków, różnice w podejściu oraz dostępne narzędzia czynią konwersję w C++ bardziej złożoną i wszechstronną.

### Rzutowanie w C

Rzutowanie w języku C pozwala jawnie konwertować wartość jednego typu na inny. Choć czasami jest to niezbędne, rzutowanie może prowadzić do nieoczekiwanych i niejednoznacznych wyników, jeśli nie jest używane ostrożnie.

#### Podstawowe rzutowanie

Ogólny schemat rzutowania wygląda następująco:

```c
(typ)wartość;
```

Przykład rzutowania zmiennej typu `int` na `double`:

```c
int a = 10;
double b = (double)a;
```

W tym przypadku rzutowanie z typu `int` na `double` jest bezpieczne i nie prowadzi do utraty danych.

#### Rzutowanie wskaźników

Kiedy pracujemy z wskaźnikami, rzutowanie może stać się bardziej skomplikowane. Wskaźnik typu `void` jest ogólnym wskaźnikiem, który może wskazywać obiekt dowolnego typu. Często używane jest w funkcjach biblioteki standardowej, takich jak `qsort()` i `bsearch()`, aby umożliwić przechowywanie wskaźników do dowolnych danych.

Niebezpieczeństwo pojawia się, gdy próbujemy rzutować wskaźnik na `void` z powrotem na inny, konkretny typ. Jeśli wskaźnik zostanie niepoprawnie zrzutowany, może to prowadzić do niezdefiniowanego zachowania.

Oto przykład, który ilustruje rzutowanie wskaźnika na `void`:

```c
void *ptr = malloc(sizeof(int));  // zaalokowanie pamięci dla typu int
char *ptr2 = (char *)ptr;         // rzutowanie na typ char *
*ptr2 = 'a';                      
printf("%c\n", *ptr2);            // wyświetlenie znaku 'a'
free(ptr); 
```

Chociaż powyższy kod jest technicznie poprawny, jego celem jest jedynie ilustracja. W praktyce rzutowanie wskaźników powinno być wykonywane z dużą ostrożnością. Przed przekształceniem wskaźnika na `void` na wskaźnik innego typu, należy upewnić się, że pierwotnie wskaźnik ten wskazywał na odpowiedni typ danych.

### Konwersja w C++

Konwersje w C++ są bardziej złożone i wszechstronne niż w C. C++ wprowadza szereg operatorów rzutowania, które są bezpieczniejsze i bardziej przejrzyste niż tradycyjne rzutowanie w C.

#### static_cast

`static_cast` jest jednym z operatorów konwersji w C++ służącym do przeprowadzania konwersji między typami, których konwersja jest znana i sprawdzana w czasie kompilacji. Jest to najbardziej ogólny operator konwersji w C++.

```c++
int a = 10;
double b = static_cast<double>(a);
```

`static_cast` może być stosowany do konwersji między podstawowymi typami danych oraz do konwersji między wskaźnikami na klasy w ramach drzewa dziedziczenia, ale tylko w jednym kierunku (z bazowego do pochodnego lub odwrotnie).

#### dynamic_cast

`dynamic_cast` to operator konwersji, który służy do konwersji wskaźników i referencji w hierarchii dziedziczenia klas. Poprawność tej konwersji jest sprawdzana w czasie działania programu, co oznacza, że program sprawdzi w trakcie wykonania, czy rzutowanie jest właściwe.

Przykład użycia `dynamic_cast` z funkcjami:

```c++
#include <iostream>
#include <vector>

class A {
public:
    virtual void identify() const {
        std::cout << "This is class A" << std::endl;
    }
    virtual ~A() = default;  // Wirtualny destruktor dla właściwego usuwania obiektów pochodnych
};

class B : public A {
public:
    void identify() const override {
        std::cout << "This is class B" << std::endl;
    }
};

class C : public A {
public:
    void identify() const override {
        std::cout << "This is class C" << std::endl;
    }
};

int main() {
    std::vector<A *> objects{new B, new C, new A};

    for (auto obj : objects) {
        obj->identify();  // Wywołanie metody identify dla obiektów bazowych i pochodnych

        if (auto b = dynamic_cast<B *>(obj)) {
            std::cout << "Object is of type B" << std::endl;
        } else if (auto c = dynamic_cast<C *>(obj)) {
            std::cout << "Object is of type C" << std::endl;
        } else {
            std::cout << "Object is of type A" << std::endl;
        }
    }

    // Oczyszczanie pamięci
    for (auto obj : objects) {
        delete obj;
    }

    return 0;
}
```

W powyższym przykładzie mamy trzy klasy: `A`, `B` i `C`. Klasa `A` posiada wirtualną funkcję `identify`, która jest nadpisywana w klasach `B` i `C`. Dzięki temu możemy demonstrować polimorfizm.

1. **Polimorfizm i wywołanie funkcji po dynamic_cast:**
    - Kiedy wywołujemy `obj->identify()`, kompilator używa mechanizmu RTTI (Run-Time Type Information) do wywołania odpowiedniej wersji funkcji `identify` zależnie od rzeczywistego typu obiektu, nawet jeśli posługujemy się wskaźnikiem typu `A*`.
    - `dynamic_cast` jest używany do sprawdzenia, czy obiekt wskazywany przez `obj` jest typu `B`, `C` lub `A`. Jeśli rzutowanie się powiedzie (np. z `A*` na `B*`), to odpowiedni komunikat jest wypisywany.

2. **Sprawdzanie typu obiektu za pomocą dynamic_cast:**
    - `dynamic_cast` zwróci wskaźnik typu `nullptr`, jeśli rzutowanie się nie powiedzie.
    - Dzięki temu możemy sprawdzić, czy dany obiekt jest instancją określonej klasy pochodnej.

##### Uwagi

- `dynamic_cast` wymaga obecności przynajmniej jednej wirtualnej funkcji w klasie bazowej (`A`), aby mechanizm RTTI mógł działać poprawnie.
- Używanie `dynamic_cast` jest związane z dodatkowymi kosztami wydajnościowymi ze względu na sprawdzanie typu w trakcie działania programu.

#### const_cast

`const_cast` to operator rzutowania używany do dodawania lub usuwania kwalifikatora `const` z typu. Jest to jedyny sposób na usunięcie `const` i pozwala na zmianę obiektu, który został pierwotnie zadeklarowany jako `const`.

```c++
const int a = 10;
int *b = const_cast<int*>(&a);
*b = 20;  // Niebezpieczne - zmiana wartości zmiennej const
```

Należy pamiętać, że modyfikacja wartości, która została zadeklarowana jako `const`, może prowadzić do niezdefiniowanego zachowania, jeśli zmienna została pierwotnie zadeklarowana jako `const`.

#### reinterpret_cast

`reinterpret_cast` to jedno z narzędzi do wymuszania konwersji w C++. Jest to najbardziej "brutalny" sposób konwersji, pozwalający programiście na wymuszenie konwersji między dowolnymi typami. Oznacza to, że nie dokonuje ona rzeczywistej konwersji wartości, ale jedynie traktuje dane w pamięci jako inny typ.

Ogólna składnia:

```c++
typ_docelowy = reinterpret_cast<typ_docelowy>(obiekt_źródłowy);
```

Rozważmy poniższy kod:

```c++
int a = 10;
int* b = &a;
char* c = reinterpret_cast<char*>(b);
```

W powyższym przykładzie wskaźnik `b` wskazuje na `int`, natomiast `c` po operacji `reinterpret_cast` wskazuje na te same bajty w pamięci, ale traktuje je jako `char`.

##### Zastosowania reinterpret_cast

1. **Niskopoziomowe programowanie**: `reinterpret_cast` może być przydatny, gdy potrzebujemy bezpośredniego dostępu do surowych bajtów danych, na przykład przy implementacji własnych struktur danych czy protokołów komunikacyjnych.
2. **Interakcje z bibliotekami zewnętrznymi**: Często stosowany przy pracy z bibliotekami napisanymi w innych językach, które wymagają określonego formatu danych.
3. **Operacje na sprzęcie**: Używany w programowaniu systemów wbudowanych, gdzie konieczny jest dostęp do specyficznych rejestrów sprzętowych.

##### Ostrzeżenia i dobre praktyki

Należy pamiętać, że `reinterpret_cast` jest niebezpieczny. Łatwo można uzyskać nieprzewidywalne wyniki, jeśli dane nie są odpowiednio interpretowane. Kilka kluczowych punktów, o których warto pamiętać:

- **Nieprzewidywalne wyniki**: Jeśli typ docelowy nie jest odpowiednio dopasowany do źródłowego, wynik operacji może być nieprzewidywalny.
- **Brak bezpieczeństwa typów**: `reinterpret_cast` nie sprawdza zgodności typów, co może prowadzić do trudnych do zdiagnozowania błędów.
- **Czytelność i utrzymanie kodu**: Użycie tego operatora często wskazuje na to, że struktura programu nie jest optymalna lub że problem można rozwiązać w bardziej elegancki sposób.

#### Własne konwersje

C++ pozwala także na definiowanie własnych konwersji typów poprzez przeciążanie operatorów konwersji. Przykład:

```c++
class Complex {
public:
    double real, imag;
    Complex(double r, double i) : real(r), imag(i) {}

    operator double() const {
        return real;
    }
};

int main() {
    Complex c(3.0, 4.0);
    double r = c;  // używa operatora konwersji
    std::cout << r;  // wyświetli 3.0
    return 0;
}
```

W powyższym przykładzie zdefiniowano konwersję z `Complex` do `double`, która zwraca część rzeczywistą liczby zespolonej.
