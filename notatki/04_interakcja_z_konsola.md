## Interakcja z konsolą
Interakcja z konsolą to mechanizm umożliwiający programowi komunikowanie się z użytkownikiem. Umożliwia wypisywanie danych na ekran i ich pobieranie z klawiatury. 

Każdy program w momencie uruchomienia ma dostęp do trzech strumieni:
- `stdin` - strumień wejściowy,
- `stdout` - strumień wyjściowy,
- `stderr` - strumień błędów.

W C używamy funkcji `printf` oraz `scanf` odpowiednio do wypisywania danych na ekran i pobierania danych z klawiatury.

```c
#include <stdio.h>

int main() {
  int liczba;
  printf("Podaj pojedynczą liczbę: ");
  scanf("%d", &liczba);

  printf("Podales liczbę: %d\n", liczba);	

  return 0;
}
```

| Format | Typ danych |
| ------ | ---------- |
| `%d` | int |
| `%l` | long |
| `%f` | double |
| `%c` | unsigned char |
| `%s` | wskaźnik na char |

W C++ biblioteka `iostream` zawiera definicje funkcji, które pozwalają na komunikację z tymi strumieniami:
- obiekt `cout` oraz operator `<<` wypisuje tekst na standardowe wyjście;
- obiekt `cin` oraz operator `>>` wczytują pojedynczą wartość ze standardowego wejścia;
- `getline(cin, string)` wczytuje ze standardowego wejścia cały wiersz wraz ze spacjami.

```c++
#include <iostream>

using namespace std;

int main() {
  int liczba;
  cout << "Podaj pojedyncza liczbe: " << endl;
  cin >> liczba;

  cout << "Podales liczbe: " << liczba << endl;

  cin.ignore(); // wyczyszczenie bufora

  string zadanie;
  cout << "Podaj pelne zdanie: " << endl;

  getline(cin, zadanie);

  cout << "Podales zdanie: " << endl << zdanie << endl;

  return 0;
}
```
