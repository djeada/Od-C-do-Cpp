Po otrzymaniu sygnału proces ma trzy możliwości:

1.  Wykonać domyślne działanie.

2.  Obsłużyć sygnał.

3.  Zignorować sygnał (nie wszystkie sygnały są ignorowalne).

Komunikacja między procesami

-   Każdy proces ma własną przestrzeń adresów.

-   Jeśli jeden proces chce przekazać jakąś informację do innego
    procesu, to odbywa się to poprzez jeden z mechnizmów IPC.

-   Komunikacja między procesami może być widoczna jako metoda
    współpracy pomiędzy procesami.

-   Komunikacja może odbywać się zarówno między spokrewnionymi
    procesami, jak i między procesami, które nie są spokrewnione.

Generowanie sygnałów

-   Biblioteka \<signal.h\> zawiera funkcje, które pozwalają na
    wywołanie sygnałów.

-   Sygnały są generowane przez wywołanie funkcji raise() lub kill().

-   Funkcja raise(int numer) wysyła sygnał o danym numerze do aktualnie
    wykonywanego programu.

-   Funkcja kill() wysyła sygnał do procesu o podanym identyfikatorze.

-   Jeśli funkcja raise() zakończy się powodzeniem, to zwrócone
    zostanie 0.

-   Po wysłaniu sygnału, wykonywanie aktualnego procesu zostaje
    zatrzymane.

``` {.c++ language="C++"}
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

Obsługa sygnałów

``` {.c++ language="C++"}
#include <signal.h>
#include <stdio.h>

  void handler(int signum)
  {
    printf("Wywołano obsługę sygnału %d \n", signum);
  }

  int main(int argc, char *argv[])
  {
    // obsługa sygnału SIGINT
    signal(SIGINT, handler);

    // ta linijka nie zostanie wykonana
    printf("Wysłano sygnał SIGINT \n");

    return 0;
  }
```
