## Zmienne i typy danych

W języku programowania, zmienna to identyfikator reprezentujący określony obszar pamięci, w którym przechowywane są dane. Każda zmienna ma przypisany konkretny typ danych, który informuje komputer o rodzaju i zakresie informacji przechowywanej w zmiennej.

### Deklaracja i inicjalizacja zmiennej

Deklaracja zmiennej polega na określeniu jej typu i nazwy. Opcjonalnie, podczas deklaracji możemy również przypisać zmiennej jej początkową wartość, co nazywane jest inicjalizacją.

```c++
int liczba;         // deklaracja zmiennej typu int
double wspolczynnik = 2.5; // deklaracja i inicjalizacja zmiennej typu double
```

### Zasady nazewnictwa zmiennych

Podczas nazywania zmiennych, warto przestrzegać pewnych zasad:

- Nazwy zmiennych mogą składać się z liter, cyfr i podkreślnika "_" i powinny zaczynać się od litery lub podkreślnika.
- Unikaj używania słów kluczowych języka programowania.
- Nazwy powinny być opisowe i zrozumiałe, takie jak liczbaDni, wspolczynnikZmiany.

Istnieje kilka popularnych konwencji nazewnictwa:

- `snake_case`: oddzielanie słów podkreślnikiem, np. masa_czastki, adres_email.
- `camelCase`: pierwsze słowo małą literą, następne wielką, np. masaCzastki, adresEmail.
- `PascalCase`: każde słowo zaczyna się wielką literą, np. MasaCzastki, AdresEmail (często stosowane dla nazw klas).

### Przypisanie i modyfikacja wartości

Po zadeklarowaniu zmiennej, można jej przypisać wartość lub modyfikować istniejącą wartość.

```c++
int liczba = 5;   // inicjalizacja zmiennej wartością 5
liczba = liczba + 3; // modyfikacja wartości na 8
liczba++;           // inkrementacja wartości o 1; teraz liczba to 9
```

### Typy zmiennych

W języku C++ istnieje wiele różnorodnych typów zmiennych, które odpowiadają różnym kategoriom danych. Wśród nich można wymienić m.in.: pojedyncze znaki, liczby całkowite, liczby zmiennoprzecinkowe, typ logiczny oraz typ void.

| Grupa                     | Deklaracja w kodzie       | Precyzja oraz rozmiar                                                |
|---------------------------|---------------------------|----------------------------------------------------------------------|
| Pojedyncze znaki          | char                      | Jeden bajt. Najczęściej 8 bitów.                                     |
|                           | char16_t                 | Co najmniej 16 bitów.                                                |
|                           | char32_t                 | Co najmniej 32 bity.                                                 |
|                           | wchar_t                  | Zależy od implementacji, ale służy do przechowywania znaków szerokich.|
| Liczby całkowite          | signed char               | Co najmniej 8 bitów.                                                 |
|                           | signed short int          | Co najmniej 16 bitów.                                                |
|                           | signed int                | Co najmniej 16 bitów.                                                |
|                           | signed long int           | Co najmniej 32 bitów.                                                |
|                           | signed long long int      | Co najmniej 64 bitów.                                                |
| Liczby naturalne          | unsigned char             | Tak jak całkowite.                                                   |
|                           | unsigned short int        |                                                                      |
|                           | unsigned int              |                                                                      |
|                           | unsigned long int         |                                                                      |
|                           | unsigned long long int    |                                                                      |
| Liczby zmiennoprzecinkowe | float                     | 32-bitowa precyzja (zależy od platformy).                            |
|                           | double                    | Co najmniej taka sama precyzja jak `float`, ale zwykle większa.      |
|                           | long double               | Precyzja nie mniejsza niż dla `double`.                              |
| Typ logiczny              | bool                      | Reprezentuje wartości `true` lub `false`.                            |
| Typ void                  | void                      | Nie przechowuje żadnych wartości.                                    |

### Stałe

Stała to zmienna, której wartość jest niezmienna przez cały czas trwania programu. W języku C++ deklaruje się je za pomocą słowa kluczowego `const`. Istnieje też słowo kluczowe `constexpr` (wprowadzone w C++11), które pozwala kompilatorowi obliczyć wartość stałej w trakcie kompilacji.

```c++
const double pi = 3.14159; 
constexpr double euler = 2.71828;
```

### Zakres życia zmiennych

Zmienna posiada zakres życia, który określa, kiedy jest ona dostępna w trakcie działania programu. Zmienne globalne istnieją od momentu rozpoczęcia programu do jego zakończenia, natomiast zmienne lokalne istnieją tylko w obrębie funkcji lub bloku, w którym zostały zadeklarowane.

```c++
int globalna = 10; // zmienna globalna

int main() {
  int lokalna = 3; // zmienna lokalna

  cout << lokalna << endl;   // 3
  cout << ::globalna << endl; // 10
  return 0;
}
```

W powyższym przykładzie mamy zmienną globalną globalna oraz zmienną lokalną lokalna. Jeśli chcemy odwołać się do zmiennej globalnej w sytuacji, gdy w danej funkcji istnieje zmienna o tej samej nazwie, używamy operatora zakresu `::`.
