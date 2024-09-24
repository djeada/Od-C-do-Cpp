## Zmienne i typy danych

W języku programowania, zmienna to identyfikator reprezentujący określony obszar pamięci, w którym przechowywane są dane. Każda zmienna ma przypisany konkretny typ danych, który informuje komputer o rodzaju i zakresie informacji przechowywanej w zmiennej. Typ danych określa także operacje, jakie można wykonywać na tych danych, oraz ilość pamięci, jaką zmienna zajmuje.

### Deklaracja i inicjalizacja zmiennej

Deklaracja zmiennej polega na określeniu jej typu i nazwy. Inicjalizacja to przypisanie zmiennej jej początkowej wartości. Deklaracja i inicjalizacja mogą być wykonane jednocześnie lub osobno.

```c++
int liczba;                // deklaracja zmiennej typu int
liczba = 10;               // przypisanie wartości zmiennej
double wspolczynnik = 2.5; // deklaracja i inicjalizacja zmiennej typu double
```

### Zasady nazewnictwa zmiennych

Podczas nazywania zmiennych, warto przestrzegać pewnych zasad, aby kod był czytelny i łatwy w utrzymaniu:

- Nazwy zmiennych mogą składać się z liter, cyfr i podkreślnika `_` i powinny zaczynać się od litery lub podkreślnika.
- Unikaj używania słów kluczowych języka programowania, takich jak `int`, `class`, `return`.
- Nazwy powinny być opisowe i zrozumiałe, np. `liczbaDni`, `wspolczynnikZmiany`.

Istnieje kilka popularnych konwencji nazewnictwa:

- `snake_case`: oddzielanie słów podkreślnikiem, np. `masa_czastki`, `adres_email`.
- `camelCase`: pierwsze słowo małą literą, następne wielką, np. `masaCzastki`, `adresEmail`.
- `PascalCase`: każde słowo zaczyna się wielką literą, np. `MasaCzastki`, `AdresEmail` (często stosowane dla nazw klas).

### Przypisanie i modyfikacja wartości

Po zadeklarowaniu zmiennej, można jej przypisać wartość lub modyfikować istniejącą wartość.

```c++
int liczba = 5;   // inicjalizacja zmiennej wartością 5
liczba = liczba + 3; // modyfikacja wartości na 8
liczba++;           // inkrementacja wartości o 1; teraz liczba to 9
```

### Typy zmiennych

W języku C++ istnieje wiele różnorodnych typów zmiennych, które odpowiadają różnym kategoriom danych. Wśród nich można wymienić m.in.: pojedyncze znaki, liczby całkowite, liczby zmiennoprzecinkowe, typ logiczny oraz typ void.

Przykładowa tabela typów danych

| Grupa                     | Typ danych                | Rozmiar                | Zakres                                     |
|---------------------------|---------------------------|------------------------|--------------------------------------------|
| Pojedyncze znaki          | `char`                    | 1 bajt (8 bitów)       | -128 do 127 lub 0 do 255 (zależy od znaku) |
|                           | `char16_t`                | co najmniej 16 bitów   | 0 do 65,535                                 |
|                           | `char32_t`                | co najmniej 32 bity    | 0 do 4,294,967,295                          |
|                           | `wchar_t`                 | zależy od implementacji| -32768 do 32767 lub 0 do 65535             |
| Liczby całkowite          | `signed char`             | co najmniej 8 bitów    | -128 do 127                                 |
|                           | `signed short int`        | co najmniej 16 bitów   | -32,768 do 32,767                           |
|                           | `signed int`              | co najmniej 16 bitów   | -32,768 do 32,767                           |
|                           | `signed long int`         | co najmniej 32 bity    | -2,147,483,648 do 2,147,483,647             |
|                           | `signed long long int`    | co najmniej 64 bity    | -9,223,372,036,854,775,808 do 9,223,372,036,854,775,807 |
| Liczby naturalne          | `unsigned char`           | co najmniej 8 bitów    | 0 do 255                                    |
|                           | `unsigned short int`      | co najmniej 16 bitów   | 0 do 65,535                                 |
|                           | `unsigned int`            | co najmniej 16 bitów   | 0 do 65,535                                 |
|                           | `unsigned long int`       | co najmniej 32 bity    | 0 do 4,294,967,295                          |
|                           | `unsigned long long int`  | co najmniej 64 bity    | 0 do 18,446,744,073,709,551,615             |
| Liczby zmiennoprzecinkowe | `float`                   | 32 bity                | ±1.5 × 10^−45 do ±3.4 × 10^38               |
|                           | `double`                  | 64 bity                | ±5.0 × 10^−324 do ±1.7 × 10^308             |
|                           | `long double`             | co najmniej 64 bity    | Zależy od implementacji, zazwyczaj większy niż `double` |
| Typ logiczny              | `bool`                    | 1 bajt (8 bitów)       | `true` lub `false`                          |
| Typ void                  | `void`                    | n/d                    | n/d                                        |

