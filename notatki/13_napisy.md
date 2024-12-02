## Napisy w języku C i C++

Napisy są fundamentalnym elementem wielu aplikacji programistycznych, służąc do przechowywania i manipulacji tekstem, takim jak dane wejściowe użytkownika, komunikaty systemowe, informacje o błędach i wiele innych. W językach C i C++, napisy są reprezentowane na różne sposoby, co wynika z ewolucji tych języków oraz dążenia do zwiększenia bezpieczeństwa i łatwości użycia.

### Napisy w języku C (C-string)

W języku C napisy są reprezentowane jako tablice znaków typu `char`, zakończone specjalnym znakiem `'\0'`, znanym jako znak null (null terminator). Ten znak wskazuje koniec napisu i pozwala funkcjom bibliotecznym na określenie długości napisu w czasie wykonania.

#### Deklaracja i inicjalizacja napisów w C

Istnieje kilka sposobów deklarowania i inicjalizacji napisów w C:

I. **Wskaźnik do stałego łańcucha znaków:**

```c
const char *napisA = "Ala ma kota";
```

W tym przypadku `napisA` jest wskaźnikiem do stałego łańcucha znaków przechowywanego w pamięci tylko do odczytu (zazwyczaj w segmencie tekstowym programu). Próba modyfikacji tego napisu prowadzi do niezdefiniowanego zachowania.

II. **Tablica znaków z inicjalizacją literałem:**

```c
char napisB[] = "Ala ma kota";
```

Tutaj `napisB` jest tablicą znaków, która jest kopią literału napisu. Ta tablica może być modyfikowana, ponieważ jest przechowywana w pamięci dostępnej do zapisu (zazwyczaj na stosie lub w pamięci dynamicznej).

III. **Tablica znaków z inicjalizacją listą znaków:**

```c
char napisC[] = {'A', 'l', 'a', ' ', 'm', 'a', ' ', 'k', 'o', 't', 'a', '\0'};
```

Ten sposób jest równoważny poprzedniemu, ale wymaga jawnego dodania znaku null na końcu tablicy.

#### Znaczenie znaku null

Znak null `'\0'` jest kluczowy w reprezentacji napisów w C. Funkcje biblioteczne operujące na napisach zakładają, że napisy są zakończone tym znakiem. Brak znaku null może prowadzić do błędów, takich jak odczyt poza granicami tablicy (buffer overrun), co może skutkować naruszeniem ochrony pamięci i awarią programu.

#### Operacje na napisach w C

Język C dostarcza bogaty zestaw funkcji w standardowych bibliotekach do manipulacji napisami. Kluczowe biblioteki to `<string.h>`, `<ctype.h>` i `<stdlib.h>`.

##### Biblioteka `<string.h>`

Funkcje w tej bibliotece służą do manipulacji i porównywania napisów:

| Funkcja                            | Opis                                                                 |
|------------------------------------|----------------------------------------------------------------------|
| `size_t strlen(const char *s);`    | Zwraca długość napisu `s`, czyli liczbę znaków przed znakiem null.   |
| `char *strcpy(char *dest, const char *src);` | Kopiuje napis `src` do bufora `dest`. Uwaga: `dest` musi mieć wystarczający rozmiar, aby pomieścić `src`. |
| `char *strncpy(char *dest, const char *src, size_t n);` | Kopiuje maksymalnie `n` znaków z `src` do `dest`.                       |
| `char *strcat(char *dest, const char *src);` | Dołącza napis `src` do końca `dest`. `dest` musi mieć wystarczający rozmiar. |
| `char *strncat(char *dest, const char *src, size_t n);` | Dołącza maksymalnie `n` znaków z `src` do `dest`.                       |
| `int strcmp(const char *s1, const char *s2);` | Porównuje napisy `s1` i `s2`. Zwraca wartość ujemną, zero lub dodatnią w zależności od wyniku porównania. |
| `int strncmp(const char *s1, const char *s2, size_t n);` | Porównuje maksymalnie `n` znaków z `s1` i `s2`.                        |
| `char *strchr(const char *s, int c);` | Wyszukuje pierwsze wystąpienie znaku `c` w napisie `s`.               |
| `char *strrchr(const char *s, int c);` | Wyszukuje ostatnie wystąpienie znaku `c` w napisie `s`.               |
| `char *strstr(const char *haystack, const char *needle);` | Wyszukuje podciąg `needle` w napisie `haystack`.                       |

