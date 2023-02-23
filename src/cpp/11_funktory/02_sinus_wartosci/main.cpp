#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// definicja funktora
struct SinusFunctor {
    double operator()(double x) const {
        return std::sin(x);
    }
};

int main() {
    // stworzenie wektora losowych liczb zmiennoprzecinkowych
    std::vector<double> values {-0.5, 0.2, -0.8, 0.9, -0.3, 0.6, -1.0, 0.7};

    // stworzenie drugiego wektora tego samego rozmiaru i wypełnienie go sinusami wartości z pierwszego wektora
    std::vector<double> sinValues(values.size());
    std::transform(values.begin(), values.end(), sinValues.begin(), SinusFunctor());

    // wyświetlenie wyników
    std::cout << "Wejściowe wartości:\n";
    for (double v : values) {
        std::cout << v << ' ';
    }
    std::cout << '\n';

    std::cout << "Sinusy wartości:\n";
    for (double sv : sinValues) {
        std::cout << sv << ' ';
    }
    std::cout << '\n';

    return 0;
}
