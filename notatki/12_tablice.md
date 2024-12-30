## Tablice

Tablice to kontenery przechowujące wiele elementów tego samego typu, uporządkowane w określonej kolejności. Każdy element w tablicy można identyfikować za pomocą jego indeksu, przy czym indeksy zaczynają się od zera. Tablice są fundamentalnym elementem języka C++, umożliwiającym przechowywanie i zarządzanie zestawami danych w sposób zorganizowany. Ich wykorzystanie pozwala na zdefiniowanie konkretnego obszaru pamięci, w którym zostaną przechowane wszystkie elementy danej kolekcji.

Tablice w C++ są niezwykle ważne dla początkujących programistów, ponieważ wprowadzają dość podstawowe, a jednocześnie bardzo przydatne pojęcia związane ze strukturą danych. Zanim jednak zaczniemy intensywnie korzystać z tablic, warto zapoznać się z ich najważniejszymi cechami: rozmiarem określanym w czasie kompilacji (w przypadku tablic statycznych), koniecznością podawania typu przechowywanych elementów oraz mechanizmami dostępu do zawartości tablicy. Dzięki tym elementom programista może lepiej zrozumieć, jak zarządzać pamięcią w swoim programie.

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

W sytuacjach, w których znamy dokładną liczbę elementów, które musimy przechować, tablice statyczne są dobrym wyborem ze względu na wydajność i prostotę. Jeżeli jednak nie jesteśmy pewni co do rozmiaru kolekcji, możemy rozważyć alternatywy, takie jak tablice dynamiczne bądź kontenery z biblioteki standardowej (std::vector, std::array). Każde z tych rozwiązań ma swoje zalety i ograniczenia, ale sama idea tablic pozostaje przydatnym fundamentem dla zrozumienia działania struktur danych w C++.

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

Pętle for (lub inne konstrukcje iteracyjne) są podstawowym narzędziem służącym do przechodzenia przez kolejne elementy tablicy i wykonywania na nich operacji, takich jak sumowanie, szukanie największego elementu czy wyświetlanie zawartości. Dzięki nim można łatwo kontrolować indeksy i unikać ewentualnych błędów związanych z wychodzeniem poza zakres tablicy. W praktyce, przy bardziej złożonych zadaniach, warto łączyć tę technikę z innymi, np. z warunkami if, aby uzyskiwać bardziej skomplikowane efekty przetwarzania danych.

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

Bezpieczeństwo podczas korzystania z tablic jest kluczowe w kontekście programów komercyjnych oraz systemów, w których stabilność i brak błędów są absolutnym priorytetem. Chociaż w małych, testowych projektach konsekwencje wyjścia poza zakres tablicy mogą wydawać się mało dotkliwe, w większych aplikacjach może to prowadzić do trudnych do wykrycia awarii czy nawet luk bezpieczeństwa. Z tego względu, przed przetworzeniem kolejnego elementu zawsze upewniaj się, że nie wykraczasz poza rozmiar zdefiniowanej tablicy.

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

Warto zwrócić uwagę, że mimo iż tablica może być rozpoznana przez kompilator jako wskaźnik, nadal obiekty tych typów różnią się pod pewnymi względami. Tablica statyczna (np. `int arr[5]`) ma zarezerwowaną określoną ilość miejsca na stosie w momencie kompilacji, natomiast wskaźnik jest tylko zmienną przechowującą adres pamięci. Mechanizm automatycznej konwersji do wskaźnika ogranicza się głównie do kontekstu przekazywania tablic jako argumentów do funkcji, co bywa bardzo wygodne, ale jednocześnie wymaga dbałości o informacje dotyczące rozmiaru tablicy.

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

