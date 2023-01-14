## Operacje bitowe

Operacje bitowe pozwalają na bezpośredni dostęp i modyfikację poszczególnych bitów w liczbie. W językach C i C++ dostępne są następujące operacje bitowe:

* `& (AND)` - operacja AND pozwala na uzyskanie wartości 1 na danym bitach tylko wtedy, gdy obie liczby mają na tych bitach wartość 1. Przykład: `5 (0101) & 3 (0011) = 1 (0001)`
* `| (OR)` - operacja OR pozwala na uzyskanie wartości 1 na danym bitach wtedy, gdy co najmniej jedna z liczb ma na tych bitach wartość 1. Przykład: `5 (0101) | 3 (0011) = 7 (0111)`
* `^ (XOR)` - operacja XOR pozwala na uzyskanie wartości 1 na danym bitach tylko wtedy, gdy liczby mają na tych bitach różne wartości. Przykład: `5 (0101) ^ 3 (0011) = 6 (0110)`
* `~ (NOT)` - operacja NOT pozwala na zmianę wartości bitów z 0 na 1 i odwrotnie. Przykład: ~5 (0101) = -6 (1010)
* `<< (left shift)` - operacja left shift pozwala na przesunięcie wszystkich bitów w liczbie o określoną liczbę pozycji w lewo. Przykład: `5 (0101) << 2 = 20 (010100)`
* `>> (right shift)` - operacja right shift pozwala na przesunięcie wszystkich bitów w liczbie o określoną liczbę pozycji w prawo. Przykład: `5 (0101) >> 2 = 1 (0001)`

Należy pamiętać, że operacje bitowe działają tylko na liczbach całkowitych i operacje te są niskopoziomowe, w związku z tym nie są tak często stosowane jak operacje arytmetyczne czy logiczne.

### Bramka NOT

Zamienia jedynki na zera i na odwrót. Operator `~`.

<table style="width:100%">
  <tr>
    <th>Wejście</th>
    <th>Wyjście</th>
  </tr>
  <tr>
    <td>0</td>
    <td>1</td>
</tr>
  <tr>
    <td>1</td>
    <td>0</td>
  </tr>
</table>

```c++
#include <bitset>
#include <iostream>

int main() {
  bitset<8> x(5);
  std::cout << x << std::endl;  // 00000101
  std::cout << ~x << std::endl; // 11111010

  return 0;
}
```

### Bramka OR

Jedynka gdy co najmniej jeden z bitów to jedynka, w przeciwnym razie zero. Operator `|`.

<table style="width:100%">
  <tr>
    <th>Wejście 1</th>
    <th>Wejście 2</th>
    <th>Wyjście</th>
  </tr>
  <tr>
    <td>0</td>
    <td>0</td>
    <td>0</td>
</tr>
  <tr>
    <td>0</td>
    <td>1</td>
    <td>1</td>
  </tr>
  <tr>
    <td>1</td>
    <td>0</td>
    <td>1</td>
  </tr>
<tr>
    <td>1</td>
    <td>1</td>
    <td>1</td>
  </tr>
</table>

```c++
#include <bitset>
#include <iostream>

int main() {
  int a = 7;
  int b = 5;

  std::cout << bitset<8>(a) << std::endl;     // 00000111
  std::cout << bitset<8>(b) << std::endl;     // 00000101
  std::cout << bitset<8>(a | b) << std::endl; // 00000111

  return 0;
}
```

### Bramka AND

Jedynka gdy oba bity to jedynki, w przeciwnym razie zero. Operator `&`.

<table style="width:100%">
  <tr>
    <th>Wejście 1</th>
    <th>Wejście 2</th>
    <th>Wyjście</th>
  </tr>
  <tr>
    <td>0</td>
    <td>0</td>
    <td>0</td>
</tr>
  <tr>
    <td>0</td>
    <td>1</td>
    <td>0</td>
  </tr>
  <tr>
    <td>1</td>
    <td>0</td>
    <td>0</td>
  </tr>
<tr>
    <td>1</td>
    <td>1</td>
    <td>1</td>
  </tr>
</table>

```c++
#include <bitset>
#include <iostream>

int main() {
  int a = 7;
  int b = 5;

  std::cout << bitset<8>(a) << std::endl;     // 00000111
  std::cout << bitset<8>(b) << std::endl;     // 00000101
  std::cout << bitset<8>(a & b) << std::endl; // 00000101

  return 0;
}
```

### Bramka XOR

Jedynka, gdy bity są różne, w przeciwnym razie zero. Operator `^`.

<table style="width:100%">
  <tr>
    <th>Wejście 1</th>
    <th>Wejście 2</th>
    <th>Wyjście</th>
  </tr>
  <tr>
    <td>0</td>
    <td>0</td>
    <td>0</td>
</tr>
  <tr>
    <td>0</td>
    <td>1</td>
    <td>1</td>
  </tr>
  <tr>
    <td>1</td>
    <td>0</td>
    <td>1</td>
  </tr>
<tr>
    <td>1</td>
    <td>1</td>
    <td>0</td>
  </tr>
</table>

```c++
#include <bitset>
#include <iostream>

int main() {
  int a = 7;
  int b = 5;

  std::cout << bitset<8>(a) << std::endl;     // 00000111
  std::cout << bitset<8>(b) << std::endl;     // 00000101
  std::cout << bitset<8>(a ^ b) << std::endl; // 00000010

  return 0;
}
```

### Przesunięcia bitowe

* Bity w lewo przesuwamy za pomocą operatora `<<`.
* Bity w prawo przesuwamy za pomocą operatora `>>`.
* Przesunięcie w lewo o 1 bit jest równoważne podzieleniu przez 2.
* Przesuniecie w prawo o 1 bit jest równoważne przemnożeniu przez 2.

```c++
#include <bitset>
#include <iostream>

int main() {
  int a = 14;
  int b = 2;

  std::cout << bitset<8>(a) << std::endl;      // 00001110
  std::cout << bitset<8>(b) << std::endl;      // 00000010
  std::cout << bitset<8>(a << b) << std::endl; // 00111000
  std::cout << bitset<8>(a >> b) << std::endl; // 00000011

  return 0;
}
```
