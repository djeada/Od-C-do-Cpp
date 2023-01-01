## Napisy

Poznaliśmy już tablice, pozwalające pod jedną nazwą przechowywać wiele elementów tego samego typu. Napisy są specjalnym typem tablicy, który przechowuje znaki (char). Jako, że praca z tekstem jest nieunikniona w programowaniu, warto zapoznać się z funkcjami często używanymi do manipulacji napisów.

### C-string

W C napisy są tablicami charów zakończonymi znakiem '\0' (null-terminator).

Sposoby inicjalizacji napisów:

	char* napisA = "Ala ma kota"; 	// Niemodyfikowalny napis o długości 12 znaków
	char  napisB[] = "Ala ma kota";  // Modyfikowalny napis o długości 12 znaków
	char  napisC[] = {'A', 'l', 'a', ' ', 'm', 'a', ' ', 'k', 'o', 't', 'a', '\0'}; // tak samo jak napisB

Przydatne biblioteki:

	<string.h> - zawiera funkcje do manipulacji napisami
	<ctype.h>  - zawiera funkcje do manipulacji znakami
	<stdlib.h>  - zawiera funkcje do konwersji między typami

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

W języku C++ mamy klasę string dostępną w bibliotece standardowej. Praca z obiektami tej klasy jest łatwiejsza i bezpieczniejsza niż praca z tablicami charów w C.

Aby utworzyć obiekt stringa, możemy użyć konstruktora string(const char *s) lub string(const string &s).

	string napisA = "Ala ma kota";
	string napisB = napisA;

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
