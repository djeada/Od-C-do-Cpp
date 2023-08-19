## Wskaźniki

Wskaźnik w języku C (i wielu innych językach programowania) to specjalny typ zmiennej, który przechowuje adres innej zmiennej w pamięci. Dzięki wskaźnikom możemy uzyskać dostęp do wartości innej zmiennej oraz modyfikować ją poprzez odwołanie do jej adresu. Wskaźniki są kluczowym narzędziem w programowaniu niskopoziomowym, szczególnie przy zarządzaniu pamięcią i pracy z tablicami czy strukturami danych.

Poniżej kilka podstawowych informacji na temat wskaźników:

- **Definicja wskaźnika**: Aby zdefiniować wskaźnik, używamy znaku `*` przed nazwą zmiennej podczas deklaracji. Np. `int *p;` deklaruje wskaźnik do zmiennej typu `int`.

- **Pobieranie adresu zmiennej**: Aby uzyskać adres zmiennej, używamy operatora `&` przed nazwą zmiennej.

- **Dereferencja wskaźnika**: Aby uzyskać dostęp do wartości zmiennej, do której wskaźnik wskazuje, używamy operatora `*` przed nazwą wskaźnika.

Przyjrzyjmy się przykładowemu kodowi, który przedstawia działanie wskaźników:

```cpp
#include <stdio.h>

int main() {
    int x = 10;           // zwykła zmienna typu int
    int *wsk = &x;        // wskaźnik typu int wskazujący na x

    printf("Wartość zmiennej x: %d\n", x);
    printf("Adres zmiennej x: %p\n", &x);
    printf("Wartość wskaźnika wsk: %p\n", wsk);
    printf("Wartość zmiennej wskazywanej przez wskaźnik wsk: %d\n", *wsk);

    return 0;
}
```

W powyższym kodzie:

- Zmienna x jest typu int i przechowuje wartość 10.
- Wskaźnik wsk jest zainicjowany adresem zmiennej x, więc "wskazuje" na x.
- Gdy używamy *wsk, odnosimy się do wartości zmiennej x.

Wskaźniki są potężnym narzędziem, ale wymagają precyzyjności i uwagi. Błędy w ich użyciu mogą prowadzić do problemów z pamięcią, takich jak wycieki pamięci czy naruszenie segmentu pamięci.

## Dlaczego wskaźnik musi mieć typ?

Wskaźnik musi mieć określony typ, aby język programowania wiedział, jak interpretować dane przechowywane pod adresem, do którego wskaźnik wskazuje. Typ wskaźnika określa, ile bajtów pamięci powinno być traktowane jako jednostka informacji. Dlatego wskaźnik na `int` wskazuje na 4 bajty pamięci (w wielu systemach), podczas gdy wskaźnik na `double` wskazuje na 8 bajtów.

Innymi słowy, typ wskaźnika określa "rozmiar kroku", jaki wskaźnik powinien podjąć, gdy jest inkrementowany lub dekrementowany, oraz ilość pamięci, która powinna być odczytana lub zapisana, gdy wskaźnik jest dereferencjowany.

Poniżej znajduje się tabela przedstawiająca typowe rozmiary poszczególnych typów danych (można zauważyć różnice w zależności od architektury i kompilatora):

| typ          | ilość miejsca (w bajtach) |
| ------------ | -------------------------- |
| char         | 1                          |
| short        | 2                          |
| int          | 4 (zazwyczaj)              |
| long         | 4 lub 8 (zależne od systemu)|
| float        | 4                          |
| double       | 8                          |

Aby sprawdzić rzeczywisty rozmiar danego typu w konkretnym środowisku programistycznym, można użyć operatora `sizeof`:

```cpp
printf("%zu", sizeof(short));
```

Warto zwrócić uwagę, że używamy specyfikatora formatu `%zu` zamiast `%d`, ponieważ wynik `sizeof` jest typu `size_t`, który jest typem całkowitym bez znaku.

## Wskaźniki, a tablice

Wskaźniki i tablice są ze sobą ściśle powiązane w języku C i C++. Nazwa tablicy jest w rzeczywistości wskaźnikiem na jej pierwszy element. Dlatego operacje na wskaźnikach mogą być łatwo używane do manipulowania tablicami.

### Przechodzenie po tablicy za pomocą wskaźników
Elementy tablicy są przechowywane w pamięci w sposób sekwencyjny. Możemy używać wskaźników do przeglądania elementów tablicy. Inkrementacja wskaźnika powoduje przesunięcie go do kolejnego elementu tablicy, a dekrementacja cofa go do poprzedniego elementu.

Jednak trzeba być ostrożnym, aby nie przekroczyć granic tablicy. Dostęp do pamięci poza tablicą jest niezdefiniowanym zachowaniem i może prowadzić do nieprzewidywalnych wyników lub błędów.

### Różnica wskaźników
Różnica między dwoma wskaźnikami (zakładając, że oba wskazują na elementy tej samej tablicy) pokazuje, ile elementów znajduje się między nimi. Wskaźniki można odejmować, ale nie można ich dodawać bezpośrednio do siebie.

Przykład:

```cpp
int tablica[] = {6, 2, 10};
int *wsk0 = tablica;
int *wsk1 = tablica + 1;
int *wsk2 = tablica + 2;

printf("wsk2-wsk0: %ld\n", wsk2 - wsk0); // wsk2-wsk0: 2
printf("wsk2-wsk1: %ld\n", wsk2 - wsk1); // wsk2-wsk1: 1
printf("wsk0-wsk1: %ld\n", wsk0 - wsk1); // wsk0-wsk1: -1
```