**Uwaga dotycząca bezpieczeństwa:** Funkcje takie jak `strcpy` i `strcat` są podatne na błędy przepełnienia bufora (buffer overflow) i nie powinny być używane w nowym kodzie. Bezpieczniejsze alternatywy to `strncpy` i `strncat`, jednak one również mają swoje ograniczenia. W praktyce zaleca się korzystanie z funkcji takich jak `strlcpy` i `strlcat` (jeśli są dostępne) lub funkcji specyficznych dla danego systemu operacyjnego.

##### Biblioteka `<ctype.h>`

Ta biblioteka zawiera funkcje do klasyfikacji i manipulacji znakami:

| Funkcja               | Opis                                                                                     |
|-----------------------|------------------------------------------------------------------------------------------|
| `int isalpha(int c);` | Sprawdza, czy znak `c` jest literą alfabetu.                                              |
| `int isdigit(int c);` | Sprawdza, czy znak `c` jest cyfrą.                                                        |
| `int isalnum(int c);` | Sprawdza, czy znak `c` jest alfanumeryczny.                                               |
| `int isspace(int c);` | Sprawdza, czy znak `c` jest znakiem białym (spacja, tabulacja, nowa linia itp.).           |
| `int toupper(int c);` | Konwertuje znak `c` do wielkiej litery, jeśli to możliwe.                                 |
| `int tolower(int c);` | Konwertuje znak `c` do małej litery, jeśli to możliwe.                                   |

##### Biblioteka `<stdlib.h>`

Zawiera funkcje do konwersji napisów na wartości liczbowe i odwrotnie:

| Funkcja                                            | Opis                                                                                                     |
|----------------------------------------------------|----------------------------------------------------------------------------------------------------------|
| `int atoi(const char *nptr);`                     | Konwertuje napis `nptr` na wartość `int`.                                                               |
| `long int strtol(const char *nptr, char **endptr, int base);` | Konwertuje napis `nptr` na wartość `long int`, z możliwością określenia podstawy systemu liczbowego. |
| `double atof(const char *nptr);`                  | Konwertuje napis `nptr` na wartość `double`.                                                            |
| `double strtod(const char *nptr, char **endptr);` | Konwertuje napis `nptr` na wartość `double`, zwracając wskaźnik do pierwszego znaku po liczbie w `*endptr`. |
| `char *strtok(char *str, const char *delim);`     | Dzieli napis `str` na tokeny, używając separatorów zdefiniowanych w `delim`.                            |

**Uwaga dotycząca bezpieczeństwa:** Funkcja `atoi` nie obsługuje błędów i nie jest bezpieczna. Zaleca się użycie `strtol` lub `strtod`, które pozwalają na wykrycie błędów konwersji.

#### Przykłady użycia napisów w C

**Inicjalizacja i wypisanie napisu:**

```c
#include <stdio.h>

int main() {
    char napis[] = "Witaj, świecie!";
    printf("%s\n", napis);
    return 0;
}
```

**Łączenie dwóch napisów:**

```c
#include <stdio.h>
#include <string.h>

int main() {
    char napis1[50] = "Witaj, ";
    char napis2[] = "świecie!";

    strcat(napis1, napis2);

    printf("%s\n", napis1); // "Witaj, świecie!"
    return 0;
}
```

**Obliczanie długości napisu:**

```c
#include <stdio.h>
#include <string.h>

int main() {
    char napis[] = "Programowanie";
    size_t dlugosc = strlen(napis);

    printf("Długość napisu: %zu\n", dlugosc);
    return 0;
}
```

**Porównywanie dwóch napisów:**

```c
#include <stdio.h>
#include <string.h>

int main() {
    char napis1[] = "ABC";
    char napis2[] = "ABC";

    if (strcmp(napis1, napis2) == 0) {
        printf("Napisy są identyczne.\n");
    } else {
        printf("Napisy są różne.\n");
    }
    return 0;
}
```

#### Zarządzanie pamięcią i bezpieczeństwo

Podczas pracy z napisami w C należy zwrócić szczególną uwagę na alokację pamięci i zarządzanie buforami. Błędy takie jak przepełnienie bufora mogą prowadzić do poważnych luk bezpieczeństwa, w tym możliwości wykonania złośliwego kodu.

Aby uniknąć takich problemów:

