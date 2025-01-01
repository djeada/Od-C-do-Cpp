## Instrukcje warunkowe

Instrukcje warunkowe stanowią podstawowy mechanizm kontroli przepływu w praktycznie każdym języku programowania, w tym w C++. Pozwalają one na wykonywanie określonych fragmentów kodu tylko wówczas, gdy spełniony jest ustalony warunek. Dzięki temu programy mogą podejmować decyzje i reagować na bieżące wartości zmiennych bądź wynik operacji. Poniżej przedstawiono najważniejsze konstrukcje i dobre praktyki związane z instrukcjami warunkowymi w C++, w tym typowe pułapki, na które trzeba uważać podczas pisania i debugowania kodu.

### Podstawowa instrukcja `if`

Najprostszą i zarazem najczęściej wykorzystywaną konstrukcją warunkową jest `if`. Pozwala ona na wykonanie określonego bloku kodu wyłącznie wtedy, gdy podany w nawiasie okrągłym warunek przyjmuje wartość prawdziwą. Aby to zilustrować, przyjmijmy przykładową zmienną `x` o wartości 5. Jeśli `x` okaże się większe niż 3, wtedy wyświetlimy komunikat w konsoli:

```cpp
int x = 5;
if (x > 3) {
    std::cout << "x jest większe niż 3" << std::endl;

}
```

W tym przykładzie warunek `x > 3` jest spełniony (gdyż `5 > 3`), więc wewnątrz bloku `if` zostanie wywołane polecenie `std::cout << ...`. Jeżeli zaś chcielibyśmy zareagować na inny scenariusz, w którym warunek nie jest spełniony, możemy zastosować rozszerzenie `if-else`.

### Rozszerzenie `if-else`

Instrukcja `else` przydaje się w sytuacjach, kiedy chcemy wykonać inny blok kodu, jeśli warunek pierwotny nie został spełniony. Pozwala to na jasne rozgraniczenie dwóch różnych ścieżek działania programu, w zależności od wartości zmiennej:

```cpp
if (x > 10) {
    std::cout << "x jest większe niż 10" << std::endl;
} else {
    std::cout << "x nie jest większe niż 10" << std::endl;
}
```

Tutaj, jeśli `x` wyniesie przykładowo 12, to w konsoli zobaczymy pierwszy komunikat. Natomiast gdy `x` wyniesie 3, zostanie wyświetlony komunikat z bloku `else`. Jest to jeden z najbardziej podstawowych wzorców decyzyjnych w kodzie.

### Instrukcja `if-else if-else`

Często zdarza się, że chcemy zbadać więcej niż jeden warunek i wykonać różne działania zależnie od ich wyniku. W takim przypadku wygodnie jest skorzystać z instrukcji warunkowej rozszerzonej o dodatkowe gałęzie `else if`:

```cpp
if (x > 10) {
    std::cout << "x jest większe niż 10" << std::endl;

} else if (x > 5) {
    std::cout << "x jest większe niż 5, ale nie większe niż 10" << std::endl;

} else {
    std::cout << "x nie jest większe niż 5" << std::endl;

}
```

Algorytm sprawdzi kolejno: najpierw, czy `x > 10`; jeśli to prawda – wykona pierwszy blok i pominie resztę. Jeśli nie, przejdzie do drugiego warunku `x > 5`; jeśli on zostanie spełniony – wyświetli drugi komunikat, a jeśli okaże się fałszywy, wykona wreszcie blok `else`. Warto mieć na uwadze, że pierwszy warunek, który zostanie rozpoznany jako prawdziwy, przerywa dalsze sprawdzanie. 

### Złożone warunki logiczne

Operatory logiczne `&&` (koniunkcja/AND) oraz `||` (alternatywa/OR) pozwalają na łączenie wielu warunków w jednej instrukcji `if`. Dzięki nim możemy tworzyć bardziej rozbudowane wyrażenia logiczne:

```cpp
if (x > 5 && x < 10) {
    std::cout << "x jest większe niż 5 i mniejsze niż 10" << std::endl;
}

if (x < 5 || x > 10) {
    std::cout << "x jest mniejsze niż 5 lub większe niż 10" << std::endl;
}
```

Pierwszy przykład wykona się tylko wówczas, gdy wartość `x` będzie jednocześnie większa niż 5 oraz mniejsza niż 10. Drugi zadziała w sytuacjach, w których wartość `x` znajdzie się poza przedziałem [5, 10]. Tworzenie złożonych wyrażeń logicznych znacznie zwiększa elastyczność warunków, jednak zawsze należy dbać o ich czytelność. 

