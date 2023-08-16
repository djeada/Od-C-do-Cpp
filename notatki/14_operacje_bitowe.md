## Operacje bitowe

Operacje bitowe umożliwiają manipulację poszczególnymi bitami w liczbie. Są one niezbędne w wielu niskopoziomowych zadaniach programistycznych, takich jak prace z rejestrach, komunikacja sprzętowa czy optymalizacje. W językach C i C++ dostępne są następujące operacje bitowe:

### AND
Operacja AND zwraca 1 na określonych bitach, tylko jeśli obie liczby mają wartość 1 na tych samych bitach.

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
Operacja OR zwraca 1 na określonych bitach, jeśli przynajmniej jedna z liczb ma wartość 1 na tych bitach.

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
Operacja XOR zwraca 1 na określonych bitach, jeśli tylko jedna z liczb ma wartość 1 na tych bitach.

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
Operacja NOT inwertuje każdy bit w liczbie.

| Wejście | Wyjście |
|:-------:|:-------:|
|    0    |    1    |
|    1    |    0    |

Przykład: ~5 (0101) staje się (1010). Warto jednak zwrócić uwagę na to, że wynik takiej operacji zależy od systemu liczbowego i rozmiaru typu.

```c
#include <stdio.h>

int main() {
    int a = 5;
    printf("~%d = %d\n", a, ~a);
    return 0;
}

```

### Przesunięcie w lewo
Operacja left shift przesuwa bity w liczbie o określoną liczbę pozycji w lewo, wypełniając prawą stronę zerami.

* Przesunięcie w lewo o 1 bit jest równoważne podzieleniu przez 2.

Przykład: `5 (0101) << 2 = 20 (10100)`

```c
#include <stdio.h>

int main() {
    int a = 5;
    printf("%d >> 2 = %d\n", a, a >> 2);  // Wynik: 1
    return 0;
}
```

### Przesunięcie w prawo
Operacja right shift przesuwa bity w liczbie o określoną liczbę pozycji w prawo. W przypadku liczb nieujemnych lewa strona jest wypełniana zerami, podczas gdy dla liczb ujemnych lewa strona jest wypełniana jedynkami (zachowanie to zależy od implementacji).

* Przesuniecie w prawo o 1 bit jest równoważne przemnożeniu przez 2.

Przykład: `5 (0101) >> 2 = 1 (0001)`

```c
#include <stdio.h>

int main() {
    int a = 5;
    printf("%d >> 2 = %d\n", a, a >> 2);  // Wynik: 1
    return 0;
}
```

Operacje bitowe działają wyłącznie na liczbach całkowitych. Choć operacje bitowe nie są powszechnie używane w codziennym programowaniu, ich znajomość jest ważna, szczególnie w aplikacjach niskopoziomowych i systemowych.
