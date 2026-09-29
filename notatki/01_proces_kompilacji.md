# Proces kompilacji

Programista zapisuje instrukcje w pliku źródłowym, na przykład `main.cpp`. Procesor nie wykonuje bezpośrednio takiego tekstu: potrzebuje instrukcji maszynowych przygotowanych dla konkretnej architektury. Kompilacja przekształca więc kod źródłowy w program, który system operacyjny może uruchomić.

Warto poznać ten proces, bo pomaga zrozumieć, dlaczego jedne błędy pojawiają się podczas kompilacji, inne podczas linkowania, a jeszcze inne dopiero po uruchomieniu programu. Polecenie `g++` zwykle uruchamia kilka etapów za nas, ale pod spodem nadal muszą się one odbyć.

## Od plików źródłowych do programu

Mały program może mieścić się w jednym pliku. Większy projekt dzieli się na kilka plików, aby oddzielić części programu i łatwiej nad nimi pracować. Poniższy przykład składa się z pliku z deklaracją funkcji, pliku z jej definicją oraz pliku zawierającego `main`.

Plik `powitanie.hpp` informuje inne pliki, że istnieje funkcja o nazwie `wypisz_powitanie`:

```cpp
// powitanie.hpp
void wypisz_powitanie(); // deklaracja: mówi, jak funkcję wywołać
```

Plik `powitanie.cpp` zawiera definicję, czyli właściwy kod funkcji:

```cpp
// powitanie.cpp
#include "powitanie.hpp"
#include <iostream>

void wypisz_powitanie() { // definicja: opisuje, co funkcja robi
    std::cout << "Witaj!\n";
}
```

Plik `main.cpp` korzysta z deklaracji i wywołuje funkcję:

```cpp
// main.cpp
#include "powitanie.hpp"

int main() {
    wypisz_powitanie();
}
```

Deklaracja w nagłówku pozwala kompilatorowi sprawdzić wywołanie w `main.cpp`. Sama deklaracja nie zawiera jednak instrukcji, które wypisują tekst. Ich definicja znajduje się w `powitanie.cpp`. Na końcu procesu trzeba więc połączyć wyniki przygotowane dla obu plików źródłowych.

## Etapy procesu

Dokładny podział pracy zależy od kompilatora. W typowym procesie można jednak wyróżnić preprocesowanie, analizę i kompilację kodu, przygotowanie plików obiektowych oraz linkowanie.

### 1. Preprocesowanie

Preprocesor wykonuje dyrektywy rozpoczynające się od `#`. Najczęściej spotkasz `#include`, `#define` i warunkowe dyrektywy, takie jak `#if`. Przykładowo `#include "powitanie.hpp"` sprawia, że zawartość nagłówka zostaje uwzględniona w przetwarzanym pliku źródłowym.

Na tym etapie kompilator jeszcze nie sprawdza, czy wyrażenia są poprawne. Preprocesor przygotowuje tekst, który później będzie analizowany. Szczegóły jego działania i typowe pułapki opisuje następna notatka.

Każdy plik źródłowy `.cpp` jest zwykle przetwarzany osobno. Dlatego `main.cpp` i `powitanie.cpp` przejdą własne preprocesowanie, a każdy z nich utworzy osobną jednostkę translacji.

### 2. Analiza i kompilacja kodu

Kompilator czyta przygotowany kod i sprawdza go etapami.

Najpierw dzieli tekst na tokeny, czyli rozpoznawalne elementy języka: słowa kluczowe, nazwy, liczby, operatory i znaki interpunkcyjne. W instrukcji:

```cpp
int suma = a + b;
```

tokenami są między innymi `int`, `suma`, `=`, `a`, `+`, `b` i `;`. Ten podział pozwala kompilatorowi rozpoznać kolejną warstwę: strukturę instrukcji.

Następnie sprawdza składnię, czyli to, czy tokeny są ułożone zgodnie z gramatyką języka. Brak średnika albo niedomknięty nawias powoduje błąd składni. Można to porównać do zdania złożonego ze znanych słów, ale ułożonego według niewłaściwych reguł.

