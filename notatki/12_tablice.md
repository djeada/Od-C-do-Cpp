## Tablice

Jeśli zmienna to pudełko, to tablica to półka z pudełkami. Wszystkie pudełka na jednej półce przechowują dane tego samego typu. Do tworzenia tablic używamy nawiasów kwadratowych. Między nawiasy kwadratowe trafia liczba reprezentująca ilość elementów tablicy.

```c++
int tab[3]; // Półka z 3 pudełkami typu int.
```

W powyższym przykładzie miejsce w pamięci zostało zarezerwowane, ale pudełka są niezainicjalizowane. Co siedzi w środku? Śmieci.

Przykłady tablicy zadeklarowanej i zainicjalizowanej:

```c++
int tabA[3] = {7, 8, 11};
```

```c++
int tabB[] = {7, 8, 11};
```

Obie wersje są dopuszczalne.

### Wczytywanie i wypisywanie elementów tablicy

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

Jeśli spróbujesz odnieść się do tablicy przy użyciu nieprawidłowego indeksu (mniejszego od 0 bądź większego lub równego długości tablicy) to zachowanie programu jest niezdefiniowane. Jeśli system operacyjny jest miły to w ten sposób możesz otrzymać przypadkowe liczby, które akurat siedzą w komórkach pamięci na lewo bądź prawo od twojej tablicy. W przeciwnym razie twój program po prostu przestanie działać (crash).
### Tablica jako wskaźnik

Za pomocą wskaźników można również odwoływać się do elementów tablicy. Nazwa tablicy to wskaźnik do pierwszego elementu tablicy. Jeśli <code>tab</code> to nazwa tablicy, to <code>tab[0]</code> oraz <code>\*tab</code> są synonimami.

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

Zwróć uwagę, że w powyższym przykładzie przekazujemy do funkcji długość tablicy. Kompilator nie wie, czy <code>int\* tablica</code> wskazuje na pojedynczą liczbę, czy na tablicę 10 liczb. Nie pomoże nawet operator <code>sizeof</code>, zwracający rozmiar danego obiektu lub typu podany w bajtach. Dla wskaźnika zwróci jedynie rozmiar typu, na który wskazuje wskaźnik.

### Arytmetyka wskaźników

Jeśli nazwa tablicy to wskaźnik do pierwszego elementu tablicy i elementy tablicy umiejscowione są jeden obok drugiego w pamięci komputera, to fajnie byłoby mieć możliwość przesuwania się między kolejnymi elementami tablicy za pomocą wskaźników. Taki mechanizm istnieje i zwie się arytmetyką wskaźników. Arytmetyka, dlatego że do wskaźników możemy dodawać i odejmować liczby całkowite. Jeśli wskaźnik <code>wsk</code> wskazuje nam pierwszy element tablicy <code>tab</code>, to <code>wsk+3</code> będzie wskazywał na czwarty element tablicy. Przy tej operacji należy być jednak bardzo ostrożnym, gdyż łatwo jest wyjść poza granice tablicy i spróbować odczytać zabroniony obszar pamięci.

```c++
#include <iostream>

int main() {
  int tab[] = {1, 2, 3, 4, 5};
  int *wsk = tab;

  std::cout << *wsk << std::endl;
  std::cout << *(wsk + 3) << std::endl;

  return 0;
}
```

### Dynamiczna alokacja pamięci

Aby skorzystać z pamięci sterty, używamy operatora <code>new</code> do alokacji (rezerwacji) miejsc w pamięci komputera dla elementów tablicy. Użycie samego <code>new</code> zarezerwuje pamięć dla pojedynczej zmiennej. Dla tablicy używam <code>new [liczba]</code>, gdzie <code>liczba</code> to długość tablicy, jaką chcemy stworzyć.
Gdy tablica nie jest nam już potrzebna, zarezerwowaną uprzednio pamięć uwalniamy przy pomocy <code>delete</code>. Podobnie jak z operatorem <code>new</code>, dla tablicy używamy <code>delete []</code>. Tym razem nie wstawiamy już żadnych liczb w nawiasy kwadratowe.

```c++
#include <iostream>

int main() {

  std::cout << "Podaj liczbę elemntów tablicy: " << std::endl;

  int n;
  std::cin >> n;

  int *tab = new int[n];

  std::cout << "Podaj " << n << " elementów: " << std::endl;

  for (int i = 0; i < n; i++)
    std::cin >> tab[i];

  std::cout << "Twoja tablica: " << std::endl;

  for (int i = 0; i < n; i++)
    std::cout << tab[i] << std::endl;

  delete[] tab;

  return 0;
}
```

Zmienne na stercie mogą żyć dłużej niż wskazujące na nie wskaźniki. Jeśli explicite nie uwolnimy dynamicznie zaalokowanej pamięci, to system operacyjny będzie dalej ją trzymał i bronił przed nadpisaniem. Jeśli nie żyje już nasz wskaźnik, to z jednej strony nie mamy w programie możliwości dostania się do zmiennych, które stworzyliśmy na stercie, a z drugiej marnujemy zasoby komputera, bo system operacyjny nie dopuszcza innych programów do tego obszaru pamięci. Taką sytuację nazywamy wyciekiem pamięci. Dla kilku zmiennych jest to nieodczuwalne, ale dla większych programów może szybko przeciążyć naszą maszynę.

### Tablica 2D

Tablice mogą mieć dowolną ilość wymiarów. Najczęściej będziemy jednak spotykać tablice jedno i dwuwymiarowe.

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

Dla tablic dwuwymiarowych alokacja i dealokacja pamięci odbywa się przy pomocy pętli. Stwórzmy macierz o liczbie wierszy równej zmiennej <code>wysokość</code> i liczbie kolumn równej zmiennej <code>szerokość</code>:

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
