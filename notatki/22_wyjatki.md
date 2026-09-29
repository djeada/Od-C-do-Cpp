# Wyjątki w C++

Wyjątek to sposób przekazania informacji o problemie z miejsca, w którym go wykryto, do miejsca, które może zdecydować, co dalej zrobić. Najczęściej używa się go wtedy, gdy funkcja nie może wykonać swojego zadania i nie ma sensownego sposobu, by naprawić sytuację lokalnie.

Ważne: C++ nie zamienia automatycznie każdego błędu w wyjątek. To kod programu lub biblioteki musi go jawnie zgłosić. Dlatego przed użyciem wyjątków warto rozróżnić kilka rodzajów problemów.

## Błąd, wyjątek i kod błędu

Słowo „błąd” opisuje problem, a „wyjątek” jest jednym ze sposobów przekazania informacji o nim. Błąd można też zgłosić kodem zwracanym przez funkcję albo wykryć jako nieprawidłowy wynik programu.

| Sytuacja | Co się dzieje | Przykład |
|---|---|---|
| Błąd składni lub typów | Kompilator odrzuca program; program nie zaczyna działania. | Brak średnika albo przypisanie tekstu do zmiennej typu `int`. |
| Błąd logiczny | Program działa, ale wynik nie odpowiada zamiarowi autora. | Pętla kończy się o jeden krok za wcześnie. |
| Niezdefiniowane zachowanie (UB) | Standard C++ nie określa wyniku; program może zadziałać różnie lub ulec awarii. Samo UB nie oznacza wyjątku. | Dzielenie całkowite przez zero lub dereferencja nieprawidłowego wskaźnika. |
| Wyjątek | Kod wykonania jawnie zgłosił obiekt wyjątku, a program może przekazać go do obsługi wyżej w stosie wywołań. | Funkcja odrzuca niedozwolony argument przez `throw std::invalid_argument(...)`. |
| Kod błędu lub stan | Funkcja zwraca informację o niepowodzeniu; wywołujący sprawdza ją i wybiera dalsze działanie. | `fopen` w C zwraca `NULL`, a strumień C++ może ustawić `failbit`. |

Na przykład dzielenie przez zero nie powoduje, że C++ sam rzuci wyjątek. Jeśli chcemy taki przypadek obsłużyć wyjątkiem, musimy najpierw sprawdzić dzielnik i sami zgłosić wyjątek. W wielu sytuacjach przewidywalny brak wyniku lepiej obsłużyć kodem błędu; wyjątek przydaje się, gdy zwykłe wykonanie funkcji nie może być kontynuowane.

## Przepływ wyjątku: `throw`, `try` i `catch`

Załóżmy, że funkcja `podziel` otrzymuje dwa argumenty. Gdy dzielnik jest równy zero, nie ma poprawnego wyniku. Zamiast zwracać przypadkową wartość, funkcja zgłasza problem:

```cpp
#include <iostream>
#include <stdexcept>

int podziel(int licznik, int mianownik) {
    if (mianownik == 0) {
        throw std::invalid_argument("Mianownik nie może być równy zero");
    }
    return licznik / mianownik;
}

int main() {
    try {
        int wynik = podziel(20, 0);
        std::cout << "Wynik: " << wynik << '\n';
    } catch (const std::invalid_argument& blad) {
        std::cerr << "Nie udało się obliczyć ilorazu: " << blad.what() << '\n';
    }
}
```

Wywołanie `podziel(20, 0)` jest przykładowym wejściem. Funkcja wykrywa niedozwolony mianownik i wykonuje `throw`. Wtedy jej zwykły dalszy kod (`return` oraz wypisanie wyniku) nie jest wykonywany. C++ szuka pasującego `catch`: najpierw w aktywnym bloku `try`, a jeśli go tam nie ma, w funkcji, która wywołała bieżącą funkcję, i dalej w kolejnych wywołaniach. W przykładzie program wypisze:

```text
Nie udało się obliczyć ilorazu: Mianownik nie może być równy zero
```

