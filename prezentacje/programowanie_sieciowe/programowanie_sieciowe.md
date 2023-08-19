## Programowanie sieciowe w C

Programowanie sieciowe w C pozwala tworzyć aplikacje komunikujące się z innymi komputerami przez sieć. C, ze względu na swoją wydajność i dostęp do niskopoziomowych funkcji systemowych, jest popularnym wyborem dla programistów sieci.

- **C i programowanie sieciowe**: C jest językiem, który dostarcza narzędzi do niskopoziomowego dostępu do zasobów systemu. Umożliwia to tworzenie wydajnych aplikacji sieciowych.
- **Protokoły sieciowe**: Chociaż TCP jest jednym z najczęściej używanych protokołów do komunikacji sieciowej w C, UDP jest innym ważnym protokołem, który pozwala na szybszą, choć mniej niezawodną, komunikację.
  
## Model klient-serwer w C

Model klient-serwer to podstawowy model komunikacyjny w sieciach komputerowych. Jest on powszechnie używany w programowaniu sieciowym w C.

1. **Inicjacja połączenia**: Klient inicjuje połączenie wysyłając zapytanie do serwera. Musi znać adres IP i port serwera.
2. **Nawiązanie połączenia**: Serwer słucha na określonym porcie i akceptuje lub odrzuca przychodzące zapytania o połączenie.
3. **Komunikacja**: Po nawiązaniu połączenia, klient i serwer mogą wymieniać się danymi.
4. **Zamknięcie połączenia**: Po zakończeniu wymiany danych, połączenie może być zamknięte zarówno przez klienta, jak i serwera.
5. **Wielokrotne połączenia**: Serwer jest zaprojektowany tak, aby obsługiwać wiele jednoczesnych połączeń z różnymi klientami.
6. **Protokoły komunikacji**: Komunikacja między klientem a serwerem może odbywać się poprzez protokoły takie jak TCP lub UDP. Te protokoły umożliwiają komunikację w sieciach LAN (lokalne sieci komputerowe) oraz WAN (szerokopasmowe sieci komputerowe).
7. **Kluczowa koncepcja**: Model klient-serwer jest jednym z kluczowych pojęć w programowaniu sieciowym, umożliwiającym tworzenie rozproszonych aplikacji.

Programowanie sieciowe w C pozwala tworzyć różnorodne aplikacje, od prostych chatów po zaawansowane serwery baz danych. Znajomość modelu klient-serwer oraz protokołów komunikacyjnych jest kluczowa dla efektywnego tworzenia aplikacji sieciowych w C.

## Typy serwerów

Pod względem sposobu obsługi klientów, serwery można podzielić na dwa główne typy: iteracyjne i współbieżne.

### Serwery iteracyjne

* Obsługują jeden klient w danej chwili.
* Po obsłużeniu jednego klienta, serwer przechodzi do obsługi kolejnego.
* Pozostali klienci muszą czekać, aż serwer zakończy obsługę bieżącego klienta.
* Prostota i przewidywalność są głównymi zaletami tego podejścia.
* Idealne dla aplikacji, gdzie jednoczesne połączenia są rzadkie lub gdzie obsługa klienta jest szybka i nieblokująca.
* Jednakże, w środowiskach o wysokim natężeniu ruchu, mogą prowadzić do opóźnień.

### Serwery współbieżne

* Możliwość obsługi wielu klientów jednocześnie.
* Każde nowe połączenie z klientem jest obsługiwane w osobnym procesie lub wątku.
* Dzięki temu, żaden klient nie musi czekać na obsługę innego klienta.
* Skomplikowanie implementacji jest zazwyczaj większe w porównaniu z serwerami iteracyjnymi, ale oferują one znacznie lepszą skalowalność.
* Idealne dla aplikacji, które muszą obsługiwać wiele równoczesnych połączeń, takich jak serwery www czy bazy danych.
* Zastosowanie odpowiednich technik współbieżności może także pomóc w efektywnym wykorzystaniu wielordzeniowych procesorów.

Podczas wyboru między serwerem iteracyjnym a współbieżnym, warto uwzględnić wymagania dotyczące wydajności, złożoność implementacji oraz charakterystykę oczekiwanej komunikacji z klientami.

## Komunikacja między gniazdami

Gniazda to abstrakcyjne punkty końcowe dla wysyłania lub odbierania danych w sieci. Gdy dwa procesy chcą się komunikować przez sieć, tworzą gniazda, które służą jako ich "drzwi" do sieci. 

### Podstawy gniazd

* **Definicja**: Gniazda to interfejsy API umożliwiające komunikację międzyprocesową na różnych maszynach przez sieć.
* **Protokoły**: Komunikacja może odbywać się za pomocą protokołów TCP (połączeniowy) lub UDP (bezpołączeniowy).
* **Tworzenie gniazda**: Aby rozpocząć komunikację sieciową, aplikacja musi najpierw otworzyć gniazdo, określając rodzaj protokołu i typ gniazda.

