## Funkcje

Za pomocą funkcji możemy część kodu zamknąć pod jedną nazwą.

### Tworzenie i wywoływanie funkcji

Elementy składowe funkcji to:

1. <code>Typ</code> zwracanej wartości.
1. <code>Imię</code> funkcji, dzięki któremu jest ona rozpoznawalna.
1. <code>Argumenty</code>, czyli zewnętrzne wartości, które chcemy użyć w funkcji i chcemy żeby zostały nam podane w momencie wywołania funkcji.

Ogólny schemat pracy z funkcjami:

```
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

Deklaracja funkcji to wyrażenie, które zawiera nazwę funkcji, jej argumenty oraz jej zwracany typ. Deklaracja musi pojawić się w kodzie przed wywołaniem funkcji. W przeciwnym razie kompilator wyświetli komunikat o błędzie. Definicja funkcji to deklaracja wraz z ciałem funkcji.

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

Funkcje typu void nie zwracają żadnej wartości. Nie ma konieczności użycia słowa kluczowego <code>return</code>. Jeśli jednak zostanie użyte, to nie może być podana za nim żadna wartość. W kontekście funkcji typu void <code>return</code> służy jedynie do przerywania funkcji.

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

Domyślna wartość to taka, która zostanie użyta jeśli przy wywołaniu funkcji nie będzie podana wartość dla danego parametru.

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

### Przekazywanie argumentów funkcji przez wartość i referencję

Istnieją dwa sposoby na przekazywanie argumentów do funkcji. Pierwszy to przekazywanie argumentów przez wartość. Jeśli argumentem jest zmienna, to funkcja otrzymuje kopię jej wartości. Wszelkie zmiany na tą wartość w funkcji nie wpływają na oryginalną zmienną. Drugi sposób na przekazywanie argumentów to przekazywanie argumentów przez referencję. W tym przypadku funkcja otrzymuje referencję do oryginalnej zmiennej. Wszelkie zmiany na tą wartość w odbywają się bezpośrednio na oryginalnej zmiennej.

Przykład przekazywania argumentów przez wartość:

```c++
void pomnoz(int a, int b) { a = a * b; }
```

Przykład przekazywania argumentów przez referencję:

```c++
void pomnoz(int &a, int &b) { a = a * b; }
```

Uwaga: przez referencję możemy przekazywać jedynie l-wartości.
