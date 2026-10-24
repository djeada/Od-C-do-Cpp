# Programowanie obiektowe, przeciążanie i konwersje — quiz

Notatki: [Programowanie obiektowe](../notatki/15_programowanie_obietkowe.md), [Dziedziczenie](../notatki/16_dziedziczenie.md), [Przeciążanie](../notatki/18_przeciazanie.md), [Konwersje](../notatki/19_konwersje.md)

Sprawdź, czy rozumiesz klasy i enkapsulację, czas życia obiektów, polimorfizm, przeciążanie funkcji i operatorów oraz konwersje typów.

#### Q. Czym w C++ różni się `struct` od `class`?

* [ ] `struct` nie może mieć metod ani konstruktorów
* [x] Domyślnym dostępem i dziedziczeniem: publicznym albo prywatnym
* [ ] W `class` nie wolno deklarować pól publicznych
* [ ] Obiekty `struct` zawsze leżą na stosie, a obiekty `class` na stercie

> **Wyjaśnienie:** W C++ oba słowa tworzą klasę z tymi samymi możliwościami. W `struct` składowe i dziedziczenie są domyślnie publiczne, a w `class` prywatne; w C `struct` nie ma metod ani modyfikatorów dostępu.

#### Q. Co wypisze ten program w C++ z kilkoma obiektami tej samej klasy?

```cpp
#include <iostream>

class Licznik {
public:
    void zwieksz() { ++wartosc_; }
    int odczytaj() const { return wartosc_; }

private:
    int wartosc_ = 0;
};

int main() {
    Licznik a;
    Licznik b;
    a.zwieksz();
    a.zwieksz();
    b.zwieksz();
    Licznik c = a;
    c.zwieksz();
    std::cout << a.odczytaj() << ' ' << b.odczytaj() << ' ' << c.odczytaj() << '\n';
}
```

* [ ] `3 1 3`
* [x] `2 1 3`
* [ ] `2 1 2`
* [ ] `4 4 4`

> **Wyjaśnienie:** Każdy obiekt ma własne pole `wartosc_`. `c` jest kopią `a` z chwili kopiowania (2), a jej późniejsza zmiana nie wpływa na oryginał.

#### Q. Który oznaczony wiersz tego programu w C++ z prywatnym polem spowoduje błąd kompilacji?

```cpp
class Licznik {
public:
    void zwieksz() { ++wartosc_; }
    int odczytaj() const { return wartosc_; }

private:
    int wartosc_ = 0;
};

int main() {
    Licznik k;
    k.zwieksz();              // (1)
    Licznik kopia = k;        // (2)
    k.wartosc_ = 5;           // (3)
    return kopia.odczytaj();  // (4)
}
```

* [ ] `(1)`
* [ ] `(2)`
* [x] `(3)`
* [ ] `(4)`

> **Wyjaśnienie:** `wartosc_` jest prywatne, więc kod spoza klasy nie może go bezpośrednio zmienić. Publiczne metody i kopiowanie obiektu są dozwolone — tak klasa pilnuje swojego stanu.

#### Q. Klasa `Wiadomosc` ma tylko konstruktor `explicit Wiadomosc(const std::string& tresc)`. Co stanie się z deklaracją `Wiadomosc w;`?

* [ ] Utworzy wiadomość z pustą treścią
* [x] Nie skompiluje się: brak konstruktora bezargumentowego
* [ ] Utworzy obiekt z nieokreśloną treścią
* [ ] Skompiluje się, ale zgłosi wyjątek dopiero podczas działania

> **Wyjaśnienie:** Gdy klasa deklaruje własny konstruktor, kompilator nie tworzy domyślnego konstruktora bezargumentowego. Trzeba podać tekst albo świadomie dodać taki konstruktor, jeśli pusty obiekt ma sens.

#### Q. Co wypisze ten program w C++ z konstruktorem i destruktorem obiektów lokalnych?

