# Praca z plikami w C i C++

Plik przechowuje dane poza pamięcią programu, więc można z nich skorzystać także po jego ponownym uruchomieniu. Niezależnie od języka, praca z plikiem składa się z czterech kroków: wybierz tryb, otwórz plik, czytaj lub zapisuj, zamknij. Każdy krok może się nie powieść, dlatego sprawdzamy jego wynik.

Ścieżka `dane.txt` jest liczona od bieżącego katalogu roboczego programu, a niekoniecznie od katalogu, w którym leży kod źródłowy.

## Najpierw wybierz tryb

Tryb określa, czy plik musi istnieć, czy dotychczasowa zawartość zostanie usunięta i gdzie będą trafiały zapisy. Wybór `w` lub domyślnego zapisu przez `ofstream` może skasować wcześniejszą zawartość pliku.

| Zamiar | Tryb C dla `fopen` | Typowy zapis w C++ |
|---|---|---|
| Odczyt istniejącego pliku | `"r"` | `std::ifstream p("dane.txt");` |
| Zapis od początku; utworzenie lub wyczyszczenie | `"w"` | `std::ofstream p("dane.txt");` |
| Dopisywanie na końcu; utworzenie, jeśli brak | `"a"` | `std::ofstream p("dane.txt", std::ios::out \| std::ios::app);` |
| Odczyt i zapis istniejącego pliku | `"r+"` | `std::fstream` z `in | out` |
| Odczyt i zapis pliku wyczyszczonego | `"w+"` | `std::fstream` z `in | out | trunc` |
| Odczyt i dopisywanie | `"a+"` | `std::fstream` z `in | out | app` |

W tabeli `in`, `out`, `trunc` i `app` oznaczają odpowiednio `std::ios::in`, `std::ios::out`, `std::ios::trunc` i `std::ios::app`. Flagi C++ łączy się operatorem `|`. W C do trybu można dodać `b`, np. `"rb"`; w C++ służy do tego `std::ios::binary`.

Tryb binarny przekazuje bajty bez tekstowej interpretacji końców wierszy, ale sam nie określa przenośnego formatu liczb czy struktur. W trybie `app` każdy zapis trafia na koniec. Jeśli chcesz zachować wcześniejszy tekst, a potem dodać nowy, to właśnie `app` jest właściwym wyborem.

## Pliki w C

Funkcje C są zadeklarowane w `<stdio.h>`. `fopen` zwraca wskaźnik `FILE*` albo `NULL`, gdy otwarcie się nie powiedzie. Nie wykonuj operacji na pliku przed sprawdzeniem wyniku:

~~~c
#include <stdio.h>

int main(void) {
    FILE *plik = fopen("wejscie.txt", "r");
    if (plik == NULL) {
        perror("Nie można otworzyć wejscie.txt");
        return 1;
    }

    /* Miejsce na odczyt z pliku. */

    if (fclose(plik) != 0) {
        perror("Nie udało się zamknąć pliku");
        return 1;
    }
}
~~~

Tryb `"r"` wymaga istniejącego pliku; `"w"` utworzyłby plik, ale skasowałby jego wcześniejszą zawartość. `perror` wypisuje własny opis i komunikat systemowy o przyczynie błędu. `fclose` wywołujemy tylko dla poprawnie otwartego pliku.

### Odczyt i koniec pliku

Chcemy wypisać zawartość pliku znak po znaku. `fgetc` zwraca typ `int`, bo musi reprezentować zarówno dowolny znak, jak i odrębny znacznik `EOF`. Po pętli `EOF` może oznaczać zwykły koniec pliku albo błąd odczytu; `ferror` rozstrzyga, czy wystąpił błąd.

~~~c
#include <stdio.h>

int main(void) {
    FILE *plik = fopen("wejscie.txt", "r");
    if (plik == NULL) {
        perror("Nie można otworzyć wejscie.txt");
        return 1;
    }

    int znak;
    while ((znak = fgetc(plik)) != EOF) {
        putchar(znak);
    }

    if (ferror(plik)) {
        fprintf(stderr, "Błąd odczytu pliku\n");
        fclose(plik);
        return 1;
    }
    if (fclose(plik) != 0) {
        perror("Nie udało się zamknąć pliku");
        return 1;
    }
}
~~~

