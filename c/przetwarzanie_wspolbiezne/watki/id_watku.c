#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *calls(void *ptr) {
  // using pthread_self() get current thread id
  printf("HIn function \nthread id = %d\n", pthread_self());
  pthread_exit(NULL);
  return NULL;
}

int main() {

  pthread_t thread;
  pthread_create(&thread, NULL, calls, NULL);
  printf("In main \nthread id = %d\n", thread);
  pthread_join(thread, NULL);

  return 0;
}
