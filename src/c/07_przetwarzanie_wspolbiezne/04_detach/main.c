#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *threadFn(void *arg) {
  (void)arg;

  int wynik = pthread_detach(pthread_self());
  if (wynik != 0) {
    fprintf(stderr, "Nie udalo sie odlaczyc watku: %d\n", wynik);
    return NULL;
  }

  sleep(1);
  printf("ThreadFn\n");
  return NULL;
}

int main(void) {
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, threadFn, NULL);
  if (ret != 0) {
    fprintf(stderr, "Blad tworzenia watku: %d\n", ret);
    return EXIT_FAILURE;
  }

  printf("After thread created in Main\n");
  pthread_exit(NULL);
}