Podczas tej analizy kompilator buduje wewnętrzny opis struktury programu, często nazywany drzewem składniowym. Dla `int suma = a + b;` taki opis pokazuje, że jest to deklaracja zmiennej typu `int`, której wartość początkową oblicza dodawanie `a + b`. To ważne, bo kompilator nie działa na pojedynczych słowach w oderwaniu od siebie: musi wiedzieć, które wyrażenie jest argumentem którego operatora.

Potem kompilator sprawdza znaczenie kodu w danym miejscu. Weryfikuje, czy użyte nazwy zostały zadeklarowane, czy są widoczne w tym zakresie oraz czy typy pasują do wykonywanych operacji. Na przykład przypisanie napisu do zmiennej typu `int` nie ma oczekiwanego sensu:

```cpp
int liczba = "tekst"; // błąd: napis nie jest wartością typu int
```

Poprawna składnia nie gwarantuje więc poprawnego programu. `int liczba = "tekst";` przypomina poprawnie zbudowaną instrukcję, ale jej elementy są niezgodne typami.

Po analizie kompilator może przekształcić program do wewnętrznej postaci pośredniej, czyli IR (ang. *intermediate representation*). IR ułatwia optymalizowanie kodu i przygotowanie go dla różnych procesorów. Kompilator może na przykład usunąć obliczenie, którego wynik nigdzie nie jest używany. Nie oznacza to, że dowolną zmianę w źródle można usunąć: wynik programu musi zachować wymagane działanie.

Następnie kompilator przygotowuje kod dla wybranej architektury. Często tworzy po drodze kod asemblera — tekstową reprezentację instrukcji procesora. Assembler tłumaczy taki kod na instrukcje maszynowe i zapisuje wynik w pliku obiektowym. Współczesne kompilatory mogą łączyć te kroki lub ukrywać je pod jednym poleceniem, więc plik asemblera nie zawsze jest widoczny w zwykłej pracy.

### 3. Plik obiektowy

Wynik kompilowania pojedynczego pliku źródłowego często zapisuje się jako plik obiektowy: na przykład `main.o` albo `main.obj`. Zawiera on kod maszynowy oraz informacje potrzebne linkerowi. Nie musi być jeszcze samodzielnym programem.

Wewnątrz pliku obiektowego mogą znajdować się różne sekcje. Sekcja `.text` zwykle zawiera kod maszynowy, a `.data` — zainicjalizowane dane globalne i statyczne. Sekcja `.bss` służy zwykle danym globalnym i statycznym, które mają początkową wartość zero. Plik zawiera też tablicę symboli, opisującą nazwy funkcji i danych, oraz informacje o relokacji, które podpowiadają linkerowi, jak uzupełnić adresy. To uproszczony opis: format i nazwy sekcji zależą od systemu oraz formatu pliku obiektowego.

W przykładzie `main.o` zawiera wywołanie `wypisz_powitanie`, ale jego definicja powstaje podczas kompilowania `powitanie.cpp` do `powitanie.o`. Plik obiektowy może więc zawierać odwołanie do nazwy, której definicja znajduje się gdzie indziej. Informacje o takich odwołaniach linker rozwiąże w następnym etapie.

### 4. Linkowanie

Linker łączy pliki obiektowe oraz potrzebne biblioteki. Dopasowuje odwołania do funkcji i zmiennych do ich definicji, a także ustala adresy potrzebne w gotowym programie.

W naszym przykładzie linker łączy `main.o` z `powitanie.o`. W pierwszym pliku znajduje wywołanie `wypisz_powitanie`, a w drugim — kod tej funkcji. Wynikiem może być plik wykonywalny, na przykład `program`.

Kod z biblioteki statycznej jest włączany do programu, więc zwykle nie trzeba dostarczać tej biblioteki osobno przy uruchomieniu. Biblioteka dynamiczna pozostaje osobnym plikiem; program i inne aplikacje mogą korzystać z jej wspólnej kopii, ale system musi ją znaleźć podczas uruchamiania. To, jak dokładnie działa ten mechanizm i jak nazywają się pliki bibliotek, zależy od systemu.

