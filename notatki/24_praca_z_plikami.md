## Praca z plikami

Obsługa plików jest przydatną umiejętnością przy pisaniu aplikacji w C i C++. Praca z plikami pozwala na trwałe przechowywanie danych, które mogą być później odczytywane i przetwarzane przez program. Dzięki temu aplikacje mogą zachowywać stan między uruchomieniami, przechowywać konfiguracje, logi, a także przetwarzać duże ilości danych wejściowych i wyjściowych.

Zarówno C, jak i C++ oferują bogaty zestaw funkcji oraz klas do pracy z plikami, co umożliwia programistom efektywne zarządzanie danymi. W zależności od potrzeb aplikacji, można wybrać odpowiednie narzędzia i metody do otwierania, czytania, zapisywania oraz zamykania plików. Poniżej przedstawione zostaną podstawowe operacje związane z obsługą plików w obu językach, wraz z przykładami kodu i omówieniem najważniejszych funkcji.

### Praca z plikami w C

W języku C obsługa plików odbywa się za pomocą funkcji z biblioteki `<stdio.h>`. Ta biblioteka dostarcza zestaw funkcji, które umożliwiają otwieranie, czytanie, zapisywanie oraz zamykanie plików. Dzięki nim programiści mogą łatwo manipulować danymi zapisanymi na dysku, co jest niezbędne w wielu zastosowaniach, takich jak przetwarzanie danych, logowanie informacji czy tworzenie plików konfiguracyjnych.

Najważniejsze funkcje do tej operacji to `fopen`, `fclose`, `fread`, `fwrite`, `fprintf`, `fscanf`, `fgetc`, i `fputc`. Każda z nich pełni specyficzną rolę w procesie zarządzania plikami, umożliwiając różnorodne operacje na danych. Poniżej omówimy te funkcje szczegółowo, zaczynając od otwierania plików.

#### Otwieranie plików

Aby rozpocząć pracę z plikiem, należy go najpierw otworzyć. W języku C służy do tego funkcja `fopen`, która zwraca wskaźnik do pliku. Wskaźnik ten jest niezbędny do dalszych operacji na pliku, takich jak czytanie czy zapisywanie danych. Proces otwierania pliku wymaga podania nazwy pliku oraz trybu, w jakim ma być otwarty.

```c
#include <stdio.h>

int main() {
    FILE *f = fopen("plik.txt", "r");
    // ... operacje na pliku ...
    fclose(f);
}
```

Argumenty `fopen` to nazwa pliku oraz tryb otwarcia:

- `"r"`: odczyt – otwiera plik do odczytu. Plik musi istnieć.
- `"w"`: zapis – otwiera plik do zapisu. Tworzy nowy plik lub nadpisuje istniejący.
- `"a"`: dopisanie do końca pliku – otwiera plik do dopisywania danych na końcu. Jeśli plik nie istnieje, zostaje utworzony.
- `"rb"`, `"wb"`, `"ab"`: odpowiednie tryby binarne – używane do otwierania plików w trybie binarnym, co jest przydatne przy pracy z plikami nie-tekstowymi.

Wybór odpowiedniego trybu otwarcia pliku jest istotny, ponieważ determinuje sposób, w jaki dane będą odczytywane lub zapisywane. Nieprawidłowy tryb może prowadzić do błędów, takich jak utrata danych czy nieudane próby otwariańia pliku.

#### Czytanie z pliku

Po otwarciu pliku w trybie odczytu, można rozpocząć proces czytania danych z niego. Jednym ze sposobów czytania z pliku jest użycie funkcji `fgetc`, która odczytuje pojedynczy znak z pliku. Poniższy przykład pokazuje, jak można odczytywać plik znak po znaku, a następnie wyświetlać jego zawartość na standardowym wyjściu.

```c
#include <stdio.h>

int main() {
    FILE *f = fopen("plik.txt", "r");
    char c;
    
    while ((c = fgetc(f)) != EOF) {
        putchar(c);
    }

    fclose(f);
}
```

Pętla `while` kontynuuje odczytywanie znaków z pliku aż do napotkania końca pliku (`EOF`). Funkcja `putchar` służy do wyświetlania każdego odczytanego znaku na standardowym wyjściu, co pozwala na przeglądanie zawartości pliku w konsoli.

#### Zapisywanie do pliku

