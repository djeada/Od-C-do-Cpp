#include <unistd.h> 
#include <stdio.h> 
  
int main() 
{ 
    // Stworz piersze dziecko
    int wynik_funkcji_fork_1 = fork();
  
    // Stworz drugie dziecko
    int wynik_funkcji_fork_2 = fork();

    printf("Wynik funkcji fork_1: %d\n", wynik_funkcji_fork_1);
    printf("Wynik funkcji fork_2: %d\n", wynik_funkcji_fork_2);
  
    if (n1 > 0 && n2 > 0) 
    { 
        printf("Jestem rodzicem\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
    } 
    else if (n1 == 0 && n2 > 0) 
    { 
        printf("Jestem dzieckiem nr 1\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
    } 
    else if (n1 > 0 && n2 == 0) 
    { 
        printf("Jestem dzieckiem nr 2\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
    } 
    else { 
        printf("\nJestem dzieckiem nr 3\n");
        printf("PID: %d\n", getpid());
        printf("PPID: %d\n", getppid());
    } 
  
    return 0; 
} 

