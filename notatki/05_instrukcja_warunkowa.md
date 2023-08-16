## Instrukcje warunkowe

Instrukcje warunkowe pozwalają na dynamiczną kontrolę przepływu programu w oparciu o spełnienie określonych warunków. Są one nieodłącznym elementem większości języków programowania, umożliwiając tworzenie bardziej złożonych algorytmów.

### Podstawowa instrukcja `if`

Najprostszą instrukcją warunkową jest `if`, która pozwala na wykonywanie pewnego fragmentu kodu tylko wtedy, gdy dany warunek jest spełniony.

```c++
int x = 5;
if (x > 3) {
    std::cout << "x jest większe niż 3" << std::endl;
}
```

### Rozszerzenie if-else

W wielu przypadkach chcemy również określić, co ma się stać, gdy warunek nie jest spełniony. W tym celu używamy konstrukcji `else`.

```c++
if (x > 10) {
    std::cout << "x jest większe niż 10" << std::endl;
} else {
    std::cout << "x nie jest większe niż 10" << std::endl;
}
```

### Instrukcja if-else if-else

Aby sprawdzić kilka różnych warunków jednocześnie, możemy użyć konstrukcji `else if`.

```c++
if (x > 10) {
    std::cout << "x jest większe niż 10" << std::endl;
} else if (x > 5) {
    std::cout << "x jest większe niż 5, ale nie większe niż 10" << std::endl;
} else {
    std::cout << "x nie jest większe niż 5" << std::endl;
}
```

### Operatory warunkowe

W języku C++ istnieje również operator warunkowy `?:`, który pozwala wykonać krótką instrukcję warunkową bez konieczności stosowania pełnej składni if-else.

```c++
int max = (x > y) ? x : y;  // max przyjmie wartość x, jeśli x > y, w przeciwnym razie przyjmie wartość y
```

Instrukcje warunkowe umożliwiają tworzenie bardziej rozbudowanych i złożonych algorytmów, dostosowując zachowanie programu w zależności od spełnienia różnych kryteriów.

### Konstrukcja `switch`

Konstrukcja `switch` jest wysoce użytecznym narzędziem w językach programowania, które pozwala na wielokrotne sprawdzenie wartości zmiennej bez konieczności stosowania skomplikowanych łańcuchów instrukcji `if-else`. 

Kluczowe cechy `switch`:
- Służy do porównywania zmiennej z wieloma wartościami.
- Działa najefektywniej z wartościami dyskretnymi (np. liczby całkowite, znaki).
- Po znalezieniu pasującej wartości (`case`), instrukcje wykonywane są aż do napotkania słowa kluczowego `break` lub końca bloku `switch`.
- Opcja `default` służy jako "wszystkie inne przypadki", jeśli żadne z wartości `case` nie pasuje.

Przykład w C++ z użyciem `switch`:

```c++
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj numer dnia tygodnia (0-6): " << std::endl;
    std::cin >> n;

    switch (n) {
    case 0:
        std::cout << "Poniedziałek." << std::endl;
        break;
    case 1:
        std::cout << "Wtorek." << std::endl;
        break;
    case 2:
        std::cout << "Środa." << std::endl;
        break;
    case 3:
        std::cout << "Czwartek." << std::endl;
        break;
    case 4:
        std::cout << "Piątek." << std::endl;
        break;
    case 5:
        std::cout << "Sobota." << std::endl;
        break;
    case 6:
        std::cout << "Niedziela." << std::endl;
        break;
    default:
        std::cout << "Błąd! Numer dnia powinien być w zakresie 0-6." << std::endl;
    }

    return 0;
}
```

Używanie `switch` jest szczególnie przydatne w sytuacjach, gdzie mamy do czynienia z wieloma konkretnymi wartościami, które wymagają różnych działań. Pomaga to uczynić kod bardziej zorganizowanym i czytelnym w porównaniu do długich łańcuchów instrukcji `if-else`.
