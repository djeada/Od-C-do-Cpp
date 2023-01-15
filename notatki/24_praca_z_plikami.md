## Praca z plikami

W C praca z plikami odbywa sie przy pomocy funkcji, których nazwy zaczynają się od litery 'f', takich jak `fopen()`, `fread()`, `fwrite()` oraz `fclose()`. Struktura `FILE` jest używana jako uchwyt do pliku, za pomocą którego wykonujemy różne operacje na pliku.

```c
#include <stdio.h>

int main(int argc, char **argv) {
  FILE *plik;

  // otwieramy plik do odczytu
  plik = fopen("plik.txt", "r");

  // sprawdzamy, czy plik został pomyślnie otwarty
  if (plik == NULL) {
    printf("Nie udało się otworzyć pliku\n");
    return 1;
  }

  // wczytujemy zawartość pliku po jednym znaku
  char znak;
  while ((znak = fgetc(plik)) != EOF) {
    printf("%c", znak);
  }

  // wykonujemy operacje na pliku, np. zapis
  fputs("test", plik);

  // zamykamy plik
  fclose(plik);

  return 0;
}
```

W C++, do pracy z plikami, możemy korzystać z biblioteki `fstream`, która zawiera bardziej zaawansowane wersje funkcji znanych nam z biblioteki `stdio.h`.

```c++
#include <fstream>
#include <iostream>

int main() {
  std::ifstream plik;

  // otwieramy plik do odczytu
  plik.open("plik.txt", std::ios::in);

  // sprawdzamy, czy plik został pomyślnie otwarty
  if (!plik.is_open()) {
    std::cout << "Nie udało się otworzyć pliku" << std::endl;
    return 1;
  }

  // wczytujemy zawartość pliku po jednym znaku
  char znak;
  while (plik.get(znak)) {
    std::cout << znak;
  }

  // wykonujemy operacje na pliku, np. zapis
  plik << "test";

  // zamykamy plik
  plik.close();

  return 0;
}
```

W obu przykładach, wczytanie zawartości pliku i operacje na nim odbywajają się przy pomocy funkcji o zbliożonym działaniu. W C są to `fgetc()` oraz `fputs()`, natomiast w C++ jest są `get()` i operator `<<`. Warto pamiętać, że przed wykonaniem operacji na pliku, należy upewnić się czy plik został pomyślnie otwarty, oraz po zakończeniu pracy z plikiem należy go zamknąć.

Ważne jest również wybór odpowiedniego trybu otwarcia pliku. W przykładzie użyto trybu `r` dla `fopen()` i `std::ios::in` dla `open()`, co oznacza otwarcie pliku tylko do odczytu. Inne tryby, takie jak `w` lub `a` pozwalają na zapis oraz dopisywanie do pliku.

Ponadto, istnieją również funkcje pozwalające na wczytanie całej linii lub całego pliku jednym wywołaniem, takie jak `fgets()` oraz `fread()` w C oraz `getline()` oraz `read()` w C++.

### Gwarancja bezpiecznego zamknięcia pliku

Warto zwrócić uwagę na fakt, że jeśli w trakcie pracy z plikiem wystąpią błędy, może to prowadzić do sytuacji, w której system operacyjny trzyma otwarty plik dla programu, który już z niego nie korzysta. Aby uniknąć takiej sytuacji, ważne jest pomyślenie o bezpiecznym zamykaniu pliku, które polega na zapewnieniu, że plik zostanie zamknięty niezależnie od tego czy kod wykona się poprawnie czy nie. Można to zrobić za pomocą konstrukcji try-catch lub w C++11 i nowszych wersjach - za pomocą RAII.

RAII (Resource Acquisition Is Initialization) jest techniką polegającą na przypisywaniu zasobów do obiektów, które zarządzają tymi zasobami. W przypadku pliku, możemy utworzyć klasę "File" i przypisać jej metody otwarcia, zamknięcia oraz operacji na pliku. Konstruktor klasy otworzy plik, a destruktor zamknie plik niezależnie od tego czy kod wykona się poprawnie czy nie.

```c++
#include <fstream>

class File {
 public:
  File(const std::string& filename) : m_filename(filename) {
    m_file.open(filename);
  }
  ~File() {
    if (m_file.is_open()) {
      m_file.close();
    }
  }

  std::ifstream& get_file() { return m_file; }

 private:
  std::string m_filename;
  std::ifstream m_file;
};

int main() {
  File file("plik.txt");
  std::ifstream& plik = file.get_file();

  // wczytujemy zawartość pliku
  char znak;
  while (plik.get(znak)) {
    std::cout << znak;
  }

  return 0;
}
```

Dzięki temu, nie trzeba już ręcznie sprawdzać czy plik jest otwarty oraz ręcznie go zamykać, ponieważ jest to zrobione automatycznie.
