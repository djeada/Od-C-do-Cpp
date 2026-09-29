# Liczby losowe i pseudolosowe

Program może potrzebować losowego wyniku, na przykład podczas rzutu kostką, tasowania kart albo symulacji. Komputer zwykle nie losuje jednak każdej liczby od zera. W C++ najczęściej korzysta z **generatora pseudolosowego**: algorytmu, który tworzy długą, pozornie losową sekwencję wartości.

W C++ do tego celu służy biblioteka `<random>` (dostępna od C++11). Jej użycie łatwiej zrozumieć, gdy rozdzielimy dwie role:

1. **Silnik** przechowuje swój stan i tworzy kolejne liczby pseudolosowe.
2. **Rozkład** zamienia wyniki silnika na wartości potrzebne programowi, na przykład liczbę całkowitą od 1 do 6.

```text
ziarno → silnik pseudolosowy → rozkład → wartość dla programu
```

## Silnik, rozkład i ziarno

Silnik działa jak deterministyczna maszyna. Po uruchomieniu z tym samym **ziarnem** (ang. *seed*) i przy tych samych wywołaniach wytwarza tę samą sekwencję. To przydatne: można ponownie uruchomić symulację z tymi samymi danymi i odtworzyć jej przebieg.

Ziarno nie jest wynikiem losowania ani gwarancją bezpieczeństwa. To wartość, od której silnik zaczyna pracę. Dwie kopie tego samego silnika z tym samym ziarnem odtworzą tę samą sekwencję.

Rozkład określa, **jakiego rodzaju wynik** chcemy dostać. Na przykład `std::uniform_int_distribution<int>(1, 6)` wybiera każdą liczbę od 1 do 6 z takim samym prawdopodobieństwem. Rozkład całkowity obejmuje oba końce zakresu. Dla porównania rozkład rzeczywisty `std::uniform_real_distribution<double>(0.0, 1.0)` generuje wartości z przedziału od `0.0` włącznie do `1.0` wyłącznie.

### Pseudolosowość a losowość fizyczna

Generator pseudolosowy (PRNG) jest algorytmem: mając początkowy stan, oblicza następny stan i wynik. Dlatego jego wyniki są odtwarzalne, jeśli znamy ziarno i sposób użycia. Sekwencja po pewnym czasie zacznie się powtarzać; liczbę wartości przed powtórzeniem nazywa się **okresem** generatora. Długi okres jest przydatny w długich symulacjach, ale sam w sobie nie gwarantuje dobrych wyników ani bezpieczeństwa.

Losowość fizyczna pochodzi z pomiaru zjawiska, którego nie da się praktycznie przewidzieć, na przykład szumu w urządzeniu. Generator kryptograficzny (CSPRNG) ma dodatkowy cel: utrudniać przewidzenie przyszłych wartości nawet wtedy, gdy ktoś pozna część wcześniejszych wyników. To inne wymaganie niż równomierny rozkład w symulacji. `std::mt19937` jest PRNG do zastosowań ogólnych, a nie CSPRNG.

## Rzut kostką w C++

Poniższy kompletny program wykonuje dziesięć rzutów sześcienną kostką. Stałe ziarno jest celowe: po każdym uruchomieniu, na tej samej implementacji biblioteki, program odtworzy tę samą sekwencję wyników.

```cpp
#include <iostream>
#include <random>

int main() {
    std::mt19937 silnik(12345); // stałe ziarno: łatwo powtórzyć przebieg
    std::uniform_int_distribution<int> kostka(1, 6);

    for (int rzut = 1; rzut <= 10; ++rzut) {
        int wynik = kostka(silnik);
        std::cout << "Rzut " << rzut << ": " << wynik << '\n';
    }
}
```

Jak czytać ten przykład:

1. `std::mt19937 silnik(12345);` tworzy silnik Mersenne Twister z jawnym ziarnem.
2. `kostka(1, 6)` tworzy rozkład, który ma zwracać liczby całkowite od 1 do 6.
3. Wywołanie `kostka(silnik)` pobiera kolejny wynik z silnika i przekształca go zgodnie z rozkładem.
4. Silnik jest tworzony **raz**, przed pętlą. Każde kolejne wywołanie rozkładu przesuwa jego stan i daje następny wynik.

Jeśli chcemy, by kolejne uruchomienia zwykle zaczynały od innej sekwencji, można pobrać ziarno z `std::random_device`:

