#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  printf("Rodzic przed forkiem\n");
  pid_t zwroconaWartosc = fork();

  if (zwroconaWartosc < 0) {
    perror("fork");
    return EXIT_FAILURE;
  }

  printf("wartosc zwrocona przez fork: %ld\n", (long)zwroconaWartosc);

  if (zwroconaWartosc == 0) {
    printf("Dziecko jest wykonywane.\n");
    sleep(1);
    printf("Dziecko umiera.\n");
  } else {
    printf("Rodzic %ld oczekuje na dziecko\n", (long)zwroconaWartosc);
    int status = 0;
    if (waitpid(zwroconaWartosc, &status, 0) < 0) {
      perror("waitpid");
      return EXIT_FAILURE;
    }
    printf("Rodzic umiera.\n");
  }

  return EXIT_SUCCESS;
}