```cpp
#include <iostream>

struct S {
    char n;
    explicit S(char c) : n(c) { std::cout << '+' << n; }
    ~S() { std::cout << '-' << n; }
};

int main() {
    S a('a');
    {
        S b('b');
    }
    S c('c');
}
```

* [x] `+a+b-b+c-c-a`
* [ ] `+a+b+c-a-b-c`
* [ ] `+a+b-b+c-a-c`
* [ ] `+a+b+c-c-b-a`

> **Wyjaśnienie:** `b` jest niszczony na końcu swojego bloku, jeszcze przed utworzeniem `c`. Na końcu `main` obiekty są niszczone w kolejności odwrotnej do tworzenia: najpierw `c`, potem `a`.

#### Q. Co wypisze ten program w C++ z polem `static`?

```cpp
#include <iostream>

class K {
public:
    static int ile;
    K() { ++ile; }
};

int K::ile = 0;

int main() {
    K a;
    K b;
    {
        K c;
    }
    std::cout << K::ile << '\n';
}
```

* [ ] `1`
* [ ] `2`
* [x] `3`
* [ ] `0`

> **Wyjaśnienie:** Pole `static` należy do klasy i jest wspólne dla wszystkich obiektów. Każdy z trzech konstruktorów zwiększył ten sam licznik; zniszczenie `c` go nie zmniejsza.

#### Q. Co jest prawdą o statycznej metodzie klasy w C++?

* [ ] Musi być wywoływana na konkretnym obiekcie
* [x] Nie ma `this`; bezpośrednio używa tylko pól statycznych
* [ ] Odczytuje pola obiektu przez niejawny wskaźnik `this`
* [ ] W jednej klasie może istnieć najwyżej jedna metoda statyczna

> **Wyjaśnienie:** Statyczna metoda należy do klasy, a nie do obiektu, więc wywołuje się ją np. jako `Ustawienia::pobierz_limit()`. Bez `this` nie ma bezpośredniego dostępu do zwykłych pól.

#### Q. Co jest prawdą o funkcji zadeklarowanej w klasie jako `friend`?

* [ ] Staje się publiczną metodą tej klasy
* [x] To zwykła funkcja z dostępem do prywatnych składników
* [ ] Można ją wywołać wyłącznie z metod tej klasy
* [ ] Jest automatycznie dziedziczona przez wszystkie klasy pochodne

> **Wyjaśnienie:** `friend` daje zwykłej funkcji dostęp do prywatnych składników, ale nie czyni jej składnikiem klasy. Typowy przykład to `operator<<`, który wypisuje prywatne pola obiektu.

#### Q. Co wypisze ten program w C++ z klasą pilnującą niezmiennika salda?

```cpp
#include <iostream>

class Konto {
public:
    bool wyplac(int kwota) {
        if (kwota <= 0 || kwota > saldo_) {
            return false;
        }
        saldo_ -= kwota;
        return true;
    }

    int saldo() const { return saldo_; }

private:
    int saldo_ = 10000;
};

int main() {
    Konto k;
    bool a = k.wyplac(3000);
    bool b = k.wyplac(8000);
    std::cout << a << ' ' << b << ' ' << k.saldo() << '\n';
}
```

* [ ] `1 1 -1000`
* [x] `1 0 7000`
* [ ] `1 0 10000`
* [ ] `0 0 10000`

> **Wyjaśnienie:** Pierwsza wypłata się udaje i saldo spada do 7000. Druga jest większa niż saldo, więc metoda odmawia i nie zmienia stanu — niezmiennik „saldo nie jest ujemne” zostaje zachowany.

#### Q. Co wypisze ten program w C++ z `std::variant`?

```cpp
#include <iostream>
#include <variant>

int main() {
    std::variant<int, float> v = 10;
    try {
        float f = std::get<float>(v);
        std::cout << f << '\n';
    } catch (const std::bad_variant_access&) {
        std::cout << "zły typ\n";
    }
}
```

* [ ] `10`
* [x] `zły typ`
* [ ] `0`
* [ ] Przypadkową wartość z pamięci

