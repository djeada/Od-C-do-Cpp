## Sygnały w języku C

Sygnały w języku C to mechanizm, który pozwala na asynchroniczną komunikację między procesami. Sygnał to specjalne zdarzenie, które może zostać wysłane do procesu, aby poinformować go o wystąpieniu pewnego zdarzenia, np. odbioru danych od innego procesu, końcu działania innego procesu lub błędzie wewnętrznym. Po otrzymaniu sygnału proces ma trzy możliwości: wykonać domyślne działanie, obsłużyć sygnał lub zignorować sygnał (nie wszystkie sygnały są ignorowalne).


## Komunikacja między procesami

W języku C każdy proces ma własną przestrzeń adresową, co oznacza, że procesy nie mają dostępu do pamięci innych procesów. Jeśli jeden proces chce przekazać jakąś informację do innego procesu, to odbywa się to poprzez jeden z mechanizmów IPC (Inter-Process Communication). Komunikacja między procesami może być widoczna jako metoda współpracy pomiędzy procesami. Komunikacja może odbywać się zarówno między spokrewnionymi procesami, jak i między procesami, które nie są spokrewnione.

## Generowanie sygnałów

Biblioteka `<signal.h>` zawiera funkcje, które pozwalają na generowanie sygnałów. Sygnały są generowane przez wywołanie funkcji `raise()` lub `kill()`. Funkcja `raise(int numer)` wysyła sygnał o danym numerze do aktualnie wykonywanego programu. Funkcja `kill()` wysyła sygnał do procesu o podanym identyfikatorze. Jeśli funkcja `raise()` zakończy się powodzeniem, to zwrócone zostanie 0. Po wysłaniu sygnału, wykonywanie aktualnego procesu zostaje zatrzymane.

```cpp
#include <signal.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  // wysłanie sygnału SIGINT do aktualnie wykonywanego programu
  raise(SIGINT);
   
  // ta linijka nie zostanie wykonana
  printf("Wysłano sygnał SIGINT \n");

  return 0;
}
```

## Obsługa sygnałów
Obsługa sygnałów polega na zdefiniowaniu funkcji obsługi, która zostanie wykonana po otrzymaniu sygnału. Aby zdefiniować funkcję obsługi, należy utworzyć funkcję, która przyjmuje jako argument numer sygnału i zwraca typ void. Funkcja ta powinna wykonać odpowiednie działania w zależności od otrzymanego sygnału.

Aby zarejestrować funkcję obsługi dla danego sygnału, należy użyć funkcji signal, która jako argumenty przyjmuje numer sygnału i wskaźnik do funkcji obsługi.

Przykład kodu obsługi sygnału `SIGINT`:


```cpp
#include <signal.h>
#include <stdio.h>

void obsluga(int signum)
{
    printf("Otrzymano sygnał %d\n", signum);
}

int main()
{
    signal(SIGINT, obsluga); // zarejestrowanie funkcji obsługi sygnału SIGINT

    printf("Program oczekuje na sygnał...\n");

    while(1); // nieskończona pętla oczekiwania na sygnał

    return 0;
}
```

W powyższym kodzie funkcja `obsluga` jest zarejestrowana jako funkcja obsługi dla sygnału `SIGINT`. Główna pętla programu jest nieskończona, co oznacza, że program będzie oczekiwał na sygnał bez końca. Po otrzymaniu sygnału `SIGINT`, zostanie wywołana funkcja obsługi `obsluga`. W tym przypadku funkcja wyświetli na ekranie informację o otrzymanym sygnale.

Aby wysłać sygnał `SIGINT` (Ctrl+C) do programu działającego w terminalu, należy otworzyć terminal i uruchomić program, a następnie wciśnąć klawisze Ctrl+C. 