Gdy korzystamy z własnej biblioteki, linker musi wiedzieć, gdzie jej szukać i jak się nazywa. W narzędziach GNU opcja `-L` dodaje katalog wyszukiwania, a `-l` wskazuje bibliotekę. Na przykład `-L./lib -lmatematyka` prosi o wyszukanie biblioteki o nazwie odpowiadającej `matematyka` w katalogu `./lib`. Nazwa pliku i zasady wyszukiwania różnią się między systemami.

Na systemach uniksowych biblioteka statyczna ma zwykle rozszerzenie `.a`, a dynamiczna — `.so` lub `.dylib`; na Windows często spotyka się `.lib` i `.dll`. Po skompilowaniu `powitanie.cpp` do `powitanie.o` można utworzyć bibliotekę statyczną i połączyć z nią `main.o`:

```bash
ar rcs libpowitanie.a powitanie.o
g++ main.o -L. -lpowitanie -o program
```

W poleceniu `-lpowitanie` pomija się prefiks `lib` oraz rozszerzenie pliku. Wariant z biblioteką dynamiczną na systemie Linux może wyglądać tak:

```bash
g++ -fPIC -c powitanie.cpp -o powitanie.o
g++ -shared -o libpowitanie.so powitanie.o
g++ main.o -L. -lpowitanie -o program
```

`-fPIC` przygotowuje kod do umieszczenia w bibliotece współdzielonej, a `-shared` tworzy taką bibliotekę. Samo poprawne linkowanie nie wystarczy: podczas uruchamiania system musi jeszcze znaleźć plik `.so`. Sposób wskazywania bibliotek w czasie działania zależy od systemu i konfiguracji. Nie należy zakładać, że biblioteka dynamiczna będzie szukana w dowolnym katalogu.

## Kompilowanie z wiersza poleceń

Sterownik `g++` może wykonać wszystkie etapy i od razu zbudować program z kilku plików:

```bash
g++ -std=c++20 -Wall -Wextra -pedantic main.cpp powitanie.cpp -o program
```

`-std=c++20` wybiera standard języka, `-Wall -Wextra` włącza zestaw ostrzeżeń, a `-pedantic` prosi o zwracanie uwagi na rozszerzenia poza standardem. Ostrzeżenia nie zawsze oznaczają błąd, ale często wskazują na kod, który warto sprawdzić. `-o program` określa nazwę pliku wynikowego. Jeśli pominiemy `-o`, nazwa domyślna zależy od systemu i kompilatora.

Możemy też rozdzielić kompilowanie od linkowania. Opcja `-c` każe przygotować plik obiektowy i zakończyć pracę przed linkowaniem:

```bash
g++ -std=c++20 -Wall -Wextra -c main.cpp -o main.o
g++ -std=c++20 -Wall -Wextra -c powitanie.cpp -o powitanie.o
g++ main.o powitanie.o -o program
```

Dwa pierwsze polecenia przetwarzają pliki źródłowe osobno. Trzecie łączy gotowe pliki obiektowe. Taki podział ma znaczenie w większych projektach: zmiana jednego pliku zwykle wymaga ponownego zbudowania tylko jego części, a potem ponownego linkowania programu.

Opcje narzędzi GNU pozwalają również zatrzymać proces wcześniej: `-E` wypisuje wynik preprocesowania, `-S` przygotowuje kod asemblera, a `-c` kończy na pliku obiektowym. Te opcje przydają się, gdy chcemy zobaczyć, na którym etapie pojawia się problem; na co dzień kompilator zwykle wykonuje te etapy automatycznie.

Do pliku C używa się zwykle sterownika `gcc`, a do C++ — `g++`. To nazwy narzędzi z rodziny GCC; inne kompilatory mogą używać innych poleceń i opcji.

Analogiczny przykład dla pojedynczego pliku C wygląda tak:

```bash
gcc -std=c11 -Wall -Wextra main.c -o program_c
```

Tutaj `-std=c11` wybiera C11, a pozostałe opcje mają podobne znaczenie jak w przykładzie C++. Do wieloplikowego projektu C podaje się kilka plików `.c` albo kompiluje je osobno do plików obiektowych i łączy.