Dla pliku zawierającego tekst `Ala` i znak końca wiersza program wypisze te znaki, a przy normalnym końcu pętli `ferror(plik)` pozostanie fałszywe. Częsta pomyłka to przypisać wynik `fgetc` do `char`. Znak o pewnej wartości mógłby wtedy zostać pomylony z `EOF`.

### Zapis i sprawdzanie

`fputc` zapisuje jeden znak, a `fprintf` tekst z formatowaniem. Sprawdź wynik zapisu i zamknięcia, ponieważ błąd może ujawnić się dopiero, gdy `fclose` opróżnia bufor:

~~~c
#include <stdio.h>

int main(void) {
    FILE *plik = fopen("raport.txt", "w");
    if (plik == NULL) {
        perror("Nie można otworzyć raport.txt");
        return 1;
    }

    int status = 0;
    if (fprintf(plik, "Wynik: %d\n", 42) < 0) {
        fprintf(stderr, "Błąd zapisu do raport.txt\n");
        status = 1;
    }
    if (fclose(plik) != 0) {
        perror("Nie udało się zapisać lub zamknąć raport.txt");
        status = 1;
    }
    return status;
}
~~~

Po udanym zapisie plik zawiera wiersz `Wynik: 42`. W C programista sam odpowiada za `fclose`. Przy wielu możliwych wyjściach z funkcji zaplanuj sprzątanie tak, by plik nie został otwarty po błędzie.

Inne funkcje: `fgets` czyta wiersz do bufora o ograniczonym rozmiarze; `fscanf` czyta wartości według formatu; `fread` i `fwrite` czytają lub zapisują określoną liczbę elementów. Sprawdzaj liczbę elementów faktycznie przeczytanych lub zapisanych oraz wynik `fscanf`.

## Pliki w C++

Nagłówek `<fstream>` udostępnia `std::ifstream` do odczytu, `std::ofstream` do zapisu i `std::fstream` do obu tych operacji. Strumień jest obiektem pamiętającym stan operacji; warunek `if (!plik)` pozwala wykryć nieudane otwarcie albo późniejszy błąd.

### Odczyt wierszami

`std::getline(plik, linia)` pobiera znaki do końca wiersza, usuwa znak nowej linii ze strumienia i zapisuje pozostały tekst do `linia`:

~~~cpp
#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream plik("wejscie.txt");
    if (!plik) {
        std::cerr << "Nie można otworzyć wejscie.txt\n";
        return 1;
    }

    std::string linia;
    while (std::getline(plik, linia)) {
        std::cout << linia << '\n';
    }

    if (plik.bad()) {
        std::cerr << "Błąd wejścia/wyjścia podczas odczytu\n";
        return 1;
    }
}
~~~

Jeśli plik zawiera wiersze `Ala` oraz `ma kota`, pętla wykona się dwa razy i wypisze:

~~~text
Ala
ma kota
~~~

Przy zwykłym końcu pliku `getline` zwraca fałsz, co kończy pętlę. To normalny koniec odczytu, a nie awaria; `bad()` służy do wykrywania poważnego błędu I/O.

### Stan strumienia

| Metoda | Znaczenie |
|---|---|
| `good()` | Nie ustawiono flag błędu. |
| `eof()` | Odczyt dotarł do końca pliku. Sam koniec może być normalny. |
| `fail()` | Operacja nie dostarczyła oczekiwanych danych, np. tekstu nie dało się zamienić na liczbę. Może być ustawione przy końcu pliku. |
| `bad()` | Poważny błąd wejścia/wyjścia. |

Warunek `if (plik)` jest prawdziwy, gdy nie ustawiono `failbit` ani `badbit`. Nie pisz `while (!plik.eof())`. Flaga końca zwykle pojawia się dopiero po próbie odczytu za końcem pliku; taka pętla może więc ponownie użyć poprzedniej wartości. Umieść odczyt w warunku pętli:

