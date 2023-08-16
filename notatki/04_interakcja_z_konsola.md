## Interakcja z konsolą

Interakcja z konsolą jest kluczowym mechanizmem, który pozwala programowi na komunikację z użytkownikiem. Dzięki niej można wyświetlać informacje oraz odbierać dane wprowadzane przez użytkownika.

Podczas uruchomienia programu, system operacyjny dostarcza trzy główne strumienie:
- `stdin` - strumień wejściowy, skąd program odczytuje dane,
- `stdout` - strumień wyjściowy, gdzie program wypisuje dane,
- `stderr` - strumień błędów, służący do komunikatów o błędach.

### W języku C

W C do interakcji z konsolą używamy funkcji z biblioteki `stdio.h`. Najczęściej są to `printf` (do wypisywania) oraz `scanf` (do odczytu).

```c
#include <stdio.h>

int main() {
  int liczba;
  printf("Podaj pojedynczą liczbę: ");
  scanf("%d", &liczba);

  printf("Podales liczbe: %d\n", liczba);  

  return 0;
}
```

Tabela specyfikatorów formatu dla `printf` i `scanf`:

| Specyfikator formatu | Typ danych      | Opis                                       |
| -------------------- | --------------- | ------------------------------------------ |
| `%d`                 | int             | Całkowita liczba ze znakiem                |
| `%u`                 | unsigned int    | Całkowita liczba bez znaku                 |
| `%ld`                | long            | Całkowita liczba długa ze znakiem          |
| `%lu`                | unsigned long   | Całkowita liczba długa bez znaku           |
| `%lld`               | long long       | Całkowita liczba długa długa ze znakiem    |
| `%llu`               | unsigned long long | Całkowita liczba długa długa bez znaku  |
| `%f`                 | float           | Liczba zmiennoprzecinkowa                  |
| `%lf`                | double          | Liczba zmiennoprzecinkowa podwójnej precyzji |
| `%Lf`                | long double     | Liczba zmiennoprzecinkowa z długą precyzją |
| `%c`                 | char            | Znak                                       |
| `%s`                 | char*           | Łańcuch znaków                             |
| `%p`                 | void*           | Adres wskaźnika                            |

### W języku C++

W C++ do komunikacji z konsolą używamy biblioteki iostream. Dostarcza ona obiekty takie jak cin, cout oraz funkcje jak getline.

- `cout` z operatorem `<<` służy do wypisywania na standardowe wyjście.
- `cin` z operatorem `>>` wczytuje pojedynczą wartość ze standardowego wejścia.
- `getline(cin, string)` pozwala wczytać cały wiersz tekstu, łącznie ze spacjami.

```c++
#include <iostream>
#include <string>

using namespace std;

int main() {
  int liczba;
  cout << "Podaj pojedyncza liczbe: ";
  cin >> liczba;
  cout << "Podales liczbe: " << liczba << endl;

  cin.ignore(); // wyczyszczenie bufora po wczytaniu liczby

  string zdanie;
  cout << "Podaj pelne zdanie: ";
  getline(cin, zdanie);
  cout << "Podales zdanie: " << zdanie << endl;

  return 0;
}
```

Dzięki tym narzędziom można tworzyć interaktywne programy, które są w stanie komunikować się z użytkownikiem w czasie rzeczywistym.
