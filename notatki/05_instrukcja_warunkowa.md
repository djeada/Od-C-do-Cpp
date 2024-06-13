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

### Złożone warunki logiczne

Możemy łączyć wiele warunków w jednej instrukcji `if` za pomocą operatorów logicznych `&&` (AND) oraz `||` (OR).

```c++
if (x > 5 && x < 10) {
    std::cout << "x jest większe niż 5 i mniejsze niż 10" << std::endl;
}

if (x < 5 || x > 10) {
    std::cout << "x jest mniejsze niż 5 lub większe niż 10" << std::endl;
}
```

### Operator warunkowy (trójargumentowy)

W języku C++ istnieje również operator warunkowy `?:`, który pozwala wykonać krótką instrukcję warunkową bez konieczności stosowania pełnej składni if-else.

```c++
int max = (x > y) ? x : y;  // max przyjmie wartość x, jeśli x > y, w przeciwnym razie przyjmie wartość y
```

### Instrukcja warunkowa z wartością logiczną

W języku C++ możemy również używać wartości logicznych jako warunków w instrukcjach `if`.

```c++
bool warunek = true;
if (warunek) {
    std::cout << "Warunek jest prawdziwy" << std::endl;
} else {
    std::cout << "Warunek jest fałszywy" << std::endl;
}
```

### Na co uważać przy używaniu instrukcji warunkowych

#### Kolejność ewaluacji warunków

Kolejność ewaluacji warunków w instrukcjach `if`, `else if`, `else` ma znaczenie. Program przestaje sprawdzać warunki po znalezieniu pierwszego, który jest spełniony.

```c++
int x = 10;

if (x > 5) {
    std::cout << "x jest większe niż 5" << std::endl;
} else if (x > 8) {
    std::cout << "x jest większe niż 8" << std::endl;  // Ten blok nie zostanie wykonany, mimo że warunek jest prawdziwy.
}
```

#### Ewaluacja wartości logicznych

Wartości logiczne w C++ są ewaluowane na podstawie wartości liczbowych:
- `0` jest interpretowane jako `false`.
- Każda inna liczba jest interpretowana jako `true`.

```c++
int liczba = 0;

if (liczba) {
    std::cout << "To jest prawdziwe" << std::endl;
} else {
    std::cout << "To jest fałszywe" << std::endl;  // Ten blok zostanie wykonany.
}
```

#### Potencjalne pułapki przy użyciu `==` i `=`

Pomyłki przy użyciu operatora przypisania `=` zamiast operatora porównania `==` mogą prowadzić do trudnych do wykrycia błędów.

```c++
int x = 5;

// Błąd: przypisanie zamiast porównania
if (x = 10) {
    std::cout << "x jest równe 10" << std::endl;  // Ten blok zawsze zostanie wykonany, ponieważ x = 10 jest prawdziwe.
}

// Poprawne porównanie
if (x == 10) {
    std::cout << "x jest równe 10" << std::endl;
}
```

#### Porównywanie zmiennych zmiennoprzecinkowych

Porównywanie zmiennych zmiennoprzecinkowych (`float`, `double`) bezpośrednio za pomocą operatora `==` może prowadzić do nieoczekiwanych rezultatów z powodu ograniczeń precyzji zmiennoprzecinkowej.

```c++
double a = 0.1;
double b = 0.1 + 0.1 + 0.1 - 0.3;

if (a == b) {
    std::cout << "a jest równe b" << std::endl;  // Ten blok może nie zostać wykonany, mimo że a i b są teoretycznie równe.
} else {
    std::cout << "a nie jest równe b" << std::endl;
}

// Poprawne porównanie zmiennych zmiennoprzecinkowych
const double epsilon = 1e-9;
if (fabs(a - b) < epsilon) {
    std::cout << "a jest równe b (z tolerancją)" << std::endl;
}
```

#### Efekty uboczne w warunkach

Unikaj umieszczania wyrażeń z efektami ubocznymi w warunkach, aby uniknąć trudnych do znalezienia błędów.

```c++
int x = 5;
if (x++ > 5) {
    std::cout << "x jest większe niż 5" << std::endl;  // Efekt uboczny: wartość x jest zwiększana.
}
std::cout << "x = " << x << std::endl;  // x = 6
```

#### Złożone warunki logiczne

Złożone warunki logiczne mogą być trudne do odczytania i zrozumienia. Rozważ ich rozbicie na mniejsze, bardziej czytelne fragmenty.

```c++
int a = 5, b = 10, c = 15;

// Złożony warunek logiczny
if (a > 0 && b > 0 && c > 0 && (a + b > c) && (a + c > b) && (b + c > a)) {
    std::cout << "Wszystkie liczby są dodatnie i spełniają nierówności trójkąta" << std::endl;
}

// Bardziej czytelne
bool wszystkieDodatnie = (a > 0) && (b > 0) && (c > 0);
bool spelniaNierownosciTrojkata = (a + b > c) && (a + c > b) && (b + c > a);

if (wszystkieDodatnie && spelniaNierownosciTrojkata) {
    std::cout << "Wszystkie liczby są dodatnie i spełniają nierówności trójkąta" << std::endl;
}
```

#### Unikanie powtórzeń kodu

Często w blokach `if` i `else` powtarza się ten sam kod. Warto wyekstrahować wspólny kod poza instrukcje warunkowe.

```c++
int x = 5;

if (x > 10) {
    std::cout << "x jest większe niż 10" << std::endl;
    // wspólny kod
    std::cout << "To jest wspólny kod" << std::endl;
} else {
    std::cout << "x nie jest większe niż 10" << std::endl;
    // wspólny kod
    std::cout << "To jest wspólny kod" << std::endl;
}

// Refaktoryzacja
if (x > 10) {
    std::cout << "x jest większe niż 10" << std::endl;
} else {
    std::cout << "x nie jest większe niż 10" << std::endl;
}
// wspólny kod
std::cout << "To jest wspólny kod" << std::endl;
```

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