> **Wyjaśnienie:** `std::variant` pamięta, która alternatywa jest aktywna — tutaj `int`. `std::get<float>` dla nieaktywnego typu zgłasza `std::bad_variant_access`, zamiast odczytać bajty jak zwykła unia.

#### Q. Jaki zakres wartości może przechować pole bitowe `unsigned int dzien : 5;`?

* [x] Od 0 do 31
* [ ] Od 0 do 5
* [ ] Od 0 do 32
* [ ] Od 1 do 31

> **Wyjaśnienie:** Pięć bitów bez znaku daje $2^5 = 32$ wartości, czyli od 0 do 31. Pole nie sprawdza jednak reguł modelu, np. czy dana data w ogóle istnieje.

#### Q. Dlaczego funkcja `void f(const Wiadomosc& w) { w.oznacz_przeczytana(); }` się nie skompiluje, jeśli metoda `oznacz_przeczytana` nie jest oznaczona `const`?

* [ ] Bo referencji nie można przekazywać do funkcji
* [x] Bo przez referencję do stałej wolno wołać tylko metody `const`
* [ ] Bo metody można wywoływać wyłącznie przez wskaźnik
* [ ] Bo `const` przy parametrze kopiuje cały obiekt

> **Wyjaśnienie:** `const Wiadomosc&` obiecuje, że funkcja nie zmieni obiektu. Metoda bez `const` po liście parametrów może zmieniać stan, więc kompilator nie pozwala jej wywołać.

#### Q. Co wypisze ten program w C++ z metodą wirtualną i niewirtualną?

```cpp
#include <iostream>

struct B {
    virtual ~B() = default;
    void a() const { std::cout << "B.a "; }
    virtual void b() const { std::cout << "B.b "; }
};

struct D : B {
    void a() const { std::cout << "D.a "; }
    void b() const override { std::cout << "D.b "; }
};

int main() {
    D d;
    const B& r = d;
    r.a();
    r.b();
    std::cout << '\n';
}
```

* [ ] `D.a D.b`
* [x] `B.a D.b`
* [ ] `B.a B.b`
* [ ] `D.a B.b`

> **Wyjaśnienie:** Przez referencję do bazy metoda niewirtualna jest wybierana według typu referencji (`B::a`). Metoda wirtualna jest wybierana według rzeczywistego obiektu, więc wywołuje się `D::b`.

#### Q. Co wypisze ten program w C++, który przypisuje obiekt pochodny do zmiennej bazowej?

```cpp
#include <iostream>

struct Bazowa {
    virtual ~Bazowa() = default;
    virtual void opisz() const { std::cout << "Bazowa\n"; }
};

struct Pochodna : Bazowa {
    void opisz() const override { std::cout << "Pochodna\n"; }
};

int main() {
    Pochodna oryginal;
    Bazowa kopia = oryginal;
    const Bazowa& ref = oryginal;
    kopia.opisz();
    ref.opisz();
}
```

* [ ] `Pochodna`, a potem `Pochodna`
* [x] `Bazowa`, a potem `Pochodna`
* [ ] `Bazowa`, a potem `Bazowa`
* [ ] `Pochodna`, a potem `Bazowa`

> **Wyjaśnienie:** `kopia` to nowy obiekt typu `Bazowa` — przy kopiowaniu przez wartość zachowała się tylko część bazowa (krojenie obiektu). Referencja `ref` nadal odnosi się do obiektu `Pochodna`.

#### Q. Co jest prawdą o klasie `Figura` z metodą `virtual double pole() const = 0;`?

* [ ] Nie może mieć pól ani konstruktora
* [x] Nie można utworzyć jej obiektu, ale wolno używać `Figura&`
* [ ] Każda jej klasa pochodna też jest zawsze abstrakcyjna
* [ ] Jej metoda `pole` jest zawsze wywoływana w wersji bazowej

> **Wyjaśnienie:** Funkcja czysto wirtualna czyni klasę abstrakcyjną: tworzy się tylko obiekty klas pochodnych, które ją implementują. Klasa abstrakcyjna może mieć pola, konstruktor i zwykłe metody.