Z praktycznego punktu widzenia, przekazywanie wskaźnika do funkcji zapewnia pewną elastyczność w działaniu programu, jednak wymaga odpowiedzialnego obchodzenia się z pamięcią i dokładnego pilnowania zakresu. W większych projektach często korzysta się ze zdefiniowanych struktur lub klas, a także z kontenerów biblioteki standardowej (m.in. `std::vector`), które automatycznie przechowują informacje o swoim rozmiarze i zapewniają metody kontroli dostępu do elementów.

### Arytmetyka wskaźników

Wskaźniki w C++ umożliwiają wykonanie operacji arytmetycznych, co pozwala na przesuwanie się po tablicy w sposób dynamiczny. Operacje te są bardzo użyteczne podczas manipulacji tablicami i strukturami danych.

#### Podstawowe operacje arytmetyczne na wskaźnikach:

| Operator | Opis                                                                                  |
|----------|---------------------------------------------------------------------------------------|
| `++`     | Przesuwa wskaźnik do następnego elementu.                                             |
| `--`     | Przesuwa wskaźnik do poprzedniego elementu.                                           |
| `+=`     | Przesuwa wskaźnik o określoną liczbę elementów do przodu.                             |
| `-=`     | Przesuwa wskaźnik o określoną liczbę elementów do tyłu.                               |
| `+`      | Zwraca nowy wskaźnik przesunięty o określoną liczbę elementów od obecnego miejsca.    |
| `-`      | Jeśli użyte między dwoma wskaźnikami, zwraca różnicę (liczbę elementów) pomiędzy nimi.|

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

Arytmetyka wskaźników może wydawać się nieco abstrakcyjna osobom, które nie miały dotąd styczności z niskopoziomowymi zagadnieniami pamięci. Jednak w językach z rodziny C/C++ stanowi ona potężne narzędzie, pozwalające na dostęp do poszczególnych komórek pamięci i poruszanie się między nimi z dużą swobodą. Warto jednak pamiętać, że większe możliwości zawsze pociągają za sobą większą odpowiedzialność. Każdy błąd wynikający z niepoprawnej arytmetyki wskaźników może powodować trudne do wykrycia błędy w programie.

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

W celu uniknięcia błędów związanych z tego typu niepożądanymi operacjami, warto zawsze kontrolować, w jakim obszarze pamięci się poruszamy. Najczęściej wiąże się to z pilnowaniem limitów pętli iterujących po tablicy lub stosowaniem wyższych abstrakcji (np. wspomniany już wcześniej `std::vector`). Zasada ograniczonego zaufania do wskaźników i sprawdzanie, czy dany indeks mieści się w granicach tablicy, w znacznym stopniu redukuje ryzyko nieoczekiwanych awarii.

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

Gdy dynamicznie zaalokowana pamięć nie jest już potrzebna, musimy ją zwolnić. Do tego służy operator `delete`. Dla pojedynczej zmiennej używamy `delete`, natomiast dla tablicy `delete[]` - bez podawania liczby elementów.

```c++
  // ... Koniec pracy z tablicą
  delete[] tab;
  return 0;
}
```

Zarządzanie dynamicznie alokowaną pamięcią jest kluczowe. Niezwalnianie pamięci może prowadzić do wycieków pamięci, które w skumulowaniu mogą obciążyć zasoby systemu. Wyciek pamięci występuje, gdy program zaalokuje pamięć, lecz nigdy jej nie zwolni, co może prowadzić do zużycia wszystkich dostępnych zasobów.

Dodatkowo warto podkreślić, że dynamiczna alokacja pamięci ma pewne koszty - nie tylko w postaci zużywanej pamięci, ale też czasu potrzebnego na jej alokację i dealokację. Z tego powodu warto rozważyć, czy dynamiczna alokacja jest rzeczywiście konieczna w danym przypadku. W wielu sytuacjach może być bardziej opłacalne korzystanie z gotowych kontenerów, takich jak `std::vector`, które automatycznie zarządzają pamięcią.

