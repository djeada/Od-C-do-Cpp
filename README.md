# Od-C-do-Cpp

Kod źródłowy do programów z yt.

![Screenshot from 2022-08-22 11-41-50](https://user-images.githubusercontent.com/37275728/185891430-7f77914e-f81b-4dcf-bd81-c86ac0d47b70.png)

# Spis Treści
<!--ts-->

- [Proces kompilacji](#Proces-kompilacji)
- [Preprocesor](#Preprocesor)
- [Zmienne](#Zmienne)
- [Interakcja z konsolą](#Interakcja-z-konsolą)
- [Instrukcje warunkowe](#Instrukcje-warunkowe)
- [Pętle](#Pętle)
- [Liczby losowe](#Liczby-losowe)
- [Typ wyliczeniowy enum](#Typ-wyliczeniowy-enum)
- [Funkcje](#Funkcje)
- [L wartości i r wartości](#L-wartości-i-r-wartości)
- [Wskaźniki](#Wskaźniki)
- [Tablice](#Tablice)
- [Napisy](#Napisy)
- [Operacje bitowe](#Operacje-bitowe)
- [Programowanie Obiektowe](#Programowanie-Obiektowe)
- [Dziedziczenie](#Dziedziczenie)
- [Zaawansowne wskaźniki](#Zaawansowne-wskaźniki)
- [Przeciążanie](#Przeciążanie)
- [Konwersje](#Konwersje)
- [Lambdy](#Lambdy)
- [Szablony](#Szablony)
- [Wyjątki](#Wyjątki)
- [STL](#STL)
- [Praca z plikami](#Praca-z-plikami)
- [C vs Cpp](#C-vs-Cpp)
- [Bibliografia](#Bibliografia)

<!--te-->

## Proces kompilacji

Kompilator to program, który na wejściu otrzymuje kod źródłowy innego programu i generuje pliki obiektowe zawierające kod assemblera.

1. Najpierw na scenę wkracza Pan Preprocesor. Zadań tego Pana jest wiele, wśród nich wymienić można:

   - Włączenie zawartości załączonych plików nagłówkowych do kodu źródłowego. Na przykład, jeśli w jednym z kompilowanych plików umieściliśmy <code>#include "plik.h"</code>, to treść tego pliku zostanie przekopiowana do naszego kodu źródłowego.
   - Generacja kodu makr.
   - Zamiana stałych zdefiniowanych za pomocą #define na ich wartości. Kod źródłowy przygotowany przez Pana Preprocesora jest następnie poddany analizie składni, w której skład wchodzą:
   - Analiza leksykalna (np. odrzucenie zakomentowanych fragmentów kodu). - Analiza składni (np. czy nie próbujemy skorzystać ze zmiennej, zanim została stworzona).
   - Analiza semantyczna (np. weryfikacja typów i poprawność instrukcji).

2. Tworzenie plików obiektowych z rozszerzeniem .o i zawierających kod źródłowy przetłumaczony na rozkazy w assemblerze.
3. Przygotowany w ten sposób kod obiektowy jest łączony z kodem obiektowym funkcji z zewnętrznych bibliotek w wykonywalny program (pod Windowsem będzie mieć rozszerzenie .exe).

Dlaczego nie piszemy bezpośrednio w assemblerze?

1. Istnieje wiele dialektów języka assembler. Każdy procesor ma własny zestaw instrukcji, który nie zawsze pokrywa się z instrukcjami innych typów procesorów. Kompilator pozwala nam ten sam kod kompilować do wielu typów procesorów.
2. Kompilatory to szczwane bestie. Twój kod jest nie tylko tłumaczony na assembler, ale również optymalizowany pod względem wydajności.
3. Wysokopoziomowe języki programowania bogate są wiele konstrukcji ułatwiających pracę nad złożonym kodem. Przykładem mogą być struktury danych jak stosy, czy kolejki. Assembler to tylko kilka instrukcji, typu zwiększ, skocz do innej linii, porównaj.
   Pan Preprocesor przetwarza kod źródłowy.

Zadania Pana Preprocesora definiowane są za pomocą specjalnych zaklęć zwanych dyrektywami rozpoczynanych od kratki <i>#</i>.
Dyrektywy mogą być umieszczane w dowolnym miejscu programu, ale przyjęło się, że najczęściej gromadzi się je u góry pliku źródłowego.

Najczęściej spotykaną dyrektywą będzie załączenie biblioteki.

Kompilacja programu napisanego w C, przy pomocy gcc:

    gcc -std=c99 main.c -o exe

Kompilacja programu napisanego w C++, przy pomocy g++:

    g++ -pedantic -std=c++98 main.cpp -o exe
    g++-10 -Wall -Wextra -std=c++20 main.cpp -o exe

Poprawa formatowania, przy pomocy clang-format:

    find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;

## Preprocesor

Pan Preprocesor przetwarza kod źródłowy.

Zadania Pana Preprocesora definiowane są za pomocą specjalnych zaklęć zwanych dyrektywami rozpoczynanych od kratki <i>#</i>.
Dyrektywy mogą być umieszczane w dowolnym miejscu programu, ale przyjęło się, że najczęściej gromadzi się je u góry pliku źródłowego.

Najczęściej spotykaną dyrektywą będzie załączenie biblioteki.

```c++
#include <biblioteka>
```

Za pomocą dyrektyw możemy definiować stałe.

```c++
#define TRUE 1
```

Możemy również włączyć/wyłączyć część kodu w zależności od danego warunku. Działa to tak samo, jak zwykłe instrukcje warunkowe, z tym że podane warunki ustalane są przed uruchomieniem programu.

```c++
#if 1 == 1
// kod
#else
// inny kod
#endif
```

## Zmienne

### Tworzenie zmiennej

Ogólna zasada: <code>Typ</code> + nazwa</code>.

```c++
int x;    // zmienna x typu int
double y; // zmienna y typu double
```

### Zasady nazewnictwa zmiennych

Nazwy zmiennych mogą składać się z:

- liter </br>
- liczb </br>
- podkreślnika "\_"

Muszą zaczynać się od litery bądź podkreślnika. </br>

Nazwa zmiennej powinna coś znaczyć np. <i>liczbaSamochodow</i>, bądź <i>kolorTla</i>.

Są różne konwencje tworzenie złożonych nazw zmiennych. Dwie najpopularniejsze współcześnie to:

1. oddzielanie słów podkreślnikiem np. masa_czastki_alfa (tzw. snake_case).
2. oddzielanie słów wielką literą np. masaCzastkiAlfa (tzw. camelCase).

### Inicjalizacja

```c++
int x = 10;
double y = 3.56;
```

### Nadpisanie:

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
            <td>Nie mniejszy niż <code>char16_t</code>.Co najmniej 32 bity.</td>
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
            <td>signed short int</code>
            </td>
            <td>Nie mniejszy niż <code>char</code>. Co najmniej 16 bitów.</td>
        </tr>
        <tr>
            <td>signed int </td>
            <td>Nie mniejszy niż <code>short</code>. Co najmniej 16 bitów.</td>
        </tr>
        <tr>
            <td>signed long int</code>
            </td>
            <td>Nie mniejszy niż <code>int</code>. Co najmniej 32 bitów.</td>
        </tr>
        <tr>
            <td>signed long long int</code>
            </td>
            <td>Nie mniejszy niż <code>long</code>. Co najmniej 64 bitów.</td>
        </tr>
        <tr>
            <td rowspan="5">Liczby naturalne</td>
            <td>unsigned char</td>
            <td rowspan="5">Tak jak całkowite.</td>
        </tr>
        <tr>
            <td>unsigned short <code>int</code></code>
            </td>
        </tr>
        <tr>
            <td>unsigned <code>int</code></code>
            </td>
        </tr>
        <tr>
            <td>unsigned long <code>int</code></code>
            </td>
        </tr>
        <tr>
            <td>unsigned long long <code>int</code></code>
            </td>
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
const double doInicjalizacji; // Zle. Tak nie robimy!
```

W nowszych wersjach C++ (11+) dodano inne słowo kluczowe służące do określania stałości. Słowo kluczowe <code>constexpr</code> wymusza na kompilatorze sprawdzenie, czy potrafi on wyliczyć  wartość na etapie kompilacji. Jeśli nie, zostanie zgłoszony błąd.

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

## Interakcja z konsolą

Każdy program w momencie uruchomienia ma dostęp do trzech strumieni:

    1. stdin - strumień wejściowy
    2. stdout - strumień wyjściowy
    3. stderr - strumień błędów

W C używamy funkcji <code>printf</code> oraz <code>scanf</code> odpowiednio do wypisywania danych na ekran i pobierania danych z klawiatury.

```
#include <iostream>

using namespace std;

int main() {
  int liczba;
  cout << "Podaj pojedyncza liczbe: " << endl;
  scanf("%d", &liczba);

  printf("Podales liczbe: %d\n", liczba);	

  return 0;
}
```

| fromat | typ danych |
-----------------------
| <code>%d</code> | int |
| <code>%l</code> | long |
| <code>%f</code> | double |
| <code>%c</code> | unsigned char |
| <code>%s</code> | wskaźnik na char |

W C++ biblioteka <code>iostream</code>zawiera definicje funkcji, które pozwalają na komunikację z tymi strumieniami:

- obiekt <code>cout</code> oraz operator <code><<</code> wypisuje tekst na standardowe wyjście;
- obiekt <code>cin</code> oraz operator <code>>></code> wczytują pojedynczą wartość ze standardowego wejścia;
- <code>getline(cin, string)</code> wczytuje ze standardowego wejścia cały wiersz wraz ze spacjami.

```c++
#include <iostream>

using namespace std;

int main() {
  int liczba;
  cout << "Podaj pojedyncza liczbe: " << endl;
  cin >> liczba;

  cout << "Podales liczbe: " << liczba << endl;

  cin.ignore(); // wyczyszczenie bufora

  string zadanie;
  cout << "Podaj pelne zdanie: " << endl;

  getline(cin, zdanie);

  cout << "Podales zdanie: " << endl << zdanie << endl;

  return 0;
}
```

## Instrukcje warunkowe

Instrukcje warunkowe służą do włączania i wyłączania fragmentów kodu w zależności od warunku.

### If

<code> If </code> to podstawowa instrukcja warunkowa, dostępna w wielu językach programowania. Warunek definiowany jest w nawiasach okrągłych. Jeśli warunek jest spełniony, to wykonany zostanie kod znajdujący się w nawiasach klamrowych. W przeciwnym razie program pomija kod znajdujący się w nawiasach klamrowych i przechodzi do następnych linii kodu.

```c++
  if (warunek) {
    kod;
  }
```

Konstrukcja <code>if-else</code> pozwala na wykonanie różnych bloków kodu w zależności od warunku. Jeśli warunek jest spełniony, to wykonany zostanie kod znajdujący się w nawiasach klamrowych za <code>if</code>. W przeciwnym razie wykonany zostanie kod znajdujący się w nawiasach klamrowych za <code>else</code>.

```c++
  if (warunek) {
    kod;
  } else {
    kod;
  }
```

Jeśli kod jaki chcemy umieścić po słowach kluczowych <code>if</code> lub <code>else</code> składa się wyłącznie z pojedynczej linii, to nawiasy klamrowe mogą zostać pominięte.

```c++
#include <iostream>

int main() {
  int n;
  std::cin >> n;
  if (n % 3 == 0)
    std::cout << "Liczba " << n << " jest podzielna przez 3 " << std::endl;
  else {
    n++;
    std::cout << "Wczytana liczba powiekszona o 1 to: " << n << std::endl;
  }

  return 0;
}
```

### Wielokrotne warunki

Możemy sprawdzić wiele warunków jeden po drugim i uzleżnić od ich spełnienia różne bloki kodu.

```c++
#include <iostream>

int main() {
  int n;
  std::cout << "Podaj numer dnia tygodnia: " << std::endl;
  std::cin >> n;

  if (n == 0)
    std::cout << "Poniedzialek." << std::endl;

  else if (n == 1)
    std::cout << "Wtorek." << std::endl;

  else if (n == 2)
    std::cout << "Sroda. " << std::endl;

  else if (n == 3)
    std::cout << "Czwartek." << std::endl;

  else if (n == 4)
    std::cout << "Piatek." << std::endl;

  else if (n == 5)
    std::cout << "Sobota." << std::endl;

  else if (n == 6)
    std::cout << "Niedziela." << std::endl;
  else
    std::cout << "Error! " << std::endl;

  return 0;
}
```

### Switch

<code>Switch</code> daje nam również możliwość sprawdzenia wielokrotnych warunków.
Niektóre kompilatory lepiej optymalizują kod z użyciem <code>switch</code> niż <code>else if</code>.
Mechanizm ten jest również niejednokrotnie uważany za bardziej elegancki.

```c++
#include <iostream>

int main() {
  int n;
  std::cout << "Podaj numer dnia tygodnia: " << std::endl;
  std::cin >> n;

  switch (n) {
  case 0:
    std::cout << "Poniedzialek." << std::endl;
    break;

  case 1:
    std::cout << "Wtorek." << std::endl;
    break;

  case 2:
    std::cout << "Sroda. " << std::endl;
    break;

  case 3:
    std::cout << "Czwartek." << std::endl;
    break;

  case 4:
    std::cout << "Piatek." << std::endl;
    break;

  case 5:
    std::cout << "Sobota." << std::endl;
    break;

  case 6:
    std::cout << "Niedziela." << std::endl;
    break;

  default:
    std::cout << "Error! " << std::endl;
  }

  return 0;
}
```

## Pętle

### Pętla for

Po słowie kluczowym <code>for</code> w nawiasach okrągłych mamy do dyspozycji trzy miejsca oddzielone średnikami. Na pierwszym miejscu wstawiamy kod, który ma się wykonać przed pętlą. Najczęściej będzie to inicjalizacja licznika. Na drugim miejscu wstawiamy warunek, który będzie sprawdzany w każdej iteracji pętli. Jeśli warunek jest spełniony, to wykonany zostanie kod znajdujący się w nawiasach klamrowych za <code>for</code>. W przeciwnym razie pętla zostanie zakończona. Na trzecim miejscu wstawiamy kod, który ma się wykonać po każdej iteracji pętli.

```
  for (inicjalizaja; warunek; inkrementacja) {
    kod;
  }
```

### Pętla while

Pętla <code>while</code> jest podobna do pętli <code>for</code>, z tym, że nie musi mieć inicjalizacji, ani inkrementacji. Warunek jest również spradzany przed każdą iteracją pętli.

```
  while (warunek) {
    kod;
  }
```

### Pętla do while

Pętla <code>do while</code> jest niemalże identyczna jak pętla <code>while</code>, z tym, że kod wykonywany jest przed sprawdzeniem warunku. Z tej przyczyny ciało pętli będzie zawsze wykonane conajmniej raz, nawet jeśli warunek jest już na samym początku fałszywy.

```
  do {
    kod;
  } while (warunek);
```

### Continue

Słowo kluczowe <code>continue</code> pozwala przerwać aktualną iterację pętli i wrócić do początku pętli. Jeśli warunek pętli jest dalej spełniony, to ciało pętli zostanie ponownie wykonane.

```c++
#include <iostream>

int main() {
  int n;
  std::cout << "Podaj liczbe: " << std::endl;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    if (i % 2)
      continue;
    std::cout << i << std::endl;
  }

  return 0;
}
```

### Break

Podobnie jak <code>continue</code>, <code>break</code> przerywa aktualną iterację pętli. Różnica polega na tym, że po wywołaniu <code>break</code> pętla zostanie całkowicie przerwana i program przejdzie do kodu znajdującego się pod pętlą.

```c++
#include <iostream>

int main() {
  int n;
  std::cout << "Podaj liczbe: " << std::endl;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    if (i % 2)
      break;
    std::cout << i << std::endl;
  }

  return 0;
}
```

## Liczby losowe

```c++
#include <random>

int losowa_z_przedzialu(int start, int end) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist(start, end);
  return distr(gen);
}

bool orzel_lub_reszka() { return (randomInRange(-10001, 10000)); }
```

## Typ wyliczeniowy enum

Typ wyliczeniowy <code>enum</code> pozwala na tworzenie zmiennych, które mogą przyjmować jedynie z góry określone wartości. Wartości te mają czytelne nazwy, a dodatkowo <code>enum</code> jest bardzo szybki i opłaca się go używać nawet w krytycznych miejscach programu.

```c++
#include <iostream>

enum class Kolor { Czerwony, Zielony, Niebieski };

int main() {
  Kolor kolor = Color::Czerwony;

  switch (kolor) {
  case Color::Czerwony:
    std::cout << "Wybrano czerwony." << std::endl;
    break;
  case Color::Zielony:
    std::cout << "Wybrano zielony." << std::endl;
    break;
  case Color::Niebieski:
    std::cout << "Wybrano niebieski." << std::endl;
    break;
  default:
    std::cout << "Blad!" << std::endl;
  }

  return 0;
}
```

## Funkcje

Za pomocą funkcji możemy część kodu zamknąć pod jedną nazwą.

### Tworzenie i wywoływanie funkcji

Elementy składowe funkcji to:

1. <code>Typ</code> zwracanej wartości.
1. <code>Imię</code> funkcji, dzięki któremu jest rozpoznawalna.
1. <code>Argumenty</code>, czyli zewnętrzne wartości, które chcemy użyć w funkcji i chcemy żeby zostały nam podane w momencie wywołania funkcji.

Ogólny schemat pracy z funkcjami:

```
wybrany_typ nazwa_funkcji(argumenty...) {
  
  ... // cialo czyli kod kotry chcemy zeby zostal uruchomiony 
  ... // po wywolaniu nazwa_funkcji(argumenty...);
  
  return wartosc; // zwracamy wartosc ktora musi zgadzac sie z wybrany_typ
}

int main() { 
  wybrany_typ x = nazwa_funkcji(argumenty...));
  return 0;  
}
```

### Deklaracja i definicja funkcji

Deklaracja funkcji to wyrażenie, które zawiera nazwę funkcji, jej argumenty oraz jej zwracany typ. Deklaracja musi pojawić się w kodzie przed wywołaniem funkcji. W przeciwnym razie kompilator wyświetli komunikat o błędzie. Definicja funkcji to deklaracja wraz z ciałem funkcji.

```c++
#include <iostream>

// definicja
void fun1() { std::cout << "fun1" << std::endl; }

// deklaracja
void fun2();

int main() {
  fun1(); // OK
  fun2(); // OK
  fun3(); // ZLE

  return 0;
}

void fun2() { std::cout << "fun2" << std::endl; }

void fun3() { std::cout << "fun3" << std::endl; }
```

### Funkcja zwracająca wartość

Do zwracania wartości poprzez funkcję używamy słowa kluczowego <code>return</code>. Słowo kluczowe <code>return</code> przerywa działanie funkcji i zwraca wartość umieszczoną po nim w kodzie. Typ zwracanej wartości musi być taki sam jak typ funkcji. Funkcja nie będąca funkjcą typu void musi zawsze zwracać wartość.

```c++
#include <iostream>

int suma(int x, int y) { return x + y; }

int main() {
  int a = 5;
  int b = 3;

  std::cout << suma(a, b) << std::endl;

  return 0;
}
```

### Funkcja typu void

Funkcje typu void nie zwracają żadnej wartości. Nie ma konieczności użycia słowa kluczowego <code>return</code>. Jeśli jednak zostanie użyte, to nie może być podana za nim żadna wartość. W kontekście funkcji typu void <code>return</code> służy jedynie do przerywania funkcji.

```c++
#include <iostream>

void wypisz_imie(string s) { std::cout << s << std::endl; }

int main() {
  std::string imie = "Karol";
  wypisz_imie(imie);

  return 0;
}
```

### Parametry z domyślną wartością

Domyślna wartość to taka, która zostanie użyta jeśli przy wywołaniu funkcji nie będzie podana wartość dla danego parametru.

```c++
#include <iostream>

int pomnoz(int a, int b = 3) { return a * b; }

int main() {
  int x = 2;
  int y = 7;

  std::cout << pomnoz(x, y) << std::endl; // Drugi argument ma wartosc y
  std::cout << pomnoz(x) << std::endl;    // Drugi argument ma domyslna wartosc

  return 0;
}
```

### Przekazywanie argumentów funkcji przez wartość i referencję

Istnieją dwa sposoby na przekazywanie argumentów do funkcji. Pierwszy to przekazywanie argumentów przez wartość, jeśli argumentem jest zmienna, to funkcja otrzymuje kopię jej wartości. Wszelkie zmianny na tą wartość w funkcji nie wpływają na oryginalną zmienną. Drugi sposób na przekazywanie argumentów to przekazywanie argumentów przez referencję. W tym przypadku funkcja otrzymuje referencję do oryginalnej zmiennej. Wszelkie zmiany na tą wartość w odbywają się bezpośrednio na oryginalnej zmiennej.

Przykład przekazywania argumentów przez wartość:

```c++
void pomnoz(int a, int b) { a = a * b; }
```

Przykład przekazywania argumentów przez referencję:

```c++
void pomnoz(int a, int b) { a = a * b; }
```

Uwaga: przez referencję możemy przekazywać jedynie l-wartości.

## L-wartości i r-wartości

Niektóre wartości w C++ istnieją jedynie w obrębie jednego wyrażenia i nie można ich adresować. Takie wartości zwane są r-wartościami (bo mogą występować po prawej stronie znaku =). Ich nadzbiorem są l-wartości. Wszystkie l-wartości są r-wartościami, ale nie wszystkie r-wartości są l-wartościami.

```c++
int main() {
  int i = 3;  // OK
  3 = i;      // Zle
  i + 4 = 20; // Zle

  return 0;
}
```

## Wskaźniki

Wskaźnik to zmienna, która przechowuje adres innej zmiennej. Dodatkowo przy pomocy wskaźników mamy możliwość modyfikowania zmiennych, których adresy przechowują wskaźniki.

<code>Typ_zmiennej_kt&oacute;rej_adres_przechowuje_wskaźnik \* nazwa_wskaźnika;</code>

```c++
#include <string>

int main() {
  // Deklaracja
  int *p1;
  double *p2;
  string *p3;

  int x = 4;
  double y = 3.5;
  std::string s = "napis";

  // Inicjalizacja
  // p1 = &y; // Zle. Niezgodne typy.
  p1 = &x;    // OK. Typy się zgadzają
  p2 = &y;
  p3 = &s;
  
  return 0;
}
```

### Dereferencja

Wyłuskanie wartości na, która znajduje się w zmiennej, na którą wskazuje nasz wskaźnik.
Używane nie tylko do odczytu, ale również zmiany wartości tej zmiennej.

<code>\*nazwa wskaźnika</code>

```c++
#include <iostream>
#include <string>

int main() {
  int x = 4;
  double y = 3.5;
  std::string s = "napis";

  int *p1 = &x;
  double *p2 = &y;
  std::string *p3 = &s;

  std::cout << "Wartosc zmiennej x: " << *p1 << std::endl;
  std::cout << "Wartosc zmiennej y: " * p2 << std::endl;
  std::cout << "Wartosc zmiennej s: " * p3 << std::endl;

  *p1 = 7;      // zmiana wartosci zmiennej x
  *p2 = 8.123;  // zmiana wartosci zmiennej y
  *p3 = "inny"; // zmiana wartosci zmiennej s

  std::cout << "Wartosc zmiennej x: " << *p1 << std::endl;
  std::cout << "Wartosc zmiennej y: " * p2 << std::endl;
  std::cout << "Wartosc zmiennej s: " * p3 << std::endl;

  return 0;
}
```

### Wskaźnik na wskaźnik

Operator \* pozwala również tworzyć wskaźniki przechowujące adresy innych wskaźników.

```c++
int main() {
  int i = 20;
  int *j = &i;
  int **k = &j;
  int ***l = &k;

  return 0;
}
```

### Wskaźnik na NULL

<code>NULL</code> to specjalna wartość wskaźnika symbolizująca wskazywanie na nieistniejący obiekt. Dzięki tej wartości możemy sygnalizować koniec listy połączonej lub poinformować o niemożliwości przydziału pamięci, lub otwarcia pliku (współcześnie preferuje się wyjątki).

W C, w zależności od implementacji <code>NULL</code> definiowany jest jako <code>0</code> lub <code>((void\*)0)</code>. W obu przypadkach używany jest dokładnie do tego samego.
Z uwagi na to, że <code>NULL</code> to po prostu zero, możemy w taki sposób sprawdzić, czy wskaźnik <code>wsk</code> nie jest wskaźnikiem na <code>NULL</code>:

```c++
  if (wsk != 0) {
  }
```

Na pierwszy rzut oka nie widać jednak, czy <code>wsk</code> jest wskaźnikiem, czy zwykłą liczbą. Z tego powodu lepiej jest użyć następującej konstrukcji:

```c++
  if (wsk != NULL) {
  }
```

C++ jest (prawie) nadzbiorem C, ale żyje własnym życie i ewoluuje w innym kierunku. <code>NULL</code> dalej istnieje w C++, ale oprócz niego mamy jeszcze jego młodszego brata <code>nullptr</code>. Pojawia się więc pytanie, po co wymyślono coś nowego, jeśli służy do tego samego co coś, co już istniało wcześniej. Otóż w C++ możemy przeciążać funkcje, tzn. definiować kilka funkcji z tą samą nazwą, ale różnymi typami parametrów.

```c++
void foo(void *wsk);
void foo(int liczba);
```

Która funkcja zostanie użyta, gdy wywołamy <code>foo(NULL)</code>? <code>NULL</code> to przecież zwykłe 0, więc zostanie użyta druga funkcja. Z tego powodu wprowadzono <code>nullptr</code>, który nigdy nie będzie zinterpretowany jako liczba.

Tak, więc jeśli piszesz kod w C++, to używaj <code>nullptr</code>.

### Stałe wskaźniki

Podobnie jak możemy deklarować zwykłe stałe, tak samo możemy mieć stałe wskaźniki - jednak są ich dwa rodzaje. Wskaźniki na stałą wartość:

```c++
  const int *a;
  int const *a; // rownowaznne do poprzedniego przykladu
```

oraz stałe wskaźniki:

```c++
  int *const b;
```

Słówko const przed typem działa jak w przypadku zwykłych stałych, tzn. nie możemy zmienić wartości wskazywanej przy pomocy wskaźnika.

W drugim przypadku słowo const jest tuż za gwiazdką oznaczającą typ wskaźnikowy, co skutkuje stworzeniem stałego wskaźnika, czyli takiego którego nie można przestawić na inny adres.

```c++
int main() {
  int zmienna = 10;
  const int stala = 15;
  int *const wskaznik_na_stala = &stala;
  int *const wskaznik_na_zmienna = &zmienna;
  const int *const wskaznik_na_stala_wskaznik = &wskaznik_na_stala;
  const int *const wskaznik_na_zmienna_wskaznik = &wskaznik_na_zmienna;

  return 0;
}
```

## Tablice

Jeśli zmienna to pudełko, to tablica to półka z pudełkami. Wszystkie pudełka na jednej półce przechowują dane tego samego typu. Do tworzenia tablic używamy nawiasów kwadratowych. Między nawiasy kwadratowe trafia liczba reprezentująca ilość elementów tablicy.

```c++
int tab[3]; // Polka z 3 pudelkami typu int.
```

W powyższym przykładzie miejsce w pamięci zostało zarezerwowane, ale pudełka są niezaincjalizowane. Co siedzi w środku? Śmieci.

Przykłady tablicy zadeklarowanej i zainicjalizowanej:

```c++
int tabA[3] = {7, 8, 11};
```

```c++
int tabB[] = {7, 8, 11};
```

Obie wersje są dopuszczalne.

### Wczytywanie i wypisywanie elemntów tablicy

```c++
#include <iostream>

const int n = 10;

int main() {

  int a[n];

  std::cout << "Podaj " << n << " elementów: " << std::endl;

  // wczytywanie
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  std::cout << "Twoja tablica: " << std::endl;

  // wypisywanie
  for (int i = 0; i < n; i++)
    std::cout << a[i] << std::endl;

  return 0;
}
```

Jeśli spróbujesz odnieść się do tablicy przy użyciu nieporawnego indeksu (mniejszego od 0 bądź większego lub równego długości tablicy) to zachowanie programu jest niezdefiniowane. Jeśli system operacyjny jest miły to w ten sposób możesz otrzymać przypadkowe liczby, które akurat siedzą w komórkach pamięci na lewo bądź prawo od twojej tablicy. W przeciwnym razie twój program po prostu przestanie działać (crash).

### Tablica jako wskaźnik

Za pomocą wskaźników można również odwoływać się do elementów tablicy. Nazwa tablicy to wskaźnik do pierwszego elementu tablicy. Jeśli <code>tab</code> to nazwa tablicy, to <code>tab[0]</code> oraz <code>\*tab</code> są synonimami.

```c++
#include <iostream>

int suma(int *tablica, int dlugosc) {
  int suma = 0;

  for (int i = 0; i < dlugosc; i++)
    suma += tablica[i];

  return suma;
}

int main() {

  int tab[] = {2, 4, 8, 16, 32};
  std::cout << suma(tab, 5) << std::endl;

  return 0;
}
```

Zwróć uwagę, że w powyższym przykładzie przekazujemy do funkcji długość tablicy. Kompilator nie wie, czy <code>int\* tablica</code> wskazuje na pojedynczą liczbę, czy na tablicę 10 liczb. Nie pomoże nawet operator <code>sizeof</code>, zwracający rozmiar danego obiektu lub typu podany w bajtach. Dla wskaźnika zwróci jedynie rozmiar typu, na który wskazuje wskaźnik.

### Arytmetyka wskaźników

Jeśli nazwa tablicy to wskaźnik do pierwszego elementu tablicy i elementy tablicy umiejscowione są jeden obok drugiego w pamięci komputera, to fajnie byłoby mieć możliwość przesuwania się między kolejnymi elementami tablicy za pomocą wskaźników. Taki mechanizm istnieje i zwie się arytmetyką wskaźników. Arytmetyka, dlatego że do wskaźników możemy dodawać i odejmować liczby całkowite. Jeśli wskaźnik <code>wsk</code> wskazuje nam pierwszy element tablicy <code>tab</code>, to <code>wsk+3</code> będzie wskazywał na czwarty element tablicy. Przy tej operacji należy być jednak bardzo ostrożnym, gdyż łatwo jest wyjść poza granice tablicy i spróbować odczytać zabroniony obszar pamięci.

```c++
#include <iostream>

int main() {
  int tab[] = {1, 2, 3, 4, 5};
  int *wsk = tab;

  std::cout << *wsk << std::endl;
  std::cout << *(wsk + 3) << std::endl;

  return 0;
}
```

### Dynamiczna alokacja pamięci

Aby skorzystać z pamięci sterty, używamy operatora <code>new</code> do alokacji (rezerwacji) miejsc w pamięci komputera dla elementów tablicy. Użycie samego <code>new</code> zarezerwuje pamięć dla pojedynczej zmiennej. Dla tablicy używam <code>new [liczba]</code>, gdzie <code>liczba</code> to długość tablicy, jaką chcemy stworzyć.
Gdy tablica nie jest nam już potrzebna, zarezerwowaną uprzednio pamięć uwalniamy przy pomocy <code>delete</code>. Podobnie jak z operatorem <code>new</code>, dla tablicy używamy <code>delete []</code>. Tym razem nie wstawiamy już żadnych liczb w nawiasy kwadratowe.

```c++
#include <iostream>

int main() {

  std::cout << "Podaj liczbę elemntów tablicy: " << std::endl;

  int n;
  std::cin >> n;

  int *tab = new int[n];

  std::cout << "Podaj " << n << " elementów: " << std::endl;

  for (int i = 0; i < n; i++)
    std::cin >> tab[i];

  std::cout << "Twoja tablica: " << std::endl;

  for (int i = 0; i < n; i++)
    std::cout << tab[i] << std::endl;

  delete[] tab;

  return 0;
}
```

Zmienne na stercie mogą żyć dłużej niż wskazujące na nie wskaźniki. Jeśli explicite nie uwolnimy dynamicznie zaalokowanej pamięci, to system operacyjny będzie dalej ją trzymał i bronił przed nadpisaniem. Jeśli nie żyje już nasz wskaźnik, to z jednej strony nie mamy w programie możliwości dostania się do zmiennych, które stworzyliśmy na stercie, a z drugiej marnujemy zasoby komputera, bo system operacyjny nie dopuszcza innych programów do tego obszaru pamięci. Taką sytuację nazywamy wyciekiem pamięci. Dla kilku zmiennych jest to nieodczuwalne, ale dla większych programów może szybko przeciążyć naszą maszynę.

### Tablica 2D

Tablice mogą mieć dowolną ilość wymiarów. Najczęściej będziemy jednak spotykać tablice jedno i dwuwymiarowe.

```c++
#include <iostream>

const unsigned int n = 3;
const unsigned int m = 4;

int main() {

  int a[n][m];

  std::cout << "Podaj " << n * m << " elementów: " << std::endl;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      std::cin >> a[i][j];

  std::cout << "Twoja tablica: " << std::endl;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      std::cout << a[i][j] << " ";
    std::cout << std::endl;
  }

  return 0;
}
```

Dla tablic dwuwymiarowych alokacja i dealokacja pamięci odbywa się przy pomocy pętli. Stwórzmy macierz o liczbie wierszy równej zmiennej <code>wysokość</code> i liczbie kolumn równej zmiennej <code>szerokość</code>:

```c++
#include <iostream>

int main() {

  double **macierz;
  int wysokosc, szerokosc;

  std::cin >> wysokosc >> szerokosc;

  // Alokacja
  macierz = new (double *)[wysokosc];

  for (int i = 0; i < wysokosc; i++)
    macierz[i] = new double[szerokosc];

  // Dealokacja
  for (int i = 0; i < wysokosc; i++)
    delete[] macierz[i];

  delete[] macierz;

  return 0;
}
```

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

Aby utworzyć obiekt stringa, możemy użyć konstruktor string(const char *s) lub string(const string &s).

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
| a.replace(int pos, int len, string b) | zastąpi len znaków z napisu a od indeksu pos przez napis b |
| a.substr(int pos, int len) | zwraca podnapis napisu a od indeksu pos o długości len |
| a.clear() | usuwa wszystkie znaki z napisu a |

## Operacje bitowe

Mamy możliwość wykonywania operacji na pojedynczych bitach.

### Bramka NOT

Zamienia zera na jedynki i na odwrót. Operator ~.

<table style="width:100%">
  <tr>
    <th>Wejście</th>
    <th>Wyjście</th>
  </tr>
  <tr>
    <td>0</td>
    <td>1</td>
</tr>
  <tr>
    <td>1</td>
    <td>0</td>
  </tr>
</table>

```c++
#include <bitset>
#include <iostream>

int main() {
  bitset<8> x(5);
  std::cout << x << std::endl;  // 00000101
  std::cout << ~x << std::endl; // 11111010

  return 0;
}
```

### Bramka OR

Jedynka gdy co najmniej jeden z bitów to jedynka, w przeciwnym razie zero. Operator |.

<table style="width:100%">
  <tr>
    <th>Wejście 1</th>
    <th>Wejście 2</th>
    <th>Wyjście</th>
  </tr>
  <tr>
    <td>0</td>
    <td>0</td>
    <td>0</td>
</tr>
  <tr>
    <td>0</td>
    <td>1</td>
    <td>1</td>
  </tr>
  <tr>
    <td>1</td>
    <td>0</td>
    <td>1</td>
  </tr>
<tr>
    <td>1</td>
    <td>1</td>
    <td>1</td>
  </tr>
</table>

```c++
#include <bitset>
#include <iostream>

int main() {
  int a = 7;
  int b = 5;

  std::cout << bitset<8>(a) << std::endl;     // 00000111
  std::cout << bitset<8>(b) << std::endl;     // 00000101
  std::cout << bitset<8>(a | b) << std::endl; // 00000111

  return 0;
}
```

### Bramka AND

Jedynka gdy oba bity to jedynki, w przeciwnym razie zero. Operator &.

<table style="width:100%">
  <tr>
    <th>Wejście 1</th>
    <th>Wejście 2</th>
    <th>Wyjście</th>
  </tr>
  <tr>
    <td>0</td>
    <td>0</td>
    <td>0</td>
</tr>
  <tr>
    <td>0</td>
    <td>1</td>
    <td>0</td>
  </tr>
  <tr>
    <td>1</td>
    <td>0</td>
    <td>0</td>
  </tr>
<tr>
    <td>1</td>
    <td>1</td>
    <td>1</td>
  </tr>
</table>

```c++
#include <bitset>
#include <iostream>

int main() {
  int a = 7;
  int b = 5;

  std::cout << bitset<8>(a) << std::endl;     // 00000111
  std::cout << bitset<8>(b) << std::endl;     // 00000101
  std::cout << bitset<8>(a & b) << std::endl; // 00000101

  return 0;
}
```

### Bramka XOR

Jedynka gdy bity różne, w przeciwnym razie zero. Operator ^.

<table style="width:100%">
  <tr>
    <th>Wejście 1</th>
    <th>Wejście 2</th>
    <th>Wyjście</th>
  </tr>
  <tr>
    <td>0</td>
    <td>0</td>
    <td>0</td>
</tr>
  <tr>
    <td>0</td>
    <td>1</td>
    <td>1</td>
  </tr>
  <tr>
    <td>1</td>
    <td>0</td>
    <td>1</td>
  </tr>
<tr>
    <td>1</td>
    <td>1</td>
    <td>0</td>
  </tr>
</table>

```c++
#include <bitset>
#include <iostream>

int main() {
  int a = 7;
  int b = 5;

  std::cout << bitset<8>(a) << std::endl;     // 00000111
  std::cout << bitset<8>(b) << std::endl;     // 00000101
  std::cout << bitset<8>(a ^ b) << std::endl; // 00000010

  return 0;
}
```

### Przesunięcia bitowe

Bity w lewo przesuwamy za pomocą operatora <code><<</code>. </br>
Bity w prawo przesuwamy za pomocą operatora <code>>></code>. </br>
Przesunięcie w lewo o 1 bit równoważne jest podzieleniu przez 2. </br>
Przesuniecie w prawo o 1 bit równoważne jest przemnożeniu przez 2. </br>

```c++
#include <bitset>
#include <iostream>

int main() {
  int a = 14;
  int b = 2;

  std::cout << bitset<8>(a) << std::endl;      // 00001110
  std::cout << bitset<8>(b) << std::endl;      // 00000010
  std::cout << bitset<8>(a << b) << std::endl; // 00111000
  std::cout << bitset<8>(a >> b) << std::endl; // 00000011

  return 0;
}
```

## Programowanie Obiektowe

Pisanie programów, w których w interakcje ze sobą wchodzą różne <b>obiekty</b>.

1. <b>Klasa</b> to szablon, w którym definiujemy <b>pola</b> (jakie dane mogą przechowywać obiekty danej klasy) oraz metody</b> (funkcje coś robiące z tymi polami).
2. Zastosowania obiektów danej klasy dane są przez dostępne metody.

Dlaczego?

1. Modularność: każda klasa ma jasno określony cel i wszystko, co z nim jest związane, zamknięte jest w tej klasie (przynajmniej w teorii).
2. Łatwość wielokrotnego użytku: możemy tworzyć nieskończenie wiele obiektów danej klasy, ograniczają nas jedynie fizyczne możliwości naszej maszyny.

```C++
class Prostokat {
  int a;
  int b;

public:
  Prostokat(int a, int b) {
    this->a = a;
    this->b = b;
  }

  int pole() { return a * b; }
};
```

### Konstruktor

Konstruktor jest funkcją, która jest wywoływana przy tworzeniu obiektu. Konstruktor ma taką samą nazwę jak klasa i nie posiada zwracanego typu, gdyż nigdy nie zwraca wartości. Istnieje wiele typów konstruktorów:

- konstruktor domyślny (nie ma argumentów)
- konstruktor z parametrami (argumenty są przekazywane do konstruktora)
- konstruktor kopiujący (kopiuje wartości z innego obiektu)
- konstruktor przenoszący (kopiuje wartości z innego obiektu i ustawia pola innego obiektu na domyślne wartości)

```C++
class Prostoka {
  int a;
  int b;

public:
  // konstruktor domyślny
  Prostokat() {
    a = 1;
    b = 1;
  }

  // konstruktor z parametrem
  Prostokat(int a, int b) {
    this->a = a;
    this->b = b;
  }

  // konstruktor kopiujący
  Prostokat(const Prostokat &p) {
    a = p.a;
    b = p.b;
  }

  // konstruktor przenoszący
  Prostokat(Prostokat &&p) {
    a = p.a;
    b = p.b;
    p.a = 1;
    p.b = 1;
  }
};
```

### Destruktor

Destruktor jest funkcją, która jest wywoływana przy usuwaniu obiektu. Destruktor ma taką samą nazwę jak klasa i nie posiada zwracanego typu, gdyż nigdy nie zwraca wartości.

```C++
class Prostokat {
  int a;
  int b;

public:
  Prostokat(int a, int b) {
    this->a = a;
    this->b = b;
  }

  ~Prostokat() { cout << "Destruktor" << endl; }
};
```

### Dostępność pól oraz metod

Istnieją trzy poziomy dostępu do pól oraz metod:

    - public
    - protected
    - private

Do pól i metod zdefiniowanych w sekcji <code>public</code> dostęp jest zawsze możliwy. Możemy się do nich odwołać z poziomu klasy, jak i z poziomu obiektu. W przypadku pól i metod zdefiniowanych w sekcji <code>private</code> dostęp jest możliwy tylko z poziomu klasy. Sekcja <code>protected</code> ma znaczenie przy dziedziczeniu. Klasy pochodne mają dostęp do pól i metod zdefiniowanych w sekcji <code>protected</code>, podobnie jak tych zdefiniowanych w sekcji <code>public</code>, ale nie mają dostępu do pól i metod zdefiniowanych w sekcji <code>private</code>.

```C++
class Prostokat {
  int a;
  int b;

public:
  Prostokat(int a, int b) {
    this->a = a;
    this->b = b;
  }

  int pole() { return a * b; }
};

int main() {

  Prostokat prostokat(2, 3);
  auto pole = prostokat.pole(); // Ok. Mamy dostęp do pól publicznych.
  auto a = prostokat.a;         // Źle. Nie mamy dostępu do pól prywatnych.

  return 0;
}
```

### Wskaźnik na obiekt

Podbnie jak tworzyliśmy wskaźniki na typy wbudowane, możemy tworzyć wskaźniki na obiekty. Do pól obiektu, na który wskazuje wskaźnik, możemy się odwoływać za pomocą konstrukcji <code>\*wsk.pole</code> lub <code>wsk->pole</code>.

```C++
#include <iostream>

class Foo {
  int bar;

public:
  Foo() { bar = 0; }

  void setBar(int bar) { this->bar = bar; }

  int getBar() { return bar; }
};

int main() {
  Foo foo;
  Foo *wsk = &foo;
  wsk->setBar(10);
  std::cout << wsk->getBar() << std::endl;
  return 0;
}
```

### Przeciążanie operatorów

C++ daje nam możliwość definiowania nowego znaczenia różnych operatorów dla definiowanych przez nas klas. W naszym przykładzie, definiujemy operator <code>+</code> dla klasy <code>Prostokat</code>.

    operator + (Prostokat &p1, Prostokat &p2) {
      return Prostokat(p1.a + p2.a, p1.b + p2.b);
    }
    operator + (Prostokat &p1, int a) {
      return Prostokat(p1.a + a, p1.b + a);
    }
    operator + (int a, Prostokat &p1) {
      return Prostokat(a + p1.a, a + p1.b);
    }

### Pola i metody statyczne

Istnieje specjalny typ pól oraz metod definiowanych w obrębie klasy, są to pola i metody statyczne. Tworzymy je umieszczając przed typem danej zmiennej lub przed typem zwracanym przez funkcję słowem kluczowym <code>static</code>. Do pól statycznych możemy się odwoływać za pomocą konstrukcji <code>\*klasa::pole</code> lub <code>klasa::pole</code>. Nie wymagają one utworzenia obiektu klasy. Wartości pól statycznych są współdzielone przez wszystkie obiekty klasy.

```C++
#include <iostream>

class Prostokat {
  static unsigned int liczbaProstokatow;

public:
  Prostokat() { liczbaProstokatow++; }

  static int getLiczbaProstokatow() { return liczbaProstokatow; }
};

unsigned int Prostokat::liczbaProstokatow = 0;

int main() {

  for (int i = 0; i < 10; i++) {
    Prostokat prostokat;
  }

  std::cout << Prostokat::getLiczbaProstokatow() << std::endl; // 10
  return 0;
}
```

### Funkcje zaprzyjaźnione

Istnieje specjalna klasa funkcji, tak zwane funkcje zaprzyjaźnione. Są to zewnętrzne funkcje, które mają dostęp do prywatnych pól i metod klasy. Przykład dla klasy <code>Prostokat</code>:

    friend void swap(Prostokat &p1, Prostokat &p2) {
      p1.a = p2.a;
      p1.b = p2.b;
    }

### Struktury

Struktura jest protoplastą klasy. W C struktury pozwalają na łączenie pod jedną nazwą danych różnego typu. W C nie ma jednak możliwości definiowania funkcji w obrębie struktury. C++ zmienia znaczenie tego pojęcia. W C++ struktury i klasy są dokładnie tym samym, z wyjątkiem tego, że domyślnie wszystkie pola struktur są publiczne, a pola klas prywatne (mamy więc możliwość definiowania metod).

Przykład w C:

```C
struct Foo {
  int bar;
};

int main() {
  struct Foo foo;
  foo.bar = 10;
  return 0;
}
```

W C nazwy struktur żyją we własnej przestrzeni nazw. Zmienną tego typu tworzymy, podając jako jej typ słowo kluczowe <code>struct</code>, nazwę struktury oraz nazwę zmiennej.

```C
struct Foo obiekt_foo;
```

W C++ możemy dalej używać tej składni, ale nie jest to konieczne. Możemy po prostu napisać:

```c++
Foo obiekt_foo;
```

### Pole bitowe

Możemy wskazać ile dokładnie bitów chcemy zarezerwować dla danego pola struktury.

```c++
#include <iostream>

struct Data {
  unsigned int Rok : 13;    // 2^13 = 8192
  unsigned int Miesiac : 4; // 2^4 = 16
  unsigned int Dzien : 5;   // 2^5 = 32
};

void wypiszDate(Data d) {
  std::cout << "Mamy dziś: " << std::endl;
  std::cout << d.Dzien << "-" << d.Miesiac << "-" << d.Rok << std::endl;
}

int main() {
  Data d;
  d.Rok = 2020;
  d.Miesiac = 7;
  d.Dzien = 18;

  wypiszDate(d);

  return 0;
}
```

### Unie

Unie to kolejny sposób reprezentacji danych w pamięci.

```c++
#include <iostream>

union Przyklad {
  int a;
  int b;
};

int main() {
  Przyklad unia;
  unia.a = 10;
  unia.b = 20;

  std::cout << unia.a << std::endl; // 20
  std::cout << unia.b << std::endl; // 20

  return 0;
}
```

Mogłoby się wydawać, że unie są tym samym co struktury. Różnica polega na tym, że w danej chwili tylko jedno pole unii może przechowywać wartość. Z tego powodu Unie są chudsze od struktur i unia zajmuje w pamięci tyle miejsca, ile wynosi rozmiar największego z jej pól.

## Dziedziczenie

Dziedziczenie to mechanizm, który pozwala na tworzenie nowych klas wykorzystujących część kodu z klasy już istniejącej. Pierwotna klasa zwana jest klasą bazową (bądź rodzicem), a klasa dziedzicząca jest klasą pochodną (bądź dzieckiem). W C++ dziedziczenie jest zdefiniowane przez zapisanie klasy dziedziczącej w nawiasach klamrowych po nazwie klasy bazowej. W naszym przykładzie, klasa <code>Prostokat</code> dziedziczy po klasie <code>Figura</code>.

```c++
class Figura {
  std::string nazwa;

  public:
    Figura(std::string nazwa) : nazwa(nazwa) {}
    void info() { std::cout << "Figura: " << nazwa << std::endl; }
    virtual double obliczPole() = 0;
};

class Prostokat : public Figura {
  int a;
  int b;

  public:
    Prostokat(int a, int b, std::string nazwa) : Figura(nazwa), a(a), b(b) {}
    void info() {
      Figura::info(); // wywolanie metody bazowej
      std::cout << "Prostokat: " << a << "x" << b << std::endl;
    }
    double obliczPole() { return a * b; }
}
```

W powyższym przykładzie <code>Prostokat</code> dziedziczy wszystkie pola i metody z klasy <code>Figura</code>. Przykładowo pole <code>nazwa</code> jest zdefiniowane w klasie <code>Figura</code>, ale posiadają je również obiekty klasy <code>Prostokat</code>. Dodatkowo w klasie <code>Prostokat</code> dodaliśmy nowe pola <code>a</code> i <code>b</code>. W ten sposób klasy pochodne poszerzają funkcjonalność klas bazowych. Inną rzeczą na którą możemy zwrócić uwagę jest to, że klasa metoda <code>info()</code> w klasie <code>Prostokat</code> zmienia definicję metody <code>info()</code> z klasy bazowej, wywołując implementację bazową, a następnie dodając do niej dodatkowe informacje.

### Typy dziedziczenia

Istnieją trzy podstawowe typy dziedziczenia:

1. publiczne (<code>public</code>)
2. prywatne (<code>private</code>)
3. chronione (<code>protected</code>)

W poniższej tabeli znajdują się informacje o dostępności pól oraz metod klasy bazoowej w klasie pochodnej ze względu na typ dziedziczenia:

| Typ Dziedziczenia | Prywatne pola i metody | Chronione pola i metody | Publiczne pola i metody |
| ---------------- | ---------------------- | ---------------------- | ---------------------- |
| publiczne | tak | tak | tak |
| chronione | nie | tak | tak (ale ich dostępność zmienia się w chronioną) |
| prywatne | nie | tak (ale ich dostępność zmienia się w prywatną) | tak (ale ich dostępność zmienia się w prywatną) |

### Polimorfizm

Polimorfizm to mechanizm umożliwiający nadawcy wysłania tej samej wiadomości do odbiorców różnych typów, bez wiedzy o konkretnym typie danego odbiorcy. Każdy odbiorca może odpowiedzieć na wiadomość we własny sposób. Odpowiedzi mogą, ale nie muszą się pokrywać. Polimorfizm jest często defniowany w kontekście dziedziczenia. Mamy klasę bazową zawierającą defnicję pewnej metody oraz klasy pochodne, każda klasa pochodna może mieć swoją własną implementację tej metody. Załóżmy teraz, że mamy kolekcję obiektów klasy bazowej, część z tych obiektów jest obiektami klas pochodnych. Wywołując tą samą metodę na każdym elemencie kolekcji, otrzymamy różne rezeltuty w zależności od dokładnego typu obiektu.

    class A {
      public:
        void foo() { std::cout << "A" << std::endl; }
    };

    class B : public A {
      public:
        void foo() { std::cout << "B" << std::endl; }
    };

    class C : public A {
      public:
        void foo() { std::cout << "C" << std::endl; }
    };

    std::vector<A*> obiekty { new A, new B, new C };

    for (auto obiekt : obiekty)
      obiekt->foo();

Ważnym problemem rozwiązanym przez polimorfizm jest zbędne rozgałęzienie kodu w celu sprawdzenia typu obiektu. Weźmy pod uwagę poniższy przykład:

    class Kaczka {
      public:
        void kwacz() { std::cout << "Kwaczę" << std::endl; }
    };

    class Pies {
      public:
        void szczekaj() { std::cout << "Szczekam" << std::endl; }
    };

    void foo(void* obiekt) {
      if (dynamic_cast<Kaczka*>(obiekt))
        dynamic_cast<Kaczka*>(obiekt)->kwacz();
      else if (dynamic_cast<Pies*>(obiekt))
        dynamic_cast<Pies*>(obiekt)->szczekaj();
    }

Dla dwóch klas takie rozgałęzienie wygląda niegroźnie. Co jednak jeśli zdecydujemy dodać nowe klasy? Co więcej w większym programie może się okazać, że podobne rozgałęzienia pojawiają się w wielu miejscach. Prostym rozwiązaniem jest zastosowanie polimorfizmu.

    class Zwierze {
      public:
        virtual void zachowanie() = 0;
    };

    class Kaczka : public Zwierze {
      public:
        void zachowanie() { std::cout << "Kwaczę" << std::endl; }
    };

    class Pies : public Zwierze {
      public:
        void zachowanie() { std::cout << "Szczekam" << std::endl; }
    };

    void foo(Zwierze* obiekt) {
      obiekt->zachowanie();
    }

### Metody wirtualne

Jeśli mamy wskaźnik typu klasy bazowej, wskazujący na obiekt klasy pochodnej to jeśli wywołamy przy jego pomocy metodę zdefiniowaną w obu klasach, to wywołana zostanie implementacja klasy bazowej.

    class A {
      public:
        void foo() { std::cout << "A" << std::endl; }
    };

    class B : public A {
      public:
        void foo() { std::cout << "B" << std::endl; }
    };

    B b;
    A* wsk = &b;
    wsk->foo(); // wyswietli "A"


Aby nie uchronić się przed tym nieoczekiwanym zachowaniem musimy użyć słowa kluczowego <code>virtual</code> przed nazwą metody w klasie bazowej.

    class A {
      public:
        virtual void foo() { std::cout << "A" << std::endl; }
    };

    class B : public A {
      public:
        void foo() { std::cout << "B" << std::endl; }
    };

    B b;
    A* wsk = &b;
    wsk->foo(); // wyswietli "B"

Uwaga: Destruktor to też funkcja. Jeśli chcemy by przy usuwaniu obiektu została wywołana implementacja destruktora w klasie pochodnej musimy użyć słowa kluczowego <code>virtual</code> przed nazwą destruktora w klasie bazowej.

### Klasy abstrakcyjne

W C++ istnieje możliwość tworzenia klas, które zawierają jedynie deklaracje metod, ale same ich nie implementują. Co więcej, mogą one definiować metody, których implementacje w klasach pochodnych jest wymagana. Takie metody zwane czysto wirtualnymi, mają specjalną składnię, mianowicie zaczynają się od słowa kluczowego <code>virtual</code>, a kończą się przyrównaniem do zera.

    class A {
      public:
        virtual void foo() = 0;
    };

    class B : public A {
      public:
        void foo() { std::cout << "B" << std::endl; }
    };

    B b;
    A* wsk = &b;
    wsk->foo(); // wyswietli "B"

W powyższym przykładzie klasa A jest klasą abstrakcyjną. Istnieje tylko jeden warunek, aby klasa była uznana za klasę abstrakcyjną. Taka klasa musi zawierać przynajmniej jedną metodę czysto wirtualną. Co zmienia konwersja metody wirtualnej na czysto wirtualną?

1. Nie można utworzyć obiektu klasy abstrakcyjnej.
1. Klasy pochodne muszą zaimplementować metodę czysto wirtualną.

Klasy czysto abstrakcyjne to klasy abstrakcyjne składające się wyłącznie z metod czysto wirtualnych i nieposiadające żadnych pól.

## Zaawansowne wskaźniki

Poza zwykłymi, surowymi wskaźnikami istnieją jeszcze inne, bardziej zaawansowane typy wskaźników.

### Wskaźniki na funkcje

Wskaźniki mogą wskazywać nie tylko na zmienne i obiekty, ale także na funkcje. Dzięki temu możemy na przykład przekazać jedną funkcję jako argument do innej funkcji.

```c++
#include <iostream>

void funkcja(void (*f)(int), int a) { f(a); }

void zwieksz(int a) { std::cout << a + 1 << std::endl; }

void zmniejsz(int a) { std::cout << a - 1 << std::endl; }

int main() {
  funkcja(zwieksz, 10);
  funkcja(zmniejsz, 10);
  return 0;
}
```

### Wskaźniki do składowych klasy

Możemy wskazywać na składowe klasy. Przykładowo jeśli mamy obiekt <code>foo</code> klasy <code>Foo</code>, mającą pola <code>x</code> i <code>y</code> to możemy wskazać na <code>foo.x</code> i <code>foo.y</code>.

```c++
#include <iostream>

class Foo {
public:
  int x;
  int y;

  Foo(int x, int y) : x(x), y(y) {}
};

int main() {
  Foo foo(10, 20);

  // wskazniki na zwykle pola
  int *x = &foo.x;
  int *y = &foo.y;
  *x = 100;
  *y = 200;
  std::cout << foo.x << std::endl;
  std::cout << foo.y << std::endl;

  return 0;
}
```

### Podsumowanie wskaźników

| Kod                                  | Opis                                                           |
| ------------------------------------ | -------------------------------------------------------------- |
| <code>int \*wsk;</code>              | wskaźnik wskazujący na zmienną typu int                        |
| <code>int \*\*wskNaWsk;</code>       | wskaźnik wskazujący na wskaźnik wskazujący na zmienną typu int |
| <code>int (\*wskNaTablice)[];</code> | wskaźnik wskazujący na tablicę zmienną typu intów              |
| <code>int (\*wskNaFunkcje)();</code> | wskaźnik wskazujący na funkcję zwracającą zmienną typu int     |
| <code>int \*tab[];</code>            | tablica wskaźników na zmienną typu int                         |
| <code>int \*fun();</code>            | funkcja zwracająca wskaźnik na zmienną typu int                |

### Sprytne wskaźniki

W C++11 wprowadzono tak zwane sprytne wskaźniki. Wskaźniki te to nakładki na znane nam surowe wskaźniki, poszerzone o dodatkowe funkcjonalności. Przykładowo sprytne wskaźniki w momencie śmierci (destruktor) uwalniają pamięć sterty zarezerowaną dla wskazywanych przez nie obiektów.

#### unique_ptr

Dzięki niemu, mamy pewność że zarezerwowana pamięć zostanie zwolniona przy gdy program wyjdzie poza zakres życia wskaźnika. Programista nie ma możliwości popełniania błędów, wynikających z nie użycia operatora delete. Pamięć zwalniana jest automatycznie.

Nie oznacza to jednak, że nie ma żadnej możliwości na popełnienie błędu przy pracy z unique_ptr. Jeśli utworzymy dwa obiekty unique_ptr poprzez przekazanie do konstruktora tego samego surowego wskaźnika, to nasz program zostanie zakończony z komunikatem o double free.

    int *surowyWsk = new int;

    std::unique_ptr<int> unikalnyWsk1(surowy_wsk);
    std::unique_ptr<int> unikalnyWsk2(surowy_wsk);

Nawet jeśli nie popełnimy tak fatalnego, ale dość oczywistego błędu, to dalej istnieją inne błędy na które musimy uważać. Po utworzeniu obiektu unique_ptr poprzez przekazanie do konstruktora surowego wskaźnika, nigdy nie powinniśmy zwalniać pamięci poprzez operator delete.

Bezpieczniejszą opcją tworzenia obiektu unique_ptr jest std::make_unique. Jest to funkcja zwracająca unique_ptr dla podanego typu. Załóżmy, że mamy klasę <code>Foo</code> z dwoma polami typu double <code>x</code> i <code>y</code>.

	std::unique_ptr<Foo> unikalnyWsk = std::make_unique<Foo>(1.0, 2.0);

Dlaczego te wskaźniki zwane są unikalnymi? Otóż, nie mamy możliwości inicalizacji obiektów uniqe_ptr poprzez przypisanie im wartości innego obiektu tego samego typu. Tzn. obiekty uniqe_ptr nie są kopiowalne.

	std::unique_ptr<Foo> unikalnyWsk1(new Foo);       // Ok
	std::unique_ptr<Foo> unikalnyWsk2 = unikalnyWsk1; // Error

Mamy za to możliwość przenoszenia jednego obiektu uniqe_ptr do drugiego.

	std::unique_ptr<Foo> unikalnyWsk1(new Foo);                  
	std::unique_ptr<Foo> unikalnyWsk2 = std::move(unikalnyWsk1);

#### shared_ptr

Jeśli przyrównać uniqe_ptr do wozu pancernego, to shared_ptr jest czołgiem. Działa tak samo jak uniqe_ptr, ale daje nam więcej opcji. Możemy zarówno przenosić, jak i kopiować obiekty shared_ptr. Mamy też możliwość sprawdzenia ile aktualnie obiektów shared_ptr wskazuje na dany obiekt.

	std::shared_ptr<Foo> dzielonyWsk1(new Foo);       // Ok
	std::shared_ptr<Foo> dzielonyWsk2 = dzielonyWsk1; // Ok

Aby sprawdzić ile obiektów wskazuje na dany obiekt, możemy użyć metody <code>use_count()</code>.

	std::cout << dzielonyWsk.use_count() << std::endl;

#### weak_ptr

Innym typem sprytnych wskaźników jest weak_ptr. Jest to wskaźnik, który nie ma praw własności do żadnego obiektu. Zamiast tego możemy przypisać mu wartość sprytnego wskaźnika innego typu i za jego pomocą możemy sprawdzić, czy dane na które wskazuje inny wskaźnik dalej istnieją.

```c++
#include <iostream>
#include <memory>

void czy_istnieje(std::weak_ptr<int> wsk) {
  if (auto tmp = wsk.lock())
    std::cout << "Obiekt istnieje: " << *tmp << std::endl;
  else
    std::cout << "Obiekt nie istnieje" << std::endl;
}

int main() {
  std::shared_ptr<int> dzielonyWsk(new int(42));

  std::weak_ptr<int> slabyWsk = dzielonyWsk;
  czy_istnieje(slabyWsk);
  dzielonyWsk.reset();
  czy_istnieje(slabyWsk);

  return 0;
}
```

## Przeciążanie
Przeciążanie odnosi się do sytuacji gdzie w kodzie używamy tej samej nazwy dla kilku różnych definicji.

### Przeciążanie funkcji

W poniższym przykładzie, mamy trzy funckje, które są rozróżnialne dla kompilatora. W zależności od tego jaki będzie typ zmiennej przekazanej do funkcji, zostanie wywołana odpowiednia funkcja.

```c++
#include <iostream>

// funkcja1
void f(int a) { std::cout << "int" << std::endl; }

// funkcja2
void f(double a) { std::cout << "double" << std::endl; }

// funkcja3
void f(int a, double b) { std::cout << "int, double" << std::endl; }

int main() {
  int a = 10;
  double b = 10.0;
  f(a);    // wywolana zostanie funkcja1
  f(b);    // wywolana zostanie funkcja2
  f(a, b); // wywolana zostanie funkcja3
  return 0;
}
```
Przy przeciążaniu funkcji należy być szczególnie ostrożnym w przypadku domyślnych wartości parametrów. Jeśli do powyższego przykładu dodalibyśmy nową funkcję o następującej definicji:

    // funkcja4
    void f(int a, double b = 10.0) { std::cout << "int, double" << std::endl; }

To w następującym przypadku mielibyśmy konflikt z funkcjami 1 i 3:

    f(10);       // konflikt między funkcjami 1 i 4
    f(10, 10.0); // konflikt między funkcjami 3 i 4

### Przeciążanie operatorów

Innym typem przeciążania jest przeciążanie operatorów. W C++ możemy przeciążyć operator przypisania, operatora dodawania, operatora mnożenia i wiele innych. To znaczy możemy dla różnych symboli zdefiniować całkowicie nowe zachowanie.

```c++
class Foo {
public:
  Foo() { std::cout << "Konstruktor" << std::endl; }
  Foo(const Foo &foo) { std::cout << "Konstruktor kopiujący" << std::endl; }
  Foo &operator=(const Foo &foo) {
    std::cout << "Operator przypisania" << std::endl;
    return *this;
  }
  Foo operator+(const Foo &foo) {
    std::cout << "Operator dodawania" << std::endl;
    return *this;
  }
  Foo operator*(const Foo &foo) {
    std::cout << "Operator mnożenia" << std::endl;
    return *this;
  }
};

int main() {
  Foo foo1;
  Foo foo2;
  foo1 = foo2;
  foo1 + foo2;
  foo1 *foo2;
  return 0;
}
```

## Konwersje

Zarówno w C, jak i w C++ istnieją mechanizmy umożliwiające konwersje wartości z jednego typu na inny.

### Rzutowanie

W C możemy jawnie dokonać konwersji wartości z jednego typu na inny za pomocą rzutowania. Ogólny schemat to:

       (typ) wartość;

Przykład:

       int a = 10;
       double b = (double)a;

 W powyższym przykładzie wszystko działa jak należy. Nie ma problemu z konwersją z typu int na typ double. W wielu innych przypadkach taki zabieg może okazać się niebezpieczny. W szczególności gdy bawimy się wskaźnikami na void. Czasami musimy ich użyć, jest jedyny sposób na osiągnięcie polimorfizmu w C. Przykładowo funkcje qsort() i bsearch() pracują z wskaźnikami na void, dzięki temu możemy przekazać do nich tablice dowolnego typu. Niebezpieczeństwo pojawia się gdy chemy rzutować wskaźnik na void z powrotem na inny typ. Nic nie powstrzymuje nas przed konwersją na zły typ i nieoczekiwanymi rezultatami.

        void *ptr = malloc(sizeof(int)); // zaalokowanie pamięci dla typu int
        char *ptr2 = (char *)ptr;        // rzutowanie na inny typ
        *ptr2 = 'a';
        printf("%c\n", *ptr2);           // wyswietlenie znaku 'a'
        free(ptr); 


### Konwersja statyczna

Konwersja statyczna <code>static_cast</code> jest bardzo podobna do rzutowania, z tym że jej poprawność jest sprawdzana na etapie kompilacji. Jeśli konwersja nie jest możliwa, kompilator wygeneruje błąd.

        int a = 10;
        double b = static_cast<double>(a);

### Konwersja dynamiczna

Konwersje dynamiczne <code>dynamic_cast</code> są bardziej ograniczone niż konwersje statyczne, a ich poprawność jest sprawdzana na etapie wykonania. Dynamicznie możemy konwertować jedynie wskaźniki i referencje do obiektów klas polimorficznych.

Popularnym zastosowaniem dynamicznego rzutowania jest sprawdzenie czy dany obiekt jest instacją jednej z klas pochodnych.

```c++
#include <iostream>
#include <vector>

class A {
  virtual void vf() {}
};
class B : public A {};
class C : public A {};
int main() {

  std::vector<A *> v{new B, new C};

  for (auto a : v) {
    if (auto b = dynamic_cast<B *>(a)) {
      std::cout << "B" << std::endl;
    } else if (auto c = dynamic_cast<C *>(a)) {
      std::cout << "C" << std::endl;
    }
  }
  return 0;
}
```

### Konwersja wymuszona

Konwersja wymuszona <code>reinterpret_cast</code> ma dość niszowe zastosowania i nie jest zalecana. Działa jedynie dla konwersji między różnymi wskaźnikami. Jest ona używana do konwersji typów, które nie są możliwe do wykonania za pomocą konwersji statycznej lub dynamicznej. Jej poprawność nie będzie sprawdzana i sami musimy wiedzieć czy konwersja jest możliwa.

    void convert(ObscureType *obscure, FamiliarType *familiar) {
        familiar = reinterpret_cast<FamiliarType *>(obscure);
    }

## Lambdy

W C++ mamy możliwość tworzenia funkcji w obrębie innych funkcji, a nawet w momencie wywołania funkcji w samym argumencie. Takie funkcje nie mają nazw i nie muszą być uprzednio zadeklarowane. Te funkcje zwane są lambdami.

Ogólna postać funkcji anonimowej jest następująca:

    [domknięcie](parametry) -> typ { ciało }

W nawiasach okrągłych mamy listę parametrów, która działa tak samo jak dla zwykłych funkcji. W wielu przypadkach możemy pominąć strzałkę wraz typem zwracanym, gdyż kompilator jest w stanie wydedukować typ na etapie kompilacji.

Przykład funkcji lambda przyjmującej dwa argumenty i zwracającej wartość typu int:

    [](int a, int b) { return a + b; } 

Jeśli chcemy mieć bezpośredni dostęp do zmiennych z zewnętrznego kontekstu, możemy użyć <code>&</code> w nawiasie kwadratowym. Wtedy nie musimy przekazywać takich zmiennych jako argumentów funkcji, a mimo to możemy ich użyć w ciele lambdy.

    int x = 10;
    [&](int a, int b) { return x * (a + b); } 

Możemy lambdę przypisać do nazwy i użyć ją wielokrotnie w obrębie kontekstu, w którym została zdefiniowana.

    int x = 10;

    auto nazwaFunkcji = [&](int a, int b) { return x * (a + b); };

    nazwaFunkcji(10, 10); // 200
    nazwaFunkcji(5, 2);   // 70

## Szablony

Szablony umożliwiają tworzenie klas i funkcji, bez konieczności precyzowania typów argumentów i zwracanych wartości. Zamiast konkretnego typu jak char, int, czy bool, możemy użyć typu uogólnionego o dowolnej nazwie, np. T. 

### Szablon funkcji

Przykładowo możemy mieć funkcję max2(T arg1, T arg2) zwracającą największą z dwóch wartości typu T. Pod ogólnym typem T może kryć się dowolny typ dla, którego zdefiniowane jest porównanie między dwoma elementami.

    template <typename T> T max2(T arg1, T arg2) {
      return arg1 > arg2 ? arg1 : arg2;
    }

    max2(10, 20);     // 20
    max2(16.2, 3.14); // 16.2
    max2('a', 'b');   // 'b'

Kompilator jest w stanie wywnioskować typy argumentów na podstawie podanych wartości. Jeśli  typy argumentów będą niezgodne, kompilator zgłosi błąd. Kompilator również zgłosi błąd jeśli operacja umieszczona w ciele funkcji nie jest zdefiniowana dla typu przekazanych przez nas argumentów.

### Szablon klasy

Podobnie jak dla funkcji, możemy mieć jedną definicję klasy i decydować o typie pól w momencie tworzenia obiektu. 

    template <typename T> class Foo {
      T x;

    public:
      Foo(T x) : x(x) {
        std::cout << "Utworzono obiekt Foo o typie pola x: " << typeid(T).name()
                  << std::endl;
      }
      T getX() { return x; }
    };

## Wyjątki

Błąd - wszystko co uniemożliwia poprawne działanie programu.
Sygnał - informacja przesyłana do procesu.
Wyjątek - mechanizm języka programowania umożliwiający prgoramiście, że dana funkcja nie może poprawnie kontynuować działania.

Błędy składniowe – użycie kodu niezgodnego z konwencjami danego języka programowania. wykrywane w czasie kompilacji.
Błędy logiczne – kod, który miał zostać uruchomiony nie jest uruchomiony, błędy w ifach, zła kolejność wykonywania operacji
Błędy semantyczne – program został błędnie zakodowany, nie robi tego co powinien robić

Problemy z pamięcią:

- Przepełnienie stosu (rekurencja, rozmiar zmiennych statycznych)
- rozmiar zmiennych

### Działanie wyjątków

Wyrzucenie wyjątku powoduje przerwanie działania funkcji, w której wystąpiło wyrzucenie.
Istnieje możliwość obsłużenia wyjątku przy pomocy bloku try-catch. Catch musi sprecyzować typ wyjątku, który ma zostać obsłużony. Jeśli typ pokrywa się z typem wyjątku, to blok catch zostanie wykonany.

```c++
#include <iostream>

void funkcja() { throw std::runtime_error("Wyjatek"); }

int main() {
  try {
    funkcja();
  } catch (std::runtime_error &e) {
    std::cout << "Wyjatek: " << e.what() << std::endl;
  }

  std::cout << "Zycie toczy sie dalej" << std::endl;

  return 0;
}
```

## STL

STL (Standard Template Library) jest biblioteką, która implementuje wiele przydatnych funkcji, algorytmów i struktur danych. W skład STL wchodzą między innymi:

    <vector>
    <list>
    <map>
    <set>
    <queue>
    <stack>
    <algorithm>
    <iterator>
    <memory>

### Kolekcje

Kolekcje to implementacje struktur danych wraz z wieloma funkcjami, przeznaczonymi do pracy z nimi.

1. unordered_map

Kontener unordered_map implementuje tablicę mieszającą.

| operacja | złożoność czasowa |
|---|---|
| wyszukiwanie | O(1) |
| wstawianie | O(1) | 
| usuwanie | O(1) | 

2. map

Kontener map implementuje drzewo czerwono-czarne.

| operacja | złożoność czasowa |
|---|---|
| wyszukiwanie | O(log n) |
| wstawianie | O(log n) | 
| usuwanie | O(log n) | 

3. priority_queue

Kontener priority_queue implementuje kopiec.

| operacja | złożoność czasowa |
|---|---|
| wstawianie | O(log n) |
| zdejmowanie | O(log n) | 
| wierzchołek | O(1) | 

4. list

Kontener list implementuje listę dwukierunkową.

| operacja | złożoność czasowa |
|---|---|
| wyszukiwanie | O(n) |
| wstawianie | O(n) | 
| usuwanie | O(n) | 

5. vector

Kontener vector implementuje tablicę dynamiczną.

| operacja | złożoność czasowa |
|---|---|
| dostawianie na koniec | O(1) |
| usuwanie z końca | O(1) | 
| dostawianie (ogólnie) | O(n) | 
| usuwanie (ogólnie) | O(n) | 
| wyszukiwanie | O(n) | 

6. unordered_set

Struktura unordered_set implementuje tablicę mieszającą.

| operacja | złożoność czasowa |
|---|---|
| wyszukiwanie | O(1) |
| wstawianie | O(1) | 
| usuwanie | O(1) | 

7. set

Struktura set implementuje drzewo czerwono-czarne.

| operacja | złożoność czasowa |
|---|---|
| wyszukiwanie | O(log n) |
| wstawianie | O(log n) | 
| usuwanie | O(log n) | 

### Iteratory

Iteratory to konstrukcje, które umożliwiają jednolitą iterację po elementach kolekcji. Dzięki temu nie musimy zamiast poznawać osobne mechanizmy dla każdej kolekcji, możemy zawsze użyć iteratorów.

W poniższym przykładzie wykorzystano iterator do wyświetlenia elementów wektora:

```c++
#include <iostream>
#include <string>
#include <vector>

int main() {
  vector<string> v;
  v.push_back("ala");
  v.push_back("ma");
  v.push_back("kota");

  for (auto it = v.begin(); it != v.end(); ++it)
    std::cout << *it << std::endl;

  return 0;
}
```

Iterator do pierwszego elementu kolekcji to:

    kontener.begin()

Iterator do następnego elementu za ostanim to:

    kontener.end()

Wartość na którą wskazuje iterator <code>it</code> to:

    *it

Dodanie elementu poprzez iterator <code>it</code>:

    it = kontener.insert(it, "ala");

Usunięcie elementu poprzez iterator <code>it</code>:

    it = kontener.erase(it);

### Algorytmy

Biblioteka <code>algorithm</code> zawiera wiele funkcji, które mogą być użyte do pracy z kolekcjami. Przyjrzymy się teraz kilku przykładom.

#### sort()

Dzięki funkcji <code>sort()</code> możemy posortować częściowo lub całkowicie kolekcję. Pierwszym argumentem jest iterator od którego mamy zacząć sortowanie, a drugim to iterator na którym mamy zakończyć sortowanie.

```c++
#include <vector>
#include <algorithm>

int main() {

  std::vector<int> wektor{8, 3, 5, 1, 2, 4, 6, 7};
  auto kopia = wektor;

  std::sort(wektor.begin(), wektor.begin() + 3); // posortowane zostana pierwsze 3 elementy
  std::sort(kopia.begin(), kopia.end());         // posortowane zostana wszystkie elementy

  return 0;
}
```

### find()

Funkcja <code>find()</code> zwróci nam iterator odpowiadający szukanemu elementowi. Pierwszym argumentem jest iterator od którego mamy zacząć szukanie, drugim jest iterator na którym mamy zakończyć szukanie, a trzecim szukany element.

```c++
#include <vector>
#include <algorithm>

int main() {

  std::vector<int> wektor{8, 3, 5, 1, 2, 4, 6, 7};

  auto it = std::find(wektor.begin(), wektor.end(), 3);

  if (it != wektor.end())
    std::cout << "Znaleziono element o wartości 3" << std::endl;

  return 0;
}
```

### for_each()

Jeśli chcemy jakąś operację wykonać na każdym elemencie kolekcji, możemy użyć funkcji <code>for_each()</code>. Pierwszym argumentem jest iterator od którego mamy zacząć wykonywanie operacji, drugim jest iterator na którym mamy zakończyć wykonywanie operacji, a trzecim jest funkcja, która będzie wywoływana na każdym elemencie.

```c++
#include <vector>
#include <algorithm>

int main() {

  std::vector<int> wektor{8, 3, 5, 1, 2, 4, 6, 7};
  std::for_each(wektor.begin(), wektor.end(), [](int &x) { x *= 2; });
  // wynik: [16, 6, 10, 2, 4, 8, 12, 14]

  return 0;
}
```

## Praca z plikami

W C nazwy funkcji używanych do pracy z plikami zaczynają się od litery <i>f</i>, są to np. <code>fopen()</code>, <code>fread()</code> i <code>fclose()</code>. Struktura <code>FILE</code> używana jest jako uchwyt do pliku, za pomocą którego wykonujemy różne operacje na pliku.

```c
#include <stdio.h>

int main(int argc, char **argv) {
  FILE *plik;

  // otwieramy plik
  plik = fopen("plik.txt", "r");

  // sprawdzamy, czy plik zostal otwarty
  if (plik == NULL) {
    printf("Nie udalo sie otworzyc pliku");
    return 1;
  }

  // wczytujemy zawartosc pliku
  char znak;
  while ((znak = fgetc(plik)) != EOF) {
    printf("%c", znak);
  }

  // wykonujemy operacje na pliku
  fputs("test", plik);

  // zamykamy plik
  fclose(plik);

  return 0;
}
```

W C++ możemy używać funkcji z biblioteki <code>fstream</code>, która jest bardziej zaawansowaną wersją funkcji znanych nam z biblioteki <code>stdio.h</code>.

```c++
#include <fstream>
#include <iostream>

int main() {
  std::ifstream plik;

  // otwieramy plik
  plik.open("plik.txt", std::ios::in);

  // sprawdzamy, czy plik zostal otwarty
  if (!plik.is_open()) {
    std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
    return 1;
  }

  // wczytujemy zawartosc pliku
  char znak;
  while (plik.get(znak)) {
    std::cout << znak;
  }

  // wykonujemy operacje na pliku
  plik << "test";

  // zamykamy plik
  plik.close();

  return 0;
}
```

## C vs Cpp

* C został stworzony w 1970 roku, a C++ w 1985 roku.
* C++ jest (niemalże) nadzbiorem C. Kompilatory C++ prawie zawsze poradzą sobie z kodem napisanym w czystym C.

### Dyrektywy #include

W C załączając biblioteki standardowe dodajemy rozszerzenie '.h' po nazwie biblioteki. W C++ nie musimy dodawać rozszerzeń.

Przykłady załączania bibliotek w C:

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

Przykłady załączania bibliotek w C++:

    #include <iostream>
    #include <vector>
    #include <string>

Przykłady załączania bibliotek z C w C++:

    #include <cstdlib>
    #include <cstring>
    #include <cmath>

### Słowa kluczowe

Przykłady słów kluczowych wykorzystywanych zarówno w C i C++:

    auto
    break
    case
    char
    const
    continue
    default
    do
    double
    else
    enum
    extern
    float
    for
    goto
    if
    int
    long
    register
    return
    short
    signed
    sizeof
    static
    struct
    switch
    typedef
    union
    unsigned
    void
    volatile
    while

Przykłady słów kluczowych używanych jedynie w C++:

    static_cast
    dynamic_cast
    const_cast
    reinterpret_cast
    bool
    explicit
    namespace
    protected
    throw
    using
    catch
    false
    new
    public
    true
    virtual
    class
    friend
    operator
    template
    try
    delete
    inline
    private
    this
    typename

### Funkcjonalności dostępne jedynie w C++

* Przeciążanie funkcji
* Przekazywanie zmiennych przez referencję
* Inicjalizacja zmiennych przy pomocy nawiasów okrągłych
	int x(5);
* Domyślne wartości dla parametrów funkcji

### Dlaczego C?

* Minimalny język zawierający wszystko czego potrzebujesz do napisania dowolnego programu, bez zbędnych abstrakcji.
* Mechanizmy języka są niezależne od siebie nawzajem.
* Mała standardowa biblioteka.
* Napotkane problemy możesz zawsze rozwiązać samemu, dokładnie tak jak chcesz. Nie ma potrzeby dolepiania tysiąca zewnętrznych bibliotek i frameworków.
* Jesteś kowalem własnego losu. Masz niemalże nieograniczoną kontrolę nad pamięcią wykorzystywaną przez twój program. Możesz zadecydować o tym, skąd pamięć jest brana i jak jest używana.
* Niedościgniona stabilność. Programy skompilowane w latach 80'tych działają po dziś dzień.

### Dlaczego C++?

* C++ jest twoim przyjacielem, jeśli chcesz używać abstrakcji niedostępnych w C.

## Bibliografia

- https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md
- http://www.doc.ic.ac.uk/~wjk/C++Intro/index.html
- https://www.cs.fsu.edu/~myers/cop3014/
- https://rules.sonarsource.com/cpp/RSPEC-5184
- https://pythontutor.com/cpp.html#mode=edit
- https://beej.us/guide/bgc/html/split/
- https://beej.us/guide/bgnet/html/
- https://beej.us/guide/bgipc/html/multi/index.html
- https://graphics.stanford.edu/~seander/bithacks.html
- https://hackingcpp.com/index.html
- https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1226/
- https://eel.is/c++draft/
- https://www.cs.cmu.edu/~ab/15-123S09/annotatedNotes/

