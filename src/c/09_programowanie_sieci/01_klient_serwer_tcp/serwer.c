#include <arpa/inet.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define UZYWANY_PORT 12345
#define ROZMIAR_BUFORA 100

int utworzGniazdo(void) { return socket(AF_INET, SOCK_STREAM, 0); }

int przygotujGniazdo(int uchwytGniazda) {
  int reuse = 1;
  if (setsockopt(uchwytGniazda, SOL_SOCKET, SO_REUSEADDR, &reuse,
                 sizeof(reuse)) < 0) {
    return -1;
  }

  struct sockaddr_in adresSerwera = {0};
  adresSerwera.sin_family = AF_INET;
  adresSerwera.sin_addr.s_addr = htonl(INADDR_ANY);
  adresSerwera.sin_port = htons(UZYWANY_PORT);

  return bind(uchwytGniazda, (struct sockaddr *)&adresSerwera,
              sizeof(adresSerwera));
}

int main(void) {
  int uchwytGniazda = utworzGniazdo();
  if (uchwytGniazda < 0) {
    perror("socket");
    return EXIT_FAILURE;
  }

  if (przygotujGniazdo(uchwytGniazda) < 0) {
    perror("bind");
    close(uchwytGniazda);
    return EXIT_FAILURE;
  }

  if (listen(uchwytGniazda, 3) < 0) {
    perror("listen");
    close(uchwytGniazda);
    return EXIT_FAILURE;
  }

  struct sockaddr_in klient = {0};
  socklen_t dlugoscKlienta = sizeof(klient);
  int klientFd = accept(uchwytGniazda, (struct sockaddr *)&klient,
                        &dlugoscKlienta);
  if (klientFd < 0) {
    perror("accept");
    close(uchwytGniazda);
    return EXIT_FAILURE;
  }

  char wiadomosc[ROZMIAR_BUFORA];
  ssize_t odebrano = recv(klientFd, wiadomosc, sizeof(wiadomosc) - 1, 0);
  if (odebrano < 0) {
    perror("recv");
    close(klientFd);
    close(uchwytGniazda);
    return EXIT_FAILURE;
  }
  wiadomosc[odebrano] = '\0';

  errno = 0;
  char *koniec = NULL;
  long liczba = strtol(wiadomosc, &koniec, 10);
  if (errno != 0 || koniec == wiadomosc || *koniec != '\0' ||
      liczba == LONG_MIN) {
    fprintf(stderr, "Nieprawidlowa wiadomosc: %s\n", wiadomosc);
    close(klientFd);
    close(uchwytGniazda);
    return EXIT_FAILURE;
  }

  liczba--;
  char odpowiedz[ROZMIAR_BUFORA];
  int zapisano = snprintf(odpowiedz, sizeof(odpowiedz), "%ld", liczba);
  if (zapisano < 0 || (size_t)zapisano >= sizeof(odpowiedz)) {
    close(klientFd);
    close(uchwytGniazda);
    return EXIT_FAILURE;
  }

  if (send(klientFd, odpowiedz, (size_t)zapisano, 0) < 0) {
    perror("send");
    close(klientFd);
    close(uchwytGniazda);
    return EXIT_FAILURE;
  }

  close(klientFd);
  close(uchwytGniazda);
  return EXIT_SUCCESS;
}