Co więcej, dynamiczna alokacja daje dużą elastyczność w sytuacjach, gdy nie znamy dokładnego rozmiaru tablicy w czasie kompilacji, lub gdy rozmiar ten może się zmieniać w trakcie działania programu. Jednak przy tej swobodzie zawsze należy pamiętać o ryzyku błędów i obowiązku samodzielnego zarządzania pamięcią. Niepoprawne lub zbyt późne zwolnienie zasobów może prowadzić do destabilizacji działania programu i licznych problemów z wydajnością.

### Zwracanie tablic z funkcji

W C++ istnieje kilka sposobów na zwracanie tablic z funkcji. Możemy używać wskaźników, dynamicznie alokowanej pamięci, struktur lub nowoczesnych kontenerów, takich jak `std::vector`. Każde podejście ma swoje zalety i wady, które zostaną omówione poniżej. Wybór konkretnej metody zależy w dużej mierze od charakteru problemu, z którym się mierzymy — od tego, czy nasza tablica ma mieć stały rozmiar, być zmienna w trakcie działania programu, czy też czy chcemy z niej korzystać tylko lokalnie, czy również poza funkcją. Przed podjęciem decyzji warto przemyśleć długoterminowe konsekwencje dotyczące wydajności i zarządzania pamięcią.

#### I. Zwracanie wskaźnika do tablicy

Jednym z najprostszych sposobów jest zwracanie wskaźnika do pierwszego elementu tablicy. Należy jednak pamiętać, że tablica musi być dynamicznie alokowana, aby jej zawartość była dostępna poza funkcją. Podejście to jest szczególnie przydatne, jeśli nie znamy dokładnie rozmiaru tablicy w czasie kompilacji i chcemy zaalokować ją w trakcie działania programu. Trzeba jednak zwrócić uwagę na konieczność ręcznego zwalniania pamięci po zakończeniu korzystania z tablicy.

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
- Możliwe do zastosowania, gdy rozmiar tablicy nie jest znany w czasie kompilacji.

**Wady:**

- Odpowiedzialność za zarządzanie pamięcią spoczywa na użytkowniku funkcji.
- Potencjalne wycieki pamięci, jeśli zapomni się zwolnić zaalokowaną pamięć.
- Konieczność pamiętania, gdzie w kodzie zaalokowano pamięć, aby móc ją poprawnie zwolnić.

#### II. Zwracanie tablicy przez strukturę

Innym podejściem jest opakowanie tablicy w strukturę i zwracanie tej struktury. Pozwala to na ominięcie problemów związanych z dynamiczną alokacją pamięci, gdyż zwracany obiekt (struktura) istnieje w obszarze stosu i jest automatycznie zarządzany przez kompilator. Rozwiązanie to sprawdza się w sytuacjach, w których rozmiar tablicy jest z góry znany i nie zamierzamy go zmieniać w trakcie działania programu.

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
- Łatwiejsze zarządzanie cyklem życia obiektu (struktury), który jest automatycznie niszczony poza swoim zasięgiem.

**Wady:**

- Rozmiar tablicy musi być znany w czasie kompilacji.
- Nieelastyczne, jeśli rozmiar tablicy ma być zmienny.
- W przypadku większych tablic może pojawić się koszt kopiowania podczas zwracania struktury, chociaż w praktyce nowoczesne kompilatory C++ optymalizują takie sytuacje (Return Value Optimization).

#### III. Zwracanie wskaźnika do dynamicznie alokowanej tablicy z zarządzaniem pamięcią w funkcji wywołującej

Zamiast zwracać wskaźnik do dynamicznie alokowanej pamięci, możemy przekazać wskaźnik do funkcji, która wypełni tablicę danymi. Dzięki temu kontrola nad tym, jak i gdzie pamięć jest alokowana, pozostaje w całości po stronie funkcji wywołującej. Jest to wygodne w sytuacjach, w których już dysponujemy pewnym obszarem pamięci (np. statycznie zdefiniowaną tablicą) i chcemy jedynie, aby funkcja ją zainicjalizowała.

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

