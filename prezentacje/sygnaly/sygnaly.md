# Sygnały w C i systemach POSIX

Sygnał jest asynchronicznym powiadomieniem wysyłanym do procesu. System operacyjny używa sygnałów m.in. do informowania o przerwaniu z terminala, błędach wykonania i zmianie stanu procesu potomnego.

## Cele

Po tej prezentacji powinieneś umieć:

- wyjaśnić, czym sygnał różni się od kanału przesyłania danych,
- wysłać sygnał przez `raise()` lub `kill()`,
- zainstalować handler przez `sigaction()`,
- wskazać operacje niedozwolone w handlerze,
- rozpoznać rolę maski sygnałów.

## Co może zrobić proces po otrzymaniu sygnału?

Dla większości sygnałów proces może:

1. wykonać działanie domyślne,
2. zainstalować własną funkcję obsługi,
3. zignorować sygnał.

Dwa ważne wyjątki:

- `SIGKILL` — nie można go przechwycić ani zignorować,
- `SIGSTOP` — nie można go przechwycić ani zignorować.

## Typowe sygnały

| Sygnał | Typowe źródło / znaczenie |
| --- | --- |
| `SIGINT` | przerwanie z terminala, zwykle Ctrl+C |
| `SIGTERM` | prośba o zakończenie procesu |
| `SIGKILL` | bezwarunkowe zakończenie |
| `SIGSTOP` | zatrzymanie procesu |
| `SIGCONT` | wznowienie procesu |
| `SIGCHLD` | zmiana stanu procesu potomnego |
| `SIGPIPE` | zapis do potoku/gniazda bez czytelnika |

Dokładne działania domyślne i dostępność sygnałów należy sprawdzać w dokumentacji danej platformy, np. `man 7 signal`.

## Sygnały a IPC

Sygnały są częścią szerokiej rodziny mechanizmów IPC, ale najlepiej traktować je jako **powiadomienia**, a nie kanał do przesyłania dużych danych.

Inne mechanizmy IPC:

- potoki,
- FIFO,
- gniazda,
- kolejki komunikatów,
- pamięć współdzielona,
- semafory.

Przykładowo sygnał może powiedzieć „coś się wydarzyło”, a właściwe dane mogą być odczytane z potoku lub pamięci współdzielonej.

## Wysyłanie sygnału do siebie: `raise()`

```c
#include <signal.h>
#include <stdio.h>

int main(void) {
    puts("przed raise");

    if (raise(SIGTERM) != 0) {
        perror("raise");
        return 1;
    }

    puts("ta linia zwykle nie zostanie wykonana");
    return 0;
}
```

Przy domyślnej obsłudze `SIGTERM` proces zostanie zakończony.

## Wysyłanie sygnału do procesu: `kill()`

`kill()` jest interfejsem POSIX:

```c
#include <signal.h>
#include <sys/types.h>

if (kill(pid, SIGTERM) < 0) {
    perror("kill");
}
```

Nazwa bywa myląca: `kill()` nie zawsze „zabija” proces. Wysyła wskazany sygnał, a efekt zależy od tego sygnału i jego obsługi.

## `signal()` czy `sigaction()`?

ISO C udostępnia `signal()`, ale w programach POSIX zwykle preferuje się `sigaction()`, ponieważ daje większą kontrolę nad maską i flagami obsługi.

```c
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static volatile sig_atomic_t stop_requested = 0;

static void handle_sigint(int signum) {
    (void)signum;
    stop_requested = 1;
}

int main(void) {
    struct sigaction action;
    memset(&action, 0, sizeof(action));

    action.sa_handler = handle_sigint;
    sigemptyset(&action.sa_mask);

    if (sigaction(SIGINT, &action, NULL) < 0) {
        perror("sigaction");
        return 1;
    }

    puts("Ctrl+C ustawi flagę zakończenia");

    while (!stop_requested) {
        sleep(1);
    }

    puts("kończę poza handlerem");
    return 0;
}
```

Handler robi tylko minimalną rzecz: ustawia flagę typu `sig_atomic_t`. Normalna logika programu wykonuje się poza handlerem.

## Dlaczego nie `printf()` w handlerze?

Sygnał może przerwać program praktycznie w dowolnym miejscu. Jeżeli handler wywoła funkcję, która nie jest **async-signal-safe**, może wejść w konflikt z przerwaną operacją tej samej biblioteki.

W handlerze należy unikać m.in.:

- `printf()`,
- `malloc()` i `free()`,
- większości funkcji biblioteki standardowej,
- skomplikowanej logiki.

POSIX definiuje ograniczony zestaw funkcji async-signal-safe, np. `write()` i `_exit()`.

## Maska sygnałów

Proces może tymczasowo blokować dostarczanie wybranych sygnałów.

Do pracy z maską w POSIX służą m.in.:

- `sigemptyset()`,
- `sigaddset()`,
- `sigprocmask()`,
- `pthread_sigmask()` w programach wielowątkowych,
- `sigsuspend()`.

Blokowanie sygnału jest przydatne podczas modyfikowania danych, które mogłyby zostać równocześnie użyte przez handler.

## Standardowe sygnały nie są kolejką komunikatów

Wiele zwykłych sygnałów POSIX może się **zlewać**: jeżeli ten sam sygnał zostanie wysłany kilka razy, zanim proces go obsłuży, program nie powinien zakładać, że handler zostanie wykonany dokładnie tyle samo razy.

Dlatego licznik zdarzeń lub dane powinny być przekazywane innym mechanizmem, jeżeli utrata informacji jest niedopuszczalna.

## `SIGCHLD` i procesy potomne

Gdy proces potomny zmieni stan, rodzic może otrzymać `SIGCHLD`.

Typowy serwer lub shell wykorzystuje to do odebrania statusu przez `waitpid()` i usunięcia zakończonych procesów zombie.

Obsługa `SIGCHLD` wymaga ostrożności, ponieważ w czasie jednego przebudzenia mogło zakończyć się więcej niż jedno dziecko.

## Najczęstsze pułapki

- Używanie `printf()` lub alokacji pamięci w handlerze.
- Próba przechwycenia `SIGKILL` lub `SIGSTOP`.
- Traktowanie sygnałów jako niezawodnej kolejki zdarzeń.
- Wykonywanie całej logiki aplikacji w handlerze zamiast ustawienia flagi.
- Brak rozróżnienia między mechanizmami ISO C (`signal`, `raise`) a API POSIX (`sigaction`, `kill`, maski sygnałów).

## Podsumowanie

Bezpieczny model myślenia:

1. sygnał **powiadamia** proces,
2. handler wykonuje minimalną pracę,
3. właściwa logika odbywa się w normalnym przepływie programu,
4. dane przekazujemy przez mechanizm do tego przeznaczony.

W kodzie POSIX `sigaction()` jest zwykle lepszym punktem wyjścia niż proste `signal()`.
