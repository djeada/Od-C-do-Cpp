## Funkcje

Funkcje są jednym z kluczowych narzędzi w programowaniu, które pozwalają na podzielenie kodu na mniejsze, zarządzalne części. Funkcje składają się z deklaracji (nazwa, typ zwracany, argumenty) i definicji (ciało funkcji).

### Tworzenie i wywoływanie funkcji

Podstawowe składniki funkcji to:

1. **Typ zwracanej wartości**: Określa, jaki typ danych zostanie zwrócony przez funkcję.
2. **Nazwa funkcji**: Umożliwia jej identyfikację w kodzie.
3. **Lista argumentów**: Są to wartości przekazywane do funkcji podczas jej wywołania.

Struktura funkcji:

```c++
typ_zwracanej_wartości nazwa_funkcji(typ_argumentu nazwa_argumentu, ...) {
    // ciało funkcji
    return wartość; // zwracana wartość (jeśli funkcja nie jest typu void)
}

int main() { 
  typ_zwracanej_wartości wynik = nazwa_funkcji(argumenty...);
  return 0;  
}
```

### Deklaracja vs. Definicja funkcji

- Deklaracja funkcji mówi kompilatorowi o nazwie funkcji, jej zwracanym typie oraz o typach argumentów. Pozwala to wywoływać funkcję przed jej faktyczną definicją w kodzie.
- Definicja funkcji zawiera rzeczywisty kod funkcji. Zawiera zarówno deklarację, jak i ciało funkcji.

Przykład:

```c++

#include <iostream>

// definicja funkcji fun1
void fun1() { std::cout << "fun1" << std::endl; }

// deklaracja funkcji fun2 (jej definicja znajduje się poniżej funkcji main)
void fun2();

int main() {
  fun1(); // wywołanie fun1 - działa, ponieważ fun1 została zdefiniowana wcześniej
  fun2(); // wywołanie fun2 - również działa, mimo że definicja jest poniżej, dzięki wcześniejszej deklaracji

  return 0;
}

// definicja funkcji fun2 (po funkcji main)
void fun2() { std::cout << "fun2" << std::endl; }

// UWAGA: fun3 nie została ani zadeklarowana, ani zdefiniowana przed funkcją main, dlatego jej wywołanie by się nie powiodło
```

W praktyce dobre jest umieszczanie deklaracji funkcji w plikach nagłówkowych (.h lub .hpp), a ich definicji w plikach źródłowych (.cpp), aby zachować porządek i modularność kodu.

### Funkcja zwracająca wartość

Funkcje, które zwracają wartość, muszą określić swój typ zwracanej wartości w deklaracji. Aby zwrócić wartość, używamy słowa kluczowego `return`, które kończy wykonywanie funkcji i zwraca określoną wartość. Typ zwracanej wartości musi być zgodny z deklarowanym typem funkcji.

Przykład:

```c++
#include <iostream>

int suma(int x, int y) { return x + y; }

int main() {
  int a = 5;
  int b = 3;
  std::cout << "Suma a + b: " << suma(a, b) << std::endl;
  return 0;
}
```

### Funkcje typu void

Funkcje typu void nie zwracają wartości. Słowo kluczowe return nie jest wymagane, chociaż może być używane do wczesnego zakończenia funkcji.

Przykład:

```c++
#include <iostream>

void wypisz_imie(const std::string& s) { std::cout << "Imię: " << s << std::endl; }

int main() {
  std::string imie = "Karol";
  wypisz_imie(imie);
  return 0;
}
```

### Parametry z domyślną wartością

Funkcje w C++ mogą mieć parametry z domyślnymi wartościami. Jeśli taki parametr nie jest dostarczany podczas wywoływania funkcji, używana jest jego domyślna wartość. Ułatwia to tworzenie funkcji bardziej elastycznych, które można dostosowywać do różnych potrzeb.

Przykład:

```c++
#include <iostream>

int pomnoz(int a, int b = 3) { return a * b; }

int main() {
  int x = 2;
  int y = 7;

  std::cout << "x * y: " << pomnoz(x, y) << std::endl; // Używając wartości y jako drugiego argumentu
  std::cout << "x * 3: " << pomnoz(x) << std::endl;    // Używając domyślnej wartości dla drugiego argumentu

  return 0;
}
```

Uwaga: Jeśli chcemy ustawić domyślną wartość dla jednego parametru, wszystkie kolejne parametry (po nim) także muszą mieć domyślne wartości.

### Przekazywanie argumentów funkcji przez wartość i referencję

Podczas projektowania funkcji w C++, możemy wybrać, czy chcemy przekazać argumenty przez wartość, czy przez referencję.

#### Przekazywanie przez wartość

Przekazując argument przez wartość, funkcja otrzymuje **kopię** wartości argumentu. Wszelkie modyfikacje tej kopii w ciele funkcji nie wpływają na oryginalną zmienną.

Przykład:

```c++
#include <iostream>

void pomnoz(int a, int b) { a = a * b; }

int main() {
  int x = 2;
  pomnoz(x, 3);
  
  std::cout << x << std::endl;  // Wypisuje 2, ponieważ wartość x nie została zmieniona w funkcji pomnoz

  return 0;
}
```

#### Przekazywanie przez referencję

Jeśli argument jest przekazywany przez referencję, funkcja pracuje bezpośrednio na **oryginalnej** zmiennej, a nie na jej kopii. Dlatego modyfikacje tej zmiennej w ciele funkcji wpływają na oryginalną zmienną.

Przykład:

```c++
#include <iostream>

void pomnoz(int &a, int b) { a = a * b; }

int main() {
  int x = 2;
  pomnoz(x, 3);
  
  std::cout << x << std::endl;  // Wypisuje 6, ponieważ wartość x została zmieniona w funkcji pomnoz

  return 0;
}
```

Uwaga: Referencje są idealne do przekazywania obiektów o dużym rozmiarze (np. duże wektory lub macierze), ponieważ unika się wtedy kosztownego kopiowania. Jednak trzeba być ostrożnym, aby nie modyfikować przekazanych danych bez zamierzenia. Jeśli chcesz użyć referencji, ale nie chcesz modyfikować oryginalnych danych, możesz użyć referencji stałej:

```c++
void funkcja(const int &param) {
    // można odczytać wartość param, ale nie można jej modyfikować
}
```

Dzięki temu funkcja ma dostęp do oryginalnych danych bez konieczności ich kopiowania, ale jednocześnie jest pewność, że dane nie zostaną przypadkowo zmienione wewnątrz funkcji.
