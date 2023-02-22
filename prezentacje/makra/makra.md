## Konstrukcja 'include guard'

Konstrukcja 'include guard' pozwala na uniknięcie powtórzeń przy załączaniu plików. Jeśli wielokrotnie użyjemy dyrektywy include wraz z tą samą nazwą pliku, to domyślnie zostanie on wielokrotnie załączony.

```cpp
#ifndef NAZWA_PLIKU
#define NAZWA_PLIKU

  // kod...

#endif
```

Dzięki temu zabiegowi, ten plik zostanie załączony tylko raz. Preprocesor sprawdzi, czy plik został już załączony. Jeśli tak, to zostanie pominięty.

## Makra

Dyrektywa define pozwala na definiowanie makr oraz stałych. Makra są wykonywane przed wykonaniem kodu.

Ogólna postać makra:

```cpp
# define + nazwa + cialo
```

Nazwy pisane są często dużymi literami, ale nie jest to wymagane. Domyślnie, ciało makra definiowane jest w jednym wierszu, ale przy użyciu lewego ukośnika można poszerzyć ciało makra o nowe wiersze.

```cpp
// Przykład stałej
#define PI 3.14

// Makro zwracające stałą wartość, wynik dzielenia PI przez 2
#define PI_2 PI/2

// Makro zwracające wartość przekazanej liczby podniesionej do kwadratu
#define KWADRAT(x) x*x

// Makro zwracające większą z dwóch wartości
#define MAKS_2(x,y) (x>y?x:y)

// Makro zwracające największą z trzech wartości
#define MAKS_3(x,y,z) MAKS_2(MAKS_2(x,y),z) 
```

## Makra, a funkcje

  |               Makra               |            Funkcje            |   
  -----------------------------------|  --------------------------- | 
  |      Makra nie są kompilowane      |  Funkcje są kompilowane       | 
   |      Typy nie są sprawdzane        |  Typy są sprawdzane        | 
  |  Przy wywołaniu kod jest kopiowany    |  Kod jest wykonywany       | 
   |          Szybkie              |  Szybkie, ale wolniejsze   | 
   |   Brak wsparcia dla skalowania    |  Wsparcie dla skalowania      | 
  |   Kompilator nie sprawdza błędów  |   Kompilator sprawdza błędy     | 

## Dyrektywa if

Dyrektywa `if` pozwala na warunkowe kompilacje.

```cpp
#define FLAGA 1

int main() {

  #if FLAGA
    // kod do wykonania, gdy flaga jest ustawiona
  #else
    // kod do wykonania, gdy flaga nie jest ustawiona
  #endif

  return 0;
}
```
