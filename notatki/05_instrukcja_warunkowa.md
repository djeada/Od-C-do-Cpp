## Instrukcje warunkowe

Instrukcje warunkowe to konstrukcje, które pozwalają na włączanie i wyłączanie fragmentów kodu w zależności od warunku. Są one dostępne w wielu językach programowania. Najpopularniejszą instrukcją warunkową jest słowo kluczowe `if`, które pozwala na wykonanie kodu w zależności od spełnienia określonego warunku. Warunek jest definiowany w nawiasach okrągłych, a kod, który ma być wykonany, jest umieszczony w nawiasach klamrowych. Jeśli warunek jest spełniony, to wykonany zostanie kod znajdujący się w nawiasach klamrowych; w przeciwnym razie program omija kod znajdujący się w nawiasach klamrowych i przechodzi do następnych linii kodu.

Konstrukcja `if-else` pozwala na wykonanie różnych bloków kodu w zależności od warunku. Jeśli warunek jest spełniony, to wykonany zostanie kod znajdujący się w nawiasach klamrowych za `if`. W przeciwnym razie wykonany zostanie kod znajdujący się w nawiasach klamrowych za `else`. Jeśli kod jaki chcemy umieścić po słowach kluczowych `if` lub `else` składa się wyłącznie z pojedynczej linii, to nawiasy klamrowe mogą zostać pominięte. Przykład:

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

Jeśli chcemy sprawdzić wiele warunków jeden po drugim i uzależnić od ich spełnienia różne bloki kodu, możemy użyć konstrukcji `if-else if-else`. Przykład:

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

Instrukcje warunkowe pozwalają programiście na skuteczny i łatwy dostęp do konkretnych bloków kodu w zależności od określonego warunku. Są one niezwykle przydatne w przypadku, gdy chcemy sprawdzić kilka warunków jeden po drugim i uzależnić od ich spełnienia różne bloki kodu.

### Switch
Switch jest konstrukcją języka programowania, która pozwala na wykonanie określonego bloku kodu w zależności od wartości zmiennej. Umożliwia ona sprawdzenie wielokrotnych warunków bez potrzeby używania wielu instrukcji <code>if-else</code>.

Dodatkowo, kompilatory lepiej optymalizują kod z wykorzystaniem <code>switch</code>. Przykładowy kod w C++ używający <code>switch</code> może wyglądać następująco:

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
