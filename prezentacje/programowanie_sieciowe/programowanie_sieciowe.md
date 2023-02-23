## Programowanie sieciowe w C

* C jest jednym z popularnych języków programowania służących do programowania sieciowego.
* Protokół TCP jest często wykorzystywany do tworzenia połączeń sieciowych w programowaniu w C.
* Model klient-serwer jest często wykorzystywany w programowaniu sieciowym w C.

## Model klient-serwer

* Klient wysyła zapytanie o połączenie do serwera (musi znać adres IP oraz port serwera).
* Serwer udziela zgodę na połączenie lub odrzuca prośbę.
* Klient otrzymuje odpowiedź i wysyła dane do serwera.
* Serwer odbiera dane i ewentualnie wysyła odpowiedź.
* Połączenie może być zamknięte przez serwer lub klienta.
* Jednocześnie z jednym serwerem może być połączonych wielu klientów.
* Komunikacja odbywa się poprzez protokoły TCP bądź UDP, zarówno w obrębie LAN jak i WAN.
* Klient-serwer to centralna koncepcja w teorii sieci komputerowych.

## Typy serwerów

### Serwery iteracyjne

* W danej chwili może być obsłużony tylko jeden klient.
* Program przechodzi przez wszystkich klientów, przetwarzając ich zapytania.
* Klienci, którzy nie są w danej chwili obsługiwani, czekają na swoją kolej.
* Zaletą tego typu serwerów jest prostota implementacji.

### Serwery współbieżne

* W tym przypadku, serwer jest zdolny do obsługi wielu klientów równocześnie.
* Każdy nowy klient jest obsługiwany przez osobny wątek lub proces.
* Zaletą tego typu serwerów jest możliwość obsługi dużej ilości klientów jednocześnie.

## Komunikacja między gniazdami

* W programowaniu sieciowym w C, komunikacja między gniazdami jest kluczowym zagadnieniem.
* Gniazda umożliwiają komunikację między procesami działającymi na różnych maszynach.
* Komunikacja między gniazdami może odbywać się przy użyciu protokołu TCP lub UDP.
* W celu nawiązania połączenia sieciowego, każdy proces musi utworzyć swoje gniazdo.
* Istnieją dwa typy gniazd: gniazda strumieniowe i gniazda pakietowe.
* Gniazda strumieniowe zapewniają ciągły strumień danych, podczas gdy gniazda pakietowe wysyłają i odbierają pojedyncze pakiety danych.

Oto niektóre ważne funkcje w programowaniu z gniazdami:

* `socket()` - funkcja ta tworzy nowe gniazdo i zwraca jego deskryptor pliku. Jest to jeden z pierwszych kroków w programowaniu z gniazdami. Funkcja ta przyjmuje trzy argumenty: rodzaj gniazda (SOCK_STREAM lub SOCK_DGRAM), protokół (zwykle 0, co oznacza wybór domyślnego protokołu dla danego typu gniazda) oraz rodzaj protokołu (zwykle AF_INET, czyli protokół internetowy IPv4).
* `bind()` - funkcja ta powiązuje gniazdo z konkretnym adresem IP i portem. Umożliwia to klientom połączenie się z serwerem poprzez określenie adresu IP i portu serwera. Funkcja ta przyjmuje trzy argumenty: deskryptor pliku gniazda, strukturę adresu (zwykle struktura sockaddr_in, która zawiera adres IP i numer portu) oraz rozmiar struktury.
* `listen()` - funkcja ta umożliwia gniazdom typu SOCK_STREAM nasłuchiwanie na połączenia przychodzące. Funkcja ta przyjmuje dwa argumenty: deskryptor pliku gniazda i maksymalną liczbę połączeń oczekujących w kolejce.
* `accept()` - funkcja ta akceptuje połączenie przychodzące z gniazda typu SOCK_STREAM. Funkcja ta blokuje program, aż do momentu nadejścia połączenia przychodzącego. Funkcja ta przyjmuje dwa argumenty: deskryptor pliku gniazda i strukturę adresu, która zawiera adres IP i numer portu klienta.
* `connect()` - funkcja ta nawiązuje połączenie z serwerem na danym porcie. Funkcja ta przyjmuje trzy argumenty: deskryptor pliku gniazda, strukturę adresu (zwykle struktura sockaddr_in, która zawiera adres IP i numer portu) oraz rozmiar struktury.
* `send()` - funkcja ta wysyła dane przez gniazdo. Funkcja ta przyjmuje trzy argumenty: deskryptor pliku gniazda, wskaźnik na bufor z danymi do wysłania oraz rozmiar bufora.
* `recv()` - funkcja ta odbiera dane przez gniazdo. Funkcja ta przyjmuje trzy argumenty: deskryptor pliku gniazda, wskaźnik na bufor, w którym zostaną umieszczone dane oraz maksymalny rozmiar bufora.
* `close()` - funkcja ta zamyka deskryptor pliku gniazda. Funkcja ta przyjmuje jeden argument: deskryptor pliku gniazda, który ma zostać zamknięty.

## Implementacja klient-serwer z użyciem TCP

![client_server(1)](https://user-images.githubusercontent.com/37275728/220887792-7a43fa1c-67fe-456c-9c3d-3f284d7460e5.png)
