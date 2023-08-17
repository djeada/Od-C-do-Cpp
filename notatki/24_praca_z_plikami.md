## Praca z plikami

Obsługa plików jest kluczową umiejętnością przy pisaniu aplikacji w C i C++. Zarówno C, jak i C++ oferują bogaty zestaw funkcji do pracy z plikami.

### Praca z plikami w C

W języku C obsługa plików odbywa się za pomocą funkcji z biblioteki `<stdio.h>`. Najważniejsze funkcje do tej operacji to `fopen`, `fclose`, `fread`, `fwrite`, `fprintf`, `fscanf`, `fgetc`, i `fputc`.

#### Otwieranie plików

Aby otworzyć plik, używamy funkcji `fopen`, która zwraca wskaźnik do pliku:

```c
#include <stdio.h>

int main() {
    FILE *f = fopen("plik.txt", "r");
    // ... operacje na pliku ...
    fclose(f);
}
```

Argumenty fopen to nazwa pliku oraz tryb otwarcia:

- "r": odczyt
- "w": zapis (tworzy nowy lub nadpisuje istniejący)
- "a": dopisanie do końca pliku
- "rb", "wb", "ab": odpowiednie tryby binarne

#### Czytanie z pliku

Jednym ze sposobów czytania z pliku jest użycie `fgetc`:

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

#### Zapisywanie do pliku

Aby zapisać do pliku, można użyć `fputc`:

```c
#include <stdio.h>

int main() {
    FILE *f = fopen("wyjscie.txt", "w");
    
    fputc('H', f);
    fputc('i', f);
    
    fclose(f);
}
```

Lub użyj `fprintf` dla formatowanego wyjścia:

```c
FILE *f = fopen("wyjscie.txt", "w");
fprintf(f, "Witaj, %s!", "świecie");
fclose(f);
```

#### Sprawdzanie błędów

Zawsze warto sprawdzić, czy otwarcie pliku powiodło się:

```c
FILE *f = fopen("plik.txt", "r");
if (!f) {
    perror("Błąd podczas otwierania pliku");
    return 1;
}
```

W języku C obsługa plików opiera się na wskaźnikach do plików i zestawie funkcji z `<stdio.h>`. Kluczową funkcją jest `fopen`, która zwraca wskaźnik do pliku, a także `fclose`, która zamyka plik. Pamiętaj, aby zawsze zamykać pliki po zakończeniu pracy!

### Praca z plikami w C++

Obsługa plików w C++ odbywa się głównie za pomocą klas `ifstream`, `ofstream` i `fstream` z biblioteki `<fstream>`. Poniżej przedstawiam podstawowe informacje na ten temat.

#### Otwieranie plików

Aby otworzyć plik, należy stworzyć obiekt jednego z typów `ifstream` (do czytania), `ofstream` (do pisania) lub `fstream` (do obu operacji). Podczas tworzenia obiektu, można od razu podać nazwę pliku.

```c++
#include <fstream>

int main() {
  std::ifstream plik_wejsciowy("plik.txt");
  std::ofstream plik_wyjsciowy("wyjscie.txt");
}
```

#### Czytanie z pliku

Do czytania z pliku często używa się pętli `while` w połączeniu z metod `getline()`:

```c++
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

#### Zapisywanie do pliku

Zapisywanie do pliku jest równie proste:

```c++
#include <fstream>

int main() {
  std::ofstream plik("wyjscie.txt");
  
  plik << "Witaj, świecie!" << std::endl;
  
  plik.close();
}
```

#### Sprawdzanie błędów

Przed przystąpieniem do operacji na pliku warto sprawdzić, czy otwarcie pliku powiodło się:

```c++
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

#### Binary Mode

Domyślnie pliki są otwierane w trybie tekstowym. Aby otworzyć plik w trybie binarnym, dodaj std::ios::binary jako drugi argument podczas otwierania:

```c++
std::ofstream binarny_plik("plik.bin", std::ios::binary);
```

Obsługa plików w C++ jest prosta i intuicyjna. Kluczowe klasy to `ifstream`, `ofstream` i `fstream`, które umożliwiają odpowiednio czytanie, zapisywanie lub obie te operacje. Nie zapominaj też o zamykaniu plików po zakończeniu pracy!

### Gwarancja bezpiecznego zamknięcia pliku

Prawidłowe zarządzanie zasobami, takimi jak pliki, jest kluczowe dla stabilności i wydajności programu. W językach programowania, które nie mają wbudowanego zarządzania pamięcią, jak C++, błędy w obsłudze zasobów mogą prowadzić do wycieków pamięci, błędów dostępu lub blokowania zasobów.

#### Dlaczego bezpieczne zamykanie pliku jest ważne?

Jeśli plik nie zostanie zamknięty prawidłowo, może prowadzić to do różnych problemów:

1. **Strata danych**: Niezamknięty plik może nie zapisać wszystkich danych.
2. **Blokada zasobów**: Inne programy mogą nie mieć dostępu do pliku, jeśli jest nadal otwarty przez inny program.
3. **Wycieki pamięci**: System operacyjny może rezerwować zasoby dla otwartych plików.

#### RAII w C++

RAII to koncepcja przypisania życia zasobu do czasu życia obiektu. Poniżej przedstawiam bardziej rozbudowaną klasę `File`:

```c++
#include <fstream>
#include <stdexcept>

class File {
 public:
  File(const std::string& filename, const std::string& mode = "r") 
    : m_filename(filename) {
      if (mode == "r") m_file.open(filename, std::ios::in);
      else if (mode == "w") m_file.open(filename, std::ios::out);
      else if (mode == "a") m_file.open(filename, std::ios::app);
      else {
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

  std::fstream& stream() { return m_file; }

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

W powyższym kodzie klasa File otwiera plik w konstruktorze i zamyka go w destruktorze. Jeśli wystąpią błędy, będą one zgłaszane jako wyjątki. Dzięki temu użytkownik klasy File nie musi martwić się o manualne zamykanie pliku.
