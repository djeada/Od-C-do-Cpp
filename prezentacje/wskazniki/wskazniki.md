# Wskaźniki

Wskaźnik to zmienna, która przechowuje informacje o tym, gdzie w pamięci komputera znajduje się inna zmienna. Zmienna jest jak pudełko, w którym możemy przechowywać określone wartości (liczby, napisy, wartości logiczne).

```cpp
int x = 10;
int *wsk = &x;  // definicja wskaźnika p i przypisanie mu adresu zmiennej x

printf("Wartość zmiennej x: %d\n", x);
printf("Adres zmiennej x: %p\n", &x);
printf("Wartość wskaźnika p: %p\n", wsk);
printf("Wartość zmiennej wskazywanej przez wskaźnik p: %d\n", *wsk);
```

## Dlaczego wskaźnik musi mieć typ?
Wskaźnik musi wiedzieć jak daleko ma skoczyć, aby dostać się do odpowiedniego pudełka. Nie wszystkie pudełka mają taki sam rozmiar, dlatego wskaźnik musi mieć określony typ, aby wiedzieć, jaką ilość miejsca musi przeskoczyć. Poniżej znajduje się przykładowa tabela, która przedstawia ilość miejsca potrzebną dla każdego typu:

| typ          | ilość miejsca |
| ------------ | ------------- |
| char         | 1             |
| short        | 2             |
| int, long, float | 4           |
| double       | 8             |

Możemy sprawdzić ilość miejsca potrzebną dla typu, używając funkcji `printf`: 

`printf("%d", sizeof(short));`

## Wskaźniki, a tablice
Zmienne w tablicy są przechowywane obok siebie. Możemy przypisać wskaźnikowi adres dowolnej zmiennej w tablicy, a następnie przesunąć się do innych elementów, używając dodawania lub odejmowania. Jeśli w ten sposób wyjdziemy poza granice naszej tablicy, możemy spowodować błędy w programie.

Różnica dwóch wskaźników to liczba pudełek jakie się znajdują między pudełkami, na które wskazują. Na przykład: 

```cpp
int tablica[] = {6, 2, 10};
int *wsk0 = tablica;
int *wsk1 = tablica + 1;
int *wsk2 = tablica + 2;
printf("wsk2-wsk0: %ld\n", wsk2 - wsk0); // wsk2-wsk0: 2
printf("wsk2-wsk1: %ld\n", wsk2 - wsk1); // wsk2-wsk1: 1
printf("wsk0-wsk1: %ld\n", wsk0 - wsk1); // wsk0-wsk1: -1
```

## Czy wskaźnik może nie wskazywać na nic?
Tak, może. Możemy przypisać wskaźnikowi wartość NULL, co spowoduje, że wskaźnik nie będzie nic wskazywał. Dwa puste wskaźniki są zawsze równe, stąd przydatność do wyznaczania granic różnych struktur danych.

```cpp
int* wsk = NULL;

if (wsk == NULL) {
    printf("Wskaźnik jest ustawiony na NULL\n");
}
```

## Operatory wskaźników
Operatory wskaźników to znaczki, które wykonują określoną operację, gdy są użyte razem z wskaźnikiem. Oto kilka przykładowych operatorów:

| znaczek | co to robi? | przykład |
| ------- | ----------- | -------- |
| * | deklaracja wskaźnika | `int *p;` |
| * | wyłuskanie wartości na którą wskazuje | `printf("%d", *p);` |
| +-, -+ | inkrementacja/dekremntacja | `p = p + 1;` |
| ==, != | porównanie dwóch wskaźników | `if(p == NULL)` |

## Czego nie należy robić ze wskaźnikami?

* Wskaźniki to bardzo potężne narzędzie, ale z wielką mocą wiąże się wielka odpowiedzialność. Pamiętaj o tym i bądź ostrożny w ich używaniu.
* Przed użyciem wskaźnika zawsze należy go zainicjalizować wartością początkową. Wskaźniki niezainicjowane mogą prowadzić do nieprzewidywalnych błędów.
* Unikaj używania wskaźników do nieistniejących lub już zwolnionych zmiennych, ponieważ może to prowadzić do niestabilności programu i nieprzewidywalnego zachowania.
* Stosuj wskaźniki tylko do jak najmniejszego możliwego zakresu zmiennych, które wskazują, aby łatwiej kontrolować ich wartości i uniknąć nieprzewidywalnych błędów.
* Nigdy nie myl znaczków. Upewnij się, że wiesz co chcesz zrobić.
* Zawsze sprawdź, czy wartość wskaźnika jest poprawna przed użyciem go w programie.
* Unikaj wyjeżdżania wskaźnikiem poza tablicę.
* Staraj się używać wskaźników tylko wtedy, gdy jest to absolutnie konieczne. Wiele programów można napisać bez ich użycia.
