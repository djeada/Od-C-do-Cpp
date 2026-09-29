# Programowanie obiektowe w C++

W poprzednich notatkach tekst był ciągiem bajtów, a maska pozwalała wybrać bity opisujące stan. W programie można te dane połączyć: na przykład wiadomość ma treść i status „przeczytana”. Klasa pozwala przechowywać taki stan razem z operacjami, które go zmieniają. To podstawowa idea programowania obiektowego: program organizujemy wokół elementów mających własne dane i jasno określone czynności.

Klasy nie trzeba tworzyć dla każdego kawałka danych. Dobrze służy wtedy, gdy chcemy określić, co element przechowuje, za co odpowiada i jakie reguły muszą pozostać prawdziwe podczas jego używania.

## Klasa opisuje obiekty, obiekt ma własny stan

**Klasa** jest definicją rodzaju obiektu: opisuje, jakie dane i operacje będą dostępne. **Obiekt** jest konkretnym egzemplarzem tej klasy. Można myśleć o klasie jak o projekcie, a o obiekcie jak o jednej wykonanej według niego rzeczy. Każdy obiekt ma własne wartości pól, nawet jeśli wszystkie obiekty utworzono z tej samej klasy.

Poniższa klasa przechowuje treść wiadomości oraz dwie flagi. Flagi są liczbą, a jej bity odpowiadają statusom. To połączenie z poprzednią notatką o operacjach bitowych: klasa ukrywa maski i daje nazwy operacjom, które zmieniają status.

```cpp
#include <iostream>
#include <string>

class Wiadomosc {
public:
    explicit Wiadomosc(const std::string& tresc)
        : tresc_(tresc), flagi_(0) {}

    const std::string& tresc() const {
        return tresc_;
    }

    void oznacz_przeczytana() {
        flagi_ |= PRZECZYTANA;
    }

    void oznacz_wazna() {
        flagi_ |= WAZNA;
    }

    bool czy_przeczytana() const {
        return (flagi_ & PRZECZYTANA) != 0;
    }

    bool czy_wazna() const {
        return (flagi_ & WAZNA) != 0;
    }

private:
    enum : unsigned int {
        PRZECZYTANA = 1u << 0,
        WAZNA = 1u << 1
    };

    std::string tresc_;
    unsigned int flagi_;
};

int main() {
    Wiadomosc pierwsza("Spotkanie o 15:00");
    Wiadomosc druga("Przynieś notatki");

    std::cout << pierwsza.tresc() << '\n';
    std::cout << pierwsza.czy_przeczytana() << '\n'; // 0: początkowo nieprzeczytana

    pierwsza.oznacz_przeczytana();
    pierwsza.oznacz_wazna();

    std::cout << pierwsza.czy_przeczytana() << '\n'; // 1
    std::cout << pierwsza.czy_wazna() << '\n';      // 1
    std::cout << druga.czy_przeczytana() << '\n';   // 0: drugi obiekt ma własny stan

    Wiadomosc* wskaznik = &druga;
    wskaznik->oznacz_przeczytana();
    std::cout << druga.czy_przeczytana() << '\n';   // 1: zmieniliśmy wskazywany obiekt
}
```

Gdy program wykonuje `Wiadomosc pierwsza(...)`, konstruktor tworzy nowy obiekt. Inicjalizuje `tresc_` przekazanym tekstem, a `flagi_` zerem — zatem na początku żaden status nie jest włączony. Następnie powstaje niezależny obiekt `druga`; zmiany statusu pierwszej wiadomości nie zmieniają drugiej.

`oznacz_przeczytana()` wykonuje OR z maską `0001`, więc ustawia bit numer 0, nie zmieniając pozostałych bitów. `czy_przeczytana()` wykonuje AND z tą samą maską: wynik niezerowy oznacza, że bit jest ustawiony. Analogicznie działa status ważności na bicie numer 1. Użytkownik klasy nie musi pamiętać, że „przeczytana” oznacza bit zero — wywołuje metodę o mówiącej nazwie.

