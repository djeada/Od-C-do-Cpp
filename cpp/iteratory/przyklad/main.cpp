#include <vector>
#include <list>
#include <forward_list>
#include <iostream>

/*
Iteratory uogoglniaja prace z kontenerami.
Ten sam sposob na przechodzenie przez wszystkie kontenery.

Mimo wszystko roznice.
#1. Random Access Iterator: vector, deque, array
- Opcja porownania dwoch iteratorow
- Inkrementacja
- Dekrementacja
- Ogolnie mozna dodawac i odejmowac dowolne liczby calkowite

#2. Bidirectional Iterator: list, set/multiset, map/multimap
- Brak opcji porownywania
- Inkrementacja
- Dekrementacja
- Nie mozna dodawac i odejmowac dowolnych liczb calkowitych

#3. Forward Iterator: forward_list
- Inkrementacja
*/

int main()
{
    std::vector<int> wektor{1, 2, 3, 4, 5};
  
    std::vector<int>::iterator itr = wektor.begin();
    std::vector<int>::iterator itr1 = itr + 5;
    std::vector<int>::iterator itr2 = itr - 4;
    if (itr2 > itr1)
        std::cout << "itr2 gt itr1" << std::endl;

    //Dodaj wyswietlanie samego iteratora i *iterator
    auto x = *itr;
  
    // Pokaz co sie stanie z kontenerem jak zmienie 
    // wartosc za pomoca gwiazdki *
    *itr = 100;

    return 0;
}