### Stałe

Stała to zmienna, której wartość jest niezmienna przez cały czas trwania programu. W języku C++ stałe deklaruje się za pomocą słowa kluczowego `const`. Stałe mogą być również wyliczane w trakcie kompilacji przy użyciu słowa kluczowego `constexpr`, wprowadzonego w C++11, co pozwala na jeszcze bardziej efektywne zarządzanie pamięcią i optymalizację kodu przez kompilator.

#### Deklaracja stałych

- **Stałe z `const`**: Słowo kluczowe `const` jest używane do deklaracji zmiennych, które nie mogą zmieniać swojej wartości po inicjalizacji.
  
  ```c++
  const double pi = 3.14159;
  ```
  
  W powyższym przykładzie `pi` jest stałą typu `double` o wartości 3.14159.

- **Stałe z `constexpr`**: Słowo kluczowe `constexpr` wskazuje, że wartość zmiennej może być obliczona podczas kompilacji, co jest szczególnie przydatne w kontekście optymalizacji i zapewnienia, że dane są dostępne w czasie kompilacji.
  
  ```c++
  constexpr double euler = 2.71828;
  ```
  
  W powyższym przykładzie `euler` jest stałą typu `double`, której wartość zostanie obliczona podczas kompilacji.

#### Korzyści z używania stałych

- Używanie stałych w kodzie **zapobiega przypadkowemu modyfikowaniu wartości**, co znacząco zwiększa jego bezpieczeństwo, ponieważ unika się niezamierzonych zmian w kluczowych zmiennych.
- **Stałe z dobrze opisanymi nazwami** pomagają w poprawie czytelności kodu, co sprawia, że program jest łatwiejszy do zrozumienia zarówno dla twórcy, jak i innych programistów.
- Kompilator, mając wiedzę, że pewne wartości są niezmienne, może skuteczniej **optymalizować działanie programu**, co prowadzi do bardziej wydajnego kodu.
- **Dzięki stałym** łatwiej jest zarządzać dużymi projektami, ponieważ kluczowe wartości są centralnie zdefiniowane i ich zmiana nie wymaga przeszukiwania całego kodu.
- Stałe mogą również poprawiać **dokumentację kodu**, ponieważ ich nazwy często jasno sugerują, co reprezentują, co zmniejsza potrzebę dodatkowych komentarzy.
- **Stałe pozwalają na lepsze testowanie** i weryfikację poprawności kodu, ponieważ wartości niezmienne są przewidywalne i łatwiej jest stworzyć przypadki testowe. 

### Zakres życia zmiennych

Zakres życia zmiennej określa, kiedy zmienna jest dostępna i kiedy jest niszczona podczas działania programu. Zmiennymi mogą być globalne, lokalne, statyczne i dynamiczne.

#### Zmienne globalne

Zmienne globalne są deklarowane poza funkcjami i są dostępne w całym programie od momentu jego uruchomienia do zakończenia. Mogą być dostępne z dowolnej funkcji w programie.

```c++
int globalna = 10; // zmienna globalna

int main() {
  int lokalna = 3; // zmienna lokalna

  std::cout << lokalna << std::endl;   // 3
  std::cout << ::globalna << std::endl; // 10
  return 0;
}
```

W powyższym przykładzie `globalna` jest zmienną globalną, a `lokalna` jest zmienną lokalną dostępną tylko w funkcji `main`. Jeśli chcemy odwołać się do zmiennej globalnej w sytuacji, gdy w danej funkcji istnieje zmienna o tej samej nazwie, używamy operatora zakresu `::`.

#### Zmienne lokalne

Zmienne lokalne są deklarowane wewnątrz funkcji lub bloku kodu i są dostępne tylko w ramach tej funkcji lub bloku. Istnieją one od momentu ich deklaracji do końca bloku, w którym zostały zadeklarowane.

```c++
void funkcja() {
  int lokalna = 5; // zmienna lokalna
  std::cout << lokalna << std::endl; // 5
}
// zmienna lokalna nie jest dostępna poza funkcją
```

#### Zmienne statyczne

Zmienne statyczne zachowują swoją wartość między wywołaniami funkcji. Mogą być deklarowane zarówno na poziomie globalnym, jak i wewnątrz funkcji.

```c++
void funkcja() {
  static int licznik = 0; // zmienna statyczna
  licznik++;
  std::cout << "Licznik: " << licznik << std::endl;
}

int main() {
  funkcja(); // Licznik: 1
  funkcja(); // Licznik: 2
  funkcja(); // Licznik: 3
  return 0;
}
```

W powyższym przykładzie zmienna `licznik` zachowuje swoją wartość między wywołaniami funkcji `funkcja`.
