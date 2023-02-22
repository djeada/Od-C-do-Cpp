#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define UZYWANY_PORT 12345

short utworzGniazdo() {
  printf("Tworzenie gniazda\n");
  return socket(AF_INET, SOCK_STREAM, 0);
}

int polaczGniazdo(short uchwytGniazda) {
  int portKlienta = UZYWANY_PORT;

  struct sockaddr_in adresSerwera = {0};
  adresSerwera.sin_family = AF_INET; // Rodzina adresow IP (IPv4)
  adresSerwera.sin_addr.s_addr =
      htonl(INADDR_ANY); // Adres IP serwera (zostawiamy domyslny)
  adresSerwera.sin_port = htons(portKlienta); // Port serwera (przekazujemy
                                              // wartosc zdefiniowana w #define)

  return bind(uchwytGniazda, (struct sockaddr *)&adresSerwera,
              sizeof(adresSerwera));
  ;
}

int main(int argc, char *argv[]) {
  struct sockaddr_in klient;
  char wiadomoscDoWyslania[200] = {0};
  char wiadomoscOdebrana[100] = {0};

  int uchwytGniazda = utworzGniazdo();

  if (uchwytGniazda == -1) {
    printf("Nie udalo sie utworzyc gniazda\n");
    return 1;
  }

  printf("Gniazdo utworzone!\n");

  if (polaczGniazdo(uchwytGniazda) < 0) {
    perror("Nie udalo sie polaczyc gniazda");
    return 1;
  }

  printf("Gniazdo polaczone!\n");

  // Nasluchujemy prob polaczen
  listen(uchwytGniazda, 3);

  printf("Oczekiwanie na klienta...\n");
  int dlugoscKlienta = sizeof(struct sockaddr_in);
  int wynikProbyPolaczenia = accept(uchwytGniazda, (struct sockaddr *)&klient,
                                    (socklen_t *)&dlugoscKlienta);

  if (wynikProbyPolaczenia < 0) {
    perror("Nie udalo sie polaczyc z klientem");
    return 1;
  }

  printf("Proba polaczenia z klientem udana!\n");
  memset(wiadomoscDoWyslania, '\0', sizeof wiadomoscDoWyslania);
  memset(wiadomoscOdebrana, '\0', sizeof wiadomoscOdebrana);

  if (recv(wynikProbyPolaczenia, wiadomoscDoWyslania, 200, 0) < 0) {
    printf("Nie udalo sie odebrac wiadomosci od klienta\n");
  }

  printf("Otrzymano wiadomosc od klienta: %s\n", wiadomoscDoWyslania);

  int i = atoi(wiadomoscDoWyslania);
  i--;
  sprintf(wiadomoscOdebrana, "%d", i);
  close(wynikProbyPolaczenia);

  printf("Oczekiwanie na klienta...\n");
  wynikProbyPolaczenia = accept(uchwytGniazda, (struct sockaddr *)&klient,
                                (socklen_t *)&dlugoscKlienta);

  if (wynikProbyPolaczenia < 0) {
    perror("Polaczenie nie zostalo przyjete");
    return 1;
  }

  printf("Proba polaczenia z klientem udana!\n");

  if (send(wynikProbyPolaczenia, wiadomoscOdebrana, strlen(wiadomoscOdebrana),
           0) < 0) {
    printf("Wysylanie wiadomosci nie powiodlo sie\n");
    return 1;
  }

  return 0;
}
