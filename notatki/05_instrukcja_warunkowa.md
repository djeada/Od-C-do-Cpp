## Instrukcje warunkowe

Instrukcje warunkowe służą do włączania i wyłączania fragmentów kodu w zależności od warunku.

### If

<code>If</code> to podstawowa instrukcja warunkowa, dostępna w wielu językach programowania. Warunek definiowany jest w nawiasach okrągłych. Jeśli warunek jest spełniony, to wykonany zostanie kod znajdujący się w nawiasach klamrowych. W przeciwnym razie program omija kod znajdujący się w nawiasach klamrowych i przechodzi do następnych linii kodu.

```c++
  if (warunek) {
    kod;
  }
```

Konstrukcja <code>if-else</code> pozwala na wykonanie różnych bloków kodu w zależności od warunku. Jeśli warunek jest spełniony, to wykonany zostanie kod znajdujący się w nawiasach klamrowych za <code>if</code>. W przeciwnym razie wykonany zostanie kod znajdujący się w nawiasach klamrowych za <code>else</code>.

```c++
  if (warunek) {
    kod;
  } else {
    kod;
  }
```

Jeśli kod jaki chcemy umieścić po słowach kluczowych <code>if</code> lub <code>else</code> składa się wyłącznie z pojedynczej linii, to nawiasy klamrowe mogą zostać pominięte.

```c++
#include <iostream>

int main() {
  int n;
  std::cin >> n;
  if (n % 3 == 0)
    std::cout << "Liczba " << n << " jest podzielna przez 3 " << std::endl;
  else {
    n++;
    std::cout << "Wczytana liczba powiekszona o 1 to: " << n << std::endl;
  }

  return 0;
}
```

### Wielokrotne warunki

Możemy sprawdzić wiele warunków jeden po drugim i uzależnić od ich spełnienia różne bloki kodu.

```c++
#include <iostream>

int main() {
  int n;
  std::cout << "Podaj numer dnia tygodnia: " << std::endl;
  std::cin >> n;

  if (n == 0)
    std::cout << "Poniedziałek." << std::endl;

  else if (n == 1)
    std::cout << "Wtorek." << std::endl;

  else if (n == 2)
    std::cout << "Środa. " << std::endl;

  else if (n == 3)
    std::cout << "Czwartek." << std::endl;

  else if (n == 4)
    std::cout << "Piątek." << std::endl;

  else if (n == 5)
    std::cout << "Sobota." << std::endl;

  else if (n == 6)
    std::cout << "Niedziela." << std::endl;
  else
    std::cout << "Błąd! " << std::endl;

  return 0;
}
```

### Switch

<code>Switch</code> daje nam również możliwość sprawdzenia wielokrotnych warunków.
Niektóre kompilatory lepiej optymalizują kod z użyciem <code>switch</code> niż <code>else if</code>.
Mechanizm ten jest również niejednokrotnie uważany za bardziej elegancki.

```c++
#include <iostream>

int main() {
  int n;
  std::cout << "Podaj numer dnia tygodnia: " << std::endl;
  std::cin >> n;

  switch (n) {
  case 0:
    std::cout << "Poniedzialek." << std::endl;
    break;

  case 1:
    std::cout << "Wtorek." << std::endl;
    break;

  case 2:
    std::cout << "Sroda. " << std::endl;
    break;

  case 3:
    std::cout << "Czwartek." << std::endl;
    break;

  case 4:
    std::cout << "Piatek." << std::endl;
    break;

  case 5:
    std::cout << "Sobota." << std::endl;
    break;

  case 6:
    std::cout << "Niedziela." << std::endl;
    break;

  default:
    std::cout << "Error! " << std::endl;
  }

  return 0;
}
```
