## Tablice

Tablice to kontenery przechowujące wiele elementów tego samego typu, uporządkowane w określonej kolejności. Każdy element w tablicy można identyfikować za pomocą jego indeksu, przy czym indeksy zaczynają się od zera. Tablice są fundamentalnym elementem języka C++, umożliwiającym przechowywanie i zarządzanie zestawami danych w sposób zorganizowany.

### Deklaracja tablicy

Aby zadeklarować tablicę w C++, umieszczamy liczbę elementów w nawiasach kwadratowych po typie danych i nazwie tablicy. Deklaracja tablicy rezerwuje blok pamięci dla określonej liczby elementów.

```c++
int numbers[5]; // Tablica składająca się z 5 elementów typu int.
```

Warto pamiętać, że niezainicjalizowane tablice, zwłaszcza tablice lokalne (wewnątrz funkcji), mogą zawierać losowe wartości. Dlatego zaleca się inicjalizować tablicę podczas jej deklaracji.

```c++
int arrayA[3] = {1, 2, 3}; // Inicjalizacja tablicy wartościami 1, 2, 3.
```

Możemy również pominąć rozmiar tablicy podczas jej inicjalizacji, a kompilator sam obliczy odpowiedni rozmiar na podstawie liczby podanych elementów.

```c++
int arrayB[] = {4, 5, 6, 7}; // Rozmiar to 4, ponieważ tablica zawiera 4 elementy.
```

### Przeszukiwanie i wyświetlanie tablicy

Do przeszukiwania i wyświetlania tablicy często używa się pętli. Poniżej znajduje się przykład wczytywania i wyświetlania tablicy za pomocą pętli for. Ten proces ilustruje, jak można iterować przez wszystkie elementy tablicy, aby wykonać operacje na jej zawartości.

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

### Dostęp do elementów tablicy i bezpieczeństwo

Dostęp do elementów tablicy odbywa się za pomocą operatora indeksowania `[]`. Poniższy przykład pokazuje, jak przypisywać wartości do elementów tablicy i je odczytywać.

```c++
int main() {
    int arr[3];
    arr[0] = 10; // Przypisanie wartości 10 do pierwszego elementu tablicy
    arr[1] = 20; // Przypisanie wartości 20 do drugiego elementu tablicy
    arr[2] = 30; // Przypisanie wartości 30 do trzeciego elementu tablicy

    std::cout << "Pierwszy element: " << arr[0] << std::endl;
    std::cout << "Drugi element: " << arr[1] << std::endl;
    std::cout << "Trzeci element: " << arr[2] << std::endl;

    return 0;
}
```

Kiedy próbujemy uzyskać dostęp do indeksu tablicy poza jej zakresem, może to prowadzić do niezdefiniowanego zachowania programu. To zachowanie może być różne w zależności od sytuacji: od czytania nieprawidłowych danych, przez nadpisywanie pamięci poza tablicą, aż po awarię programu. Dlatego zawsze należy zachować ostrożność przy manipulacji indeksami tablicy.

```c++
int main() {
    int arr[3] = {1, 2, 3};

    // Próba dostępu do elementu poza zakresem
    std::cout << arr[3] << std::endl; // Niezdefiniowane zachowanie

    return 0;
}
```

### Tablica jako wskaźnik

W C++, tablica to kontener przechowujący elementy tego samego typu. Jednak tablica sama w sobie może być traktowana jako wskaźnik do jej pierwszego elementu. Oznacza to, że odwołanie się do `tab[0]` jest równoważne z `*tab`. Kiedy przekazujemy tablicę do funkcji, faktycznie przekazujemy wskaźnik do jej pierwszego elementu. Dzięki temu możliwe jest operowanie na elementach tablicy w funkcjach, jak pokazano w poniższym przykładzie.

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

### Przekazywanie tablic do funkcji

Warto zauważyć, że przekazując tablicę jako wskaźnik do funkcji, kompilator nie zna jej rzeczywistego rozmiaru. Dlatego musimy jawnie przekazać długość tablicy jako drugi argument funkcji. Operator `sizeof` w tym kontekście zwróci jedynie rozmiar wskaźnika, a nie całej tablicy.

```c++
void printArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    printArray(arr, size);
    return 0;
}
```

### Arytmetyka wskaźników

Wskaźniki w C++ umożliwiają wykonanie operacji arytmetycznych, co pozwala na przesuwanie się po tablicy w sposób dynamiczny. Operacje te są bardzo użyteczne podczas manipulacji tablicami i strukturami danych.

#### Podstawowe operacje arytmetyczne na wskaźnikach:

- `++`: Przesuwa wskaźnik do następnego elementu.
- `--`: Przesuwa wskaźnik do poprzedniego elementu.
- `+=`: Przesuwa wskaźnik o określoną liczbę elementów do przodu.
- `-=`: Przesuwa wskaźnik o określoną liczbę elementów do tyłu.
- `+`: Zwraca nowy wskaźnik przesunięty o określoną liczbę elementów od obecnego miejsca.
- `-`: Jeśli użyte między dwoma wskaźnikami, zwraca różnicę (liczbę elementów) pomiędzy nimi.