### Operator warunkowy (trójargumentowy)

W C++ funkcjonuje również tzw. operator trójargumentowy `?:`, nazywany często „ternary operator”. Pozwala on na zapisanie prostego warunku i przypisania wartości w jednej linii, co bywa przydatne przy nadawaniu wartości zmiennym. Składnia wygląda następująco:

```cpp
int max = (x > y) ? x : y;
```
Wyrażenie `(x > y) ? x : y` odczytujemy w sposób: „Jeżeli `x` jest większe od `y`, zwróć `x`, w przeciwnym razie zwróć `y`”. Dzięki temu w zmiennej `max` znajdzie się większa z dwóch liczb bez konieczności stosowania rozbudowanego `if-else`.

### Instrukcja warunkowa z wartością logiczną

W języku C++ typ logiczny `bool` może być bezpośrednio wykorzystywany w instrukcjach `if`. Zmienna typu `bool` przyjmuje wartość `true` lub `false`, a jej interpretacja w warunku odbywa się bezpośrednio:

```cpp
bool warunek = true;
if (warunek) {
    std::cout << "Warunek jest prawdziwy" << std::endl;
} else {
    std::cout << "Warunek jest fałszywy" << std::endl;
}
```

Powyższy przykład jest bardzo przejrzysty, gdyż unika rzutowania na wartość całkowitą (`0`/`1`). Niemniej w C++ dopuszczalne jest używanie liczb całkowitych w warunkach – warto jednak zaznaczyć, że `0` interpretowane jest jako `false`, a każda inna wartość całkowita jako `true`.

### Na co uważać przy używaniu instrukcji warunkowych

Choć konstrukcje warunkowe wydają się dość proste, w praktyce mogą pojawić się pewne trudności i sytuacje, w których działanie programu nie będzie takie, jak się spodziewaliśmy. Oto kilka typowych pułapek i dobrych praktyk:

I. **Kolejność ewaluacji warunków**

W przypadku zagnieżdżonych instrukcji `if-else if-else` sprawdzanie kończy się w momencie znalezienia pierwszego warunku, który zwraca prawdę. Kolejne ścieżki nie zostaną wówczas wykonane, nawet jeśli również byłyby prawdziwe.

```cpp
int x = 10;
if (x > 5) {
   std::cout << "x jest większe niż 5" << std::endl;

} else if (x > 8) {

   // Do tej gałęzi nigdy nie dojdzie, mimo że x > 8 również jest prawdą.
   std::cout << "x jest większe niż 8" << std::endl;

}
```

II. **Ewaluacja wartości logicznych**: W C++ liczba `0` jest interpretowana jako `false`, natomiast każda inna liczba całkowita traktowana jest jak `true`. Może to prowadzić do niezamierzonego działania, jeśli przez pomyłkę zostanie użyty typ całkowity w warunkach.

```cpp
int liczba = 0;
if (liczba) {
   std::cout << "To jest prawdziwe" << std::endl;
} else {
   std::cout << "To jest fałszywe" << std::endl;  // Wyświetli się ten komunikat.
}
```

III. **Pomyłki `==` vs. `=`**: Zdarza się, że przez nieuwagę zamiast operatora porównania `==` użyjemy operatora przypisania `=`. Taka pomyłka w warunku nie wywoła błędu kompilacji, ale zmieni wartość zmiennej i zawsze zwróci wynik interpretowany jak `true` (jeśli przypisana wartość jest różna od zera).

```cpp
int x = 5;

// Niepoprawne, bo użyto '=' zamiast '=='
if (x = 10) {
   std::cout << "x jest równe 10" << std::endl; 

   // Ten blok wykona się zawsze (po przypisaniu x=10 jest interpretowane jako true).

}

// Poprawna wersja:
if (x == 10) {
   std::cout << "x jest równe 10" << std::endl;

}
```

IV. **Porównywanie zmiennoprzecinkowe**

Korzystanie z operatora `==` przy danych zmiennoprzecinkowych (`float`, `double`) może być niebezpieczne, ze względu na ograniczoną precyzję zapisu liczb w tym formacie. Zaleca się w takich przypadkach porównywanie z pewną tolerancją (epsilonem).

```cpp
double a = 0.1;
double b = 0.1 + 0.1 + 0.1 - 0.3;
if (a == b) {
   std::cout << "a == b" << std::endl;  // Może nie zadziałać zgodnie z oczekiwaniami.
}
const double epsilon = 1e-9;
if (fabs(a - b) < epsilon) {
   std::cout << "a i b są w przybliżeniu równe" << std::endl;
}
```

