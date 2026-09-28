#include <iostream>
#include <mutex>
#include <thread>

class Blokada {
public:
  explicit Blokada(std::mutex &mutex) : mutex_(mutex) { mutex_.lock(); }

  Blokada(const Blokada &) = delete;
  Blokada &operator=(const Blokada &) = delete;

  ~Blokada() { mutex_.unlock(); }

private:
  std::mutex &mutex_;
};

class WspoldzielonaLiczba {
public:
  explicit WspoldzielonaLiczba(int wartosc_poczatkowa)
      : wartosc_(wartosc_poczatkowa) {}

  int pobierz_wartosc() {
    Blokada blokada(mutex_);
    return wartosc_;
  }

  void inkrementuj() {
    Blokada blokada(mutex_);
    ++wartosc_;
  }

private:
  int wartosc_;
  std::mutex mutex_;
};

void inkrementuj_liczbe(WspoldzielonaLiczba &liczba) {
  for (int i = 0; i < 100000; ++i) {
    liczba.inkrementuj();
  }
}

int main() {
  WspoldzielonaLiczba liczba(0);

  std::thread watek1(inkrementuj_liczbe, std::ref(liczba));
  std::thread watek2(inkrementuj_liczbe, std::ref(liczba));

  watek1.join();
  watek2.join();

  std::cout << "Wartość: " << liczba.pobierz_wartosc() << '\n';
  return 0;
}