Zapisywanie danych do pliku jest równie ważną operacją. W języku C można to zrobić za pomocą funkcji `fputc`, która zapisuje pojedynczy znak do pliku. Alternatywnie, dla bardziej złożonych operacji, można użyć `fprintf`, która umożliwia formatowane zapisywanie danych, podobnie jak funkcja `printf`.

```c
#include <stdio.h>

int main() {
    FILE *f = fopen("wyjscie.txt", "w");
    
    fputc('H', f);
    fputc('i', f);
    
    fclose(f);
}
```

W powyższym przykładzie otwieramy plik `wyjscie.txt` w trybie zapisu (`"w"`) i zapisujemy do niego dwa znaki: `H` oraz `i`. Po zakończeniu operacji ważne jest, aby zamknąć plik, co gwarantuje zapisanie wszystkich danych i zwolnienie zasobów systemowych.

Lub użyj `fprintf` dla formatowanego wyjścia:

```c
FILE *f = fopen("wyjscie.txt", "w");
fprintf(f, "Witaj, %s!", "świecie");
fclose(f);
```

Funkcja `fprintf` pozwala na zapisanie sformatowanego tekstu do pliku, co jest szczególnie przydatne przy generowaniu bardziej złożonych treści, takich jak raporty czy pliki konfiguracyjne.

#### Sprawdzanie błędów

Przy pracy z plikami zawsze istnieje ryzyko wystąpienia błędów, takich jak brak dostępu do pliku, nieistniejący plik czy problemy z dyskiem. Dlatego zawsze warto sprawdzić, czy otwarie pliku powiodło się przed przystąpieniem do dalszych operacji.

```c
FILE *f = fopen("plik.txt", "r");
if (!f) {
    perror("Błąd podczas otwierania pliku");
    return 1;
}
```

Funkcja `perror` wyświetla komunikat o błędzie związanym z ostatnią operacją systemową, co pomaga w diagnozowaniu problemów podczas pracy z plikami. Dzięki temu program może odpowiednio zareagować na błędy, na przykład poprzez zakończenie działania lub próbę ponownego otwariańia pliku.

W języku C obsługa plików opiera się na wskaźnikach do plików i zestawie funkcji z `<stdio.h>`. Często używaną funkcją jest `fopen`, która zwraca wskaźnik do pliku, a także `fclose`, która zamyka plik. Pamiętaj, aby zawsze zamykać pliki po zakończeniu pracy, co pozwala na prawidłowe zarządzanie zasobami systemowymi i unikanie problemów z dostępem do plików przez inne procesy.

### Praca z plikami w C++

Obsługa plików w C++ odbywa się głównie za pomocą klas `ifstream`, `ofstream` i `fstream` z biblioteki `<fstream>`. Te klasy są częścią standardowej biblioteki C++ i oferują obiektowo-zorientowane podejście do pracy z plikami, co ułatwia zarządzanie zasobami i integrację z resztą kodu.

W przeciwieństwie do C, gdzie operacje na plikach są funkcjami proceduralnymi, C++ pozwala na używanie strumieni, które można łatwo łączyć i manipulować nimi w bardziej intuicyjny sposób. Dzięki temu programiści mogą pisać bardziej czytelny i zorganizowany kod, co jest szczególnie ważne w większych projektach.

#### Otwieranie plików

Aby rozpocząć pracę z plikiem w C++, należy stworzyć obiekt jednej z klas `ifstream` (do czytania), `ofstream` (do pisania) lub `fstream` (do obu operacji). Podczas tworzenia obiektu można od razu podać nazwę pliku oraz tryb otwarcia, co upraszcza proces inicjalizacji.

```cpp
#include <fstream>

int main() {
  std::ifstream plik_wejsciowy("plik.txt");
  std::ofstream plik_wyjsciowy("wyjscie.txt");
}
```

W powyższym przykładzie tworzymy dwa obiekty: `plik_wejsciowy` do odczytu z pliku `plik.txt` oraz `plik_wyjsciowy` do zapisu do pliku `wyjscie.txt`. Dzięki temu możemy łatwo zarządzać różnymi operacjami na plikach w naszym programie.

#### Czytanie z pliku

Do czytania z pliku w C++ często używa się pętli `while` w połączeniu z metodą `getline()`, która odczytuje kolejne linie z pliku. Jest to wygodny sposób na przetwarzanie danych tekstowych linia po linii, co jest często potrzebne w aplikacjach przetwarzających duże pliki tekstowe.