#### Przykłady zastosowania arytmetyki wskaźników

```c++
#include <iostream>

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;

    std::cout << "Pierwszy element: " << *ptr << std::endl;

    ptr++; // Przesunięcie wskaźnika do następnego elementu
    std::cout << "Drugi element: " << *ptr << std::endl;

    ptr += 2; // Przesunięcie wskaźnika o dwa elementy do przodu
    std::cout << "Czwarty element: " << *ptr << std::endl;

    ptr--; // Przesunięcie wskaźnika do poprzedniego elementu
    std::cout << "Trzeci element: " << *ptr << std::endl;

    int *start = arr;
    int *end = arr + 4;
    std::cout << "Różnica między wskaźnikami start i end: " << end - start << std::endl;

    return 0;
}
```

### Bezpieczeństwo arytmetyki wskaźników

Chociaż arytmetyka wskaźników jest potężnym narzędziem, wymaga ostrożności. Operacje na wskaźnikach poza zakresem tablicy mogą prowadzić do niezdefiniowanego zachowania programu, które może objawiać się w różny sposób: od czytania nieprawidłowych danych, przez nadpisywanie pamięci, aż po awarie programu. Przykładem takiego niebezpiecznego zachowania jest:

```c++
int main() {
    int arr[3] = {1, 2, 3};
    int *ptr = arr;

    ptr += 5; // Przesunięcie wskaźnika poza zakres tablicy
    std::cout << *ptr << std::endl; // Niezdefiniowane zachowanie

    return 0;
}
```



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

### Zwracanie tablic z funkcji

W C++ istnieje kilka sposobów na zwracanie tablic z funkcji. Możemy używać wskaźników, dynamicznie alokowanej pamięci, struktur lub nowoczesnych kontenerów, takich jak `std::vector`. Każde podejście ma swoje zalety i wady, które zostaną omówione poniżej.

#### I. Zwracanie wskaźnika do tablicy

Jednym z najprostszych sposobów jest zwracanie wskaźnika do pierwszego elementu tablicy. Należy jednak pamiętać, że tablica musi być dynamicznie alokowana, aby jej zawartość była dostępna poza funkcją.

```c++
#include <iostream>

int* createArray(int size) {
    int* array = new int[size];
    for (int i = 0; i < size; ++i) {
        array[i] = i + 1;
    }
    return array;
}

int main() {
    int size = 5;
    int* myArray = createArray(size);

    for (int i = 0; i < size; ++i) {
        std::cout << myArray[i] << " ";
    }
    std::cout << std::endl;

    // Pamiętaj, aby zwolnić zaalokowaną pamięć
    delete[] myArray;

    return 0;
}
```

**Zalety:**
- Proste i bezpośrednie podejście.

**Wady:**
- Odpowiedzialność za zarządzanie pamięcią spoczywa na użytkowniku funkcji.
- Potencjalne wycieki pamięci, jeśli zapomni się zwolnić zaalokowaną pamięć.

#### II. Zwracanie tablicy przez strukturę

Innym podejściem jest opakowanie tablicy w strukturę i zwracanie tej struktury. Pozwala to na ominięcie problemów związanych z dynamiczną alokacją pamięci.

```c++
#include <iostream>

struct ArrayWrapper {
    int array[5];
};

ArrayWrapper createArray() {
    ArrayWrapper wrapper;
    for (int i = 0; i < 5; ++i) {
        wrapper.array[i] = i + 1;
    }
    return wrapper;
}

int main() {
    ArrayWrapper myArray = createArray();

    for (int i = 0; i < 5; ++i) {
        std::cout << myArray.array[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

**Zalety:**
- Unikamy dynamicznej alokacji pamięci i związanych z nią problemów.

**Wady:**
- Rozmiar tablicy musi być znany w czasie kompilacji.
- Nieelastyczne, jeśli rozmiar tablicy ma być zmienny.

#### III. Zwracanie wskaźnika do dynamicznie alokowanej tablicy z zarządzaniem pamięcią w funkcji wywołującej

Zamiast zwracać wskaźnik do dynamicznie alokowanej pamięci, możemy przekazać wskaźnik do funkcji, która wypełni tablicę danymi.

```c++
#include <iostream>

void createArray(int* array, int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = i + 1;
    }
}

