## Operacje bitowe

Operacje bitowe umożliwiają manipulację poszczególnymi bitami w liczbie. Są one niezbędne w wielu niskopoziomowych zadaniach programistycznych, takich jak prace z rejestrami, komunikacja sprzętowa czy optymalizacje. W językach C i C++ dostępne są następujące operacje bitowe:

### AND
Operacja AND (koniunkcja) zwraca 1 na określonych bitach, tylko jeśli obie liczby mają wartość 1 na tych samych bitach. Jest to operacja logiczna, która działa na poziomie bitowym.

| Wejście 1 | Wejście 2 | Wyjście |
|-----------|-----------|---------|
| 0         | 0         | 0       |
| 0         | 1         | 0       |
| 1         | 0         | 0       |
| 1         | 1         | 1       |

Przykład: `5 (0101) & 3 (0011) = 1 (0001)`

```c
#include <stdio.h>

int main() {
    int a = 5; // 0101 w binarnym
    int b = 3; // 0011 w binarnym
    printf("%d & %d = %d\n", a, b, a & b);  // Wynik: 1
    return 0;
}
```

### OR
Operacja OR (alternatywa) zwraca 1 na określonych bitach, jeśli przynajmniej jedna z liczb ma wartość 1 na tych bitach. Jest to operacja logiczna, która działa na poziomie bitowym.

| Wejście 1 | Wejście 2 | Wyjście |
|-----------|-----------|---------|
| 0         | 0         | 0       |
| 0         | 1         | 1       |
| 1         | 0         | 1       |
| 1         | 1         | 1       |

Przykład: `5 (0101) | 3 (0011) = 7 (0111)`

```c
#include <stdio.h>

int main() {
    int a = 5;
    int b = 3;
    printf("%d | %d = %d\n", a, b, a | b);  // Wynik: 7
    return 0;
}
```

### XOR
Operacja XOR (alternatywa wyłączająca) zwraca 1 na określonych bitach, jeśli tylko jedna z liczb ma wartość 1 na tych bitach.

| Wejście 1 | Wejście 2 | Wyjście |
|-----------|-----------|---------|
| 0         | 0         | 0       |
| 0         | 1         | 1       |
| 1         | 0         | 1       |
| 1         | 1         | 0       |

Przykład: `5 (0101) ^ 3 (0011) = 6 (0110)`

```c
#include <stdio.h>

int main() {
    int a = 5;
    int b = 3;
    printf("%d ^ %d = %d\n", a, b, a ^ b);  // Wynik: 6
    return 0;
}
```

### NOT
Operacja NOT (negacja) inwertuje każdy bit w liczbie. Działa jako negacja bitowa.

| Wejście | Wyjście |
|:-------:|:-------:|
|    0    |    1    |
|    1    |    0    |

Przykład: `~5 (0101) staje się (1010)`. Warto jednak zwrócić uwagę na to, że wynik takiej operacji zależy od systemu liczbowego i rozmiaru typu.

```c
#include <stdio.h>

int main() {
    int a = 5;
    printf("~%d = %d\n", a, ~a);
    return 0;
}
```

### Przesunięcie w lewo
Operacja left shift (przesunięcie w lewo) przesuwa bity w liczbie o określoną liczbę pozycji w lewo, wypełniając prawą stronę zerami. Każde przesunięcie w lewo o 1 bit jest równoważne pomnożeniu liczby przez 2.

Przykład: `5 (0101) << 2 = 20 (10100)`

```c
#include <stdio.h>

int main() {
    int a = 5;
    printf("%d << 2 = %d\n", a, a << 2);  // Wynik: 20
    return 0;
}
```

### Przesunięcie w prawo
Operacja right shift (przesunięcie w prawo) przesuwa bity w liczbie o określoną liczbę pozycji w prawo. W przypadku liczb nieujemnych lewa strona jest wypełniana zerami, podczas gdy dla liczb ujemnych lewa strona jest wypełniana jedynkami (zachowanie to zależy od implementacji). Każde przesunięcie w prawo o 1 bit jest równoważne podzieleniu liczby przez 2.

Przykład: `5 (0101) >> 2 = 1 (0001)`

```c
#include <stdio.h>

int main() {
    int a = 5;
    printf("%d >> 2 = %d\n", a, a >> 2);  // Wynik: 1
    return 0;
}
```

### Praktyczne zastosowanie operacji bitowych

Operacje bitowe działają wyłącznie na liczbach całkowitych. Choć operacje bitowe nie są powszechnie używane w codziennym programowaniu, ich znajomość jest ważna, szczególnie w aplikacjach niskopoziomowych i systemowych.

#### Maski bitowe
Maski bitowe to technika wykorzystywana do izolowania, ustawiania lub zerowania określonych bitów w liczbie. Na przykład:

```c
#include <stdio.h>

int main() {
    int mask = 0xF0; // maska 11110000
    int value = 0xA5; // wartość 10100101
    int result = value & mask; // wynik 10100000
    printf("Wynik maski bitowej: 0x%X\n", result);  // Wynik: 0xA0
    return 0;
}
```

#### Optymalizacje wydajności
Operacje bitowe mogą być wykorzystywane do optymalizacji wydajności programów poprzez zastąpienie kosztownych operacji arytmetycznych (mnożenie, dzielenie) prostymi operacjami przesunięcia bitowego.

#### Przesyłanie danych
W komunikacji sprzętowej i sieciach komputerowych operacje bitowe są używane do zarządzania protokołami, formatowaniem danych i kompresją.

#### Przykład z maskowaniem bitowym
Załóżmy, że chcemy sprawdzić, czy trzeci bit (licząc od 0) liczby jest ustawiony na 1:

```c
#include <stdio.h>

int main() {
    int value = 0b10101010; // liczba 170 w systemie dziesiętnym
    int mask = 1 << 3; // maska ustawiająca trzeci bit
    if (value & mask) {
        printf("Trzeci bit jest ustawiony.\n");
    } else {
        printf("Trzeci bit nie jest ustawiony.\n");
    }
    return 0;
}
```

Operacje bitowe są fundamentem wielu zaawansowanych technik programistycznych, od prostych manipulacji bitami po skomplikowane algorytmy kryptograficzne. Ich opanowanie daje programiście potężne narzędzie do efektywnego i precyzyjnego zarządzania danymi na najniższym poziomie.
