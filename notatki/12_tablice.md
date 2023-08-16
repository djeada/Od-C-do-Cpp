## Tablice w C++

Tablice to kontenery przechowujące wiele elementów tego samego typu. Każdy element w tablicy można identyfikować za pomocą jego indeksu.

### Deklaracja tablicy

Aby zadeklarować tablicę w C++, umieszczamy liczbę elementów w nawiasach kwadratowych po typie danych i nazwie tablicy.

```c++
int numbers[5]; // Tablica składająca się z 5 elementów typu int.
```

Niezainicjalizowane tablice, zwłaszcza tablice lokalne (wewnątrz funkcji), mogą zawierać losowe wartości. Dlatego zaleca się inicjalizować tablicę podczas jej deklaracji.

```c++
int arrayA[3] = {1, 2, 3};
```

Możemy również pominąć rozmiar tablicy podczas jej inicjalizacji, a kompilator sam obliczy odpowiedni rozmiar na podstawie liczby podanych elementów.

```c++
int arrayB[] = {4, 5, 6, 7}; // Rozmiar to 4.
```

### Przeszukiwanie i wyświetlanie tablicy

Do przeszukiwania i wyświetlania tablicy często używa się pętli. Poniżej znajduje się przykład wczytywania i wyświetlania tablicy za pomocą pętli for.

```c++
#include <iostream>

const int SIZE = 5;

int main() {
    int arr[SIZE];

    std::cout << "Wprowadź " << SIZE << " liczb: " << std::endl;

    // Wczytywanie danych do tablicy
    for (int i = 0; i < SIZE; i++) {
        std::cin >> arr[i];
    }

    std::cout << "Elementy tablicy to:" << std::endl;

    // Wyświetlanie zawartości tablicy
    for (int i = 0; i < SIZE; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

Kiedy próbujemy uzyskać dostęp do indeksu tablicy poza jej zakresem, może to prowadzić do niezdefiniowanego zachowania programu. To zachowanie może być różne w zależności od sytuacji: od czytania nieprawidłowych danych, przez nadpisywanie pamięci poza tablicą, aż po awarię programu. Dlatego zawsze należy zachować ostrożność przy manipulacji indeksami tablicy. W wielu przypadkach warto rozważyć użycie kontenerów standardowych, takich jak std::vector, które oferują większe bezpieczeństwo i elastyczność niż tradycyjne tablice.

### Tablica jako wskaźnik

W C++, tablica to kontener przechowujący elementy tego samego typu. Jednak tablica sama w sobie może być traktowana jako wskaźnik do jej pierwszego elementu. Innymi słowy, `tab[0]` i `*tab` są równoważne. Poniżej znajduje się funkcja, która oblicza sumę elementów tablicy przyjmując jako argument wskaźnik do pierwszego elementu oraz długość tablicy.

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

Jest ważne, by pamiętać, że przekazując tablicę jako wskaźnik do funkcji, kompilator nie jest w stanie określić jej rzeczywistego rozmiaru. W tym przypadku musimy jawnie przekazać długość tablicy jako drugi argument funkcji. Operator sizeof nie będzie tutaj pomocny, ponieważ dla wskaźnika zwróci jedynie rozmiar typu wskaźnika, a nie całej tablicy.

### Arytmetyka wskaźników

Wskaźniki w C++ umożliwiają wykonanie operacji arytmetycznych. Poniżej znajduje się lista dostępnych operacji:

- `++`: Przesuwa wskaźnik do następnego elementu.
- `--`: Przesuwa wskaźnik do poprzedniego elementu.
- `+=`: Przesuwa wskaźnik o określoną liczbę elementów do przodu.
- `-=`: Przesuwa wskaźnik o określoną liczbę elementów do tyłu.
- `+`: Zwraca nowy wskaźnik przesunięty o określoną liczbę elementów od obecnego miejsca.
-  `-`: Jeśli użyte między dwoma wskaźnikami, zwraca różnicę (liczbę elementów) pomiędzy nimi.

Arytmetyka wskaźników jest szczególnie przydatna podczas operacji na tablicach. Umożliwia to przesuwanie się po tablicy bez konieczności korzystania z konkretnego indeksu. Jednak kluczowe jest przestrzeganie ostrożności i unikanie operacji poza zakresem tablicy, co może prowadzić do niezdefiniowanego zachowania programu.

### Dynamiczna alokacja pamięci

Dynamiczna alokacja pamięci w C++ pozwala na rezerwację przestrzeni w pamięci w czasie działania programu, zamiast podczas jego kompilacji. Aby zaalokować pamięć na stercie, korzystamy z operatora `new`. Do alokacji pojedynczej zmiennej używamy `new`, natomiast dla tablicy `new [liczba]`, gdzie "liczba" reprezentuje ilość elementów w tablicy.

```c++
#include <iostream>