- **Zawsze sprawdzaj długości napisów** przed kopiowaniem lub łączeniem, aby zapobiec błędom przepełnienia bufora i zapewnić bezpieczeństwo pamięci.
- **Używaj bezpiecznych funkcji** lub bibliotek, które automatycznie zarządzają pamięcią, aby uniknąć ręcznego zarządzania wskaźnikami i potencjalnych błędów.
- **Rozważ użycie dynamicznej alokacji pamięci**, jeśli rozmiar napisu nie jest znany z góry, co pozwala na bardziej elastyczne zarządzanie pamięcią w programie.
  
### Napisy w języku C++ (`std::string`)

Chociaż język C++ jest zgodny z C i pozwala na użycie tradycyjnych C-stringów, oferuje również bardziej zaawansowaną i bezpieczniejszą klasę `std::string` do reprezentacji napisów. Klasa ta jest częścią standardowej biblioteki C++ i znajduje się w nagłówku `<string>`.

#### Zalety użycia `std::string`

- **`std::string` automatycznie zarządza alokacją i dealokacją pamięci**, co zmniejsza ryzyko wystąpienia błędów, takich jak wycieki pamięci, dzięki czemu program jest bardziej bezpieczny i stabilny.
- **Metody klasy `std::string` zazwyczaj sprawdzają granice buforów**, co chroni przed błędami przepełnienia bufora, zwiększając bezpieczeństwo operacji na napisach.
- **Klasa `std::string` oferuje bogatą funkcjonalność**, w tym metody do takich operacji jak konkatenacja, wyszukiwanie, czy zamiana podłańcuchów, co upraszcza manipulację tekstem.
- **`std::string` jest dobrze zintegrowany z innymi komponentami STL**, co pozwala na jego efektywne użycie z kontenerami i algorytmami biblioteki standardowej C++.

#### Tworzenie i inicjalizacja `std::string`

```cpp
#include <string>

std::string napis1; // Pusty napis
std::string napis2("Ala ma kota"); // Inicjalizacja napisem
std::string napis3(napis2); // Kopia istniejącego napisu
```

#### Podstawowe operacje na `std::string`

I. **Dodawanie napisów:**

```cpp
std::string napis1 = "Ala";
std::string napis2 = " ma kota";
std::string wynik = napis1 + napis2; // "Ala ma kota"
```

II. **Dostęp do znaków:**

```cpp
char znak = napis1[0]; // 'A'
napis1[0] = 'E'; // napis1 teraz to "Ela"
```

**Uwaga:** Dostęp poza granicami napisu (`napis1.at(index)`) generuje wyjątek `std::out_of_range`.

III. **Pobieranie długości napisu:**

```cpp
size_t dlugosc = napis1.length();
```

IV. **Porównywanie napisów:**

```cpp
if (napis1 == napis2) {
// Napisy są identyczne
}
```

V. **Wyszukiwanie w napisie:**

```cpp
size_t pozycja = napis1.find("ma");
if (pozycja != std::string::npos) {
// Znaleziono podnapis
}
```

VI. **Zamiana podnapisu:**

```cpp
napis1.replace(0, 3, "Ola"); // Zamienia pierwsze 3 znaki na "Ola"
```

VII. **Wydzielanie podnapisu:**

```cpp
std::string podnapis = napis1.substr(4, 2); // Wydziela 2 znaki od pozycji 4
```

#### Interoperacyjność z C-stringami

Chociaż `std::string` jest wygodny w użyciu, czasami konieczna jest interakcja z kodem, który wymaga tradycyjnych C-stringów (np. funkcje biblioteki C). Klasa `std::string` udostępnia metodę `c_str()`, która zwraca wskaźnik do tablicy znaków zakończonej znakiem null:

```cpp
const char *c_napis = napis1.c_str();
```

**Uwaga:** Wskaźnik zwrócony przez `c_str()` jest ważny tylko do momentu zmodyfikowania napisu. Jeśli planujesz modyfikować napis po pobraniu wskaźnika, musisz skopiować ciąg znaków do osobnego bufora.

#### Bezpieczeństwo i wydajność

