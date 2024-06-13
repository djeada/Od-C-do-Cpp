## Interakcja z konsolą

Interakcja z konsolą jest kluczowym mechanizmem, który pozwala programowi na komunikację z użytkownikiem. Dzięki niej można wyświetlać informacje oraz odbierać dane wprowadzane przez użytkownika. Podczas uruchomienia programu, system operacyjny dostarcza trzy główne strumienie:

- `stdin` - strumień wejściowy, skąd program odczytuje dane,
- `stdout` - strumień wyjściowy, gdzie program wypisuje dane,
- `stderr` - strumień błędów, służący do komunikatów o błędach.

### W języku C

W języku C do interakcji z konsolą używamy funkcji z biblioteki `stdio.h`. Najczęściej są to `printf` (do wypisywania) oraz `scanf` (do odczytu).

#### Specyfikatory formatu dla `printf` i `scanf`

| Specyfikator formatu | Typ danych          | Opis                                        |
|----------------------|---------------------|---------------------------------------------|
| `%d`                 | int                 | Całkowita liczba ze znakiem                 |
| `%u`                 | unsigned int        | Całkowita liczba bez znaku                  |
| `%ld`                | long                | Całkowita liczba długa ze znakiem           |
| `%lu`                | unsigned long       | Całkowita liczba długa bez znaku            |
| `%lld`               | long long           | Całkowita liczba długa długa ze znakiem     |
| `%llu`               | unsigned long long  | Całkowita liczba długa długa bez znaku      |
| `%f`                 | float               | Liczba zmiennoprzecinkowa                   |
| `%lf`                | double              | Liczba zmiennoprzecinkowa podwójnej precyzji|
| `%Lf`                | long double         | Liczba zmiennoprzecinkowa z długą precyzją  |
| `%c`                 | char                | Znak                                        |
| `%s`                 | char*               | Łańcuch znaków                              |
| `%p`                 | void*               | Adres wskaźnika                             |

### Funkcje wejścia/wyjścia

#### `printf`

Funkcja `printf` służy do wyświetlania danych na standardowym wyjściu. Może ona przyjmować różne specyfikatory formatu, które określają sposób wyświetlania danych. Przykłady użycia:

```c
#include <stdio.h>

int main() {
    int liczba = 10;
    float liczbaZmiennoprzecinkowa = 3.14;
    char znak = 'A';
    char lancuch[] = "Hello, world!";

    printf("Liczba całkowita: %d\n", liczba);
    printf("Liczba zmiennoprzecinkowa: %.2f\n", liczbaZmiennoprzecinkowa);
    printf("Znak: %c\n", znak);
    printf("Łańcuch znaków: %s\n", lancuch);

    return 0;
}
```

#### `scanf`

Funkcja `scanf` służy do odczytywania danych ze standardowego wejścia. Także używa specyfikatorów formatu do określania typu danych, które mają być odczytane. Przykład użycia:

```c
#include <stdio.h>

int main() {
    int liczba;
    float liczbaZmiennoprzecinkowa;
    char znak;
    char lancuch[100];

    printf("Podaj liczbę całkowitą: ");
    scanf("%d", &liczba);

    printf("Podaj liczbę zmiennoprzecinkową: ");
    scanf("%f", &liczbaZmiennoprzecinkowa);

    printf("Podaj znak: ");
    scanf(" %c", &znak); // Spacja przed %c jest potrzebna, aby zignorować białe znaki

    printf("Podaj łańcuch znaków: ");
    scanf("%s", lancuch);

    printf("Podano liczbę całkowitą: %d\n", liczba);
    printf("Podano liczbę zmiennoprzecinkową: %.2f\n", liczbaZmiennoprzecinkowa);
    printf("Podano znak: %c\n", znak);
    printf("Podano łańcuch znaków: %s\n", lancuch);

    return 0;
}
```

### Obsługa błędów

Podczas pracy z wejściem i wyjściem warto obsługiwać błędy, które mogą wystąpić, na przykład w przypadku niepoprawnego formatu danych. Przykład obsługi błędów w C:

```c
#include <stdio.h>

int main() {
    int liczba;

    printf("Podaj liczbę: ");
    if (scanf("%d", &liczba) != 1) {
        fprintf(stderr, "Błąd: nieprawidłowy format liczby.\n");
        return 1;
    }

    printf("Podałeś liczbę: %d\n", liczba);
    return 0;
}
```

