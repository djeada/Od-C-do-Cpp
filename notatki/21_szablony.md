
## Szablony

Szablony umożliwiają tworzenie klas i funkcji, bez konieczności precyzowania typów argumentów i zwracanych wartości. Zamiast konkretnego typu jak char, int, czy bool, możemy użyć typu uogólnionego o dowolnej nazwie, np. T. 

### Szablon funkcji

Przykładowo możemy mieć funkcję max2(T arg1, T arg2) zwracającą największą z dwóch wartości typu T. Pod ogólnym typem T może kryć się dowolny typ, dla którego zdefiniowane jest porównanie między dwoma elementami.

    template <typename T> T max2(T arg1, T arg2) {
      return arg1 > arg2 ? arg1 : arg2;
    }

    max2(10, 20);     // 20
    max2(16.2, 3.14); // 16.2
    max2('a', 'b');   // 'b'

Kompilator jest w stanie wywnioskować typy argumentów na podstawie podanych wartości. Jeśli typy argumentów będą niezgodne, kompilator zgłosi błąd. Kompilator również zgłosi błąd jeśli operacja umieszczona w ciele funkcji nie jest zdefiniowana dla typu przekazanych przez nas argumentów.

### Szablon klasy

Podobnie jak dla funkcji, możemy mieć jedną definicję klasy i decydować o typie pól w momencie tworzenia obiektu. 

    template <typename T> class Foo {
      T x;

    public:
      Foo(T x) : x(x) {
        std::cout << "Utworzono obiekt Foo o typie pola x: " << typeid(T).name()
                  << std::endl;
      }
      T getX() { return x; }
    };
