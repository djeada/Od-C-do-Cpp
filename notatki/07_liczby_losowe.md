# Liczby losowe i generatory liczb losowych

W języku C++ liczby losowe generuje się za pomocą standardowej biblioteki `<random>`. Proces losowania zaczyna się od utworzenia generatora liczb pseudolosowych, np. `std::mt19937`, który bazuje na algorytmie Mersenne Twister. Aby uzyskać bardziej losowe wyniki, generator inicjalizuje się za pomocą unikalnej wartości, zwanej "ziarnem" (ang. *seed*), co można zrobić np. poprzez `std::random_device`. Następnie używa się odpowiednich dystrybucji, takich jak `std::uniform_int_distribution` (dla liczb całkowitych z równomiernym rozkładem) lub `std::uniform_real_distribution` (dla liczb zmiennoprzecinkowych), aby wygenerować liczby z określonego zakresu. Dzięki tej bibliotece losowanie w C++ jest bardziej elastyczne i daje kontrolę nad różnymi aspektami generowania liczb losowych, w tym nad zakresem i typem wartości.

## Liczby losowe

Liczby losowe to wartości numeryczne generowane w taki sposób, że nie da się przewidzieć ich kolejności czy wartości bez znajomości wewnętrznych mechanizmów generowania. W kontekście informatyki i matematyki, liczby te są niezbędne w wielu zastosowaniach, takich jak symulacje komputerowe, kryptografia, statystyka czy gry losowe.

### Pseudolosowość a prawdziwa losowość

Warto zauważyć, że komputery, będąc maszynami deterministycznymi, nie są w stanie generować prawdziwie losowych liczb bez zewnętrznego źródła entropii. Dlatego też korzystają z algorytmów generujących liczby pseudolosowe (PRNG - Pseudorandom Number Generator). Algorytmy te produkują sekwencje liczb, które wyglądają na losowe i spełniają pewne statystyczne własności losowości, ale są deterministyczne i powtarzalne, jeśli znany jest ich stan początkowy (tzw. ziarno - seed).

### Zastosowania liczb losowych

Liczby losowe są używane w:

- **Symulacjach komputerowych** do modelowania zjawisk losowych w fizyce, chemii czy ekonomii.
- **Kryptografii** do generowania kluczy szyfrujących, wektorów inicjujących i innych elementów bezpieczeństwa.
- **Grach komputerowych** do tworzenia nieprzewidywalnych zachowań przeciwników czy losowych zdarzeń.
- **Metodach Monte Carlo** w numerycznej integracji i optymalizacji.
- **Testowaniu i walidacji** do tworzenia losowych danych testowych.

## Generowanie liczb losowych w C++

W języku C++ od wersji C++11 wprowadzono nowoczesne narzędzia do generowania liczb pseudolosowych w postaci biblioteki `<random>`. Biblioteka ta oferuje różnorodne generatorów i dystrybucji, pozwalając na precyzyjną kontrolę nad procesem generowania.

### Generatory i dystrybucje

Proces generowania liczb losowych w C++ opiera się na dwóch elementach:

1. **Generator liczb losowych** to algorytm dostarczający sekwencję losowych bitów. Przykłady to `std::mt19937` (Mersenne Twister) czy `std::random_device`.
2. **Dystrybucja** to funkcja przekształcająca losowe bity z generatora na liczby w określonym rozkładzie (np. równomiernym, normalnym, Poissona).

### Inicjalizacja generatora

Ważne jest, aby generator został zainicjalizowany odpowiednim ziarnem, co zapewnia różnorodność generowanych sekwencji. `std::random_device` może być użyty do pobrania entropii z systemu operacyjnego, co jest szczególnie istotne w aplikacjach kryptograficznych.

Przykład funkcji `losowa_z_przedzialu()`:

```c++
#include <random>

int losowa_z_przedzialu(int start, int end) {
    // Inicjalizacja generatora liczb losowych
    std::random_device rd;   // Źródło prawdziwej entropii (jeśli dostępne)
    std::mt19937 gen(rd());  // Mersenne Twister PRNG, zainicjalizowany za pomocą rd()
    std::uniform_int_distribution<> dist(start, end); // Dystrybucja równomierna na przedziale [start, end]
    return dist(gen); // Generowanie liczby losowej
}
```

W powyższym kodzie:

- `std::random_device rd;` służy do pobrania losowego ziarna z systemu.
- `std::mt19937 gen(rd());` tworzy generator Mersenne Twister z ziarna `rd()`.
- `std::uniform_int_distribution<> dist(start, end);` definiuje dystrybucję równomierną całkowitoliczbową.
- `return dist(gen);` zwraca liczbę losową z określonego przedziału.

## Przykłady zastosowania

### Rzut monetą

Symulacja rzutu monetą jest klasycznym przykładem wykorzystania liczb losowych. Moneta ma dwa możliwe wyniki: orzeł lub reszka, co odpowiada zdarzeniu losowemu z prawdopodobieństwem 0.5 dla każdego wyniku.

```c++
#include <iostream>
#include <random>

bool orzel_lub_reszka() {
    // Użycie dystrybucji Bernoulliego
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist(0.5); // Prawdopodobieństwo sukcesu 0.5
    return dist(gen);
}

int main() {
    if (orzel_lub_reszka()) {
        std::cout << "Orzeł" << std::endl;
    } else {
        std::cout << "Reszka" << std::endl;
    }
    return 0;
}
```