```cpp
#include <random>

int main() {
    std::random_device zrodlo;
    std::mt19937 silnik(zrodlo());
    std::uniform_int_distribution<int> kostka(1, 6);

    int wynik = kostka(silnik);
}
```

`std::random_device` jest źródłem wartości użytej do inicjalizacji silnika. To, czy korzysta z niedeterministycznego źródła systemowego, zależy od implementacji. Nie zakładaj, że samo użycie `std::random_device` zawsze daje generator odpowiedni do kryptografii.

Ważna praktyczna zasada: **nie twórz i nie inicjalizuj silnika wewnątrz pętli**. Jeśli za każdym razem użyjesz tego samego ziarna, dostaniesz za każdym obiegiem pierwszy element tej samej sekwencji. Jeśli zaś za każdym razem pobierzesz ziarno z zegara o małej dokładności, kilka inicjalizacji może dostać tę samą wartość. Utwórz silnik raz i używaj go wielokrotnie.

## Jakie rozkłady są dostępne?

Rozkład opisuje, jakie wyniki mogą wystąpić i z jakimi prawdopodobieństwami. Wybieramy go według pytania, które modeluje program:

| Rozkład | Parametry | Przykład zastosowania |
| --- | --- | --- |
| `std::uniform_int_distribution` | całkowite `a` i `b` | kostka, losowy indeks, liczba z zakresu; oba końce są włączone |
| `std::uniform_real_distribution` | rzeczywiste `a < b` | położenie punktu na odcinku; `a` jest włączone, `b` wyłączone |
| `std::bernoulli_distribution` | prawdopodobieństwo `p` od 0 do 1 | zdarzenie zachodzi albo nie zachodzi, np. rzut monetą |
| `std::normal_distribution` | średnia `mu`, odchylenie `sigma > 0` | pomiary skupione wokół średniej |
| `std::poisson_distribution` | dodatnia średnia liczba zdarzeń `lambda` | liczba zdarzeń w przedziale czasu lub przestrzeni, jeśli taki model pasuje |

Krótkie fragmenty w tej części zakładają, że program ma `#include <random>` i wcześniej utworzony silnik, na przykład `std::mt19937 silnik(12345);`.

### Co oznaczają prawdopodobieństwo, średnia i rozrzut?

W przypadku rozkładu **dyskretnego** można wymienić możliwe wyniki i prawdopodobieństwo każdego z nich. Dla uczciwej kostki każdy wynik ma prawdopodobieństwo `1/6`. W przypadku rozkładu **ciągłego** opisuje się przedziały: prawdopodobieństwo trafienia do przedziału odpowiada polu pod krzywą gęstości. Dlatego pojedynczej dokładnej wartości rzeczywistej nie interpretuje się tak samo jak jednej ścianki kostki.

**Wartość oczekiwana** to teoretyczna średnia z wielu prób, a **wariancja** opisuje, jak bardzo wyniki rozpraszają się wokół tej średniej. Nie muszą być możliwymi wynikami pojedynczej próby: wartość oczekiwana rzutu kostką wynosi `3.5`, mimo że na kostce nie ma ścianki z takim numerem.

### Rozkład jednostajny

W rozkładzie jednostajnym wszystkie dopuszczalne wyniki mają takie samo prawdopodobieństwo. Dla liczb całkowitych od `a` do `b` włącznie jest `b - a + 1` wyników, więc prawdopodobieństwo każdego wynosi:

$$
P(X=k)=\frac{1}{b-a+1},\qquad k=a,\ldots,b.
$$

Dla przykładu kostki oznacza to sześć wyników po `1/6`. Jej średnia wynosi `3.5`, a wariancja `35/12`. To opis wielu rzutów, a nie obietnica, że wyniki w krótkiej serii będą równo rozłożone.

Dla ciągłego rozkładu jednostajnego na przedziale `[a,b]` gęstość jest stała: `1/(b-a)`. Średnia wynosi `(a+b)/2`, a wariancja `(b-a)^2/12`. W bibliotece C++ rozkład rzeczywisty zwraca wynik z `[a,b)`, czyli z `a` włącznie i bez `b`.

### Rozkład Bernoulliego

Rozkład Bernoulliego modeluje pojedynczą próbę z dwoma wynikami: sukces (`true`) z prawdopodobieństwem `p` albo brak sukcesu (`false`) z prawdopodobieństwem `1-p`. Jego średnia wynosi `p`, a wariancja `p(1-p)`.

