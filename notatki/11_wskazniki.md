## Wskaźniki

Wskaźnik to zmienna, która przechowuje adres innej zmiennej. Dodatkowo przy pomocy wskaźników mamy możliwość modyfikowania zmiennych, których adresy przechowują wskaźniki.

Aby zadeklarować wskaźnik, należy użyć operatora * przed nazwą zmiennej, która będzie przechowywać adres. Typ zmiennej, której adres przechowuje wskaźnik, musi być jawnie określony.

```c++
#include <iostream>

int main() {
  // Deklaracja wskaźników
  int *p1;  // wskaźnik przechowujący adres zmiennej typu int
  double *p2;  // wskaźnik przechowujący adres zmiennej typu double
  std::string *p3;  // wskaźnik przechowujący adres zmiennej typu std::string

  // Inicjalizacja wskaźników
  int x = 4;
  double y = 3.5;
  std::string s = "napis";

  p1 = &x;    // OK. Typy się zgadzają
  p2 = &y;
  p3 = &s;
  
  std::cout << "Wartość zmiennej x: " << x << std::endl;
  std::cout << "Wartość zmiennej y: " << y << std::endl;
  std::cout << "Wartość zmiennej s: " << s << std::endl;
  
  return 0;
}
```

### Dereferencja

Aby odczytać wartość zmiennej, na którą wskazuje wskaźnik, należy użyć operatora * przed nazwą wskaźnika (<code>*nazwa_wskaznika</code>).

```c++
#include <iostream>
#include <string>

int main() {
  int x = 4;
  double y = 3.5;
  std::string s = "napis";

  int *p1 = &x;
  double *p2 = &y;
  std::string *p3 = &s;

  std::cout << "Wartość zmiennej x: " << *p1 << std::endl;
  std::cout << "Wartość zmiennej y: " << *p2 << std::endl;
  std::cout << "Wartość zmiennej s: " << *p3 << std::endl;

  return 0;
}
```

### Wskaźnik na wskaźnik

Operator * pozwala również tworzyć wskaźniki przechowujące adresy innych wskaźników. W celu utworzenia wskaźnika na wskaźnik należy dodać kolejny operator * przed nazwą zmiennej.

```c++
int main() {
  int i = 20;
  int *j = &i;  // j to wskaźnik na zmienną i
  int **k = &j;  // k to wskaźnik na wskaźnik j
  int ***l = &k;  // l to wskaźnik na wskaźnik k
  
  std::cout << "Wartość zmiennej i: " << **k << std::endl;
  // równoważne z: std::cout << "Wartość zmiennej i: " << *j << std::endl;
  
  return 0;
}
```

### Wskaźnik na NULL

`NULL` to specjalna wartość wskaźnika, która symbolizuje brak wskazywania na jakikolwiek obiekt. Może ona służyć do oznaczenia końca listy połączonej, sygnalizowania braku możliwości przydziału pamięci lub otwarcia pliku. W C, implementacja `NULL` jest zdefiniowana jako `0` lub `((void*)0)`, oba przypadki służą dokładnie do tego samego celu.

Należy jednak pamiętać, że `NULL` jest po prostu zerem, co może być mylące szczególnie gdy chcemy sprawdzić czy wskaźnik jest pusty. Dlatego najlepiej jest używać konstrukcji:

```c++
if (wsk != NULL) {
}
```

W C++ pojawił się również `nullptr`, który jest młodszym bratem `NULL`. `nullptr` został wprowadzony, ponieważ w C++ możliwe jest przeciążanie funkcji, czyli definiowanie kilku funkcji o tej samej nazwie, ale z różnymi typami parametrów.

```c++
void foo(void *wsk);
void foo(int liczba);
```

Jeśli wywołamy `foo(NULL)`, to zostanie użyta druga funkcja. `nullptr` zapobiega takim sytuacjom, ponieważ nigdy nie jest interpretowany jako liczba.

W związku z powyższym, jeśli piszesz kod w C++, to należy używać `nullptr` zamiast `NULL`.

Przykład:

```c++
int *wsk = nullptr;
if(wsk == nullptr)
   cout << "wskaznik wsk jest pusty" << endl;
```

Przykład 2:

```c++
class A {};
A *a = nullptr;
if (a == nullptr)
    cout << "wskaznik a jest pusty" << endl;
```

### Stałe wskaźniki

Podobnie jak możemy deklarować zwykłe stałe, tak samo możemy mieć stałe wskaźniki - jednak są ich dwa rodzaje. Wskaźniki na stałą wartość:

```c++
  const int *a;
  int const *a; // rownowazne do poprzedniego przykladu
```

oraz stałe wskaźniki:

```c++
  int *const b;
```

Słowo const przed typem działa tak samo jak w przypadku zwykłych stałych, oznacza to, że nie możemy zmienić wartości wskazywanej przez wskaźnik.

W drugim przypadku, słowo const jest tuż za gwiazdką oznaczającą typ wskaźnikowy, co skutkuje stworzeniem stałego wskaźnika, czyli takiego, którego nie można przestawić na inny adres.

```c++
#include <iostream>

int main() {
    int x = 5;
    int y = 10;
    int* const ptr1 = &x; // stały wskaźnik na zmienną x
    const int* ptr2 = &y; // wskaźnik na stałą y
    
    std::cout << "Wartość x: " << x << std::endl;
    std::cout << "Wartość y: " << y << std::endl;
    std::cout << "Wartość wskazywana przez ptr1: " << *ptr1 << std::endl;
    std::cout << "Wartość wskazywana przez ptr2: " << *ptr2 << std::endl;
    
    *ptr1 = 7; // poprawne, możemy zmienić wartość wskazywaną przez stały wskaźnik
    ptr2 = &x; // poprawne, możemy zmienic adres na ktory wskazuje wskaźnik na stałą
    // *ptr2 = 7; // niepoprawne, nie możemy zmienić wartości wskazywanej przez wskaźnik na stałą
    //ptr1 = &y; // niepoprawne, nie możemy zmienic adresu na ktory wskazuje wskaźnik na stałą

    std::cout << "Wartość x po zmianie: " << x << std::endl;
    std::cout << "Wartość y po zmianie: " << y << std::endl;
    std::cout << "Wartość wskazywana przez ptr1 po zmianie: " << *ptr1 << std::endl;
    std::cout << "Wartość wskazywana przez ptr2 po zmianie: " << *ptr2 << std::endl;
    
    return 0;
}
```
