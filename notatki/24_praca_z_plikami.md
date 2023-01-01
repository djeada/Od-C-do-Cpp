
## Praca z plikami

W C nazwy funkcji używanych do pracy z plikami zaczynają się od litery <i>f</i>, są to np. <code>fopen()</code>, <code>fread()</code> i <code>fclose()</code>. Struktura <code>FILE</code> jest używana jako uchwyt do pliku, za pomocą którego wykonujemy różne operacje na pliku.

```c
#include <stdio.h>

int main(int argc, char **argv) {
  FILE *plik;

  // otwieramy plik
  plik = fopen("plik.txt", "r");

  // sprawdzamy, czy plik został otwarty
  if (plik == NULL) {
    printf("Nie udało się otworzyć pliku");
    return 1;
  }

  // wczytujemy zawartość pliku
  char znak;
  while ((znak = fgetc(plik)) != EOF) {
    printf("%c", znak);
  }

  // wykonujemy operacje na pliku
  fputs("test", plik);

  // zamykamy plik
  fclose(plik);

  return 0;
}
```

W C++ możemy używać funkcji z biblioteki <code>fstream</code>, która jest bardziej zaawansowaną wersją funkcji znanych nam z biblioteki <code>stdio.h</code>.

```c++
#include <fstream>
#include <iostream>

int main() {
  std::ifstream plik;

  // otwieramy plik
  plik.open("plik.txt", std::ios::in);

  // sprawdzamy, czy plik został otwarty
  if (!plik.is_open()) {
    std::cout << "Nie udało się otworzyć pliku" << std::endl;
    return 1;
  }

  // wczytujemy zawartość pliku
  char znak;
  while (plik.get(znak)) {
    std::cout << znak;
  }

  // wykonujemy operacje na pliku
  plik << "test";

  // zamykamy plik
  plik.close();

  return 0;
}
```
