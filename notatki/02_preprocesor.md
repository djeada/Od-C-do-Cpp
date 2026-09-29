# Preprocesor

W poprzedniej notatce zobaczyliśmy, że przed analizą kodu kompilator przetwarza dyrektywy takie jak `#include`. Robi to preprocesor. Jego zadaniem jest przygotowanie tekstu źródłowego: dołącza wskazane pliki, rozwija makra i wybiera fragmenty objęte kompilacją warunkową.

Preprocesor nie wykonuje programu i nie sprawdza typów tak jak kompilator. Działa wcześniej, na tekście. Dlatego dyrektywy z `#` mogą zmienić to, jaki kod trafi do kompilatora, ale nie potrafią na przykład sprawdzić wartości zmiennej podczas działania programu.

Komentarze również nie są instrukcjami programu. W trakcie wczesnego przetwarzania zostają zastąpione białymi znakami, dzięki czemu nie zmieniają sąsiadujących tokenów. Pisze się je dla osób czytających kod; procesor nie wykonuje ich treści.

Przykłady w tej notatce są zapisane w C++. W C działają te same podstawowe dyrektywy, choć nazwy nagłówków i kod korzystający z bibliotek mogą się różnić.

## Dołączanie plików przez `#include`

Gdy plik źródłowy korzysta z funkcji lub typu opisanego w nagłówku, musi znać jego deklarację. `#include` włącza treść wskazanego pliku do przetwarzanego pliku źródłowego. Można to sobie wyobrazić jako tekstowe rozwinięcie nagłówka w miejscu dyrektywy.

```cpp
#include <iostream>       // nagłówek biblioteki standardowej C++
#include "powitanie.hpp"  // nagłówek z bieżącego projektu
```

Nawiasy ostre stosuje się zwykle dla nagłówków bibliotek, a cudzysłowy — dla plików projektu. To konwencja dotycząca sposobu wyszukiwania plików: dokładne katalogi przeszukiwane przez kompilator zależą od jego konfiguracji.

Warto rozdzielić dwie rzeczy: dołączenie nagłówka udostępnia deklaracje, ale samo w sobie nie łączy gotowej definicji funkcji z programem. Na przykład nagłówek może powiedzieć kompilatorowi, że istnieje `void wypisz_powitanie();`, a kod tej funkcji może znajdować się w osobnym pliku `.cpp`. Pliki obiektowe trzeba później połączyć linkerem.

### Dlaczego nagłówki mają strażniki?

Jeden nagłówek może zostać dołączony do pliku kilka razy pośrednio: na przykład `main.cpp` dołącza `a.hpp` i `b.hpp`, a oba te nagłówki dołączają `wspolne.hpp`. Wielokrotne przetworzenie tej samej deklaracji lub definicji może spowodować błędy. Strażnik nagłówka sprawia, że treść zostanie uwzględniona tylko raz w danej jednostce translacji:

```cpp
// wspolne.hpp
#ifndef WSPOLNE_HPP
#define WSPOLNE_HPP

int oblicz_sume(int a, int b);

#endif // WSPOLNE_HPP
```

Przy pierwszym przejściu `WSPOLNE_HPP` nie jest jeszcze zdefiniowane, więc preprocesor wchodzi do bloku i definiuje makro. Gdy ponownie napotka ten nagłówek, warunek `#ifndef` jest fałszywy i jego zawartość zostaje pominięta. Nazwa strażnika powinna być charakterystyczna dla pliku, aby nie zderzyła się z inną nazwą.

W wielu popularnych kompilatorach działa też prostsze `#pragma once`, które zapobiega wielokrotnemu dołączeniu pliku. Jest szeroko obsługiwane, ale nie jest przenośnym zamiennikiem zdefiniowanym w taki sam sposób jak standardowe dyrektywy. Strażniki są bezpiecznym, powszechnym rozwiązaniem.

Zapis `#pragma once` wygląda tak:

```cpp
#pragma once
```

Umieszcza się go na początku nagłówka zamiast strażnika. Wybierz jeden z tych sposobów i stosuj go konsekwentnie w projekcie.

## Makra i podstawianie tekstu

`#define` wprowadza makro. Preprocesor zastępuje jego nazwę wskazanym tekstem, zanim kompilator sprawdzi kod. Makro nie jest zmienną ani funkcją: nie ma własnego typu i kompilator nie analizuje jego argumentów tak jak argumentów zwykłej funkcji.

