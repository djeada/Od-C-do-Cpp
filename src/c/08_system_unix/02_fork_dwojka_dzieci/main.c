#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
  pid_t wynik_funkcji_fork_1 = fork();
  if (wynik_funkcji_fork_1 < 0) {
    perror("fork");
    return EXIT_FAILURE;
  }

  pid_t wynik_funkcji_fork_2 = fork();
  if (wynik_funkcji_fork_2 < 0) {
    perror("fork");
    return EXIT_FAILURE;
  }

  printf("Wynik funkcji fork_1: %ld\n", (long)wynik_funkcji_fork_1);
  printf("Wynik funkcji fork_2: %ld\n", (long)wynik_funkcji_fork_2);

  if (wynik_funkcji_fork_1 > 0 && wynik_funkcji_fork_2 > 0) {
    printf("Jestem rodzicem\n");
  } else if (wynik_funkcji_fork_1 == 0 && wynik_funkcji_fork_2 > 0) {
    printf("Jestem pierwszym dzieckiem\n");
  } else if (wynik_funkcji_fork_1 > 0 && wynik_funkcji_fork_2 == 0) {
    printf("Jestem drugim dzieckiem\n");
  } else {
    printf("Jestem dzieckiem utworzonym przez pierwsze dziecko\n");
  }

  printf("PID: %ld\n", (long)getpid());
  printf("PPID: %ld\n", (long)getppid());

  return EXIT_SUCCESS;
}
