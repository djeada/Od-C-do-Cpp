
## Zaawansowane wskaźniki

Poza zwykłymi, surowymi wskaźnikami istnieją jeszcze inne, bardziej zaawansowane typy wskaźników.

### Wskaźniki na funkcje

Wskaźniki mogą wskazywać nie tylko na zmienne i obiekty, ale także na funkcje. Dzięki temu możemy na przykład przekazać jedną funkcję jako argument do innej funkcji, co jest przydatne w przypadku, gdy chcemy przekazać do funkcji różne operacje do wykonania na danym argumencie. W przykładzie poniżej zdefiniowano dwie funkcje `zwieksz` i `zmniejsz`, które przyjmują jeden argument typu int i zwracają odpowiednio zwiększoną o jeden lub zmniejszoną o jeden wartość. Funkcja funkcja przyjmuje dwa argumenty, pierwszy z nich to wskaźnik na funkcję, a drugi to liczba, na której ta funkcja ma być wykonana. W mainie funkcje te są przekazywane jako argumenty do `funkcjaWysokopoziomowa`, co pozwala na wykonanie odpowiedniej operacji na liczbie 10.

```c++
#include <iostream>

void funkcjaWysokopoziomowa(void (*f)(int), int a) { f(a); }

void zwieksz(int a) { std::cout << a + 1 << std::endl; }

void zmniejsz(int a) { std::cout << a - 1 << std::endl; }

int main() {
  funkcjaWysokopoziomowa(zwieksz, 10);
  funkcjaWysokopoziomowa(zmniejsz, 10);
  return 0;
}
```

### Wskaźniki do składowych klasy

Możemy wskazywać na składowe klasy. Przykładowo jeśli mamy obiekt `foo` klasy `Foo`, mającą pola `x` i `y`, to możemy wskazać na `foo.x` i `foo.y`. W przykładzie poniżej, klasa `Foo` posiada dwa pola publiczne `x` i `y`, które są inicjalizowane przy tworzeniu obiektu. W `main` tworzymy obiekt `foo` z wartościami 10 i 20 odpowiednio dla pól `x` i `y`. Następnie tworzymy dwa wskaźniki `x` i `y`, które wskazują na pola `foo.x` i `foo.y`. Przez dereferencję tych wskaźników, jesteśmy w stanie zmienić wartości tych pól (`*x = 100` oraz `*y = 200`). Możemy wyświetlić aktualne wartości przy pomocy `std::cout`.

```c++
#include <iostream>

class Foo {
public:
  int x;
  int y;

  Foo(int x, int y) : x(x), y(y) {}
};

int main() {
  Foo foo(10, 20);

  // wskazniki na zwykle pola
  int *x = &foo.x;
  int *y = &foo.y;
  *x = 100;
  *y = 200;
  std::cout << foo.x << std::endl;
  std::cout << foo.y << std::endl;

  return 0;
}
```

### Podsumowanie wskaźników

Jak widzimy, wskaźniki mogą być używane w różnych celach i w różnych kontekstach, od wskazywania na zmienne, przez funkcje, aż po składowe klas. Ważne jest, aby dobrze rozumieć jakiego typu wskaźnik jest potrzebny w danym kontekście, oraz jakie operacje możemy wykonać na danym wskaźniku.

| Kod                                  | Opis                                                           |
| ------------------------------------ | -------------------------------------------------------------- |
| <code>int \*wsk;</code>              | wskaźnik wskazujący na zmienną typu int                        |
| <code>int \*\*wskNaWsk;</code>       | wskaźnik wskazujący na wskaźnik wskazujący na zmienną typu int |
| <code>int (\*wskNaTablice)[];</code> | wskaźnik wskazujący na tablicę zmienną typu intów              |
| <code>int (\*wskNaFunkcje)();</code> | wskaźnik wskazujący na funkcję zwracającą zmienną typu int     |
| <code>int \*tab[];</code>            | tablica wskaźników na zmienną typu int                         |
| <code>int \*fun();</code>            | funkcja zwracająca wskaźnik na zmienną typu int                |


### Sprytne wskaźniki

W C++11 wprowadzono tak zwane sprytne wskaźniki. Wskaźniki te to nakładki na znane nam surowe wskaźniki, poszerzone o dodatkowe funkcjonalności. Przykładowo sprytne wskaźniki w momencie śmierci (destruktor) uwalniają pamięć sterty zarezerwowaną dla wskazywanych przez nie obiektów.

#### unique_ptr

`unique_ptr` to jeden z rodzajów sprytnych wskaźników, który zapewnia, że pamięć zarezerwowana przez wskaźnik zostanie automatycznie zwolniona w momencie, gdy wskaźnik przestanie istnieć (np. wyjdzie poza zakres życia). Dzięki temu, programista nie musi martwić się o ręczne zwalnianie pamięci za pomocą operatora `delete`, co zwiększa bezpieczeństwo kodu.

