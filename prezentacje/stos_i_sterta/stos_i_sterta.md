## Pamiec operacyjna

Pamięć operacyjna, zwana również pamięcią RAM (Random Access Memory), to rodzaj pamięci komputera, w której programy przechowują dane podczas wykonywania.

Pamięć wykorzystywana przez program podzielona jest m.in. na:

- Stos
- Stertę

## Stos

Stos to część pamięci przechowująca tymczasowe zmienne, argumenty przekazywane funkcjom oraz zmienne tworzone w obrębie funkcji. Jest to pamięć dostępna tylko lokalnie i łatwo wkładać oraz zdejmować. Kiedy zmienne nie są więcej wykorzystywane, ściągane są ze stosu. Jest to liniowa struktura danych, gdzie LIFO (Last In, First Out) określa porządek dodawania i usuwania elementów. Stos ma stałą wielkość określoną przez twój komputer, a przy próbie włożenia zbyt wiele na stos może wystąpić błąd stack overflow. Popularnym błędem jest próba użycia zmiennej zapisanej na stosie poza funkcją, która tą zmienną odłożyła na stos.

## Sterta

Sterta to duże pole pamięci, które można wykorzystywać dynamicznie. Nikt za nas nie zarządza pamięcią, dlatego dostęp do pamięci odbywa się poprzez wskaźniki. Alokujemy pamięć przy użyciu funkcji malloc i dealokujemy przy użyciu funkcji free. W przeciwnym razie może wystąpić wyciek pamięci (pamięć której nie używamy jest dla nas trzymana). Sterta nie ma ograniczeń poza fizyczną pamięcią komputera i zmienne zdefiniowane na stercie są dostępne z całego programu. Jednakże, stos jest szybszy w dostępie od sterty.

## Po co używać sterty?

- Dzięki stercie zmienna stworzona w funkcji może żyć dłużej niż wywołanie funkcji.
- Nie musisz się przejmować długością życia zmiennych odłożonych na stertę, będą one żyć tak długo, aż explicite zwolnisz pamięć.
- Stos jest mniejszy niż sterta. Gdy mamy dostęp z dużymi danymi (np. dla obrazów) możemy użyć sterty.
- Struktury danych zaimplementowane w bibliotece standardowej (np. std::vector) trzymają swoje dane na stercie.
    
## Przyklad

``` {.c++ language="C++"}
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
