## Lambdy

W języku C++, mamy możliwość tworzenia funkcji anonimowych, czyli takich, które nie posiadają nazwy i nie muszą być uprzednio zadeklarowane. Te funkcje nazywane są lambdami.

Ogólna postać funkcji anonimowej jest następująca:

```c++
[domknięcie](parametry) { blok kodu }
```

W nawiasach okrągłych mamy listę parametrów, która działa tak samo jak dla zwykłych funkcji. W wielu przypadkach możemy pominąć strzałkę wraz z typem zwracanym, gdyż kompilator jest w stanie wydedukować typ na etapie kompilacji.

Przykład funkcji lambda przyjmującej dwa argumenty i zwracającej wartość typu int:

```c++
[](int a, int b) { return a + b; } 
```

Jeśli chcemy mieć bezpośredni dostęp do zmiennych z zewnętrznego kontekstu, takich jak zmienne globalne, możemy użyć operatora "&" w nawiasie kwadratowym. Wtedy nie musimy przekazywać takich zmiennych jako argumentów funkcji, a mimo to możemy ich użyć w ciele lambdy.

```c++
int x = 10;
[&](int a, int b) { return x * (a + b); } 
```

Możemy też przypisać lambdę do nazwy i użyć ją wielokrotnie w obrębie kontekstu, w którym została zdefiniowana.

```c++
int x = 10;

auto nazwaFunkcji = [&](int a, int b) { return x * (a + b); };

nazwaFunkcji(10, 10); // 200
nazwaFunkcji(5, 2);   // 70
```

Lambdy są przydatne w przypadku, gdy potrzebujemy wywołać funkcję tylko raz i nigdy więcej jej nie użyjemy, lub w sytuacjach, gdy chcemy dostarczyć funkcję jako argument do innej funkcji. Mogą być one również użyte do skrócenia kodu, ponieważ pozwalają na zapisanie kodu w miejscu, gdzie jest on potrzebny, zamiast tworzenia osobnej funkcji. Lambdy są szczególnie przydatne w przypadku użycia z bibliotekami, takimi jak STL, które wymagają funkcji jako argumentów.
