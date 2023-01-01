## Dziedziczenie

Dziedziczenie to mechanizm, który pozwala na tworzenie nowych klas wykorzystujących część kodu z klasy już istniejącej. Klasa pierwotna nazywana jest klasą bazową (bądź rodzicem), a klasa dziedzicząca jest klasą pochodną (bądź dzieckiem). W C++ dziedziczenie jest zdefiniowane przez zapisanie klasy dziedziczącej w nawiasach klamrowych po nazwie klasy bazowej. W naszym przykładzie, klasa <code>Prostokat</code> dziedziczy po klasie <code>Figura</code>.

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

W powyższym przykładzie <code>Prostokat</code> dziedziczy wszystkie pola i metody z klasy <code>Figura</code>. Przykładowo pole <code>nazwa</code> jest zdefiniowane w klasie <code>Figura</code>, ale posiada je również obiekty klasy <code>Prostokat</code>. Dodatkowo w klasie <code>Prostokat</code> dodaliśmy nowe pola <code>a</code> i <code>b</code>. W ten sposób klasy pochodne poszerzają funkcjonalność klas bazowych. Inną rzeczą na którą możemy zwrócić uwagę jest to, że klasa metoda <code>info()</code> w klasie <code>Prostokat</code> zmienia definicję metody <code>info()</code> z klasy bazowej, wywołując implementację bazową, a następnie dodając do niej dodatkowe informacje.

### Typy dziedziczenia

Istnieją trzy podstawowe typy dziedziczenia:

1. publiczne (<code>public</code>)
2. prywatne (<code>private</code>)
3. chronione (<code>protected</code>)

Poniższa tabela zawiera informacje o dostępności pól oraz metod klasy bazowej w klasie pochodnej ze względu na typ dziedziczenia:

| Typ Dziedziczenia | Prywatne pola i metody | Chronione pola i metody | Publiczne pola i metody |
| ---------------- | ---------------------- | ---------------------- | ---------------------- |
| publiczne | tak | tak | tak |
| chronione | nie | tak | tak (lecz ich dostępność zmienia się na chronioną) |
| prywatne | nie | tak (lecz ich dostępność zmienia się na prywatną) | tak (lecz ich dostępność zmienia się na prywatną) |


### Polimorfizm

Polimorfizm to mechanizm umożliwiający nadawcy wysłania tej samej wiadomości do odbiorców różnych typów, bez wiedzy o konkretnym typie danego odbiorcy. Każdy odbiorca może odpowiedzieć na wiadomość we własny sposób. Odpowiedzi mogą, ale nie muszą się pokrywać. Polimorfizm jest często definiowany w kontekście dziedziczenia. Mamy klasę bazową zawierającą definicję pewnej metody oraz klasy pochodne, każda z tych klas może mieć swoją własną implementację tej metody. Załóżmy teraz, że mamy kolekcję obiektów klasy bazowej, część z nich jest obiektami klas pochodnych. Wywołując tą samą metodę na każdym elemencie kolekcji, otrzymamy różne rezultaty w zależności od dokładnego typu obiektu.

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

    std::vector<A*> obiekty { new A, new B, new C };

    for (auto obiekt : obiekty)
      obiekt->foo();

Ważnym problemem rozwiązanym przez polimorfizm jest zbędne rozgałęzienie kodu w celu sprawdzenia typu obiektu. Weźmy pod uwagę poniższy przykład:

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

Dla dwóch klas takie rozgałęzienie wygląda niegroźnie. Co jednak jeśli zdecydujemy dodać nowe klasy? Co więcej w większym programie może się okazać, że podobne rozgałęzienia pojawiają się w wielu miejscach. Prostym rozwiązaniem jest zastosowanie polimorfizmu.

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

### Metody wirtualne

Jeśli mamy wskaźnik typu klasy bazowej, wskazujący na obiekt klasy pochodnej, to jeśli wywołamy przy jego pomocy metodę zdefiniowaną w obu klasach, to wywołana zostanie implementacja klasy bazowej.

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


Aby uniknąć tego nieoczekiwanego zachowania musimy użyć słowa kluczowego <code>virtual</code> przed nazwą metody w klasie bazowej.

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

Uwaga: Destruktor to też funkcja. Jeśli chcemy, aby przy usuwaniu obiektu została wywołana implementacja destruktora w klasie pochodnej, musimy użyć słowa kluczowego <code>virtual</code> przed nazwą destruktora w klasie bazowej.

### Klasy abstrakcyjne

W C++ istnieje możliwość tworzenia klas, które zawierają jedynie deklaracje metod, ale same ich nie implementują. Co więcej, mogą one definiować metody, których implementacje w klasach pochodnych jest wymagana. Takie metody zwane czysto wirtualnymi, mają specjalną składnię, mianowicie zaczynają się od słowa kluczowego <code>virtual</code>, a kończą się przyrównaniem do zera.

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

W powyższym przykładzie klasa A jest klasą abstrakcyjną. Istnieje tylko jeden warunek, aby klasa była uznana za klasę abstrakcyjną: musi zawierać przynajmniej jedną metodę czysto wirtualną. Co zmienia konwersja metody wirtualnej na czysto wirtualną?

1. Nie można utworzyć obiektu klasy abstrakcyjnej.
2. Klasy pochodne muszą zaimplementować metodę czysto wirtualną.

Klasy czysto abstrakcyjne to klasy abstrakcyjne składające się wyłącznie z metod czysto wirtualnych i nieposiadające żadnych pól.
