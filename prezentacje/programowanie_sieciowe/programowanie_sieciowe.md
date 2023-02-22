Protokół TCP

Model klient-serwer

-   Klient wysyła zapytanie o połączenie do serwera (musi znać adres IP
    oraz port serwera).

-   Serwer udziela zgodę na połączenie lub odrzuca prośbę.

-   Klient otrzymuje odpowiedź i wysyła dane do serwera.

-   Serwer odbiera dane i ewentualnie wysyła odpowiedź.

-   Połączenie może być zamknięte przez serwer lub klienta.

-   Jednocześnie z jednym serwerem może być połączonych wielu klientów.

-   Komunikacja odbywa się poprzez protokoły TCP bądź UDP, zarówno w
    obrębie LAN jak i WAN.

-   Klient-serwer to centralna koncepcja w teorii sieci komputerowych.

Typy serwerów

Serwery iteracyjne

-   W danej chwili może być obsłużony tylko jeden klient.

-   Program przechodzi przez wszystkich klientów, przetwarzając ich
    zapytania.

-   Klienci, którzy nie są w danej chwili obsługiwani, czekają na swoją
    kolej.

-   Zaletą tego typu serwerów jest prostota implementacji.

Serwery współbieżne

Komunikacja między gniazdami:
