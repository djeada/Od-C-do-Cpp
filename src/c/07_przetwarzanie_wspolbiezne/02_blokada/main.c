#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t lock;
int j = 0;

void *przykladowa_funkcja(void *arg) {
  (void)arg;

  pthread_mutex_lock(&lock);

  j++;
  printf("Aktualna wartosc j: %d\n", j);
  for (int i = 0; i < 5; i++) {
    sleep(1);
    printf("i: %d\n", i);
  }
  printf("Zakonczono watek\n");

  pthread_mutex_unlock(&lock);
  return NULL;
}

int main(void) {
  pthread_t t1, t2;

  if (pthread_mutex_init(&lock, NULL) != 0) {
    fprintf(stderr, "Inicjalizacja mutexa nie powiodla sie\n");
    return EXIT_FAILURE;
  }

  if (pthread_create(&t1, NULL, przykladowa_funkcja, NULL) != 0) {
    pthread_mutex_destroy(&lock);
    return EXIT_FAILURE;
  }
  if (pthread_create(&t2, NULL, przykladowa_funkcja, NULL) != 0) {
    pthread_join(t1, NULL);
    pthread_mutex_destroy(&lock);
    return EXIT_FAILURE;
  }

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_mutex_destroy(&lock);

  return EXIT_SUCCESS;
}