Ostatnie trzy wiersze kodu pokazują wskaźnik: `&druga` pobiera adres istniejącego obiektu, a `wskaznik->oznacz_przeczytana()` wywołuje metodę właśnie na tym obiekcie. Wskaźnik przechowuje adres, nie kopię wiadomości. Po tej operacji status `druga` jest już włączony.

## Enkapsulacja: ukryj reprezentację, udostępnij operacje

Pola `tresc_` i `flagi_` są prywatne (`private`), a metody do odczytu i zmiany statusu są publiczne (`public`). Takie połączenie ukrytych danych i kontrolowanych operacji nazywa się **enkapsulacją**.

Gdyby `flagi_` było publiczne, kod korzystający z klasy mógłby wpisać do niego dowolną liczbę, np. ustawić bity dla statusów, których klasa w ogóle nie rozumie. W obecnej wersji obiekt rozpoczyna działanie z zerem, a jego publiczne metody zmieniają tylko dwa znane bity. Dzięki temu spełniona jest reguła (nazywana **niezmiennikiem obiektu**): „w polu statusu wolno ustawiać tylko bity zdefiniowane przez `Wiadomosc`”. Każda nowa metoda zmieniająca status powinna tę regułę zachować.

Enkapsulacja nie polega wyłącznie na ukrywaniu pól. Klasa ma pilnować zasad swojego modelu. Przykładowo klasa konta bankowego mogłaby zabronić wypłaty większej niż saldo, a klasa prostokąta mogłaby wymagać dodatnich boków. Konstruktor ustanawia początkowy poprawny stan; każda metoda, która go zmienia, musi utrzymać tę samą regułę. Jeżeli publiczne pola pozwalają w dowolnej chwili wpisać błędne wartości, obiekt nie ma jak tych zasad dopilnować.

Na koncie bankowym niezmiennikiem może być „saldo nie jest ujemne”. Obiekt zaczyna ze stanem 100 zł zapisanym w groszach. Wypłata 120 zł zostaje odrzucona, bo zmieniłaby saldo na wartość ujemną; stan konta pozostaje wtedy bez zmian:

```cpp
#include <iostream>

class Konto {
public:
    bool wyplac(int kwota_groszy) {
        if (kwota_groszy <= 0 || kwota_groszy > saldo_grosze_) {
            return false; // odmowa: saldo nie zostaje zmienione
        }
        saldo_grosze_ -= kwota_groszy;
        return true;
    }

    int saldo() const {
        return saldo_grosze_;
    }

private:
    int saldo_grosze_ = 10000; // stan początkowy: 100 zł
};

int main() {
    Konto konto;
    bool wyplacono = konto.wyplac(12000); // próba wypłaty 120 zł
    std::cout << wyplacono << '\n';       // 0: operacja odrzucona
    std::cout << konto.saldo() << '\n';   // 10000: nadal 100 zł
}
```

`saldo_grosze_` jest prywatne, więc kod zewnętrzny nie może ustawić go np. na `-2000`. Jedyną pokazaną drogą zmiany salda jest `wyplac`, a ta metoda zmniejsza je wyłącznie po sprawdzeniu warunków. Właśnie dlatego stan i reguła powinny należeć do tej samej klasy.

Publiczne metody tworzą **interfejs klasy**: mówią, co użytkownik może z obiektem zrobić. Pole prywatne opisuje, jak klasa przechowuje dane. Jeśli później zmienimy `flagi_` na dwa pola `bool`, korzystający z klasy może nadal wywoływać te same metody. Taki podział pozwala zmieniać wnętrze bez zmuszania reszty programu do poznawania szczegółów.

## Poziomy dostępu

C++ ma trzy główne modyfikatory dostępu:

