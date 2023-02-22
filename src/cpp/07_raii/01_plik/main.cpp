#include <fstream>
#include <iostream>
#include <stdexcept>

class Plik {
public:
    Plik(const std::string& sciezka) : plik_(sciezka) {
        if (!plik_) {
            throw std::runtime_error("Nie udało się otworzyć pliku");
        }
    }

    ~Plik() {
        plik_.close();
    }

    std::ifstream& get() {
        return plik_;
    }

private:
    std::ifstream plik_;
};

int main() {
    try {
        Plik plik("example.txt"); // RAII: pobranie zasobu pliku w konstruktorze

        // Zrób coś z plikiem...
        std::string line;
        while (std::getline(plik.get(), line)) {
            std::cout << line << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Błąd: " << e.what() << '\n';
        return 1;
    }
    // RAII: automatyczne zwolnienie zasobu pliku, gdy obiekt 'plik' wychodzi poza zasięg
    return 0;
}
