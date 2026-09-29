# Typy wyliczeniowe: `enum` i `enum class`

Poprzednia notatka pokazała, że generator zwraca wartość, na przykład liczbę oczek na kostce. Sama liczba nie zawsze mówi, jakie ma znaczenie w programie. Typ wyliczeniowy pozwala opisać niewielki, z góry określony zestaw możliwości pod czytelnymi nazwami.

Zamiast pisać:

```cpp
int stan = 2; // Co oznacza 2?
```

możemy nazwać możliwe stany:

```cpp
enum class Stan { Nowy, WTrakcie, Zakonczony };
Stan stan = Stan::WTrakcie;
```

Teraz deklaracja pokazuje, że `stan` przechowuje jedną z wymienionych kategorii, a nie dowolną liczbę całkowitą. W C++ spotkamy dwa warianty: klasyczny `enum` oraz `enum class`, wprowadzony w C++11. W nowym kodzie C++ zwykle wybieramy `enum class`.

## `enum class`: zwykle najlepszy wybór w C++

`enum class` grupuje wartości w typie i wprowadza dla nich osobny zakres nazw. Oznacza to, że zapisujemy je jako `NazwaTypu::NazwaWartosci`. Różne typy mogą więc mieć podobnie nazwane elementy bez konfliktu.

```cpp
#include <iostream>

enum class Kolor { Czerwony, Zielony, Niebieski };

int main() {
    Kolor wybranyKolor = Kolor::Zielony;

    switch (wybranyKolor) {
        case Kolor::Czerwony:
            std::cout << "Wybrano czerwony\n";
            break;
        case Kolor::Zielony:
            std::cout << "Wybrano zielony\n";
            break;
        case Kolor::Niebieski:
            std::cout << "Wybrano niebieski\n";
            break;
    }
}
```

Krok po kroku:

1. Deklaracja `enum class Kolor { ... };` tworzy nowy typ `Kolor` i wymienia jego trzy nazwane wartości.
2. `Kolor wybranyKolor` mówi, że zmienna może przechowywać wartość tego typu.
3. `Kolor::Zielony` wybiera konkretną wartość. Podwójny dwukropek oznacza, że `Zielony` należy do typu `Kolor`.
4. `switch` wybiera działanie zależnie od przechowywanej wartości. `break` kończy daną gałąź, aby wykonanie nie przechodziło do następnego `case`.

Elementów `enum class` nie można niejawnie użyć jako liczb całkowitych. Na przykład poniższe przypisanie jest błędem:

```cpp
enum class Tryb { Wylaczony, Wlaczony };

int main() {
    Tryb tryb = Tryb::Wlaczony;
    // int numer = tryb; // błąd: konwersja nie jest niejawna
}
```

Jeśli program rzeczywiście potrzebuje liczby, konwersję trzeba zapisać jawnie:

```cpp
enum class Tryb { Wylaczony, Wlaczony };

int main() {
    int numer = static_cast<int>(Tryb::Wlaczony);
}
```

Nie należy jednak traktować tej liczby jako tekstowej nazwy wartości. Strumień `std::cout` sam z siebie nie wypisze `Wlaczony`; nazwę trzeba obsłużyć na przykład przez `switch`. Podobnie, jeśli program odczytuje liczbę z pliku lub sieci i zamienia ją na enum przez `static_cast`, taka konwersja nie sprawdza, czy liczba odpowiada jednej z dozwolonych wartości. Dane z zewnątrz trzeba zweryfikować osobno.

## Wartości domyślne i wartości przypisane ręcznie

Jeśli nie podamy numerów, elementy otrzymują kolejne wartości całkowite, zaczynając od zera. Dla tego przykładu `Mala` ma wartość 0, `Srednia` ma 1, a `Duza` ma 2:

```cpp
enum class Wielkosc { Mala, Srednia, Duza };
```

Można przypisać konkretne liczby, na przykład wtedy, gdy program musi korzystać z kodów określonych przez zewnętrzne API:

