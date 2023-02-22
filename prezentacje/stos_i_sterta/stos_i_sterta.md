Pamięć wykorzystywana przez program podzielony jest m.in. na:

-   Stos

-   Stertę

![Pamięć wykorzystywana przez program podzielony jest m.in. na: Stos i
Stertę](pamiec.png){width="\\linewidth"}

-   stos to część pamięci przechowująca tymczasowe zmienne;

-   argumenty przekazywane funkcjom są zbierane na stosie;

-   zmienne tworzone w obrębie funkcji;

-   pamięć dostępna tylko lokalnie;

-   łatwo wkładać i zdejmować;

-   kiedy zmienne nie są więcej wykorzystywane, ściągane są ze stosu;

-   liniowa struktura danych;

-   LIFO;

-   stos ma stałą wielkość określoną przez twój komputer;

-   stack overflow gdy chcemy włożyć zbyt wiele na stos;

-   popularny błąd: próba użycia zmiennej zapisanej na stosie poza
    funkcją, która tą zmienną odłożyła na stos;

```{=html}
<!-- -->
```
-   duże pole pamięci, które można wykorzystywać dynamicznie;

-   nikt za nas nie zarządza pamięcią;

-   dostęp do pamięci poprzez wskaźniki;

-   allokujemy (malloc) i dealokujemy (free);

-   w przeciwnym razie wyciek pamięci (pamięć której nie używamy jest
    dla nas trzymana);

-   nie ma ograniczeń na stertę poza fizyczną pamięcią komputera;

-   zmienne dostępne z całego programu;

-   wolniejsza w dostępie od stosu;

Po co używać sterty?

-   Dzięki stercie zmienna stworzona w funkcji może żyć dłużej niż
    wywołanie funkcji;

-   Nie musisz się przejmować długością życia zmiennch odłożonych na
    stertę, będą one żyć tak długo, aż explicite zwolnisz pamięć;

-   Stos jest mniejszy niż sterta. Gdy mamy dostęp z dużymi danymi (np.
    dla obrazów) możemy użyć sterty.

-   Struktury danych zaimplementowane w bibliotece standardowej (np.
    std::vector) trzymają swoje dane na stercie.

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

Malloc vs new (free vs delete)

  malloc                                   new
  ---------------------------------------- --------------------------------
  funkcja                                  operator
  zwraca void\*                            nic nie zwraca
  w razie błędu zwraca NULL                w razie błędu wyrzuca wyjątek
  nie może być nadpisany                   może być nadpisany
  sami podejmy liczbę bajtów do alokacji   kompilator liczy za nas
  jedynie alokuje pamięć                   dodatkowo wywołuje konstruktor

1\. Rezerwacja pamieci (new, malloc) 2. Inicjalizacja zasobow (new) 3.
Niszczenie zasobow (delete) 4. Uwalnianie pamieci (delete, free)
