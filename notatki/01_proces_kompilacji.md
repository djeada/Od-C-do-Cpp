## Proces kompilacji

Kompilator to program, który na wejściu otrzymuje kod źródłowy innego programu i generuje pliki obiektowe zawierające kod assemblera. Proces kompilacji składa się z kilku etapów:

1. Etap preprocesowania - na tym etapie na scenie pojawia się Pan Preprocesor. Jego zadaniem jest przetworzenie kodu źródłowego przed jego analizą składniową. Jego zadania obejmują m.in:
  * Włączenie zawartości załączonych plików nagłówkowych do kodu źródłowego. Na przykład, jeśli w jednym z kompilowanych plików umieściliśmy <code>#include "plik.h"</code>, to treść tego pliku zostanie przekopiowana do naszego kodu źródłowego.
  * Generacja kodu makr. Makra to specjalne instrukcje, które pozwalają na zdefiniowanie stałych czy zmiennych, które będą zamieniane na ich wartości podczas preprocesowania.
  * Odrzucenie zakomentowanych fragmentów kodu.

2. Analiza składni - po przetworzeniu kodu przez preprocesor, następuje analiza składni kodu źródłowego. Składa się ona z trzech etapów:
  * Analiza leksykalna - na tym etapie kod źródłowy jest dzielony na leksemy (tokeny), czyli najmniejsze logiczne jednostki kodu.
  * Analiza składniowa - na tym etapie sprawdzane jest, czy kod jest zgodny z gramatyką języka programowania. Sprawdzane są m.in. poprawność składni, czy nie próbujemy skorzystać ze zmiennej, zanim została stworzona.
  * Analiza semantyczna - na tym etapie weryfikowana jest poprawność typów i instrukcji, które zostały zastosowane w kodzie.

3. Tworzenie plików obiektowych - po przejściu przez etap analizy składni, kompilator generuje pliki obiektowe z rozszerzeniem .o, które zawierają kod źródłowy przetłumaczony na rozkazy w assemblerze. Pliki te zawierają już przetworzony kod, ale nie są jeszcze gotowe do uruchomienia.

4. Linkowanie - na tym etapie pliki obiektowe są łączone z kodem obiektowym funkcji z zewnętrznych bibliotek, tworząc wykonywalny program. Proces ten polega na połączeniu wszystkich plików obiektowych oraz bibliotek, które zostały użyte w projekcie, w jeden plik wykonywalny.

### Dlaczego nie piszemy bezpośrednio w assemblerze?

* Istnieje wiele dialektów języka assembler. Każdy procesor ma własny zestaw instrukcji, który nie zawsze pokrywa się z instrukcjami innych typów procesorów. Kompilator pozwala na tłumaczenie tego samego kodu na różne typy procesorów.
* Kompilatory umożliwiają automatyczną optymalizację kodu pod kątem wydajności. Dzięki temu, tworzony program jest szybszy i bardziej wydajny.
* Wysokopoziomowe języki programowania, takie jak C++ czy Java, oferują bogaty zestaw konstrukcji i narzędzi, które ułatwiają pracę nad złożonym kodem. Assembler, jako język niższego poziomu, nie posiada takiej funkcjonalności.

### Dyrektywy preprocesora
Zadania Pana Preprocesora definiowane są za pomocą specjalnych zaklęć, zwanych dyrektywami, rozpoczynanych od znaku <i>#</i>. Dyrektywy te pozwalają na modyfikację kodu źródłowego przed jego kompilacją. Przykłady takich dyrektyw to <code>#include</code> (załączanie bibliotek), <code>#define</code> (definiowanie makr) czy <code>#ifdef</code> (warunkowe kompilowanie fragmentów kodu).

Dyrektywy mogą być umieszczane w dowolnym miejscu programu, jednak przyjęło się, że najczęściej gromadzi się je u góry pliku źródłowego, aby były one łatwiejsze do zlokalizowania.

### Kompilacja z wiersza poleceń
Kompilacja programu napisanego w języku C przy użyciu kompilatora gcc może wyglądać następująco:

```
gcc -std=c99 main.c -o exe
```

Natomiast kompilacja programu napisanego w języku C++ przy użyciu kompilatora g++ może wyglądać następująco:

```
g++ -pedantic -std=c++98 main.cpp -o exe
```

```
g++-10 -Wall -Wextra -std=c++20 main.cpp -o exe
```

Dodatkowo, możemy użyć narzędzia clang-format do poprawy formatowania naszego kodu. Przykładowo, poniższe polecenie znajduje wszystkie pliki z rozszerzeniem .c, .cpp, .h, .hpp, .cu i wykonuje na nich formatowanie zgodnie z ustalonym stylem:

```
find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;
```

To tylko przykłady, w zależności od potrzeb można użyć różnych opcji kompilatorów, narzędzi czy bibliotek, które pozwolą na uzyskanie pożądanego rezultatu.
