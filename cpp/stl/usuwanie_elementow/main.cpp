#include <iterator>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

template <class T>
void wypisz(T& kontener)
{
  std::cout << "{";
    for (auto it = kontener.begin(); it != kontener.end(); it++)
    {
        std::cout << *it << ", ";
    }
    std::cout << "}" << std::endl;
}

// Complexity: O(n*m)
// ALthough it seems to be quite efficient but its not. 
// Because erase function deletes the elements and shifts all the elements in right by 1.
template<typename T>
std::vector< T> usunElement1(std::vector< T> wektor,  T element) {
       for (auto itr = wektor.begin(); itr != wektor.end();)
    {
        if (*itr == 1)
        {
            itr = wektor.erase(itr);
        }
        else
        {
            itr++;
        }
    }
  return wektor;
}

// Complexity : O(n)
// metoda ogolna (dziala dla wektorow, drzew binarnych, tablic mieszajacych itd.) 
// nie usunie wszystkich elementow, jesli sa powtorzenia
template<typename T>
std::vector<T> usunElement2(std::vector<T> wektor, T element) {
  std::remove(wektor.begin(), wektor.end(), 1);
  return wektor;
}

// Complexity : O(n)
template<typename T>
std::vector<T> usunElement3(std::vector<T> wektor, T element) {
  auto itr = std::remove(wektor.begin(), wektor.end(), 1); 
  wektor.erase(itr, wektor.end());
  // wektor.shrink_to_fit(); // uwolnij pamiec, samo usuwanie nie uwalnia pamieci!
  // std::cout << wektor.capacity() << std::endl;
  return wektor;
}

int main()
{
  std::vector<int> c = {1, 4, 6, 1, 1, 1, 1, 12, 18, 16};
  wypisz(c);

  auto wynik1 = usunElement1(c, 1);
  wypisz(wynik1);
  
  auto wynik2 = usunElement2(c, 1);
  wypisz(wynik2);
  
  auto wynik3 = usunElement3(c, 1);
  wypisz(wynik3);
  
  return 0;
}
