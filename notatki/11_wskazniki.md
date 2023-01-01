## Wskaźniki

Wskaźnik to zmienna, która przechowuje adres innej zmiennej. Dodatkowo przy pomocy wskaźników mamy możliwość modyfikowania zmiennych, których adresy przechowują wskaźniki.

<code>Typ_zmiennej_której_adres_przechowuje_wskaźnik * nazwa_wskaźnika;</code>

```c++
#include <string>

int main() {
  // Deklaracja
  int *p1;
  double *p2;
  string *p3;

  int x = 4;
  double y = 3.5;
  std::string s = "napis";

  // Inicjalizacja
  // p1 = &y; // Złe. Niezgodne typy.
  p1 = &x;    // OK. Typy się zgadzają
  p2 = &y;
  p3 = &s;
  
  return 0;
}
```

### Dereferencja

Wyłuskanie wartości znajdującej się w zmiennej, na którą wskazuje nasz wskaźnik.
Używane nie tylko do odczytu, ale również zmiany wartości tej zmiennej.

<code>*nazwa wskaźnika</code>

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
  std::cout << "Wartość zmiennej y: " * p2 << std::endl;
  std::cout << "Wartość zmiennej s: " * p3 << std::endl;

  *p1 = 7;      // zmiana wartości zmiennej x
  *p2 = 8.123;  // zmiana wartości zmiennej y
  *p3 = "inny"; // zmiana wartości zmiennej s

  std::cout << "Wartość zmiennej x: " << *p1 << std::endl;
  std::cout << "Wartość zmiennej y: " * p2 << std::endl;
  std::cout << "Wartość zmiennej s: " * p3 << std::endl;

  return 0;
}
```

### Wskaźnik na wskaźnik

Operator \* pozwala również tworzyć wskaźniki przechowujące adresy innych wskaźników.

```c++
int main() {
  int i = 20;
  int *j = &i;
  int **k = &j;
  int ***l = &k;

  return 0;
}
```

### Wskaźnik na NULL

<code>NULL</code> to specjalna wartość wskaźnika symbolizująca wskazywanie na nieistniejący obiekt. Dzięki tej wartości możemy sygnalizować koniec listy połączonej lub poinformować o niemożliwości przydziału pamięci, lub otwarcia pliku (współcześnie preferuje się wyjątki).

W C, w zależności od implementacji <code>NULL</code> definiowany jest jako <code>0</code> lub <code>((void*)0)</code>. W obu przypadkach używany jest dokładnie do tego samego.
Z uwagi na to, że <code>NULL</code> to po prostu zero, możemy w taki sposób sprawdzić, czy wskaźnik <code>wsk</code> nie jest wskaźnikiem na <code>NULL</code>:

```c++
  if (wsk != 0) {
  }
```

Na pierwszy rzut oka nie widać jednak, czy <code>wsk</code> jest wskaźnikiem, czy zwykłą liczbą. Z tego powodu lepiej jest użyć następującej konstrukcji:

```c++
  if (wsk != NULL) {
  }
```

C++ jest (prawie) nadzbiorem C, ale żyje własnym życiem i ewoluuje w innym kierunku. <code>NULL</code> dalej istnieje w C++, ale oprócz niego mamy jeszcze jego młodszego brata <code>nullptr</code>. Pojawia się więc pytanie, po co wymyślono coś nowego, jeśli służy do tego samego co coś, co już istniało wcześniej? Otóż w C++ możemy przeciążać funkcje, tzn. definiować kilka funkcji z tą samą nazwą, ale różnymi typami parametrów.

```c++
void foo(void *wsk);
void foo(int liczba);
```

Która funkcja zostanie użyta, gdy wywołamy <code>foo(NULL)</code>? <code>NULL</code> jest zwykłym 0, więc zostanie użyta druga funkcja. Z tego powodu wprowadzono <code>nullptr</code>, który nigdy nie będzie zinterpretowany jako liczba.

Tak więc jeśli piszesz kod w C++, to używaj <code>nullptr</code>.

### Stałe wskaźniki

Podobnie jak możemy deklarować zwykłe stałe, tak samo możemy mieć stałe wskaźniki - jednak są ich dwa rodzaje. Wskaźniki na stałą wartość:

```c++
  const int *a;
  int const *a; // równoważne do poprzedniego przykładu
```

oraz stałe wskaźniki:

```c++
  int *const b;
```

Słowo const przed typem działa jak w przypadku zwykłych stałych, tzn. nie możemy zmienić wartości wskazywanej przy pomocy wskaźnika.

W drugim przypadku słowo const jest tuż za gwiazdką oznaczającą typ wskaźnikowy, co skutkuje stworzeniem stałego wskaźnika, czyli takiego, którego nie można przestawić na inny adres.

```c++
int main() {
  int zmienna = 10;
  const int stala = 15;
  int *const wskaznik_na_stala = &stala;
  int *const wskaznik_na_zmienna = &zmienna;
  const int *const wskaznik_na_stala_wskaznik = &wskaznik_na_stala;
  const int *const wskaznik_na_zmienna_wskaznik = &wskaznik_na_zmienna;

  return 0;
}
```