V. **Efekty uboczne w warunkach**

Używanie inkrementacji (np. `x++`) czy wyrażeń z innymi efektami ubocznymi wewnątrz warunku może prowadzić do trudnych do wyśledzenia błędów. Wynika to z faktu, że samą inkrementację można łatwo przeoczyć, co zmienia dalsze działanie programu:

```cpp
int x = 5;
if (x++ > 5) {
   std::cout << "x jest większe niż 5" << std::endl;  

}
std::cout << "x = " << x << std::endl;  // x = 6, co może być nieoczywiste na pierwszy rzut oka.
```

VI. **Złożone warunki logiczne**

Bardzo długie wyrażenia logiczne, łączące wiele operatorów `&&` i `||`, bywają trudne do odczytania. Dobrym pomysłem jest dzielenie ich na mniejsze, wyodrębnione warunki przypisane do pomocniczych zmiennych o znaczących nazwach:

```cpp
int a = 5, b = 10, c = 15;
bool wszystkieDodatnie = (a > 0) && (b > 0) && (c > 0);
bool spelniaNierownosciTrojkata = (a + b > c) && (a + c > b) && (b + c > a);
if (wszystkieDodatnie && spelniaNierownosciTrojkata) {
   std::cout << "Wszystkie liczby są dodatnie i spełniają nierówności trójkąta" << std::endl;
}
```

VII. **Unikanie powtórzeń kodu**

Czasem w blokach `if` i `else` pojawia się identyczny fragment kodu. Zamiast duplikować instrukcje, lepiej przenieść je na zewnątrz, co poprawia czytelność i ułatwia konserwację:

```cpp
int x = 5;
if (x > 10) {
   std::cout << "x jest większe niż 10" << std::endl;

   // wspólny fragment kodu

} else {
   std::cout << "x nie jest większe niż 10" << std::endl;

   // wspólny fragment kodu

}

// Lepsze podejście
if (x > 10) {
   std::cout << "x jest większe niż 10" << std::endl;

} else {
   std::cout << "x nie jest większe niż 10" << std::endl;

}

// Wspólna część po instrukcjach
std::cout << "To jest wspólny kod" << std::endl;
```
   
### Konstrukcja `switch`

Konstrukcja `switch` stanowi alternatywę dla rozbudowanych łańcuchów `if-else if-else`. Szczególnie przydaje się wtedy, gdy chcemy wielokrotnie porównać jedną i tę samą zmienną z różnymi wartościami stałymi (np. liczbami całkowitymi lub znakami). Działa to w ten sposób, że podajemy wartość zmiennej w nawiasie po słowie kluczowym `switch`, a następnie w kolejnych blokach `case` sprawdzamy, czy zmienna tę wartość przyjmuje.

```cpp
#include <iostream>

int main() {
    int n;
    std::cout << "Podaj numer dnia tygodnia (0-6): " << std::endl;
    std::cin >> n;

    switch (n) {
    case 0:
        std::cout << "Poniedziałek." << std::endl;
        break;
    case 1:
        std::cout << "Wtorek." << std::endl;
        break;
    case 2:
        std::cout << "Środa." << std::endl;
        break;
    case 3:
        std::cout << "Czwartek." << std::endl;
        break;
    case 4:
        std::cout << "Piątek." << std::endl;
        break;
    case 5:
        std::cout << "Sobota." << std::endl;
        break;
    case 6:
        std::cout << "Niedziela." << std::endl;
        break;
    default:
        std::cout << "Błąd! Numer dnia powinien być w zakresie 0-6." << std::endl;
    }

    return 0;
}
```

Gdy zostanie znaleziony pasujący `case`, wykonywanie kodu trwa aż do momentu napotkania słowa `break` lub końca całej konstrukcji `switch`. Z kolei `default` pełni rolę „wszystkich innych przypadków”, czyli jest wykonywany wtedy, gdy żaden z bloków `case` nie pasuje.

Konstrukcja `switch` bywa czytelniejsza i efektywniejsza w sytuacjach, gdzie występują liczne porównania zmiennej z różnymi wartościami. Dodatkowo, kompilator może czasem zoptymalizować `switch` wewnętrznie (np. przy użyciu tablicy przeskoków), co przy rozbudowanych instrukcjach może przyspieszyć wykonywanie kodu. 