### Typy gniazd

1. **Gniazda strumieniowe (SOCK_STREAM)**
   * Używają protokołu TCP.
   * Zapewniają niezawodną, dwukierunkową komunikację strumieniową.
   * Dane są wysyłane jako ciągły strumień bajtów, co gwarantuje ich kolejność i niezawodność.
   * Typowo stosowane w aplikacjach wymagających niezawodności, takich jak serwery WWW czy FTP.

2. **Gniazda pakietowe (SOCK_DGRAM)**
   * Używają protokołu UDP.
   * Umożliwiają wysyłanie i odbieranie pojedynczych pakietów danych.
   * Nie gwarantują kolejności ani dostarczenia pakietów.
   * Szybkie i lekkie, idealne dla aplikacji wymagających minimalnego opóźnienia, takich jak gry online czy transmisje wideo na żywo.
  
### Protokoły komunikacyjne:

- **TCP (Transmission Control Protocol)**: Jest to protokół połączeniowy i zapewnia niezawodny strumień danych. W przypadku połączeń TCP, komunikacja zaczyna się od trzyetapowego uścisku dłoni (three-way handshake).
- **UDP (User Datagram Protocol)**: Jest to protokół bezpołączeniowy, co oznacza, że dane są wysyłane jako pojedyncze pakiety bez nawiązywania i zamykania połączenia.

### Adresowanie:

Dla każdego gniazda kluczowe jest adresowanie, które obejmuje adres IP i numer portu. Adres IP identyfikuje maszynę w sieci, podczas gdy port identyfikuje konkretny proces działający na tej maszynie.

### 1. Tworzenie gniazda

Aby nawiązać komunikację, proces musi najpierw utworzyć gniazdo za pomocą funkcji `socket()`. 

```c
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
```

### 2. Nawiązywanie połączenia

Serwer:
  - Związanie gniazda z konkretnym adresem IP i portem przy użyciu funkcji `bind()`.
  - Nasłuchiwanie na połączenia przychodzące za pomocą funkcji `listen()`.
  - Akceptacja połączeń przychodzących za pomocą funkcji `accept()`.
  
Klient:
  - Łączenie się z serwerem za pomocą funkcji `connect()`.

### 3. Komunikacja

Po nawiązaniu połączenia, procesy mogą zacząć się komunikować.

- **Wysyłanie danych**: Procesy używają funkcji `send()` (lub `write()`) do wysyłania danych przez gniazdo.
- **Odbieranie danych**: Procesy używają funkcji `recv()` (lub `read()`) do odbierania danych z gniazda.

### 4. Zamykanie gniazda

Po zakończeniu komunikacji, gniazda są zamykane za pomocą funkcji `close()`. Można także częściowo zamykać gniazdo dla wysyłania lub odbierania danych za pomocą funkcji `shutdown()`.

### Przykład

```c
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    // Tworzenie gniazda TCP
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Nie można utworzyć gniazda");
        return 1;
    }

    // Konfiguracja adresu serwera
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // ...

    close(sockfd);
    return 0;
}
```

## Struktury używane w programowaniu sieciowym w C

W programowaniu sieciowym w języku C, wiele funkcji API korzysta z konkretnych struktur danych do przechowywania informacji na temat gniazd, adresów i innych aspektów komunikacji sieciowej. Poniżej omówiono kilka kluczowych struktur:

### sockaddr_in

To jest główna struktura używana do przechowywania adresów w protokole IPv4.

```c
struct sockaddr_in {
    short            sin_family;   // rodzina adresów, zwykle ustawiana na AF_INET
    unsigned short   sin_port;     // numer portu (w kolejności sieciowej)
    struct in_addr   sin_addr;     // struktura IPv4 adresu
    char             sin_zero[8];  // padding do rozmiaru `sockaddr`
};
```

Składnik in_addr:

```c
struct in_addr {
    unsigned long s_addr;  // adres IPv4 w formie liczby (kolejność sieciowa)
};
```

### sockaddr_in6

Struktura ta jest używana do przechowywania adresów w protokole IPv6.

```c
struct sockaddr_in6 {
    u_int16_t       sin6_family;   // rodzina adresów, AF_INET6
    u_int16_t       sin6_port;     // numer portu
    u_int32_t       sin6_flowinfo; // pole flow info
    struct in6_addr sin6_addr;     // struktura adresu IPv6
    u_int32_t       sin6_scope_id; // pole zakresu
};
```

Składnik in6_addr:

```c
struct in6_addr {
    unsigned char   s6_addr[16];   // adres IPv6
};
```

### sockaddr

Ogólna struktura adresowa. W praktyce jest rzadko używana bezpośrednio, ale jest często wymagana przez funkcje gniazd, które przyjmują zarówno sockaddr_in, jak i sockaddr_in6.

