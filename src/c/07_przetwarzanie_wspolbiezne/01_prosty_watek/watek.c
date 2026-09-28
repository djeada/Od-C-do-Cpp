#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *print_message_function(void *ptr) {
  const char *message = ptr;
  printf("%s\n", message);
  return NULL;
}

int main(void) {
  pthread_t thread1, thread2;
  const char *message1 = "Thread 1";
  const char *message2 = "Thread 2";

  int iret1 =
      pthread_create(&thread1, NULL, print_message_function, (void *)message1);
  if (iret1 != 0) {
    fprintf(stderr, "Nie udalo sie utworzyc watku 1: %d\n", iret1);
    return EXIT_FAILURE;
  }

  int iret2 =
      pthread_create(&thread2, NULL, print_message_function, (void *)message2);
  if (iret2 != 0) {
    fprintf(stderr, "Nie udalo sie utworzyc watku 2: %d\n", iret2);
    pthread_join(thread1, NULL);
    return EXIT_FAILURE;
  }

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("Thread 1 returns: %d\n", iret1);
  printf("Thread 2 returns: %d\n", iret2);

  return EXIT_SUCCESS;
}
