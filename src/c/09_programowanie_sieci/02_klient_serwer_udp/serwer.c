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

int main(void) {
  int gniazdo = socket(AF_INET, SOCK_DGRAM, 0);
  if (gniazdo < 0) {
    perror("socket");
    return EXIT_FAILURE;
  }

  struct sockaddr_in adresSerwera = {0};
  adresSerwera.sin_family = AF_INET;
  adresSerwera.sin_addr.s_addr = htonl(INADDR_ANY);
  adresSerwera.sin_port = htons(UZYWANY_PORT);

  if (bind(gniazdo, (struct sockaddr *)&adresSerwera, sizeof(adresSerwera)) <
      0) {
    perror("bind");
    close(gniazdo);
    return EXIT_FAILURE;
  }

  struct sockaddr_in klient = {0};
  socklen_t dlugoscKlienta = sizeof(klient);
  char wiadomosc[ROZMIAR_BUFORA];
  ssize_t odebrano =
      recvfrom(gniazdo, wiadomosc, sizeof(wiadomosc) - 1, 0,
               (struct sockaddr *)&klient, &dlugoscKlienta);
  if (odebrano < 0) {
    perror("recvfrom");
    close(gniazdo);
    return EXIT_FAILURE;
  }
  wiadomosc[odebrano] = '\0';

  errno = 0;
  char *koniec = NULL;
  long liczba = strtol(wiadomosc, &koniec, 10);
  if (errno != 0 || koniec == wiadomosc || *koniec != '\0' ||
      liczba == LONG_MIN) {
    fprintf(stderr, "Nieprawidlowa wiadomosc: %s\n", wiadomosc);
    close(gniazdo);
    return EXIT_FAILURE;
  }

  liczba--;
  char odpowiedz[ROZMIAR_BUFORA];
  int zapisano = snprintf(odpowiedz, sizeof(odpowiedz), "%ld", liczba);
  if (zapisano < 0 || (size_t)zapisano >= sizeof(odpowiedz)) {
    close(gniazdo);
    return EXIT_FAILURE;
  }

  if (sendto(gniazdo, odpowiedz, (size_t)zapisano, 0,
             (struct sockaddr *)&klient, dlugoscKlienta) < 0) {
    perror("sendto");
    close(gniazdo);
    return EXIT_FAILURE;
  }

  close(gniazdo);
  return EXIT_SUCCESS;
}