int main() {
    int size = 5;
    int myArray[5];

    createArray(myArray, size);

    for (int i = 0; i < size; ++i) {
        std::cout << myArray[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

**Zalety:**
- Zarządzanie pamięcią jest prostsze, brak potrzeby ręcznego zwalniania pamięci.

**Wady:**
- Tablica musi być zadeklarowana i zaalokowana przed wywołaniem funkcji.

### Tablica 2D

Tablica dwuwymiarowa, inaczej znana jako "2D array" w języku angielskim, można sobie wyobrazić jako tablicę tablic. Składa się ona z pewnej liczby rzędów, gdzie każdy rząd to jednowymiarowa tablica. Tablice dwuwymiarowe są powszechnie używane w programowaniu do reprezentowania macierzy, siatek, czy tabel danych.

#### Deklaracja i Inicjalizacja Tablicy 2D

Deklaracja tablicy dwuwymiarowej wymaga podania zarówno liczby rzędów, jak i liczby kolumn. Oto przykład deklaracji i inicjalizacji tablicy 2D:

```c++
int a[3][4] = { 
    {1, 2, 3, 4}, 
    {5, 6, 7, 8}, 
    {9, 10, 11, 12} 
};
```

W tym przypadku mamy do czynienia z tablicą o trzech rzędach i czterech kolumnach. Każdy element w tablicy 2D może być dostępny za pomocą dwóch indeksów: pierwszego dla rzędu i drugiego dla kolumny.

#### Wczytywanie i Wyświetlanie Tablicy 2D

Poniżej przedstawiono kod, który pozwala na wczytanie danych do tablicy 2D od użytkownika i wyświetlenie jej zawartości.

```c++
#include <iostream>

const unsigned int n = 3;
const unsigned int m = 4;

int main() {
    int a[n][m];

    std::cout << "Podaj " << n * m << " elementów: " << std::endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }

    std::cout << "Twoja tablica: " << std::endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
```

#### Dynamiczna Alokacja Tablicy 2D

W niektórych przypadkach chcemy alokować pamięć dla tablicy dwuwymiarowej dynamicznie. Jest to szczególnie przydatne, gdy wymiary tablicy są nieznane w czasie kompilacji i muszą być określone w czasie wykonywania programu. Dynamiczną alokację pamięci można osiągnąć za pomocą operatora `new`.

```c++
#include <iostream>

int main() {
    int wysokość, szerokość;

    std::cout << "Podaj wysokość i szerokość macierzy: ";
    std::cin >> wysokość >> szerokość;

    // Alokacja dynamiczna
    double **macierz = new double*[wysokość];
    for (int i = 0; i < wysokość; i++) {
        macierz[i] = new double[szerokość];
    }

    // Wypełnianie tablicy wartościami
    std::cout << "Podaj wartości dla macierzy:" << std::endl;
    for (int i = 0; i < wysokość; i++) {
        for (int j = 0; j < szerokość; j++) {
            std::cin >> macierz[i][j];
        }
    }

    // Wyświetlanie zawartości tablicy
    std::cout << "Macierz:" << std::endl;
    for (int i = 0; i < wysokość; i++) {
        for (int j = 0; j < szerokość; j++) {
            std::cout << macierz[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Dealokacja pamięci
    for (int i = 0; i < wysokość; i++) {
        delete[] macierz[i];
    }
    delete[] macierz;

    return 0;
}
```

W tym kodzie użytkownik określa wymiary macierzy (wysokość i szerokość), po czym następuje dynamiczna alokacja pamięci dla niej. Ważne jest, aby po skończonej pracy z tablicą dynamiczną odpowiednio zwolnić zajmowaną przez nią pamięć, korzystając z operatora `delete[]`.

#### Przykład: Dodawanie Danych do Tablicy 2D

Poniżej przedstawiono przykład programu, który dynamicznie tworzy tablicę 2D, wypełnia ją danymi wprowadzonymi przez użytkownika i wyświetla jej zawartość.

```c++
#include <iostream>

int main() {
    int rows, cols;

    std::cout << "Podaj liczbę rzędów i kolumn: ";
    std::cin >> rows >> cols;

    // Dynamiczna alokacja pamięci dla tablicy 2D
    int** array = new int*[rows];
    for (int i = 0; i < rows; i++) {
        array[i] = new int[cols];
    }

    // Wczytywanie danych do tablicy
    std::cout << "Podaj " << rows * cols << " elementów:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> array[i][j];
        }
    }

    // Wyświetlanie zawartości tablicy
    std::cout << "Zawartość tablicy:" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << array[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Zwolnienie pamięci
    for (int i = 0; i < rows; i++) {
        delete[] array[i];
    }
    delete[] array;

    return 0;
}
```

#### Zastosowania Tablic 2D

Tablice 2D są powszechnie stosowane w różnych dziedzinach informatyki, takich jak:
- **Przetwarzanie obrazów:** Macierz pikseli obrazu.
- **Symulacje fizyczne:** Siatki i modele symulacji.
- **Przechowywanie danych:** Tabele danych, macierze matematyczne.
- **Gry komputerowe:** Plansze gier, mapy poziomów.

### Zalecenia dotyczące użycia tablic

1. **Inicjalizacja:** Zawsze inicjalizuj tablice, aby uniknąć losowych wartości.
2. **Bezpieczeństwo:** Sprawdzaj granice tablicy, aby zapobiec dostępowi poza zakresem.
3. **Kontenery standardowe:** W wielu przypadkach warto rozważyć użycie kontenerów standardowych, takich jak `std::vector`, które oferują większe bezpieczeństwo i elastyczność niż tradycyjne tablice.
