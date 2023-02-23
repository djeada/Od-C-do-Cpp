## Pamiec operacyjna

Pamięć operacyjna, zwana również pamięcią RAM (Random Access Memory), to rodzaj pamięci komputera, w której programy przechowują dane podczas wykonywania.

Pamięć wykorzystywana przez program podzielona jest m.in. na:

- Stos
- Stertę

## Stos

* Stos to część pamięci, która przechowuje tymczasowe zmienne, argumenty przekazywane funkcjom oraz zmienne tworzone w obrębie funkcji.
* Zmienne są dostępne tylko lokalnie i łatwo można je odkłać oraz zdejmować ze stosu.
* Kiedy zmienne nie są już wykorzystywane, są automatycznie ściągane ze stosu.
* Stos to liniowa struktura danych, gdzie LIFO (Last In, First Out) określa porządek dodawania i usuwania elementów.
* Wielkość stosu jest stała i zależy od komputera, a próba włożenia zbyt wielu elementów może spowodować błąd stack overflow.
* Użycie zmiennej zapisanej na stosie poza funkcją, która ją tam umieściła, jest błędem i może prowadzić do nieprzewidywalnego zachowania programu.

## Sterta

* Sterta to obszar pamięci, który może być dynamicznie wykorzystywany przez program.
* Sterta wymaga ręcznego zarządzania pamięcią,Sterta wymaga ręcznego zarządzania pamięcią, co oznacza, że konieczne jest korzystanie z wskaźników w celu uzyskania dostępu do pamięci. co oznacza, że konieczne jest korzystanie z wskaźników w celu uzyskania dostępu do pamięci.
* Alokacja pamięci na stercie odbywa się za pomocą funkcji malloc, a dealokacja przez funkcję free.
* W przypadku braku dealokacji może wystąpić wyciek pamięci.
* Zmienne zdefiniowane na stercie są dostępne z całego programu.
* Stos jest szybszy w dostępie do pamięci niż sterta.

## Po co używać sterty?

- Dzięki stercie zmienna stworzona w funkcji może żyć dłużej niż wywołanie funkcji.
- Nie musisz się przejmować długością życia zmiennych odłożonych na stertę, będą one żyć tak długo, aż explicite zwolnisz pamięć.
- Stos jest mniejszy niż sterta. Gdy mamy dostęp z dużymi danymi (np. dla obrazów) możemy użyć sterty.
- Struktury danych zaimplementowane w bibliotece standardowej (np. std::vector) trzymają swoje dane na stercie.
    
## Przyklad

```c++
int* utworz_tablice(int rozmiar) {
    int* tablica = (int*) malloc(rozmiar * sizeof(int));
    return tablica;
}

// Nielegalne w C++, g++ z flagą -pedantic nie skompiluje tego kodu
int* utworz_tablice_zle(int rozmiar) {
    int tablica[rozmiar] = {0};
    return tablica;
}
```

## Malloc vs new (free vs delete)

 | malloc                                 |   new| 
 |  ----------------------------------------|  --------------------------------| 
 |  funkcja      |                             operator| 
|   zwraca void*   |                          nic nie zwraca| 
|   w razie błędu zwraca NULL  |               w razie błędu wyrzuca wyjątek| 
 |  nie może być nadpisany         |           może być nadpisany| 
 |  sami podejmy liczbę bajtów do alokacji |   kompilator liczy za nas| 

1. Rezerwacja pamięci: new i malloc 
2. Inicjalizacja zasobów: tylko new 
3. Niszczenie zasobów: tylko delete 
4. Zwalnianie pamięci: delete i free

Warto zwrócić uwagę, że stosowanie new i delete zamiast malloc i free jest zalecane w C++, ponieważ pozwala to na korzystanie z mechanizmu zarządzania pamięcią zwanej RAII (Resource Acquisition Is Initialization). Dzięki temu można uniknąć problemów związanych z wyciekami pamięci, a także poprawić czytelność i bezpieczeństwo kodu.
