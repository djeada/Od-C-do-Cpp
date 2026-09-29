# Przeciążanie funkcji i operatorów

> Przykłady w tej notatce wymagają C++11.

Przeciążanie pozwala użyć tej samej nazwy dla kilku powiązanych operacji. Kompilator wybiera funkcję na podstawie argumentów wywołania. To wybór **podczas kompilacji** (polimorfizm statyczny), odmienny od polimorfizmu dynamicznego z funkcjami wirtualnymi: w tamtym przypadku wybrana implementacja zależy od rzeczywistego typu obiektu w czasie działania programu. Przeciążanie opisuje wybór między deklaracjami widocznymi w miejscu wywołania.

## Przeciążanie funkcji

Rozważmy funkcję `pokaz`, która może wyświetlić liczbę całkowitą albo zmiennoprzecinkową:

```cpp
#include <iostream>

void pokaz(int wartosc) {
    std::cout << "liczba całkowita: " << wartosc << '\n';
}

void pokaz(double wartosc) {
    std::cout << "liczba zmiennoprzecinkowa: " << wartosc << '\n';
}

void pokaz(int kod, double wynik) {
    std::cout << "kod " << kod << ", wynik " << wynik << '\n';
}

int main() {
    int x = 5;
    double y = 3.14;

    pokaz(x);       // wybiera pokaz(int): typ argumentu pasuje dokładnie
    pokaz(y);       // wybiera pokaz(double): typ argumentu pasuje dokładnie
    pokaz(x, y);    // wybiera wersję z dwoma parametrami
}
```

Ten sam identyfikator nie oznacza jednej uniwersalnej funkcji. Są to trzy osobne funkcje o różnych sygnaturach. W uproszczeniu kompilator postępuje tak:

1. Zbiera dostępne funkcje o nazwie `pokaz`.
2. Odrzuca te, których nie da się wywołać z podaną liczbą argumentów albo których parametry nie mogą przyjąć tych argumentów.
3. Spośród pozostałych wybiera przeciążenie wymagające najlepszych konwersji argumentów.
4. Jeśli dwie możliwości są równie dobre, wywołanie jest niejednoznaczne i kompilacja kończy się błędem.

### Co tworzy nowe przeciążenie?

Funkcje mogą różnić się liczbą, typami lub kolejnością typów parametrów. Sam inny typ zwracany nie wystarczy, ponieważ przy wywołaniu `f(x)` kompilator nie musi znać kontekstu, do którego przypisany będzie wynik:

```cpp
int    oblicz(int x);
double oblicz(int x); // błąd: różni się tylko typem zwracanym
```

Kwalifikator `const` przy parametrze przekazywanym przez wartość także nie tworzy nowego przeciążenia: `void f(int)` i `void f(const int)` są tą samą funkcją. W metodach klasy kwalifikator `const` po liście parametrów ma inne znaczenie — opisuje, czy metoda może zmienić obiekt — i może odróżniać przeciążenia metod dla obiektów stałych i niestałych.

### Konwersje i niejednoznaczne wywołanie

Gdy nie ma dokładnie pasującego parametru, C++ może wykonać dozwoloną konwersję. Czasem kilka konwersji jest równie dobrych:

```cpp
void wybierz(long wartosc);
void wybierz(double wartosc);

// wybierz(10); // błąd: z int można przejść do long albo double,
                // a żadna z tych konwersji nie jest lepsza
```

Nie należy rozwiązywać niejasnego API przez dopisywanie coraz większej liczby przeciążeń. Często czytelniej jest poprawić typ argumentu lub nadać operacjom różne nazwy. Gdy intencja jest jednoznaczna, można też jawnie skonwertować argument: `wybierz(static_cast<long>(10));`.

Domyślne argumenty również mogą spowodować niejednoznaczność:

```cpp
void f(int wartosc);
void f(int wartosc, double mnoznik = 1.0);

// f(10);       // błąd: obie funkcje mogą przyjąć jeden argument
f(10, 2.0);     // wybiera drugą funkcję, bo przekazano dwa argumenty
```

Liczba argumentów nie rozstrzyga wywołania `f(10)`, ponieważ druga funkcja może uzupełnić brakujący argument wartością domyślną. Usuń jedno z pokrywających się przeciążeń albo zmień nazwę lub liczbę wymaganych parametrów. Komentarze przy błędnych liniach są objaśnieniem — odkomentowanie ich celowo powoduje błąd kompilacji.

Przeciążona nazwa funkcji może nie wskazywać jednej konkretnej funkcji, więc czasem nie można jej przypisać bezpośrednio do wskaźnika. Typ wskaźnika może wtedy wybrać żądaną wersję:

```cpp
void ustaw(int);
void ustaw(double);

using FunkcjaNaInt = void (*)(int);
FunkcjaNaInt operacja = static_cast<FunkcjaNaInt>(ustaw);
```

To ten sam rodzaj wskaźnika na funkcję, który opisuje [notatka o wskaźnikach](17_zaawansowane_wskazniki.md).

## Przeciążanie operatorów

Operatorów można użyć do zapisu naturalnych operacji na typach zdefiniowanych przez programistę. Dla liczb zespolonych dodawanie `a + b` ma oczywiste znaczenie: dodajemy osobno części rzeczywiste i urojone. Przeciążenie jest przydatne właśnie wtedy, gdy zapis operatorowy wyjaśnia intencję lepiej niż osobna nazwa funkcji.

