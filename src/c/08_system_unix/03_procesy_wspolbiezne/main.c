#include <sys/wait.h>
#include <unistd.h>

// Przyklad szeregowego vs rowneleglego programu

// int forkNexec(StrVec argList);

void szeregowo() {
  char *const parametry[] = {"/bin/sleep", "5", NULL};

  int pid1 = fork();
  execv("/bin/sleep", parametry);
  waitpid(pid1, NULL, 0);

  int pid2 = fork();
  execv("/bin/sleep", parametry);
  waitpid(pid2, NULL, 0);
}

void rownolegle() {
  char *const parametry[] = {"sleep", "5", NULL};

  int pid1 = fork();
  int pid2 = fork();

  execv("/bin/sleep", parametry);
  execv("/bin/sleep", parametry);

  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);
}

int main() {

  // szeregowo();
  rownolegle();

  return 0;
}