Dla wejścia `podziel(20, 4)` wyjątek nie jest zgłaszany i funkcja zwraca `5`. Blok `catch` nie zostaje wtedy wykonany.

`throw` oznacza „zgłoś problem”, `try` obejmuje operacje, które mogą taki problem zgłosić, a `catch` określa reakcję na konkretny typ problemu. Funkcja, która wykryła problem, nie musi znać decyzji całego programu: może przekazać wyjątek wyżej, np. do warstwy wyświetlającej komunikat użytkownikowi.

### Rozwijanie stosu i RAII

Funkcje działające w danej chwili tworzą stos wywołań. Jeśli wyjątek nie zostanie obsłużony w bieżącej funkcji, C++ opuszcza ją i wraca po stosie do miejsca, gdzie znajdzie odpowiedni `catch`. Ten proces nazywa się rozwijaniem stosu (stack unwinding).

Przy opuszczaniu funkcji niszczone są jej lokalne obiekty — w kolejności odwrotnej do ich tworzenia. To ważne, bo destruktory obiektów RAII zwalniają zasoby takie jak pamięć, blokada lub otwarty plik. Przykład pokazuje kolejność sprzątania:

```cpp
#include <iostream>
#include <stdexcept>

struct Slad {
    const char* nazwa;
    ~Slad() { std::cout << "Sprzątanie: " << nazwa << '\n'; }
};

void drugi_krok() {
    Slad zasob{"drugi krok"};
    throw std::runtime_error("awaria w drugim kroku");
}

void pierwszy_krok() {
    Slad zasob{"pierwszy krok"};
    drugi_krok();
}

int main() {
    try {
        pierwszy_krok();
    } catch (const std::runtime_error& blad) {
        std::cout << "Obsłużono: " << blad.what() << '\n';
    }
}
```

Po wywołaniu `pierwszy_krok()` powstaje jej lokalny obiekt, potem `drugi_krok()` tworzy swój obiekt i zgłasza wyjątek. Najpierw niszczony jest obiekt z `drugi_krok`, następnie obiekt z `pierwszy_krok`, a dopiero potem działa `catch`. Oczekiwany wynik:

```text
Sprzątanie: drugi krok
Sprzątanie: pierwszy krok
Obsłużono: awaria w drugim kroku
```

RAII zwalnia zasoby, ale samo w sobie nie cofa zmian w danych ani nie naprawia problemu. Odpowiedzialność za decyzję, czy program ma ponowić operację, poinformować użytkownika czy zakończyć pracę, należy do kodu obsługującego wyjątek.

## Jaki typ wyjątku wybrać?

Standardowa biblioteka udostępnia m.in. typy z nagłówka `<stdexcept>`:

- `std::invalid_argument` — argument funkcji nie spełnia jej warunków;
- `std::out_of_range` — wartość, np. indeks, jest poza dopuszczalnym zakresem;
- `std::runtime_error` — operacja nie powiodła się z przyczyn wykrytych podczas działania programu;
- `std::logic_error` — problem wskazuje na niepoprawne użycie lub założenie w logice programu.

Własny typ wyjątku ma sens, gdy kod wywołujący musi rozpoznać szczególną kategorię problemu. Zwykle najprościej rozszerzyć typ standardowy zamiast samodzielnie implementować `what()`:

```cpp
#include <stdexcept>
#include <string>

class BladFormatu : public std::runtime_error {
public:
    explicit BladFormatu(const std::string& opis)
        : std::runtime_error(opis) {}
};
```

Można wtedy osobno obsłużyć ten przypadek, a inne wyjątki pozostawić ogólnej obsłudze:

```cpp
try {
    // Odczyt i przetwarzanie danych.
} catch (const BladFormatu& blad) {
    // Reakcja właściwa dla niepoprawnego formatu.
} catch (const std::exception& blad) {
    // Pozostałe wyjątki standardowej biblioteki.
}
```