```cpp
#include <iostream>

class Kompleks {
    double re_;
    double im_;

public:
    Kompleks(double re, double im) : re_(re), im_(im) {}

    Kompleks operator+(const Kompleks& inny) const {
        return Kompleks(re_ + inny.re_, im_ + inny.im_);
    }

    friend std::ostream& operator<<(std::ostream& wyjscie,
                                    const Kompleks& liczba) {
        wyjscie << '(' << liczba.re_ << ", " << liczba.im_ << "i)";
        return wyjscie;
    }
};

int main() {
    Kompleks a(1, 2);
    Kompleks b(3, 4);
    Kompleks suma = a + b;

    std::cout << suma << '\n'; // (4, 6i)
}
```

Jak działa ten przykład:

- `a + b` jest równoważne wywołaniu `a.operator+(b)`. Metoda nie zmienia `a`, dlatego jest oznaczona jako `const`. Parametr jest referencją do stałego obiektu, więc unikamy niepotrzebnego kopiowania argumentu.
- Wynik dodawania jest nowym obiektem `Kompleks`. Operator `+` zachowuje typowe znaczenie dodawania i nie zmienia niespodziewanie operandów.
- Operator `<<` ma strumień jako lewy operand: w `std::cout << suma` lewą stroną jest `std::ostream`, której nie możemy zmienić ani dodać do niej naszej metody. Dlatego `operator<<` jest wolną funkcją; `friend` pozwala jej odczytać prywatne części liczby.
- `operator<<` zwraca strumień przez referencję, co umożliwia łączenie operacji, na przykład `std::cout << suma << '\n';`.

### Reguły i ograniczenia operatorów

- Co najmniej jeden operand musi mieć typ zdefiniowany przez użytkownika (klasę lub typ wyliczeniowy). Nie można zmienić znaczenia `int + int`.
- Można przeciążać istniejące operatory, lecz nie tworzyć nowych symboli.
- Nie zmienia się liczby operandów, priorytetu ani łączności operatora. `a + b * c` nadal grupuje się według zwykłego priorytetu mnożenia.
- Nie można przeciążyć m.in. operatora zakresu `::`, dostępu do składowej `.`, dostępu do składowej przez wskaźnik `.*`, operatora warunkowego `?:` ani `sizeof`.

Operator warto przeciążać, gdy operacja ma dla typu naturalne, oczekiwane znaczenie. Nie przeciążaj na przykład `+` po to, by wysyłać wiadomość, zmieniać stan globalny albo usuwać plik — czytelnik ma prawo oczekiwać, że dodawanie nie wykona takich działań. Jeśli zamierzona operacja nie pasuje do zwykłego znaczenia operatora, użyj nazwanej funkcji.

### Inkrementacja przedrostkowa i przyrostkowa

`++x` i `x++` różnią się wynikiem, nie tylko zapisem: wersja przedrostkowa zwiększa obiekt, po czym zwraca go po zmianie; wersja przyrostkowa zwraca kopię sprzed zmiany. Dlatego wersja przyrostkowa ma dodatkowy, nieużywany parametr `int` — to znacznik składni wymagany przez język.

```cpp
class Licznik {
    int wartosc_ = 0;

public:
    explicit Licznik(int wartosc = 0) : wartosc_(wartosc) {}

    Licznik& operator++() { // ++licznik
        ++wartosc_;
        return *this;       // zwraca ten sam obiekt po zmianie
    }

    Licznik operator++(int) { // licznik++
        Licznik poprzedni = *this;
        ++wartosc_;
        return poprzedni;   // zwraca kopię sprzed zmiany
    }

    int wartosc() const { return wartosc_; }
};
```

Operator przedrostkowy zwraca referencję, bo nie tworzy kopii — wynikiem jest zmieniony licznik. Operator przyrostkowy musi zapamiętać i zwrócić poprzednią wartość, więc zwraca kopię. Jeśli wynik `x++` nie jest potrzebny, `++x` jest prostszym wyborem, zwłaszcza dla typów iteratorów, które mogą być kosztowne do kopiowania.

## Najczęstsze pomyłki

- **Odróżnianie funkcji tylko typem wyniku** — nie tworzy przeciążenia; trzeba zmienić parametry albo nazwę.
- **Zakładanie, że kompilator zawsze wybierze „najbardziej pasującą” funkcję** — przy równorzędnych konwersjach zgłasza niejednoznaczność. Jawnie popraw typ argumentu albo uprość zestaw przeciążeń.
- **Przeciążanie operatora dla efektu zaskakującego użytkownika** — składnia zaciemnia wtedy działanie. Operator powinien zachować intuicyjne znaczenie.
- **Zwracanie nowego obiektu z `operator<<` zamiast referencji do strumienia** — utrudnia albo uniemożliwia łączenie wypisywania.
- **Traktowanie `++x` i `x++` jako równoważnych** — pierwszy zwraca wartość po zmianie, drugi kopię sprzed zmiany.

Przeciążenia powinny tworzyć spójny interfejs. Jeśli czytelnik musi zapamiętywać wyjątki od reguł lub odgadywać, która funkcja zostanie wybrana, najpierw uprość API, zamiast dodawać kolejne przeciążenia.
