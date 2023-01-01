## Lambdy

W C++ mamy możliwość tworzenia funkcji w obrębie innych funkcji, a nawet w momencie wywołania funkcji w samym argumencie. Takie funkcje nie mają nazwy i nie muszą być uprzednio zadeklarowane. Te funkcje zwane są lambdami.

Ogólna postać funkcji anonimowej jest następująca:

    [domknięcie](parametry) -> typ { ciało }

W nawiasach okrągłych mamy listę parametrów, która działa tak samo jak dla zwykłych funkcji. W wielu przypadkach możemy pominąć strzałkę wraz z typem zwracanym, gdyż kompilator jest w stanie wydedukować typ na etapie kompilacji.

Przykład funkcji lambda przyjmującej dwa argumenty i zwracającej wartość typu int:

    [](int a, int b) { return a + b; } 

Jeśli chcemy mieć bezpośredni dostęp do zmiennych z zewnętrznego kontekstu, możemy użyć <code>&</code> w nawiasie kwadratowym. Wtedy nie musimy przekazywać takich zmiennych jako argumentów funkcji, a mimo to możemy ich użyć w ciele lambdy.

    int x = 10;
    [&](int a, int b) { return x * (a + b); } 

Możemy lambdę przypisać do nazwy i użyć ją wielokrotnie w obrębie kontekstu, w którym została zdefiniowana.

    int x = 10;

    auto nazwaFunkcji = [&](int a, int b) { return x * (a + b); };

    nazwaFunkcji(10, 10); // 200
    nazwaFunkcji(5, 2);   // 70