- `public` — element należy do interfejsu widocznego dla kodu używającego obiektu;
- `private` — element jest dostępny tylko wewnątrz klasy i dla jej funkcji zaprzyjaźnionych;
- `protected` — element jest dostępny wewnątrz klasy oraz jej klas pochodnych, ale nie dla dowolnego kodu z zewnątrz.

W klasie (`class`) składniki są domyślnie prywatne. Przy dziedziczeniu domyślny poziom również jest prywatny. `protected` bywa przydatne w hierarchiach, ale nadmierne odsłanianie pól klasie pochodnej wiąże ją ze szczegółami implementacji klasy bazowej. Często lepiej udostępnić funkcję `protected`, która wykonuje dozwoloną operację.

## Konstruktor i powstanie obiektu

Konstruktor jest wywoływany przy tworzeniu obiektu. Ma nazwę klasy i nie ma typu zwracanego. Jego lista inicjalizacyjna (część po dwukropku) ustawia pola, zanim wykona się ciało konstruktora. W przykładzie powyżej `tresc_(tresc), flagi_(0)` określa stan początkowy nowej wiadomości.

Możemy zdefiniować kilka konstruktorów z różnymi parametrami, np. jeden przyjmujący tekst, a drugi tworzący pustą wiadomość. W klasie `Wiadomosc` z pierwszego przykładu zdefiniowaliśmy tylko konstruktor przyjmujący tekst. Dlatego `Wiadomosc w("Treść");` jest poprawne, ale `Wiadomosc w;` nie — nie ma konstruktora bezargumentowego. Dodaj taki konstruktor tylko wtedy, gdy pusty obiekt ma sens w modelu.

Kompilator może też tworzyć operacje kopiowania i przenoszenia:

- konstruktor kopiujący tworzy nowy obiekt ze stanu istniejącego obiektu;
- konstruktor przenoszący może przejąć zasoby obiektu tymczasowego;
- przypisanie kopiuje albo przenosi stan do już istniejącego obiektu.

Zakładając, że definicja klasy `Wiadomosc` z pierwszego przykładu jest dostępna, poniższy `main` pokazuje kopię dwóch wiadomości:

```cpp
int main() {
    Wiadomosc oryginal("Plan na jutro");
    Wiadomosc kopia = oryginal;
    oryginal.oznacz_przeczytana();
    std::cout << kopia.czy_przeczytana() << '\n'; // 0: kopia zachowuje własny stan
}
```

`kopia` jest odrębnym obiektem. Zawiera ten sam tekst i statusy co `oryginal` w chwili kopiowania, ale późniejsza zmiana statusu jednego z nich nie zmienia drugiego. `std::string` sam poprawnie kopiuje własne znaki, dlatego dla takiej klasy zwykle nie trzeba pisać konstruktora kopiującego ręcznie.

Współczesne C++ zaleca tzw. **regułę zera**: jeśli zasoby, takie jak pamięć tekstu, przechowujemy w gotowych typach zarządzających nimi (`std::string`, `std::vector`, `std::unique_ptr`), zwykle nie piszemy samodzielnie destruktora ani własnych metod kopiowania/przenoszenia. Ręczne zarządzanie zasobem wymaga przemyślenia kopiowania, przenoszenia i zwalniania, inaczej łatwo o wyciek lub dwukrotne zwolnienie pamięci.

## Czas życia i destruktor

Obiekt lokalny istnieje od miejsca utworzenia do końca otaczającego go bloku. Wtedy C++ automatycznie wywołuje destruktor — metodę zapisaną jako `~NazwaKlasy()`. Destruktor jest potrzebny przede wszystkim wtedy, gdy klasa bezpośrednio zarządza zasobem, który trzeba zwolnić. W typowym kodzie nie pisze się destruktora, który tylko wyświetla komunikat.

