## Pętle

Pętle są konstrukcją programistyczną wykorzystywaną do wielokrotnego wykonywania bloku kodu. Mamy dwa typy pętli: pętla `for` i pętla `while`.

### Pętla for

Pętla `for` jest używana w celu wykonania czynności określoną liczbę razy. Składa się z trzech elementów oddzielonych średnikami: inicjalizacji licznika, warunku oraz inkrementacji licznika.

Poniższy przykład pokazuje jak wykorzystać pętlę `for` do wyświetlenia wszystkich parzystych liczb z zakresu od 0 do n.

```c++
#include <iostream>

int main() {
  int n;
  std::cout << "Podaj liczbe: " << std::endl;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    if (i % 2)
      continue;
    std::cout << i << std::endl;
  }

  return 0;
}
```

### Pętla while

Pętla `while` jest używana w celu wykonywania czynności, dopóki określony warunek jest spełniony. Składa się z jednego elementu - warunku.

Poniższy przykład pokazuje jak wykorzystać pętlę `while` do wyświetlenia wszystkich liczb z zakresu od 0 do n.

```c++
#include <iostream>

int main() {
  int n;
  std::cout << "Podaj liczbe: " << std::endl;
  std::cin >> n;
  
  int i = 0;
  while (i < n) {
    std::cout << i << std::endl;
    i++;
  }

  return 0;
}
```

### Pętla do while

Pętla `do while` jest używana w celu wykonywania czynności, dopóki określony warunek jest spełniony. Jest ona zbliżona do pętli `while`, z tą różnicą, że ciało pętli jest wykonane przed sprawdzeniem warunku, dzięki czemu jest ona wykonana co najmniej raz.

Poniższy przykład pokazuje jak wykorzystać pętlę `do while` do wyświetlenia wszystkich liczb z zakresu od 0 do n.

```c++
#include <iostream>

int main() {
  int n;
  std::cout << "Podaj liczbę: " << std::endl;
  std::cin >> n;

  int i = 0;
  do {
    std::cout << i << std::endl;
    i++;
  } while (i < n);

  return 0;
}
```

### Continue

Słowo kluczowe `continue` pozwala na natychmiastowe przejście do następnej iteracji pętli.

Poniższy przykład pokazuje jak wykorzystać `continue` do wyświetlenia wszystkich parzystych liczb z zakresu od 0 do n.

```c++
#include <iostream>

int main() {
  int n;
  std::cout << "Podaj liczbę: " << std::endl;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    if (i % 2)
      continue;
    std::cout << i << std::endl;
  }

  return 0;
}
```

### Break

Słowo kluczowe `break` pozwala przerwać wykonywanie pętli.

Poniższy przykład pokazuje jak wykorzystać `break` do wyświetlenia wszystkich nieparzystych liczb z zakresu od 0 do n.

```c++
#include <iostream>

int main() {
  int n;
  std::cout << "Podaj liczbę: " << std::endl;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    if (i % 2)
      break;
    std::cout << i << std::endl;
  }

  return 0;
}
```
