# Wskaźniki funkcyjne, do składowych i inteligentne wskaźniki

Wskaźnik to wartość, która może przechowywać adres. Sam surowy wskaźnik nie mówi jednak, kto odpowiada za obiekt ani jak długo ten obiekt będzie istniał. Ta różnica jest kluczowa: wskaźnik może jedynie **obserwować** obiekt albo uczestniczyć w zarządzaniu jego **własnością**. W C++ wskaźniki mogą też wskazywać funkcje i składowe klas.

> Przykłady ze `std::unique_ptr` i `std::make_unique` wymagają C++14. `std::shared_ptr`, `std::weak_ptr`, wskaźniki do funkcji i wskaźniki do składowych są dostępne od C++11.

## Wskaźnik a czas życia obiektu

Obiekt lokalny istnieje do chwili wyjścia z bloku, w którym został utworzony. Wskaźnik do takiego obiektu nie przedłuża jego życia:

```cpp
#include <iostream>

int main() {
    int* wskaznik = nullptr;

    {
        int liczba = 7;
        wskaznik = &liczba;
        std::cout << *wskaznik << '\n'; // poprawnie: liczba jeszcze istnieje
    }

    // tutaj wskaznik nadal przechowuje dawny adres, ale liczba już nie istnieje
    // *wskaznik; // błąd: użycie wiszącego wskaźnika
}
```

Po wyjściu z bloku `wskaznik` jest **wiszący** (*dangling pointer*). Jego dereferencja — użycie `*wskaznik` lub `wskaznik->pole` — ma niezdefiniowane zachowanie. Surowy wskaźnik nie usuwa też obiektu sam z siebie. Jeżeli nie wskazuje na żaden obiekt, powinien mieć wartość `nullptr`; sprawdź ją przed dereferencją.

Gdy funkcja tylko korzysta z obiektu, ale nie zarządza jego życiem, zwykle czytelniejsza i bezpieczniejsza jest referencja (`T&` lub `const T&`): oznacza ona, że obiekt istnieje podczas wywołania i nie przenosi własności. Wskaźnik jest uzasadniony, gdy brak obiektu jest dozwolony (`nullptr`), gdy trzeba zmienić wskazywany obiekt albo gdy API wymaga wskaźnika.

## Wskaźniki na funkcje

Wskaźnik na funkcję przechowuje adres funkcji o dokładnie zgodnym typie: liczą się typy argumentów i typ zwracany. Dzięki temu można przekazać operację do innej funkcji, zamiast zapisywać jej nazwę na stałe:

```cpp
#include <iostream>

void zwieksz(int x) { std::cout << x + 1 << '\n'; }
void zmniejsz(int x) { std::cout << x - 1 << '\n'; }

void wykonaj(void (*operacja)(int), int wartosc) {
    operacja(wartosc);
}

int main() {
    wykonaj(zwieksz, 10); // przekazujemy adres funkcji zwieksz
    wykonaj(zmniejsz, 10);
}
```

Typ parametru `void (*operacja)(int)` czytamy: „`operacja` jest wskaźnikiem na funkcję, która przyjmuje `int` i zwraca `void`”. Nawiasy są istotne: `void *operacja(int)` oznacza funkcję `operacja`, która zwraca `void*`, a nie wskaźnik na funkcję.

Wskaźnik na funkcję nie przechowuje obiektu i nie przedłuża jego czasu życia. Przekazując nazwę przeciążonej funkcji, czasem trzeba wskazać właściwą wersję przez jawny typ wskaźnika — wybór przeciążenia omawia [notatka o przeciążaniu](18_przeciazanie.md).

## Wskaźniki do składowych klasy

Zwykły wskaźnik do pola, na przykład `int*`, zawiera adres konkretnego pola konkretnego obiektu. Wskaźnik **do składowej klasy** wskazuje natomiast, które pole lub metodę wybrać, ale sam nie wskazuje konkretnego obiektu. Do użycia potrzebuje obiektu tej klasy. Z tego powodu jego typ ma specjalną składnię:

```cpp
#include <iostream>

struct Punkt {
    int x;
    int y;

    void wypisz() const {
        std::cout << '(' << x << ", " << y << ")\n";
    }
};

int main() {
    int Punkt::* wybranePole = &Punkt::x;
    Punkt p{10, 20};

    p.*wybranePole = 15; // wybierz pole x w obiekcie p
    std::cout << p.x << '\n';

    void (Punkt::*wybranaMetoda)() const = &Punkt::wypisz;
    (p.*wybranaMetoda)();

    Punkt* adresPunktu = &p;
    adresPunktu->*wybranePole = 30;
    std::cout << p.x << '\n';
}
```

`int Punkt::*` oznacza wskaźnik do składowej typu `int` klasy `Punkt`. Operator `.*` łączy go z obiektem, a `->*` — ze wskaźnikiem do obiektu. Wskaźnik do metody zapisuje się podobnie, ale w typie trzeba uwzględnić listę parametrów i kwalifikatory metody, na przykład `void (Punkt::*metoda)() const`. To inny typ niż zwykły wskaźnik na funkcję: metoda należy do klasy i do wywołania nadal potrzebuje obiektu.

