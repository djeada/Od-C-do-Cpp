# Wskaźniki

Wskaźnik to zmienna, która przechowuje informacje o tym, gdzie w pamięci komputera znajduje się inna zmienna. Zmienna jest jak pudełko, w którym możemy przechowywać określone wartości (liczby, napisy, wartości logiczne).

```cpp
int x = 10;
int *p = &x;  // definicja wskaźnika p i przypisanie mu adresu zmiennej x

printf("Wartość zmiennej x: %d\n", x);
printf("Adres zmiennej x: %p\n", &x);
printf("Wartość wskaźnika p: %p\n", p);
printf("Wartość zmiennej wskazywanej przez wskaźnik p: %d\n", *p);
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

### Odejmowanie wskaźników
Różnica dwóch wskaźników to liczba półek jakie się znajdują między półkami, na które wskazują. Na przykład: 

```cpp
int a[] = {6, 2, 10};
int *p0 = a;
int *p1 = a+1;
int *p2 = a+2;
printf("p2-p0: %d\n",p2-p0); // p2-p0: 2
printf("p2-p1: %d\n",p2-p1); // p2-p1: 1
printf("p0-p1: %d\n",p0-p1); // p0-p1: -1
```

### Czy wskaźnik może nie wskazywać na nic?
Tak, może. Możemy przypisać wskaźnikowi wartość NULL, co spowoduje, że wskaźnik nie będzie nic wskazywał. Dwa puste wskaźniki są zawsze równe, stąd przydatność do wyznaczania granic różnych struktur danych.

## Operatory wskaźników
Operatory wskaźników to znaczki, które wykonują określoną operację, gdy są użyte razem z wskaźnikiem. Oto kilka przykładowych operatorów:

| znaczek | co to robi? | przykład |
| ------- | ----------- | -------- |
| * | deklaracja wskaźnika | `int *p;` |
| * | wyłuskanie wartości na którą wskazuje | `printf("%d", *p);` |
| +-, -+ | inkrementacja/dekremntacja | `p = p + 1;` |
| ==, != | porównanie dwóch wskaźników | `if(p == NULL)` |

## Czego nie należy robić ze wskaźnikami?
- Wskaźniki nigdy nie powinny być używane przed inicjalizacją.
- Odwoływanie się do wskaźnika do którego nie przydzielono pamięci.
- Mylenie znaczków i zamienne stosowanie wskaźników i zmiennych na które wskazują.
- Wyjechanie wskaźnikiem za tablicę.