Przykład makra bez argumentów:

```cpp
#define PI 3.14159

double pole_kola(double promien) {
    return PI * promien * promien;
}
```

Definicja obowiązuje od miejsca, w którym pojawia się `#define`, do końca jednostki translacji albo do chwili usunięcia jej dyrektywą `#undef`. Dlatego makro nazwane `PI` nie jest zmienną o zasięgu funkcji: jego podmiana może dotyczyć całego dalszego kodu przetwarzanego pliku.

Przed analizą kompilatora użycie `PI` zostanie zastąpione tekstem `3.14159`. W nowym kodzie C++ stałą liczbową zwykle lepiej zapisać jako `constexpr`, bo ma wtedy typ i podlega regułom języka:

```cpp
constexpr double pi = 3.14159;
```

### Nawiasy w makrach funkcyjnych

Makro może przyjmować argumenty, ale nadal działa przez podstawienie tekstu. To łatwo przeoczyć, bo zapis makra przypomina wywołanie funkcji.

Rozważmy błędne makro:

```cpp
#define KWADRAT(x) x * x

int a = 5;
int wynik = KWADRAT(a + 1);
```

Preprocesor wstawi argument dosłownie. Otrzymamy więc:

```cpp
int wynik = a + 1 * a + 1;
```

Mnożenie ma pierwszeństwo przed dodawaniem, więc przy `a == 5` wyrażenie oznacza `5 + (1 * 5) + 1`, czyli `11`. Nie jest to oczekiwany kwadrat liczby `6`.

Nawiasy wokół argumentu i całego wyrażenia naprawiają ten konkretny błąd:

```cpp
#define KWADRAT(x) ((x) * (x))
```

Teraz `KWADRAT(a + 1)` rozwija się do `((a + 1) * (a + 1))`. Nadal jednak nie jest to bezpieczne zastępstwo funkcji. Argument trafia do makra dwa razy, więc przekazanie wyrażenia, które zmienia stan — na przykład `i++` — może spowodować nieoczekiwane zachowanie. W C++ do obliczeń lepiej użyć funkcji; makr używa się głównie tam, gdzie potrzebna jest właśnie praca preprocesora.

## Wybieranie kodu przed kompilacją

Dyrektywy `#if`, `#ifdef`, `#ifndef`, `#elif`, `#else` i `#endif` pozwalają włączyć wybrane wiersze do kodu przekazanego kompilatorowi, a inne pominąć. Przydaje się to między innymi do ustawień debugowania albo kodu zależnego od platformy.

Poniższy kompletny przykład wypisuje informację diagnostyczną tylko wtedy, gdy makro `NDEBUG` nie zostało zdefiniowane:

```cpp
#include <iostream>

int main() {
#ifndef NDEBUG
    std::cout << "Wersja z informacją diagnostyczną\n";
#endif

    std::cout << "Program działa\n";
}
```

Gdy preprocesor napotka `#ifndef NDEBUG`, sprawdza wyłącznie, czy makro o tej nazwie istnieje. Jeśli istnieje, pomija aż do `#endif` tekst diagnostyczny. W przeciwnym razie pozostawia ten tekst dla kompilatora. Makro można zdefiniować w poleceniu kompilacji opcją `-DNDEBUG` w narzędziach GNU. Biblioteka standardowa używa `NDEBUG` między innymi do wyłączania sprawdzeń `assert`.

`#ifdef NAZWA` pyta, czy makro jest zdefiniowane. Nie sprawdza, czy jego wartość jest równa `1`. Do sprawdzania wartości służy `#if`:

```cpp
#define WERSJA 2

#if WERSJA == 1
    // kod dla wersji 1
#elif WERSJA == 2
    // kod dla wersji 2
#else
    // kod dla pozostałych wersji
#endif
```

Preprocesor wybiera gałąź na podstawie wyrażenia złożonego ze stałych całkowitych i makr. Nie może w tym miejscu zapytać o wartość zmiennej programu, ponieważ zmienna nie została jeszcze utworzona ani program nie został uruchomiony.

Jeśli w wyrażeniu `#if` użyjesz nazwy, która nie jest zdefiniowanym makrem, preprocesor potraktuje ją jak `0`. Literówka w nazwie wersji może więc po cichu wybrać inną gałąź, zamiast dać błąd. Gdy warunek ma sprawdzać samo istnienie makra, użyj `#ifdef NAZWA` albo `#if defined(NAZWA)`.