```cpp
#include <iostream>
#include <fstream>
#include <string>

int main() {
  std::ifstream plik("plik.txt");
  std::string linia;
  
  while (std::getline(plik, linia)) {
    std::cout << linia << std::endl;
  }

  plik.close();
}
```

W tym przykładzie otwieramy plik `plik.txt` do odczytu, a następnie w pętli `while` odczytujemy każdą linię i wyświetlamy ją na standardowym wyjściu. Po zakończeniu operacji zamykamy plik, co jest dobrą praktyką zapewniającą prawidłowe zarządzanie zasobami.

#### Zapisywanie do pliku

Zapisywanie danych do pliku w C++ jest równie proste jak odczytywanie. Możemy użyć operatora `<<`, który umożliwia łatwe i intuicyjne zapisywanie danych do strumienia wyjściowego.

```cpp
#include <fstream>

int main() {
  std::ofstream plik("wyjscie.txt");
  
  plik << "Witaj, świecie!" << std::endl;
  
  plik.close();
}
```

W tym przykładzie otwieramy plik `wyjscie.txt` w trybie zapisu i zapisujemy do niego tekst `"Witaj, świecie!"`. Operator `<<` automatycznie konwertuje dane do formatu odpowiedniego dla pliku, co upraszcza proces zapisywania danych.

#### Sprawdzanie błędów

Podobnie jak w języku C, w C++ również warto sprawdzić, czy otwarie pliku powiodło się przed przystąpieniem do dalszych operacji. Pozwala to na odpowiednie reagowanie na ewentualne problemy, takie jak brak dostępu do pliku czy błędy dysku.

```cpp
#include <fstream>
#include <iostream>

int main() {
  std::ifstream plik("plik.txt");
  
  if (!plik) {
    std::cerr << "Błąd podczas otwierania pliku!" << std::endl;
    return 1;
  }
  
  // reszta kodu

  plik.close();
}
```

W tym przykładzie sprawdzamy, czy plik `plik.txt` został poprawnie otwarty. Jeśli nie, wyświetlamy komunikat o błędzie na standardowym wyjściu błędów (`std::cerr`) i kończymy działanie programu z kodem błędu `1`. Dzięki temu unikamy prób operacji na nieotwartym pliku, co mogłoby prowadzić do nieprzewidywalnych zachowań programu.

#### Binary Mode

Domyślnie pliki są otwierane w trybie tekstowym, co oznacza, że dane są interpretowane jako tekst. Jednak w niektórych przypadkach, zwłaszcza przy pracy z plikami binarnymi, konieczne jest otwarie pliku w trybie binarnym. W C++ można to zrobić, dodając flagę `std::ios::binary` jako drugi argument podczas otwierania pliku.

```cpp
std::ofstream binarny_plik("plik.bin", std::ios::binary);
```

Otwieranie pliku w trybie binarnym jest niezbędne, gdy chcemy pracować z danymi nie-tekstowymi, takimi jak obrazy, pliki dźwiękowe czy inne formaty binarne. Tryb binarny zapewnia, że dane są zapisywane i odczytywane dokładnie w takiej formie, w jakiej są przechowywane, bez żadnych modyfikacji czy konwersji.

Obsługa plików w C++ jest prosta i intuicyjna dzięki zastosowaniu klas `ifstream`, `ofstream` i `fstream`. Te klasy umożliwiają odpowiednio czytanie, zapisywanie lub wykonywanie obu tych operacji na plikach. Nie zapominaj też o zamykaniu plików po zakończeniu pracy, co zapewnia prawidłowe zarządzanie zasobami systemowymi i unikanie potencjalnych problemów z dostępem do plików przez inne procesy.

### Gwarancja bezpiecznego zamknięcia pliku

Prawidłowe zarządzanie zasobami, takimi jak pliki, jest ważne dla stabilności i wydajności programu. W językach programowania, które nie mają wbudowanego zarządzania pamięcią, jak C++, błędy w obsłudze zasobów mogą prowadzić do wycieków pamięci, błędów dostępu lub blokowania zasobów. Dlatego ważne jest, aby zawsze dbać o zamknięcie plików po zakończeniu ich używania oraz korzystać z technik programistycznych, które zapewniają bezpieczeństwo i niezawodność w zarządzaniu zasobami.

#### Dlaczego bezpieczne zamykanie pliku jest ważne?

Bezpieczne zamykanie pliku jest istotne z kilku powodów:

- Zamykanie plików zapewnia **integralność danych**, ponieważ gwarantuje, że wszystkie zapisane dane zostaną prawidłowo zapisane na dysku. Nieprawidłowo zamknięty plik może prowadzić do utraty danych lub ich uszkodzenia, co jest szczególnie istotne w przypadku krytycznych informacji.
- Proces ten pozwala na **zwolnienie zasobów systemowych**, takich jak uchwyty plików. Brak zamykania plików może doprowadzić do osiągnięcia limitu otwartych plików, uniemożliwiając otwieranie nowych plików przez programy.
- Zamykanie plików eliminuje **blokady plików**, które mogą ograniczać dostęp dla innych aplikacji. Otwarte pliki często blokują możliwość modyfikacji przez inne programy, co może prowadzić do błędów.
- W niektórych przypadkach zamykanie plików pozwala na **zwalnianie pamięci**, ponieważ otwarte pliki mogą zajmować zasoby pamięciowe. Nieprawidłowe zarządzanie tymi plikami może prowadzić do wycieków pamięci, co w dłuższej perspektywie może skutkować awariami aplikacji.

Ważne jest, aby programiści dbali o prawidłowe zamykanie plików oraz stosowali techniki zapewniające, że pliki zostaną zamknięte nawet w przypadku wystąpienia błędów czy wyjątków.

### RAII w C++

**RAII (Resource Acquisition Is Initialization)** to wzorzec projektowy i zarazem podejście, w którym przejęcie zasobów (np. pamięci, gniazda sieciowego czy uchwytu do pliku) następuje podczas inicjalizacji obiektu, a zwolnienie tych zasobów jest gwarantowane w jego destruktorze. Dzięki temu:

1. **Obiekt jest uznawany za w pełni zainicjalizowany dopiero wtedy, gdy z powodzeniem uda się nabyć wszystkie potrzebne zasoby.** Jeżeli pozyskanie któregokolwiek z nich się nie powiedzie (np. nie uda się otworzyć pliku czy nawiązać połączenia sieciowego), konstruktor może zgłosić błąd poprzez wyjątek, a obiekt nie zostanie w pełni utworzony.  
2. **Zwalnianie zasobów odbywa się automatycznie w destruktorze**, gdy obiekt wychodzi z zasięgu (scope) – na przykład po zakończeniu funkcji lub bloku, w którym został zadeklarowany.  
3. **Nie ma potrzeby wywoływania jawnych operacji zwalniania** (np. zamykania pliku czy zwalniania pamięci), co znacząco minimalizuje ryzyko wycieków zasobów.  

Przykładowymi zasobami, które często są „opakowywane” w obiekty RAII, mogą być:

- **Pamięć** (zazwyczaj zarządzana przy pomocy inteligentnych wskaźników, takich jak `std::unique_ptr` czy `std::shared_ptr` w C++),  
- **Gniazda sieciowe (sockets)** do komunikacji przez sieć,  
- **Uchwyty do plików** (otwarte strumienie wejścia/wyjścia),  
- **Blokady (locki) i muteksy** w środowiskach wielowątkowych,  
- **Dowolne inne zasoby systemowe**, takie jak uchwyty do baz danych czy identyfikatory procesów.

Kluczową zaletą RAII jest to, że **dopóki obiekt istnieje, zasób pozostaje w użytecznym stanie**, a gdy obiekt przestaje istnieć, zasób jest zwalniany. Podejście to ściśle współgra z mechanizmem wyjątków w C++ – jeśli nie uda się pozyskać zasobu, konstruktor zgłasza wyjątek, a wszystkie wcześniej pobrane zasoby są natychmiast zwalniane w ramach stack unwinding (cofania stosu wywołań).

**Przykład z klasą `File`**

Aby zilustrować ideę RAII na prostym przykładzie, można zaprezentować klasę `File`, która odpowiada za otwieranie i zamykanie pliku:

```cpp
#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>

class File {
 public:
  File(const std::string& filename, const std::string& mode = "r") 
    : m_filename(filename) {
      if (mode == "r") {
          m_file.open(filename, std::ios::in);
      } else if (mode == "w") {
          m_file.open(filename, std::ios::out);
      } else if (mode == "a") {
          m_file.open(filename, std::ios::app);
      } else {
          throw std::invalid_argument("Nieznany tryb otwarcia pliku");
      }

      if (!m_file.is_open()) {
          throw std::runtime_error("Nie można otworzyć pliku");
      }
  }

  ~File() {
    if (m_file.is_open()) {
      m_file.close();
    }
  }

  std::fstream& stream() {
    return m_file;
  }

 private:
  std::string m_filename;
  std::fstream m_file;
};

int main() {
  try {
      File file("plik.txt", "r");
      char znak;
      while (file.stream().get(znak)) {
        std::cout << znak;
      }
  } catch (const std::exception& e) {
      std::cerr << "Błąd: " << e.what() << std::endl;
  }

  return 0;
}
```

