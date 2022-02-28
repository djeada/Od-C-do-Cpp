/*
Uproszczona definicja:
- lwartosc: obiekt, ktory zajmuje pewna identyfikowalna lokalizacje w pamieci
    - cos w pamieci, a nie cos w rejestrze
    - ma mozliwy do zidentyfikowania adres
- rvalue: dowolny obiekt, ktory nie jest lvalue
    - jesli sprobuje uzyskac ich adres w ten sposob, kompilator wystapi blad
    - Nie moge im tez przypisac innej wartosci
*/

class PrzykladowaKlasa {};

int sum(int x, int y) { return x + y; }

int square(int &x) { return x * x; }

int csquare(const int &x) { return x * x; }

int myglobal;

int &foo() { return myglobal; }
int bar() { return myglobal; }

int main() {
  int i;       // i is a lvalue
  int *p = &i; // i's address is identifiable
  i = 2;       // memory content is modified

  PrzykladowaKlasa d1; // lvalue of user defined type(class)

  int x = 2;     // 2 is an rvalue
  int c = i + 2; //(i+2) is an rvalue
  *p = (i + 2);  // Error
  // i + 2 = 4;      //Error
  // 2 = i;          //Error

  PrzykladowaKlasa d2;
  d2 = PrzykladowaKlasa(); // Dog() is rvalue of user defined type(class)
  i = sum(3, 4);           // sum is rvalue

  // Rvalues: 2, i+2, PrzykladowaKlasa(), sum(3,4), x+y
  // Lvalues: x, i, d1, , d2, p

  int &adress = i;
  // int &adress = 5; //Error

  // Exception: Constant lvalue reference can be assign a rvalue;
  const int &r = 5;

  square(i); // OK
  // square(40); //Error

  csquare(i);  // OK
  csquare(40); // OK

  foo() = 50; // this will compile, foo() is lvalue
              // bar() = 50;   // Error
}