#### Q. Co wypisze ten program w C++ z konstruktorami i destruktorami w hierarchii?

```cpp
#include <iostream>

struct B {
    B() { std::cout << "B "; }
    ~B() { std::cout << "~B "; }
};

struct D : B {
    D() { std::cout << "D "; }
    ~D() { std::cout << "~D "; }
};

int main() {
    D d;
}
```

* [ ] `D B ~D ~B`
* [x] `B D ~D ~B`
* [ ] `B D ~B ~D`
* [ ] `D B ~B ~D`

> **Wyjaśnienie:** Najpierw konstruowana jest część bazowa, potem pochodna. Przy niszczeniu kolejność jest odwrotna: najpierw destruktor `D`, potem `B`.

#### Q. Klasa `Baza` ma publiczny, niewirtualny destruktor. Co można powiedzieć o kodzie `Baza* p = new Pochodna; delete p;`?

* [ ] Wywołają się oba destruktory, jak zwykle
* [ ] Kompilator odrzuci taki kod
* [x] Ma niezdefiniowane zachowanie
* [ ] Wywoła się tylko destruktor `Pochodna`

> **Wyjaśnienie:** Usuwanie obiektu pochodnego przez wskaźnik do bazy bez wirtualnego destruktora jest niezdefiniowane. Polimorficzna baza używana z `delete Baza*` lub `unique_ptr<Baza>` powinna mieć `virtual ~Baza()`.

#### Q. Co wypisze ten program w C++ z nieudanym `dynamic_cast`?

```cpp
#include <iostream>
#include <typeinfo>

struct Figura { virtual ~Figura() = default; };
struct Kolo : Figura {};
struct Prostokat : Figura {};

int main() {
    Kolo k;
    Figura& f = k;
    if (dynamic_cast<Prostokat*>(&f) == nullptr) {
        std::cout << "nullptr ";
    }
    try {
        Prostokat& p = dynamic_cast<Prostokat&>(f);
        (void)p;
        std::cout << "ok\n";
    } catch (const std::bad_cast&) {
        std::cout << "bad_cast\n";
    }
}
```

* [x] `nullptr bad_cast`
* [ ] `nullptr ok`
* [ ] `bad_cast`
* [ ] `ok`

> **Wyjaśnienie:** Obiekt jest kołem, więc rzutowanie na `Prostokat` się nie udaje. Dla wskaźnika `dynamic_cast` zwraca wtedy `nullptr`, a dla referencji, która nie może być pusta, zgłasza `std::bad_cast`.

#### Q. Czym staje się publiczna składowa klasy `Baza` w klasie `class Pochodna : protected Baza`?

* [ ] Publiczną składową `Pochodna`
* [x] Chronioną składową `Pochodna`
* [ ] Prywatną składową `Pochodna`
* [ ] Składową niedostępną w `Pochodna`

> **Wyjaśnienie:** Dziedziczenie chronione obniża publiczne i chronione składowe bazy do poziomu `protected`. Prywatne składowe bazy w każdym rodzaju dziedziczenia pozostają niedostępne bezpośrednio.

#### Q. W bazie jest `virtual double pole() const`, a w klasie pochodnej napisano `double pole() override` (bez `const`). Co się stanie?

* [ ] Metoda nadpisze wersję z bazy mimo braku `const`
* [x] Kompilator zgłosi błąd, bo metoda niczego nie nadpisuje
* [ ] Powstanie nowa metoda, a `override` zostanie zignorowane
* [ ] Program się skompiluje, ale wywoła wersję bazową

> **Wyjaśnienie:** Brak `const` zmienia sygnaturę, więc metoda nie nadpisuje funkcji wirtualnej z bazy. `override` prosi kompilator o sprawdzenie nadpisania i zamienia tę cichą pomyłkę w błąd kompilacji.

#### Q. Co się stanie przy kompilacji tego programu w C++ z dziedziczeniem bez słowa `public`?

