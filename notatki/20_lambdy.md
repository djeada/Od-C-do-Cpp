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
- `[a, &b]` - zmienna `a` jest przechwytywana przez wartość, a `b` przez referencję.

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

### Rozszerzone Zastosowania

#### Przechwytywanie przez wartość i referencję

Lambdy mogą przechwytywać zmienne na różne sposoby, co daje dużą elastyczność. Przykłady:

```c++
int x = 10;
int y = 20;

auto lambda1 = [=]() { return x + y; };  // Przechwytuje przez wartość
auto lambda2 = [&]() { x++; y++; };  // Przechwytuje przez referencję
```

#### Lambda jako funkcja zwracająca

Lambda może być również używana jako funkcja zwracająca z innej funkcji:

```c++
auto get_multiplier(int mnoznik) {
    return [mnoznik](int x) { return x * mnoznik; };
}

auto multiply_by_3 = get_multiplier(3);
std::cout << multiply_by_3(10);  // Wyświetli 30
```

#### Lambdy jako obiekty funkcji

Lambdy mogą być przechowywane jako std::function, co pozwala na ich bardziej elastyczne użycie:

```c++
std::function<int(int, int)> dodaj = [](int a, int b) { return a + b; };
std::cout << dodaj(3, 4);  // Wyświetli 7
```

### Klauzula mutable

Domyślnie, lambdy przechwytujące zmienne przez wartość nie mogą zmieniać tych zmiennych wewnątrz swojego ciała. Klauzula `mutable` zmienia to zachowanie:

```c++
int counter = 0;
auto increment = [counter]() mutable { counter++; return counter; };

std::cout << increment();  // Wyświetli 1
std::cout << increment();  // Wyświetli 2
```

### Użycie lambd z algorytmami STL

Lambdy są często używane z algorytmami z biblioteki standardowej. Oto kilka przykładów:

#### std::for_each

```c++
std::vector<int> liczby = {1, 2, 3, 4, 5};
std::for_each(liczby.begin(), liczby.end(), [](int &n) { n *= 2; });
// liczby teraz zawiera {2, 4, 6, 8, 10}
```

#### std::find_if

```c++
std::vector<int> liczby = {1, 2, 3, 4, 5};
auto it = std::find_if(liczby.begin(), liczby.end(), [](int n) { return n > 3; });

if (it != liczby.end()) {
    std::cout << "Znaleziono liczbę większą od 3: " << *it;  // Wyświetli 4
}
```

### Praktyczne zastosowania lambd

#### Obsługa zdarzeń

Lambdy są często używane w programowaniu GUI do obsługi zdarzeń:

```c++
button.onClick([]() {
    std::cout << "Button clicked!";
});
```

#### Asynchroniczność

Lambdy mogą być używane z bibliotekami asynchronicznymi do definiowania zadań:

```c++
std::async(std::launch::async, []() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Task completed after 1 second";
});
```
