## Konstrukcja 'include guard' (strażnik załącznika)

Konstrukcja 'include guard', znana też jako "strażnik załącznika", zapewnia, że dany plik nagłówkowy jest załączony tylko raz w jednym źródle. Jest to niezbędne, ponieważ wielokrotne załączenie tego samego pliku nagłówkowego może prowadzić do błędów kompilacji związanych z wielokrotną definicją tych samych zmiennych, struktur czy funkcji.

Poniżej przedstawiono sposób wykorzystania 'include guard' w języku C++:

```cpp
#ifndef NAZWA_PLIKU_H
#define NAZWA_PLIKU_H

  // Zawartość pliku nagłówkowego...

#endif // NAZWA_PLIKU_H
```

Gdy preprocesor napotka dyrektywę #include dla danego pliku:

- Najpierw sprawdza, czy symbol NAZWA_PLIKU_H został już zdefiniowany.
- Jeżeli nie został zdefiniowany, preprocesor definiuje ten symbol i kontynuuje przetwarzanie zawartości pliku.
- Jeśli symbol został już zdefiniowany (co oznacza, że plik został wcześniej załączony), to cała zawartość pliku między #ifndef a #endif jest pomijana.

W praktyce, dla większej czytelności i uniknięcia konfliktów nazw, zaleca się używanie unikalnych nazw dla strażników załącznika, często opartych na nazwie pliku i/lub ścieżce. Dla pliku my_directory/my_header.h strażnik mógłby wyglądać np. tak: MY_DIRECTORY_MY_HEADER_H.

## Makra

Makro w językach programowania, takich jak C i C++, to wyrażenia, które są rozwijane lub podmieniane przez preprocesor przed kompilacją kodu źródłowego. Makra są często używane do definiowania stałych, skrótów i różnych konstrukcji, które mają być ekspandowane w kodzie przed kompilacją.

### Składnia dyrektywy `#define`

Dyrektywa `#define` jest używana do definiowania makr:

```cpp
#define NAZWA_MAKRA wartosc_makra
```

Zaleca się, by nazwy makr były pisane wielkimi literami, choć nie jest to konieczne. Dzięki temu łatwiej je odróżnić od zmiennych i funkcji.

Możemy również definiować makra z argumentami:

```cpp
#define NAZWA_MAKRA(arg1, arg2) wyrażenie_używające_arg1_i_arg2
```

### Przykłady makr

Poniżej przedstawiono różne przykłady makr:

```cpp
// Definiowanie stałej
#define PI 3.141592653589793

// Makro zwracające stałą wartość - wynik dzielenia PI przez 2
#define PI_2 (PI/2)

// Makro zwracające wartość przekazanej liczby podniesionej do kwadratu
// Uwaga: Nawiasy są ważne, by zapewnić poprawne rozwinięcie makra w kodzie.
#define KWADRAT(x) ((x)*(x))

// Makro zwracające większą z dwóch wartości
#define MAKS_2(x, y) ((x) > (y) ? (x) : (y))

// Makro zwracające największą z trzech wartości
#define MAKS_3(x, y, z) MAKS_2(MAKS_2(x, y), z)
```

Powyższe makra korzystają z nawiasów w celu zapewnienia poprawnego rozwinięcia i uniknięcia problemów związanych z kolejnością wykonywania operacji w trakcie ekspansji makr. Nawiasy gwarantują, że wartości argumentów są traktowane jako pojedyncze jednostki podczas operacji.

## Makra vs Funkcje

Makra i funkcje to dwa różne mechanizmy w językach programowania C i C++, które pozwalają na wielokrotne używanie tego samego bloku kodu. Mimo że oba te mechanizmy wydają się podobne, mają różne właściwości i zastosowania.

| Właściwość                            | Makra                                   | Funkcje                                |
|---------------------------------------|-----------------------------------------|----------------------------------------|
| Kompilacja                            | Makra nie są kompilowane                 | Funkcje są kompilowane                  |
| Sprawdzanie typów                     | Typy nie są sprawdzane                   | Typy są sprawdzane                      |
| Wywołanie                             | Kod jest ekspandowany (kopiowany)        | Kod jest wywoływany (funkcja jest wykonywana)|
| Szybkość wykonywania                  | Szybkie (bez kosztu wywołania)           | Generalnie szybkie, ale z kosztem wywołania funkcji |
| Skalowanie (rekursja)                 | Brak wsparcia dla rekursji               | Wsparcie dla rekursji                   |
| Kontrola błędów przez kompilator      | Kompilator nie sprawdza błędów w makrach | Kompilator sprawdza błędy               |
| Zasięg zmiennej                       | Globalny (w całym pliku)                 | Lokalny (tylko wewnątrz funkcji)        |
| Oddzielne przestrzenie nazw           | Nie                                      | Tak                                     |

Chociaż makra są wygodne w wielu sytuacjach, takich jak definicje stałych czy proste operacje, mają pewne ograniczenia i potencjalne pułapki. Na przykład, skomplikowane makra mogą prowadzić do nieoczekiwanych skutków ubocznych z powodu ekspansji kodu. W związku z tym, dla bardziej skomplikowanych operacji, zaleca się korzystanie z funkcji.

### Dyrektywa `#if`

Dyrektywa `#if` umożliwia wykonanie pewnych fragmentów kodu tylko wtedy, gdy określone warunki są spełnione. Jest to użyteczne w wielu scenariuszach, takich jak różne konfiguracje dla różnych platform, włączanie/wyłączanie funkcji debugowania itp.

```cpp
#define FLAGA 1

int main() {

  #if FLAGA
    // Kod do wykonania, gdy FLAGA jest różna od zera (czyli prawda).
  #else
    // Kod do wykonania, gdy FLAGA jest równa zeru (czyli fałsz).
  #endif

  return 0;
}
```

### Rozszerzenia dyrektywy #if

Dyrektywa `#if` może być również używana z `#elif` (wariant "else if").

```cpp
#define WERSJA 2

int main() {

  #if WERSJA == 1
    // Kod dla wersji 1.
  #elif WERSJA == 2
    // Kod dla wersji 2.
  #else
    // Kod dla wszystkich innych wersji.
  #endif

  return 0;
}
```

### Dyrektywa #ifdef i #ifndef

Często używanymi dyrektywami są również `#ifdef` (sprawdza, czy dany symbol/makro został zdefiniowany) oraz `#ifndef` (sprawdza, czy dany symbol/makro nie został zdefiniowany).

```cpp
#define DEBUG

int main() {

  #ifdef DEBUG
    // Kod do wykonania, gdy DEBUG jest zdefiniowany.
  #else
    // Kod do wykonania, gdy DEBUG nie jest zdefiniowany.
  #endif

  return 0;
}
```

Dzięki tym dyrektywom można skutecznie zarządzać kompilacją różnych fragmentów kodu w zależności od konfiguracji lub celów kompilacji.
