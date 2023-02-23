/*
Lvalue - obiekt, który ma przypisany adres w pamięci i może być identyfikowany
jako pojedyncza wartość. Można do niego przypisać inną wartość lub zmienić jego
wartość bez zmiany miejsca w pamięci. Rvalue - obiekt, który nie ma przypisanego
adresu w pamięci i zazwyczaj jest wartością tymczasową lub stałą. Nie można
przypisać do niego innego obiektu ani zmienić jego wartości bezpośrednio.

Przykłady funkcji przyjmujących różne rodzaje parametrów:
*/

class PrzykladowaKlasa {};

int suma(int x, int y) { return x + y; }

int kwadrat(int &x) { return x * x; }

int stalyKwadrat(const int &x) { return x * x; }

int zmiennaGlobalna;

int &foo() { return zmiennaGlobalna; }
int bar() { return zmiennaGlobalna; }

int main() {
  int i;       // i jest lvalue
  int *p = &i; // adres i jest identyfikowalny
  i = 2;       // modyfikacja zawartości pamięci

  PrzykladowaKlasa d1; // lvalue użytkownika zdefiniowanego typu (klasy)

  int x = 2;     // 2 jest rvalue
  int c = i + 2; // (i+2) jest rvalue
  // *p = (i + 2);    // błąd, próba przypisania do rvalue
  // i + 2 = 4;       // błąd, próba przypisania do rvalue
  // 2 = i;           // błąd, próba przypisania do rvalue

  PrzykladowaKlasa d2;
  d2 = PrzykladowaKlasa(); // PrzykladowaKlasa() jest rvalue użytkownika
                           // zdefiniowanego typu (klasy)
  i = suma(3, 4);          // suma jest rvalue

  // Rvalues: 2, i+2, PrzykladowaKlasa(), suma(3,4), x+y
  // Lvalues: x, i, d1, d2, p

  int &adress = i;
  // int& adress = 5; // błąd, próba przypisania do rvalue

  // Wyjątek: Stała referencja lvalue może zostać przypisana do rvalue;
  const int &r = 5;

  kwadrat(i); // OK
  // kwadrat(40);  // błąd, próba przypisania do rvalue

  stalyKwadrat(i);  // OK
  stalyKwadrat(40); // OK

  foo() = 50; // to skompiluje się, foo() jest lvalue
  // bar() = 50; // błąd, próba przypisania do rvalue
}
