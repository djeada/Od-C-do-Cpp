#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Utworz gniazdo dla komunikacji z serwerem
// Polacz z serwerem
// Odbierz wiadomosc od serwera
// Wyslij wiadomosc do serwera
// Zamykamy gniazdo

#define UZYWANY_PORT 12345

short utworzGniazdo() {
  printf("Tworzenie gniazda\n");
  return socket(AF_INET, SOCK_STREAM, 0);
}

int polaczGniazdo(short uchwytGniazda) {
  int portSerwera = UZYWANY_PORT;

  struct sockaddr_in adresSerwera = {0};
  adresSerwera.sin_family = AF_INET; // Rodzina adresów IP (IPv4)
  adresSerwera.sin_addr.s_addr =
      htonl(INADDR_ANY); // Adres IP serwera (zostawiamy domyślny)
  adresSerwera.sin_port = htons(portSerwera); // Port serwera (przekazujemy
                                              // wartość zdefiniowaną w #define)

  return bind(uchwytGniazda, (struct sockaddr *)&adresSerwera,
              sizeof(adresSerwera));
  ;
}

int wyslijWiadomosc(short uchwytGniazda, char *wiadomosc) {

  struct timeval tv;
  tv.tv_sec = 20;
  tv.tv_usec = 0;
  if (setsockopt(uchwytGniazda, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
    perror("Zbyt dlugi czas oczekiwania na odpowiedz od serwera");
    return 1;
  }

  int wynik = send(uchwytGniazda, wiadomosc, strlen(wiadomosc), 0);
  if (wynik < 0) {
    perror("Nie udalo sie wyslac wiadomosci");
    return 1;
  }
  return 0;
}

odbierzWiadomosc(short uchwytGniazda, char *wiadomosc) {
  int wynik = recv(uchwytGniazda, wiadomosc, 100, 0);
  if (wynik < 0) {
    perror("Nie udalo sie odebrac wiadomosci");
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  short uchwytGniazda = utworzGniazdo();
  if (uchwytGniazda < 0) {
    perror("Nie udalo sie utworzyc gniazda");
    return 1;
  }

  int wynik = polaczGniazdo(uchwytGniazda);
  if (wynik < 0) {
    perror("Nie udalo sie polaczyc z serwerem");
    return 1;
  }

  char wiadomosc[100];
  wyslijWiadomosc(uchwytGniazda, "Witaj");
  odbierzWiadomosc(uchwytGniazda, wiadomosc);
  printf("Odebrana wiadomosc: %s\n", wiadomosc);

  close(uchwytGniazda);
  return 0;
}
