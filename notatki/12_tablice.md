## Tablice

Tablice to struktura danych przechowująca elementy tego samego typu, które mogą być dostępne przez indeks. W języku C++ tworzenie tablicy odbywa się przez umieszczenie liczby reprezentującej ilość elementów tablicy między nawiasy kwadratowe, po nazwie zmiennej.

```c++
int tab[3]; // Polka z 3 pudelkami typu int.
```

W powyższym przykładzie zostaje zarezerwowane miejsce w pamięci, jednak elementy tablicy nie są jeszcze zainicjalizowane. Oznacza to, że w środku znajdują się jakieś nieznane dane ("śmieci"). Aby uniknąć tego problemu, możemy zainicjalizować tablicę od razu po jej deklaracji, poprzez przypisanie jej wartości.

```c++
int tabA[3] = {7, 8, 11};
```

lub

```c++
int tabB[] = {7, 8, 11};
```

Obie wersje są dopuszczalne.

### Wczytywanie i wypisywanie elementów tablicy

Wczytywanie i wypisywanie elementów tablicy odbywa się przy użyciu pętli for i operatorów wejścia/wyjścia.

```c++
#include <iostream>

const int n = 10;

int main() {

  int a[n];

  std::cout << "Podaj " << n << " elementów: " << std::endl;

  // wczytywanie
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  std::cout << "Twoja tablica: " << std::endl;

  // wypisywanie
  for (int i = 0; i < n; i++)
    std::cout << a[i] << std::endl;

  return 0;
}
```

Należy pamiętać, że dostęp do elementów tablicy poza jej zakresem (próba odwołania się do indeksu mniejszego od 0 lub większego od długości tablicy) może skutkować niezdefiniownym zachowaniem programu. W niektórych przypadkach możemy otrzymać przypadkowe wartości, które akurat znajdują się w komórkach pamięci obok naszej tablicy, natomiast w innych przypadkach program może po prostu zakończyć działanie (crash).

### Tablica jako wskaźnik

Tablice również mogą być traktowane jako wskaźniki. Nazwa tablicy jest wskaźnikiem do pierwszego elementu tablicy. Oznacza to, że `tab[0]` oraz `*tab` są synonimami. Poniższy przykład przedstawia funkcję, która oblicza sumę elementów tablicy przyjmując jako argument wskaźnik do pierwszego elementu oraz długość tablicy.

```c++
#include <iostream>

int suma(int *tablica, int dlugosc) {
  int suma = 0;

  for (int i = 0; i < dlugosc; i++)
    suma += tablica[i];

  return suma;
}

int main() {

  int tab[] = {2, 4, 8, 16, 32};
  std::cout << suma(tab, 5) << std::endl;

  return 0;
}
```

Zwróć uwagę, że w powyższym przykładzie przekazujemy do funkcji długość tablicy. Kompilator nie wie, czy `int* tablica` wskazuje na pojedynczą liczbę, czy na tablicę 10 liczb. Nie pomoże nawet operator <code>sizeof</code>, zwracający rozmiar danego obiektu lub typu podany w bajtach. Dla wskaźnika zwróci jedynie rozmiar typu, na który wskazuje wskaźnik.

### Arytmetyka wskaźników

Arytmetyka wskaźników polega na operowaniu na wartościach wskaźników za pomocą operatorów arytmetycznych. W języku C++ dostępne są następujące operatory arytmetyczne dla wskaźników:

* `++` (inkrementacja) - zwiększa wartość wskaźnika o jeden, co oznacza, że przesuwa wskaźnik na kolejny element tablicy. Przykład: `int* wsk = &tab[0]; wsk++;` oznacza, że wsk teraz wskazuje na `tab[1]`.
* -- (dekrementacja) - zmniejsza wartość wskaźnika o jeden, co oznacza, że przesuwa wskaźnik na poprzedni element tablicy. Przykład: `int* wsk = &tab[1]; wsk--;` oznacza, że wsk teraz wskazuje na `tab[0]`.
* `+=` (dodawanie) - dodaje wartość do wskaźnika, co oznacza, że przesuwa wskaźnik o określoną liczbę elementów. Przykład: `int* wsk = &tab[0]; wsk += 2;` oznacza, że wsk teraz wskazuje na `tab[2]`.
* `-=` (odejmowanie) - odejmuje wartość od wskaźnika, co oznacza, że przesuwa wskaźnik o określoną liczbę elementów wstecz. Przykład: `int* wsk = &tab[2]; wsk -= 1;` oznacza, że wsk teraz wskazuje na `tab[1]`.
* `+` (dodawanie) - zwraca wskaźnik do elementu tablicy o określonej liczbie pozycji dalej. Przykład: `int* wsk = &tab[0]; int* wsk_plus = wsk + 2;` oznacza, że wsk_plus teraz wskazuje na `tab[2]`.
* `-` (odejmowanie) - zwraca różnicę pomiędzy dwoma wskaźnikami, która jest liczbą elementów pomiędzy nimi. Przykład: `int* wsk1 = &tab[0]; int* wsk2 = &tab[2]; int roznica = wsk2 - wsk1;` oznacza, że roznica jest równa 2, co oznacza, że między wskaźnikami wsk1 i wsk2 znajdują się 2 elementy tablicy.