Bardziej szczegółowe typy umieszczaj przed typem bazowym. Gdyby `catch (const std::exception&)` znalazł się pierwszy, przechwyciłby również `BladFormatu` i późniejszy blok nie zostałby osiągnięty.

## Jak przechwytywać i przekazywać wyjątki

- Rzucaj obiekt wyjątku przez wartość, np. `throw std::runtime_error("opis");`.
- Przechwytuj przez `const` referencję, np. `catch (const std::exception& blad)`. Kopiowanie wyjątku jest niepotrzebne i mogłoby utracić informację o typie pochodnym.
- Przechwytuj tylko tam, gdzie możesz podjąć sensowną decyzję. Jeśli aktualna funkcja nie umie naprawić sytuacji, pozwól wyjątkowi przejść wyżej.
- Aby przechwycić wyjątek, wykonać część działań i przekazać ten sam wyjątek dalej, użyj `throw;` bez argumentu. Zapis `throw blad;` tworzy nowy obiekt na podstawie zmiennej i może utracić typ pochodny.
- Nie używaj pustego `catch`, bo wtedy problem znika z pola widzenia programu. Jeśli potrzebujesz awaryjnego `catch (...)`, powinien on np. zapisać informację i zakończyć działanie w kontrolowany sposób.

Jeśli wyjątek przejdzie poza `main()` bez przechwycenia, program kończy się przez `std::terminate()`. Nie należy zakładać, że po nieobsłużonym wyjątku program będzie działał dalej.

## Wyjątek czy kod błędu?

Wyobraźmy sobie funkcję, która próbuje znaleźć użytkownika w opcjonalnej pamięci podręcznej. Brak użytkownika jest normalnym wynikiem wyszukiwania, więc wygodny może być jawny wynik typu `bool`, `std::optional` lub inny kod statusu. Jeśli funkcja ma obowiązkowo zapisać raport, ale dysk jest niedostępny, może nie być w stanie spełnić swojego kontraktu — wyjątek pozwala przekazać tę informację do miejsca, które zdecyduje, czy przerwać raportowanie, spróbować innej lokalizacji czy powiadomić użytkownika.

| Mechanizm | Kiedy pasuje | Co musi zrobić wywołujący |
|---|---|---|
| Kod błędu / status | Wynik „brak danych” lub „nie znaleziono” jest spodziewaną częścią normalnego działania. | Sprawdzić zwróconą wartość i obsłużyć każdy wymagany przypadek. |
| Wyjątek | Operacja nie może spełnić swojego zadania, a obsługa jest sensowna w wyższym miejscu programu. | Umieścić operację w `try`, jeśli potrafi podjąć decyzję; w przeciwnym razie przekazać wyjątek dalej. |

Nie używaj wyjątków do zwykłego sterowania pętlą ani do każdego braku dopasowania — to utrudnia odczytanie normalnej ścieżki programu. Z drugiej strony nie zamieniaj wyjątku na milczącą wartość, jeśli przez to wywołujący nie będzie wiedział, że wymaganej operacji nie udało się wykonać.

## Czego wyjątki nie robią

- Nie wykrywają automatycznie błędów. Dzielenie całkowite przez zero, błędny wskaźnik i przepełnienie typu ze znakiem nie są automatycznie zamieniane na wyjątek C++.
- Nie naprawiają stanu programu. Jeśli wyjątek zgłoszono po częściowym zmodyfikowaniu pliku lub obiektu, te zmiany mogą pozostać.
- Nie gwarantują, że można bezpiecznie kontynuować. Obsługa powinna wiedzieć, czy dane i zasoby są w poprawnym stanie.
- Nie zastępują RAII. Nadal trzeba wiązać zasoby z czasem życia obiektów, aby zostały zwolnione podczas rozwijania stosu.

Najważniejsza zasada: zgłoś wyjątek w miejscu, gdzie wykrywasz niepowodzenie; przechwyć go tam, gdzie możesz zdecydować o dalszym działaniu; a zasoby powierz obiektom RAII.
