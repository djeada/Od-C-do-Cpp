## Zmienne i typy danych
Zmienna to pojęcie informatyczne, które odnosi się do obszaru pamięci, w którym można zapisać dane. Każda zmienna ma swój typ, aby komputer wiedział, jak interpretować dane przechowywane w pamięci.

### Tworzenie zmiennej

Aby utworzyć zmienną, należy połączyć typ i nazwę:

```c++
int x;    // zmienna x typu int
double y; // zmienna y typu double
```

### Zasady nazewnictwa zmiennych

Nazwy zmiennych mogą składać się z liter, liczb i podkreślnika "_". Powinny zaczynać się od litery lub podkreślnika. Powinny być zrozumiałe, np. `liczbaSamochodow` lub `kolorTla`.

Istnieje wiele konwencji tworzenia złożonych nazw zmiennych. Dwie najpopularniejsze to:

1. oddzielanie słów podkreślnikiem, np. `masa_czastki_alfa` (tzw. snake_case). Przykład: `cena_paliwa`, `nr_telefonu`.
2. oddzielanie słów wielką literą, np. `masaCzastkiAlfa` (tzw. camelCase). Przykład: `cenaPaliwa`, `nrTelefonu`.

### Inicjalizacja

Inicjalizacja to proces przypisywania wartości zmiennej:

```c++
int x = 10;
double y = 3.56;
```

### Nadpisanie

Aby zmienić wartość zmiennej, można wykorzystać operator przypisania:

```c++
int x = 10;
x = x + 3; // teraz x przechowuje 13
x++;       // teraz x przechowuje 14
```

### Typy zmiennych

Istnieje wiele typów zmiennych, wśród nich można wymienić: pojedyncze znaki, liczby całkowite, liczby naturalne, liczby zmiennoprzecinkowe, typ logiczny i typ void.

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

Stała jest to zmienna, której wartość nie może zostać zmieniona w trakcie trwania programu. Deklaruje się je za pomocą słowa kluczowego `const`, a w nowszych wersjach C++ (11+) także `constexpr`, które wymusza na kompilatorze sprawdzenie, czy potrafi on wyliczyć wartość na etapie kompilacji. Przykłady:

```c++
const double pi = 3.14; // Ok. Stala jest zadeklarowana i zainicjalizowana.
constexpr double pi = 3.14;
```

### Zakres życia zmiennych

Każda zmienna ma zakres życia, który określa, gdzie i jak długo będzie istnieć. Zmienne globalne istnieją cały czas, od rozpoczęcia do zakończenia programu, natomiast zmienne lokalne są tworzone i usuwane w trakcie działania programu.

```c++
int a = 10; // zmienna globalna

int main() {
  int a = 3; // zmienna lokalna

  cout << a << endl;   // 3
  cout << ::a << endl; // 10
  return 0;
}
```

W powyższym przykładzie mamy dwie zmienne `a`, jedną globalną i jedną lokalną. Do zmiennej globalnej można odwołać się za pomocą operatora `::`.