### Przydatne opcje kompilatora

Opcje pozwalają określić sposób budowania programu. Najczęściej podczas nauki przydadzą się:

- `-std=c++20` wybiera standard C++20. Można wskazać inny standard obsługiwany przez zainstalowany kompilator.
- `-Wall -Wextra` włącza wiele ostrzeżeń. Nie są to wszystkie możliwe ostrzeżenia, ale pomagają zauważyć podejrzany kod.
- `-g` dodaje informacje pomocne dla debugera, który pozwala śledzić wykonanie programu i oglądać wartości zmiennych.
- `-O2` włącza optymalizacje. Spotkasz również `-O1` i `-O3`, a `-Os` prosi o optymalizację rozmiaru. Numery nie są uniwersalną miarą jakości ani szybkości programu — dokładny zestaw zmian zależy od kompilatora. Przy szukaniu błędu początkującej osobie zwykle łatwiej pracować bez optymalizacji; optymalizacje warto włączać, gdy program działa poprawnie i pomiar wydajności wskazuje taką potrzebę.
- `-DDEBUG` definiuje makro `DEBUG`, a `-I./include` dodaje katalog wyszukiwania plików nagłówkowych.
- `-Werror` zmienia ostrzeżenia w błędy. Nie jest konieczne na początku nauki, bo ostrzeżenia zależą od kompilatora, ale nie warto ich też bezmyślnie wyłączać.

Opcje można połączyć w jednym poleceniu:

```bash
g++ -std=c++20 -Wall -Wextra -g -I./include main.cpp powitanie.cpp -o program
```

W przykładzie kompilator ma szukać nagłówków w `include`, ostrzegać o części typowych problemów i dołączyć dane dla debugera. Nie trzeba od razu pamiętać wszystkich opcji; ważne jest, by rozumieć, że wybierają one konfigurację budowania.

### Budowanie większego projektu

W małym ćwiczeniu można wpisać wszystkie pliki źródłowe w jednym poleceniu. Gdy plików jest więcej, powtarzanie tych poleceń staje się uciążliwe. Narzędzie `make` odczytuje reguły z pliku `Makefile` i uruchamia tylko te kroki, których wyniki są nieaktualne. W praktycznych projektach podobną rolę pełnią też inne systemy budowania.

`Makefile` zawiera zależności i polecenia, na przykład informację, że `program` zależy od `main.o` i `powitanie.o`, a każdy plik `.o` zależy od odpowiadającego mu pliku `.cpp`. Dzięki temu zmiana `powitanie.cpp` nie wymaga ponownego kompilowania wszystkich źródeł. Szczegóły składni Makefile są osobnym tematem; na tym etapie wystarczy wiedzieć, że automatyzuje opisane wcześniej polecenia.

Oto mały przykład dla projektu z wcześniejszej lekcji:

```make
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic
OBJS = main.o powitanie.o

.PHONY: all clean

all: program

program: $(OBJS)
	$(CXX) $(OBJS) -o program

main.o: main.cpp powitanie.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

powitanie.o: powitanie.cpp powitanie.hpp
	$(CXX) $(CXXFLAGS) -c powitanie.cpp -o powitanie.o

clean:
	rm -f $(OBJS) program
```

Reguły `main.o` i `powitanie.o` opisują, jak powstają pliki obiektowe. Zależność od `powitanie.hpp` mówi `make`, że zmianę nagłówka trzeba uwzględnić przy budowaniu obu plików. Reguła `program` linkuje obiekty, a `clean` usuwa wyniki budowania. Wcięcia przed poleceniami w Makefile muszą być znakami tabulacji. Uruchomienie `make` buduje domyślny cel `all`; `make clean` usuwa pliki wynikowe.

### Narzędzia używane obok kompilatora

Nie każde narzędzie związane z kodem uczestniczy w tworzeniu pliku wykonywalnego. `clang-format` automatycznie porządkuje odstępy i układ kodu, ale nie sprawdza, czy program działa. Na przykład `clang-format -i main.cpp` formatuje wskazany plik.