- Zarządzanie pamięcią jest prostsze, brak potrzeby ręcznego zwalniania pamięci w funkcji wywołującej, jeśli tablica jest statyczna.
- Tablica może być zaalokowana przez wywołującego w dowolny sposób (na stosie lub dynamicznie), a funkcja jedynie ją wypełnia.

**Wady:**

- Tablica musi być zadeklarowana i zaalokowana przed wywołaniem funkcji, co oznacza mniejszą elastyczność, jeśli dopiero w funkcji chcemy określić rozmiar.
- Funkcja musi polegać na poprawnym rozmiarze tablicy przekazanej przez wywołującego, co wymaga dodatkowej ostrożności i sprawdzania ewentualnych błędów.

### Tablica 2D

Tablica dwuwymiarowa, inaczej znana jako „2D array” w języku angielskim, można sobie wyobrazić jako tablicę tablic. Składa się ona z pewnej liczby rzędów, gdzie każdy rząd to jednowymiarowa tablica. Tablice dwuwymiarowe są powszechnie używane w programowaniu do reprezentowania macierzy, siatek czy tabel danych. Dzięki nim możemy w przejrzysty sposób zarządzać danymi, które posiadają dwa wymiary (np. współrzędne w przestrzeni 2D, piksele obrazu, czy tabele w bazach danych).

#### Deklaracja i Inicjalizacja Tablicy 2D

Deklaracja tablicy dwuwymiarowej wymaga podania zarówno liczby rzędów, jak i liczby kolumn. Oto przykład deklaracji i inicjalizacji tablicy 2D:

```c++
int a[3][4] = { 
    {1, 2, 3, 4}, 
    {5, 6, 7, 8}, 
    {9, 10, 11, 12} 
};
```

W tym przypadku mamy do czynienia z tablicą o trzech rzędach i czterech kolumnach. Każdy element w tablicy 2D może być dostępny za pomocą dwóch indeksów: pierwszego dla rzędu i drugiego dla kolumny. Takie rozwiązanie doskonale sprawdza się w sytuacjach, w których z góry znamy rozmiar siatki (np. macierze matematyczne stałej wielkości).

#### Wczytywanie i Wyświetlanie Tablicy 2D

Poniżej przedstawiono kod, który pozwala na wczytanie danych do tablicy 2D od użytkownika i wyświetlenie jej zawartości. Takie operacje są często stosowane w zadaniach z przetwarzania danych, na przykład przy analizie arkuszy kalkulacyjnych lub w wypadku symulacji fizycznych, gdzie dane wejściowe określają warunki początkowe.

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

Dzięki wykorzystaniu zagnieżdżonej pętli `for`, iterujemy po wszystkich wierszach i kolumnach tablicy, co pozwala w przystępny sposób zarówno wczytywać, jak i wyświetlać zawartość tablicy. Strukturę takiej tablicy można łatwo przenieść na bardziej złożone zastosowania, jak systemy bazodanowe czy oprogramowanie do analizy zdjęć.

#### Dynamiczna Alokacja Tablicy 2D

W niektórych przypadkach chcemy alokować pamięć dla tablicy dwuwymiarowej dynamicznie. Jest to szczególnie przydatne, gdy wymiary tablicy są nieznane w czasie kompilacji i muszą być określone w czasie wykonywania programu. Dynamiczną alokację pamięci można osiągnąć za pomocą operatora `new`. Takie podejście jest typowe w bardziej złożonych aplikacjach, gdzie ilość danych wejściowych może zależeć od pliku konfiguracyjnego, danych z sieci czy innych zmiennych czynników.

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