~~~cpp
int liczba;
while (plik >> liczba) {
    // Liczba została poprawnie odczytana.
}
if (plik.bad()) {
    // Poważny błąd I/O.
} else if (!plik.eof()) {
    // Niepoprawny tekst, np. „abc” zamiast liczby.
}
~~~

Dla danych `10 20 30` pętla odczyta trzy liczby, a następna próba trafi na koniec pliku. Dla tekstu `10 abc 30` odczyt zatrzyma się przy `abc`: `fail()` będzie prawdziwe, ale koniec pliku jeszcze nie został osiągnięty.

### Zapis i kontrola błędów

`operator<<` zapisuje tekst i wartości do strumienia. Sprawdzamy stan po zapisie; jawne zamknięcie pozwala też wykryć błąd opróżniania bufora:

~~~cpp
#include <fstream>
#include <iostream>

int main() {
    std::ofstream plik("raport.txt"); // Tworzy albo czyści plik.
    if (!plik) {
        std::cerr << "Nie można otworzyć raport.txt\n";
        return 1;
    }

    plik << "Wynik: " << 42 << '\n';
    if (!plik) {
        std::cerr << "Błąd zapisu do raport.txt\n";
        return 1;
    }

    plik.close();
    if (!plik) {
        std::cerr << "Błąd podczas zamykania pliku\n";
        return 1;
    }
}
~~~

Po poprawnym zapisie w pliku znajdzie się `Wynik: 42`. Zwykle nie musisz pisać `close()`: strumień zamknie plik automatycznie przy wyjściu obiektu z zakresu. W przykładzie robimy to jawnie, aby sprawdzić końcowy stan.

### Dopisywanie i tryb binarny

Jeśli plik `log.txt` zawiera już `Start`, tryb `std::ios::app` dopisze nowy tekst na końcu zamiast skasować wcześniejszy:

~~~cpp
#include <fstream>

int main() {
    std::ofstream plik("log.txt", std::ios::out | std::ios::app);
    if (!plik) return 1;
    plik << "Nowe zdarzenie\n";
}
~~~

Po zapisie plik zawiera oba wiersze: `Start` i `Nowe zdarzenie`. Flaga `std::ios::binary` wybiera pracę z bajtami i można ją łączyć z `std::ios::in` lub `std::ios::out`. Sama flaga nie czyni formatu przenośnym: reprezentacja liczby zależy m.in. od architektury.

Do odczytu i zapisu służy `std::fstream`. Flagi `in` i `out` wybierają kierunek, `app` wymusza dopisywanie na końcu, `trunc` czyści plik przy otwarciu. Przy przeplataniu odczytu i zapisu na jednym strumieniu trzeba poprawnie przechodzić między tymi operacjami; w prostych programach łatwiej użyć osobnych plików wejściowego i wyjściowego.

## C i C++: to samo zadanie, inny sposób zarządzania

| Zadanie | C | C++ |
|---|---|---|
| Otwarcie | `fopen` zwraca `FILE*` albo `NULL`. | Tworzymy `ifstream`, `ofstream` lub `fstream` i sprawdzamy `if (!plik)`. |
| Odczyt wiersza | `fgets` zapisuje do bufora o ustalonym rozmiarze. | `std::getline` zapisuje do `std::string`. |
| Zapis tekstu | `fprintf` lub `fputs`; sprawdź wynik. | `operator<<`; sprawdź stan strumienia. |
| Zamknięcie | Jawne `fclose`; sprawdź wynik. | Destruktor strumienia zamyka plik automatycznie; `close()` umożliwia sprawdzenie końcowego błędu. |
| Błędy | Kody zwrotu funkcji, `ferror`, `perror`. | Flagi stanu strumienia; wyjątki są opcjonalne. |

W C programista musi dopilnować `fclose` na każdej ścieżce wyjścia. W C++ strumień stosuje RAII: zamyka plik, kiedy obiekt wychodzi z zakresu, także przy wcześniejszym wyjściu z funkcji lub rozwijaniu stosu po wyjątku. RAII zwalnia zasób, ale nie wykrywa za programistę błędów odczytu i zapisu. Te nadal trzeba sprawdzać.
