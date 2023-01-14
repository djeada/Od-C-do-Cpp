
## Funkcje

Funkcje pozwalają nam na zamknięcie określonego fragmentu kodu pod jedną nazwą. Umożliwia to zmniejszenie złożoności programu i zwiększenie jego czytelności.

### Tworzenie i wywoływanie funkcji

Elementy składowe funkcji to:

1. <code>Typ</code> zwracanej wartości - określa jaki typ danych ma zostać zwrócony przez funkcję.
2. <code>Imię</code> funkcji, dzięki któremu jest ona rozpoznawalna.
3. <code>Argumenty</code> - są to zewnętrzne wartości, które chcemy użyć w funkcji i chcemy żeby zostały nam podane w momencie jej wywołania.

Ogólny schemat pracy z funkcjami:

```c++
wybrany_typ nazwa_funkcji(argumenty...) {
  
  ... // ciało czyli kod, który chcemy, żeby został uruchomiony 
  ... // po wywołaniu nazwa_funkcji(argumenty...);
  
  return wartość; // zwracamy wartość, która musi zgadzać się z wybranym typem
}

int main() { 
  wybrany_typ x = nazwa_funkcji(argumenty...));
  return 0;  
}
```

### Deklaracja i definicja funkcji

Deklaracja funkcji to wyrażenie, które zawiera nazwę funkcji, jej argumenty oraz jej zwracany typ. Deklaracja musi pojawić się w kodzie przed wywołaniem funkcji. Definicja funkcji to deklaracja wraz z ciałem funkcji - czyli odpowiednim kodem, który ma zostać wykonany po wywołaniu funkcji.

Przykład:
```c++
#include <iostream>

// definicja
void fun1() { std::cout << "fun1" << std::endl; }

// deklaracja
void fun2();

int main() {
  fun1(); // OK
  fun2(); // OK
  fun3(); // BŁĄD

  return 0;
}

void fun2() { std::cout << "fun2" << std::endl; }

void fun3() { std::cout << "fun3" << std::endl; }
```

### Funkcja zwracająca wartość

Do zwracania wartości poprzez funkcję używamy słowa kluczowego <code>return</code>. Słowo kluczowe <code>return</code> przerywa działanie funkcji i zwraca wartość umieszczoną po nim w kodzie. Typ zwracanej wartości musi być taki sam jak typ funkcji. Funkcja nie będąca funkcją typu void musi zawsze zwracać wartość.

Przykład:
```c++
#include <iostream>

int suma(int x, int y) { return x + y; }

int main() {
  int a = 5;
  int b = 3;

  std::cout << suma(a, b) << std::endl;

  return 0;
}
```

### Funkcja typu void

Funkcje typu void nie zwracają żadnej wartości. Nie ma konieczności użycia słowa kluczowego <code>return</code>. Jeśli jednak zostanie użyte, to nie może być podana za nim żadna wartość. W kontekście funkcji typu void <code>return</code> służy jedynie do przerywania jej działania.

Przykład:
```c++
#include <iostream>

void wypisz_imie(string s) { std::cout << s << std::endl; }

int main() {
  std::string imie = "Karol";
  wypisz_imie(imie);

  return 0;
}
```

### Parametry z domyślną wartością

Parametry z domyślną wartością to takie, które w przypadku niepodania ich wartości przy wywołaniu funkcji, używana jest wartość podana w definicji funkcji. Jest to bardzo przydatne, gdyż pozwala na przesłanie mniejszej liczby argumentów do funkcji. Przykładem użycia parametrów z domyślną wartością może być funkcja `pomnoz` zaprezentowana poniżej:

```c++
#include <iostream>

int pomnoz(int a, int b = 3) { return a * b; }

int main() {
  int x = 2;
  int y = 7;

  std::cout << pomnoz(x, y) << std::endl; // Drugi argument ma wartosc y
  std::cout << pomnoz(x) << std::endl;    // Drugi argument ma domyslna wartosc

  return 0;
}
```

Uwaga: parametry z domyślną wartością mogą być podane w dowolnej kolejności, o ile parametry bez domyślnej wartości będą podane w odpowiedniej kolejności.

### Przekazywanie argumentów funkcji przez wartość i referencję

Istnieją dwa sposoby na przekazywanie argumentów do funkcji. Pierwszy to przekazywanie argumentów przez wartość. W tym przypadku funkcja otrzymuje kopię wartości argumentu. Wszelkie zmiany na tą wartość w funkcji nie wpływają na oryginalną zmienną. Przykładem tego może być funkcja `pomnoz` zaprezentowana poniżej, gdzie zmiana wartości zmiennej `a` w funkcji nie wpływa na wartość zmiennej `x` w `main`:

```c++
#include <iostream>

void pomnoz(int a, int b) { a = a * b; }

int main() {
  int x = 2;

  pomnoz(x, 3);
  std::cout << x << std::endl; // Wypisuje 2, poniewaz wartosc x w funkcji pomnoz nie zostala zmieniona

  return 0;
}
```

Drugi sposób na przekazywanie argumentów to przekazywanie argumentów przez referencję. W tym przypadku funkcja otrzymuje referencję do oryginalnej zmiennej. Wszelkie zmiany na tą wartość w odbywają się bezpośrednio na oryginalnej zmiennej. Przykładem tego może być funkcja `pomnoz` zaprezentowana poniżej, gdzie zmiana wartości zmiennej `a` w funkcji wpływa na wartość zmiennej `x` w `main`:

```c++
#include <iostream>

void pomnoz(int &a, int &b) { a = a * b; }

int main() {
  int x = 2;

  pomnoz(x, 3);
  std::cout << x << std::endl; // Wypisuje 6, poniewaz wartosc x w funkcji pomnoz zostala zmieniona

  return 0;
}
```

Uwaga: przez referencję możemy przekazywać jedynie l-wartości.
