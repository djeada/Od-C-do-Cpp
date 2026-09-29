# Dziedziczenie i polimorfizm

> Przykłady w tej notatce wymagają C++14. Używają `std::make_unique`, wprowadzonego w C++14.

Wyobraźmy sobie program, który oblicza pola różnych figur. Można napisać osobne funkcje dla prostokątów i kół, ale każda nowa figura wymagałaby dopisywania kolejnych warunków. Wspólny interfejs pozwala powiedzieć programowi: „oblicz pole tej figury”, bez sprawdzania, czy jest ona prostokątem, czy kołem. W C++ można zbudować taki interfejs za pomocą klasy bazowej i funkcji wirtualnych.

## Klasa bazowa i klasy pochodne

Klasa bazowa zawiera wspólne dane lub operacje. Klasa pochodna przejmuje jej część interfejsu i może dodać własne składowe albo zastąpić wybrane zachowania. Zapis `class Prostokat : public Figura` oznacza publiczne dziedziczenie: `Prostokat` jest rodzajem `Figura`, więc można użyć prostokąta tam, gdzie oczekuje się figury.

Poniższy program tworzy prostokąt i koło, przechowuje je pod wspólnym typem `Figura` i prosi każde o obliczenie pola:

```cpp
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Figura {
    std::string nazwa_;

public:
    explicit Figura(std::string nazwa) : nazwa_(std::move(nazwa)) {}
    virtual ~Figura() = default;

    const std::string& nazwa() const { return nazwa_; }
    virtual double pole() const = 0;
};

class Prostokat : public Figura {
    double szerokosc_;
    double wysokosc_;

public:
    Prostokat(std::string nazwa, double szerokosc, double wysokosc)
        : Figura(std::move(nazwa)),
          szerokosc_(szerokosc), wysokosc_(wysokosc) {}

    double pole() const override {
        return szerokosc_ * wysokosc_;
    }
};

class Kolo : public Figura {
    double promien_;

public:
    Kolo(std::string nazwa, double promien)
        : Figura(std::move(nazwa)), promien_(promien) {}

    double pole() const override {
        constexpr double pi = 3.141592653589793;
        return pi * promien_ * promien_;
    }
};

int main() {
    std::vector<std::unique_ptr<Figura>> figury;
    figury.push_back(std::make_unique<Prostokat>("prostokąt", 3, 4));
    figury.push_back(std::make_unique<Kolo>("koło", 2));

    for (const auto& figura : figury) {
        std::cout << figura->nazwa() << ": "
                  << figura->pole() << '\n';
    }
}
```

Jak czytać ten przykład:

1. `Figura` przechowuje nazwę wspólną dla wszystkich figur. Jej pola są prywatne, więc klasy pochodne nie odczytują ich bezpośrednio. Mogą skorzystać z publicznej funkcji `nazwa()`.
2. `virtual double pole() const = 0;` deklaruje funkcję wirtualną czysto wirtualną. `= 0` oznacza, że sama klasa `Figura` nie podaje sposobu liczenia pola. Każda konkretna figura ma go dostarczyć.
3. `Prostokat` i `Kolo` implementują `pole()`. Słowo `override` prosi kompilator o sprawdzenie, czy sygnatura rzeczywiście odpowiada funkcji wirtualnej z bazy. Literówka lub brak `const` zostaną dzięki temu wykryte.
4. `std::unique_ptr<Figura>` może posiadać obiekt klasy pochodnej. Konwersja wskaźnika z `Prostokat*` do `Figura*` jest bezpieczna i niejawna, bo każdy prostokąt jest figurą.
5. Wyrażenie `figura->pole()` wywołuje implementację odpowiadającą rzeczywistemu obiektowi: dla prostokąta metodę `Prostokat::pole`, a dla koła `Kolo::pole`. Taki wybór w czasie działania programu to **polimorfizm dynamiczny**.

Bez funkcji wirtualnej wywołanie przez `Figura*` wybrałoby wersję zadeklarowaną w typie wskaźnika, a nie wersję klasy rzeczywistego obiektu. Słowo `virtual` w bazie włącza dynamiczny wybór. `override` samo nie włącza polimorfizmu — potwierdza tylko poprawne nadpisanie.

### Klasa abstrakcyjna

Klasa z co najmniej jedną funkcją czysto wirtualną jest abstrakcyjna. Nie można utworzyć jej bezpośrednio: oznacza to, że klasa bazowa wymaga od klasy konkretnej dostarczenia implementacji tej operacji. Można jednak tworzyć wskaźniki i referencje do klasy abstrakcyjnej. `Figura` jest abstrakcyjna przez `pole() = 0`, natomiast `Prostokat` i `Kolo` są konkretne, bo implementują tę funkcję.

Klasa abstrakcyjna może zawierać zwykłe pola, konstruktor, funkcje z implementacją oraz wiele funkcji wirtualnych. Nie musi być „pustym interfejsem”. Gdy klasa pochodna nie zaimplementuje wszystkich odziedziczonych funkcji czysto wirtualnych, sama też pozostanie abstrakcyjna.

### Konstrukcja i niszczenie obiektu

Przy tworzeniu obiektu pochodnego najpierw konstruowana jest jego część bazowa, następnie jego własne pola. Przy niszczeniu kolejność jest odwrotna: najpierw niszczona jest część pochodna, potem bazowa. Dlatego konstruktor `Prostokat` najpierw wywołuje `Figura(...)` na liście inicjalizacyjnej, a dopiero potem inicjalizuje szerokość i wysokość.

