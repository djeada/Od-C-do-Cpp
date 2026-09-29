# Konwersje i rzutowania

Program często łączy wartości różnych typów: dzieli liczbę całkowitą przez zmiennoprzecinkową, przekazuje wskaźnik do funkcji albo zamienia obiekt jednego rodzaju na drugi. **Konwersja** to zmiana wartości lub sposobu, w jaki program może z niej korzystać, na inny typ. Może wykonać się niejawnie albo na nasze jawne żądanie.

Słowo **rzutowanie** zwykle oznacza jawną składnię, na przykład `(double)x` w C albo `static_cast<double>(x)` w C++. Rzutowanie mówi kompilatorowi, jaką konwersję próbujemy wykonać; nie sprawia samo z siebie, że konwersja jest poprawna, bezstratna albo bezpieczna. To szczególnie ważne przy wskaźnikach. W notatkach o wskaźnikach i przeciążaniu funkcji pojawiają się podobne pytania: jaki typ ma wyrażenie i którą wersję funkcji kompilator wybierze.

## Konwersje arytmetyczne w C

Rzutowanie w stylu C ma postać `(typ_docelowy)wyrażenie`. Najpierw obliczane jest wyrażenie, następnie jego wartość zostaje przekonwertowana na wskazany typ.

```c
int liczba = 10;
double szersza = (double)liczba;

double pomiar = 3.75;
int calkowita = (int)pomiar;  // 3
```

W pierwszym przypadku wartość `10` jest reprezentowana jako `double`, a zmienna `liczba` nadal ma typ `int`. Zwykłe wartości całkowite dają się dokładnie przedstawić jako `double`, ale typ zmiennoprzecinkowy nie musi dokładnie reprezentować każdej możliwej dużej liczby całkowitej — przy konwersji może wtedy zniknąć część precyzji. W drugim przykładzie część ułamkowa zostaje odrzucona: konwersja obcina w kierunku zera, więc `(int)-3.75` daje `-3`, a nie `-4`. Jeśli część całkowita wyniku nie mieści się w typie docelowym, zachowanie jest niezdefiniowane. Nie używaj więc rzutowania jako sposobu sprawdzania, czy liczba mieści się w typie.

### Typ wyrażenia ma znaczenie

Rzutowanie może zmienić wynik całego wyrażenia, jeśli wykonamy je przed operacją. Dzielenie dwóch liczb całkowitych jest całkowite:

```c
int a = 7;
int b = 2;

double wynik1 = a / b;          // Najpierw int: 7 / 2 daje 3, potem 3 staje się 3.0
double wynik2 = (double)a / b;  // a staje się double; b też jest konwertowane do double
                                // dzielenie daje 3.5
```

Przypisanie wyniku do `double` nie zmienia wstecz typu operacji. Jeśli chcemy dzielenia zmiennoprzecinkowego, co najmniej jeden operand musi mieć taki typ już w chwili dzielenia.

Przed obliczeniem kompilator stosuje też **promocje całkowitoliczbowe**. Na przykład `unsigned char` o wartości `250` jest zwykle promowany do `int`, bo `int` może reprezentować wszystkie wartości tego typu:

```c
unsigned char x = 250;
unsigned char y = 10;
int suma = x + y;  // Oba argumenty są promowane do int; suma wynosi 260
```

Promocja dotyczy wartości użytej w wyrażeniu, nie zmienia deklarowanego typu zmiennej `x` ani `y`. Po promocjach **zwykłe konwersje arytmetyczne** ustalają wspólny typ operandów. Przy typach zmiennoprzecinkowych słabszy typ, np. `float`, może zostać podniesiony do `double`; przy mieszaniu typów całkowitych ze znakiem i bez znaku wynik zależy od ich rang i zakresów. Konwersja do typu całkowitego o mniejszym zakresie może utracić informację. Reguły wyniku poza zakresem typu ze znakiem różnią się między językami i wersjami standardu, dlatego najpierw sprawdź zakres, jeśli ma on znaczenie.

Mieszanie `signed` i `unsigned` jest częstym źródłem zaskoczeń:

```c
int s = -1;
unsigned int u = 1;

/* int i unsigned int mają tę samą rangę.
   s zostaje przekonwertowane do unsigned int, a -1 daje UINT_MAX.
   Dlatego porównanie s < u jest fałszywe. */
if (s < u) {
    /* ... */
}
```

Konwersja liczby całkowitej do typu bez znaku jest określona modulo `UINT_MAX + 1` dla `unsigned int` (analogicznie dla innego typu bez znaku). To zawijanie wartości, a nie sygnał błędu. Przepełnienie arytmetyczne typu ze znakiem nie ma takiej gwarancji i w C prowadzi do niezdefiniowanego zachowania. Jeżeli zakres wartości ma znaczenie, sprawdź go przed obliczeniem i nie polegaj na rzutowaniu ani na mieszaniu znaków.

## Wskaźniki w C

Rzutowanie wskaźnika zmienia typ, pod którym program próbuje używać adresu. Nie konwertuje obiektu na nowy typ i nie przekształca automatycznie jego bajtów.

W C wynik `malloc` ma typ `void *`. Taki wskaźnik można przypisać do wskaźnika na obiekt bez rzutowania:

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *liczba = malloc(sizeof *liczba);
    if (liczba == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    *liczba = 42;
    printf("%d\n", *liczba);
    free(liczba);
    return 0;
}
```

Zapis `sizeof *liczba` wiąże ilość pamięci z typem wskazywanym przez `liczba`; dzięki temu zmiana typu wskaźnika nie wymaga ręcznej zmiany liczby w `sizeof`. W C rzutowanie wyniku `malloc` jest zbędne i może ukryć brak deklaracji tej funkcji. W C++ `void *` nie konwertuje się niejawnie do `int *`, a pamięć dla obiektów zwykle uzyskuje się przez typowane narzędzia języka, nie przez kopiowanie tego idiomu C.

Nie rób tego:

```c
float pomiar = 3.14f;
int *adres = (int *)&pomiar;
printf("%d\n", *adres);  // Niepoprawny odczyt przez niezgodny typ
```

`adres` ma typ `int *`, ale wskazuje na obiekt typu `float`. Odczyt przez taki wskaźnik może naruszać wyrównanie, efektywny typ i reguły aliasowania. W rezultacie program może działać inaczej po zmianie kompilatora lub opcji optymalizacji. Jeśli potrzebujesz obejrzeć reprezentację obiektu bajt po bajcie, w C użyj wskaźnika do `unsigned char` i pamiętaj, że otrzymane bajty zależą od reprezentacji używanej przez maszynę. Jeśli potrzebujesz przenośnego zapisu danych, zdefiniuj format zamiast kopiować surowe bajty obiektu.

## Jawne operatory konwersji w C++

C++ ma kilka operatorów rzutowania. Ich nazwy ułatwiają rozpoznanie intencji i wyszukiwanie ryzykownych miejsc w kodzie. Nie są one „bezpiecznymi wersjami” rzutowania: każdy pozwala wykonać określoną operację, której warunki nadal muszą być spełnione.

### `static_cast`

Używaj `static_cast` dla zwykłych konwersji arytmetycznych i konwersji w hierarchii klas, których poprawność wynika z wiedzy o programie.

```cpp
int liczba = 10;
double pomiar = static_cast<double>(liczba);  // 10.0
double ulamek = 3.75;
int obciety = static_cast<int>(ulamek);       // 3; konwersja obcina część ułamkową

struct Baza {
    virtual ~Baza() = default;
};
struct Pochodna : Baza {};