```cpp
int main() {
    {
        Wiadomosc tymczasowa("Ta wiadomość istnieje w bloku");
        // W tym miejscu obiekt można używać.
    } // kończy się zakres: niszczony jest obiekt tymczasowa
}
```

Nie wolno użyć `delete` do takiego obiektu lokalnego. `delete` jest przeznaczone dla obiektów zaalokowanych odpowiednim `new`, ale w zwykłym C++ należy preferować obiekty lokalne i gotowe typy zarządzające pamięcią. Jeśli polimorficzne obiekty klas pochodnych są usuwane przez wskaźnik do klasy bazowej, destruktor bazowy powinien być wirtualny.

## Referencje i wskaźniki do obiektów

Funkcja często ma tylko odczytać istniejący obiekt, bez tworzenia kopii. Przyjmujemy wtedy referencję do stałego obiektu (`const T&`). Po definicji klasy `Wiadomosc` z pierwszego przykładu można napisać:

```cpp
#include <iostream>

void wypisz(const Wiadomosc& wiadomosc) {
    std::cout << wiadomosc.tresc() << '\n';
}
```

Referencja musi odnosić się do istniejącego obiektu. `const` oznacza, że ta funkcja może odczytywać obiekt, ale nie zmieniać go przez tę referencję. Wskaźnik (`T*`) może nie wskazywać na obiekt — może mieć wartość `nullptr` — i wymaga sprawdzenia, zanim zostanie użyty. Operator `->` wywołuje metodę obiektu wskazywanego przez wskaźnik. W nowoczesnym C++ do współdzielenia lub przekazania własności obiektu dynamicznego służą inteligentne wskaźniki, np. `std::unique_ptr`, zamiast ręcznej pary `new`/`delete`.

## Odpowiedzialność klasy i współpraca typów

Wiadomość zna swoją treść i potrafi raportować lub zmieniać własne statusy. Kod poza klasą decyduje, kiedy poprosić ją o taką zmianę, ale nie grzebie bezpośrednio w jej reprezentacji. To jest podział odpowiedzialności: każdy typ powinien odpowiadać za spójność tych danych i operacji, które do niego należą.

Ten sam pomysł działa w większym programie. Klasa `Dokument` może przechowywać tekst w `std::string` i udostępnić wyszukiwanie słowa. Klasa `Wiadomosc` może używać kilku flag bitowych, ale ujawniać je przez nazwy metod. Użytkownik klasy pracuje wtedy z pojęciami programu, a nie z liczbami bajtów i maskami. Jeśli typ robi zbyt wiele różnych rzeczy, jego odpowiedzialności należy rozdzielić.

## Dziedziczenie i polimorfizm

Dziedziczenie pozwala zdefiniować klasę pochodną, która jest szczególnym rodzajem klasy bazowej. Stosuj je, gdy ta relacja ma sens, a nie tylko po to, by odziedziczyć kilka pól lub funkcji.

Funkcja wirtualna umożliwia wybranie implementacji na podstawie rzeczywistego typu obiektu, nawet gdy używamy go przez referencję do klasy bazowej:

```cpp
#include <iostream>

class Powiadomienie {
public:
    virtual ~Powiadomienie() = default;
    virtual void pokaz() const {
        std::cout << "Nowe powiadomienie\n";
    }
};

class PowiadomienieTekstowe : public Powiadomienie {
public:
    void pokaz() const override {
        std::cout << "Nowa wiadomość tekstowa\n";
    }
};

void wyswietl(const Powiadomienie& p) {
    p.pokaz();
}

int main() {
    PowiadomienieTekstowe sms;
    wyswietl(sms); // wypisuje "Nowa wiadomość tekstowa"
}
```

Jeśli `wyswietl` otrzyma obiekt `PowiadomienieTekstowe`, wywoła jego wersję `pokaz`, mimo że parametr ma typ `const Powiadomienie&`. `override` prosi kompilator o sprawdzenie, czy metoda rzeczywiście nadpisuje funkcję wirtualną z klasy bazowej. Wirtualny destruktor klasy bazowej zapewnia prawidłowe niszczenie obiektu pochodnego, gdy jest usuwany przez wskaźnik do bazy.

