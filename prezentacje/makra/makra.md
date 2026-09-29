# Preprocesor, makra i kompilacja warunkowa

Preprocesor działa przed właściwą kompilacją C/C++. Obsługuje m.in. `#include`, `#define` oraz dyrektywy kompilacji warunkowej.

## Cele

Po tej prezentacji powinieneś umieć:

- wyjaśnić rolę preprocesora,
- zabezpieczyć nagłówek przed wielokrotnym dołączeniem,
- rozpoznać pułapki makr funkcyjnych,
- stosować kompilację warunkową,
- wskazać bezpieczniejsze alternatywy dla makr w nowoczesnym C++.

## Include guard

Nagłówek może zostać pośrednio dołączony wiele razy. Include guard sprawia, że jego treść zostanie przetworzona tylko raz w obrębie jednej jednostki translacji.

```cpp
#ifndef MY_PROJECT_WIDGET_H
#define MY_PROJECT_WIDGET_H

struct Widget {
    int value;
};

#endif  // MY_PROJECT_WIDGET_H
```

Dobra nazwa strażnika powinna być możliwie unikalna, np. zawierać nazwę projektu i ścieżkę.

W wielu kompilatorach działa także:

```cpp
#pragma once
```

To rozwiązanie jest bardzo popularne i szeroko wspierane, ale nie jest dyrektywą zdefiniowaną przez standard C/C++.

## Makra obiektowe

```cpp
#define BUFFER_SIZE 4096
#define APP_NAME "demo"
```

Preprocesor wykonuje podstawienie tekstowe przed kompilacją. Makro nie jest zmienną i nie ma typu.

W C++ dla stałych zwykle lepsze są:

```cpp
constexpr std::size_t buffer_size = 4096;
constexpr std::string_view app_name = "demo";
```

## Makra funkcyjne

```cpp
#define SQUARE(x) ((x) * (x))
```

Nawiasy chronią przed częścią błędów związanych z priorytetem operatorów:

```cpp
SQUARE(a + b)
```

bez nawiasów mogłoby rozwinąć się niepoprawnie.

## Najważniejsza pułapka: wielokrotna ewaluacja

```cpp
int i = 3;
int y = SQUARE(i++);
```

Makro rozwija argument tekstowo, więc `i++` pojawia się dwa razy. Taki kod może prowadzić do nieoczekiwanego lub niezdefiniowanego zachowania.

Bezpieczniejsza wersja w C++:

```cpp
template <typename T>
constexpr T square(T x) {
    return x * x;
}
```

Argument funkcji jest obliczany raz, a typ podlega normalnej kontroli kompilatora.

## Makro wieloinstrukcyjne

Jeżeli makro musi zawierać kilka instrukcji, popularny wzorzec wygląda tak:

```cpp
#define LOG_IF_ERROR(expr)        \
    do {                          \
        if (!(expr)) {            \
            log_error(#expr);     \
        }                         \
    } while (0)
```

Konstrukcja `do { ... } while (0)` sprawia, że makro zachowuje się składniowo jak pojedyncza instrukcja.

## Kompilacja warunkowa

```cpp
#if defined(DEBUG)
    log_debug("start");
#endif
```

Można też użyć:

```cpp
#ifdef DEBUG
    // ...
#endif

#ifndef FEATURE_X
    // ...
#endif
```

oraz warunków liczbowych:

```cpp
#define API_VERSION 2

#if API_VERSION >= 2
    // kod dla nowszego API
#else
    // kod zgodności
#endif
```

## Typowe zastosowania kompilacji warunkowej

- kod zależny od platformy,
- opcjonalne funkcje,
- tryb debugowania,
- konfiguracja biblioteki,
- zgodność z różnymi wersjami API.

Przykład:

```cpp
#if defined(_WIN32)
    // Windows
#elif defined(__linux__)
    // Linux
#else
    // inna platforma
#endif
```

## Zasięg makra

Makro nie ma zasięgu blokowego ani przestrzeni nazw jak zmienna czy funkcja. Od miejsca definicji jest widoczne dla preprocesora aż do:

- `#undef`,
- końca jednostki translacji,
- lub końca odpowiedniej gałęzi przetwarzania warunkowego.

```cpp
#define TEMP 10
// ...
#undef TEMP
```

To jeden z powodów, dla których nadmierne użycie makr utrudnia utrzymanie dużych projektów.

## Makra a funkcje

| Cecha | Makro | Funkcja / `constexpr` / szablon |
| --- | --- | --- |
| Kontrola typów | brak na etapie preprocessingu | normalna kontrola typów |
| Argument | może zostać rozwinięty wiele razy | obliczany zgodnie z semantyką języka |
| Debugowanie | trudniejsze | zwykle prostsze |
| Przestrzeń nazw | nie | tak |
| Możliwość optymalizacji inline | nie dotyczy wprost | kompilator może inline'ować |
| Użycie w `#if` | tak | nie |

Makra nie są automatycznie „szybsze” od funkcji. Współczesny kompilator może inline'ować małe funkcje, a bezpieczeństwo typów zwykle jest cenniejsze niż ręczne podstawianie kodu.

## Kiedy makra nadal mają sens?

- include guardy,
- kompilacja warunkowa,
- generowanie kodu wymagające operatorów `#` lub `##`,
- integracja z API lub frameworkiem opartym na makrach.

W pozostałych przypadkach w C++ często lepiej rozważyć:

- `constexpr`,
- `inline`,
- szablony,
- funkcje,
- `enum class`.

## Podsumowanie

Preprocesor jest potężny, ale działa na poziomie tekstu, zanim kompilator sprawdzi typy i semantykę programu. Dlatego:

1. zabezpieczaj nagłówki,
2. otaczaj argumenty i całe wyrażenia makr nawiasami,
3. unikaj argumentów ze skutkami ubocznymi,
4. preferuj konstrukcje języka C++, gdy nie potrzebujesz funkcji dostępnych wyłącznie w preprocesorze.