W powyższym przykładzie wsk0, wsk1 i wsk2 są wskaźnikami wskazującymi na kolejne elementy tablicy. Różnica między nimi reprezentuje różnicę w ich pozycjach w tablicy.

Aby pracować efektywnie z wskaźnikami i tablicami, warto znać i rozumieć te zależności oraz zachować ostrożność podczas manipulowania wskaźnikami.

## Czy wskaźnik może nie wskazywać na nic?

Tak, wskaźnik może nie wskazywać na żadne konkretne miejsce w pamięci. W takim przypadku nazywamy go wskaźnikiem nullowym lub wskaźnikiem niezainicjowanym. Wskaźnikowi możemy przypisać wartość `NULL` (lub w C++ wartość `nullptr`), co oznacza, że wskaźnik nie wskazuje na żadną konkretną zmienną czy obszar pamięci. Wskaźniki nullowe są często używane do sygnalizowania, że wskaźnik nie jest aktualnie używany lub że nie odnosi się do żadnego ważnego miejsca w pamięci.

```cpp
int* wsk = NULL;

if (wsk == NULL) {
    printf("Wskaźnik jest ustawiony na NULL\n");
}
```

Sprawdzanie wskaźników pod kątem wartości NULL jest ważne przed próbą dostępu do wartości, na którą wskazują, aby uniknąć błędów wykonywania.

### Operatory wskaźników

Wskaźniki w języku C (i C++) współpracują z określonym zestawem operatorów, które pozwalają manipulować wskaźnikami i uzyskiwać dostęp do wartości, na które wskazują. Poniżej znajduje się przegląd najczęściej używanych operatorów wskaźników:

| Operator | Opis                                        | Przykład                       |
| -------- | ------------------------------------------- | ------------------------------ |
| `*`      | Dereferencja: pobiera wartość, na którą wskazuje wskaźnik. | `int value = *ptr;`           |
| `&`      | Operator adresu: pobiera adres zmiennej.    | `int *ptr = &variable;`        |
| `++`     | Inkrementacja wskaźnika: przesuwa wskaźnik do następnego adresu. | `ptr++;`                      |
| `--`     | Dekrementacja wskaźnika: przesuwa wskaźnik do poprzedniego adresu. | `ptr--;`                      |
| `+`      | Dodaje wartość do wskaźnika.                | `ptr = ptr + 3;`              |
| `-`      | Odejmuje wartość od wskaźnika.              | `ptr = ptr - 2;`              |
| `==, !=` | Porównanie wskaźników: sprawdza, czy wskaźniki wskazują na ten sam adres lub różne adresy. | `if (ptr != NULL)`       |

Warto pamiętać, że podczas operacji na wskaźnikach, jak dodawanie czy odejmowanie, zmiana wartości wskaźnika zależy od typu wskaźnika. Na przykład, jeśli mamy wskaźnik na int i inkrementujemy go, wskaźnik przesunie się o rozmiar int w pamięci.

## Czego nie należy robić ze wskaźnikami?

Wskaźniki są jednym z najpotężniejszych i jednocześnie jednym z najbardziej skomplikowanych aspektów języka C (i C++). Właściwe korzystanie z wskaźników może prowadzić do efektywnych i wydajnych programów, ale ich nieprawidłowe używanie może prowadzić do trudnych do zidentyfikowania błędów. Oto kilka wskazówek, czego unikać przy pracy z wskaźnikami:

1. **Nie korzystaj z niezainicjowanych wskaźników.** Przed użyciem wskaźnika upewnij się, że został zainicjowany. Wskaźniki niezainicjowane wskazują na nieznane miejsca w pamięci i ich używanie może prowadzić do nieprzewidywalnych błędów.
2. **Nie dereferencjuj wskaźników nullowych.** Próbując dostać się do wartości, na którą wskazuje wskaźnik `NULL`, napotkasz błąd wyjątku naruszenia segmentu.
3. **Uważaj na wycieki pamięci.** Jeśli przydzielasz pamięć dynamicznie (np. za pomocą `malloc` w C lub `new` w C++), pamiętaj, by ją później zwolnić (za pomocą `free` lub `delete`).
4. **Nie korzystaj z pamięci po jej zwolnieniu.** Odnoszenie się do obszaru pamięci po jego zwolnieniu jest błędem i może prowadzić do nieprzewidywalnego zachowania.
5. **Bądź ostrożny z arytmetyką wskaźników.** Przesuwając wskaźnik, upewnij się, że nie wskazuje on na miejsce poza zakresem zaalokowanej pamięci lub tablicy.
6. **Nie korzystaj z wskaźników na lokalne zmienne po zakończeniu funkcji.** Lokalne zmienne są przechowywane na stosie i są usuwane po zakończeniu funkcji. Wskaźnik na taką zmienną stanie się nieprawidłowy po zakończeniu funkcji.
7. **Nie przypisuj wskaźnikom wartości, które nie są adresami.** Przypisanie losowej wartości wskaźnikowi może prowadzić do niezamierzonych błędów.
8. **Dokładnie zrozum różnicę między operatorem `&` (adres) a `*` (dereferencja).** Często początkujący programiści mylą te dwa operatory.
9. **Ograniczaj użycie wskaźników tam, gdzie można je zastąpić bezpieczniejszymi konstrukcjami.** Współczesne języki programowania, takie jak C++ lub Rust, oferują struktury, które są bardziej bezpieczne niż surowe wskaźniki, np. inteligentne wskaźniki w C++.
