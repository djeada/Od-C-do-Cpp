## Lambdy

Jednym z najbardziej potężnych narzędzi wprowadzonych w standardzie C++11, są funkcje lambda (inaczej anonimowe). Pozwalają one na tworzenie niewielkich fragmentów funkcji w miejscu, gdzie są używane, bez konieczności deklarowania ich wcześniej w kodzie.

### Składnia

Ogólna postać lambdy jest następująca:

```c++
[domknięcie](parametry) -> typ_zwracany { blok kodu }
```

W praktyce często `-> typ_zwracany` jest pomijany, gdyż kompilator jest w stanie wydedukować zwracany typ.

### Domknięcie

To, co sprawia, że lambdy w C++ są wyjątkowe, to zdolność do "uchwycenia" zmiennych z otaczającego je zakresu:

- `[]` - nic nie jest przechwytywane.
- `[=]` - wszystkie dostępne zmienne są przechwytywane przez wartość.
- `[&]` - wszystkie dostępne zmienne są przechwytywane przez referencję.
- `[a, &b]` - zmienna a jest przechwytywana przez wartość, a b przez referencję.

### Przykłady

Prosta lambda sumująca dwie wartości:

```c++
auto suma = [](int a, int b) -> int { return a + b; }; 
std::cout << suma(3, 4);  // Wyświetli 7
```

Dzięki automatycznemu wyznaczaniu typu przez kompilator możemy tworzyć lambdy o skomplikowanych typach zwracanych:

```c++
auto zlozona = [](int x) -> std::pair<int, int> { return {x, x*x}; };
```

Lambda z domknięciem:

```c++
int mnoznik = 2;
auto pomnoz = [mnoznik](int wartosc) { return wartosc * mnoznik; };
std::cout << pomnoz(5);  // Wyświetli 10
```

Domyślnie, jeśli przechwytujemy zmienną przez wartość, nie możemy jej zmienić wewnątrz lambdy. Ale możemy to zmienić, używając klauzuli `mutable`:

```c++
int y = 5;
auto zwieksz = [y]() mutable { y += 1; return y; };
```

Jednym z najczęstszych zastosowań lambd jest ich użycie jako argumentów dla funkcji z biblioteki standardowej, takich jak `std::sort` czy `std::for_each`. Przykładowo, sortowanie wektora w odwrotnej kolejności:

```c++
std::vector<int> liczby = {3, 1, 4, 1, 5, 9, 2, 6};
std::sort(liczby.begin(), liczby.end(), [](int a, int b) { return a > b; });
```