Pochodna obiekt;
Baza *baza = &obiekt;
Pochodna *pochodna = static_cast<Pochodna *>(baza);  // Poprawne: obiekt jest Pochodna
```

Konwersja w górę z `Pochodna *` do `Baza *` jest bezpieczna i zwykle zachodzi niejawnie. Konwersja arytmetyczna `static_cast<int>(3.75)` również obcina część ułamkową; nie sprawdza, czy wynik zachowa potrzebną precyzję ani czy konwersja zmieści się w typie. Konwersja w dół za pomocą `static_cast` nie sprawdza typu obiektu. Jej warunkiem jest to, że wskaźnik bazowy rzeczywiście wskazuje na podobiekt `Baza` wewnątrz obiektu `Pochodna`. Jeśli nie:

```cpp
Baza tylkoBaza;
Baza *b = &tylkoBaza;
Pochodna *p = static_cast<Pochodna *>(b);  // Niezdefiniowane zachowanie
```

Kompilator może zaakceptować ten zapis, ale obiekt `tylkoBaza` nie zawiera części `Pochodna`. Nie dereferencjonuj takiego wskaźnika. Gdy rzeczywisty typ nie jest znany, w hierarchii polimorficznej użyj `dynamic_cast` albo zaprojektuj interfejs tak, by nie trzeba było rozpoznawać typu pochodnego.

`static_cast` nie usuwa `const` ani `volatile` i nie pozwala na dowolne rzutowanie między niepowiązanymi typami wskaźników.

### `dynamic_cast`

`dynamic_cast` sprawdza w czasie działania, czy wskaźnik lub referencja wskazuje na obiekt żądanego typu. Przy konwersji w dół lub w poprzek hierarchii klasa źródłowa musi być polimorficzna, czyli mieć co najmniej jedną funkcję wirtualną. Najczęściej rolę tę spełnia wirtualny destruktor.

```cpp
struct Baza {
    virtual ~Baza() = default;
};
struct Pochodna : Baza {
    void wykonaj() {}
};
struct Inna : Baza {};

Inna innyObiekt;
Baza *baza = &innyObiekt;

if (Pochodna *p = dynamic_cast<Pochodna *>(baza)) {
    p->wykonaj();  // Ta gałąź wykonałaby się tylko dla rzeczywistego obiektu Pochodna
} else {
    // Rzutowanie wskaźnika nie powiodło się: wynik to nullptr
}
```

Tutaj `baza` wskazuje na `Inna`, więc wynik rzutowania to `nullptr` i `wykonaj` nie jest wywołane. Przy rzutowaniu referencji nie ma wartości `nullptr`; niepowodzenie powoduje wyjątek `std::bad_cast` (deklaracja jest w `<typeinfo>`). Jeśli kod stale sprawdza typy pochodne, wiele takich kontroli może wskazywać, że lepiej dodać wirtualną operację do interfejsu `Baza`.

### `const_cast`

`const_cast` może dodać lub usunąć kwalifikator `const` albo `volatile`. Nie zmienia jednak tego, czy obiekt został pierwotnie zadeklarowany jako stały.

```cpp
int wartosc = 10;              // Obiekt sam w sobie nie jest const
const int *widok = &wartosc;   // Przez ten wskaźnik nie wolno go zmieniać
int *zapis = const_cast<int *>(widok);
*zapis = 20;                   // Poprawne: pierwotny obiekt wartosc nie jest const

const int stala = 10;
const int *widokStalej = &stala;
int *blednyZapis = const_cast<int *>(widokStalej);
// *blednyZapis = 20;          // Niezdefiniowane zachowanie
```

Typowy powód użycia to stare API z parametrem `char *`, które w rzeczywistości tylko czyta tekst. Usunięcie `const` jest wtedy dopuszczalne wyłącznie, jeśli funkcja go nie modyfikuje. Lepszą naprawą jest zmiana sygnatury funkcji na `const char *`, jeśli mamy wpływ na API. Rzutowanie nie chroni przed funkcją, która jednak zapisze do przekazanej pamięci.

### `reinterpret_cast`

`reinterpret_cast` pozwala na określone konwersje niskopoziomowe, m.in. między niepowiązanymi typami wskaźników. Nie wykonuje konwersji wartości liczbowej tak jak `static_cast` i nie daje ogólnego pozwolenia na odczytanie wskazywanego obiektu jako innego typu.

```cpp
struct DaneA { int liczba; };
struct DaneB { double liczba; };