```cpp
std::bernoulli_distribution zdarzenie(0.3);
bool zaszlo = zdarzenie(silnik); // true z prawdopodobieństwem 0.3
```

Jeśli wykonamy `n` niezależnych prób i policzymy sukcesy, ich liczba ma rozkład dwumianowy. Nie oznacza to, że w każdej serii `n` prób będzie dokładnie `n * p` sukcesów; to oczekiwana liczba, do której zbliża się średni wynik wielu takich serii.

### Rozkład normalny

Rozkład normalny, zwany też Gaussa, ma kształt dzwonu: wyniki blisko średniej `mu` są częstsze niż wyniki od niej odległe. Odchylenie standardowe `sigma` określa szerokość tego dzwonu. W przybliżeniu 68% wyników mieści się w zakresie `mu ± sigma`, a 95% w `mu ± 2 sigma`.

```cpp
std::normal_distribution<double> pomiar(50.0, 10.0); // średnia 50, odchylenie 10
double wartosc = pomiar(silnik);
```

Ten rozkład bywa użyteczny przy modelowaniu błędów pomiarowych, jeśli uzasadnia to przyjęty model. Nie oznacza, że zmienna jest ograniczona do podanego „typowego” przedziału: rozkład normalny teoretycznie dopuszcza także wartości daleko od średniej.

### Rozkład Poissona

Rozkład Poissona opisuje liczbę zdarzeń w ustalonym przedziale, gdy zdarzenia zachodzą niezależnie i ze stałą średnią intensywnością. Parametr `lambda` oznacza oczekiwaną liczbę zdarzeń w tym przedziale. Dla tego rozkładu średnia i wariancja są równe `lambda`.

```cpp
std::poisson_distribution<int> liczbaZdarzen(4.0);
int ile = liczbaZdarzen(silnik); // możliwe są także 0, 1, 2, ...
```

Wartość `4.0` nie oznacza, że w każdym przedziale wystąpią dokładnie cztery zdarzenia. To średnia z wielu podobnych przedziałów. Sam dobór rozkładu zależy od tego, czy założenia modelu odpowiadają opisywanej sytuacji.

## Zastosowanie do symulacji

Losowanie służy nie tylko do gier. W metodzie Monte Carlo wykonujemy wiele losowych prób i uśredniamy wyniki, aby oszacować wielkość, którą trudno obliczyć bezpośrednio. Na przykład całkę z `x*x` na przedziale od 0 do 1 można oszacować jako średnią z wielu wartości `x*x`, gdzie `x` losujemy równomiernie z tego przedziału:

```cpp
#include <cstddef>
#include <iostream>
#include <random>

int main() {
    std::mt19937 silnik(12345);
    std::uniform_real_distribution<double> odcinek(0.0, 1.0);

    constexpr std::size_t liczbaProb = 100000;
    double suma = 0.0;

    for (std::size_t i = 0; i < liczbaProb; ++i) {
        double x = odcinek(silnik);
        suma += x * x;
    }

    double oszacowanieCalki = suma / liczbaProb;
    std::cout << "Oszacowanie: " << oszacowanieCalki << '\n';
    // Wynik powinien być w pobliżu 1/3.
}
```

Całka z `x*x` od 0 do 1 wynosi `1/3`. Program nie liczy jej wzorem: losuje punkty, oblicza wartość funkcji dla każdego z nich i wyznacza średnią. Przy niezależnych próbach o skończonej wariancji typowy błąd takiego oszacowania maleje w przybliżeniu jak `1/sqrt(N)`. W praktyce oznacza to, że aby typowy błąd zmniejszyć około dwa razy, trzeba wykonać mniej więcej cztery razy więcej prób. Monte Carlo jest przydatne zwłaszcza wtedy, gdy podobne uśrednianie można wykonać w problemie o wielu wymiarach.

## Wybór silnika i ocena jakości

Silnik odpowiada za sekwencję, a nie za sens wyniku. Wybierając go, warto wiedzieć, czy potrzebujemy odtwarzalnej symulacji, czy nieprzewidywalności kryptograficznej:

| Narzędzie | Rola i typowe zastosowanie |
| --- | --- |
| `std::mt19937` | deterministyczny silnik Mersenne Twister; popularny do symulacji, ma długi okres `2^19937 - 1`, ale nie jest kryptograficzny |
| `std::mt19937_64` | wariant Mersenne Twistera zwracający 64-bitowe wartości; również nie jest kryptograficzny |
| `std::random_device` | źródło wartości, często używane do ziarna; niedeterministyczność zależy od implementacji |
| `rand()` w C/C++ | starszy interfejs z `<stdlib.h>`; parametry i jakość zależą od implementacji, lepiej unikać w nowym kodzie C++ |

