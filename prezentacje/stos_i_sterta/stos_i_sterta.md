## Pamięć operacyjna

Pamięć operacyjna, często nazywana pamięcią RAM (Random Access Memory), to rodzaj pamięci komputera, w którym system operacyjny, aplikacje i dane w użyciu są tymczasowo przechowywane, by mogły być szybko dostępne dla procesora.

Pamięć, w której programy przechowują dane podczas wykonywania, podzielona jest głównie na:

- Stos
- Stertę

## Stos

* Stos to część pamięci, która przechowuje tymczasowe zmienne, argumenty przekazywane funkcjom oraz zmienne lokalne tworzone w obrębie funkcji.
* Zmienne są dostępne tylko lokalnie, tzn. wewnątrz funkcji, w której zostały zadeklarowane.
* Kiedy funkcja kończy swoje działanie, jej zmienne są automatycznie usuwane ze stosu.
* Jest to liniowa struktura danych, działająca według zasady LIFO (Last In, First Out), co określa porządek dodawania i usuwania elementów.
* Wielkość stosu jest ograniczona i zależy od systemu oraz architektury komputera. Przekroczenie tego limitu prowadzi do błędu "stack overflow".
* Dostęp do zmiennej zapisanej na stosie poza jej zakresem funkcji jest błędem i może prowadzić do nieprzewidywalnego zachowania programu.

## Sterta

* Sterta to obszar pamięci, który może być dynamicznie zarządzany przez program.
* Sterta wymaga ręcznego zarządzania pamięcią, co oznacza, że programista musi jawnie alokować i zwalniać pamięć. Do tego celu używane są wskaźniki.
* Pamięć na stercie jest alokowana przy użyciu funkcji, takich jak `malloc`, a zwalniana za pomocą funkcji `free` w języku C.
* Niewłaściwe zarządzanie stertą, np. niezwalnianie zaalokowanej pamięci, może prowadzić do wycieków pamięci.
* Zmienne zdefiniowane na stercie są dostępne z różnych części programu, aż do momentu ich dealokacji.
* Chociaż stos jest zazwyczaj szybszy w dostępie do pamięci niż sterta, sterta oferuje większą elastyczność, umożliwiając dynamiczne alokowanie i dealokowanie pamięci w trakcie działania programu.

## Po co używać sterty?

- Dzięki stercie, zmienna lub obiekt stworzony w funkcji może przetrwać dłużej niż czas trwania tej funkcji.
- Sterta umożliwia dynamiczną alokację pamięci. Oznacza to, że możemy przydzielić pamięć w trakcie działania programu, w zależności od aktualnych potrzeb.
- Pamięć zaalokowana na stercie będzie dostępna aż do momentu, kiedy jawnie zostanie zwolniona przez programistę.
- Sterta jest znacznie większa niż stos. W przypadku pracy z dużymi ilościami danych, takimi jak obrazy czy filmy, używanie sterty jest niezbędne.
- Wiele struktur danych i klas w bibliotece standardowej (np. `std::vector`, `std::string`) trzyma swoje dane na stercie, aby zapewnić elastyczność w zarządzaniu pamięcią.

## Przykład

W poniższym przykładzie pierwsza funkcja `utworz_tablice` tworzy tablicę na stercie, a druga, `utworz_tablice_zle`, próbuje stworzyć tablicę na stosie o zmiennej długości i zwrócić wskaźnik do niej, co jest nieprawidłowe.

```c++
int* utworz_tablice(int rozmiar) {
    int* tablica = (int*) malloc(rozmiar * sizeof(int));
    return tablica;
}

// Nielegalne w C++. Gdy kompilujesz z flagą -pedantic, g++ zgłosi błąd
int* utworz_tablice_zle(int rozmiar) {
    int tablica[rozmiar] = {0};
    return tablica;
}
```

Warto zwrócić uwagę, że dynamiczna alokacja pamięci, choć potężna, niesie za sobą odpowiedzialność za odpowiednie zarządzanie pamięcią, w tym zwalnianie pamięci, która nie jest już potrzebna.

## Malloc vs new (free vs delete)

| Kategoria                                | malloc                               | new                              |
| ---------------------------------------- | ------------------------------------ | -------------------------------- |
| Rodzaj                                   | funkcja                              | operator                         |
| Typ zwracany                             | zwraca `void*`                       | nic nie zwraca                   |
| Reakcja na błąd                          | w razie błędu zwraca `NULL`          | w razie błędu wyrzuca wyjątek    |
| Nadpisywanie                             | nie może być nadpisany              | może być nadpisany              |
| Określenie liczby bajtów do alokacji     | sami podajemy liczbę bajtów         | kompilator liczy za nas         |

### Kluczowe różnice:

1. **Rezerwacja pamięci:** Obydwie funkcje - `new` i `malloc` - służą do rezerwacji pamięci.
2. **Inicjalizacja zasobów:** Tylko `new` po rezerwacji pamięci dodatkowo inicjalizuje zasoby (np. wywołując konstruktor w przypadku obiektów).
3. **Niszczenie zasobów:** Tylko `delete` przed zwolnieniem pamięci niszczy zasoby (np. wywołując destruktor w przypadku obiektów).
4. **Zwalnianie pamięci:** Obydwa - `delete` i `free` - służą do zwalniania pamięci, ale powinny być używane w parach odpowiednio z `new` i `malloc`.

### Dlaczego zaleca się `new` i `delete` w C++?
Stosowanie `new` i `delete` zamiast `malloc` i `free` jest zalecane w C++, ponieważ pozwala to na korzystanie z mechanizmu zarządzania pamięcią zwanej RAII (Resource Acquisition Is Initialization). Dzięki temu można uniknąć problemów związanych z wyciekami pamięci, a także poprawić czytelność i bezpieczeństwo kodu.