DaneA a{42};
DaneB *b = reinterpret_cast<DaneB *>(&a);  // Rzutowanie może być dozwolone składniowo
// b->liczba;  // Nie wolno zakładać, że pod tym adresem istnieje obiekt DaneB
```

Samo utworzenie takiego wskaźnika nie tworzy obiektu `DaneB`, nie zapewnia mu właściwego wyrównania ani czasu życia. Dereferencja może prowadzić do niezdefiniowanego zachowania. Do kopiowania reprezentacji typów trywialnie kopiowalnych w C++20 można rozważyć `std::bit_cast` z `<bit>`; źródło i cel muszą mieć ten sam rozmiar. `bit_cast` także nie definiuje przenośnego formatu pliku ani sieciowego — bajty reprezentacji mogą zależeć od platformy.

Nie używaj `reinterpret_cast` tylko dlatego, że kompilator odrzuca inne rzutowanie. Najpierw ustal, jaki obiekt faktycznie znajduje się pod danym adresem i jakie reguły pamięci obowiązują.

## Własne konwersje w C++

Konstruktor z jednym wymaganym argumentem może pozwolić przekształcić inny typ w obiekt klasy. Bez `explicit` taka konwersja może zostać użyta niejawnie:

```cpp
class Ulamek {
public:
    Ulamek(int liczba) : licznik_(liczba), mianownik_(1) {}
private:
    int licznik_;
    int mianownik_;
};

Ulamek u = 5;  // Kompilator tworzy Ulamek z liczby 5
```

To zachowanie nie zawsze jest pożądane: liczba całkowita może nie być oczywistym zamiennikiem ułamka przy wyborze przeciążonej funkcji. `explicit` blokuje taką niejawną konwersję, ale pozwala jawnie utworzyć obiekt:

```cpp
class Ulamek {
public:
    explicit Ulamek(int liczba) : licznik_(liczba), mianownik_(1) {}
private:
    int licznik_;
    int mianownik_;
};

Ulamek u{5};       // Poprawne: jawna inicjalizacja
// Ulamek v = 5;   // Błąd: wymagałoby niejawnej konwersji
```

Funkcja konwersji działa w przeciwną stronę — przekształca obiekt na inny typ. Dla konwersji, która nie powinna następować przypadkiem, również używaj `explicit`:

```cpp
#include <cmath>

class Zespolona {
public:
    Zespolona(double rzeczywista, double urojona)
        : rzeczywista_(rzeczywista), urojona_(urojona) {}

    explicit operator double() const {
        return std::hypot(rzeczywista_, urojona_);
    }

private:
    double rzeczywista_;
    double urojona_;
};

Zespolona z{3.0, 4.0};
double modul = static_cast<double>(z);  // Jawnie prosimy o moduł: 5.0
```

Jawność ogranicza przypadkowe konwersje, ale nie ocenia ich sensu matematycznego. Projektuj konwersję tak, by jej wynik miał jedno intuicyjne znaczenie; w przeciwnym razie lepsza może być nazwana metoda, np. `modul()`.

### Jak wybierać zapis

- Dla wartości arytmetycznych najpierw sprawdź typ operacji i możliwą utratę zakresu lub precyzji; jawny zapis nie usuwa tych ograniczeń.
- Dla rzutowania w dół w hierarchii użyj `dynamic_cast`, jeśli rzeczywisty typ jest niepewny. `static_cast` wymaga, byś już wiedział, że obiekt ma odpowiedni typ pochodny.
- `const_cast` stosuj tylko przy znanej gwarancji, że obiekt nie jest modyfikowany przez API albo sam nie był pierwotnie stały.
- `reinterpret_cast` zostaw dla interfejsów niskopoziomowych z dobrze udokumentowanymi warunkami pamięci.
- Dla własnych klas preferuj `explicit`, gdy niejawną konwersję trudno uznać za oczywistą.

Konwersja decyduje, jaki typ argumentu otrzyma wywoływana funkcja. W następnej notatce zobaczymy to w praktyce na lambdach: obiektach funkcyjnych, które przyjmują argumenty i mogą przechowywać własny stan.
