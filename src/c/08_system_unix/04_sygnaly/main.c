#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void uchwyc_dzielenie_przez_zero(int num_sygnalu) {
  if (num_sygnalu == SIGFPE) {
    const char komunikat[] = "Odebrano SIGFPE.\n";
    write(STDOUT_FILENO, komunikat, sizeof(komunikat) - 1);
  }
}

void uchwyc_alarm(int num_sygnalu) {
  if (num_sygnalu == SIGALRM) {
    const char komunikat[] = "Alarm zostal obsluzony!\n";
    write(STDOUT_FILENO, komunikat, sizeof(komunikat) - 1);
  }
}

int main(void) {
  if (signal(SIGALRM, uchwyc_alarm) == SIG_ERR) {
    perror("signal");
    return EXIT_FAILURE;
  }

  alarm(1);
  pause();

  if (signal(SIGFPE, uchwyc_dzielenie_przez_zero) == SIG_ERR) {
    perror("signal");
    return EXIT_FAILURE;
  }

  // Dzielenie zmiennoprzecinkowe przez zero nie musi generowac SIGFPE,
  // dlatego sygnal wysylamy jawnie, aby przyklad byl przenosny.
  if (raise(SIGFPE) != 0) {
    perror("raise");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
