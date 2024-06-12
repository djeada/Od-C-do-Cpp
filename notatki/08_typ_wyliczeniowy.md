## Typ wyliczeniowy `enum`

Typ wyliczeniowy `enum` w C++ umożliwia tworzenie zmiennych mogących przyjmować tylko pewien, wstępnie określony zestaw wartości. Każda z tych wartości reprezentowana jest przez czytelną nazwę, co przyczynia się do zwiększenia czytelności kodu. Od C++11 wprowadzono `enum class`, który oferuje silniejsze typowanie i lepszą hermetyzację niż tradycyjne `enum`.

### Tradycyjny `enum`

Tradycyjny `enum` pozwala na zdefiniowanie zestawu nazwanych stałych, które są domyślnie przypisane do wartości całkowitych zaczynając od zera. Możliwe jest również ręczne przypisanie wartości.

Przykład użycia tradycyjnego `enum` do reprezentacji dni tygodnia:

```c++
#include <iostream>

enum DzienTygodnia { Poniedzialek, Wtorek, Sroda, Czwartek, Piatek, Sobota, Niedziela };

int main() {
    DzienTygodnia dzien = Poniedzialek;  // Nie używamy tutaj specyfikatora DzienTygodnia::Poniedzialek

    switch (dzien) {
    case Poniedzialek:
        std::cout << "Dzisiaj jest poniedziałek." << std::endl;
        break;
    case Wtorek:
        std::cout << "Dzisiaj jest wtorek." << std::endl;
        break;
    // ... można kontynuować dla pozostałych dni
    default:
        std::cout << "Nieznany dzień tygodnia!" << std::endl;
    }

    return 0;
}
```

### `enum class`

`enum class`, wprowadzony w C++11, różni się od tradycyjnego `enum` w kilku kluczowych aspektach:

- **Silniejsze typowanie**: wartości `enum class` nie mogą być automatycznie konwertowane na liczby całkowite i odwrotnie, co zapobiega błędom typowania.
- **Brak konfliktów nazw**: wartości `enum class` są przestrzenią nazw dla siebie, co eliminuje potencjalne konflikty nazw.
- **Typ bazowy**: Możliwość określenia typu bazowego dla wartości wyliczeniowych, co może być przydatne w kontekście optymalizacji pamięci lub interoperacyjności z innymi systemami.

Przykład wykorzystania `enum class` do reprezentacji kolorów:

```c++
#include <iostream>

enum class Kolor { Czerwony, Zielony, Niebieski };

int main() {
    Kolor kolor = Kolor::Czerwony;

    switch (kolor) {
    case Kolor::Czerwony:
        std::cout << "Wybrano czerwony." << std::endl;
        break;
    case Kolor::Zielony:
        std::cout << "Wybrano zielony." << std::endl;
        break;
    case Kolor::Niebieski:
        std::cout << "Wybrano niebieski." << std::endl;
        break;
    default:
        std::cout << "Blad!" << std::endl;
    }

    return 0;
}
```

### Zalety użycia `enum class` w porównaniu do tradycyjnych `enum`:

- **Brak konfliktów nazewnictwa**: wartości w `enum class` nie są wprowadzane do przestrzeni nazw, co eliminuje potencjalne konflikty nazw.
- **Silniejsze typowanie**: nie można przypadkowo przekształcić wartości `enum class` na liczbę ani porównać wartości z różnych typów wyliczeniowych bez jawnej konwersji.
- **Możliwość określenia typu bazowego**: `enum class` pozwala określić typ bazowy (np. `enum class Kolor : uint8_t`).

### Praktyczne zastosowania `enum` i `enum class`

1. **Definiowanie stanów**:
    ```c++
    enum class Stan { Uruchomiony, Zatrzymany, Wstrzymany };

    void zmienStan(Stan nowyStan) {
        // logika zmiany stanu
    }
    ```

2. **Przypisywanie wartości**:
    ```c++
    enum class Bledy : int {
        Brak = 0,
        Ostrzezenie = 1,
        Krytyczny = 2
    };

    Bledy blad = Bledy::Krytyczny;
    ```

3. **Przykład z określeniem typu bazowego**:
    ```c++
    enum class Wielkosc : uint8_t { Mala, Srednia, Duza };

    Wielkosc koszulka = Wielkosc::Srednia;
    ```

4. **Używanie w strukturach i klasach**:
    ```c++
    struct Samochod {
        enum class Typ { Sedan, Kombi, Hatchback };
        Typ typ;
    };

    Samochod samochod;
    samochod.typ = Samochod::Typ::Sedan;
    ```