```cpp
class Baza {
public:
    virtual ~Baza() = default;
};

class Pochodna : Baza {};

int main() {
    Pochodna d;
    Baza* p = &d;
    return p != nullptr;
}
```

* [x] Błąd: `Baza` jest prywatną klasą bazową
* [ ] Program się skompiluje i zwróci 1
* [ ] Błąd: `Pochodna` nie ma konstruktora
* [ ] Program się skompiluje, ale `p` będzie `nullptr`

> **Wyjaśnienie:** W deklaracji `class` domyślne dziedziczenie jest prywatne, więc kod spoza klasy nie może zamienić `Pochodna*` na `Baza*`. Zapis `class Pochodna : public Baza` (albo `struct`) usuwa ten problem.

#### Q. Co wypisze ten program w C++ z przeciążeniami dla `int` i `double`?

```cpp
#include <iostream>

void pokaz(int) { std::cout << "int "; }
void pokaz(double) { std::cout << "double "; }

int main() {
    pokaz('A');
    pokaz(3.0f);
    std::cout << '\n';
}
```

* [x] `int double`
* [ ] `double double`
* [ ] `int int`
* [ ] Błąd: oba wywołania są niejednoznaczne

> **Wyjaśnienie:** `char` jest promowany do `int`, a `float` do `double`. Promocja jest lepszą konwersją niż zamiana na inny typ, więc każde wywołanie ma jednoznacznie najlepsze przeciążenie.

#### Q. Co się stanie przy kompilacji tego programu w C++ z przeciążeniami dla `long` i `double`?

```cpp
void wybierz(long) {}
void wybierz(double) {}

int main() {
    wybierz(10);
}
```

* [ ] Zostanie wybrana wersja dla `long`
* [ ] Zostanie wybrana wersja dla `double`
* [x] Błąd: wywołanie jest niejednoznaczne
* [ ] Błąd: brak wersji przyjmującej `int`

> **Wyjaśnienie:** Z `int` do `long` i do `double` prowadzą konwersje tej samej rangi, więc żadna nie jest lepsza. Trzeba poprawić typ argumentu, np. `wybierz(10L)`, albo uprościć zestaw przeciążeń.

#### Q. Co się stanie, gdy w jednym pliku zdefiniujesz `void f(int x) {}` oraz `void f(const int x) {}`?

* [ ] Powstaną dwa poprawne przeciążenia
* [x] Błąd: to ta sama funkcja zdefiniowana dwa razy
* [ ] Wywołanie `f(1)` wybierze wersję z `const`
* [ ] Druga definicja zastąpi pierwszą bez błędu

> **Wyjaśnienie:** `const` przy parametrze przekazywanym przez wartość nie zmienia sygnatury funkcji, więc to dwie definicje tej samej funkcji. Inaczej jest z `const` po liście parametrów metody lub przy referencji.

#### Q. Którego z tych operatorów nie można przeciążyć w C++?

* [ ] `+`
* [ ] `<<`
* [ ] `[]`
* [x] `?:`

> **Wyjaśnienie:** Nie można przeciążać m.in. `::`, `.`, `.*`, `?:` i `sizeof`. Operatory `+`, `<<` i `[]` często przeciąża się dla własnych typów.

#### Q. Co wypisze ten program w C++ z przedrostkowym i przyrostkowym `operator++`?

```cpp
#include <iostream>

class Licznik {
    int wartosc_ = 0;

public:
    Licznik& operator++() {
        ++wartosc_;
        return *this;
    }

    Licznik operator++(int) {
        Licznik poprzedni = *this;
        ++wartosc_;
        return poprzedni;
    }

    int wartosc() const { return wartosc_; }
};

int main() {
    Licznik l;
    Licznik a = l++;
    Licznik& b = ++l;
    std::cout << a.wartosc() << ' ' << b.wartosc() << ' ' << l.wartosc() << '\n';
}
```

* [ ] `1 2 2`
* [x] `0 2 2`
* [ ] `0 1 2`
* [ ] `1 1 2`

