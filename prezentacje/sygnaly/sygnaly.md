## Sygnały w języku C

Sygnały w języku C to mechanizm umożliwiający asynchroniczną komunikację między procesami. Są to specjalne zdarzenia, które mogą zostać wysłane do procesu, aby poinformować go o wystąpieniu pewnego zdarzenia, np. odbioru danych od innego procesu, końcu działania innego procesu lub błędzie wewnętrznym. Sygnały mogą być wykorzystywane w różnorodnych sytuacjach, od obsługi wyjątkowych warunków (jak próba dzielenia przez zero) po komunikację między procesami.

Po otrzymaniu sygnału, proces ma trzy podstawowe opcje:
1. Wykonać domyślne działanie związane z sygnałem.
2. Obsłużyć sygnał za pomocą zdefiniowanego przez użytkownika przerwania.
3. Zignorować sygnał (choć warto zaznaczyć, że nie wszystkie sygnały są ignorowalne).

## Komunikacja międzyprocesowa (IPC) i rola sygnałów

Kiedy mówimy o komunikacji między procesami w kontekście systemów operacyjnych, sygnały to tylko jedna z wielu technik służących do tego celu. IPC (Inter-Process Communication) to zbiorczy termin dla mechanizmów, które pozwalają procesom na wymianę danych i komunikację ze sobą. 

Sygnały w kontekście IPC służą głównie do informowania procesów o pewnych zdarzeniach. Można je traktować jako pewnego rodzaju "budziki", które informują proces o tym, że coś ważnego się stało. Na przykład, sygnał może być użyty do poinformowania procesu, że inny proces, z którym współpracuje, zakończył działanie lub wymaga uwagi.

Inne mechanizmy IPC obejmują:
- **Potoki (Pipes):** Umożliwiają przesyłanie danych między spokrewnionymi procesami w jednym kierunku.
- **Gniazda (Sockets):** Pozwalają na komunikację między procesami zarówno lokalnie, jak i w sieci.
- **Kolejki komunikatów:** Umożliwiają wymianę danych w formie komunikatów między procesami.
- **Semafory:** Używane do synchronizacji dostępu do wspólnych zasobów.
- **Pamięć współdzielona:** Umożliwia wielu procesom dostęp do wspólnego bloku pamięci.

Podczas gdy każdy z tych mechanizmów pełni unikalną rolę w komunikacji między procesami, sygnały są często używane jako mechanizm powiadamiania lub alarmowania procesów o konkretnych zdarzeniach.

## Generowanie sygnałów

W języku C biblioteka `<signal.h>` dostarcza funkcji służących do generowania i obsługi sygnałów. Możemy generować sygnały za pomocą funkcji `raise()` i `kill()`.

- **raise(int signum)**: Wysyła sygnał o określonym numerze (signum) do aktualnie wykonywanego programu. Jeśli operacja przebiegnie pomyślnie, funkcja zwraca 0. W przypadku błędu zwraca wartość różną od zera.

- **kill(pid_t pid, int signum)**: Wysyła sygnał o określonym numerze (signum) do procesu o podanym identyfikatorze (pid). Umożliwia to komunikację sygnałami między różnymi procesami. Jeśli operacja zakończy się powodzeniem, zwraca 0, w przeciwnym razie zwraca wartość -1.

Po wysłaniu pewnych sygnałów (na przykład SIGINT lub SIGTERM), domyślne działanie to zakończenie procesu. W tym przypadku kod po instrukcji `raise()` lub `kill()` nie zostanie wykonany, chyba że sygnał został przechwycony i obsłużony w inny sposób.

```c
#include <signal.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  // wysłanie sygnału SIGINT do aktualnie wykonywanego programu
  if (raise(SIGINT) != 0) {
    perror("Błąd podczas wysyłania sygnału");
    return 1;
  }

  // Jeśli sygnał SIGINT nie zostanie obsłużony w specjalny sposób, 
  // ta linijka nie zostanie wykonana
  printf("Wysłano sygnał SIGINT \n");

  return 0;
}
```

Warto również pamiętać, że niektóre sygnały nie mogą być zignorowane lub przechwycone, takie jak SIGKILL.

## Obsługa sygnałów

Obsługa sygnałów w języku C umożliwia procesowi reagowanie na określone sygnały w sposób zdefiniowany przez programistę. To, jak proces reaguje na sygnał, zależy od zarejestrowanej funkcji obsługi dla tego sygnału.

Aby zarejestrować funkcję obsługi dla sygnału, używana jest funkcja `signal()`, która przyjmuje dwa argumenty: numer sygnału oraz wskaźnik do funkcji obsługi.

Poniżej przedstawiono przykład obsługi sygnału `SIGINT`:

```c
#include <signal.h>
#include <stdio.h>

void obsluga(int signum)
{
    printf("Otrzymano sygnał %d\n", signum);
}

int main()
{
    if (signal(SIGINT, obsluga) == SIG_ERR) {
        perror("Nie można zarejestrować funkcji obsługi");
        return 1;
    }

    printf("Program oczekuje na sygnał...\n");

    while(1); // nieskończona pętla oczekiwania na sygnał

    return 0;
}
```

W powyższym kodzie:

- Funkcja obsluga służy jako handler dla sygnału SIGINT.
- Używając funkcji `signal()`, rejestrujemy funkcję obsluga jako handler dla sygnału SIGINT.
- Główna pętla programu jest nieskończona, więc program będzie oczekiwać na sygnały w nieskończoność.
- Gdy proces otrzyma sygnał SIGINT, wywoła funkcję obsluga, która wyświetli na ekranie informację o otrzymanym sygnale.

Chociaż sygnał SIGINT można wygenerować, używając kombinacji klawiszy Ctrl+C w terminalu, warto pamiętać, że sygnały można wysyłać również przy użyciu różnych narzędzi systemowych i funkcji programistycznych, takich jak `kill()`.

Pamiętaj też, że obsługa sygnałów powinna być jak najkrótsza i unikać wywoływania funkcji, które nie są bezpieczne dla sygnałów (takich jak `malloc`, `free` i wielu innych). Dlatego często rekomenduje się ustawianie flag w handlerach sygnałów i obsługę sygnału w głównej części programu.
