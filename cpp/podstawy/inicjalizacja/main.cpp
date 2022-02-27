#include <vector>
#include <iostream>

class Pies
{
int wiek;
    std::string imie;
public:
    Pies(int wiek, std::string imie):
      wiek(wiek),
imie(imie)
    {
        std::cout << "wiek : " << wiek << "imie : " << imie << std::endl;
    };
};
int main()
{
    std::vector<int> v1;
    v1.push_back(3);
    v1.push_back(2);
    v1.push_back(4);
    v1.push_back(5);

    std::vector<int> v2= {3, 4, 1, 9};
    std::vector<int> v3{0, 2, 3, 4};

    Pies p2 = Pies(5, "Henry");
    Pies p4(5, "Henry");
    Pies p1 = {5, "Henry"};
    Pies p3{5, "Henry"};
  
    return 0;
}