### Jak czytać deklaracje

Nawiasy w deklaracjach wskaźników nie są ozdobą — zmieniają znaczenie. Porównaj:

| Deklaracja | Znaczenie |
| --- | --- |
| `int* p` | `p` jest wskaźnikiem na `int` |
| `int** p` | `p` jest wskaźnikiem na wskaźnik na `int` |
| `int* tab[3]` | `tab` jest tablicą trzech wskaźników na `int` |
| `int (*tab)[3]` | `tab` jest wskaźnikiem na tablicę trzech wartości `int` |
| `int* pobierz()` | `pobierz` jest funkcją zwracającą wskaźnik na `int` |
| `int (*funkcja)(int)` | `funkcja` jest wskaźnikiem na funkcję przyjmującą `int` i zwracającą `int` |

Praktyczna metoda czytania: zacznij od nazwy, a potem uwzględnij nawiasy. Na przykład w `int (*funkcja)(int)` nawias wokół `*funkcja` wiąże wskaźnik z nazwą; końcowe `(int)` mówi, że wskazywany element jest funkcją.

## Inteligentne wskaźniki i własność

Inteligentny wskaźnik z biblioteki `<memory>` jest obiektem, który przechowuje adres oraz stosuje ustaloną regułę zarządzania czasem życia. Pasuje do idiomu **RAII**: zasób zostaje powiązany z obiektem, a jego zwolnienie następuje automatycznie podczas niszczenia właściciela. Dzięki temu zwykle nie trzeba ręcznie wywoływać `delete`.

Wybór typu odpowiada na pytanie „kto jest właścicielem?”:

| Typ | Własność | Kiedy obiekt jest niszczony? |
| --- | --- | --- |
| `std::unique_ptr<T>` | jeden właściciel | gdy ten właściciel znika lub oddaje obiekt |
| `std::shared_ptr<T>` | wielu współwłaścicieli | gdy znika ostatni `shared_ptr` współdzielący obiekt |
| `std::weak_ptr<T>` | brak własności | sam nie niszczy ani nie utrzymuje obiektu przy życiu |

Jeśli obiekt ma właściciela przez cały czas życia w programie, nie zawsze trzeba go alokować dynamicznie. Zwykła zmienna lokalna często jest prostsza. Inteligentny wskaźnik jest przydatny, gdy obiekt rzeczywiście ma żyć niezależnie od bloku wywołującego albo gdy jego własność musi być przekazywana.

### `std::unique_ptr` — jeden właściciel

`unique_ptr` jest niewyłącznym w dostępie, ale **wyłącznym w posiadaniu**: wiele miejsc może chwilowo obserwować obiekt przez referencję lub zwykły wskaźnik, lecz właściciel jest tylko jeden. Nie można kopiować `unique_ptr`, bo powstałyby dwa obiekty próbujące zwolnić ten sam zasób. Własność można przenieść:

```cpp
#include <iostream>
#include <memory>
#include <utility>

int main() {
    auto pierwszy = std::make_unique<int>(5);
    auto drugi = std::move(pierwszy);

    std::cout << *drugi << '\n'; // 5
    std::cout << static_cast<bool>(pierwszy) << '\n'; // 0: jest pusty
}
```

`std::move` samo nie przenosi obiektu — pozwala wybrać operację przenoszącą. W przypadku `unique_ptr` po przeniesieniu `drugi` staje się właścicielem, a `pierwszy` jest pusty. Nie należy później dereferencjonować pustego wskaźnika.

Używaj `std::make_unique<T>(...)` do tworzenia obiektu. Nie konstruuj dwóch właścicieli z tego samego surowego adresu:

```cpp
int* adres = new int(5);
std::unique_ptr<int> a(adres);
// std::unique_ptr<int> b(adres); // błąd: drugi właściciel tego samego adresu
```

Odkomentowanie ostatniej linii utworzyłoby dwóch właścicieli tego samego adresu. Oba obiekty próbowałyby usunąć tę samą wartość, co prowadzi do niezdefiniowanego zachowania. `make_unique` tworzy obiekt i właściciela w jednym wyrażeniu, więc nie trzeba przechowywać surowego adresu pomiędzy tymi operacjami.

Załóżmy, że w programie istnieje typ `Dane`. Sygnatura funkcji powinna pokazywać, czy przekazuje własność:

```cpp
void uzyj(const Dane& dane);                    // tylko odczyt, bez przejęcia własności
void zmien(Dane& dane);                         // modyfikacja, bez przejęcia własności
void przejmij(std::unique_ptr<Dane> dane);       // funkcja przejmuje własność
```

Wywołanie `przejmij(std::move(wsk))` przekazuje własność funkcji. Jeśli funkcja ma tylko czytać lub zmieniać obiekt, zwykle nie powinna otrzymywać inteligentnego wskaźnika przez wartość.

### `std::shared_ptr` — współdzielona własność

