## L-wartości i r-wartości

W języku C++, istnieją dwa rodzaje wartości: L-wartości (ang. l-value) i R-wartości (ang. r-value).

L-wartości to wartości, które posiadają adres w pamięci i mogą być przypisane do zmiennej. Przykłady L-wartości to zmienne, elementy tablicy, wskaźniki, etc.

```c++
int main() {
  int i = 3;  // OK
  int j = 4;  // OK
  int *pi = &i;  // OK
  int &rj = j;  // OK
  int &rrj = rj; // OK
  return 0;
}
```

Natomiast R-wartości to wartości, które nie posiadają adresu w pamięci i nie mogą być przypisane do zmiennej. Przykłady R-wartości to liczby nie przechowywane w zmiennych, wyrażenia, wyniki funkcji zwracających wartość, itd.

```c++
int main() {
  int i = 3;  // OK
  3 = i;      // Zle - 3 jest stała
  i + 4 = 20; // Zle - (i + 4) jest wyrazeniem
  return 0;
}
```

Należy pamiętać, że wszystkie L-wartości są R-wartościami, ale nie wszystkie R-wartości są L-wartościami.
