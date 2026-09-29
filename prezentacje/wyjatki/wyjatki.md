# Wyjątki w C++

Wyjątki pozwalają oddzielić normalny przebieg programu od obsługi sytuacji wyjątkowych. Mechanizm opiera się na `throw`, `try` i `catch`, a podczas propagacji wyjątku niszczone są lokalne obiekty o automatycznym czasie życia.

## Cele

Po tej prezentacji powinieneś umieć:

- rzucić i przechwycić wyjątek,
- wyjaśnić stack unwinding,
- stosować RAII razem z wyjątkami,
- łapać wyjątki przez `const&`,
- rozpoznać sytuacje, w których wyjątek nie jest dobrym mechanizmem sterowania.

## Obsługa błędów bez wyjątków

W C typowe podejścia to:

- specjalna wartość zwracana,
- kod błędu,
- `errno`,
- parametr wyjściowy.

Przykład:

```c
#include <stdio.h>

FILE *file = fopen("plik.txt", "r");

if (file == NULL) {
    perror("fopen");
    return 1;
}
```

Taki model jest poprawny, ale kod wywołujący musi pamiętać o sprawdzaniu wyniku każdej operacji.

## `try`, `throw`, `catch`

```cpp
#include <iostream>
#include <stdexcept>

double divide(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("dzielenie przez zero");
    }

    return a / b;
}

int main() {
    try {
        std::cout << divide(10.0, 0.0) << '\n';
    } catch (const std::invalid_argument& e) {
        std::cerr << "błąd: " << e.what() << '\n';
    }
}
```

Po wykonaniu `throw` sterowanie przechodzi do pasującego `catch`.

## Stack unwinding

Jeżeli wyjątek nie zostanie obsłużony w bieżącej funkcji, propaguje się wyżej po stosie wywołań.

Podczas tego procesu niszczone są lokalne obiekty:

```cpp
void f() {
    std::string text = "dane";
    std::vector<int> values(100);

    g();  // jeśli g() rzuci wyjątek, text i values zostaną zniszczone
}
```

To jest jeden z powodów, dla których RAII tak dobrze współpracuje z wyjątkami.

## RAII zamiast ręcznego sprzątania

Ryzykowny styl:

```cpp
Resource *r = new Resource;

operation();  // może rzucić

delete r;
```

Jeżeli `operation()` rzuci wyjątek, `delete` nie zostanie wykonane.

Lepszy model:

```cpp
auto r = std::make_unique<Resource>();

operation();
```

`std::unique_ptr` zwolni zasób automatycznie podczas normalnego wyjścia i podczas stack unwinding.

## Standardowe wyjątki

Często spotykane typy:

- `std::invalid_argument`,
- `std::out_of_range`,
- `std::runtime_error`,
- `std::logic_error`,
- `std::bad_alloc`.

Przykład `std::vector::at()`:

```cpp
std::vector<int> values = {1, 2, 3};

try {
    std::cout << values.at(10) << '\n';
} catch (const std::out_of_range& e) {
    std::cerr << e.what() << '\n';
}
```

## `std::stoi()` może rzucić różne wyjątki

```cpp
try {
    int value = std::stoi(text);
} catch (const std::invalid_argument& e) {
    // tekst nie rozpoczyna się poprawną liczbą
} catch (const std::out_of_range& e) {
    // wynik nie mieści się w int
}
```

Warto znać kontrakt konkretnej funkcji zamiast zakładać jeden wspólny sposób raportowania błędów.

## Brak wyniku nie zawsze jest wyjątkiem

`std::find()` nie rzuca wyjątku tylko dlatego, że elementu nie ma:

```cpp
auto it = std::find(values.begin(), values.end(), 42);

if (it == values.end()) {
    // brak elementu jest normalnym wynikiem wyszukiwania
}
```

To dobra ilustracja zasady: wyjątki są przeznaczone do sytuacji wyjątkowych dla danego interfejsu, a nie do każdego alternatywnego wyniku.

## Łap przez `const&`

Preferowany styl:

```cpp
catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
}
```

Zalety:

- brak niepotrzebnej kopii,
- zachowanie polimorfizmu,
- możliwość obsługi klas pochodnych.

Bardziej szczegółowe typy należy łapać przed ogólnymi:

```cpp
try {
    // ...
} catch (const std::out_of_range& e) {
    // szczegółowo
} catch (const std::exception& e) {
    // ogólnie
}
```

## Własny wyjątek

Najprościej często dziedziczyć po istniejącym typie standardowym:

```cpp
#include <stdexcept>
#include <string>

class ConfigError : public std::runtime_error {
public:
    explicit ConfigError(const std::string& message)
        : std::runtime_error(message) {}
};
```

Użycie:

```cpp
throw ConfigError("brak pola 'port'");
```

Dzięki dziedziczeniu można przechwycić błąd zarówno jako `ConfigError`, jak i ogólnie jako `std::exception`.

## Czego lepiej nie rzucać?

Język pozwala rzucać obiekty wielu typów, ale w praktycznym C++ lepiej unikać:

```cpp
throw "error";  // const char*
throw 42;       // int
```

Klasy wyjątków niosą typ, komunikat i współpracują z hierarchią `std::exception`.

## `noexcept`

Funkcja oznaczona `noexcept` deklaruje, że nie powinna wypuścić wyjątku na zewnątrz:

```cpp
void swap(Widget& a, Widget& b) noexcept;
```

Jeżeli wyjątek opuści funkcję `noexcept`, program wywoła `std::terminate()`.

`noexcept` ma znaczenie m.in. dla destruktorów, operacji przenoszenia i optymalizacji kontenerów standardowych.

## Kiedy używać wyjątków?

Wyjątki dobrze pasują, gdy:

- operacja nie może spełnić swojego kontraktu,
- błąd powinien przejść przez kilka warstw wywołań,
- kod używa RAII do bezpiecznego zarządzania zasobami.

Nie zawsze są najlepsze, gdy:

- alternatywny wynik jest częścią normalnego sterowania,
- kod działa w środowisku bez wyjątków,
- interfejs systemowy naturalnie używa kodów błędów,
- wymagania czasu rzeczywistego zabraniają nieprzewidywalnych ścieżek obsługi.

## Najczęstsze pułapki

- Łapanie wyjątków przez wartość zamiast przez `const&`.
- Ręczne zarządzanie zasobami, które przeciekną podczas stack unwinding.
- `catch (...)` bez jasnego planu dalszej obsługi.
- Rzucanie surowych napisów lub liczb.
- Używanie wyjątków jako zamiennika zwykłych instrukcji warunkowych.
- Ignorowanie informacji o tym, jakie wyjątki może zgłosić używane API.

## Podsumowanie

Najważniejszy przepływ:

```text
throw
  |
szukanie pasującego catch
  |
niszczenie lokalnych obiektów po drodze
  |
catch
```

Wyjątki są najbezpieczniejsze wtedy, gdy zasoby są zarządzane przez RAII, a kod jasno odróżnia normalne wyniki od sytuacji, w których operacja nie może zostać poprawnie wykonana.
