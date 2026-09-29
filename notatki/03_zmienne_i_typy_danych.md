# Zmienne i typy danych

Preprocesor przygotowuje tekst programu, a kompilator sprawdza, czy jego instrukcje mają poprawną składnię i znaczenie. Żeby ocenić znaczenie wyrażenia, kompilator musi wiedzieć, jakiego rodzaju wartości w nim występują. Tę informację opisuje typ.

Zmienna to nazwana część programu, w której przechowujemy wartość. Typ mówi, jakie wartości może przyjmować dana zmienna i jakie działania mają dla niej sens. Na przykład liczby całkowite można dodawać, a wartość logiczna opisuje warunek jako prawdziwy albo fałszywy.

Przykłady w tej notatce są w C++. Dlatego pojawiają się nagłówki `<iostream>` do wypisywania oraz `<string>` do tekstu. C ma wiele wspólnych typów podstawowych, ale nie zawiera klasy `std::string`.

## Deklaracja, inicjalizacja i przypisanie

Deklaracja podaje typ i nazwę zmiennej. Inicjalizacja nadaje jej pierwszą wartość. Późniejsza zmiana wartości to przypisanie. Te czynności są powiązane, ale oznaczają różne etapy pracy ze zmienną.

```cpp
int liczba{10}; // deklaracja zmiennej typu int i jej inicjalizacja
liczba = 13;    // przypisanie nowej wartości już istniejącej zmiennej
```

Nawiasy klamrowe w `int liczba{10};` są formą inicjalizacji w C++. Dla początkujących są użyteczne, bo kompilator odrzuca w nich część przypadkowych konwersji, które mogłyby utracić dane.

Można też rozdzielić deklarację od późniejszego przypisania:

```cpp
int wynik;       // deklaracja bez podanej wartości początkowej
wynik = 5 + 7;   // pierwsze przypisanie wartości
```

Lokalna zmienna liczbowa, która nie została zainicjalizowana, nie ma wartości, której można bezpiecznie użyć. Nie należy jej odczytywać przed przypisaniem. Bezpieczniej od razu nadać wartość:

```cpp
int wynik{0};
```

Warto też odróżniać operator przypisania `=` od operatora porównania `==`. Instrukcja `liczba = 13;` zmienia wartość zmiennej, a wyrażenie `liczba == 13` sprawdza, czy ta wartość jest równa `13`.

## Podstawowe typy

Na początek najważniejsze są typy całkowite, zmiennoprzecinkowe, logiczne i znakowe. W C++ przydaje się także `std::string` do przechowywania tekstu.

| Typ | Co przechowuje | Przykład |
|---|---|---|
| `int` | Liczbę całkowitą, bez części ułamkowej | `int wiek{20};` |
| `short`, `long`, `long long` | Całkowite wartości o różnych gwarantowanych zakresach i rozmiarach | `long long populacja{8000000000LL};` |
| `unsigned int` | Nieujemną liczbę całkowitą | `unsigned int liczba_prob{3};` |
| `float`, `double`, `long double` | Przybliżoną wartość zmiennoprzecinkową | `double temperatura{21.5};` |
| `bool` | Jedną z wartości: `true` albo `false` | `bool gotowe{false};` |
| `char` | Pojedynczy znak lub małą jednostkę reprezentacji tekstu | `char litera{'A'};` |
| `std::string` | Tekst składający się z wielu znaków | `std::string imie{"Ala"};` |

Tabela opisuje przeznaczenie typów, a nie dokładną liczbę bajtów. Rozmiary typów całkowitych zależą od implementacji. Nawet dla popularnych typów, takich jak `int` czy `long`, nie należy zakładać jednego rozmiaru na wszystkich platformach. Jeśli program wymaga dokładnej szerokości, trzeba świadomie użyć odpowiednich typów i nagłówków; w typowych ćwiczeniach wystarczy dobrać typ do rodzaju obliczeń.

Jeśli chcesz sprawdzić rozmiar typu na swoim komputerze, operator `sizeof` zwraca go w bajtach:

```cpp
#include <iostream>

int main() {
    std::cout << "sizeof(int) = " << sizeof(int) << '\n';
}
```

Wynik może się różnić na innej platformie. `sizeof` odpowiada na pytanie o rozmiar konkretnego typu w danej implementacji; sam wynik nie mówi jeszcze, jaki zakres wartości ten typ ma w każdym standardowym środowisku.

### Liczby całkowite i znak

`int` służy do zwykłych liczb całkowitych, takich jak liczba osób albo numer elementu. Warianty `short`, `long` i `long long` pozwalają dobrać typ do potrzebnego zakresu. Ich dokładne rozmiary są zależne od platformy, a standard określa minimalne wymagania.

Typy całkowite mogą być ze znakiem (`signed`) albo bez znaku (`unsigned`). Zwykły `int` jest typem ze znakiem i może przechowywać wartości ujemne. `unsigned int` przechowuje wartości od zera wzwyż w zakresie zależnym od platformy. Nie wybieraj `unsigned` automatycznie tylko dlatego, że w danym przykładzie liczba akurat nie jest ujemna: odejmowanie mniejszej wartości od większej może dać bardzo dużą dodatnią wartość zamiast liczby ujemnej.