## Przeciążanie operatorów

Przeciążenie operatora pozwala określić, co operator taki jak `+`, `==` lub `<<` ma oznaczać dla obiektów własnej klasy. Dobrze użyty zapis odpowiada naturalnemu znaczeniu operacji — np. suma wektorów — i ułatwia czytanie kodu.

```cpp
#include <iostream>

class Wektor2D {
public:
    Wektor2D(int x, int y) : x_(x), y_(y) {}

    Wektor2D operator+(const Wektor2D& drugi) const {
        return Wektor2D(x_ + drugi.x_, y_ + drugi.y_);
    }

    int x() const { return x_; }
    int y() const { return y_; }

private:
    int x_;
    int y_;
};

int main() {
    Wektor2D wynik = Wektor2D(2, 3) + Wektor2D(4, 1);
    std::cout << '(' << wynik.x() << ", " << wynik.y() << ")\n";
}
```

Operator `+` nie zmienia operandów, dlatego metoda jest oznaczona `const` i zwraca nowy obiekt. Nie można tworzyć nowych symboli operatorów ani zmieniać ich pierwszeństwa. Nie przeciążaj operatora w znaczeniu zaskakującym — jeśli `a + b` usuwa plik albo zmienia `b`, zapis przestaje być czytelny.

## Składniki statyczne

Zwykłe pole należy do obiektu, więc każdy egzemplarz ma własną wartość. Pole `static` należy do klasy i jest wspólne dla wszystkich jej obiektów. Statyczna metoda nie jest wywoływana na konkretnym obiekcie i nie ma wskaźnika `this`; może bezpośrednio używać tylko składników statycznych.

```cpp
#include <iostream>

class Ustawienia {
public:
    static int limit;

    static int pobierz_limit() {
        return limit;
    }
};

int Ustawienia::limit = 100;

int main() {
    std::cout << Ustawienia::pobierz_limit() << '\n';
}
```

Definicja `int Ustawienia::limit = 100;` tworzy wspólne pole klasy (dla standardów przed C++17 trzeba umieścić ją poza definicją klasy, zwykle w jednym pliku źródłowym). Wartość odczytuje się przez `Ustawienia::limit`, a nie przez konkretne konto/obiekt. W C++17 można też użyć pola `inline static` zainicjalizowanego wewnątrz klasy.

## Funkcje zaprzyjaźnione

Funkcja zaprzyjaźniona jest zwykłą funkcją spoza klasy, której deklaracja `friend` zezwala na dostęp do prywatnych składników. Przydaje się na przykład przy wypisywaniu obiektu, gdy funkcja `operator<<` ma odczytać kilka prywatnych pól. To wyjątek od enkapsulacji, więc używaj go tylko wtedy, gdy nie da się równie jasno skorzystać z publicznego interfejsu.

```cpp
#include <iostream>

class Punkt {
public:
    Punkt(int x, int y) : x_(x), y_(y) {}

    friend std::ostream& operator<<(std::ostream& out, const Punkt& p) {
        return out << '(' << p.x_ << ", " << p.y_ << ')';
    }

private:
    int x_;
    int y_;
};

int main() {
    Punkt p(2, 5);
    std::cout << p << '\n'; // (2, 5)
}
```

Operator `<<` nie jest metodą `Punkt` — jego lewym argumentem jest strumień `std::cout`. Dzięki `friend` może jednak odczytać prywatne współrzędne `p` i zapisać je do strumienia. Sama funkcja zaprzyjaźniona nie staje się składnikiem klasy.

## `struct` i `class`