> **Wyjaśnienie:** Wersja przyrostkowa (z nieużywanym parametrem `int`) zwraca kopię sprzed zmiany, więc `a` ma 0. Wersja przedrostkowa zwraca referencję do samego `l` po zwiększeniu, więc `b` i `l` pokazują 2.

#### Q. Dlaczego `operator<<` do wypisywania obiektu własnej klasy definiuje się jako funkcję spoza klasy?

* [ ] Bo metody klasy nie mogą zwracać referencji do strumienia
* [x] Bo lewym operandem jest strumień `std::ostream`
* [ ] Bo funkcja zaprzyjaźniona działa szybciej
* [ ] Bo operator `<<` działa tylko dla `int`

> **Wyjaśnienie:** W `std::cout << obiekt` lewym operandem jest strumień, a do klasy `std::ostream` nie dodamy własnej metody. Funkcja zwraca `std::ostream&`, co pozwala łączyć kolejne wypisania.

#### Q. Jak kompilator interpretuje wyrażenie `a + b`, gdy `operator+` jest metodą klasy `Kompleks`?

* [x] Jako `a.operator+(b)`
* [ ] Jako `b.operator+(a)`
* [ ] Jako `operator+(b, a)`
* [ ] Jako `a.operator=(a + b)`

> **Wyjaśnienie:** Dla operatora będącego metodą lewy operand jest obiektem, na którym wywołuje się metodę, a prawy trafia do parametru. Dlatego metoda nie zmieniająca `a` powinna być oznaczona `const`.

#### Q. Co wypisze ten program w C z rzutowaniem liczb zmiennoprzecinkowych na `int`?

```c
#include <stdio.h>

int main(void) {
    printf("%d %d\n", (int)3.75, (int)-3.75);
    return 0;
}
```

* [ ] `4 -4`
* [x] `3 -3`
* [ ] `3 -4`
* [ ] `4 -3`

> **Wyjaśnienie:** Konwersja zmiennoprzecinkowej wartości na typ całkowity odrzuca część ułamkową, czyli obcina w kierunku zera. Nie zaokrągla ani do najbliższej liczby, ani w dół, dlatego `-3.75` daje `-3`.

#### Q. Co wypisze ten program w C, w którym rzutowanie stoi w różnych miejscach wyrażenia?

```c
#include <stdio.h>

int main(void) {
    int a = 7;
    int b = 2;
    double w1 = (double)(a / b);
    double w2 = (double)a / b;
    printf("%.1f %.1f\n", w1, w2);
    return 0;
}
```

* [ ] `3.5 3.5`
* [x] `3.0 3.5`
* [ ] `3.0 3.0`
* [ ] `3.5 3.0`

> **Wyjaśnienie:** W `w1` najpierw wykonuje się dzielenie całkowite (3), a dopiero wynik zamienia się na `double`. W `w2` rzutowanie dotyczy `a` przed dzieleniem, więc całe działanie jest zmiennoprzecinkowe.

#### Q. Co wypisze ten program w C porównujący `int` z `unsigned int`?

```c
#include <stdio.h>

int main(void) {
    int s = -1;
    unsigned int u = 1;
    printf("%d\n", s < u);
    return 0;
}
```

* [ ] `1`
* [x] `0`
* [ ] `-1`
* [ ] Wynik jest niezdefiniowany

> **Wyjaśnienie:** Przy tej samej randze `s` zostaje przekonwertowane do `unsigned int`, a `-1` staje się `UINT_MAX`. Porównanie `UINT_MAX < 1` jest fałszywe; konwersja jest dobrze zdefiniowana, choć zaskakująca.

#### Q. Co wypisze ten program w C z dodawaniem wartości `unsigned char`?

```c
#include <stdio.h>

int main(void) {
    unsigned char x = 250;
    unsigned char y = 10;
    int suma = x + y;
    unsigned char z = x + y;
    printf("%d %d\n", suma, z);
    return 0;
}
```

* [ ] `4 4`
* [x] `260 4`
* [ ] `260 260`
* [ ] `4 260`

