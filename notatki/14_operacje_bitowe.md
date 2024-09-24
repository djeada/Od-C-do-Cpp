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

### Praktyczne zastosowania operacji bitowych

Operacje bitowe są podstawowymi narzędziami w programowaniu niskopoziomowym, umożliwiającymi bezpośrednią manipulację na poziomie bitów danych binarnych. Działają one wyłącznie na liczbach całkowitych, ponieważ tylko one mają precyzyjnie zdefiniowaną reprezentację bitową. Choć w codziennym programowaniu wysokopoziomowym operacje bitowe nie są tak powszechne, ich znajomość jest niezbędna w wielu dziedzinach, takich jak programowanie systemowe, systemy wbudowane, optymalizacja kodu czy kryptografia.

#### Optymalizacje wydajności

Operacje bitowe są niezwykle efektywne pod względem wydajności, ponieważ są bezpośrednio wspierane przez większość procesorów na poziomie sprzętowym. Można je wykorzystać do optymalizacji kodu poprzez zastępowanie kosztownych operacji arytmetycznych, takich jak mnożenie czy dzielenie, prostymi operacjami bitowymi, takimi jak przesunięcia bitowe.

**Przesunięcia bitowe jako szybkie mnożenie i dzielenie:**

Operacje przesunięcia bitowego w lewo (`<<`) i w prawo (`>>`) są równoważne odpowiednio mnożeniu i dzieleniu przez potęgi dwóch. Przesunięcie o `n` pozycji odpowiada mnożeniu lub dzieleniu przez `2^n`.

**Przykład:**

```c
#include <stdio.h>

int main() {
    int value = 16;
    int result_multiplication = value * 8; // Mnożenie przez 8
    int result_shift = value << 3; // Przesunięcie w lewo o 3 bity (mnożenie przez 2^3 = 8)

    printf("Wynik mnożenia: %d\n", result_multiplication);
    printf("Wynik przesunięcia: %d\n", result_shift);

    return 0;
}
```

**Analiza:**

- `value * 8` wykonuje standardowe mnożenie całkowite.
- `value << 3` przesuwa bity wartości `value` o 3 pozycje w lewo, efektywnie mnożąc przez 8.

**Wynik:**

```
Wynik mnożenia: 128
Wynik przesunięcia: 128
```

**Uwagi dotyczące wydajności:**

- W przeszłości różnica w wydajności między mnożeniem/dzieleniem a przesunięciami bitowymi była znacząca.
- Współczesne kompilatory i procesory często optymalizują te operacje automatycznie, jednak w krytycznych sekcjach kodu ręczne zastosowanie operacji bitowych może nadal przynieść korzyści.

#### Manipulacja maskami bitowymi i flagami

Operacje bitowe są niezbędne w sytuacjach, gdzie trzeba zarządzać pojedynczymi bitami w liczbach całkowitych, na przykład podczas obsługi flag, rejestrów sprzętowych czy protokołów komunikacyjnych.

**Ustawianie, czyszczenie i przełączanie pojedynczych bitów:**

- `value |= (1 << n);` – ustawia bit na pozycji `n`.
- `value &= ~(1 << n);` – zeruje bit na pozycji `n`.
- `value ^= (1 << n);` – zmienia stan bitu na pozycji `n` na przeciwny.

**Przykład:**

```c
#include <stdio.h>

int main() {
    unsigned char status_register = 0x00; // Rejestr statusu początkowo wyzerowany

    // Ustawienie flagi na pozycji bitu 2
    status_register |= (1 << 2);

    printf("Rejestr po ustawieniu bitu 2: 0x%X\n", status_register);

    // Sprawdzenie, czy flaga na pozycji bitu 2 jest ustawiona
    if (status_register & (1 << 2)) {
        printf("Flaga bitu 2 jest ustawiona.\n");
    }

    // Wyzerowanie flagi na pozycji bitu 2
    status_register &= ~(1 << 2);

    printf("Rejestr po wyzerowaniu bitu 2: 0x%X\n", status_register);

    // Sprawdzenie, czy flaga na pozycji bitu 2 jest wyzerowana
    if (!(status_register & (1 << 2))) {
        printf("Flaga bitu 2 jest wyzerowana.\n");
    }

    return 0;
}
```

**Analiza:**

- `status_register` reprezentuje 8-bitowy rejestr statusu.
- Operacje bitowe pozwalają na manipulację poszczególnymi flagami bez wpływu na pozostałe bity.

**Wynik:**

```
Rejestr po ustawieniu bitu 2: 0x4
Flaga bitu 2 jest ustawiona.
Rejestr po wyzerowaniu bitu 2: 0x0
Flaga bitu 2 jest wyzerowana.
```

#### Przesyłanie i formatowanie danych

W komunikacji sprzętowej oraz sieciach komputerowych operacje bitowe są kluczowe przy implementacji protokołów, które często wymagają manipulacji na poziomie pojedynczych bitów, bajtów czy określonych pól w strukturach danych.

**Implementacja sumy kontrolnej:**

Sumy kontrolne służą do wykrywania błędów w transmisji danych. Prostą formą sumy kontrolnej jest operacja XOR na wszystkich bajtach danych.

**Przykład:**

```c
#include <stdio.h>

int main() {
    unsigned char data[] = {0x5A, 0xA5, 0xFF, 0x00}; // Przykładowe dane
    unsigned char checksum = 0;

    // Obliczanie sumy kontrolnej XOR
    for (int i = 0; i < sizeof(data); i++) {
        checksum ^= data[i];
    }

    printf("Suma kontrolna: 0x%X\n", checksum);

    return 0;
}
```

