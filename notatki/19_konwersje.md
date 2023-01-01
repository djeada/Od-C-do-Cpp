
## Konwersje

Zarówno w C, jak i w C++ istnieją mechanizmy umożliwiające konwersje wartości z jednego typu na inny.

### Rzutowanie

W C możemy jawnie dokonać konwersji wartości z jednego typu na inny za pomocą rzutowania. Ogólny schemat to:

       (typ) wartość;

Przykład:

       int a = 10;
       double b = (double)a;

W powyższym przykładzie wszystko działa jak należy. Nie ma problemu z konwersją z typu int na typ double. W wielu innych przypadkach taki zabieg może okazać się niebezpieczny. W szczególności, gdy bawimy się wskaźnikami na void. Czasami musimy ich użyć, jest to jedyny sposób na osiągnięcie polimorfizmu w C. Przykładowo funkcje qsort() i bsearch() pracują z wskaźnikami na void, dzięki temu możemy przekazać do nich tablice dowolnego typu. Niebezpieczeństwo pojawia się, gdy chcemy rzutować wskaźnik na void z powrotem na inny typ. Nic nie powstrzymuje nas przed konwersją na zły typ i nieoczekiwanymi rezultatami.

        void *ptr = malloc(sizeof(int)); // zaalokowanie pamięci dla typu int
        char *ptr2 = (char *)ptr;        // rzutowanie na inny typ
        *ptr2 = 'a';
        printf("%c\n", *ptr2);           // wyświetlenie znaku 'a'
        free(ptr); 


### Konwersja statyczna

Konwersja statyczna <code>static_cast</code> jest bardzo podobna do rzutowania, z tym że jej poprawność jest sprawdzana na etapie kompilacji. Jeśli konwersja nie jest możliwa, kompilator wygeneruje błąd.

        int a = 10;
        double b = static_cast<double>(a);

### Konwersja dynamiczna

Konwersje dynamiczne <code>dynamic_cast</code> są bardziej ograniczone niż konwersje statyczne, a ich poprawność jest sprawdzana na etapie wykonania. Dynamicznie możemy konwertować jedynie wskaźniki i referencje do obiektów klas polimorficznych.

Popularnym zastosowaniem dynamicznego rzutowania jest sprawdzenie, czy dany obiekt jest instancją jednej z klas pochodnych.

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


Konwersja wymuszona <code>reinterpret_cast</code> ma dość niszowe zastosowania i nie jest zalecana. Służy do konwersji typów, które nie są możliwe do wykonania za pomocą konwersji statycznej lub dynamicznej. Jej poprawność nie jest sprawdzana, a więc sami musimy wiedzieć czy konwersja jest możliwa.

    void convert(ObscureType *obscure, FamiliarType *familiar) {
        familiar = reinterpret_cast<FamiliarType *>(obscure);
    }
