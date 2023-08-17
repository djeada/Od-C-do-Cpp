## Dziedziczenie

Dziedziczenie to mechanizm w programowaniu obiektowym, który pozwala na tworzenie nowych klas, wykorzystując część kodu z klasy już istniejącej. Klasa, z której dziedziczymy, nazywana jest klasą bazową lub rodzicem, natomiast klasa dziedzicząca to klasa pochodna lub dziecko. Dziedziczenie pozwala klasom pochodnym na wykorzystanie pól i metod klasy bazowej oraz rozszerzenie lub modyfikację jej funkcjonalności.

W języku C++ dziedziczenie reprezentowane jest poprzez umieszczenie nazwy klasy dziedziczącej w nawiasach klamrowych po nazwie klasy bazowej. W poniższym przykładzie, klasa `Prostokat` dziedziczy po klasie `Figura`.

```c++
class Figura {
  std::string nazwa;

  public:
    Figura(std::string nazwa) : nazwa(nazwa) {}
    void info() { std::cout << "Figura: " << nazwa << std::endl; }
    virtual double obliczPole() = 0;
};

class Prostokat : public Figura {
  int a;
  int b;

  public:
    Prostokat(int a, int b, std::string nazwa) : Figura(nazwa), a(a), b(b) {}
    void info() {
      Figura::info(); // wywołanie metody bazowej
      std::cout << "Prostokat: " << a << "x" << b << std::endl;
    }
    double obliczPole() { return a * b; }
}
```

W powyższym przykładzie, Prostokat dziedziczy wszystkie pola i metody z klasy Figura, takie jak nazwa, a także dodaje nowe pola a i b. Klasa Prostokat nadpisuje również metodę info() z klasy bazowej, wywołując jej pierwotną implementację i dodając nowe informacje.

### Typy dziedziczenia

Istnieją trzy podstawowe typy dziedziczenia w C++:

- publiczne (`public`) - pozwala na dostęp do pol i metod klasy bazowej zarówno wewnątrz klasy pochodnej, jak i z zewnątrz.
- prywatne (`private`) - ogranicza dostęp do pol i metod klasy bazowej tylko do wnętrza klasy pochodnej.
- chronione (`protected`) - udostępnia pola i metody klasy bazowej dla klas pochodnych oraz dla samej klasy bazowej.

Poniższa tabela przedstawia dostępność pol i metod klasy bazowej w zależności od typu dziedziczenia:

| Typ Dziedziczenia | Dostęp do prywatnych pól i metod	 | Dostęp do chronionych pól i metod | Dostęp do publicznych pól i metod |
| ---------------- | ---------------------- | ---------------------- | ---------------------- |
| publiczne | tak | tak | tak |
| chronione | nie | tak | tak (ale zmienia się na chronioną) |
| prywatne | nie | tak (ale zmienia się na prywatną) | tak (ale zmienia się na prywatną) |

### Polimorfizm

Polimorfizm to jedno z kluczowych zagadnień programowania obiektowego, które umożliwia obiektom różnych klas reagowanie na te same wywołania metod w indywidualny sposób. Polimorfizm pozwala na interakcję z obiektami poprzez interfejs ich klas bazowych, nie znając ich rzeczywistej klasy. W praktyce oznacza to, że różne klasy mogą implementować metody o tej samej nazwie, lecz różnej funkcjonalności.

W kontekście języków programowania takich jak C++, polimorfizm osiągany jest głównie za pomocą funkcji wirtualnych i dziedziczenia. 

Przykładowo, możemy mieć klasę bazową `A` z metodą wirtualną `foo()`, oraz klasy pochodne `B` i `C`, które nadpisują tę metodę.

```c++
class A {
  public:
    virtual void foo() { std::cout << "A" << std::endl; }
};

class B : public A {
  public:
    void foo() override { std::cout << "B" << std::endl; }
};

class C : public A {
  public:
    void foo() override { std::cout << "C" << std::endl; }
};
```

Gdy mamy kolekcję wskaźników do klasy bazowej A, które w rzeczywistości wskazują na obiekty klas A, B i C, wywołanie metody foo() da różne rezultaty w zależności od rzeczywistego typu obiektu.

```c++
std::vector<A*> obiekty { new A, new B, new C };

for (auto obiekt : obiekty)
  obiekt->foo();
```

To podejście eliminuje potrzebę ręcznego sprawdzania typu obiektu i decydowania, jaką metodę wywołać. Dla porównania, bez polimorfizmu, musielibyśmy użyć instrukcji warunkowych, aby obsłużyć każdy typ obiektu indywidualnie.

