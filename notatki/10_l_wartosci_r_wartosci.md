## L-wartości i r-wartości

Niektóre wartości w C++ istnieją jedynie w obrębie jednego wyrażenia i nie można ich adresować. Takie wartości zwane są r-wartościami (bo mogą występować po prawej stronie znaku =). Ich nadzbiorem są l-wartości. Wszystkie l-wartości są r-wartościami, ale nie wszystkie r-wartości są l-wartościami.

```c++
int main() {
  int i = 3;  // OK
  3 = i;      // Złe
  i + 4 = 20; // Złe

  return 0;
}
```
