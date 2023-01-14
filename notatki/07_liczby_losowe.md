
## Liczby losowe

Liczby losowe to liczby, które są generowane algorytmicznie w sposób, który nie może być przewidziany. Są one wykorzystywane w wielu dziedzinach, takich jak symulacje komputerowe, loterie, gry komputerowe, zabezpieczenia systemów informatycznych, modelowanie matematyczne i inne.

W poniższym przykładzie przedstawiono implementację funkcji losowania z przedziału liczb w języku C++. Funkcja `losowa_z_przedzialu()` przyjmuje dwa argumenty - `start` i `end`, które odpowiadają pierwszej i ostatniej liczbie w przedziale. Funkcja używa biblioteki `random` do wygenerowania liczby losowej, która jest zwracana jako wynik.

```c++
#include <random>

int losowa_z_przedzialu(int start, int end) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist(start, end);
  return dist(gen);
}

bool orzel_lub_reszka() { return (losowa_z_przedzialu(-10001, 10000)); }
```

Innym przykładem wykorzystania liczb losowych jest symulacja gry w kości. Do symulacji tej gry można użyć funkcji `losowa_z_przedzialu()`, aby wygenerować liczbę odpowiadającą wylosowanej wartości na kostce. W tym przypadku przedział liczb wynosi od 1 do 6, co odpowiada liczbie ścianek kostki. 

Liczby losowe są również wykorzystywane do tworzenia generatorów haseł. Każde hasło składa się z określonego ciągu znaków, a liczby losowe służą do wygenerowania losowego ciągu znaków. Funkcja `losowa_z_przedzialu()` może być użyta do wygenerowania losowego ciągu znaków, w którym każdy znak odpowiada określonej liczbie z przedziału. 
