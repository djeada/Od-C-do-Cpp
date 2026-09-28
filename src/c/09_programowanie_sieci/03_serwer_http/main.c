#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

static int wyslij_wszystko(int fd, const char *bufor, size_t rozmiar) {
  while (rozmiar > 0) {
    ssize_t wyslano = send(fd, bufor, rozmiar, 0);
    if (wyslano <= 0) {
      return -1;
    }
    bufor += wyslano;
    rozmiar -= (size_t)wyslano;
  }
  return 0;
}

int main(void) {
  int serwer = socket(AF_INET, SOCK_STREAM, 0);
  if (serwer < 0) {
    perror("socket");
    return EXIT_FAILURE;
  }

  int reuse = 1;
  if (setsockopt(serwer, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
    perror("setsockopt");
    close(serwer);
    return EXIT_FAILURE;
  }

  struct sockaddr_in adres = {0};
  adres.sin_family = AF_INET;
  adres.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  adres.sin_port = htons(PORT);

  if (bind(serwer, (struct sockaddr *)&adres, sizeof(adres)) < 0) {
    perror("bind");
    close(serwer);
    return EXIT_FAILURE;
  }

  if (listen(serwer, 4) < 0) {
    perror("listen");
    close(serwer);
    return EXIT_FAILURE;
  }

  printf("Serwer HTTP: http://127.0.0.1:%d\n", PORT);

  int klient = accept(serwer, NULL, NULL);
  if (klient < 0) {
    perror("accept");
    close(serwer);
    return EXIT_FAILURE;
  }

  char zadanie[1024];
  ssize_t odebrano = recv(klient, zadanie, sizeof(zadanie) - 1, 0);
  if (odebrano < 0) {
    perror("recv");
    close(klient);
    close(serwer);
    return EXIT_FAILURE;
  }
  zadanie[odebrano] = '\0';
  printf("Pierwsze zadanie HTTP:\n%.*s\n", (int)odebrano, zadanie);

  const char body[] = "Witaj z prostego serwera C!\n";
  char naglowki[256];
  int dlugosc_naglowkow =
      snprintf(naglowki, sizeof(naglowki),
               "HTTP/1.1 200 OK\r\n"
               "Content-Type: text/plain; charset=utf-8\r\n"
               "Content-Length: %zu\r\n"
               "Connection: close\r\n\r\n",
               sizeof(body) - 1);

  if (dlugosc_naglowkow < 0 ||
      (size_t)dlugosc_naglowkow >= sizeof(naglowki) ||
      wyslij_wszystko(klient, naglowki, (size_t)dlugosc_naglowkow) != 0 ||
      wyslij_wszystko(klient, body, sizeof(body) - 1) != 0) {
    perror("send");
    close(klient);
    close(serwer);
    return EXIT_FAILURE;
  }

  close(klient);
  close(serwer);
  return EXIT_SUCCESS;
}