- **`std::string` automatycznie zarządza pamięcią**, jednak w przypadku operacji na bardzo dużych napisach lub częstych operacjach w pętlach, może to negatywnie wpływać na wydajność. W takich przypadkach warto z wyprzedzeniem zarezerwować pamięć za pomocą metody `reserve(size_t n);`, aby zminimalizować koszt dynamicznej alokacji.
- Metody klasy `std::string` mogą rzucać **wyjątki**, takie jak `std::bad_alloc` w przypadku braku pamięci czy `std::out_of_range` przy dostępie poza granicami. Ważne jest uwzględnienie tych wyjątków w kodzie, zwłaszcza w środowiskach, gdzie stabilność jest kluczowa.
- W C++11 i nowszych wersjach wprowadzono **semantykę przenoszenia**, co umożliwia efektywne przenoszenie zasobów zamiast ich kopiowania. Warto korzystać z konstruktorów i operatorów przenoszących, aby poprawić wydajność w miejscach, gdzie kopiowanie jest zbędne.

#### Przykłady użycia `std::string`

**Łączenie i manipulacja napisami:**

```cpp
#include <iostream>
#include <string>

int main() {
    std::string napis = "Ala ma kota";
    std::string napis2 = " i psa";

    // Połączenie napisów
    napis += napis2;

    std::cout << napis << std::endl; // "Ala ma kota i psa"

    // Zamiana fragmentu napisu
    napis.replace(4, 2, "nie ma");

    std::cout << napis << std::endl; // "Ala nie ma kota i psa"

    // Wyszukiwanie
    size_t pozycja = napis.find("kota");
    if (pozycja != std::string::npos) {
        std::cout << "Znaleziono 'kota' na pozycji: " << pozycja << std::endl;
    }

    // Wydzielanie podnapisu
    std::string zwierze = napis.substr(pozycja, 4); // "kota"
    std::cout << "Zwierzę: " << zwierze << std::endl;

    return 0;
}
```

**Konwersja liczb na napisy i odwrotnie:**

W C++11 i nowszych dostępne są funkcje takie jak `std::to_string`, które ułatwiają konwersję liczb na napisy:

```cpp
#include <iostream>
#include <string>

int main() {
    int liczba = 42;
    std::string napis = "Liczba: " + std::to_string(liczba);

    std::cout << napis << std::endl; // "Liczba: 42"

    // Konwersja napisu na liczbę
    std::string liczba_napis = "123";
    int liczba2 = std::stoi(liczba_napis);

    std::cout << "Liczba2: " << liczba2 << std::endl; // 123

    return 0;
}
```

#### Zaawansowane operacje na napisach

Operacje na napisach w C++ to kluczowy element przetwarzania tekstu, szczególnie w aplikacjach związanych z analizą danych, przetwarzaniem języka naturalnego oraz systemami wielojęzycznymi. Poniżej opisano kilka zaawansowanych technik operacji na napisach, które znacznie rozszerzają możliwości programisty.

I. **Wyrażenia regularne:**  

W C++11 wprowadzono bibliotekę `<regex>`, która umożliwia manipulację napisami za pomocą wyrażeń regularnych. Jest to niezwykle potężne narzędzie, które pozwala na dopasowywanie wzorców, wyszukiwanie i manipulację fragmentami tekstu. Wyrażenia regularne mogą być stosowane do walidacji danych, ekstrakcji informacji oraz skomplikowanej manipulacji tekstu.

Przykład poniżej demonstruje podstawową operację wyszukiwania dopasowań w tekście za pomocą wyrażenia regularnego. Program dopasowuje wzorzec, który identyfikuje kto posiada jakie zwierzę, a następnie wyświetla wyniki.

```cpp
#include <iostream>
#include <string>
#include <regex>

int main() {
   std::string tekst = "Ala ma kota i psa";
   std::regex wzorzec("(\\w+) ma (\\w+)");
   std::smatch dopasowanie;
   
   if (std::regex_search(tekst, dopasowanie, wzorzec)) {
      std::cout << "Dopasowanie: " << dopasowanie[0] << std::endl;
      std::cout << "Osoba: " << dopasowanie[1] << std::endl;
      std::cout << "Zwierzę: " << dopasowanie[2] << std::endl;
   }
   
   return 0;
}
```

Wyrażenia regularne umożliwiają również bardziej zaawansowane operacje, takie jak:

- **Wyrażenia regularne umożliwiają znajdowanie i zamienianie fragmentów tekstu** na podstawie określonych wzorców, co jest przydatne w operacjach edycji i transformacji danych.
- Można wyszukiwać **wielokrotne dopasowania w tekście**, co pozwala na iteracyjne przeszukiwanie np. logów lub dokumentów, aby znaleźć wszystkie wystąpienia określonych wzorców.
- **Walidacja formatu** jest możliwa dzięki wyrażeniom regularnym, które mogą być używane do sprawdzania poprawności danych takich jak adresy e-mail, numery telefonów czy inne dane o określonym formacie.

