#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// Utworz globalny mutex
std::mutex mutexPrzyklad;

// Mutex sprawi, ze inne watki zostaną zablokowane
// przed wykonaniem sie do czasu, az nie zostanie
// wykonany kod miedzy blokada.
void petla(int id) {
  mutexPrzyklad.lock();
  for (int i = 0; i < 1000; i++) {
    std::cout << "Watek nr: " << id << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  mutexPrzyklad.unlock();
}

int main() {
  // Odpal watki
  std::thread watekA(petla, 0);
  std::thread watekB(petla, 1);
  std::thread watekC(petla, 2);
  std::thread watekD(petla, 3);

  // Zablokuj program przed przejsciem
  // do nastepnych linii kodu do czasu
  // az watki nie zakoncza pracy
  watekA.join();
  watekB.join();
  watekC.join();
  watekD.join();

  std::cout << "KONIEC" << std::endl;

  return 0;
}
