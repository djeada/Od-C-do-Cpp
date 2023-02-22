#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock = NULL;

int j = 0;

void przykladowa_funkcja() {
  pthread_mutex_lock(&lock);

  // change j
  // sleep(1);
  j++;
  printf("Aktualna wartosc j: %d\n", j);
  for (int i = 0; i < 5; i++) {
    sleep(1);
    printf("i: %d\n", i);
  }
  printf("Zakonczono proces\n");

  pthread_mutex_unlock(&lock);
}

int main() {

  pthread_t t1, t2;

  if (pthread_mutex_init(&lock, NULL) != 0) {
    printf("Inicjalizacja mutexa nie powiodla sie\n");
    return 1;
  }
  j = 0;

  pthread_create(&t1, NULL, przykladowa_funkcja, NULL);
  pthread_create(&t2, NULL, przykladowa_funkcja, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}
