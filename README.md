# Od-C-do-Cpp

Kod źródłowy do programów z yt.

# Spis Treści

<!--ts-->

- [Proces kompilacji](#Proces-kompilacji)
- [Preprocesor](#Preprocesor)
- [Zmienne](#Zmienne)
- [Interakcja z konsolą](#Interakcja-z-konsolą)
- [Instrukcje sterujące](#Instrukcje-sterujące)
- [Pętle](#Pętle)
- [Liczby losowe](#Liczby-losowe)
- [Funkcje](#Funkcje)
- [Wskaźniki](#Wskaźniki)
- [Tablice](#Tablice)
- [Napisy](#Napisy)
- [Pola bitowe](#Pola-bitowe)
- [Operacje bitowe](#Operacje-bitowe)
- [Iteratory](#Iteratory)

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
#include <something>
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
int x; // zmienna x typu int
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
x++; // teraz x przechowuje 14
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
const double pi = 3.14; // Ok. Stała jest zadeklarowana i zainicjalizowana.
const double doInicjalizacji; // Źle. Tak nie robimy!
```

### Zakres życia zmiennych

```c++
int liczba = 5;

if(liczba % 2 == 1){
	int liczba = 3; // zmienna lokalna!

	cout << liczba << endl;	// 3
}

cout << liczba << endl;	// 5
```

```c++
int a = 10; // zmienna globalna

int main(){
	int a = 3; // zmienna lokalna

	cout << a << endl;	// 3
  cout << ::a << endl;	// 10
}
```

## Interakcja z konsolą

Każdy program w momencie uruchomienia ma dostęp do trzech strumieni:

    1. stdin - strumień wejściowy
    2. stdout - strumień wyjściowy
    3. stderr - strumień błędów

Biblioteka <code>iostream</code>zawiera definicje funkcji, które pozwalają na komunikację z tymi strumieniami:

- obiekt<code>cout</code> oraz operator <code><<</code> wypisuje tekst na standardowe wyjście;
- obiekt<code>cin</code> oraz operator <code>>></code> wczytują pojedynczą wartość ze standardowego wejścia;
- <code>getline(cin, string)</code> wczytuje ze standardowego wejścia cały wiersz wraz ze spacjami.

```c++
#include <iostream>

using namespace std;

int main(){
    int liczba;
    cout << "Podaj pojedynczą liczbę: "<< endl;
    cin >> liczba;

    cout << "Podałeś liczbę: " << liczba << endl;

    cin.ignore();  //wyczyszczenie bufora

    string zadanie;
    cout << "Podaj pełne zdanie: "<< endl;

    getline(cin, zdanie);

    cout << "Podałeś zdanie: " << endl << zdanie << endl;

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

using namespace std;

int main(){
	int n;
	cin >> n;
	if (n % 3 == 0)
		cout << "Liczba " << n << " jest podzielna przez 3 " << endl;
	else {
		n++;
		cout << "Wczytana liczba powiększona o 1 to: " << n << endl;
	}

	return 0;
}
```

### Wielokrotne warunki

Możemy sprawdzić wiele warunków jeden po drugim i uzleżnić od ich spełnienia różne bloki kodu.

```c++
#include <iostream>

using namespace std;

int main(){
	int n;
	cout << "Podaj numer dnia tygodnia: " << endl;
	cin >> n;

	if (n == 0)
		cout << "Poniedziałek." << endl;

	else if (n == 1)
		cout << "Wtorek." << endl;

	else if (n == 2)
		cout << "Środa. " << endl;

	else if (n == 3)
		cout << "Czwartek." << endl;

	else if (n == 4)
		cout << "Piątek." << endl;

	else if (n == 5)
		cout << "Sobota." << endl;

	else if (n == 6)
		cout << "Niedziela." << endl;
	else
		cout << "Error! " << endl;

	return 0;
}
```

### Switch

<code>Switch</code> daje nam również możliwość sprawdzenia wielokrotnych warunków.
Niektóre kompilatory lepiej optymalizują kod z użyciem <code>switch</code> niż <code>else if</code>.
Mechanizm ten jest również niejednokrotnie uważany za bardziej elegancki.

```c++
#include <iostream>

using namespace std;

int main(){
	int n;
	cout << "Podaj numer dnia tygodnia: " << endl;
	cin >> n;

	switch (n) {
		case 0:
			cout << "Poniedziałek." << endl;
			break;

		case  1:
			cout << "Wtorek." << endl;
			break;

		case 2:
			cout << "Środa. " << endl;
			break;

		case 3:
			cout << "Czwartek." << endl;
			break;

		case 4:
			cout << "Piątek." << endl;
			break;

		case 5:
			cout << "Sobota." << endl;
			break;

		case 6:
			cout << "Niedziela." << endl;
			break;

		default:
			cout << "Error! " << endl;
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

using namespace std;

int main(){
	int n;
	cout << "Podaj liczbę: " << endl;
	cin >> n;

	for (int i = 0; i < n; i++) {
		if (i % 2)
			continue;
		cout << i << endl;
	}

	return 0;
}
```

### Break

Podobnie jak <code>continue</code>, <code>break</code> przerywa aktualną iterację pętli. Różnica polega na tym, że po wywołaniu <code>break</code> pętla zostanie całkowicie przerwana i program przejdzie do kodu znajdującego się pod pętlą.

```c++
#include <iostream>

using namespace std;

int main(){
	int n;
	cout << "Podaj liczbę: " << endl;
	cin >> n;

	for (int i = 0; i < n; i++) {
		if (i % 2)
			break;
		cout << i << endl;
	}

	return 0;
}
```

## Liczby losowe

```c++
#include <random>

int losowa_z_przedzialu(int start, int end){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(start,end);
    return distr(gen);
}

//Dwie opcje z równym prawdopodobieństwem
int orzel_lub_reszka(){
    if(randomInRange(-10001, 10000) >= 1){
        return 1;
    }
    return -1;
}
```

## Typ wyliczeniowy enum

Typ wyliczeniowy <code>enum</code> pozwala na tworzenie zmiennych, które mogą przyjmować jedynie z góry określone wartości. Wartości te mają czytelne nazwy, a dodatkowo <code>enum</code> jest bardzo szybki i opłaca się go używać nawet w krytycznych miejscach programu.

```c++
#include <iostream>

using namespace std;

enum class Kolor {
	Czerwony,
	Zielony,
	Niebieski
};

int main(){
	Kolor kolor = Color::Czerwony;

	switch (kolor) {
		case Color::Czerwony:
			cout << "Wybrano czerwony." << endl;
			break;
		case Color::Zielony:
			cout << "Wybrano zielony." << endl;
			break;
		case Color::Niebieski:
			cout << "Wybrano niebieski." << endl;
			break;
		default:
			cout << "Blad!" << endl;
	}

	return 0;
}
```

## Funkcje

Za pomocą funkcji możemy część kodu zamknąć pod jedną nazwą.

### Tworzenie i wywoływanie funkcji

Elementy składowe funkcji to:

1. <code>Typ</code> zwracanej wartości.
2. <code>Imię</code> funkcji, dzięki któremu jest rozpoznawalna.
3. <code>Argumenty</code>, czyli zewnętrzne wartości, które chcemy użyć w funkcji i chcemy żeby zostały nam podane w momencie wywołania funkcji.

```
wybrany_typ nazwa_funkcji(argumenty){
	//ciało czyli jaki kod chcemy żeby został uruchomiony po wywołaniu nazwa_funkcji
	return wartosc_jaka_ma_zostac_zwrocona;

}

int main(){
	wybrany_typ x = nazwa_funkcji(argumenty);
}
```

### Deklaracja funkcji

Deklaracja funkcji to wyrażenie, które zawiera nazwę funkcji, jej argumenty oraz jej zwracany typ. Deklaracja musi pojawić się w kodzie przed wywołaniem funkcji. W przeciwnym razie kompilator wyświetli komunikat o błędzie. Definicja funkcji to deklaracja wraz z ciałem funkcji.

```c++
#include <iostream>

using namespace std;

// definicja
void fun1(){
	cout << "fun1" << endl;
}

// deklaracja
void fun2();

int main() {
	fun1(); // OK
	fun2(); // OK
	fun3(); // ŹLE

	return 0;
}

void fun2(){
	cout << "fun2" << endl;
}

void fun3(){
	cout << "fun3" << endl;
}
```

### Funkcja zwracająca wartość

Do zwracania wartości poprzez funkcję używamy słowa kluczowego <code>return</code>. Słowo kluczowe <code>return</code> przerywa działanie funkcji i zwraca wartość umieszczoną po nim w kodzie. Typ zwracanej wartości musi być taki sam jak typ funkcji. Funkcja nie będąca funkjcą typu void musi zawsze zwracać wartość.

```c++
#include <iostream>

using namespace std;

int suma(int x, int y){
	return x + y;
}

int main() {
	int a = 5;
	int b = 3;

	cout << suma(a, b) << endl;

	return 0;
}
```

### Funkcja typu void

Funkcje typu void nie zwracają żadnej wartości. Nie ma konieczności użycia słowa kluczowego <code>return</code>. Jeśli jednak zostanie użyte, to nie może być podana za nim żadna wartość. W kontekście funkcji typu void <code>return</code> służy jedynie do przerywania funkcji.

```c++
#include <iostream>

using namespace std;

void wypisz_imie(string s){
	cout << s << endl;
}

int main() {
	string imie = "Karol";
	wypisz_imie(imie);

	return 0;
}
```

### Parametry z domyślną wartością

Domyślna wartość to taka, która zostanie użyta jeśli przy wywołaniu funkcji nie będzie podana wartość dla danego parametru.

```c++
#include <iostream>

using namespace std;

int pomnoz(int a, int b = 3){
	return a*b;
}

int main() {
	int x = 2;
	int y = 7;

	cout << pomnoz(x, y) << endl;
	cout << pomnoz(x) << endl;

	return 0;
}
```

### Przekazywanie argumentów funkcji przez wartość i referencję

Istnieją dwa sposoby na przekazywanie argumentów do funkcji. Pierwszy to przekazywanie argumentów przez wartość, jeśli argumentem jest zmienna, to funkcja otrzymuje kopię jej wartości. Wszelkie zmianny na tą wartość w funkcji nie wpływają na oryginalną zmienną. Drugi sposób na przekazywanie argumentów to przekazywanie argumentów przez referencję. W tym przypadku funkcja otrzymuje referencję do oryginalnej zmiennej. Wszelkie zmiany na tą wartość w odbywają się bezpośrednio na oryginalnej zmiennej.

Przykład przekazywania argumentów przez wartość:

```c++
void pomnoz(int a, int b){
	a = a*b;
}
```

Przykład przekazywania argumentów przez referencję:

```c++
void pomnoz(int &a, int &b){
	a = a*b;
}
```

## L-wartości i r-wartości

Niektóre wartości w C++ istnieją jedynie w obrębie jednego wyrażenia i nie można ich adresować. Takie wartości zwane są r-wartościami (bo mogą występować po prawej stronie znaku =). Ich nadzbiorem są l-wartości. Wszystkie l-wartości są r-wartościami, ale nie wszystkie r-wartości są l-wartościami.

```c++
int main() {
	int i = 3; // Poprawne
	3 = i; // Niepoprawne;
	i + 4 = 20; // Niepoprawne;

	return 0;
}
```

## Wskaźniki

Wskaźnik to zmienna, która przechowuje adres innej zmiennej. Dodatkowo przy pomocy wskaźników mamy możliwość modyfikowania zmiennych, których adresy przechowują wskaźniki.

<code>Typ_zmiennej_kt&oacute;rej_adres_przechowuje_wskaźnik \* nazwa_wskaźnika;</code>

```c++
\\ Deklaracja
int* p1;
double* p2;
string* p3;

int x = 4;
double y = 3.5;
string s = "napis";

// Inicjalizacja
// p1 = &y; // Crash. Niezgodne typy.
p1 = &x; // OK. Typy się zgadzają
p2 = &y;
p3 = &s;
```

### Dereferencja

Wyłuskanie wartości na, która znajduje się w zmiennej, na którą wskazuje nasz wskaźnik.
Używane nie tylko do odczytu, ale również zmiany wartości tej zmiennej.

<code>\*nazwa wskaźnika</code>

```c++
#include<iostream>
using namespace std;

int main(){
	int x = 4;
	double y = 3.5;
	string s = "napis";

	int* p1 = &x;
	double* p2 = &y;
	string* p3 = &s;

  	cout << "Co siedzi w zmiennych x, y, s: " << endl;
	cout << p1* << endl;
	cout << p2* << endl;
	cout << p3* << endl;

  	*p1 = 7; //zmiana wartosci zmiennej x
	*p2 = 8.123; //zmiana wartosci zmiennej y
  	*p3 = "inny"; //zmiana wartosci zmiennej s

	cout << "Co siedzi w zmiennych x, y, s: " << endl;
	cout << p1* << endl;
	cout << p2* << endl;
	cout << p3* << endl;

  	return 0;
}
```

### Wskaźnik na wskaźnik

Operator \* pozwala również tworzyć wskaźniki przechowujące adresy innych wskaźników.

```c++
#include<iostream>
using namespace std;

int main(){
	int i = 20;
	int* j = &i;
	int** k = &j;
	int*** l = &k;

  	return 0;
}
```

### Wskaźnik na NULL

<code>NULL</code> to specjalna wartość wskaźnika symbolizująca wskazywanie na nieistniejący obiekt. Dzięki tej wartości możemy sygnalizować koniec listy połączonej lub poinformować o niemożliwości przydziału pamięci, lub otwarcia pliku (współcześnie preferuje się wyjątki).

W C, w zależności od implementacji <code>NULL</code> definiowany jest jako <code>0</code> lub <code>((void\*)0)</code>. W obu przypadkach używany jest dokładnie do tego samego.
Z uwagi na to, że <code>NULL</code> to po prostu zero, możemy w taki sposób sprawdzić, czy wskaźnik <code>wsk</code> nie jest wskaźnikiem na <code>NULL</code>:

```c++
if (wsk != 0) {}
```

Na pierwszy rzut oka nie widać jednak, czy <code>wsk</code> jest wskaźnikiem, czy zwykłą liczbą. Z tego powodu lepiej jest użyć następującej konstrukcji:

```c++
if (wsk != NULL) {}
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
 int const * a;  /* równoważnie */
```

oraz stałe wskaźniki:

```c++
 int * const b;
```

Słówko const przed typem działa jak w przypadku zwykłych stałych, tzn. nie możemy zmienić wartości wskazywanej przy pomocy wskaźnika.

W drugim przypadku słowo const jest tuż za gwiazdką oznaczającą typ wskaźnikowy, co skutkuje stworzeniem stałego wskaźnika, czyli takiego którego nie można przestawić na inny adres.

```c++
#include <iostream>
using namespace std;

int main() {
	int zmienna = 10;
	const int stala = 15;
	int * const wskaznik_na_stala = &stala;
	int * const wskaznik_na_zmienna = &zmienna;
	const int * const wskaznik_na_stala_wskaznik = &wskaznik_na_stala;
	const int * const wskaznik_na_zmienna_wskaznik = &wskaznik_na_zmienna;


	return 0;
}
```

## Tablice

Jeśli zmienna to pudełko, to tablica to półka z pudełkami. Wszystkie pudełka na jednej półce przechowują dane tego samego typu. Do tworzenia tablic używamy nawiasów kwadratowych. Między nawiasy kwadratowe trafia liczba reprezentująca ilość elementów tablicy.

```c++
int tab[3]; // Półka z 3 pudełkami typu int.
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
using namespace std;

const int n = 10;

int main() {

	int a[n];

	cout << "Podaj " << n << " elementów: " << endl;

	// wczytywanie
	for (int i = 0; i < n; i++)
		cin >> a[i];

	cout << "Twoja tablica: " << endl;

	// wypisywanie
	for (int i = 0; i < n; i++)
		cout << a[i] << endl;

	return 0;
}
```

Jeśli spróbujesz odnieść się do tablicy przy użyciu nieporawnego indeksu (mniejszego od 0 bądź większego lub równego długości tablicy) to zachowanie programu jest niezdefiniowane. Jeśli system operacyjny jest miły to w ten sposób możesz otrzymać przypadkowe liczby, które akurat siedzą w komórkach pamięci na lewo bądź prawo od twojej tablicy. W przeciwnym razie twój program po prostu przestanie działać (crash).

### Tablica jako wskaźnik

Za pomocą wskaźników można również odwoływać się do elementów tablicy. Nazwa tablicy to wskaźnik do pierwszego elementu tablicy. Jeśli <code>tab</code> to nazwa tablicy, to <code>tab[0]</code> oraz <code>\*tab</code> są synonimami.

```c++
#include <iostream>
using namespace std;

int suma(int* tablica, int dlugosc) {
	int suma = 0;

	for (int i = 0; i < dlugosc; i++)
		suma += tablica[i];

	return suma;
}

int main() {

	int tab[] = {2, 4, 8, 16, 32};
	cout << suma(tab, 5) << endl;

	return 0;
}
```

Zwróć uwagę, że w powyższym przykładzie przekazujemy do funkcji długość tablicy. Kompilator nie wie, czy <code>int\* tablica</code> wskazuje na pojedynczą liczbę, czy na tablicę 10 liczb. Nie pomoże nawet operator <code>sizeof</code>, zwracający rozmiar danego obiektu lub typu podany w bajtach. Dla wskaźnika zwróci jedynie rozmiar typu, na który wskazuje wskaźnik.

### Arytmetyka wskaźników

Jeśli nazwa tablicy to wskaźnik do pierwszego elementu tablicy i elementy tablicy umiejscowione są jeden obok drugiego w pamięci komputera, to fajnie byłoby mieć możliwość przesuwania się między kolejnymi elementami tablicy za pomocą wskaźników. Taki mechanizm istnieje i zwie się arytmetyką wskaźników. Arytmetyka, dlatego że do wskaźników możemy dodawać i odejmować liczby całkowite. Jeśli wskaźnik <code>wsk</code> wskazuje nam pierwszy element tablicy <code>tab</code>, to <code>wsk+3</code> będzie wskazywał na czwarty element tablicy. Przy tej operacji należy być jednak bardzo ostrożnym, gdyż łatwo jest wyjść poza granice tablicy i spróbować odczytać zabroniony obszar pamięci.

```c++
#include <iostream>
using namespace std;
int main() {
	int tab[] = {1, 2, 3, 4, 5};
	int* wsk = tab;

	cout << *wsk << endl;
	cout << *(wsk+3) << endl;

	return 0;
}
```

### Dynamiczna alokacja pamięci

Aby skorzystać z pamięci sterty, używamy operatora <code>new</code> do alokacji (rezerwacji) miejsc w pamięci komputera dla elementów tablicy. Użycie samego <code>new</code> zarezerwuje pamięć dla pojedynczej zmiennej. Dla tablicy używam <code>new [liczba]</code>, gdzie <code>liczba</code> to długość tablicy, jaką chcemy stworzyć.
Gdy tablica nie jest nam już potrzebna, zarezerwowaną uprzednio pamięć uwalniamy przy pomocy <code>delete</code>. Podobnie jak z operatorem <code>new</code>, dla tablicy używamy <code>delete []</code>. Tym razem nie wstawiamy już żadnych liczb w nawiasy kwadratowe.

```c++
#include <iostream>

using namespace std;

int main() {

	cout << "Podaj liczbę elemntów tablicy: " << endl;

	int n;
	cin >> n;

	int *tab = new int[n];

	cout << "Podaj " << n << " elementów: " << endl;

	for (int i = 0; i < n; i++)
		cin >> tab[i];

	cout << "Twoja tablica: " << endl;

	for (int i = 0; i < n; i++)
		cout << tab[i] << endl;

	delete[] tab;

	return 0;
}
```

Zmienne na stercie mogą żyć dłużej niż wskazujące na nie wskaźniki. Jeśli explicite nie uwolnimy dynamicznie zaalokowanej pamięci, to system operacyjny będzie dalej ją trzymał i bronił przed nadpisaniem. Jeśli nie żyje już nasz wskaźnik, to z jednej strony nie mamy w programie możliwości dostania się do zmiennych, które stworzyliśmy na stercie, a z drugiej marnujemy zasoby komputera, bo system operacyjny nie dopuszcza innych programów do tego obszaru pamięci. Taką sytuację nazywamy wyciekiem pamięci. Dla kilku zmiennych jest to nieodczuwalne, ale dla większych programów może szybko przeciążyć naszą maszynę.

### Tablica 2D

Tablice mogą mieć dowolną ilość wymiarów. Najczęściej będziemy jednak spotykać tablice jedno i dwuwymiarowe.

```c++
#include <iostream>

using namespace std;

int const n = 3;
int const m = 4;

int main() {

	int a[n][m];

	cout << "Podaj " << n*m << " elementów: " << endl;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j];

	cout << "Twoja tablica: " << endl;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}

	return 0;
}
```

Dla tablic dwuwymiarowych alokacja i dealokacja pamięci odbywa się przy pomocy pętli. Stwórzmy macierz o liczbie wierszy równej zmiennej <code>wysokość</code> i liczbie kolumn równej zmiennej <code>szerokość</code>:

```c++
#include <iostream>
using namespace std;

int main() {

	double** macierz;
	int wysokosc, szerokosc;

	cin >> wysokosc >> szerokosc;

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

Napis (string) to tablica znaków. Przydatne funkcje:

<table style="height: 263px; width: 546px;">
    <tbody>
        <tr>
            <td style="width: 155px; text-align: center;">Funkcja</td>
            <td style="width: 385px; text-align: center;">Działanie</td>
        </tr>
        <tr>
            <td style="width: 155px;">a.size()</td>
            <td style="width: 385px;">z ilu znak&oacute;w składa się napis<code>a</code>(długość)</td>
        </tr>
        <tr>
            <td style="width: 155px;">a.clear() </td>
            <td style="width: 385px;">wyczyść napis a</td>
        </tr>
        <tr>
            <td style="width: 155px;">a.empty() </td>
            <td style="width: 385px;">prawda jeśli napis <code>a</code> jest pusty</td>
        </tr>
        <tr>
            <td style="width: 155px;">a.append("czesc")</td>
            <td style="width: 385px;">dostaw "czesc" na koniec napisu<code>a</code></td>
        </tr>
        <tr>
            <td style="width: 155px;">a.insert(0, "hej")</td>
            <td style="width: 385px;">wstaw "hej" na pozycje 0 do napisu<code>a</code></td>
        </tr>
        <tr>
            <td style="width: 155px;">a.pop_back() </td>
            <td style="width: 385px;">ściągnij ostatni znak z napisu<code>a</code></td>
        </tr>
        <tr>
            <td style="width: 155px;">a.c_str() </td>
            <td style="width: 385px;">konwersja<code>a</code> na char *</td>
        </tr>
        <tr>
            <td style="width: 155px;">a.find("lol")</td>
            <td style="width: 385px;">na jakiej pozyji w napisie<code>a </code>znajduje się napis "lol"</td>
        </tr>
        <tr>
            <td style="width: 155px;">a.compare(b)</td>
            <td style="width: 385px;">por&oacute;wnaj napis<code>a</code> z<code>b</code></td>
        </tr>
    </tbody>
</table>

## Pole bitowe

Możemy wskazać ile dokładnie bitów chcemy zarezerwować dla danego pola struktury.

```c++
#include <iostream>

using namespace std;

struct Data {
	unsigned int Rok : 13; // 2^13 = 8192
	unsigned int Miesiac : 4; // 2^4 = 16
	unsigned int Dzien : 5; // 2^5 = 32
};

void wypiszDate(Data d) {
	cout << "Mamy dziś: " << endl;
	cout << d.Dzien << "-" << d.Miesiac << "-" << d.Rok << endl;
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
#include <iostream>
#include <bitset>

using namespace std;

int main() {
	bitset<8> x(5);
	cout << x << endl; //00000101
	cout << ~x << endl; //11111010

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
#include <iostream>
#include <bitset>

using namespace std;

int main() {
	int a = 7;
	int b = 5;

	cout << bitset<8>(a) << endl; //00000111
	cout << bitset<8>(b) << endl; //00000101
	cout << bitset<8>(a | b) << endl; //00000111

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
#include <iostream>
#include <bitset>

using namespace std;

int main() {
	int a = 7;
	int b = 5;

	cout << bitset<8>(a) << endl; //00000111
	cout << bitset<8>(b) << endl; //00000101
	cout << bitset<8>(a & b) << endl; //00000101

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
#include <iostream>
#include <bitset>

using namespace std;

int main() {
	int a = 7;
	int b = 5;

	cout << bitset<8>(a) << endl; //00000111
	cout << bitset<8>(b) << endl; //00000101
	cout << bitset<8>(a ^ b) << endl; //00000010

	return 0;
}
```

### Przesunięcia bitowe

Bity w lewo przesuwamy za pomocą operatora <<. </br>
Bity w prawo przesuwamy za pomocą operatora >>. </br>
Przesunięcie w lewo o 1 bit równoważne jest podzieleniu przez 2. </br>
Przesuniecie w prawo o 1 bit równoważne jest przemnożeniu przez 2. </br>

```c++
#include <iostream>
#include <bitset>

using namespace std;

int main() {
	int a = 14;
	int b = 2;

	cout << bitset<8>(a) << endl; //00001110
	cout << bitset<8>(b) << endl; //00000010
	cout << bitset<8>(a << b) << endl; //00111000
	cout << bitset<8>(a >> b) << endl; //00000011

	return 0;
}
```

## Zawansowne wskaźniki

### Wskaźniki na funkcje

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

		int pole() {
			return a * b;
		}
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

		~Prostokat() {
			cout << "Destruktor" << endl;
		}
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

		int pole() {
			return a * b;
		}
};

int main() {

	Prostokat prostokat(2, 3);
	auto pole = prostokat.pole(); // Ok. Mamy dostęp do pól publicznych.
	auto a = prostokat.a; // Źle. Nie mamy dostępu do pól prywatnych.

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
		Foo() {
			bar = 0;
		}

		void setBar(int bar) {
			this->bar = bar;
		}

		int getBar() {
			return bar;
		}
};

int main() {
	Foo foo;
	Foo *wsk = &foo;
	wsk->setBar(10);
	cout << wsk->getBar() << endl;
	return 0;
}
```

### Przeciążanie operatorów

C++ daje nam możliwość definiowania nowego znaczenia różnych operatorów dla definiowanych przez nas klas. W naszym przykładzie, definiujemy operator <code>+</code> dla klasy <code>Prostokat</code>.

    - operator + (Prostokat &p1, Prostokat &p2)
    - operator + (Prostokat &p1, int a)
    - operator + (int a, Prostokat &p1)

### Struktury

Struktura jest protoplastą klasy. W C struktury pozwalają na łączenie pod jedną nazwą danych różnego typu. W C nie ma jednak możliwości definiowania funkcji w obrębie struktury. C++ zmienia znaczenie struktur. W C++ struktury i klasy są dokładnie tym samym, z wyjątkiem tego, że domyślnie wszystkie pola struktur są publiczne, a pola klas prywatne.

Przykład w C

```c++
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

```c++
struct Foo zmienna_foo;
```

W C++ możemy dalej używać tej składni, ale nie jest to konieczne. Możemy po prostu napisać:

```c++
Foo zmienna_foo;
```

W C istnieje jeszcze jeden sposób tworzenia struktur

### Unie

Unie to kolejny sposób reprezentacji danych w pamięci.

```c++
Union {
	int a;
	int b;
};

int main() {
	Union unia;
	unia.a = 10;
	unia.b = 20;
	return 0;
}
```

Mogłoby się wydawać, że unie są tym samym co struktury. Różnica polega na tym, że w danej chwili tylko jedno pole unii może przechowywać wartość. Z tego powodu Unie są chudsze od struktur i unia zajmuje w pamięci tyle miejsca, ile wynosi rozmiar największego z jej pól.

## Dziedziczenie

Dziedziczenie to

### Typy dziedziczenia

### Polimorfizm

DLACZEGO TAKI ISTOTNY? BO ROZWIAZUJE CODE SMELL Z IF

    if obiekt.type == Kaczka:
    	obiekt.dziobaj()
    if obiekt.type == Pies:
    	obiekt.skacz()

Zamiast tego mamy:

    obiekt.przywitaj()

### Metody wirtualne

### Klasy abstrakcyjne

## Lambdy

Funkcje, które nie mają żadnych parametrów, można zapisać w nawiasach klamrowych. W tym przypadku funkcja nie posiada nazwy, a jest to zwykły wyrażenie.

    [](int a, int b) {
    	return a + b;
    }

Jeśli chcemy mieć bezpośredni dostęp do zmiennych z zewnętrznego kontekstu, możemy użyć <code>&</code> w nawiasie kwadratowym.

    [&](int a, int b) {
    	return a + b;
    }

## Szablony

## Iteratory

Iteratory to funkcje, które pozwalają na iterowanie po obiektach. Używając iteratory możemy zmieniać wartości obiektów. Inną funkcją jest <b>konstruktor kopiujący</b>.

```c++
#include <iostream>
#include <vector>
#include <string>

int main() {
	vector<string> v;
	v.push_back("ala");
	v.push_back("ma");
	v.push_back("kota");

	for (auto it = v.begin(); it != v.end(); ++it) {
		cout << *it << endl;
	}

	return 0;
}
```

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

void funkcja()
{
    throw std::runtime_error("Wyjatek");
}

int main() {
  try
  {
      funkcja();
  }
  catch(std::runtime_error& e)
  {
      std::cout << "Wyjątek: " << e.what() << std::endl;
  }

  std::cout << "Zycie toczy sie dalej" << std::endl;

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

	// sprawdzamy, czy plik został otwarty
	if (plik == NULL) {
		printf("Nie udało się otworzyć pliku");
		return 1;
	}

	// wczytujemy zawartość pliku
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

	// sprawdzamy, czy plik został otwarty
	if (!plik.is_open()) {
		std::cout << "Nie udało się otworzyć pliku" << std::endl;
		return 1;
	}

	// wczytujemy zawartość pliku
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

## STL

STL (Standard Template Library) jest biblioteką, która implementuje wiele przydatnych funkcji, algorytmów i struktur danych. Wiele innych bibliotek standardowych używa STL, np. <code>std::string</code> i <code>std::vector</code>.

1. unordered_map

Kontener unordered_map implementuje tablicę mieszającą.

\begin{tabular}{ |c|c| }
\hline
operacje & złożoność czasowa \\
\hline
wyszukiwanie & O(1) \\
wstawianie & O(1) \\
usuwanie & O(1) \\
\hline
\end{tabular}
\end{tabular}

2. map

Kontener map implementuje drzewo czerwono-czarne.

\begin{tabular}{ |c|c| }
\hline
operacje & złożoność czasowa \\
\hline
wyszukiwanie & O(log n) \\
wstawianie & O(log n) \\
usuwanie & O(log n) \\
\hline
\end{tabular}

3. priority_queue

Kontener priority_queue implementuje kopiec.

\begin{tabular}{ |c|c| }
\hline
operacje & złożoność czasowa \\
\hline
wstawianie & O(log n) \\
zdejmowanie & O(log n) \\
wierzchołek & O(1) \\
\hline
\end{tabular}

4. list

Kontener list implementuje listę dwukierunkową.

\begin{tabular}{ |c|c| }
\hline
operacje & złożoność czasowa \\
\hline
wstawianie & O(n) \\
usuwanie & O(n) \\
wyszukiwanie & O(n) \\
\hline
\end{tabular}

5. vector

Kontener vector implementuje tablicę dynamiczną.

\begin{tabular}{ |c|c| }
\hline
operacje & złożoność czasowa \\
\hline
dostawianie na koniec & O(1) \\
usuwanie z końca & O(1) \\
dostawianie (ogólnie) & O(n) \\
usuwanie (ogólnie) & O(n) \\
wyszukiwanie & O(n) \\
\hline
\end{tabular}

6. unordered_set

Struktura unordered_set implementuje tablicę mieszającą.

\begin{tabular}{ |c|c| }
	\hline
	operacje & złożoność czasowa \\
	\hline
	wyszukiwanie & O(1) \\
	wstawianie & O(1) \\
	usuwanie & O(1) \\
	\hline
\end{tabular}

7. set

Struktura set implementuje drzewo czerwono-czarne.

\begin{tabular}{ |c|c| }
\hline
operacje & złożoność czasowa \\
\hline
wyszukiwanie & O(log n) \\
wstawianie & O(log n) \\
usuwanie & O(log n) \\
\hline
\end{tabular}

## Bibliografia

- https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md
- http://www.doc.ic.ac.uk/~wjk/C++Intro/index.html
- https://rules.sonarsource.com/cpp/RSPEC-5184
- https://pythontutor.com/cpp.html#mode=edit
- https://beej.us/guide/bgc/html/split/
- https://beej.us/guide/bgnet/html/
- https://beej.us/guide/bgipc/html/multi/index.html