**Analiza:**

- Suma kontrolna jest obliczana poprzez zastosowanie operacji XOR na każdym bajcie danych.
- Operacja XOR ma właściwość, że jeśli ten sam bajt zostanie użyty dwa razy, wynik XOR powróci do poprzedniej wartości, co jest użyteczne w detekcji błędów.

**Wynik:**

```
Suma kontrolna: 0xFF
```

#### Algorytmy i struktury danych

Operacje bitowe są wykorzystywane w optymalizacji algorytmów i struktur danych, zwłaszcza tam, gdzie liczy się wydajność i efektywność pamięciowa.

**Sprawdzanie potęgi dwóch:**

Częstym zadaniem jest sprawdzenie, czy dana liczba jest potęgą dwóch, co można efektywnie zrobić za pomocą operacji bitowych.

**Przykład:**

```c
#include <stdio.h>

// Funkcja do sprawdzania, czy liczba jest potęgą dwóch
int isPowerOfTwo(unsigned int x) {
    return (x != 0) && ((x & (x - 1)) == 0);
}

int main() {
    for (unsigned int num = 0; num <= 17; num++) {
        if (isPowerOfTwo(num)) {
            printf("%u jest potęgą dwóch.\n", num);
        } else {
            printf("%u nie jest potęgą dwóch.\n", num);
        }
    }

    return 0;
}
```

**Analiza:**

- Liczby będące potęgami dwóch mają tylko jeden bit ustawiony na `1` w reprezentacji binarnej.
- Wyrażenie `x & (x - 1)` wyzeruje najmniej znaczący ustawiony bit. Jeśli wynik jest `0`, to znaczy, że liczba miała tylko jeden bit ustawiony, czyli jest potęgą dwóch.

**Wynik:**

```
0 nie jest potęgą dwóch.
1 jest potęgą dwóch.
2 jest potęgą dwóch.
3 nie jest potęgą dwóch.
4 jest potęgą dwóch.
5 nie jest potęgą dwóch.
6 nie jest potęgą dwóch.
7 nie jest potęgą dwóch.
8 jest potęgą dwóch.
9 nie jest potęgą dwóch.
10 nie jest potęgą dwóch.
11 nie jest potęgą dwóch.
12 nie jest potęgą dwóch.
13 nie jest potęgą dwóch.
14 nie jest potęgą dwóch.
15 nie jest potęgą dwóch.
16 jest potęgą dwóch.
17 nie jest potęgą dwóch.
```

#### Bezpieczeństwo i kryptografia

Operacje bitowe są podstawą wielu algorytmów kryptograficznych i funkcji haszujących. Pozwalają na efektywną i kontrolowaną manipulację danymi na poziomie bitów, co jest kluczowe w zapewnianiu bezpieczeństwa danych.

**Implementacja prostego algorytmu haszującego:**

Funkcje haszujące przekształcają dane wejściowe w skrót o stałej długości. Operacje bitowe są często używane do miksowania bitów wejściowych w celu uzyskania równomiernego rozkładu wartości wyjściowych.

**Przykład:**

```c
#include <stdio.h>

// Prosta funkcja haszująca wykorzystująca rotacje bitowe i operacje XOR
unsigned int simpleHash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash ^= (unsigned int)(*str);
        hash = (hash << 5) | (hash >> (27)); // Rotacja w lewo o 5 bitów
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

**Analiza:**

- Funkcja haszująca używa operacji XOR oraz rotacji bitowych do efektywnego miksowania danych wejściowych.
- Rotacja bitowa (`(hash << 5) | (hash >> (27))`) przesuwa bity w taki sposób, że bity wypadające z jednej strony są wprowadzane z drugiej, co zapobiega utracie informacji.

**Wynik:**

```
Hasz dla "Hello, World!": 0xFCDE2E86
```

**Uwagi dotyczące bezpieczeństwa:**

- Proste funkcje haszujące nie są bezpieczne kryptograficznie i nie powinny być używane w aplikacjach wymagających wysokiego poziomu bezpieczeństwa.
- W kryptografii stosuje się zaawansowane funkcje haszujące, takie jak SHA-256, które również intensywnie wykorzystują operacje bitowe.

#### Implementacja zaawansowanych struktur danych

Operacje bitowe pozwalają na tworzenie wydajnych i kompaktowych struktur danych, takich jak:

- **Tablice bitowe (bitset)** umożliwiają przechowywanie dużych zbiorów wartości logicznych w skompresowanej formie.
- **Drzewa trie i radix** wykorzystują bity kluczy do nawigacji po strukturze drzewa, co pozwala na szybkie wyszukiwanie.

**Przykład: Tablica bitowa**

```c
#include <stdio.h>
#include <string.h>

#define MAX 1024

int main() {
    unsigned char bitmap[MAX / 8]; // Tablica bitowa dla 1024 bitów
    memset(bitmap, 0, sizeof(bitmap)); // Inicjalizacja zerami

    // Ustawienie bitu o indeksie 100
    bitmap[100 / 8] |= (1 << (100 % 8));

    // Sprawdzenie, czy bit o indeksie 100 jest ustawiony
    if (bitmap[100 / 8] & (1 << (100 % 8))) {
        printf("Bit 100 jest ustawiony.\n");
    } else {
        printf("Bit 100 nie jest ustawiony.\n");
    }

    return 0;
}
```

**Analiza:**

- Tablica `bitmap` pozwala na przechowywanie 1024 bitów w 128 bajtach.
- Operacje bitowe pozwalają na efektywne zarządzanie poszczególnymi bitami w tablicy.

**Wynik:**

```
Bit 100 jest ustawiony.
```
