## Operacje bitowe

Mamy możliwość wykonywania operacji na pojedynczych bitach.

### Bramka NOT

Zamienia jedynki na zera i na odwrót. Operator ~.

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

Jedynka gdy co najmniej jeden z bitów to jedynka, w przeciwnym razie zero. Operator |.

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

Jedynka gdy oba bity to jedynki, w przeciwnym razie zero. Operator &.

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

Jedynka, gdy bity są różne, w przeciwnym razie zero. Operator ^.

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

Bity w lewo przesuwamy za pomocą operatora <code><<</code>. </br>
Bity w prawo przesuwamy za pomocą operatora <code>>></code>. </br>
Przesunięcie w lewo o 1 bit jest równoważne podzieleniu przez 2. </br>
Przesuniecie w prawo o 1 bit jest równoważne przemnożeniu przez 2. </br>

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