> **Wyjaśnienie:** Przed dodawaniem oba argumenty są promowane do `int`, więc suma wynosi 260. Zapis do `unsigned char` (8 bitów na typowych platformach) zachowuje wartość modulo 256, czyli $260 \bmod 256 = 4$.

#### Q. Wskaźnik `Baza* b` wskazuje obiekt typu `Baza`, a nie `Pochodna`. Co można powiedzieć o wyniku `static_cast<Pochodna*>(b)`?

* [ ] Jest równy `nullptr`, jak przy `dynamic_cast`
* [ ] Rzutowanie zgłasza wyjątek `std::bad_cast`
* [x] Kompiluje się, ale jego użycie jest niezdefiniowane
* [ ] Kompilator zawsze odrzuci takie rzutowanie

> **Wyjaśnienie:** `static_cast` nie sprawdza w czasie działania, jaki obiekt leży pod adresem. Zakłada, że programista wie, iż to `Pochodna`; gdy typ jest niepewny, używa się `dynamic_cast` i sprawdza wynik.

#### Q. Kiedy zapis przez wskaźnik uzyskany z `const_cast<int*>(p)` jest poprawny?

* [ ] Zawsze, bo `const_cast` trwale usuwa stałość obiektu
* [ ] Nigdy, bo `const_cast` usunięto w C++20
* [x] Gdy wskazywany obiekt nie był pierwotnie `const`
* [ ] Tylko gdy obiekt jest zmienną globalną

> **Wyjaśnienie:** `const_cast` zmienia tylko typ wskaźnika, a nie sam obiekt. Zapis do obiektu zadeklarowanego jako `const` pozostaje niezdefiniowanym zachowaniem, nawet po usunięciu `const` z typu.

#### Q. Który oznaczony wiersz tego programu w C++ z konstruktorem `explicit` spowoduje błąd kompilacji?

```cpp
class Ulamek {
public:
    explicit Ulamek(int liczba) : licznik_(liczba) {}

private:
    int licznik_;
};

int main() {
    Ulamek a{5};           // (1)
    Ulamek b(5);           // (2)
    Ulamek c = Ulamek(5);  // (3)
    Ulamek d = 5;          // (4)
}
```

* [ ] `(1)`
* [ ] `(2)`
* [ ] `(3)`
* [x] `(4)`

> **Wyjaśnienie:** `explicit` blokuje niejawną konwersję z `int` na `Ulamek`, a zapis `Ulamek d = 5;` właśnie jej wymaga. Pozostałe wiersze jawnie wywołują konstruktor.

#### Q. Co wypisze ten program w C++ z jawnym operatorem konwersji?

```cpp
#include <cmath>
#include <iostream>

class Zespolona {
public:
    Zespolona(double re, double im) : re_(re), im_(im) {}
    explicit operator double() const { return std::hypot(re_, im_); }

private:
    double re_;
    double im_;
};

int main() {
    Zespolona z{3.0, 4.0};
    double modul = static_cast<double>(z);
    std::cout << modul << '\n';
}
```

* [x] `5`
* [ ] `3`
* [ ] `7`
* [ ] Błąd: operator jest oznaczony `explicit`

> **Wyjaśnienie:** `explicit operator double()` blokuje tylko niejawne użycie, np. `double m = z;`. Jawne `static_cast<double>(z)` jest dozwolone i zwraca moduł `hypot(3, 4) = 5`.

#### Q. Jak w C++20 poprawnie odczytać reprezentację bitową `float f` jako `std::uint32_t` (typy tego samego rozmiaru)?

* [ ] `*reinterpret_cast<std::uint32_t*>(&f)`
* [ ] `static_cast<std::uint32_t>(f)`
* [x] `std::bit_cast<std::uint32_t>(f)`
* [ ] `const_cast<std::uint32_t&>(f)`

> **Wyjaśnienie:** `std::bit_cast` z `<bit>` kopiuje reprezentację obiektu do typu o tym samym rozmiarze. Odczyt przez `reinterpret_cast` narusza reguły aliasowania, a `static_cast` zamienia wartość liczbową, a nie bity.
