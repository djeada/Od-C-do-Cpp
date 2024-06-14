## Liczby losowe

Liczby losowe to liczby generowane w sposób, który sprawia wrażenie przypadkowości. Choć są one wytwarzane za pomocą algorytmów (i tym samym są w rzeczywistości "pseudolosowe"), są nieprzewidywalne dla użytkowników. Znajdują zastosowanie w wielu dziedzinach: od symulacji komputerowych, przez loterie, po kryptografię.

### Generowanie liczb losowych

W C++ do generowania liczb losowych można wykorzystać bibliotekę `<random>`. Poniżej znajduje się funkcja `losowa_z_przedzialu()`, która zwraca losową liczbę całkowitą z podanego zakresu:

```c++
#include <random>

int losowa_z_przedzialu(int start, int end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(start, end);
    return dist(gen);
}
```

### Przykłady zastosowania

#### Rzut monetą

Przykładowa funkcja `orzel_lub_reszka()` symuluje rzut monetą. Jeśli funkcja zwróci `true`, oznacza to "orzeł", w przeciwnym razie "reszka".

```c++
#include <iostream>

bool orzel_lub_reszka() {
    return (losowa_z_przedzialu(0, 1) == 1);
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

#### Rzut kostką

Symulacja rzutu kostką sześciościenną może być zrealizowana przy użyciu funkcji `losowa_z_przedzialu(1, 6)`.

```c++
#include <iostream>

int rzut_kostka() {
    return losowa_z_przedzialu(1, 6);
}

int main() {
    std::cout << "Wynik rzutu kostką: " << rzut_kostka() << std::endl;
    return 0;
}
```

#### Generator haseł

Liczby losowe mogą służyć jako podstawa dla generatorów haseł, gdzie każda liczba losowa może być mapowana na określony znak z zestawu dozwolonych znaków.

```c++
#include <iostream>
#include <string>

std::string generuj_haslo(int dlugosc) {
    const char zestaw_znakow[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+";
    std::string haslo;
    for(int i = 0; i < dlugosc; i++) {
        haslo += zestaw_znakow[losowa_z_przedzialu(0, sizeof(zestaw_znakow) - 2)]; // -2 aby wykluczyć znak końca ciągu
    }
    return haslo;
}

int main() {
    std::cout << "Wygenerowane hasło: " << generuj_haslo(12) << std::endl;
    return 0;
}
```

### Zastosowanie różnych dystrybucji

Biblioteka `<random>` oferuje różne typy dystrybucji do generowania liczb losowych, takie jak:

#### Dystrybucja równomierna

```c++
#include <iostream>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < 10; ++i) {
        std::cout << dist(gen) << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

#### Dystrybucja normalna (Gaussa)

```c++
#include <iostream>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(50, 10); // średnia 50, odchylenie standardowe 10

    for (int i = 0; i < 10; ++i) {
        std::cout << dist(gen) << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

#### Dystrybucja Bernoulliego

```c++
#include <iostream>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist(0.5); // prawdopodobieństwo sukcesu 0.5

    for (int i = 0; i < 10; ++i) {
        std::cout << dist(gen) << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### Zalety i wady różnych metod

#### Korzystanie z `std::random`

**Zalety:**

- Wysoka jakość generowanych liczb losowych.
- Różnorodność dostępnych dystrybucji.
- Wsparcie dla zaawansowanych potrzeb, takich jak kryptografia (przy użyciu odpowiednich generatorów).

**Wady:**

- Złożoność i mniejsza wydajność w porównaniu do prostszych metod (np. `rand()`).

#### Porównanie z `rand()`

Starsza funkcja `rand()` również może być używana do generowania liczb losowych, choć ma pewne ograniczenia.

```c++
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(0));
    for (int i = 0; i < 10; ++i) {
        std::cout << std::rand() % 100 << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

**Zalety `rand()`:**

- Prostota użycia.
- Szeroka dostępność i wsparcie.

**Wady `rand()`:**

- Niższa jakość generowanych liczb losowych.
- Mniejsza elastyczność (brak wsparcia dla różnych dystrybucji).
