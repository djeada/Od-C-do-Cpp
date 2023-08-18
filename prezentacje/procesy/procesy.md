## Procesy

Procesy w C to niezależne jednostki, które wykonują programy. Każdy proces posiada swój własny obszar pamięci i może wykonywać zadania równolegle do innych procesów. Procesy są podstawowym mechanizmem działania systemów operacyjnych i pozwalają na realizację wielu zadań jednocześnie.

## Tworzenie procesów

Tworzenie nowych procesów w systemach bazujących na Unix jest kluczowe dla wielu aplikacji, które potrzebują równoległego przetwarzania lub wyizolowanego środowiska dla pewnych zadań. Język C oferuje kilka funkcji, które umożliwiają tworzenie i zarządzanie procesami.

### `fork()`: Podstawowe tworzenie procesów

Najbardziej podstawową funkcją do tworzenia procesów jest `fork()`. Kiedy jest wywoływana, proces, który ją wywołał (proces macierzysty), jest duplikowany, tworząc nowy proces (proces potomny). Obie wersje programu (macierzysty i potomny) rozpoczynają wykonywanie od miejsca, gdzie została wywołana funkcja `fork()`.

- **Zwraca**:
  - 0 w procesie potomnym.
  - PID (identyfikator procesu) procesu potomnego w procesie macierzystym.
  - -1 w przypadku błędu.

```cpp
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Błąd podczas tworzenia procesu potomnego
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        printf("Jestem procesem potomnym z PID: %d\n", getpid());
    } else {
        printf("Jestem procesem macierzystym z PID: %d, mój potomek ma PID: %d\n", getpid(), pid);
    }

    return 0;
}
```

### exec(): Rodzina funkcji do uruchamiania programów

Chociaż fork() pozwala na tworzenie nowych procesów, procesy te domyślnie wykonują ten sam kod co proces macierzysty. Aby uruchomić inny program w procesie potomnym, używamy jednej z funkcji z rodziny exec().

```cpp
#include <unistd.h>

int main() {
    char *args[] = {"ls", "-l", NULL};
    execvp(args[0], args);
    
    // Kody poniżej nie zostaną wykonane, chyba że wystąpi błąd w execvp.
    printf("Ta linia nie zostanie wydrukowana\n");
    return 0;
}
```

W powyższym przykładzie, po utworzeniu procesu potomnego używając fork(), w procesie potomnym używamy funkcji execvp() do uruchomienia programu ls z argumentem -l.

## Czekanie na zakończenie procesów potomnych

W systemach operacyjnych opartych na Unix, funkcje `wait()` i `waitpid()` są wykorzystywane przez procesy macierzyste do czekania na zakończenie ich procesów potomnych. Używanie tych funkcji jest kluczowe, aby zapewnić poprawne działanie programów korzystających z wielu procesów.

### `wait()`

Funkcja `wait()` pozwala procesowi macierzystemu czekać na zakończenie dowolnego z jego procesów potomnych.

- **Składnia**: `pid_t wait(int *status);`
- **Zwraca**:
  - ID procesu potomnego, jeśli zakończył on swoje działanie.
  - -1 w przypadku błędu.

### `waitpid()`

Funkcja `waitpid()` jest bardziej elastyczna niż `wait()`, pozwalając procesowi macierzystemu czekać na zakończenie konkretnego procesu potomnego lub grupy procesów.

- **Składnia**: `pid_t waitpid(pid_t pid, int *status, int options);`
- **Argumenty**:
  - `pid`: ID procesu potomnego, na którego zakończenie chcemy czekać.
  - `status`: wskaźnik na zmienną, która przechowywać będzie status zakończenia procesu potomnego.
  - `options`: flagi określające zachowanie funkcji (np. `WNOHANG` pozwala `waitpid()` na natychmiastowy powrót, jeśli żaden proces potomny nie zakończył działania).
  
- **Zwraca**:
  - ID procesu potomnego, jeśli zakończył on działanie.
  - 0, jeśli użyto flagi `WNOHANG` i żaden proces potomny nie zakończył działania.
  - -1 w przypadku błędu.