```c
struct sockaddr {
    unsigned short  sa_family;     // rodzina adresów
    char            sa_data[14];   // adres i port
};
```

### addrinfo

Używana przez funkcję getaddrinfo(), która jest używana do tłumaczenia nazw hostów na adresy oraz odwrotnie. Pomaga również w konfiguracji struktur gniazd.

```c
struct addrinfo {
    int             ai_flags;      // flagi AI_PASSIVE, AI_CANONNAME itd.
    int             ai_family;     // AF_INET, AF_INET6, AF_UNSPEC
    int             ai_socktype;   // SOCK_STREAM, SOCK_DGRAM
    int             ai_protocol;   // protokół używany w gnieździe
    size_t          ai_addrlen;    // długość adresu w ai_addr
    char            *ai_canonname; // kanoniczna nazwa hosta
    struct sockaddr *ai_addr;      // wskaźnik na adres
    struct addrinfo *ai_next;      // następny wpis na liście
};
```

## Kluczowe funkcje

W języku C, istnieje wiele funkcji służących do obsługi gniazd, które pozwalają na nawiązywanie, obsługę i zamykanie połączeń sieciowych. Oto bardziej szczegółowy przegląd kluczowych funkcji:

### 1. `socket()`
- **Opis**: Tworzy nowe gniazdo i zwraca jego deskryptor.
- **Argumenty**: 
  - `int domain` (np. AF_INET dla IPv4)
  - `int type` (np. SOCK_STREAM dla TCP, SOCK_DGRAM dla UDP)
  - `int protocol` (często ustawiane na 0, co pozwala systemowi wybrać domyślny protokół dla danego typu gniazda)
- **Zwraca**: Deskryptor gniazda lub -1 w przypadku błędu.

### 2. `bind()`
- **Opis**: Powiązuje gniazdo z określonym adresem IP i portem.
- **Argumenty**: 
  - `int sockfd` (deskryptor gniazda)
  - `const struct sockaddr *addr` (adres, z którym ma być powiązane gniazdo)
  - `socklen_t addrlen` (rozmiar struktury adresu)
- **Zwraca**: 0 w przypadku powodzenia lub -1 w przypadku błędu.

### 3. `listen()`
- **Opis**: Pozwala gniazdu nasłuchiwać na połączenia przychodzące.
- **Argumenty**:
  - `int sockfd` (deskryptor gniazda)
  - `int backlog` (maksymalna liczba połączeń oczekujących w kolejce)
- **Zwraca**: 0 w przypadku powodzenia lub -1 w przypadku błędu.

### 4. `accept()`
- **Opis**: Akceptuje połączenie przychodzące na gniazdo.
- **Argumenty**: 
  - `int sockfd` (deskryptor gniazda)
  - `struct sockaddr *addr` (opcjonalnie może zawierać adres klienta)
  - `socklen_t *addrlen` (rozmiar struktury adresu; wartość jest aktualizowana przy wywołaniu funkcji)
- **Zwraca**: Deskryptor nowego gniazda dla połączenia lub -1 w przypadku błędu.

### 5. `connect()`
- **Opis**: Próbuje nawiązać połączenie z serwerem na określonym adresie IP i porcie.
- **Argumenty**: 
  - `int sockfd` (deskryptor gniazda)
  - `const struct sockaddr *addr` (adres serwera)
  - `socklen_t addrlen` (rozmiar struktury adresu)
- **Zwraca**: 0 w przypadku powodzenia lub -1 w przypadku błędu.

### 6. `send()`
- **Opis**: Wysyła dane przez gniazdo.
- **Argumenty**: 
  - `int sockfd` (deskryptor gniazda)
  - `const void *buf` (wskaźnik na dane do wysłania)
  - `size_t len` (rozmiar danych)
  - `int flags` (opcjonalne flagi; często ustawiane na 0)
- **Zwraca**: Liczbę bajtów wysłanych lub -1 w przypadku błędu.

### 7. `recv()`
- **Opis**: Odbiera dane z gniazda.
- **Argumenty**: 
  - `int sockfd` (deskryptor gniazda)
  - `void *buf` (bufor do odbioru danych)
  - `size_t len` (maksymalny rozmiar bufora)
  - `int flags` (opcjonalne flagi; często ustawiane na 0)
- **Zwraca**: Liczbę bajtów odebranych lub -1 w przypadku błędu.

### 8. `close()`
- **Opis**: Zamyka gniazdo i zwalnia wszystkie związane z nim zasoby.
- **Argument**: 
  - `int sockfd` (deskryptor gniazda)
- **Zwraca**: 0 w przypadku powodzenia lub -1 w przypadku błędu.

## Implementacja klient-serwer z użyciem TCP

![client_server(1)](https://user-images.githubusercontent.com/37275728/220887792-7a43fa1c-67fe-456c-9c3d-3f284d7460e5.png)

