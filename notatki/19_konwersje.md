
## Konwersje

Zarówno w języku C, jak i w języku C++ istnieją mechanizmy umożliwiające konwersje wartości z jednego typu na inny.

### Rzutowanie

W języku C możemy jawnie dokonać konwersji wartości z jednego typu na inny za pomocą rzutowania. Ogólny schemat to:

```c++
(typ) wartość;
```

Przykład:

```c++
int a = 10;
double b = (double)a;
```

W powyższym przykładzie wszystko działa jak należy. Nie ma problemu z konwersją z typu int na typ double. W wielu innych przypadkach taki zabieg może okazać się niebezpieczny. W szczególności, gdy bawimy się wskaźnikami na void. Czasami musimy ich użyć, jest to jedyny sposób na osiągnięcie polimorfizmu w języku C. Przykładowo funkcje `qsort()` i `bsearch()` pracują z wskaźnikami na void, dzięki temu możemy przekazać do nich tablice dowolnego typu. Niebezpieczeństwo pojawia się, gdy chcemy rzutować wskaźnik na void z powrotem na inny typ. Nic nie powstrzymuje nas przed konwersją na zły typ i nieoczekiwanymi rezultatami.

```c++
void *ptr = malloc(sizeof(int)); // zaalokowanie pamięci dla typu int
char *ptr2 = (char *)ptr;        // rzutowanie na inny typ
*ptr2 = 'a';
printf("%c\n", *ptr2);           // wyświetlenie znaku 'a'
free(ptr); 
```

### Konwersja statyczna

Konwersja statyczna `static_cast` jest bardzo podobna do rzutowania, z tym że jej poprawność jest sprawdzana na etapie kompilacji. Jeśli konwersja nie jest możliwa, kompilator wygeneruje błąd.

```c++
int a = 10;
double b = static_cast<double>(a);
```

### Konwersja dynamiczna

Konwersje dynamiczne `dynamic_cast` są bardziej ograniczone niż konwersje statyczne, a ich poprawność jest sprawdzana na etapie wykonania. Dynamicznie możemy konwertować jedynie wskaźniki i referencje do obiektów klas polimorficznych.

Popularnym zastosowaniem dynamicznego rzutowania jest sprawdzenie, czy dany obiekt jest instancją jednej z klas pochodnych. Przykład:

```c++
#include <iostream>
#include <vector>

class A {
  virtual void vf() {}
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
  return 0;
}
```

Rzutowanie dynamiczne jest związane z wykorzystaniem RTTI (Run-Time Type Identification) i jego użycie jest związane z dodatkowymi kosztami wydajnościowymi.

### Konwersja wymuszona

Konwersja wymuszona <code>reinterpret_cast</code> ma dość niszowe zastosowania i nie jest powszechnie zalecana. Służy do zmiany interpretacji bajtów danych bez zmiany ich wartości. Oznacza to, że po reinterpretacji dane mogą zostać odczytane jako inny typ niż oryginalnie zapisane.

Ogólny schemat to:

```c++
void convert(ObscureType *obscure, FamiliarType *familiar) {
    familiar = reinterpret_cast<FamiliarType *>(obscure);
}
```

Przykład:

```c++
int a = 10;
int* b = &a;
char* c = reinterpret_cast<char*>(b);
```
    
W powyższym przykładzie, b jest wskaźnikiem na int, a c jest wskaźnikiem na char. Po reinterpretacji, bajty przechowywane przez b są interpretowane jako bajty przechowywane przez c.

Reinterpretacja jest niebezpieczna, ponieważ może spowodować utratę danych lub błędy, jeśli konwersja nie jest poprawna. Dlatego też powinna być stosowana tylko w specjalnych przypadkach, gdy jest absolutnie konieczna.
