#include <iostream>
#include <vector>
#include <numeric>

// Szablon klasy Para trzymający 2 obiekty tego samego typu
template <typename T>
class Para {
    T a, b;

public:
    Para(T _a, T _b) : a(_a), b(_b) {}

    T suma() const {
        return a + b;
    }
};



int main() {
    // Przykład użycia szablonu klasy Para
    Para<double> para(3.14, 2.72);
    std::cout << "Suma: " << para.suma() << std::endl;

    // Przykład użycia szablonu klasy Para
    Para<int> para2(3, 2);
    std::cout << "Suma: " << para2.suma() << std::endl;

    // Przykład użycia szablonu klasy Para
    Para<std::string> para3("Ala", "ma kota");
    std::cout << "Suma: " << para3.suma() << std::endl;

    // Przykład umieszczenia elementów szablonu w kontenerze
    std::vector<Para<int>> kontener;
    kontener.push_back(Para<int>(1, 2));
    kontener.push_back(Para<int>(3, 4));
    kontener.push_back(Para<int>(5, 6));

    // suma wszystkich elementów kontenera
    int suma = std::accumulate(kontener.begin(), kontener.end(), 0,
                               [](int a, const Para<int>& b) {
                                   return a + b.suma();
                               });
    std::cout << "Suma: " << suma << std::endl;

    return 0;
}