```c++
std::unique_ptr<int> unikalnyWsk(new int);
*unikalnyWsk = 5;
std::cout << *unikalnyWsk << std::endl;  // wyświetli 5
```

Należy pamiętać, że `unique_ptr` nie jest w pełni bezpieczny. Przykładowo, próba utworzenia dwóch `unique_ptr` i przekazanie do nich tego samego surowego wskaźnika, spowoduje błąd `double free`.

```c++
int *surowyWsk = new int;
std::unique_ptr<int> unikalnyWsk1(surowyWsk);
std::unique_ptr<int> unikalnyWsk2(surowyWsk); // błąd: double free
```

Dlatego też, zamiast ręcznie tworzyć `unique_ptr`, lepiej skorzystać z funkcji `std::make_unique`, która zwraca `unique_ptr` dla podanego typu.

```c++
std::unique_ptr<Foo> unikalnyWsk = std::make_unique<Foo>(1.0, 2.0);
```

Należy również pamiętać, że `unique_ptr` nie jest kopiowalny, tzn. nie możemy przypisać jednego `unique_ptr` do drugiego, ani przekazać go jako argument fo funkcji.

```c++
std::unique_ptr<Foo> unikalnyWsk1(new Foo);
std::unique_ptr<Foo> unikalnyWsk2 = unikalnyWsk1;   // błąd: unique_ptr nie jest kopiowalny
void func(std::unique_ptr<Foo> wsk) {}
std::unique_ptr<Foo> unikalnyWsk3(new Foo);
func(unikalnyWsk3);  // błąd: unique_ptr nie może być przekazany jako argument
```

#### shared_ptr

Innym rodzajem sprytnego wskaźnika jest `shared_ptr`. Podobnie jak `unique_ptr`, `shared_ptr` również zarządza pamięcią i automatycznie ją zwalnia, jednak ma kilka dodatkowych funkcjonalności.

Przede wszystkim, `shared_ptr` pozwala na dzielenie własności obiektu między wieloma wskaźnikami. Dopóki istnieje przynajmniej jeden `shared_ptr` wskazujący na dany obiekt, pamięć zarezerwowana dla tego obiektu nie zostanie zwolniona.

```c++
std::shared_ptr<Foo> wspolnyWsk1(new Foo);
std::shared_ptr<Foo> wspolnyWsk2 = wspolnyWsk1;
```

W przeciwieństwie do `unique_ptr`, `shared_ptr` jest kopiowalny i może być przekazywany jako argument do funkcji.

```c++
void func(std::shared_ptr<Foo> wsk) {}
std::shared_ptr<Foo> wspolnyWsk3(new Foo);
func(wspolnyWsk3); // ok
```
Jednakże, dzielenie własności obiektu między wieloma wskaźnikami może prowadzić do problemów związanych z "dangling pointers" (wskaźnikami wskazującymi na nieistniejący obiekt), dlatego należy być ostrożnym podczas pracy z tymi wskaźnikami.

#### weak_ptr

`weak_ptr` to kolejny rodzaj sprytnego wskaźnika, który pojawił się w C++11. Jest on przeznaczony do pracy z obiektami, na które już wskazuje `shared_ptr`.

`weak_ptr` pozwala na dostęp do obiektu, na który wskazuje `shared_ptr`, bez jednoczesnego zwiększania licznika właścicieli (ang. reference count) tego obiektu. Dzięki temu, unikamy problemu "dangling pointers", który może wystąpić przy pracy z `shared_ptr`.

```c++
std::shared_ptr<Foo> wspolnyWsk(new Foo);
std::weak_ptr<Foo> slabyWsk = wspolnyWsk;
```

Aby skorzystać z obiektu na który wskazuje `weak_ptr`, należy przedtem przekształcić go w `shared_ptr`.

```c++
std::shared_ptr<Foo> wspolnyWsk = slabyWsk.lock();
if(wspolnyWsk)
{
    // mamy dostęp do obiektu
}
else
{
    // obiekt nie istnieje już
}
```

Warto zauważyć, że `weak_ptr` nie zwiększa licznika właścicieli obiektu, dlatego nie przedłuża życia obiektu i nie uniemożliwia jego zwolnienia przez `shared_ptr` w przypadku, gdy nie ma już żadnego innego `shared_ptr` wskazującego na ten obiekt.

`weak_ptr` jest również niekopiowalny i nie może być przekazywany jako argument do funkcji.

W przeciwieństwie do `unique_ptr` i `shared_ptr`, `weak_ptr` nie zarządza pamięcią i nie jest odpowiedzialny za jej zwolnienie. Jest to narzędzie pomocnicze, które pozwala na bezpieczne korzystanie z obiektów, na które już istnieje `shared_ptr` bez ryzyka utworzenia "dangling pointers".
