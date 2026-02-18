### Typ wyliczeniowy `enum` w C++

Typ wyliczeniowy (`enum`) pozwala opisać **zamknięty zbiór możliwych wartości** pod czytelnymi nazwami. Zamiast “magicznych liczb” (np. `0,1,2`) używasz sensownych identyfikatorów (`Poniedzialek`, `Wtorek`), co poprawia czytelność i zmniejsza liczbę błędów.

W C++ występują dwie główne odmiany:

* **klasyczny `enum`** (starszy, mniej bezpieczny),
* **`enum class`** (od C++11 – domyślnie polecany).

### Klasyczny `enum`

Klasyczny `enum` tworzy zestaw nazwanych stałych, które **domyślnie mają wartości całkowite** zaczynające się od `0` i rosnące o `1`.

#### Podstawowy przykład

```cpp
enum DzienTygodnia { Poniedzialek, Wtorek, Sroda, Czwartek, Piatek, Sobota, Niedziela };

int main() {
    DzienTygodnia dzien = Poniedzialek; // nazwy trafiają do “globalnej” przestrzeni nazw
}
```

#### Wygoda, ale i ryzyko: automatyczne konwersje

W klasycznym `enum` wartości często da się **łatwo mieszać z int-em** (zależnie od kontekstu i kompilatora), co bywa źródłem błędów.

```cpp
enum Tryb { Off, On };

int main() {
    Tryb t = On;
    int x = t;   // często działa: implicit enum -> int
}
```

#### Kolizje nazw

Nazwy elementów klasycznego `enum` “wychodzą” na zewnątrz, więc łatwo o konflikt:

```cpp
enum Kolor { Czerwony, Zielony };
enum Swiatlo { Zielony, Czerwony }; // BŁĄD: powtórzone nazwy w tym samym zakresie
```

#### Ręczne wartości (np. pod protokoły / pliki / API)

```cpp
enum HttpStatus {
    OK = 200,
    NotFound = 404,
    ServerError = 500
};
```

### `enum class` (zalecany wariant)

`enum class` wprowadza **silne typowanie** i **enkapsulację nazw**. To znaczy:

* elementy zapisujesz jako `Typ::Wartosc`,
* **nie ma automatycznych konwersji do int**,
* łatwiej unikać konfliktów nazw.

#### Podsta wowy przykład

```cpp
#include <iostream>

enum class Kolor { Czerwony, Zielony, Niebieski };

int main() {
    Kolor k = Kolor::Czerwony;

    switch (k) {
        case Kolor::Czerwony: std::cout << "Czerwony\n"; break;
        case Kolor::Zielony:  std::cout << "Zielony\n";  break;
        case Kolor::Niebieski:std::cout << "Niebieski\n";break;
    }
}
```

#### Brak “przypadkowego int-a”

```cpp
enum class Tryb { Off, On };

int main() {
    Tryb t = Tryb::On;
    // int x = t; // BŁĄD: brak niejawnej konwersji
}
```

Jeśli naprawdę potrzebujesz liczby, rób to jawnie:

```cpp
#include <type_traits>

int x = static_cast<int>(Tryb::On);
```

### Typ bazowy (rozmiar i kompatybilność)

Zarówno `enum`, jak i `enum class` mogą mieć określony typ bazowy. To przydaje się, gdy:

* zależy Ci na konkretnym rozmiarze (np. oszczędność pamięci),
* dane mają być zgodne z formatem zewnętrznym (protokół, plik, sieć).

```cpp
#include <cstdint>

enum class Wielkosc : std::uint8_t { Mala, Srednia, Duza };

int main() {
    Wielkosc w = Wielkosc::Srednia;
}
```

### Praktyczne zastosowania

#### Stany programu / maszyny stanów

```cpp
enum class Stan { Uruchomiony, Zatrzymany, Wstrzymany };

void zmienStan(Stan s) {
    // ...
}
```

#### Kody błędów z ręcznymi wartościami

```cpp
enum class Blad : int {
    Brak = 0,
    Ostrzezenie = 1,
    Krytyczny = 2
};

Blad b = Blad::Krytyczny;
```

#### Enum w klasie/strukturze (porządek i brak konfliktów)

```cpp
struct Samochod {
    enum class Typ { Sedan, Kombi, Hatchback };
    Typ typ;
};

int main() {
    Samochod s;
    s.typ = Samochod::Typ::Sedan;
}
```

### Kiedy używać czego?

* **Domyślnie wybieraj `enum class`** (bezpieczniejszy i czytelniejszy).
* **Klasyczny `enum`** bywa ok w starym kodzie, w prostych miejscach albo gdy świadomie chcesz łatwych konwersji (rzadko warto).

Jeśli chcesz, mogę dopisać krótką sekcję o:

* bitmaskach (flagi) i operatorach dla `enum class` (`|`, `&`),
* bezpiecznym wypisywaniu enumów (mapowanie na string),
* `switch` i ostrzeżenia kompilatora, gdy nie obsłużysz wszystkich wartości.