`char` najczęściej służy do pojedynczego znaku, ale jego szczegóły zależą od kodowania i platformy. Zapis `'A'` oznacza pojedynczy znak typu `char`. Zapis `"A"` jest tekstem zawierającym znak i końcowe zakończenie napisu; w C++ można przechować go w `std::string`. To różne rodzaje wartości, mimo że na ekranie wyglądają podobnie.

Warto uważać na słowo „znak”: w tekście zapisanym w UTF-8 jedna widoczna litera może zajmować kilka bajtów, a `std::string` przechowuje jednostki tego kodowania. C++ udostępnia też typy `char16_t`, `char32_t` i `wchar_t` dla innych reprezentacji znaków. Nie należy jednak zakładać, że wybór innego typu sam rozwiązuje wszystkie problemy z tekstem wielojęzycznym; kodowanie trzeba obsłużyć świadomie.

### Liczby zmiennoprzecinkowe

`float` i `double` przechowują wartości z częścią ułamkową, na przykład `2.5`. Są to reprezentacje przybliżone, więc nie każdą wartość dziesiętną da się zapisać dokładnie. To ważne przy porównywaniu wyników obliczeń: rezultat może różnić się od oczekiwanego o bardzo małą wartość.

Zazwyczaj wybiera się `double`, gdy potrzebne są obliczenia ułamkowe. `float` może oszczędzać pamięć w dużych zbiorach danych, ale ma mniejszą precyzję. `long double` może oferować większą precyzję, lecz jego szczegóły zależą od kompilatora i platformy.

Przy typach całkowitych część ułamkowa nie istnieje. Dlatego dzielenie dwóch liczb całkowitych daje wynik całkowity:

```cpp
int calkowity_wynik = 5 / 2;      // wynik to 2
double ulamek = 5.0 / 2;          // wynik to 2.5
```

W drugim działaniu zapis `5.0` jest wartością zmiennoprzecinkową, więc dzielenie zachowuje część ułamkową. To typ argumentów wpływa na rodzaj obliczenia.

### Wartość logiczna i brak wartości

`bool` ma tylko dwie wartości: `true` (prawda) i `false` (fałsz). Używa się go między innymi do zapamiętania wyniku sprawdzenia warunku:

```cpp
bool pelnoletnia = wiek >= 18;
```

Typ `void` oznacza brak wartości zwracanej przez funkcję. Nie deklaruje się zwykłej zmiennej typu `void`, ponieważ taka zmienna nie miałaby wartości do przechowania. Przykładem funkcji zwracającej `void` jest funkcja, która tylko wypisuje tekst:

```cpp
void wypisz_powitanie() {
    // funkcja wykonuje działanie, ale nie zwraca wyniku
}
```

## Wybór typu i konwersje

Zacznij od pytania, jaką informację chcesz przechować. Dla liczby całkowitej wybierz typ całkowity, dla obliczeń ułamkowych zwykle `double`, dla odpowiedzi tak/nie — `bool`, a dla tekstu w C++ — `std::string`.

Kompilator może czasem automatycznie przekształcić wartość jednego typu na inny. Nie każda konwersja zachowuje wszystkie informacje. Na przykład przypisanie `2.7` do `int` usuwa część ułamkową. Inicjalizacja klamrowa pozwala wykryć takie zawężenie:

```cpp
double cena{2.7};
int pelne_zlotowki{cena}; // błąd: możliwa utrata części ułamkowej
```

Jeśli utrata części jest zamierzona, trzeba ją wyrazić świadomie i wyjaśnić w kodzie. Nie polegaj na przypadkowych konwersjach: trudniej wtedy zauważyć, że wynik różni się od tego, czego oczekiwałeś.

## Nazwy zmiennych

Nazwa zmiennej powinna mówić, jaką informację przechowuje. W zwykłych nazwach można używać liter, cyfr i podkreślenia `_`, ale nazwa nie może zaczynać się od cyfry. Nie można też użyć słowa zarezerwowanego przez język, takiego jak `int`, `class` czy `return`.

Na przykład `liczba_dni` i `sredniaTemperatura` są czytelniejsze niż `x` i `a1`, jeśli wskazują znaczenie danych. Warto wybrać jedną konwencję — na przykład `snake_case` albo `camelCase` — i stosować ją konsekwentnie. Nazw rozpoczynających się od podkreślenia lepiej unikać, ponieważ część takich nazw jest zarezerwowana dla implementacji języka.

## Stałe: `const` i `constexpr`

Czasem wartość ma pozostać niezmieniona. Słowo kluczowe `const` zabrania późniejszego przypisywania nowej wartości do danej zmiennej:

```cpp
const double stawka_vat{0.23};
```

Po inicjalizacji `stawka_vat` nie można zmienić. Używanie `const` zabezpiecza przed przypadkową zmianą i informuje czytelnika, że wartość ma pozostać stała.

`constexpr` oznacza, że wartość musi być możliwa do obliczenia podczas kompilacji:

```cpp
constexpr int liczba_dni_w_tygodniu{7};
```

Każdy obiekt `constexpr` jest stały, ale nie każda zmienna `const` musi być znana w czasie kompilacji. `const` wybieraj dla wartości, której program nie ma zmieniać; `constexpr` — gdy wartość powinna być dostępna już podczas kompilacji.

## Zakres widoczności i czas życia

Zakres i czas życia są powiązane, ale to nie to samo. **Zakres** mówi, w którym miejscu kodu można użyć nazwy zmiennej. **Czas życia** mówi, jak długo istnieje przechowywany przez nią obiekt.

Zmienna zadeklarowana wewnątrz funkcji albo bloku jest lokalna. Jej nazwa jest dostępna tylko od miejsca deklaracji do końca tego bloku, a sam obiekt przestaje istnieć, gdy program wychodzi z bloku:

```cpp
int main() {
    int wynik{10}; // widoczny do końca funkcji main

    {
        int tymczasowy{3}; // widoczny tylko wewnątrz tego bloku
        wynik = wynik + tymczasowy;
    } // tymczasowy przestaje istnieć

    // wynik nadal istnieje i ma wartość 13
}
```

Zmienna globalna jest deklarowana poza funkcjami. Jej nazwa może być widoczna w wielu miejscach programu, a jej czas życia obejmuje działanie programu. Globalne zmienne ułatwiają współdzielenie danych, ale ich zmiana z wielu miejsc utrudnia ustalenie, skąd wzięła się dana wartość. Dlatego początkujący kod powinien preferować zmienne lokalne, o ile nie ma powodu, by dane współdzielić.

Można też tworzyć obiekty dynamicznie, których czas życia nie jest związany z końcem pojedynczego bloku. Zarządzanie takim czasem życia wymaga dodatkowych reguł, dlatego omówimy je razem z pamięcią i wskaźnikami. Nie należy utożsamiać zmiennej dynamicznej z globalną: odpowiadają na inne pytania o to, gdzie obiekt jest widoczny i jak długo istnieje.

Lokalna zmienna ze słowem `static` ma węższy zakres nazwy — nadal można się do niej odwołać tylko z funkcji — ale zachowuje wartość między wywołaniami tej funkcji:

```cpp
#include <iostream>

void pokaz_licznik() {
    static int licznik{0}; // inicjalizowany raz, zachowuje wartość
    ++licznik;
    std::cout << licznik << '\n';
}

int main() {
    pokaz_licznik(); // wypisze 1
    pokaz_licznik(); // wypisze 2
}
```

Zwykła lokalna zmienna `licznik` zaczynałaby życie od nowa przy każdym wywołaniu. `static` sprawia, że jej obiekt istnieje przez cały czas działania programu, ale jej nazwa nie staje się globalna.

## Kompletny przykład

Poniższy program łączy kilka omówionych pojęć. Nagłówki są potrzebne, bo program korzysta ze strumienia `std::cout` i klasy `std::string`:

```cpp
#include <iostream>
#include <string>

int main() {
    std::string imie{"Ala"};
    int wiek{20};
    const int wiek_pelnoletnosci{18};
    bool pelnoletnia{wiek >= wiek_pelnoletnosci};

    std::cout << imie << " ma " << wiek << " lat.\n";
    std::cout << "Czy jest pełnoletnia? " << pelnoletnia << '\n';
}
```

`imie` przechowuje tekst, `wiek` liczbę całkowitą, a `pelnoletnia` wynik porównania. `wiek_pelnoletnosci` jest stałą, bo w tym przykładzie nie zmieniamy progu. Wiersze z `#include` umożliwiają użycie nazw z odpowiednich bibliotek; właściwe działanie zmiennych i instrukcji sprawdza już kompilator. Strumień `std::cout` domyślnie wypisuje wartość `bool` jako `1` albo `0`; można włączyć słowo `true` lub `false` za pomocą `std::boolalpha`.

## Najczęstsze pomyłki

- **Użycie niezainicjalizowanej zmiennej.** Sama deklaracja `int wynik;` nie nadaje lokalnej zmiennej wiarygodnej wartości. Zainicjalizuj ją przed odczytem.
- **Pomylenie `=` z `==`.** Pierwszy operator przypisuje wartość, drugi porównuje dwie wartości.
- **Oczekiwanie części ułamkowej przy dzieleniu całkowitym.** `5 / 2` ma wynik `2`, bo oba argumenty są całkowite.
- **Założenie, że każdy typ ma identyczny rozmiar na każdym komputerze.** Standard języka wyznacza wymagania minimalne, a szczegóły zależą od implementacji.
- **Traktowanie `char` i tekstu jako tego samego.** `'A'` to pojedyncza wartość typu `char`, a `"Ala"` to tekst.
- **Mylenie zakresu z czasem życia.** Zmienna statyczna wewnątrz funkcji zachowuje wartość dłużej niż jej nazwa jest widoczna.

Typy mówią kompilatorowi, jakie wartości i działania są dopuszczalne. Zmienne pozwalają te wartości zapamiętać, a zakres i czas życia określają, gdzie i jak długo program może z nich korzystać.
