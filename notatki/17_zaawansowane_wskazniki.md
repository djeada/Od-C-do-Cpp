
## Zaawansowane wskaźniki

Poza zwykłymi, surowymi wskaźnikami istnieją jeszcze inne, bardziej zaawansowane typy wskaźników.

### Wskaźniki na funkcje

Wskaźniki mogą wskazywać nie tylko na zmienne i obiekty, ale także na funkcje. Dzięki temu możemy na przykład przekazać jedną funkcję jako argument do innej funkcji.

```c++
#include <iostream>

void funkcja(void (*f)(int), int a) { f(a); }

void zwieksz(int a) { std::cout << a + 1 << std::endl; }

void zmniejsz(int a) { std::cout << a - 1 << std::endl; }

int main() {
  funkcja(zwieksz, 10);
  funkcja(zmniejsz, 10);
  return 0;
}
```

### Wskaźniki do składowych klasy

Możemy wskazywać na składowe klasy. Przykładowo jeśli mamy obiekt <code>foo</code> klasy <code>Foo</code>, mającą pola <code>x</code> i <code>y</code> to możemy wskazać na <code>foo.x</code> i <code>foo.y</code>.

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

Dzięki niemu, mamy pewność że zarezerwowana pamięć zostanie zwolniona gdy program wyjdzie poza zakres życia wskaźnika. Programista nie ma możliwości popełniania błędów, wynikających z nieużycia operatora delete. Pamięć zwalniana jest automatycznie.

Nie oznacza to jednak, że nie ma żadnej możliwości na popełnienie błędu przy pracy z unique_ptr. Jeśli utworzymy dwa obiekty unique_ptr poprzez przekazanie do konstruktora tego samego surowego wskaźnika, to nasz program zostanie zakończony z komunikatem o double free.

    int *surowyWsk = new int;

    std::unique_ptr<int> unikalnyWsk1(surowyWsk);
    std::unique_ptr<int> unikalnyWsk2(surowyWsk);

Nawet jeśli nie popełnimy tak fatalnego, ale dość oczywistego błędu, to wciąż istnieją inne błędy na które musimy uważać. Po utworzeniu obiektu unique_ptr poprzez przekazanie do konstruktora surowego wskaźnika, nigdy nie powinniśmy zwalniać pamięci poprzez operator delete.

Bezpieczniejszą opcją tworzenia obiektu unique_ptr jest std::make_unique. Jest to funkcja zwracająca unique_ptr dla podanego typu. Załóżmy, że mamy klasę <code>Foo</code> z dwoma polami typu double <code>x</code> i <code>y</code>.

	std::unique_ptr<Foo> unikalnyWsk = std::make_unique<Foo>(1.0, 2.0);

Dlaczego te wskaźniki są nazywane unikalnymi? Otóż, nie mamy możliwości inicjalizacji obiektów uniqe_ptr poprzez przypisanie im wartości innego obiektu tego samego typu. Tzn. obiekty uniqe_ptr nie są kopiowalne.

	std::unique_ptr<Foo> unikalnyWsk1(new Foo);       // Ok
	std::unique_ptr<Foo> unikalnyWsk2 = unikalnyWsk1; // Error

Mamy za to możliwość przenoszenia jednego obiektu unique_ptr do drugiego.

	std::unique_ptr<Foo> unikalnyWsk1(new Foo);                  
	std::unique_ptr<Foo> unikalnyWsk2 = std::move(unikalnyWsk1);

#### shared_ptr

Jeśli przyrównać uniqe_ptr do wozu pancernego, to shared_ptr jest czołgiem. Działa tak samo jak uniqe_ptr, ale daje nam więcej opcji. Możemy zarówno przenosić, jak i kopiować obiekty shared_ptr. Mamy też możliwość sprawdzenia ile aktualnie obiektów shared_ptr wskazuje na dany obiekt.

	std::shared_ptr<Foo> dzielonyWsk1(new Foo);       // Ok
	std::shared_ptr<Foo> dzielonyWsk2 = dzielonyWsk1; // Ok

Aby sprawdzić ile obiektów wskazuje na dany obiekt, możemy użyć metody <code>use_count()</code>.

	std::cout << dzielonyWsk.use_count() << std::endl;

#### weak_ptr

Innym typem sprytnych wskaźników jest weak_ptr. Jest to wskaźnik, który nie ma praw własności do żadnego obiektu. Zamiast tego możemy przypisać mu wartość sprytnego wskaźnika innego typu i za jego pomocą możemy sprawdzić, czy dane na które wskazuje inny wskaźnik dalej istnieją.

```c++
#include <iostream>
#include <memory>

void czy_istnieje(std::weak_ptr<int> wsk) {
  if (auto tmp = wsk.lock())
    std::cout << "Obiekt istnieje: " << *tmp << std::endl;
  else
    std::cout << "Obiekt nie istnieje" << std::endl;
}

int main() {
  std::shared_ptr<int> dzielonyWsk(new int(42));

  std::weak_ptr<int> slabyWsk = dzielonyWsk;
  czy_istnieje(slabyWsk);
  dzielonyWsk.reset();
  czy_istnieje(slabyWsk);

  return 0;
}
```
