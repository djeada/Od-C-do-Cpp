## Zmienne i typy danych

### Tworzenie zmiennej

Ogólna zasada: `Typ` + `nazwa`:

```c++
int x;    // zmienna x typu int
double y; // zmienna y typu double
```

### Zasady nazewnictwa zmiennych

Nazwy zmiennych mogą składać się z liter, liczb i podkreślnika "_". Powinny zaczynać się od litery lub podkreślnika. Powinny być zrozumiałe, np. `liczbaSamochodow` lub `kolorTla`.

Istnieje wiele konwencji tworzenia złożonych nazw zmiennych. Dwie najpopularniejsze to:

1. oddzielanie słów podkreślnikiem, np. `masa_czastki_alfa` (tzw. snake_case).
2. oddzielanie słów wielką literą, np. `masaCzastkiAlfa` (tzw. camelCase).

### Inicjalizacja

```c++
int x = 10;
double y = 3.56;
```

### Nadpisanie

```c++
int x = 10;
x = x + 3; // teraz x przechowuje 13
x++;       // teraz x przechowuje 14
```

### Typy zmiennych

<table class="boxed">
    <tbody>
        <tr>
            <th>Grupa</th>
            <th>Deklaracja w kodzie</th>
            <th>Precyzja oraz rozmiar</th>
        </tr>
        <tr>
            <td rowspan="4">Pojedyncze znaki</td>
            <td>char</td>
            <td>Jeden bajt. Najczęściej 8 bitów.</td>
        </tr>
        <tr>
            <td>char16_t</td>
            <td>Nie mniejszy niż <code>char</code>. Co najmniej 16 bitów.</td>
        </tr>
        <tr>
            <td>char32_t</td>
            <td>Nie mniejszy niż <code>char16_t</code>. Co najmniej 32 bity.</td>
        </tr>
        <tr>
            <td>wchar_t</td>
            <td>Najwięcej znaków pod jedną nazwą.</td>
        </tr>
        <tr>
            <td rowspan="5">Liczby całkowite</td>
            <td>signed char</td>
            <td>Taki sam rozmiar jak <code>char</code>. Co najmniej 8 bitów.</td>
        </tr>
        <tr>
            <td>signed short int</td>
            <td>Nie mniejszy niż <code>char</code>. Co najmniej 16 bitów.</td>
        </tr>
        <tr>
            <td>signed int</td>
            <td>Nie mniejszy niż <code>short</code>. Co najmniej 16 bitów.</td>
        </tr>
        <tr>
            <td>signed long int</td>
            <td>Nie mniejszy niż <code>int</code>. Co najmniej 32 bitów.</td>
        </tr>
        <tr>
            <td>signed long long int</td>
            <td>Nie mniejszy niż <code>long</code>. Co najmniej 64 bitów.</td>
        </tr>
        <tr>
            <td rowspan="5">Liczby naturalne</td>
            <td>unsigned char</td>
            <td rowspan="5">Tak jak całkowite.</td>
        </tr>
        <tr>
            <td>unsigned short int</td>
        </tr>
        <tr>
            <td>unsigned int</td>
        </tr>
        <tr>
            <td>unsigned long int</td>
        </tr>
        <tr>
            <td>unsigned long long int</td>
        </tr>
        <tr>
            <td rowspan="3">Liczby zmiennoprzecinkowe</td>
            <td>float</td>
            <td></td>
        </tr>
        <tr>
            <td>double</td>
            <td>Precyzja nie mniejsza niż dla<code>float</code>.</td>
        </tr>
        <tr>
            <td>long double</td>
            <td>Precyzja nie mniejsza niż dla <code>double</code>.</td>
        </tr>
        <tr>
            <td>Typ logiczny</td>
            <td>bool</td>
            <td></td>
        </tr>
        <tr>
            <td>Typ void</td>
            <td>void</td>
            <td>nic nie przechowuje</td>
        </tr>
    </tbody>
</table>

### Stałe

Zmienna, której wartość nie może zostać zmieniona w trakcie trwania programu zwana jest stałą.

```c++
const double pi = 3.14;       // Ok. Stala jest zadeklarowana i zainicjalizowana.
const double doInicjalizacji; // Złe. Tak nie robimy!
```

W nowszych wersjach C++ (11+) dodano inne słowo kluczowe służące do określania stałości. Słowo kluczowe <code>constexpr</code> wymusza na kompilatorze sprawdzenie, czy potrafi on wyliczyć wartość na etapie kompilacji. Jeśli nie, zostanie zgłoszony błąd.

```c++
constexpr double pi = 3.14;
```

### Zakres życia zmiennych

```c++
int a = 10; // zmienna globalna

int main() {
  int a = 3; // zmienna lokalna

  cout << a << endl;   // 3
  cout << ::a << endl; // 10
  return 0;
}
```