Polimorfizm zapewnia elastyczność i skalowalność kodu. Dzięki temu, nowe klasy mogą być dodawane z minimalnym wpływem na istniejący kod, pod warunkiem, że przestrzegają one tego samego interfejsu (wirtualne metody klasy bazowej).

W praktycznym przykładzie, zamiast tworzyć różne metody dla każdego typu zwierzęcia (jak kwacz() dla kaczki czy szczekaj() dla psa), możemy stworzyć uniwersalną metodę zachowanie() i odpowiednio ją zaimplementować w każdej klasie dziedziczącej.

```c++
class Zwierze {
  public:
    virtual void zachowanie() = 0; // czysta funkcja wirtualna
};

class Kaczka : public Zwierze {
  public:
    void zachowanie() override { std::cout << "Kwaczę" << std::endl; }
};

class Pies : public Zwierze {
  public:
    void zachowanie() override { std::cout << "Szczekam" << std::endl; }
};

void foo(Zwierze* obiekt) {
  obiekt->zachowanie();
}
```

W skrócie, polimorfizm sprzyja tworzeniu bardziej ogólnych, reużywalnych i łatwiejszych do rozwijania aplikacji.

### Metody wirtualne

W języku C++, metody wirtualne pozwalają na dynamiczne wiązanie metod. Oznacza to, że jeśli mamy wskaźnik lub referencję do klasy bazowej, który w rzeczywistości wskazuje (lub odnosi się) do obiektu klasy pochodnej, to wywołanie metody wirtualnej odwołuje się do odpowiedniej implementacji w zależności od rzeczywistego typu obiektu.

Przykład ilustrujący zachowanie bez używania metody wirtualnej:

```c++
class A {
  public:
    void foo() { std::cout << "A" << std::endl; }
};

class B : public A {
  public:
    void foo() { std::cout << "B" << std::endl; }
};

B b;
A* wsk = &b;
wsk->foo(); // wyświetli "A"
```

Aby uzyskać oczekiwane zachowanie, musimy zastosować słowo kluczowe virtual w deklaracji metody klasy bazowej:

```c++
class A {
  public:
    virtual void foo() { std::cout << "A" << std::endl; }
};

class B : public A {
  public:
    void foo() override { std::cout << "B" << std::endl; }
};

B b;
A* wsk = &b;
wsk->foo(); // wyświetli "B"
```

Pamiętaj również, że jeśli w klasie bazowej zdefiniowano destruktor jako wirtualny, destruktor w klasie pochodnej również stanie się wirtualny:

```c++
class A {
  public:
    virtual ~A() { /* ... */ }
};

class B : public A {
  public:
    ~B() override { /* ... */ }
};
```

### Klasy abstrakcyjne

W C++ klasy abstrakcyjne służą jako szablony dla innych klas. Nie można tworzyć obiektów klasy abstrakcyjnej, ale można tworzyć wskaźniki i referencje do niej. Klasy abstrakcyjne są zwykle używane jako bazy dla klas pochodnych.

Aby uczynić klasę abstrakcyjną, musisz zdefiniować przynajmniej jedną jej metodę jako czysto wirtualną, co oznacza, że nie ma ona implementacji w klasie bazowej.

```c++
class A {
  public:
    virtual void foo() = 0;
};

class B : public A {
  public:
    void foo() override { std::cout << "B" << std::endl; }
};

B b;
A* wsk = &b;
wsk->foo(); // wyświetli "B"
```

Czy warto stosować klasy abstrakcyjne?

- **Kapsułkowanie**: Umożliwiają zdefiniowanie interfejsu bez narzucania konkretnej implementacji.
- **Rozszerzalność**: Klasy pochodne mogą dostarczać własne implementacje metod, jednocześnie zachowując interfejs klasy bazowej.
- **Zachowanie spójności**: Wymagają od klas pochodnych zaimplementowania określonych metod.

Klasa czysto wirtualna to specyficzny rodzaj klasy abstrakcyjnej, która nie zawiera żadnych składowych ani implementacji, tylko deklaracje czysto wirtualnych metod:

```c++
class A {
  public:
    virtual void foo() = 0;
    virtual void bar() = 0;
};
```

W praktyce klasy czysto wirtualne są rzadko stosowane, ale mogą być użyteczne w bardzo specyficznych scenariuszach, gdzie wymagana jest wyłącznie definicja interfejsu bez jakiejkolwiek implementacji.