### Przykład zaawansowanego programu

Poniżej znajduje się bardziej zaawansowany przykład, który ilustruje użycie różnych typów danych oraz bardziej rozbudowanej logiki:

```c
#include <stdio.h>
#include <string.h>

int main() {
    char imie[50];
    int wiek;
    float wzrost;
    char kraj[50];

    printf("Podaj swoje imię: ");
```

### W języku C++

W języku C++ do komunikacji z konsolą używamy biblioteki `iostream`. Dostarcza ona obiekty takie jak `cin`, `cout`, `cerr`, `clog` oraz funkcje takie jak `getline`.

#### Podstawowe operacje

- `cout` z operatorem `<<` służy do wypisywania na standardowe wyjście.
- `cin` z operatorem `>>` wczytuje pojedynczą wartość ze standardowego wejścia.
- `getline(cin, string)` pozwala wczytać cały wiersz tekstu, łącznie ze spacjami.

#### Przykład podstawowy

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    string imie;
    int wiek;
    double wzrost;

    cout << "Podaj swoje imię: ";
    getline(cin, imie);

    cout << "Podaj swój wiek: ";
    cin >> wiek;

    cout << "Podaj swój wzrost (w metrach): ";
    cin >> wzrost;

    cout << "Twoje imię to " << imie << ", masz " << wiek << " lat i masz " << wzrost << " metra wzrostu." << endl;

    return 0;
}
```

W powyższym przykładzie program prosi użytkownika o podanie imienia, wieku i wzrostu, a następnie wyświetla te informacje. Dzięki `getline(cin, imie)`, możemy wczytać pełne imię wraz ze spacjami.

### Obsługa błędów

Podczas pracy z wejściem i wyjściem warto również obsługiwać błędy, które mogą wystąpić, na przykład w przypadku niepoprawnego formatu danych. Poniżej znajduje się przykład obsługi błędów w C++:

```cpp
#include <iostream>

using namespace std;

int main() {
    int liczba;

    cout << "Podaj liczbę: ";
    cin >> liczba;

    if (cin.fail()) {
        cerr << "Błąd: nieprawidłowy format liczby." << endl;
        return 1;
    }

    cout << "Podałeś liczbę: " << liczba << endl;
    return 0;
}
```

W tym przykładzie, jeśli użytkownik poda nieprawidłowy format danych, program wyświetli komunikat o błędzie i zakończy działanie.

### Użycie manipulacji wejścia/wyjścia

Biblioteka `iomanip` dostarcza manipulatory, które pozwalają formatować wyjście:

```cpp
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double liczba = 123.456789;

    cout << "Domyślne wyjście: " << liczba << endl;
    cout << "Wyjście zaokrąglone do 2 miejsc po przecinku: " << fixed << setprecision(2) << liczba << endl;
    cout << "Wyjście w formacie naukowym: " << scientific << liczba << endl;

    return 0;
}
```

### Obsługa wejścia z buforowaniem

Można również używać `cin.sync()` oraz `cin.ignore()`, aby radzić sobie z problemami buforowania wejścia:

```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    string imie;
    int wiek;

    cout << "Podaj swój wiek: ";
    cin >> wiek;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoruje pozostałe znaki w buforze

    cout << "Podaj swoje imię: ";
    getline(cin, imie);

    cout << "Twoje imię to " << imie << ", masz " << wiek << " lat." << endl;

    return 0;
}
```


### Kolorowanie tekstu w konsoli (C/C++)

Kolorowanie tekstu w konsoli można zrealizować za pomocą kodów ANSI (na systemach uniksowych) lub funkcji konsolowych systemu Windows.

#### Przykład użycia kodów ANSI (Linux/Unix)

```c++
#include <iostream>

using namespace std;

int main() {
    cout << "\033[1;31m"; // Ustawienie koloru na czerwony
    cout << "Czerwony tekst" << endl;
    cout << "\033[0m";    // Resetowanie koloru

    return 0;
}
```

#### Przykład kolorowania w systemie Windows

```c++
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    cout << "Czerwony tekst" << endl;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "Domyślny kolor" << endl;

    return 0;
}
```

W powyższych przykładach pokazano, jak zmieniać kolor tekstu w konsoli, co może być użyteczne do wyróżniania komunikatów lub interfejsów użytkownika.
