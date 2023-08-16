## L-wartości i R-wartości

W kontekście języka C++, istotne jest rozróżnienie między L-wartościami (ang. l-value) i R-wartościami (ang. r-value).

### L-wartości

L-wartości (l-value) to wartości, które posiadają **stałe miejsce** w pamięci, co oznacza, że posiadają adres. Możemy myśleć o nich jako o obiektach, które istnieją "na lewo od znaku przypisania" (choć to uproszczenie). Przykłady L-wartości to zmienne, elementy tablicy, wskaźniki oraz referencje.

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

Uwaga: Współczesne kompilatory C++ wprowadzają koncepcję przenoszenia R-wartości, co pozwala na efektywne przenoszenie zasobów bez konieczności kopiowania, co jest szczególnie przydatne w kontekście dynamicznie alokowanych zasobów, jak np. `std::vector`.

Jest pewne uproszczenie w stwierdzeniu, że wszystkie L-wartości są R-wartościami. Dokładniej rzecz biorąc, możemy uzyskać R-wartość z L-wartości (na przykład poprzez konwersję na tymczasowy obiekt), ale samo stwierdzenie może prowadzić do pewnych nieporozumień w bardziej zaawansowanych kontekstach.