1. **Konstruktor** próbuje otworzyć plik w zadanym trybie. Jeśli wskazany tryb jest niepoprawny, zgłasza wyjątek `std::invalid_argument`. W przypadku nieudanego otwarcia pliku rzuca `std::runtime_error`.  
2. **Obiekt** będzie uznany za w pełni zainicjalizowany wyłącznie wówczas, gdy uda się skutecznie otworzyć plik. Gdyby pojawił się błąd, konstrukcja obiektu zostanie przerwana, a kod w `main` może przechwycić wyjątek i odpowiednio na niego zareagować.  
3. **Destruktor** sprawdza, czy plik wciąż jest otwarty, i zamyka go, gdy obiekt wyjdzie z zasięgu. Ma to miejsce zarówno przy normalnym zakończeniu funkcji, jak i w przypadku wyjątku. Dzięki temu programista nie musi pamiętać o ręcznym zamykaniu pliku.  
4. Metoda `stream()` zwraca referencję do strumienia `std::fstream`, co umożliwia czytanie i pisanie do pliku za pomocą dostępnych w C++ operacji na strumieniach.

#### RAII a wyjątki

RAII i obsługa wyjątków w C++ stanowią spójny mechanizm. Jeśli konstruktor obiektu nie jest w stanie pozyskać wszystkich zasobów (na przykład plik nie może zostać otwarty, brakuje pamięci lub nie udało się nawiązać połączenia sieciowego), to wyjątek zgłoszony w konstruktorze zapewnia:

- **Automatyczne wycofanie** już zarezerwowanych zasobów (jeśli zdążono je zainicjalizować przed wystąpieniem błędu).  
- **Brak wycieków**: obiekt „nie powstaje” w niekompletnym stanie, więc nie pozostaje w pamięci.  
- **Łatwiejszą kontrolę logiki błędów**: tam, gdzie tworzymy obiekt, możemy uchwycić wyjątek i podjąć decyzję, co zrobić dalej (np. przerwać działanie programu, wyświetlić komunikat, spróbować innej ścieżki, itp.).

#### Krytyka i praktyczne wskazówki

Chociaż RAII jest bardzo pomocne, czasem krytykuje się je za to, że:

1. **Wszystkie scenariusze obsługi błędu mogą trafiać do konstruktorów i destruktorów**, co bywa trudne do rozbudowanej personalizacji. W niektórych przypadkach chcemy np. po nieudanej próbie otwarcia pliku spróbować ponownie po kilku sekundach, w innych – zapisać komunikat do dziennika zdarzeń lub całkowicie zakończyć działanie programu.  
2. **Zbyt duże obciążenie logiką błędów** wewnątrz klasy może prowadzić do zbytniej komplikacji. Zamiast ograniczać się do prostego „otwórz plik → w razie niepowodzenia rzuć wyjątek”, możemy potrzebować bardziej złożonych ścieżek decyzyjnych (np. warunkowe retry, praca w trybie awaryjnym, przełączenie na inny plik itd.).  
3. **W niektórych sytuacjach** konieczna jest bardziej rozproszona obsługa zasobów – np. kiedy żywotność zasobu nie jest ściśle powiązana z żywotnością pojedynczego obiektu (możemy mieć duży system, w którym zasób jest współdzielony między wieloma komponentami). Wtedy konstrukcja typu RAII bywa niewystarczająca lub nadmiernie skomplikowana do utrzymania.

W praktycznych projektach często stosuje się RAII do tych zasobów, które są wyraźnie powiązane z czasem życia obiektu i nie wymagają skomplikowanej logiki w sytuacjach awaryjnych. Jeśli jednak potrzeby aplikacji wykraczają poza standardowy „otwórz-wykorzystaj-zamknij”, należy rozważyć uzupełnienie RAII o inny mechanizm obsługi błędów (np. dedykowane metody zarządzania pewnymi zasobami lub rozbudowany system odroczonego przywracania/zwalniania zasobu).

