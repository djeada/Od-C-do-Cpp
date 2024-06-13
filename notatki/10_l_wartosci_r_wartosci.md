## L-wartości i R-wartości

W kontekście języka C++, istotne jest rozróżnienie między L-wartościami (ang. l-value) i R-wartościami (ang. r-value). Zrozumienie tego podziału jest kluczowe dla efektywnego zarządzania zasobami i optymalizacji kodu.

### L-wartości

L-wartości (l-value) to wartości, które posiadają **stałe miejsce** w pamięci, co oznacza, że posiadają adres. Możemy myśleć o nich jako o obiektach, które istnieją "na lewo od znaku przypisania" (choć to uproszczenie). Przykłady L-wartości to zmienne, elementy tablicy, wskaźniki oraz referencje.

#### Przykłady L-wartości

```c++
int main() {
  int i = 3;       // i jest L-wartością
  int j = 4;       // j jest L-wartością
  int *pi = &i;    // &i jest L-wartością, pi jest L-wartością
  int &rj = j;     // j i rj są L-wartościami
  int &rrj = rj;   // rj i rrj są L-wartościami
  return 0;
}
```

### R-wartości

R-wartości (r-value) to tymczasowe wartości, które **nie posiadają stałego miejsca** w pamięci. Są to wartości, które zazwyczaj występują po prawej stronie operacji przypisania. Przykłady R-wartości to literały, wyniki wyrażeń oraz tymczasowe wartości zwracane przez funkcje.

#### Przykłady R-wartości

```c++
int main() {
  int i = 3;  // 3 jest R-wartością
  int j = i + 4;  // (i + 4) jest R-wartością
  
  // Następujące linie są niepoprawne:
  // 3 = i;      // Błąd! 3 jest R-wartością i nie może być po lewej stronie przypisania
  // i + 4 = 20; // Błąd! (i + 4) jest R-wartością i nie może być po lewej stronie przypisania
  return 0;
}
```

### L-wartości vs R-wartości

#### L-wartości

L-wartości są odniesieniami do pamięci i mogą być zmieniane. Mają trwałe adresy i mogą być używane po lewej stronie operacji przypisania.

#### R-wartości

R-wartości są tymczasowymi wartościami, które nie mają trwałych adresów pamięci. Nie mogą być używane po lewej stronie operacji przypisania, ponieważ nie mają miejsca w pamięci, do którego można by przypisać wartość.

### R-wartości i L-wartości w kontekście funkcji

#### Przekazywanie argumentów przez wartość

Przekazywanie argumentów przez wartość oznacza, że do funkcji przekazywana jest kopia argumentu.

```c++
void f(int x) { /* ... */ }
int main() {
    int a = 10;
    f(a);  // a jest L-wartością
    f(20); // 20 jest R-wartością
}
```

#### Przekazywanie argumentów przez referencję

Przekazywanie argumentów przez referencję oznacza, że do funkcji przekazywana jest referencja do argumentu.

```c++
void g(int &x) { /* ... */ }
int main() {
    int a = 10;
    g(a);  // a jest L-wartością
    // g(20); // Błąd! 20 jest R-wartością
}
```

#### R-wartościowe referencje (C++11 i nowsze)

R-wartościowe referencje (`&&`) umożliwiają przechwytywanie R-wartości. Są szczególnie przydatne w kontekście semantyki przenoszenia (move semantics), która pozwala na optymalizację kopiowania zasobów.

```c++
void h(int &&x) { /* ... */ }
int main() {
    int a = 10;
    // h(a); // Błąd! a jest L-wartością
    h(20); // 20 jest R-wartością
    h(std::move(a)); // std::move(a) jest R-wartością
}
```

### Semantyka przenoszenia (Move Semantics)

Semantyka przenoszenia pozwala na "przenoszenie" zasobów z jednego obiektu do drugiego zamiast ich kopiowania. Jest to możliwe dzięki r-wartościowym referencjom.

#### Przykład klasy z konstruktorem przenoszącym

```c++
#include <iostream>
#include <vector>

class MoveExample {
public:
    std::vector<int> data;

    // Konstruktor przenoszący
    MoveExample(std::vector<int> &&vec) : data(std::move(vec)) {}

    // Funkcja do wyświetlania zawartości
    void display() {
        for (int i : data) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    MoveExample me(std::move(vec)); // vec jest przenoszone do me

    me.display();
    // vec jest teraz w stanie "moved-from"
    return 0;
}
```