int main() {
  std::cout << "Podaj liczbę elementów tablicy: ";
  int n;
  std::cin >> n;

  int *tab = new int[n];
  // Pozostała część kodu...
```

Gdy dynamicznie zaalokowana pamięć nie jest już potrzebna, musimy ją zwolnić. Do tego służy operator delete. Dla pojedynczej zmiennej używamy delete, natomiast dla tablicy `delete[]` - bez podawania liczby elementów.

```c++
  // ... Koniec pracy z tablicą
  delete[] tab;
  return 0;
}
```

Zarządzanie dynamicznie alokowaną pamięcią jest kluczowe. Niezwalnianie pamięci może prowadzić do wycieków pamięci, które w skumulowaniu mogą obciążyć zasoby systemu. Wyciek pamięci występuje, gdy program zaalokuje pamięć, lecz nigdy jej nie zwolni, co może prowadzić do zużycia wszystkich dostępnych zasobów.

Dodatkowo warto podkreślić, że dynamiczna alokacja pamięci ma pewne koszty - nie tylko w postaci zużywanej pamięci, ale też czasu potrzebnego na jej alokację i dealokację. Z tego powodu warto rozważyć, czy dynamiczna alokacja jest rzeczywiście konieczna w danym przypadku. W wielu sytuacjach może być bardziej opłacalne korzystanie z gotowych kontenerów, takich jak std::vector, które automatycznie zarządzają pamięcią.

### Tablica 2D

Tablica dwuwymiarowa, inaczej znana jako "2D array" w języku angielskim, można sobie wyobrazić jako tablicę tablic. Składa się ona z pewnej liczby rzędów, gdzie każdy rząd to jednowymiarowa tablica.

Przykładowa tablica 2D może wyglądać następująco:

```c++
int a[3][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };
```

W tym przypadku mamy do czynienia z tablicą o trzech rzędach i czterech kolumnach.

Aby stworzyć i wypełnić tablicę dwuwymiarową, można skorzystać z poniższego kodu:

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

Jednakże w niektórych przypadkach chcemy alokować pamięć dla tablicy dwuwymiarowej dynamicznie. Można to osiągnąć przy pomocy operatora new. Oto sposób dynamicznej alokacji i dealokacji dla tablicy 2D:

```c++
#include <iostream>

int main() {

  double **macierz;
  int wysokość, szerokość;

  std::cout << "Podaj wysokość i szerokość macierzy: ";
  std::cin >> wysokość >> szerokość;

  // Alokacja
  macierz = new double*[wysokość];

  for (int i = 0; i < wysokość; i++)
    macierz[i] = new double[szerokość];

  // Tu można wypełnić tablicę wartościami

  // Dealokacja
  for (int i = 0; i < wysokość; i++)
    delete[] macierz[i];

  delete[] macierz;

  return 0;
}
```

W tym kodzie użytkownik określa wymiary macierzy (wysokość i szerokość), po czym następuje dynamiczna alokacja pamięci dla niej. Ważne jest, aby po skończonej pracy z tablicą dynamiczną odpowiednio zwolnić zajmowaną przez nią pamięć, korzystając z operatora delete[].
