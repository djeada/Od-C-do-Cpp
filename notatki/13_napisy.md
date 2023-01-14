## Napisy

Poznaliśmy już tablice, które pozwalają przechowywać wiele elementów tego samego typu pod jedną nazwą. Napisy są specjalnym typem tablicy, który przechowuje znaki (char). Praca z tekstem jest nieunikniona w programowaniu, dlatego warto zapoznać się z funkcjami często używanymi do manipulacji napisów.

### C-string

W języku C napisy są tablicami znaków (char) zakończonymi znakiem '\0' (null-terminator). Oznacza to, że napis kończy się znakiem '\0', który jest znakiem specjalnym oznaczającym koniec napisu.

Istnieją różne sposoby inicjalizacji napisów:

* `char* napisA = "Ala ma kota";` - jest to niemodyfikowalny napis o długości 12 znaków
* `char napisB[] = "Ala ma kota";` - jest to modyfikowalny napis o długości 12 znaków
* `char napisC[] = {'A', 'l', 'a', ' ', 'm', 'a', ' ', 'k', 'o', 't', 'a', '\0'};` - jest to tak samo jak napisB

Przydatne biblioteki:

* `<string.h>` - zawiera funkcje do manipulacji napisami, np. strlen() zwraca długość napisu, strcpy() kopiuje napis z jednej tablicy do drugiej
* `<ctype.h>` - zawiera funkcje do manipulacji pojedynczymi znakami, np. isalpha() sprawdza czy znak jest literą, toupper() zamienia znak na wersję wielką
* `<stdlib.h>` - zawiera funkcje do konwersji między typami, np. atoi() konwertuje napis na liczbę całkowitą
    
Przykładowe funkcje:

| funkcja | działanie |
|---|---|
| strlen(const char *s) | zwraca długość napisu s |
| strcpy(char *dest, const char *src) | kopiuje zawartość napisu src do napisu dest |
| strcmp(const char *s1, const char *s2) | porównuje zawartość napisów s1 i s2 |
| strcat(char *dest, const char *src) | łączy zawartość napisów dest i src |
| strchr(const char *s, int c) | zwraca wskaźnik na pierwsze wystąpienie znaku c w napisie s |
| strstr(const char *s1, const char *s2) | zwraca wskaźnik na pierwsze wystąpienie napisu s2 w napisie s1 |
| isalpha(int c) | zwraca 1 jeśli c jest literą alfabetu, 0 w przeciwnym wypadku |
| isdigit(int c) | zwraca 1 jeśli c jest cyfrą, 0 w przeciwnym wypadku |
| isalnum(int c) | zwraca 1 jeśli c jest literą alfabetu lub cyfrą, 0 w przeciwnym wypadku |
| islower(int c) | zwraca 1 jeśli c jest małą literą alfabetu, 0 w przeciwnym wypadku |
| isupper(int c) | zwraca 1 jeśli c jest dużą literą alfabetu, 0 w przeciwnym wypadku |
| tolower(int c) | zamienia wielką literę na małą |
| toupper(int c) | zamienia małą literę na wielką |
| atoi(const char *s) | konwertuje napis s na liczbę całkowitą |
| atof(const char *s) | konwertuje napis s na liczbę zmiennoprzecinkową |

### Biblioteka string

W języku C++ mamy dostępną klasę string w bibliotece standardowej, która ułatwia i zwiększa bezpieczeństwo pracy z napisami w porównaniu do tablic znaków w języku C.

Aby utworzyć obiekt string, możemy skorzystać z następujących konstruktorów:

* `string(const char *s)` - tworzy obiekt string na podstawie ciągu znaków
* `string(const string &s)` - tworzy nowy obiekt string na podstawie istniejącego obiektu string.

Przykładowe funkcje:

| funkcja | działanie |
|---|---|
| s.length() | zwraca długość napisu s |
| s.c_str() | zwraca wskaźnik na napis s |
| s.empty() | zwraca true jeśli napis s jest pusty, false w przeciwnym wypadku |
| s.find(char c) | zwraca indeks pierwszego wystąpienia znaku c w napisie s |
| s.find(char c, int pos) | zwraca indeks pierwszego wystąpienia znaku c w napisie s od indeksu pos |
| s.find(string s) | zwraca indeks pierwszego wystąpienia napisu s w napisie s |
| s.find(string s, int pos) | zwraca indeks pierwszego wystąpienia napisu s w napisie s od indeksu pos |
| a.compare(string b) | porównuje zawartość napisów a i b |
| a.insert(int pos, string b) | wstawia napis b w miejsce pos w napisie a |
| a.erase(int pos, int len) | usuwa len znaków z napisu a od indeksu pos |
| a.replace(int pos, int len, string b) | zastępuje len znaków z napisu a od indeksu pos przez napis b |
| a.substr(int pos, int len) | zwraca podnapis napisu a od indeksu pos o długości len |
| a.clear() | usuwa wszystkie znaki z napisu a |
