## Konwersje

Zarówno w języku C, jak i w języku C++ istnieją mechanizmy umożliwiające konwersję wartości z jednego typu na inny. Chociaż niektóre z tych mechanizmów są wspólne dla obu języków, różnice w podejściu oraz dostępne narzędzia czynią konwersję w C++ bardziej złożoną i wszechstronną.

### Rzutowanie w C

Rzutowanie w języku C pozwala jawnie konwertować wartość jednego typu na inny. Choć czasami jest to niezbędne, rzutowanie może prowadzić do nieoczekiwanych i niejednoznacznych wyników, jeśli nie jest używane ostrożnie.

#### Podstawowe rzutowanie

Ogólny schemat rzutowania wygląda następująco:

```c
(typ)wartość;
```

Przykład rzutowania zmiennej typu int na double:

```c
int a = 10;
double b = (double)a;
```

W tym przypadku rzutowanie z typu int na double jest bezpieczne i nie prowadzi do utraty danych.

#### Rzutowanie wskaźników

Kiedy pracujemy z wskaźnikami, rzutowanie może stać się bardziej skomplikowane. Wskaźnik typu void jest ogólnym wskaźnikiem, który może wskazywać obiekt dowolnego typu. Często używane jest w funkcjach biblioteki standardowej, takich jak `qsort()` i `bsearch()`, aby umożliwić przechowywanie wskaźników do dowolnych danych.

Niebezpieczeństwo pojawia się, gdy próbujemy rzutować wskaźnik na `void` z powrotem na inny, konkretny typ. Jeśli wskaźnik zostanie niepoprawnie zrzutowany, może to prowadzić do niezdefiniowanego zachowania.

Oto przykład, który ilustruje rzutowanie wskaźnika na `void`:

```c
void *ptr = malloc(sizeof(int));  // zaalokowanie pamięci dla typu int
char *ptr2 = (char *)ptr;         // rzutowanie na typ char *
*ptr2 = 'a';                      
printf("%c\n", *ptr2);            // wyświetlenie znaku 'a'
free(ptr); 
```

Chociaż powyższy kod jest technicznie poprawny, jego celem jest jedynie ilustracja. W praktyce rzutowanie wskaźników powinno być wykonywane z dużą ostrożnością. Przed przekształceniem wskaźnika na void na wskaźnik innego typu, należy upewnić się, że pierwotnie wskaźnik ten wskazywał na odpowiedni typ danych.

### Konwersja statyczna w C++

`static_cast` jest jednym z operatorów konwersji w C++ służącym do przeprowadzania konwersji między typami, których konwersja jest znana i sprawdzana w czasie kompilacji. Jest to najbardziej ogólny operator konwersji w C++.

```c++
int a = 10;
double b = static_cast<double>(a);
```

static_cast może być stosowany do konwersji między podstawowymi typami danych oraz do konwersji między wskaźnikami na klasy w ramach drzewa dziedziczenia, ale tylko w jednym kierunku (z bazowego do pochodnego lub odwrotnie).

### Konwersja dynamiczna w C++

dynamic_cast to operator konwersji, który służy do konwersji wskaźników i referencji w hierarchii dziedziczenia klas. Poprawność tej konwersji jest sprawdzana w czasie działania programu, co oznacza, że program sprawdzi w trakcie wykonania, czy rzutowanie jest właściwe.

```c++
#include <iostream>
#include <vector>

class A {
  virtual void vf() {}  // wirtualna funkcja umożliwiająca polimorfizm
};
class B : public A {};
class C : public A {};

int main() {
  std::vector<A *> v{new B, new C};

  for (auto a : v) {
    if (auto b = dynamic_cast<B *>(a)) {
      std::cout << "B" << std::endl;
    } else if (auto c = dynamic_cast<C *>(a)) {
      std::cout << "C" << std::endl;
    }
  }

  // Oczyszczanie pamięci
  for (auto a : v) {
    delete a;
  }

  return 0;
}
```

Jak widać w powyższym przykładzie, dynamic_cast pozwala na sprawdzenie, czy dany obiekt jest instancją określonej klasy pochodnej w hierarchii dziedziczenia. Warto zwrócić uwagę na obecność wirtualnej funkcji w klasie bazowej - jest ona niezbędna do umożliwienia rzutowania dynamicznego.

Używanie dynamic_cast jest związane z dodatkowymi kosztami wydajnościowymi ze względu na sprawdzanie typu w trakcie działania programu. Włącza to mechanizm RTTI (Run-Time Type Identification), który pozwala na identyfikację typu obiektu w czasie wykonania.

### Konwersja `reinterpret_cast` w C++

`reinterpret_cast` to jedno z narzędzi do wymuszania konwersji w C++. Jest to najbardziej "brutalny" sposób konwersji, pozwalający programiście na wymuszenie konwersji między dowolnymi typami. Oznacza to, że nie dokonuje ona rzeczywistej konwersji wartości, ale jedynie traktuje dane w pamięci jako inny typ.

Ogólna składnia:

```c++
typ_docelowy = reinterpret_cast<typ_docelowy>(obiekt_źródłowy);
```

Przykład:

```c++
int a = 10;
int* b = &a;
char* c = reinterpret_cast<char*>(b);
```

W powyższym kodzie wskaźnik b wskazuje na int, natomiast c po operacji `reinterpret_cast` wskazuje na te same bajty w pamięci, ale traktuje je jako char.

Użycie `reinterpret_cast` może być przydatne w niskopoziomowym programowaniu, gdy potrzebujemy bezpośredniego dostępu do surowych bajtów danych. Może być też niezbędne w przypadku interakcji z bibliotekami napisanymi w innych językach lub przy operacjach na sprzęcie.

Jednak należy pamiętać, że `reinterpret_cast` jest niebezpieczny. Łatwo można uzyskać nieprzewidywalne wyniki, jeśli dane nie są odpowiednio interpretowane. Ponadto, użycie tego operatora często wskazuje na to, że struktura programu nie jest optymalna lub że programista boryka się z problemem, który mógłby zostać rozwiązany w bardziej elegancki sposób. Dlatego zaleca się ostrożność i stosowanie reinterpret_cast tylko wtedy, gdy jest to absolutnie konieczne.