W C++ `struct` i `class` mogą zawierać te same rodzaje składników. Różnią się wartościami domyślnymi: w `struct` pola i metody są publiczne, a dziedziczenie jest publiczne; w `class` pola i metody są prywatne, a dziedziczenie prywatne. W praktyce `struct` często opisuje prostą paczkę danych, której pola można bezpośrednio odczytywać, a `class` — typ, który sam pilnuje reguł stanu.

```cpp
#include <iostream>

struct Wspolrzedne {
    int x;
    int y;
};

int main() {
    Wspolrzedne p{3, 4};
    std::cout << p.x << '\n'; // dostęp publiczny
}
```

W C `struct` służy do grupowania danych i nie ma metod ani modyfikatorów dostępu. W C nazwa typu wymaga zwykle słowa `struct`, np. `struct Punkt p;`; w C++ wystarczy `Punkt p;`, jeśli typ nazywa się `Punkt`.

```c
#include <stdio.h>

struct Wspolrzedne {
    int x;
    int y;
};

int main(void) {
    struct Wspolrzedne p = {3, 4};
    printf("(%d, %d)\n", p.x, p.y);
    return 0;
}
```

W C pola takiej struktury są bezpośrednio dostępne, więc kod może wpisać do nich dowolne wartości. Jeśli program musi pilnować reguły, np. dodatnich wymiarów, trzeba kontrolować zmiany przez funkcje; w C++ może to robić prywatny stan klasy.

## Unie i pola bitowe

Unia (`union`) daje swoim składowym wspólny obszar pamięci. Kiedy zapiszemy jedną składową, to ona staje się aktywna; nie wolno bezwarunkowo odczytywać innej składowej tak, jakby nadal zawierała swoją poprzednią wartość. W C++17 dla wartości, która może mieć jeden z kilku alternatywnych typów, zazwyczaj łatwiej i bezpieczniej użyć `std::variant`.

```cpp
#include <variant>
#include <iostream>

int main() {
    std::variant<int, float> wartosc = 10;
    wartosc = 3.14f; // aktywną alternatywą jest teraz float
    float liczba = std::get<float>(wartosc);
    std::cout << liczba << '\n';
}
```

`std::variant<int, float>` jawnie pamięta, który z dopuszczonych typów jest aktywny. `std::get<float>` odczytuje wartość wtedy, gdy aktywny typ to `float`; w przeciwnym razie zgłasza `std::bad_variant_access`. W odróżnieniu od zwykłej unii typ alternatywy jest częścią stanu obiektu.

Przykład zwykłej unii:

```cpp
union Liczba {
    int calkowita;
    float rzeczywista;
};

int main() {
    Liczba liczba{};
    liczba.calkowita = 10;       // aktywna składowa: calkowita
    liczba.rzeczywista = 3.14f;  // teraz aktywna jest rzeczywista
    // Nie odczytuj teraz liczba.calkowita.
}
```

Pole bitowe określa liczbę bitów przeznaczoną na pole całkowite. Może być przydatne, gdy zakres wartości jest mały, ale standard nie gwarantuje przenośnego układu pól w pamięci. Nie zapisuj więc takiej struktury wprost jako przenośnego formatu pliku ani protokołu sieciowego — koduj i dekoduj bity jawnie.

```cpp
struct Data {
    unsigned int rok : 13;     // zakres wartości: 0–8191
    unsigned int miesiac : 4;  // 0–15
    unsigned int dzien : 5;    // 0–31
};
```

Wartości miesiąca `1`–`12` i dnia `1`–`31` mieszczą się w podanych polach, lecz same pola nie sprawdzają, czy data istnieje — np. czy 31 lutego jest poprawne. To dobry przykład różnicy między **zakresem reprezentacji** (ile wartości da się zapisać) a **regułą modelu** (które z nich mają sens). Jeśli obiekt daty ma pilnować tej reguły, potrzebuje konstruktora i operacji, które sprawdzą kalendarz, zamiast publicznie udostępniać same liczby.
