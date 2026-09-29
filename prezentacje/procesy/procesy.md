# Procesy w systemach Unix

Proces to uruchomiona instancja programu wraz z własnym stanem: przestrzenią adresową, deskryptorami plików, identyfikatorem PID i kontekstem wykonania.

## Cele

Po tej prezentacji powinieneś umieć:

- odróżnić program od procesu,
- wyjaśnić działanie `fork()`,
- uruchomić inny program za pomocą rodziny `exec()`,
- odebrać status procesu potomnego przez `waitpid()`,
- wskazać podstawowe mechanizmy IPC.

## Program a proces

**Program** to plik wykonywalny i dane zapisane na dysku.

**Proces** to działający program wraz z zasobami przydzielonymi przez system operacyjny.

Typowy proces ma m.in.:

- PID — identyfikator procesu,
- własną wirtualną przestrzeń adresową,
- stos i stertę,
- otwarte deskryptory plików,
- bieżący katalog roboczy,
- maskę i obsługę sygnałów.

## Tworzenie procesu: `fork()`

W systemach POSIX `fork()` tworzy proces potomny.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        printf("potomek: pid=%ld, ppid=%ld\n",
               (long)getpid(), (long)getppid());
    } else {
        printf("rodzic: pid=%ld, child=%ld\n",
               (long)getpid(), (long)pid);
    }

    return EXIT_SUCCESS;
}
```

Wartość zwracana przez `fork()`:

- `-1` — błąd, proces potomny nie powstał,
- `0` — jesteśmy w procesie potomnym,
- dodatni PID — jesteśmy w rodzicu, a wartość to PID potomka.

## Co jest kopiowane po `fork()`?

Rodzic i potomek mają logicznie osobne przestrzenie adresowe. Zmiana zwykłej zmiennej w jednym procesie nie zmienia jej w drugim.

W praktyce systemy często używają **copy-on-write**: strony pamięci są współdzielone do chwili, gdy któryś proces spróbuje je zmodyfikować.

Deskryptory otwartych plików są dziedziczone i mogą odnosić się do tych samych obiektów jądra.

## Rodzina `exec()`

`exec` nie tworzy nowego procesu. Zastępuje aktualny obraz procesu innym programem.

Jeżeli `exec` zakończy się sukcesem, nie wraca do kodu wywołującego.

Typowy wzorzec to **fork + exec**:

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        char *argv[] = {"ls", "-l", NULL};
        execvp(argv[0], argv);

        perror("execvp");
        _exit(127);
    }

    int status = 0;
    if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
```

## Czekanie na proces potomny

`wait()` czeka na dowolnego potomka.

`waitpid()` pozwala wskazać konkretny PID i dodatkowe opcje:

```c
pid_t result = waitpid(pid, &status, 0);
```

Analiza statusu:

```c
if (WIFEXITED(status)) {
    printf("kod wyjścia: %d\n", WEXITSTATUS(status));
} else if (WIFSIGNALED(status)) {
    printf("zakończony sygnałem: %d\n", WTERMSIG(status));
}
```

## Zombie i orphan

**Zombie** to zakończony proces, którego rodzic nie odebrał jeszcze statusu przez `wait()` lub `waitpid()`. Nie wykonuje już kodu, ale wpis z informacją o zakończeniu pozostaje w tablicy procesów.

**Orphan** to proces, którego rodzic zakończył się wcześniej. System przekazuje opiekę nad nim odpowiedniemu procesowi systemowemu.

Dlatego rodzic powinien regularnie odbierać status zakończonych potomków.

## Sygnały i `kill()`

`kill()` wysyła sygnał do procesu lub grupy procesów:

```c
#include <signal.h>

if (kill(pid, SIGTERM) < 0) {
    perror("kill");
}
```

Typowe sygnały:

| Sygnał | Znaczenie |
| --- | --- |
| `SIGINT` | zwykle Ctrl+C w terminalu |
| `SIGTERM` | prośba o zakończenie procesu |
| `SIGKILL` | natychmiastowe zakończenie; nie można go przechwycić ani zignorować |
| `SIGSTOP` | zatrzymanie; nie można go przechwycić ani zignorować |
| `SIGCONT` | wznowienie zatrzymanego procesu |
| `SIGCHLD` | zmiana stanu procesu potomnego |

## IPC — komunikacja między procesami

Osobne przestrzenie adresowe oznaczają, że procesy potrzebują jawnego mechanizmu komunikacji.

Najczęstsze mechanizmy:

- potoki,
- FIFO,
- gniazda,
- pamięć współdzielona,
- kolejki komunikatów,
- sygnały,
- semafory i inne mechanizmy synchronizacji.

## Potok: prosty przykład

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int fd[2];

    if (pipe(fd) < 0) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        close(fd[1]);

        char buffer[64] = {0};
        ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);
        if (n > 0) {
            printf("potomek odebrał: %s\n", buffer);
        }

        close(fd[0]);
        _exit(0);
    }

    close(fd[0]);

    const char message[] = "hello";
    if (write(fd[1], message, strlen(message)) < 0) {
        perror("write");
    }

    close(fd[1]);
    waitpid(pid, NULL, 0);
    return EXIT_SUCCESS;
}
```

Proces powinien zamknąć te końce potoku, których nie używa. Inaczej łatwo doprowadzić np. do sytuacji, w której czytający nigdy nie zobaczy EOF.

## Równoległość i współbieżność

Kilka procesów może wykonywać pracę współbieżnie, a na wielu rdzeniach także równolegle.

```c
for (int i = 0; i < 4; ++i) {
    pid_t pid = fork();

    if (pid == 0) {
        wykonaj_zadanie(i);
        _exit(0);
    }

    if (pid < 0) {
        perror("fork");
        break;
    }
}

while (wait(NULL) > 0) {
}
```

W praktycznym kodzie warto przechowywać PID-y, obsługiwać błędy oraz kontrolować liczbę jednoczesnych procesów.

## Najczęstsze pułapki

- Kod po `fork()` wykonują oba procesy.
- `exec()` zastępuje program w bieżącym procesie — nie tworzy kolejnego procesu.
- Brak `wait()` może pozostawić procesy zombie.
- Po `fork()` buforowane dane stdio mogą zostać zdublowane; trzeba uważać na buforowanie przed rozwidleniem.
- Po `fork()` każdy proces powinien zamknąć niepotrzebne deskryptory.
- Sygnały są mechanizmem powiadamiania, a nie wygodnym kanałem do przesyłania dużych danych.

## Podsumowanie

Najważniejszy model:

```text
fork()  -> nowy proces
exec()  -> nowy program w bieżącym procesie
wait()  -> odbiór statusu potomka
pipe()  -> kanał danych między procesami
kill()  -> wysłanie sygnału
```

Połączenie tych mechanizmów stanowi podstawę wielu powłok, serwerów i narzędzi systemowych Unix.
