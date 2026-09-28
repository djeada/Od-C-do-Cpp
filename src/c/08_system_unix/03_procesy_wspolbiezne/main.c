#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static pid_t uruchom_sleep(void) {
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return -1;
  }

  if (pid == 0) {
    execl("/bin/sleep", "sleep", "1", (char *)NULL);
    perror("execl");
    _exit(EXIT_FAILURE);
  }

  return pid;
}

void szeregowo(void) {
  pid_t pid1 = uruchom_sleep();
  if (pid1 < 0) {
    return;
  }
  waitpid(pid1, NULL, 0);

  pid_t pid2 = uruchom_sleep();
  if (pid2 < 0) {
    return;
  }
  waitpid(pid2, NULL, 0);
}

void rownolegle(void) {
  pid_t pid1 = uruchom_sleep();
  pid_t pid2 = uruchom_sleep();

  if (pid1 > 0) {
    waitpid(pid1, NULL, 0);
  }
  if (pid2 > 0) {
    waitpid(pid2, NULL, 0);
  }
}

int main(void) {
  rownolegle();
  return EXIT_SUCCESS;
}