Arytmetyka wskaźników jest przydatna, ponieważ pozwala na łatwe przesuwanie się po tablicy i dostęp do poszczególnych elementów bez konieczności znajomości ich indeksów. Pamiętać jednak należy, że operowanie poza zakresem tablicy (np. próba dekrementacji wskaźnika wskazującego na pierwszy element) może prowadzić do niezdefiniowanego zachowania programu.

### Dynamiczna alokacja pamięci

Aby skorzystać z pamięci sterty, używamy operatora `new` do alokacji (rezerwacji) miejsc w pamięci komputera dla pojedynczej zmiennej lub tablicy. Użycie samego `new` zarezerwuje pamięć dla pojedynczej zmiennej, natomiast dla tablicy używamy `new [liczba]`, gdzie liczba to długość tablicy, jaką chcemy stworzyć.

```c++
#include <iostream>

int main() {

  std::cout << "Podaj liczbę elemntów tablicy: " << std::endl;

  int n;
  std::cin >> n;

  int *tab = new int[n];
  //...
```

Gdy tablica nie jest już potrzebna, zarezerwowaną uprzednio pamięć uwalniamy przy pomocy operatora `delete`. Dla pojedynczej zmiennej używamy `delete`, natomiast dla tablicy `delete[]`. Tym razem nie wstawiamy już żadnych liczb w nawiasy kwadratowe.

```c++
  //...
  delete[] tab;
  return 0;
}
```

Ważne jest, aby pamięć zawsze była uwalniana po skończeniu pracy z nią. Zmienne na stercie mogą żyć dłużej niż wskazujące na nie wskaźniki. Jeśli nie uwolnimy dynamicznie zaalokowanej pamięci, system operacyjny będzie dalej ją trzymał i bronił przed nadpisaniem. Jeśli wskaźnik został usunięty, to z jednej strony nie mamy w programie możliwości dostania się do zmiennych, które stworzyliśmy na stercie, a z drugiej marnujemy zasoby komputera, bo system operacyjny nie dopuszcza innych programów do tego obszaru pamięci. Taką sytuację nazywamy "wyciekiem pamięci". Dla kilku zmiennych jest to nieodczuwalne, ale dla większych programów może szybko przeciążyć naszą maszynę.

Dodatkowo warto pamiętać, że korzystanie z dynamicznej alokacji pamięci wiąże się z dodatkowymi kosztami w postaci pamięci, którą trzeba zarezerwować oraz czasu, który trzeba poświęcić na alokację i dealokację pamięci. Dlatego ważne jest, aby dokładnie przemyśleć, czy dynamiczna alokacja jest konieczna dla danego problemu i czy nie lepiej skorzystać z innego rozwiązania.

### Tablica 2D

Tablica dwuwymiarowa (ang. two-dimensional array) jest to tablica, która składa się z innych tablic. Każda z tych tablic jest rzędem (ang. row) tablicy dwuwymiarowej. Ilustruje to poniższy przykład:

```c++
int a[3][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };
```

w którym tablica a składa się z trzech rzędów, a każdy rząd składa się z 4 elementów.

Poniższy przykład, pokazuje jak stworzyć tablicę dwuwymiarową:

```c++
#include <iostream>

const unsigned int n = 3;
const unsigned int m = 4;

int main() {

  int a[n][m];

  std::cout << "Podaj " << n * m << " elementów: " << std::endl;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      std::cin >> a[i][j];

  std::cout << "Twoja tablica: " << std::endl;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      std::cout << a[i][j] << " ";
    std::cout << std::endl;
  }

  return 0;
}
```

W powyższym przykładzie tworzymy tablicę dwuwymiarową o wymiarach $n \times m$ (w tym przypadku `3x4`) i pozwalamy na wprowadzenie elementów przez użytkownika. Na koniec tablica jest wypisywana na konsoli.

Tablica dwuwymiarowa może być również stworzona dynamicznie. Poniższy przykład pokazuje jak użyć operatora `new` do zbudowania dwuwymiarowej tablicy:

```c++
#include <iostream>

int main() {

  double **macierz;
  int wysokość, szerokość;

  std::cin >> wysokość >> szerokość;

  // Alokacja
  macierz = new double*[wysokość];

  for (int i = 0; i < wysokość; i++)
    macierz[i] = new double[szerokość];

  // Dealokacja
  for (int i = 0; i < wysokość; i++)
    delete[] macierz[i];

  delete[] macierz;

  return 0;
}
```

W powyższym kodzie, zmienne `wysokość` i `szerokość` służą do określenia liczby rzędów i kolumn tworzonej tablicy dwuwymiarowej. Następnie, za pomocą operatora `new`, alokujemy pamięć dla tablicy i przypisujemy ją do zmiennej `macierz`. Warto zwrócić uwagę na fakt, że alokacja pamięci dla tablicy dwuwymiarowej wykonywana jest za pomocą dwóch pętli.