W powyższym kodzie użytkownik określa wymiary macierzy (wysokość i szerokość), po czym następuje dynamiczna alokacja pamięci dla niej. Ważne jest, aby po skończonej pracy z tablicą dynamiczną odpowiednio zwolnić zajmowaną przez nią pamięć, korzystając z operatora `delete[]`. Pamiętajmy, że w bardziej rozbudowanych programach zapominanie o dealokacji pamięci może prowadzić do wycieków pamięci, powodujących stopniowe spowalnianie programu, a w skrajnych przypadkach nawet jego awarię.

#### Przykład: Dodawanie Danych do Tablicy 2D

Poniżej przedstawiono przykład programu, który dynamicznie tworzy tablicę 2D, wypełnia ją danymi wprowadzonymi przez użytkownika i wyświetla jej zawartość. Jest to jeden z częstszych scenariuszy, spotykanych w praktycznych zastosowaniach, np. podczas tworzenia prostych arkuszy kalkulacyjnych, systemów do edycji obrazów czy nawet gier 2D, w których mapa jest reprezentowana jako dwuwymiarowa tablica.

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

W programie tym w prosty sposób pokazano, jak alokować i dealokować pamięć dla tablicy 2D oraz jak odczytywać i wyświetlać dane. Przy rozbudowie takiego kodu w kierunku większych projektów należy pamiętać o zabezpieczeniach, np. sprawdzaniu poprawności wprowadzonych danych czy wyłapywaniu wyjątków, które mogą wystąpić przy niepoprawnej alokacji pamięci.

#### Zastosowania Tablic 2D

Tablice 2D są powszechnie stosowane w różnych dziedzinach informatyki, takich jak:

- W **przetwarzaniu obrazów** macierze są używane do reprezentowania pikseli obrazu, co umożliwia manipulowanie i analizowanie danych obrazowych. Każdy element macierzy może wtedy odpowiadać jednemu pikselowi.
- **Symulacje fizyczne** często wykorzystują macierze do reprezentowania siatek i modeli symulacji, co pozwala na dokładne odwzorowanie zjawisk fizycznych, np. przepływu ciepła czy symulacji ruchu cieczy.
- W kontekście **przechowywania danych**, macierze są używane do tworzenia tabel danych i macierzy matematycznych, co ułatwia organizację i obliczenia. Takie podejście bywa niezbędne w analizie dużych zbiorów danych.
- W **grach komputerowych** macierze mogą reprezentować plansze gier oraz mapy poziomów, co umożliwia efektywne zarządzanie strukturą i logiką gry. Dodatkowo ułatwia to określenie pozycji obiektów oraz kolizji.

### Zalecenia dotyczące użycia tablic

- **Zawsze inicjalizuj tablice**, aby uniknąć problemów z losowymi wartościami, które mogą prowadzić do nieprzewidywalnych błędów w programie. W przypadku tablic lokalnych warto wypełnić je odpowiednią domyślną wartością jeszcze przed pierwszym użyciem.
- **Sprawdzaj granice tablicy**, aby zapewnić bezpieczeństwo i zapobiec dostępowi do elementów poza zakresem, co może prowadzić do awarii programu. Jest to szczególnie ważne w języku C++, który nie ma wbudowanych mechanizmów automatycznej ochrony przed wyjściem poza zakres.
- W wielu przypadkach warto rozważyć **użycie kontenerów standardowych**, takich jak `std::vector`, które oferują większe bezpieczeństwo i elastyczność niż tradycyjne tablice, eliminując ryzyko błędów związanych z zarządzaniem pamięcią. Dzięki temu możemy zminimalizować liczbę błędów związanych z niewłaściwą alokacją i dealokacją.
- Jeśli jednak korzystasz z tablic surowych (ang. raw arrays), **pamiętaj o odpowiedzialności za zarządzanie pamięcią**. Dotyczy to zarówno alokacji (z operatorem `new`), jak i dealokacji (z operatorem `delete[]`). Niewłaściwe korzystanie z pamięci może skutkować wyciekami, a w konsekwencji niestabilnością i awariami oprogramowania.