Makra platformowe mogą służyć do wyboru fragmentów przeznaczonych dla danego systemu. Ich nazwy i znaczenie zależą od kompilatora oraz platformy, więc samo użycie `#ifdef` nie czyni programu przenośnym. W większym projekcie warto ograniczać taki kod do miejsc, które rzeczywiście wymagają funkcji systemowych.

Przykład pokazuje sam mechanizm, a nie gotowy sposób na przenośność całego programu:

```cpp
#if defined(_WIN32)
    // fragment przeznaczony dla środowiska Windows
#elif defined(__linux__)
    // fragment przeznaczony dla środowiska Linux
#else
    // pozostałe środowiska
#endif
```

Nazwy `_WIN32` i `__linux__` są dostarczane przez narzędzia dla odpowiednich platform. Kod wewnątrz każdej gałęzi nadal musi być poprawny dla kompilatora, który ją wybierze.

## Pozostałe przydatne dyrektywy

`#undef NAZWA` usuwa bieżącą definicję makra. Po tej dyrektywie preprocesor nie będzie już rozwijał `NAZWA` według poprzedniej definicji. Ponowne definiowanie tego samego makra w różnych miejscach zwykle utrudnia zrozumienie kodu, dlatego `#undef` przydaje się głównie w szczególnych przypadkach.

```cpp
#define ROZMIAR_BUFORA 1024
// Tutaj ROZMIAR_BUFORA rozwija się do 1024.

#undef ROZMIAR_BUFORA
// Od tego miejsca ta nazwa nie jest już makrem.
```

`#error` zatrzymuje przetwarzanie i wyświetla komunikat. Można dzięki niemu jasno zgłosić brak wymaganego ustawienia:

```cpp
#ifndef WERSJA
#error "Musisz zdefiniować makro WERSJA"
#endif
```

Jeśli `WERSJA` nie zostało zdefiniowane, kompilator zatrzyma proces na etapie preprocesowania i poda wskazany komunikat. `#warning` bywa obsługiwane przez kompilatory, ale jego dostępność i zachowanie zależą od narzędzia.

Przykład `#warning`:

```cpp
#warning "Ta część programu wymaga sprawdzenia"
```

Kompilator może wtedy wypisać ostrzeżenie i kontynuować pracę. Ponieważ obsługa tej dyrektywy różni się między kompilatorami, nie należy jej traktować jako przenośnego mechanizmu wymaganego przez język.

Kompilator udostępnia też predefiniowane nazwy. `__FILE__` oznacza nazwę bieżącego pliku, a `__LINE__` — numer wiersza. W C++ można użyć ich na przykład w prostym komunikacie diagnostycznym:

```cpp
#include <iostream>

int main() {
    std::cout << "Plik: " << __FILE__
              << ", wiersz: " << __LINE__ << '\n';
}
```

`__DATE__` i `__TIME__` dostarczają datę i czas kompilacji. Z kolei `__func__` jest w C++ nazwą dostępną wewnątrz funkcji, a nie makrem preprocesora. Takie informacje bywają przydatne przy diagnozowaniu błędów, choć w praktycznych projektach zwykle korzysta się z bibliotek do logowania.

## Najczęstsze nieporozumienia

- **„`#include` wstawia do programu gotową funkcję”.** Zwykle nagłówek udostępnia jej deklarację; definicja może być w innym pliku i wymagać linkowania.
- **„Makro jest funkcją”.** Makro zastępuje tekst przed sprawdzaniem typów i składni. Nie zapewnia takich samych reguł jak funkcja.
- **„`#ifdef WERSJA` sprawdza, czy WERSJA wynosi 1”.** Sprawdza tylko, czy nazwa makra została zdefiniowana. Do sprawdzenia liczby służy `#if WERSJA == 1`.
- **„Preprocesor widzi wartości zmiennych”.** Nie widzi ich podczas działania programu. Kompilacja warunkowa wybiera tekst wcześniej, przed kompilowaniem.

Kiedy preprocesor zakończy pracę, kompilator analizuje przygotowany kod. W następnej notatce przejdziemy od tego tekstu do podstawowych obiektów programu: zmiennych, ich typów i wartości.