Analizator statyczny, taki jak `cppcheck`, przegląda kod i szuka części błędów bez uruchamiania programu. Może znaleźć problemy, których nie zgłosiła zwykła kompilacja, ale nie zastępuje kompilatora ani dokładnego przeglądu kodu.

Profilowanie odpowiada na inne pytanie: które fragmenty działają wolno podczas wykonania. Nie warto optymalizować na podstawie przypuszczeń. Najpierw mierzy się program narzędziem profilującym, a dopiero potem sprawdza wskazane miejsca. Opcja `-pg` w niektórych narzędziach GNU dodaje dane dla profilera `gprof`; szczegóły zależą od używanego systemu i narzędzi.

## Jak rozpoznać, na którym etapie pojawił się błąd?

Komunikat kompilatora zwykle zawiera nazwę pliku i numer wiersza, ale rodzaj problemu zależy od tego, który etap go wykrył.

- **Błąd składni lub znaczenia** pojawia się podczas analizy pliku źródłowego. Przykładem jest brak średnika albo użycie niezadeklarowanej zmiennej.
- **Błąd linkowania** pojawia się, gdy kod poprawnie się skompilował, ale linker nie znalazł definicji potrzebnej funkcji lub zmiennej. Tak będzie na przykład wtedy, gdy zapomnimy dołączyć `powitanie.o` do końcowego polecenia.
- **Błąd działania programu** występuje już po uruchomieniu. Program mógł przejść kompilowanie i linkowanie, a mimo to obliczać niewłaściwy wynik albo zakończyć pracę z błędem.

Rozróżnienie tych sytuacji zawęża poszukiwanie przyczyny: brak średnika poprawia się w kodzie źródłowym, brakujący plik dodaje do linkowania, a błędny wynik analizuje w logice programu.

## Dlaczego piszemy w C lub C++, a nie bezpośrednio w asemblerze?

Asembler opisuje instrukcje bliskie temu, co wykonuje procesor. Daje precyzyjną kontrolę, ale wymaga znajomości konkretnej architektury i dużej liczby szczegółów. Ta sama prosta operacja może wymagać innych instrukcji na różnych procesorach.

W C i C++ zapisujemy zamiar, na przykład `int wynik = a + b;`, a kompilator dobiera instrukcje dla wybranego procesora. Zwykle ułatwia to czytanie, przenoszenie i utrzymywanie programu. Kompilator może też optymalizować kod, ale nie oznacza to, że zawsze wygeneruje najlepszy możliwy kod. Asembler nadal bywa potrzebny w wąskich, niskopoziomowych zastosowaniach; nie jest jednak konieczny do nauki zwykłego programowania.

Dla intuicji, w przykładowym asemblerze x86 dodawanie może wymagać osobnych poleceń do wczytania wartości do rejestru, dodania ich i zapisania wyniku:

```asm
mov eax, [a]   ; wczytaj a do rejestru eax
add eax, [b]   ; dodaj b do wartości w eax
mov [wynik], eax ; zapisz wynik w pamięci
```

To tylko fragment w konkretnej składni, nie kompletny program. Pokazuje, że nawet proste działanie wymaga wiedzy o rejestrach, pamięci i architekturze. W C++ możemy wyrazić to samo krócej: `int wynik = a + b;`.

Ręczne pisanie asemblera nadal ma zastosowanie przy pracy blisko sprzętu, w niektórych systemach wbudowanych oraz przy analizie działania procesora. W typowych aplikacjach język wyższego poziomu jest łatwiejszy do utrzymania, a kompilator zwykle potrafi wygenerować dobry kod maszynowy. Pisanie ręcznie w asemblerze nie gwarantuje większej szybkości.

## Podsumowanie drogi programu

Kod źródłowy jest najpierw przygotowywany przez preprocesor, potem analizowany i tłumaczony na kod dla docelowej platformy. Każdy plik źródłowy może dać osobny plik obiektowy. Linker łączy te pliki i biblioteki w wynik, który system może uruchomić. W następnej notatce przyjrzymy się dokładniej pierwszemu z tych etapów: działaniu preprocesora.