Konstruktory nie są zwykłymi metodami: nie są wirtualne i nie można ich nadpisywać. Destruktor może być wirtualny. W polimorficznej bazie, której obiekty usuwa się przez wskaźnik bazowy, powinien być wirtualny:

```cpp
class Figura {
public:
    virtual ~Figura() = default;
    virtual double pole() const = 0;
};
```

Gdy `std::unique_ptr<Figura>` niszczy posiadany obiekt, wirtualny destruktor pozwala uruchomić najpierw destruktor klasy rzeczywistej, a potem destruktor bazy. Usuwanie obiektu pochodnego przez wskaźnik do bazy bez wirtualnego destruktora prowadzi do niezdefiniowanego zachowania. Destruktor klasy pochodnej staje się wirtualny automatycznie; zapis `~Prostokat() override` jest dozwolony i może dokumentować intencję.

Jeśli nie planujesz usuwać obiektów przez wskaźnik bazowy, alternatywą bywa chroniony, niewirtualny destruktor. Dla początkującego praktyczna reguła jest prostsza: polimorficzna baza używana z `unique_ptr<Baza>` lub `delete Baza*` powinna mieć publiczny destruktor wirtualny.

### Rodzaje dziedziczenia i dostęp do składowych

Dziedziczenie opisuje nie tylko dostęp do elementów, ale też relację typów. Publiczne dziedziczenie mówi, że obiekt klasy pochodnej można traktować jak obiekt klasy bazowej. `protected` i `private` zmieniają widoczność odziedziczonych składowych; nie pozwalają bezpośrednio czytać prywatnych elementów bazy.

| Rodzaj dziedziczenia | Publiczna składowa bazy staje się | Chroniona składowa bazy staje się | Prywatna składowa bazy |
| --- | --- | --- | --- |
| `public` | publiczna | chroniona | niedostępna bezpośrednio |
| `protected` | chroniona | chroniona | niedostępna bezpośrednio |
| `private` | prywatna | prywatna | niedostępna bezpośrednio |

W deklaracji `class` domyślne dziedziczenie jest prywatne, a w `struct` publiczne. Prywatne pole bazy nadal istnieje w części bazowej obiektu, ale kod klasy pochodnej nie może odwołać się do niego po nazwie. Powinna to robić przez odpowiednią funkcję bazową.

Publiczne dziedziczenie jest dobrym wyborem, gdy można uczciwie powiedzieć „X jest rodzajem Y” i program ma korzystać z obiektu X przez interfejs Y. Jeśli klasa tylko używa innego obiektu jako jednego ze swoich składników, zwykle właściwsza jest kompozycja: pole jednego typu wewnątrz drugiego.

### Konwersja wskaźnika bazowego i pochodnego

Konwersja w górę hierarchii, z `Prostokat*` do `Figura*`, jest bezpieczna: wskaźnik wskazuje wtedy na część bazową tego samego obiektu. Konwersja w dół, z `Figura*` do `Prostokat*`, nie zawsze jest poprawna — wskaźnik może wskazywać na koło. Gdy rodzaj obiektu nie jest znany, użyj `dynamic_cast` i sprawdź wynik:

Korzystając z klas `Figura`, `Prostokat` i `Kolo` z poprzedniego przykładu, można napisać:

```cpp
std::unique_ptr<Figura> figura = std::make_unique<Kolo>("koło", 2);

if (auto* prostokat = dynamic_cast<Prostokat*>(figura.get())) {
    // rzutowanie się powiodło; figura wskazuje na Prostokat
} else {
    // w tym przykładzie obiekt jest kołem, więc rzutowanie się nie powiodło
}
```

W przykładzie `figura.get()` daje zwykły wskaźnik do części bazowej obiektu. Ponieważ obiekt jest kołem, `dynamic_cast` zwraca `nullptr`, a program wchodzi do gałęzi `else`. Dla wskaźnika wynik nieudanego rzutowania to `nullptr`; dla referencji `dynamic_cast` rzuca wyjątek `std::bad_cast`. Klasa bazowa musi być polimorficzna, czyli mieć co najmniej jedną funkcję wirtualną. Jeśli często musisz sprawdzać typ i rzutować w dół, zastanów się, czy wspólny interfejs nie powinien udostępniać potrzebnej operacji jako funkcji wirtualnej.

### Krojenie obiektu

Przypisanie obiektu pochodnego do zmiennej bazowej przez wartość kopiuje tylko część bazową. Dodatkowe pola i zachowanie klasy pochodnej zostają utracone. To zjawisko nazywa się **krojeniem obiektu** (*object slicing*):

```cpp
#include <iostream>

class Bazowa {
public:
    virtual ~Bazowa() = default;
    virtual void opisz() const { std::cout << "Bazowa\n"; }
};

class Pochodna : public Bazowa {
public:
    void opisz() const override { std::cout << "Pochodna\n"; }
};

Pochodna oryginal;
Bazowa kopia = oryginal; // kopia jest osobnym obiektem typu Bazowa
kopia.opisz();           // wywoła Bazowa::opisz
```

Gdy chcesz zachować rzeczywisty typ obiektu i polimorfizm, przekazuj obiekty przez referencję lub wskaźnik, a przy dynamicznym zarządzaniu czasem życia użyj inteligentnego wskaźnika do bazy, jak w pierwszym przykładzie.