- Używamy `std::bernoulli_distribution`, która zwraca `true` z określonym prawdopodobieństwem.
- Generator `gen` jest zainicjalizowany z ziarnem z `std::random_device`.

### Rzut kostką

Symulacja rzutu sześciościenną kostką wymaga generowania liczb całkowitych z przedziału [1,6], gdzie każda liczba ma jednakowe prawdopodobieństwo wystąpienia.

```c++
#include <iostream>
#include <random>

int rzut_kostka() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 6); // Dystrybucja równomierna całkowitoliczbowa
    return dist(gen);
}

int main() {
    std::cout << "Wynik rzutu kostką: " << rzut_kostka() << std::endl;
    return 0;
}
```

- Używamy dystrybucji równomiernej całkowitoliczbowej na przedziale [1,6].
- Każdy wynik ma prawdopodobieństwo 1/6.

### Generator haseł

Generowanie silnych, losowych haseł jest kluczowe dla bezpieczeństwa danych. W tym przykładzie tworzymy hasło o określonej długości, składające się z losowo wybranych znaków z predefiniowanego zestawu.

```c++
#include <iostream>
#include <string>
#include <random>

std::string generuj_haslo(int dlugosc) {
    const std::string zestaw_znakow = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, zestaw_znakow.size() - 1);

    std::string haslo;
    for(int i = 0; i < dlugosc; i++) {
        haslo += zestaw_znakow[dist(gen)];
    }
    return haslo;
}

int main() {
    int dlugosc_hasla = 12;
    std::cout << "Wygenerowane hasło: " << generuj_haslo(dlugosc_hasla) << std::endl;
    return 0;
}
```

- Używamy dystrybucji równomiernej do wyboru indeksu znaku z `zestaw_znakow`.
- Każdy znak w haśle jest losowo wybrany, co zwiększa entropię hasła.

## Zastosowanie różnych dystrybucji

Biblioteka `<random>` oferuje różne dystrybucje, które pozwalają generować liczby losowe zgodnie z określonymi rozkładami statystycznymi.

### Dystrybucja równomierna

Dystrybucja równomierna zapewnia jednakowe prawdopodobieństwo wystąpienia każdej wartości w określonym przedziale.

```c++
#include <iostream>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    std::cout << "Przykładowe liczby z dystrybucji równomiernej:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << dist(gen) << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### Dystrybucja normalna (Gaussa)

Dystrybucja normalna, zwana również rozkładem Gaussa, jest powszechnie stosowana w statystyce i modelowaniu naturalnych zjawisk.

```c++
#include <iostream>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(50, 10); // Średnia 50, odchylenie standardowe 10

    std::cout << "Przykładowe liczby z dystrybucji normalnej:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        double liczba = dist(gen);
        std::cout << liczba << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

- Liczby generowane są wokół średniej 50 z określonym odchyleniem standardowym.
- Rozkład normalny jest symetryczny i opisuje wiele zjawisk naturalnych.

### Dystrybucja Bernoulliego

Dystrybucja Bernoulliego opisuje zdarzenia dwuwartościowe (sukces/porażka) z określonym prawdopodobieństwem sukcesu `p`.

```c++
#include <iostream>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    double p = 0.3; // Prawdopodobieństwo sukcesu
    std::bernoulli_distribution dist(p);

    std::cout << "Przykładowe wyniki z dystrybucji Bernoulliego (p = " << p << "):" << std::endl;
    for (int i = 0; i < 10; ++i) {
        bool wynik = dist(gen);
        std::cout << wynik << " "; // 1 - sukces, 0 - porażka
    }
    std::cout << std::endl;

    return 0;
}
```

- Przydatne w modelowaniu zdarzeń typu "tak/nie".
- Suma wielu zmiennych Bernoulliego prowadzi do rozkładu dwumianowego.

## Zalety i wady różnych metod

### Korzystanie z `std::random`

**Zalety:**

- Generatory takie jak `std::mt19937` (Mersenne Twister) oferują wysoką jakość liczb pseudolosowych z długim okresem powtarzalności.
- Możliwość wyboru spośród wielu predefiniowanych dystrybucji.
- Precyzyjna kontrola nad ziarniem i parametrami generatora.
- Uniwersalność i przenośność kodu.

**Wady:**

- Większa liczba klas i funkcji może być trudniejsza w użyciu dla początkujących.
- Nieco mniejsza wydajność w porównaniu z prostszymi metodami, choć w praktyce różnice są często nieistotne.

### Porównanie z `rand()`

`rand()` to starsza funkcja z biblioteki C, która jest nadal dostępna w C++.

```c++
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(nullptr)); // Inicjalizacja ziarna
    for (int i = 0; i < 10; ++i) {
        std::cout << std::rand() % 100 << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

**Zalety `rand()`:**

- Łatwość użycia dla prostych zastosowań.
- Dostępna we wszystkich kompilatorach zgodnych z C i C++.

**Wady `rand()`:**

- Krótki okres powtarzalności i słaba losowość, co może prowadzić do przewidywalnych sekwencji.
- Ograniczona możliwość konfiguracji generatora i brak wsparcia dla różnych dystrybucji.
- Implementacja `rand()` może się różnić między kompilatorami.