Okres mówi, po ilu krokach sekwencja zaczyna się powtarzać. Jednak długi okres nie oznacza, że wszystkie kombinacje kolejnych wyników są równie dobrze rozłożone. Jakość statystyczną bada się na przykład tak:

| Test | Pytanie, które pomaga sprawdzić |
| --- | --- |
| Chi-kwadrat | Czy częstości wyników w przedziałach są zbliżone do oczekiwanych? |
| Test korelacji | Czy kolejne wartości wykazują widoczną zależność? |
| Kołmogorowa–Smirnowa (K–S) | Czy empiryczny rozkład wyników jest zgodny z zakładanym rozkładem ciągłym? |
| TestU01 i podobne zestawy | Czy sekwencja przechodzi szerszy zestaw testów statystycznych? |

Test może ujawnić konkretny problem, ale zaliczenie testów nie dowodzi, że źródło jest naprawdę losowe ani że nie da się przewidzieć jego wyników. W szczególności testy statystyczne nie zastępują analizy bezpieczeństwa kryptograficznego.

## A co z językiem C?

Standardowe C nie ma odpowiednika biblioteki C++ `<random>`. Udostępnia starsze funkcje `rand()` i `srand()` z nagłówka `<stdlib.h>`. Poniższy program pokazuje typowy prosty przykład:

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned)time(NULL)); // ustaw ziarno raz, przed losowaniem

    int wynik = rand() % 6 + 1;
    printf("Wynik: %d\n", wynik);
    return 0;
}
```

`srand` ustawia początkowy stan generatora używanego przez `rand`. Gdy program nie wywoła `srand`, otrzymuje powtarzalny przebieg zgodny z zachowaniem określonym dla biblioteki. Użycie `time(NULL)` często daje inne ziarno w kolejnych uruchomieniach, ale dwa uruchomienia w tej samej sekundzie mogą dostać ten sam czas.

Wyrażenie `rand() % 6 + 1` jest łatwe do zapisania, ale może rozkładać wyniki nierównomiernie. Reszta z dzielenia jest równa, jeśli liczba możliwych wyników `rand()` nie dzieli się równo przez 6. Jakość i zakres `rand()` zależą od implementacji, a sam interfejs nie oferuje osobnych rozkładów. Dlatego w nowym kodzie C++ wybieraj `<random>`.

## Czego nie używać do haseł i kluczy?

`std::mt19937` jest przydatny w symulacjach i grach, ale nie został zaprojektowany tak, by utrudniać przewidywanie kolejnych wartości. Nie używaj go do haseł, kluczy, tokenów ani innych sekretów. To samo dotyczy `rand()`.

Standardowa biblioteka C++ nie zapewnia przenośnego generatora kryptograficznego. Do sekretów użyj sprawdzonej funkcji kryptograficznej systemu operacyjnego albo biblioteki kryptograficznej. Także `std::random_device` nie daje przenośnej gwarancji bezpieczeństwa kryptograficznego.

## Częste pomyłki

- **Losowanie zakresu przez `%`.** Może dać nierówne szanse i ogranicza wynik do zakresu `rand()`. W C++ użyj `std::uniform_int_distribution`.
- **Inicjalizowanie generatora przy każdym losowaniu.** Powoduje zbędną pracę, a przy powtarzanym ziarnie powtarza pierwsze wyniki. Utwórz silnik raz poza pętlą.
- **Oczekiwanie innej sekwencji przy stałym ziarnie.** To właśnie stałe ziarno zapewnia odtwarzalność. Zmieniaj ziarno tylko wtedy, gdy potrzebujesz innego przebiegu.
- **Traktowanie „losowe” jako „kryptograficznie nieprzewidywalne”.** Dobre własności statystyczne nie oznaczają odporności na odgadnięcie przyszłych wyników.
- **Zakładanie, że test statystyczny dowodzi losowości.** Test może wykryć pewne wady sekwencji, ale sam nie potwierdzi bezpieczeństwa ani prawdziwej losowości.

Generator dostarcza wartość, ale często program powinien nadać jej znaczenie. Na przykład zamiast opisywać wynik słowami „0”, „1” i „2”, można zdefiniować nazwany zbiór stanów. Temu służy typ wyliczeniowy `enum` w następnej notatce.
