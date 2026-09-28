#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define UZYWANY_PORT 12345
#define ROZMIAR_BUFORA 100

int utworzGniazdo(void) { return socket(AF_INET, SOCK_STREAM, 0); }

int polaczGniazdo(int uchwytGniazda) {
  struct sockaddr_in adresSerwera = {0};
  adresSerwera.sin_family = AF_INET;
  adresSerwera.sin_port = htons(UZYWANY_PORT);

  if (inet_pton(AF_INET, "127.0.0.1", &adresSerwera.sin_addr) != 1) {
    return -1;
  }

  return connect(uchwytGniazda, (struct sockaddr *)&adresSerwera,
                 sizeof(adresSerwera));
}

int wyslijWiadomosc(int uchwytGniazda, const char *wiadomosc) {
  size_t pozostalo = strlen(wiadomosc);
  const char *pozycja = wiadomosc;

  while (pozostalo > 0) {
    ssize_t wynik = send(uchwytGniazda, pozycja, pozostalo, 0);
    if (wynik <= 0) {
      return -1;
    }
    pozycja += wynik;
    pozostalo -= (size_t)wynik;
  }

  return 0;
}

int odbierzWiadomosc(int uchwytGniazda, char *wiadomosc, size_t rozmiar) {
  ssize_t wynik = recv(uchwytGniazda, wiadomosc, rozmiar - 1, 0);
  if (wynik < 0) {
    return -1;
  }

  wiadomosc[wynik] = '\0';
  return 0;
}

int main(void) {
  int uchwytGniazda = utworzGniazdo();
  if (uchwytGniazda < 0) {
    perror("socket");
    return EXIT_FAILURE;
  }

  if (polaczGniazdo(uchwytGniazda) < 0) {
    perror("connect");
    close(uchwytGniazda);
    return EXIT_FAILURE;
  }

  if (wyslijWiadomosc(uchwytGniazda, "41") < 0) {
    perror("send");
    close(uchwytGniazda);
    return EXIT_FAILURE;
  }

  char wiadomosc[ROZMIAR_BUFORA];
  if (odbierzWiadomosc(uchwytGniazda, wiadomosc, sizeof(wiadomosc)) < 0) {
    perror("recv");
    close(uchwytGniazda);
    return EXIT_FAILURE;
  }

  printf("Odebrana wiadomosc: %s\n", wiadomosc);
  close(uchwytGniazda);
  return EXIT_SUCCESS;
}
