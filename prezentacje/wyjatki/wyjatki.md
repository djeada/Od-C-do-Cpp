## Wyjątki

Wyjątki to mechanizm w języku C++, który pozwala programistom obsługiwać sytuacje wyjątkowe lub błędy w czasie wykonywania programu. Gdy wystąpi błąd lub nieprzewidziana sytuacja, można "rzucić" wyjątek, który może być następnie "przechwycony" i odpowiednio obsłużony.

Oto kilka typowych funkcji biblioteki standardowej C++, które mogą rzucać wyjątki podczas nieprawidłowego użycia:

### 1. std::vector::at()
Ta funkcja próbuje uzyskać dostęp do elementu wektora na określonej pozycji. Gdy indeks jest poza zakresem, funkcja rzuca wyjątek `std::out_of_range`.

```cpp
std::vector<int> vec = {1, 2, 3};
try {
    int value = vec.at(5);  // Nieistniejący indeks
} catch (std::out_of_range& e) {
    std::cout << "Błąd: " << e.what() << std::endl;
}
```

### 2. std::stoi()

Próbuje konwertować ciąg znaków na liczbę całkowitą. Jeśli operacja konwersji nie powiedzie się, funkcja rzuca wyjątek std::invalid_argument.

```cpp
std::string str = "ABC";  // Ciąg, który nie jest liczbą
try {
    int value = std::stoi(str);
} catch (std::invalid_argument& e) {
    std::cout << "Błąd: " << e.what() << std::endl;
}
```

### 3. std::find()

Choć ta funkcja nie rzuca wyjątku std::out_of_range w przypadku pustego zakresu (jak sugerowano wcześniej), warto wiedzieć, jak działa. Zwraca ona iterator do pierwszego wystąpienia danego elementu. Jeśli elementu nie ma w kolekcji, zwraca iterator "za ostatnim" elementem.

```cpp
std::vector<int> vec = {1, 2, 3};
auto it = std::find(vec.begin(), vec.end(), 4);  // 4 nie istnieje w vec
if (it == vec.end()) {
    std::cout << "Nie znaleziono elementu\n";
}
```

Przy pracy z wyjątkami ważne jest, aby być świadomym, które funkcje mogą je rzucać, a także pamiętać o odpowiednim ich przechwytywaniu, aby zapewnić bezpieczne i przewidywalne działanie programu.

## Historia obsługi błędów

Przed wprowadzeniem mechanizmu wyjątków do języków programowania, obsługa błędów była realizowana za pomocą różnych technik. W języku C, który nie obsługuje wyjątków w sposób wbudowany, korzystano głównie z poniższych podejść:

### 1. Kodowanie błędów jako wartości zwracanej przez funkcję

Funkcje zwracały specyficzne wartości, które oznaczały błędy. Na przykład, jeśli operacja nie powiodła się, funkcja mogła zwrócić wartość ujemną lub specjalny wskaźnik, tak jak to ma miejsce w przypadku funkcji `fopen()`. W odpowiedzi na taką wartość, programista musiał napisać odpowiedni kod obsługi błędu.

```c
FILE* file = fopen("plik.txt", "r");
if (file == NULL) {
    perror("Nie udało się otworzyć pliku");
    exit(EXIT_FAILURE);
}
```

### 2. Zmienne globalne przechowujące informacje o błędzie

W niektórych sytuacjach funkcje zwracały wartość sugerującą sukces lub porażkę operacji, ale dokładne informacje o błędzie były przechowywane w zmiennej globalnej. Na przykład, errno to globalna zmienna używana przez wiele funkcji w C do komunikowania informacji o błędzie.

```c
extern int errno;
double result = sqrt(-1.0);
if (result == -1.0 && errno == EDOM) {
    perror("Nieprawidłowy argument");
}
```

### 3. Makra preprocesora do obsługi błędów

Niektóre funkcje, takie jak `assert()`, zostały zdefiniowane jako makra, które sprawdzały pewne warunki w czasie wykonywania programu. Jeśli warunek nie był spełniony, program był przerywany z odpowiednim komunikatem błędu.

```c
#include <assert.h>
int divide(int a, int b) {
    assert(b != 0);  // Program zostanie przerwany, jeśli b będzie równa 0
    return a / b;
}
```

Choć te metody były skuteczne, miały swoje ograniczenia i często prowadziły do skomplikowanego kodu. Wprowadzenie mechanizmu wyjątków, początkowo w językach takich jak C++, uczyniło obsługę błędów bardziej przejrzystą i elastyczną, co pozwoliło na tworzenie bardziej niezawodnych i łatwiejszych do utrzymania aplikacji.

