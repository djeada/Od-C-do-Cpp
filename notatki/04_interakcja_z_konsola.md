## Interakcja z konsolą

Każdy program w momencie uruchomienia ma dostęp do trzech strumieni:

    1. stdin - strumień wejściowy
    2. stdout - strumień wyjściowy
    3. stderr - strumień błędów

W C używamy funkcji <code>printf</code> oraz <code>scanf</code> odpowiednio do wypisywania danych na ekran i pobierania danych z klawiatury.

```
#include <iostream>

using namespace std;

int main() {
  int liczba;
  cout << "Podaj pojedynczą liczbę: " << endl;
  scanf("%d", &liczba);

  printf("Podales liczbę: %d\n", liczba);	

  return 0;
}
```

| Format | Typ danych |
| ------ | ---------- |
| <code>%d</code> | int |
| <code>%l</code> | long |
| <code>%f</code> | double |
| <code>%c</code> | unsigned char |
| <code>%s</code> | wskaźnik na char |

W C++ biblioteka <code>iostream</code> zawiera definicje funkcji, które pozwalają na komunikację z tymi strumieniami:

- obiekt <code>cout</code> oraz operator <code><<</code> wypisuje tekst na standardowe wyjście;
- obiekt <code>cin</code> oraz operator <code>>></code> wczytują pojedynczą wartość ze standardowego wejścia;
- <code>getline(cin, string)</code> wczytuje ze standardowego wejścia cały wiersz wraz ze spacjami.

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

  getline(cin, zdanie);

  cout << "Podales zdanie: " << endl << zdanie << endl;

  return 0;
}
```