```cpp
enum class KodOdpowiedzi {
    Sukces = 200,
    NieZnaleziono = 404,
    BladSerwera = 500
};
```

Wartości domyślne są wygodne wewnątrz programu, ale mogą się zmienić, gdy zmienimy kolejność elementów albo dodamy nowy element. Jeśli liczby są częścią protokołu, formatu pliku lub publicznego interfejsu, przypisz je świadomie i mapuj je na format zewnętrzny. Samo zapisanie obiektu `enum` bezpośrednio do pliku nie jest przenośnym sposobem serializacji — reprezentacja w pamięci to osobna kwestia.

## Klasyczny `enum`

Klasyczny `enum` pochodzi ze starszego stylu C i C++. Jego nazwy trafiają do zakresu otaczającego deklarację, a elementy mogą być niejawnie konwertowane na liczby całkowite. To bywa wygodne we współpracy ze starszym kodem, ale zwiększa ryzyko przypadkowego użycia niewłaściwej wartości.

```cpp
enum Tryb { Wylaczony, Wlaczony };

int main() {
    Tryb tryb = Wlaczony; // bez prefiksu Tryb::
    int numer = tryb;     // klasyczny enum można niejawnie zamienić na liczbę
}
```

Elementy klasycznego `enum` mogą kolidować z innymi nazwami w tym samym zakresie:

```cpp
enum Kolor { Czerwony, Zielony };
// enum Sygnal { Zielony, Czerwony }; // błąd: te nazwy są już zajęte
```

Można wpisać elementy do różnych typów, ale w klasycznym wariancie nie rozwiązuje to konfliktu nazw, bo ich nazwy nadal należą do zakresu otaczającego. `enum class` rozwiązuje problem przez zapis `Kolor::Zielony` i `Sygnal::Zielony`.

## Typ bazowy

Typ bazowy określa całkowity typ używany do reprezentowania wartości wyliczeniowych. Można go podać jawnie, gdy interfejs wymaga konkretnego typu:

```cpp
#include <cstdint>

enum class Rozmiar : std::uint8_t { Maly, Sredni, Duzy };
```

`std::uint8_t` jest tu typem bazowym. W typowym kodzie aplikacji nie trzeba go wybierać tylko po to, by „oszczędzić pamięć”. Wymagania formatu zewnętrznego trzeba sprawdzić osobno: typ bazowy nie ustala kolejności bajtów w pliku ani nie rozwiązuje problemu zgodności różnych wersji programu.

## Różnica między C i C++

W C można deklarować klasyczne typy `enum`, ale nie ma składni C++ `enum class`. Dlatego w C nazwy elementów są używane bez kwalifikatora typu, a projektując je, warto nadawać im unikatowe prefiksy:

```c
enum tryb { TRYB_WYLACZONY, TRYB_WLACZONY };

int main(void) {
    enum tryb aktualny = TRYB_WLACZONY;
    return 0;
}
```

C++ dodaje `enum class`, które ogranicza zakres nazw i wymaga jawnego podejścia do konwersji na liczby. Szczegóły dotyczące typów bazowych w C zależą od wersji standardu C; jeśli enum jest częścią binarnego interfejsu, należy oprzeć się na wymaganiach konkretnego standardu i platformy, a nie zakładać, że oba języki reprezentują go identycznie.

## Kiedy używać typu wyliczeniowego?

Użyj `enum class`, gdy wartość może przyjmować jedną z kilku nazwanych kategorii: stan zamówienia, kierunek ruchu, tryb pracy, rodzaj komunikatu albo wynik losowania. Nie zastępuj enumem liczby, która może przyjmować dowolną wartość, na przykład temperatury lub liczby punktów.

W C++ domyślnie wybieraj `enum class`. Klasyczny `enum` zostaw głównie dla zgodności ze starszym kodem lub z interfejsem, który tego wymaga. Gdy enum ma wpływać na zachowanie programu, `switch` pozwala jawnie pokazać, co robi program dla każdej wartości. W następnej notatce zobaczymy, jak wydzielić taką logikę do funkcji i przekazać jej dane.
