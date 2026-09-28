#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static sem_t semafor;

static void *zadanie(void *arg) {
  int id = *(const int *)arg;

  if (sem_wait(&semafor) != 0) {
    perror("sem_wait");
    return NULL;
  }

  printf("Watek %d wszedl do sekcji limitowanej semaforem.\n", id);

  const struct timespec opoznienie = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};
  nanosleep(&opoznienie, NULL);

  printf("Watek %d wychodzi.\n", id);

  if (sem_post(&semafor) != 0) {
    perror("sem_post");
  }

  return NULL;
}

int main(void) {
  enum { LICZBA_WATKOW = 4 };
  pthread_t watki[LICZBA_WATKOW];
  int identyfikatory[LICZBA_WATKOW] = {0, 1, 2, 3};

  if (sem_init(&semafor, 0, 2) != 0) {
    perror("sem_init");
    return EXIT_FAILURE;
  }

  int utworzone = 0;
  for (; utworzone < LICZBA_WATKOW; ++utworzone) {
    int wynik =
        pthread_create(&watki[utworzone], NULL, zadanie, &identyfikatory[utworzone]);
    if (wynik != 0) {
      fprintf(stderr, "pthread_create: %d\n", wynik);
      break;
    }
  }

  for (int i = 0; i < utworzone; ++i) {
    pthread_join(watki[i], NULL);
  }

  sem_destroy(&semafor);
  return utworzone == LICZBA_WATKOW ? EXIT_SUCCESS : EXIT_FAILURE;
}
