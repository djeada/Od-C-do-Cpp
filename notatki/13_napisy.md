## Napisy

Napisy odgrywają kluczową rolę w większości aplikacji programistycznych. Służą do przechowywania tekstu, takiego jak dane wejściowe użytkownika, komunikaty, informacje o błędach i wiele innych. W języku C, napisy są często reprezentowane jako tablice znaków.

### C-string

Tradycyjnie, w języku C napisy (zwane również "C-string") są przedstawiane jako tablice znaków, zakończone specjalnym znakiem o wartości `'\0'` (znany jako "null terminator"). Ten terminator wskazuje koniec napisu.

Istnieje kilka sposobów deklarowania napisów w C:

* `char* napisA = "Ala ma kota";` - niemodyfikowalny wskaźnik do stałego napisu, długość 12 znaków (nie licząc null terminatora).
* `char napisB[] = "Ala ma kota";` - modyfikowalna tablica znaków, również o długości 12 znaków.
* `char napisC[] = {'A', 'l', 'a', ' ', 'm', 'a', ' ', 'k', 'o', 't', 'a', '\0'};` - inny sposób deklarowania napisu podobny do `napisB`.

Do pracy z napisami w C przydatne są następujące biblioteki:

* `<string.h>`:
  * `strlen()` - zwraca długość napisu.
  * `strcpy()` - kopiuje napis z jednej tablicy do drugiej.
  * `strcat()` - dołącza jeden napis do drugiego.
  * `strcmp()` - porównuje dwa napisy.
  
* `<ctype.h>`:
  * `isalpha()` - sprawdza, czy dany znak to litera.
  * `isdigit()` - sprawdza, czy dany znak to cyfra.
  * `toupper()` - zamienia literę na jej wielką wersję.
  * `tolower()` - zamienia literę na jej małą wersję.
  
* `<stdlib.h>`:
  * `atoi()` - konwertuje napis na wartość typu int.
  * `atof()` - konwertuje napis na wartość typu double.

Inicjalizacja i wypisanie napisu:

```cpp
#include <iostream>
using namespace std;

int main() {
    char napis[] = "Witaj, świecie!";
    cout << napis << endl;
    return 0;
}
```

Łączenie dwóch napisów:

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char napis1[] = "Witaj, ";
    char napis2[] = "świecie!";
    char wynik[50];

    strcpy(wynik, napis1);
    strcat(wynik, napis2);
    
    cout << wynik << endl;
    return 0;
}
```

Obliczanie długości napisu:

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char napis[] = "Programowanie";
    int dlugosc = strlen(napis);
    
    cout << "Długość napisu: " << dlugosc << endl;
    return 0;
}
```

Porównywanie dwóch napisów:

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char napis1[] = "ABC";
    char napis2[] = "ABC";
    
    if (strcmp(napis1, napis2) == 0) {
        cout << "Napisy są identyczne." << endl;
    } else {
        cout << "Napisy są różne." << endl;
    }
    return 0;
}
```

Kiedy pracujesz z napisami w języku C, ważne jest, aby zawsze pamiętać o null terminatorze oraz o odpowiedniej alokacji pamięci, zwłaszcza przy operacjach, które mogą zmieniać rozmiar napisu.

### C++ std::string

Chociaż tradycyjne napisy typu C-string mają swoje zastosowania i są ważne z punktu widzenia zrozumienia podstaw języka C, programiści pracujący w C++ mają do dyspozycji znacznie bardziej wszechstronny i elastyczny obiekt do reprezentacji napisów: `std::string`.

Aby utworzyć obiekt string, możemy skorzystać z następujących konstruktorów:

* `string(const char *s)` - tworzy obiekt string na podstawie ciągu znaków
* `string(const string &s)` - tworzy nowy obiekt string na podstawie istniejącego obiektu string.


Klasa `std::string` jest częścią standardowej biblioteki C++ i oferuje wiele funkcji umożliwiających łatwą manipulację napisami. Przykłady:

```cpp
#include <iostream>
#include <string>

int main() {
    std::string napis = "Ala ma kota";
    std::string napis2 = " i psa";

    // Połącz napisy
    napis += napis2;

    // Wypisz połączony napis
    std::cout << napis << std::endl; // "Ala ma kota i psa"

    // Pobierz długość napisu
    std::cout << "Długość napisu: " << napis.length() << std::endl; // 17

    // Zamiana napisu
    napis.replace(4, 2, "nie ma");

    std::cout << napis << std::endl; // "Ala nie ma kota i psa"
}
```

Kluczowe zalety używania std::string nad tradycyjnymi C-stringami to:

- Bezpieczeństwo - Nie musisz martwić się o alokację pamięci czy `null terminator`.
- Elastyczność - Łatwość manipulacji napisami dzięki dostępnym metodom.
- Integracja z C++ - Możliwość użycia napisów w kontenerach standardowej biblioteki, takich jak `std::vector` czy `std::map`.

Jednakże warto pamiętać, że podczas interakcji z kodem w czystym języku C czy z niektórymi bibliotekami, mogą być wymagane tradycyjne C-stringi. Na szczęście std::string oferuje metodę `.c_str()`, która zwraca wskaźnik do tradycyjnego napisu C-string, co ułatwia interakcję między obiema reprezentacjami napisów.
