#include <arpa/inet.h>
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

  struct sockaddr_in serwer = {0};
  serwer.sin_family = AF_INET;
  serwer.sin_port = htons(UZYWANY_PORT);
  if (inet_pton(AF_INET, "127.0.0.1", &serwer.sin_addr) != 1) {
    close(gniazdo);
    return EXIT_FAILURE;
  }

  const char *wiadomosc = "41";
  if (sendto(gniazdo, wiadomosc, strlen(wiadomosc), 0,
             (struct sockaddr *)&serwer, sizeof(serwer)) < 0) {
    perror("sendto");
    close(gniazdo);
    return EXIT_FAILURE;
  }

  char odpowiedz[ROZMIAR_BUFORA];
  ssize_t odebrano = recvfrom(gniazdo, odpowiedz, sizeof(odpowiedz) - 1, 0,
                              NULL, NULL);
  if (odebrano < 0) {
    perror("recvfrom");
    close(gniazdo);
    return EXIT_FAILURE;
  }

  odpowiedz[odebrano] = '\0';
  printf("Odebrana wiadomosc: %s\n", odpowiedz);

  close(gniazdo);
  return EXIT_SUCCESS;
}