II. **Unicode i międzynarodowe napisy:**  

W świecie globalizacji obsługa napisów w różnych kodowaniach jest kluczowa. Standard C++11 wprowadził wsparcie dla literałów Unicode, co umożliwia pracę z tekstem w takich kodowaniach jak UTF-8, UTF-16 i UTF-32. Jest to istotne przy tworzeniu aplikacji wielojęzycznych, gdzie wymagane jest poprawne wyświetlanie znaków z różnych alfabetów, takich jak cyrylica, chińskie znaki czy znaki diakrytyczne.

Przykład wykorzystania literałów Unicode w C++:

```cpp
#include <iostream>
#include <string>

int main() {
   std::u16string tekst = u"Привет мир!";  // UTF-16
   std::u32string innyTekst = U"你好，世界！";  // UTF-32
   
   std::cout << "Długość tekstu w UTF-16: " << tekst.length() << std::endl;
   std::cout << "Długość tekstu w UTF-32: " << innyTekst.length() << std::endl;
   
   return 0;
}
```

Chociaż wsparcie dla Unicode w C++ jest wbudowane, manipulowanie takimi napisami może być wyzwaniem. Długość napisów w UTF-16 czy UTF-32 nie zawsze odpowiada liczbie znaków, ponieważ niektóre znaki mogą być kodowane jako wieloznakowe sekwencje. Dlatego w wielu przypadkach programiści sięgają po zewnętrzne biblioteki, takie jak ICU (International Components for Unicode), które oferują kompleksowe narzędzia do manipulacji napisami Unicode.

**ICU (International Components for Unicode):** ICU to popularna biblioteka open-source zapewniająca zaawansowane wsparcie dla międzynarodowych formatów tekstowych, sortowania według lokalnych porządków, konwersji kodowań, obsługi dat i liczb oraz innych aspektów pracy z wielojęzycznymi aplikacjami.

III. **Operacje na napisach za pomocą `std::string_view`:**  

`std::string_view` to typ dodany w C++17, który umożliwia efektywniejsze operacje na napisach bez kopiowania danych. `std::string_view` reprezentuje widok na fragment napisu (ciąg znaków), co pozwala na szybszą i bardziej pamięciooszczędną manipulację tekstem.

```cpp
#include <iostream>
#include <string_view>

void wypisz_fragment(std::string_view tekst) {
   std::cout << "Fragment tekstu: " << tekst << std::endl;
}

int main() {
   std::string calyTekst = "To jest długi tekst.";
   wypisz_fragment(std::string_view(calyTekst).substr(3, 7));  // "jest d"

   return 0;
}
```

`std::string_view` jest idealny w sytuacjach, gdy chcemy jedynie analizować fragmenty tekstu bez potrzeby tworzenia nowych obiektów typu `std::string`. Jest to często wykorzystywane w sytuacjach, gdzie wydajność jest kluczowa, jak w analizie danych lub podczas operacji na dużych plikach tekstowych.

IV. **Biblioteki zewnętrzne do operacji na napisach:**  

Chociaż standardowa biblioteka C++ oferuje bogate wsparcie dla operacji na napisach, czasem może okazać się niewystarczająca. W takich przypadkach, do bardziej zaawansowanych zastosowań, istnieje wiele zewnętrznych bibliotek, takich jak:

- **Boost.StringAlgo** jest częścią biblioteki Boost i oferuje bogaty zestaw narzędzi do pracy z napisami, w tym funkcje do przeszukiwania, zamiany, transformacji oraz cięcia i dołączania tekstów, co zwiększa elastyczność operacji na ciągach znaków.
- **fmt** to biblioteka do formatowania napisów, która zapewnia zaawansowane możliwości formatowania podobne do `printf`, ale oferuje bardziej bezpieczne i elastyczne podejście, zwiększając wygodę i bezpieczeństwo przy formatowaniu tekstów.
- **ICU (International Components for Unicode)** to jedna z najbardziej zaawansowanych bibliotek do pracy z napisami Unicode oraz międzynarodowymi formatami tekstowymi, co czyni ją niezbędnym narzędziem w aplikacjach wielojęzycznych.
