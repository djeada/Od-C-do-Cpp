Konstrukcja 'include guard' pozwala na uniknięcie powtórzeń przy
załączaniu plików. Jeśi wielokrotnie użyjemy dyrektywy `include` wraz z
tą samą nazwą pliku, to domyślnie zostanie on wielokrotnie załączony.

    #ifndef NAZWA_PLIKU
    #define NAZWA_PLIKU

      // kod...

    #endif

Dzięki temu zabiegowi, ten plik zostanie załączony tylko raz.
Preprocesor sprawdzi czy plik został już załączony. Jeśli tak, to
zostanie pominiety.

Dyrektywa `define` pozwala na definiowanie makr oraz stałych. Makra są
wykonywane przed wykonaniem kodu.

Ogólna postać makra:

$\# define + nazwa + cialo$

Nazwy pisane są często dużymi literami, ale nie jest to wymagane.
Domyślnie, ciało makra definiowane jest w jednym wierszu, ale przy
użyciu lewego ukośnika można poszerzyć ciało makra o nowe wiersze.

     // przyklad stalej
    #define PI 3.14

    // makro zwracajace stala wartosc, wynik dzielenia PI przez 2
    #define PI_2 PI/2

    // makro zwracajace wartosc przekazanej liczby podniesionej do kwadratu
    #define KWADRAT(x) x*x

    // makro zwracajace wieksza z dwoch wartosci
    #define MAKS_2(x,y) (x>y?x:y)

    // makro zwracajace najwieksza z trzech wartosci
    #define MAKS_3(x,y,z) MAKS_2(MAKS_2(x,y),z) 

Makra, a funkcje

                 Makra                          Funkcje              
  ----------------------------------- --------------------------- -- --
       makra nie są kompilowane         funkcje są kompilowane       
        typy nie są sprawdzane            typy są sprawdzane         
   przy wywolaniu kod jest kopiowany      kod jest wykonywany        
                szybkie                 szybkie, ale wolniejsze      
     brak wsparcia dla skalowania       wsparcie dla skalowania      
    kompilator nie sprawdza błędów     kompilator sprawdza błędy     

Dyrektywa `if` pozwala na warunkowe kompilacje.

    #define FLAGA 1

    int main() {

      #if FLAGA
        // kod do wykonania, gdy flaga jest ustawiona
      #else
        // kod do wykonania, gdy flaga nie jest ustawiona
      #endif

      return 0;
    }
