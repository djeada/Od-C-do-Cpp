## Proces kompilacji

Kompilator to program, który na wejściu otrzymuje kod źródłowy innego programu i generuje pliki obiektowe zawierające kod assemblera.

1. Najpierw na scenę wkracza Pan Preprocesor. Zadań tego Pana jest wiele, wśród nich wymienić można:

   - Włączenie zawartości załączonych plików nagłówkowych do kodu źródłowego. Na przykład, jeśli w jednym z kompilowanych plików umieściliśmy <code>#include "plik.h"</code>, to treść tego pliku zostanie przekopiowana do naszego kodu źródłowego.
   - Generacja kodu makr.
   - Zamiana stałych zdefiniowanych za pomocą #define na ich wartości. Kod źródłowy przygotowany przez Pana Preprocesora jest następnie poddany analizie składni, w której skład wchodzą:
   - Analiza leksykalna (np. odrzucenie zakomentowanych fragmentów kodu).
   - Analiza składni (np. czy nie próbujemy skorzystać ze zmiennej, zanim została stworzona).
   - Analiza semantyczna (np. weryfikacja typów i poprawność instrukcji).

2. Tworzenie plików obiektowych z rozszerzeniem .o i zawierających kod źródłowy przetłumaczony na rozkazy w assemblerze.
3. Przygotowany w ten sposób kod obiektowy jest łączony z kodem obiektowym funkcji z zewnętrznych bibliotek w wykonywalny program (pod Windowsem będzie mieć rozszerzenie .exe).

Dlaczego nie piszemy bezpośrednio w assemblerze?

1. Istnieje wiele dialektów języka assembler. Każdy procesor ma własny zestaw instrukcji, który nie zawsze pokrywa się z instrukcjami innych typów procesorów. Kompilator pozwala nam ten sam kod kompilować do wielu typów procesorów.
2. Kompilatory to szczwane bestie. Twój kod jest nie tylko tłumaczony na assembler, ale również optymalizowany pod względem wydajności.
3. Wysokopoziomowe języki programowania bogate są w wiele konstrukcji ułatwiających pracę nad złożonym kodem. Przykładem mogą być struktury danych, takie jak stosy czy kolejki. Assembler to tylko kilka instrukcji, typu zwiększ, skocz do innej linii, porównaj.
Pan Preprocesor przetwarza kod źródłowy.

Zadania Pana Preprocesora definiowane są za pomocą specjalnych zaklęć, zwanych dyrektywami, rozpoczynanych od kratki <i>#</i>.
Dyrektywy mogą być umieszczane w dowolnym miejscu programu, ale przyjęło się, że najczęściej gromadzi się je u góry pliku źródłowego.

Najczęściej spotykaną dyrektywą jest załączenie biblioteki.

Kompilacja programu napisanego w C, przy użyciu gcc:

	gcc -std=c99 main.c -o exe

Kompilacja programu napisanego w C++, przy użyciu g++:

    g++ -pedantic -std=c++98 main.cpp -o exe
    g++-10 -Wall -Wextra -std=c++20 main.cpp -o exe

Poprawa formatowania, przy użyciu clang-format:

    find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;