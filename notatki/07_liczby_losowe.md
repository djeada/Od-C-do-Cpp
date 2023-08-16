## Liczby losowe

Liczby losowe to liczby generowane w sposób, który sprawia wrażenie przypadkowości. Choć są one wytwarzane za pomocą algorytmów (i tym samym są w rzeczywistości "pseudolosowe"), są nieprzewidywalne dla użytkowników. Znajdują zastosowanie w wielu dziedzinach: od symulacji komputerowych, przez loterie, po kryptografię.

### Generowanie liczb losowych w C++

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

### Przykład: Rzut monetą

Przykładowa funkcja `orzel_lub_reszka()` symuluje rzut monetą. Jeśli funkcja zwróci true, oznacza to "orzeł", w przeciwnym razie "reszka".

```c++
bool orzel_lub_reszka() { return (losowa_z_przedzialu(0, 1)); }
```

### Przykład: Rzut kostką

W symulacji rzutu kostką sześciościenną możemy użyć funkcji `losowa_z_przedzialu(1, 6)`.

### Przykład: Generator haseł

Liczby losowe mogą służyć jako podstawa dla generatorów haseł, gdzie każda liczba losowa może być mapowana na określony znak z zestawu dozwolonych znaków.

```c++
std::string generuj_haslo(int dlugosc) {
    const char zestaw_znakow[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+";
    std::string haslo;
    for(int i = 0; i < dlugosc; i++) {
        haslo += zestaw_znakow[losowa_z_przedzialu(0, sizeof(zestaw_znakow) - 2)]; // -2 aby wykluczyć znak końca ciągu
    }
    return haslo;
}
```

W powyższym przykładzie, losujemy znaki z zestawu do tworzenia haseł o zadanej długości.
