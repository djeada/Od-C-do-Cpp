#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mutexPrzyklad;

void petla(int id) {
  std::lock_guard<std::mutex> blokada(mutexPrzyklad);

  for (int i = 0; i < 5; ++i) {
    std::cout << "Watek nr: " << id << ", iteracja: " << i << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

int main() {
  std::thread watekA(petla, 0);
  std::thread watekB(petla, 1);
  std::thread watekC(petla, 2);
  std::thread watekD(petla, 3);

  watekA.join();
  watekB.join();
  watekC.join();
  watekD.join();

  std::cout << "KONIEC" << std::endl;
  return 0;
}