## Mechanizm wyjątków w C++

Mechanizm wyjątków w C++ pozwala na obsługę nieprzewidzianych sytuacji (błędów) w programie. Składa się on z trzech głównych elementów: `try`, `catch` oraz `throw`.

### Blok `try`

To sekcja kodu, w której umieszczane są instrukcje mogące potencjalnie rzucić wyjątek. Jeśli w bloku `try` wystąpi wyjątek, normalny przebieg wykonywania programu zostanie przerwany, a kontrola zostanie przekazana do odpowiadającego mu bloku `catch`.

### Blok `catch`

Bloki `catch` służą do obsługi wyjątków rzuconych w bloku `try`. Każdy blok `catch` jest zaprojektowany do obsługi konkretnego typu wyjątku, który jest określany w jego definicji. W przypadku wystąpienia wyjątku w bloku `try`, program szuka odpowiedniego bloku `catch` (tj. pasującego do typu rzuconego wyjątku) i wykonuje jego instrukcje.

### Instrukcja `throw`

Instrukcja `throw` jest używana do rzucania wyjątków. Można rzucać wyjątki dowolnego typu: od wbudowanych typów danych, poprzez obiekty klasy, aż po wskaźniki.

### Przykład użycia

```cpp
#include <iostream>

int main() {
    try {
        int x = 10;
        int y = 0;
        if (y == 0) {
            throw "Division by zero!"; // rzucenie wyjątku typu const char*
        }
        int z = x / y;
        std::cout << z << std::endl;
    }
    catch (const char* errorMsg) {
        std::cout << "Caught exception: " << errorMsg << std::endl;
    }
    return 0;
}
```

W powyższym kodzie, jeśli y jest równa 0, program rzuca wyjątek typu `const char*`. Dzięki temu, zamiast kontynuować obliczenia, program przekazuje kontrolę do bloku catch, który obsługuje ten konkretny typ wyjątku.

Korzystanie z wyjątków w C++ znacząco ułatwia zarządzanie błędami w porównaniu z tradycyjnymi metodami, takimi jak zwracanie kodów błędów czy użycie globalnych zmiennych.

## Definiowanie własnych wyjątków w C++

C++ oferuje wiele standardowych wyjątków, które są często używane w praktyce. Jednakże w wielu przypadkach przydatne jest definiowanie własnych wyjątków, które lepiej opisują konkretną sytuację błędu w naszym programie.

### Standardowe wyjątki:

* `std::bad_alloc` - ten wyjątek jest rzucony, gdy operacja alokacji pamięci nie powiedzie się z powodu braku dostępnej pamięci.
* `std::logic_error` - reprezentuje błędy wynikające z błędnej logiki programu, takie jak błędne użycie funkcji bibliotecznej czy próba dostępu poza zakresem tablicy.
* `std::runtime_error` - dotyczy błędów pojawiających się w trakcie działania programu, które nie są bezpośrednio związane z błędami logiki, takich jak niepowodzenie operacji wejścia/wyjścia.

### Tworzenie własnych wyjątków:

Własne wyjątki w C++ tworzy się przez dziedziczenie po jednym z istniejących wyjątków (zwykle po `std::exception` lub jednym z jego pochodnych). Takie podejście pozwala na korzystanie z istniejącej infrastruktury wyjątków, jednocześnie dodając specyfikę związaną z konkretnym błędem.

```cpp
#include <exception>
#include <string>

class WlasnyWyjatek : public std::exception {
public:
    WlasnyWyjatek(const std::string& wiadomosc) : wiadomosc(wiadomosc) {}

    const char* what() const noexcept override {
        return wiadomosc.c_str();
    }

private:
    std::string wiadomosc;
};
```

W powyższym kodzie stworzyliśmy wyjątek WlasnyWyjatek, który przechowuje wiadomość opisującą błąd. Można go następnie rzucić i obsłużyć w programie tak samo, jak standardowe wyjątki:

```cpp
try {
    throw WlasnyWyjatek("To jest mój własny wyjątek!");
} catch (const WlasnyWyjatek& e) {
    std::cout << e.what() << std::endl;
}
```

Dzięki definiowaniu własnych wyjątków, możemy lepiej opisać i obsłużyć różne błędne sytuacje, które mogą wystąpić w naszym programie.
