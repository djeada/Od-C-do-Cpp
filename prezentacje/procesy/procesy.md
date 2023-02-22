## Procesy

Procesy w C to niezależne jednostki, które wykonują programy. Każdy proces posiada swój własny obszar pamięci i może wykonywać zadania równolegle do innych procesów. Procesy są podstawowym mechanizmem działania systemów operacyjnych i pozwalają na realizację wielu zadań jednocześnie.

## Tworzenie procesów

W języku C procesy tworzone są za pomocą funkcji `fork()`. Funkcja ta tworzy nowy proces przez duplikację bieżącego procesu. Kopiowane są wszystkie atrybuty procesu, w tym pamięć, uchwyty plików i otwarte połączenia. Funkcja zwraca wartość 0 dla procesu potomnego i wartość różną od 0 dla procesu macierzystego.

```cpp
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        printf("Jestem procesem potomnym\n");
    } else {
        printf("Jestem procesem macierzystym\n");
    }
    return 0;
}
```
W powyższym przykładzie funkcja `fork()` tworzy nowy proces i przypisuje jego identyfikator do zmiennej pid. Następnie, w zależności od wartości pid, program wyświetla odpowiedni komunikat.

## Zarządzanie procesami

W języku C procesy można zarządzać za pomocą funkcji takich jak `wait()`, `waitpid()` i `kill()`.

Funkcja `wait()` oczekuje na zakończenie procesu potomnego i zwraca jego identyfikator. Funkcja `waitpid()` działa podobnie jak `wait()`, ale pozwala na oczekiwanie na konkretny proces potomny określony przez jego identyfikator.

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid, child;
    pid = fork();
    if (pid == 0) {
        printf("Jestem procesem potomnym\n");
        sleep(5);
        exit(0);
    } else {
        printf("Jestem procesem macierzystym\n");
        child = wait(NULL);
        printf("Proces potomny %d zakończył działanie\n", child);
    }
    return 0;
}
```

W powyższym przykładzie proces macierzysty tworzy nowy proces potomny. Potem, używając funkcji `wait()`, czeka na zakończenie procesu potomnego. Po zakończeniu, wyświetla informację o jego identyfikatorze.

Funkcja `kill()` służy do wysyłania sygnałów do procesów. Sygnały to asynchroniczne powiadomienia o różnych zdarzeniach.

## Równoległe uruchamianie procesów

Uruchamianie procesów w sposób równoległy to popularne podejście do przyspieszania obliczeń na komputerze z wieloma rdzeniami lub procesorami. 

Przykładowy kod pokazuje jak uruchomić trzy procesy równolegle:

```cpp
#include <stdio.h>
#include <unistd.h>

int main() {
    int pid1, pid2, pid3;
    
    pid1 = fork();
    if (pid1 == 0) {
        printf("Proces potomny 1\n");
        // zadanie do wykonania
        return 0;
    }

    pid2 = fork();
    if (pid2 == 0) {
        printf("Proces potomny 2\n");
        // zadanie do wykonania
        return 0;
    }

    pid3 = fork();
    if (pid3 == 0) {
        printf("Proces potomny 3\n");
        // zadanie do wykonania
        return 0;
    }
    
    // czekaj na zakończenie procesów potomnych
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    printf("Wszystkie procesy potomne zakończone.\n");
    return 0;
}
```

W powyższym przykładzie trzy procesy potomne są uruchamiane równolegle przy użyciu funkcji `fork()`. Każdy proces potomny wykonuje swoje zadanie, a proces macierzysty czeka na zakończenie pracy wszystkich procesów potomnych przy użyciu funkcji `waitpid()`. Po zakończeniu pracy procesów potomnych, proces macierzysty łączy wyniki ich pracy.
