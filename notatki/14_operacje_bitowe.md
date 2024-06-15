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

### Maski bitowe
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

#### Sprawdzanie, czy n-ty bit jest ustawiony

Aby sprawdzić, czy n-ty bit jest ustawiony (czyli równy 1) w liczbie, można użyć operatora AND (&) z odpowiednią maską. Maska dla n-tego bitu ma wartość 1 przesuniętą w lewo o n pozycji.

```c
#include <stdio.h>

int main() {
    int value = 0xA5; // wartość 10100101
    int n = 4; // sprawdzamy 4-ty bit (licząc od zera)
    int mask = 1 << n; // maska 00010000
    int result = value & mask; // wynik maskowania
    if (result != 0) {
        printf("Bit %d jest ustawiony.\n", n);
    } else {
        printf("Bit %d nie jest ustawiony.\n", n);
    }
    return 0;
}
```

#### Ustawianie n-tego bitu

Aby ustawić (włączyć) n-ty bit w liczbie, używamy operatora OR (|) z odpowiednią maską.

```c
#include <stdio.h>

int main() {
    int value = 0xA5; // wartość 10100101
    int n = 3; // ustawiamy 3-ci bit (licząc od zera)
    int mask = 1 << n; // maska 00001000
    int result = value | mask; // wynik 10101101
    printf("Wynik po ustawieniu bitu %d: 0x%X\n", n, result);
    return 0;
}
```

#### Zerowanie n-tego bitu

Aby wyzerować (wyłączyć) n-ty bit w liczbie, używamy operatora AND (&) z zanegowaną maską.

```c
#include <stdio.h>

int main() {
    int value = 0xA5; // wartość 10100101
    int n = 5; // zerujemy 5-ty bit (licząc od zera)
    int mask = ~(1 << n); // maska 11011111
    int result = value & mask; // wynik 10000101
    printf("Wynik po wyzerowaniu bitu %d: 0x%X\n", n, result);
    return 0;
}
```

#### Odwrócenie n-tego bitu

Aby sflipować (zmienić na przeciwny) n-ty bit w liczbie, używamy operatora XOR (^) z odpowiednią maską.

```c
#include <stdio.h>

int main() {
    int value = 0xA5; // wartość 10100101
    int n = 2; // flipujemy 2-gi bit (licząc od zera)
    int mask = 1 << n; // maska 00000100
    int result = value ^ mask; // wynik 10100001
    printf("Wynik po sflipowaniu bitu %d: 0x%X\n", n, result);
    return 0;
}
```

### Praktyczne zastosowanie operacji bitowych

Operacje bitowe działają wyłącznie na liczbach całkowitych. Choć operacje bitowe nie są powszechnie używane w codziennym programowaniu, ich znajomość jest ważna, szczególnie w aplikacjach niskopoziomowych i systemowych.

### Praktyczne zastosowanie operacji bitowych

Operacje bitowe działają wyłącznie na liczbach całkowitych. Choć operacje bitowe nie są powszechnie używane w codziennym programowaniu, ich znajomość jest ważna, szczególnie w aplikacjach niskopoziomowych i systemowych.

#### Optymalizacje wydajności
Operacje bitowe mogą być wykorzystywane do optymalizacji wydajności programów poprzez zastąpienie kosztownych operacji arytmetycznych (mnożenie, dzielenie) prostymi operacjami przesunięcia bitowego.

Przykład:

```c
#include <stdio.h>

int main() {
    int value = 16;
    int result_multiplication = value * 2; // Mnożenie
    int result_shift = value << 1; // Przesunięcie bitowe w lewo (równoważne mnożeniu przez 2)

    printf("Wynik mnożenia: %d\n", result_multiplication);
    printf("Wynik przesunięcia: %d\n", result_shift);

    return 0;
}
```

Wynik:

```
Wynik mnożenia: 32
Wynik przesunięcia: 32
```

#### Przesyłanie danych
W komunikacji sprzętowej i sieciach komputerowych operacje bitowe są używane do zarządzania protokołami, formatowaniem danych i kompresją.

Przykład:

```c
#include <stdio.h>

int main() {
    unsigned char data = 0x5A; // Oryginalne dane 01011010
    unsigned char checksum = 0;

    // Obliczanie sumy kontrolnej XOR
    checksum ^= data;

    printf("Dane: 0x%X\n", data);
    printf("Suma kontrolna: 0x%X\n", checksum);

    return 0;
}
```

Wynik:

```
Dane: 0x5A
Suma kontrolna: 0x5A
```

#### Obsługa flag i rejestrów
W systemach wbudowanych operacje bitowe są powszechnie używane do zarządzania flagami i rejestrami.

Przykład:

```c
#include <stdio.h>

int main() {
    unsigned char status_register = 0x00; // Rejestr statusu

    // Ustawienie flagi bitu 2
    status_register |= (1 << 2);

    // Sprawdzenie flagi bitu 2
    if (status_register & (1 << 2)) {
        printf("Flaga bitu 2 jest ustawiona.\n");
    }

    // Wyzerowanie flagi bitu 2
    status_register &= ~(1 << 2);

    // Sprawdzenie flagi bitu 2
    if (!(status_register & (1 << 2))) {
        printf("Flaga bitu 2 jest wyzerowana.\n");
    }

    return 0;
}
```

Wynik:

```
Flaga bitu 2 jest ustawiona.
Flaga bitu 2 jest wyzerowana.
```

#### Algorytmy i struktury danych
Operacje bitowe są również wykorzystywane w różnych algorytmach i strukturach danych, takich jak drzewa bitowe czy tablice haszujące.

Przykład:

```c
#include <stdio.h>

// Funkcja do sprawdzania, czy liczba jest potęgą dwóch
int isPowerOfTwo(unsigned int x) {
    return (x != 0) && ((x & (x - 1)) == 0);
}

int main() {
    unsigned int num = 16;
    if (isPowerOfTwo(num)) {
        printf("%u jest potęgą dwóch.\n", num);
    } else {
        printf("%u nie jest potęgą dwóch.\n", num);
    }

    return 0;
}
```

Wynik:

```
16 jest potęgą dwóch.
```

#### Bezpieczeństwo i kryptografia
Operacje bitowe są podstawą wielu algorytmów kryptograficznych i funkcji haszujących, które są wykorzystywane do zapewnienia bezpieczeństwa danych.

Przykład:

```c
#include <stdio.h>

// Prosta funkcja haszująca XOR
unsigned int simpleHash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash ^= (unsigned int)(*str);
        str++;
    }
    return hash;
}

int main() {
    const char *data = "Hello, World!";
    unsigned int hash = simpleHash(data);

    printf("Hasz dla \"%s\": 0x%X\n", data, hash);

    return 0;
}
```

Wynik:

```
Hasz dla "Hello, World!": 0x4
```

Operacje bitowe są fundamentem wielu zaawansowanych technik programistycznych, od prostych manipulacji bitami po skomplikowane algorytmy kryptograficzne. Ich opanowanie daje programiście potężne narzędzie do efektywnego i precyzyjnego zarządzania danymi na najniższym poziomie.