### Przykład użycia `wait()` i `waitpid()`:

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) { // Proces potomny
        printf("Jestem procesem potomnym o PID: %d\n", getpid());
        sleep(2);
        exit(3); // zakończenie procesu potomnego z kodem statusu 3
    } else { // Proces macierzysty
        printf("Jestem procesem macierzystym czekającym na potomka.\n");

        wpid = waitpid(pid, &status, 0); // Czekanie na konkretny proces potomny

        if (WIFEXITED(status)) {
            printf("Proces potomny o PID %d zakończył działanie. Kod wyjścia: %d\n", wpid, WEXITSTATUS(status));
        }
    }

    return 0;
}
```

W tym przykładzie, proces macierzysty tworzy proces potomny, który wyświetla swój PID i śpi przez 2 sekundy przed zakończeniem działania. Proces macierzysty używa funkcji waitpid() do czekania na zakończenie konkretnego procesu potomnego i następnie wyświetla kod statusu tego procesu.

## Sygnały i funkcja `kill()`

Sygnały to mechanizm komunikacji asynchronicznej w systemach Unix. Są używane do informowania procesu o pewnych zdarzeniach lub do wysyłania prośby o wykonanie pewnej akcji, takiej jak zakończenie działania.

Funkcja `kill()` umożliwia wysyłanie sygnałów do procesów. Przyjmuje ona dwa argumenty: identyfikator procesu, do którego chcemy wysłać sygnał, oraz identyfikator sygnału, który chcemy wysłać.

```cpp
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        printf("Jestem procesem potomnym\n");
        while(1) {
            printf("Czekam na sygnał...\n");
            sleep(1);
        }
    } else {
        sleep(3);
        printf("Wysyłam sygnał SIGTERM do procesu potomnego\n");
        kill(pid, SIGTERM);
    }
    return 0;
}
```

W powyższym przykładzie proces macierzysty tworzy proces potomny, który cyklicznie wypisuje komunikat "Czekam na sygnał..." co sekundę. Po trzech sekundach, proces macierzysty wysyła sygnał SIGTERM do procesu potomnego, prosząc go o zakończenie działania.

Warto zwrócić uwagę, że nie wszystkie sygnały można przechwycić lub zignorować. Na przykład sygnał SIGKILL zawsze kończy działanie procesu i nie można go przechwycić ani zignorować.

Inne często używane sygnały to SIGINT (wysyłany przez kombinację klawiszy Ctrl+C w terminalu), SIGSTOP (zatrzymuje proces) i SIGCONT (wznawia działanie wcześniej zatrzymanego procesu).

Dla pełnej listy sygnałów oraz ich opisów można odwołać się do dokumentacji systemu operacyjnego lub użyć polecenia man 7 signal w terminalu systemu Unix.

## Równoległe uruchamianie procesów

Równoległe uruchamianie procesów pozwala na wykorzystanie wielu rdzeni procesora w celu zwiększenia wydajności. Dzięki temu różne części programu lub różne programy mogą być wykonywane jednocześnie. W systemach operacyjnych typu Unix, równoległe uruchamianie procesów jest osiągane głównie za pomocą funkcji `fork()`.

Załóżmy, że chcemy wykonać pewne zadanie dla dużej ilości danych. Zamiast przetwarzać dane sekwencyjnie, możemy podzielić je na mniejsze części i przetwarzać równolegle.

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define ILOSC_PROCESOW 4

void przetwarzanie_danych(int nr) {
    printf("Przetwarzanie danych przez proces potomny %d\n", nr);
    sleep(2); // symulacja obliczeń
    printf("Proces potomny %d zakończył przetwarzanie\n", nr);
}

int main() {
    pid_t pid;
    for (int i = 0; i < ILOSC_PROCESOW; i++) {
        pid = fork();
        if (pid == 0) {
            przetwarzanie_danych(i);
            exit(0);
        }
    }

    for (int i = 0; i < ILOSC_PROCESOW; i++) {
        wait(NULL);
    }

    printf("Wszystkie procesy potomne zakończyły działanie.\n");
    return 0;
}
```

W powyższym przykładzie tworzymy 4 procesy potomne, które przetwarzają dane równolegle. Funkcja wait() w procesie macierzystym gwarantuje, że wszystkie procesy potomne zakończą swoje działanie przed zakończeniem procesu macierzystego.
Komunikacja między równolegle działającymi procesami

Podczas równoległego uruchamiania procesów, często pojawia się konieczność komunikacji między nimi. Istnieje kilka mechanizmów, które pozwalają procesom komunikować się ze sobą:

- Potoki (pipes): Pozwalają na przekazywanie danych między procesami w jednym kierunku.
- Gniazda (sockets): Są bardziej uniwersalne niż potoki i umożliwiają dwukierunkową komunikację między procesami.
- Współdzielona pamięć: Umożliwia różnym procesom dostęp do tej samej przestrzeni w pamięci, ale wymaga mechanizmów synchronizacji, aby zapobiec problemom z równoczesnym dostępem.
- Semafor: Może być używany do blokowania i odblokowywania zasobów, zapewniając, że tylko jeden proces ma do nich dostęp w danym momencie.

## Komunikacja między procesami

Procesy w systemie operacyjnym działają niezależnie od siebie, ale czasami potrzebują komunikować się między sobą, wymieniając dane lub koordynując działania. Istnieje wiele mechanizmów do komunikacji między procesami (Inter-Process Communication, IPC), takich jak potoki (pipes), semafory, gniazda (sockets) i współdzielona pamięć.

### Potoki

Potoki to mechanizm pozwalający na przekazywanie danych między procesami. Najczęściej używane są do przekazywania danych wyjściowych z jednego procesu do innego jako dane wejściowe.

Przykład:

```cpp
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd[2];
    pid_t pid;

    // Utworzenie potoku
    pipe(fd);

    pid = fork();
    if (pid == 0) {
        // Proces potomny

        // Zamknięcie deskryptora zapisu w potomku
        close(fd[1]);

        // Przekierowanie standardowego wejścia na potok
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        // Wywołanie programu, który odczytuje dane z potoku
        execlp("wc", "wc", "-l", NULL);
    } else {
        // Proces macierzysty

        // Zamknięcie deskryptora odczytu w macierzystym
        close(fd[0]);

        // Zapis do potoku
        write(fd[1], "Hello, World\n", 13);
        close(fd[1]);
    }
    return 0;
}
```

W powyższym przykładzie, proces macierzysty pisze do potoku, a proces potomny odczytuje z niego. Program wc jest wywoływany w potomku i zlicza liczbę linii.

### Synchronizacja

Kiedy procesy współdziałają, czasami muszą być zsynchronizowane, aby uniknąć konfliktów czy problemów z równoczesnym dostępem do zasobów. Semafor to jedno z narzędzi, które pozwalają na kontrolowanie dostępu do zasobów między wieloma procesami. Może być używany do blokowania i odblokowywania zasobów w celu zapewnienia, że tylko jeden proces ma do nich dostęp w danym momencie.

Współdzielona pamięć to kolejny mechanizm IPC, który pozwala różnym procesom dostępować do tej samej przestrzeni w pamięci. Jest szybka i wydajna, ale wymaga precyzyjnej koordynacji w celu uniknięcia problemów z równoczesnym dostępem.
