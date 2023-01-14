## Dziedziczenie

Dziedziczenie to mechanizm, który pozwala na tworzenie nowych klas wykorzystujących część kodu z klasy już istniejącej. Klasa pierwotna nazywana jest klasą bazową (bądź rodzicem), a klasa dziedzicząca jest klasą pochodną (bądź dzieckiem). Dziedziczenie pozwala na udzielanie klasom pochodnym dostępu do pol i metod klasy bazowej, jednocześnie pozwalając na rozszerzenie bądź modyfikację funkcjonalności klasy bazowej.

W C++ dziedziczenie jest zdefiniowane przez zapisanie klasy dziedziczącej w nawiasach klamrowych po nazwie klasy bazowej. W naszym przykładzie, klasa Prostokat dziedziczy po klasie Figura.

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

W powyższym przykładzie `Prostokat` dziedziczy wszystkie pola i metody z klasy `Figura`, takie jak pole `nazwa`, a także rozszerza ją o nowe pola `a` i `b`. Klasa `Prostokat` nadpisuje również metodę `info()` klasy bazowej, wywołując implementację bazową i dodając do niej dodatkowe informacje.

### Typy dziedziczenia

Istnieją trzy podstawowe typy dziedziczenia:

1. publiczne (public) - pozwala na dostęp do pol i metod klasy bazowej zarówno wewnątrz klasy pochodnej, jak i z zewnątrz.
2. prywatne (private) - ogranicza dostęp do pol i metod klasy bazowej tylko dla wewnętrznych elementów klasy pochodnej.
3. chronione (protected) - pozwala na dostęp do pol i metod klasy bazowej tylko dla klas pochodnych oraz elementów wewnątrz klasy bazowej.

Poniższa tabela zawiera informacje o dostępności pol i metod klasy bazowej dla poszczególnych typów dziedziczenia:

| Typ Dziedziczenia | Prywatne pola i metody | Chronione pola i metody | Publiczne pola i metody |
| ---------------- | ---------------------- | ---------------------- | ---------------------- |
| publiczne | tak | tak | tak |
| chronione | nie | tak | tak (lecz ich dostępność zmienia się na chronioną) |
| prywatne | nie | tak (lecz ich dostępność zmienia się na prywatną) | tak (lecz ich dostępność zmienia się na prywatną) |


### Polimorfizm

Polimorfizm to mechanizm umożliwiający nadawaniu tej samej wiadomości do różnych typów odbiorców, bez wiedzy o konkretnym typie danego odbiorcy. Każdy odbiorca może odpowiedzieć na wiadomość we własny sposób. Odpowiedzi mogą, ale nie muszą się pokrywać. Polimorfizm jest często definiowany w kontekście dziedziczenia.

Na przykład, mamy klasę bazową zawierającą definicję metody `foo()`, oraz klasy pochodne `B` i `C` które dziedziczą po klasie bazowej `A`. Klasa `B` i `C` mogą mieć swoje własne implementacje metody `foo()`.

```c++

class A {
  public:
    void foo() { std::cout << "A" << std::endl; }
};

class B : public A {
  public:
    void foo() { std::cout << "B" << std::endl; }
};

class C : public A {
  public:
    void foo() { std::cout << "C" << std::endl; }
};
```

Jeśli utworzymy kolekcję obiektów klasy bazowej `A` oraz klas pochodnych `B` i `C`, to wywołując metodę `foo()` na każdym elemencie kolekcji, otrzymamy różne rezultaty w zależności od dokładnego typu obiektu.

```c++
std::vector<A*> obiekty { new A, new B, new C };

for (auto obiekt : obiekty)
  obiekt->foo();
```

Wynik tego kodu będzie wyświetlenie "A", "B", "C" w kolejności.

Ważnym problemem rozwiązanym przez polimorfizm jest zbędne rozgałęzienie kodu w celu sprawdzenia typu obiektu. Weźmy pod uwagę poniższy przykład:

```c++
class Kaczka {
  public:
    void kwacz() { std::cout << "Kwaczę" << std::endl; }
};

class Pies {
  public:
    void szczekaj() { std::cout << "Szczekam" << std::endl; }
};

void foo(void* obiekt) {
  if (dynamic_cast<Kaczka*>(obiekt))
    dynamic_cast<Kaczka*>(obiekt)->kwacz();
  else if (dynamic_cast<Pies*>(obiekt))
    dynamic_cast<Pies*>(obiekt)->szczekaj();
}
```

W tym przykładzie, aby wykonać odpowiednią akcję dla danego obiektu, kod musi sprawdzić typ obiektu i dopiero wtedy wykonać odpowiednią akcję. Przy większej liczbie klas i typów obiektów, takie rozgałęzienie kodu staje się coraz bardziej skomplikowane i trudne do utrzymania.

Dlatego też, polimorfizm pozwala na uniknięcie tego problemu poprzez wykorzystanie wirtualnych metod, które są implementowane przez klasy pochodne i wywoływane przez obiekty bazowej klasy, dzięki czemu kod jest bardziej czytelny i łatwiejszy do utrzymania.

```c++
class Zwierze {
  public:
    virtual void zachowanie() = 0;
};

class Kaczka : public Zwierze {
  public:
    void zachowanie() { std::cout << "Kwaczę" << std::endl; }
};

class Pies : public Zwierze {
  public:
    void zachowanie() { std::cout << "Szczekam" << std::endl; }
};

void foo(Zwierze* obiekt) {
  obiekt->zachowanie();
}
```

### Metody wirtualne

Jeśli mamy wskaźnik typu klasy bazowej, wskazujący na obiekt klasy pochodnej, to jeśli wywołamy przy jego pomocy metodę zdefiniowaną w obu klasach, to wywołana zostanie implementacja klasy bazowej.

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

Aby uniknąć tego nieoczekiwanego zachowania musimy użyć słowa kluczowego `virtual` przed nazwą metody w klasie bazowej.

```c++
class A {
  public:
    virtual void foo() { std::cout << "A" << std::endl; }
};

class B : public A {
  public:
    void foo() { std::cout << "B" << std::endl; }
};

B b;
A* wsk = &b;
wsk->foo(); // wyświetli "B"
```

Jest to tak zwany mechanizm dynamic binding, który pozwala na wywołanie odpowiedniej implementacji metody w zależności od rzeczywistego typu obiektu.

Uwaga: Destruktor to też funkcja. Jeśli chcemy, aby przy usuwaniu obiektu została wywołana implementacja destruktora w klasie pochodnej, musimy użyć słowa kluczowego <code>virtual</code> przed nazwą destruktora w klasie bazowej.

### Klasy abstrakcyjne

W C++ istnieje możliwość tworzenia klas, które zawierają jedynie deklaracje metod, ale same ich nie implementują. Co więcej, mogą one definiować metody, których implementacje w klasach pochodnych jest wymagana. Takie metody zwane czysto wirtualnymi, mają specjalną składnię, mianowicie zaczynają się od słowa kluczowego <code>virtual</code>, a kończą się przyrównaniem do zera.

```c++
class A {
  public:
    virtual void foo() = 0;
};

class B : public A {
  public:
    void foo() { std::cout << "B" << std::endl; }
};

B b;
A* wsk = &b;
wsk->foo(); // wyswietli "B"
```

W powyższym przykładzie klasa A jest klasą abstrakcyjną. Istnieje tylko jeden warunek, aby klasa była uznana za klasę abstrakcyjną: musi zawierać przynajmniej jedną metodę czysto wirtualną. Co zmienia konwersja metody wirtualnej na czysto wirtualną?

1. Nie można utworzyć obiektu klasy abstrakcyjnej.
2. Klasy pochodne muszą zaimplementować metodę czysto wirtualną.

W jakim celu stosujemy klasy abstrakcyjne?

1. Tworzymy hierarchie klas, w których klasy bazowe mają wspólne cechy, jednak nie chcemy tworzyć obiektów tych klas
2. Chcemy, aby klasy pochodne implementowały pewne metody

Klasa czysto wirtualna to taki rodzaj klasy abstrakcyjnej, która zawiera tylko metody czysto wirtualne, i nie ma żadnych składowych (pól).

```c++
class A {
  public:
    virtual void foo() = 0;
    virtual void bar() = 0;
};
```