`shared_ptr` stosuj wtedy, gdy kilka niezależnych części programu naprawdę potrzebuje współdecydować o czasie życia tego samego obiektu. Kopiowanie `shared_ptr` dodaje współwłaściciela; obiekt jest niszczony dopiero po zniknięciu ostatniego właściciela:

```cpp
#include <iostream>
#include <memory>

int main() {
    auto pierwszy = std::make_shared<int>(5);
    {
        auto drugi = pierwszy; // drugi współdzieli własność z pierwszym
        std::cout << *drugi << '\n';
    } // drugi znika, ale pierwszy nadal jest właścicielem

    std::cout << *pierwszy << '\n';
} // dopiero tutaj znika ostatni właściciel i obiekt jest niszczony
```

Kopiowanie `shared_ptr` jest inne niż kopiowanie wskazywanego obiektu: oba wskaźniki odnoszą się do tego samego obiektu. Samo posiadanie `shared_ptr` nie czyni dostępu do obiektu bezpiecznym wątkowo — synchronizacja danych jest osobnym zagadnieniem.

Nie używaj `shared_ptr` domyślnie. Współdzielenie utrudnia ustalenie, kto odpowiada za moment zniszczenia obiektu. Szczególnym problemem jest cykl: jeśli A posiada `shared_ptr` do B, a B posiada `shared_ptr` do A, licznik właścicieli nigdy nie spadnie do zera. W takim powiązaniu jeden z kierunków powinien zwykle być obserwowany przez `weak_ptr`.

### `std::weak_ptr` — obserwator bez własności

`weak_ptr` może obserwować obiekt zarządzany przez `shared_ptr`, ale nie zwiększa liczby współwłaścicieli i nie przedłuża życia obiektu. Przed dostępem trzeba wywołać `lock()`. Wynik jest lokalnym `shared_ptr`, który utrzymuje obiekt przy życiu przez czas korzystania z niego:

```cpp
#include <iostream>
#include <memory>

struct Dane {
    int wartosc = 42;
};

int main() {
    std::weak_ptr<Dane> obserwator;

    {
        auto wlasciciel = std::make_shared<Dane>();
        obserwator = wlasciciel;

        if (auto dostep = obserwator.lock()) {
            std::cout << dostep->wartosc << '\n';
        }
    } // wlasciciel znika; obiekt zostaje zniszczony

    if (auto dostep = obserwator.lock()) {
        std::cout << dostep->wartosc << '\n';
    } else {
        std::cout << "Obiekt już nie istnieje\n";
    }
}
```

Sprawdzenie `lock()` jest ważne: samo sprawdzenie, czy obiekt istniał wcześniej, nie gwarantuje, że nadal istnieje. Po `lock()` lokalna zmienna `dostep` jest właścicielem na czas działania bloku.

### Inteligentne wskaźniki do klas bazowych

Konwersja wskaźnika do klasy pochodnej na wskaźnik do publicznej, jednoznacznej klasy bazowej jest bezpieczna. Dlatego `std::unique_ptr<Prostokat>` można przenieść do `std::unique_ptr<Figura>`, a `std::shared_ptr<Prostokat>` można skopiować do `std::shared_ptr<Figura>`. Działa to tak, jak zwykłe rzutowanie w górę hierarchii.

Ważny jest jednak sposób usuwania obiektu. Jeśli `unique_ptr<Figura>` posiada obiekt `Prostokat`, przy zniszczeniu usuwa go jako `Figura*`. Destruktor bazy powinien wtedy być wirtualny — szczegóły i kompletny przykład są w [notatce o dziedziczeniu](16_dziedziczenie.md). Wartość wskaźnika sama nie przechowuje bezpiecznie „pełnego typu” na potrzeby poprawnego niszczenia przez bazę.

Nie twórz też osobnego `shared_ptr` z surowego wskaźnika, który już należy do innego `shared_ptr`:

```cpp
auto pierwszy = std::make_shared<int>(5);
// std::shared_ptr<int> drugi(pierwszy.get()); // nie rób tak: dwa bloki kontroli,
                                               // oba próbowałyby usunąć ten sam obiekt
```

Kopiuje się istniejący `shared_ptr` (`auto drugi = pierwszy;`), a nie buduje nowego właściciela z `get()`. `get()` daje tylko niewłaścicielski surowy wskaźnik.

## Krótki wybór narzędzia

- Obiekt jest lokalny i nie musi żyć dłużej niż zmienna? Użyj zwykłego obiektu.
- Funkcja ma tylko użyć istniejącego obiektu? Przekaż referencję; wskaźnik wybierz, gdy brak obiektu jest dopuszczalny.
- Potrzebny jest dynamiczny obiekt z jednym właścicielem? Zwykle `std::unique_ptr`.
- Kilka miejsc musi współdecydować o czasie życia? Rozważ `std::shared_ptr` i sprawdź, czy współwłasność naprawdę jest potrzebna.
- Potrzebny jest nieposiadający odnośnik do obiektu `shared_ptr`? Użyj `std::weak_ptr` i sprawdź wynik `lock()`.
