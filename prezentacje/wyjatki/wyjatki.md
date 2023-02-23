## Wyjątki w języku C++

Wyjątki są mechanizmem obsługi błędów w języku C++. Gdy występuje nieprzewidziane zachowanie w trakcie wykonywania programu, taki jak błąd w alokacji pamięci, dzielenie przez zero, czy błąd wejścia/wyjścia, może zostać rzucony wyjątek. Rzucenie wyjątku jest sposobem powiadomienia programu o wystąpieniu błędu i przerwaniu jego normalnego działania.
   
Przykłady funkcji biblioteki standardowej, które wyrzucają wyjątki, gdy są użyte nieprawidłowo:

* `std::vector::at()` - funkcja ta zwraca wartość elementu znajdującego się na określonej pozycji w wektorze. Jeśli pozycja nie jest poprawna, funkcja rzuca wyjątek std::out_of_range.

```cpp
std::vector<int> vec = {1, 2, 3};
try {
    int value = vec.at(5);
} catch (std::out_of_range& e) {
    std::cout << "Błąd: " << e.what() << std::endl;
}
```

* `std::stoi()` - funkcja ta konwertuje ciąg znaków na liczbę całkowitą. Jeśli ciąg nie reprezentuje liczby całkowitej, funkcja rzuca wyjątek std::invalid_argument.

```cpp
std::string str = "ABC";
try {
    int value = std::stoi(str);
} catch (std::invalid_argument& e) {
    std::cout << "Błąd: " << e.what() << std::endl;
}
```

* `std::find()` - funkcja ta zwraca iterator do pierwszego elementu w zadanym zakresie, który ma wartość równą określonemu elementowi. Jeśli element nie znajduje się w zakresie, funkcja zwraca iterator do końca zakresu. Jeśli zakres jest pusty, funkcja rzuca wyjątek std::out_of_range.

```cpp
std::vector<int> vec = {1, 2, 3};
auto it = std::find(vec.begin(), vec.end(), 4);
if (it == vec.end()) {
    std::cout << "Nie znaleziono elementu\n";
}
```

## Historia

Wcześniej, zanim wprowadzono wyjątki, programiści korzystali między innymi z kodów błędów, które zwracane były przez funkcje. Przykładowo, funkcja może zwracać wartość ujemną, gdy wystąpił błąd, a programista musiał ręcznie obsłużyć ten błąd. Wprowadzenie wyjątków ułatwiło proces obsługi błędów i zapewniło bardziej czytelny kod.

Oto kilka przykładów jak obsługa błędów wyglądała w C:

1. Kodowanie błędów jako wartości zwracanej przez funkcję. Funkcja mogła zwrócić specjalną wartość oznaczającą, że wystąpił błąd. Na przykład, funkcja fopen() zwraca wskaźnik na plik, a jeśli wystąpił błąd, to zwraca wartość NULL. Programista musiał ręcznie sprawdzać zwróconą wartość i obsługiwać błąd.

```c
FILE* file = fopen("plik.txt", "r");
if (file == NULL) {
    perror("Nie udało się otworzyć pliku");
    exit(EXIT_FAILURE);
}
```

2. Zastosowanie zmiennych globalnych do przechowywania informacji o błędzie. W takim podejściu funkcja zwraca wartość oznaczającą sukces lub porażkę, a informacje o błędzie są przechowywane w zmiennej globalnej. Programista musiał ręcznie sprawdzać wartość zwracaną przez funkcję i odwoływać się do zmiennej globalnej, aby uzyskać informacje o błędzie.

```c
int errno;
double result = sqrt(-1.0);
if (result == -1.0 && errno == EDOM) {
    perror("Nieprawidłowy argument");
}
```

3. Używanie makr preprocesora do obsługi błędów. W takim podejściu programista definiował makra, które były wywoływane w momencie wystąpienia błędu. Na przykład, funkcja assert() definiowana jest jako makro, które sprawdza, czy warunek jest spełniony, a jeśli nie, to wywołuje funkcję abort().

```c
#include <assert.h>
int divide(int a, int b) {
    assert(b != 0);
    return a / b;
}
```

## Mechanizm wyjątków

Mechanizm wyjątków składa się z trzech części: bloku try, bloku catch i instrukcji throw.

* Blok try to blok kodu, w którym występują instrukcje, które mogą rzucić wyjątek. Jeśli w bloku try wystąpi wyjątek, wykonanie programu zostanie przerwane i kontrola zostanie przekazana do bloku catch.

* Blok catch to blok kodu, który obsługuje wyjątek. Może on przyjąć argument określający typ rzucanego wyjątku. Jeśli typ wyjątku zgadza się z typem argumentu, blok catch zostanie wykonany.

* Instrukcja throw to instrukcja, która rzuca wyjątek. Może ona przyjąć argument określający typ rzucanego wyjątku.

Poniższy kod ilustruje użycie bloków try i catch:

```cpp
try {
  // kod, który może rzucić wyjątek
} catch (typ_wyjątku argument) {
  // kod obsługi wyjątku
}
```

Jeśli w bloku try zostanie rzucony wyjątek, zostanie wykonany blok catch odpowiadający typowi wyjątku. W przeciwnym razie, program będzie kontynuowany poza blokiem try-catch.

Throw może, wyrzucić wyjątek dowolnego typu, nawet zwykłą liczbę.

```cpp
#include <iostream>

int main() {
    try {
        int x = 10;
        int y = 0;
        if (y == 0) {
            throw 1; // throwing an integer as an exception
        }
        int z = x / y;
        std::cout << z << std::endl;
    }
    catch (int e) {
        std::cout << "Caught exception: " << e << std::endl;
    }
    return 0;
}
```

## Defniowanie wyjątków

Standardowe wyjątki:

* `std::bad_alloc` - jest to wyjątek rzucony przez operację alokacji pamięci, gdy nie ma wystarczającej ilości wolnej pamięci.
* `std::logic_error` - jest to rodzaj wyjątku, który jest zwykle związany z błędami programistycznymi, takimi jak błędna logika lub błędne użycie funkcji bibliotecznej.
* `std::runtime_error` - jest to rodzaj wyjątku, który jest zwykle związany z błędami wynikającymi z sytuacji działania programu, takich jak błąd wewnętrzny lub nieznana sytuacja.
    
Możemy definiować własne wyjątki, które pozwolą nam lepiej kontrolować błędy i wyjątkowe sytuacje w naszych programach. Definiowanie własnych wyjątków polega na stworzeniu klasy dziedziczącej po klasie `std::exception`.

Przykładowa klasa wyjątku może wyglądać następująco:

```cpp
class WlasnyWyjatek : public std::exception {
public:
    WlasnyWyjatek(const char* wiadomosc) : wiadomosc(wiadomosc) {}
    const char* what() const noexcept override {
        return wiadomosc.c_str();
    }
private:
    std::string wiadomosc;
};
```

Konstruktor klasy `WlasnyWyjatek` przyjmuje jako argument wiadomość, która będzie przekazywana w przypadku rzucenia wyjątku. Metoda `what()` zwraca tę wiadomość jako `const char*`.
