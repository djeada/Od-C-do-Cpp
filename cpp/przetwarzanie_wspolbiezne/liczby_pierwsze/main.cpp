#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mutex>
#include <numeric>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

std::mutex vectLock;
std::vector<unsigned int> primeVect;

void FindPrimes(unsigned int start, unsigned int end) {

  // Cycle through numbers while ignoring evens
  for (unsigned int x = start; x <= end; x += 2) {

    // If a modulus is 0 we know it isn't prime
    for (unsigned int y = 2; y < x; y++) {
      if ((x % y) == 0) {
        break;
      } else if ((y + 1) == x) {
        vectLock.lock();
        primeVect.push_back(x);
        vectLock.unlock();
      }
    }
  }
}

void FindPrimesWithThreads(unsigned int start, unsigned int end,
                           unsigned int numThreads) {

  std::vector<std::thread> threadVect;

  // Divide up the calculation so each thread
  // operates on different primes
  unsigned int threadSpread = end / numThreads;
  unsigned int newEnd = start + threadSpread - 1;

  // Create prime list for each thread
  for (unsigned int x = 0; x < numThreads; x++) {
    threadVect.emplace_back(FindPrimes, start, newEnd);

    start += threadSpread;
    newEnd += threadSpread;
  }

  for (auto &t : threadVect) {
    t.join();
  }
}

int main() {
  // Get time before code starts executing
  int startTime = clock();

  FindPrimesWithThreads(1, 100000, 3);

  // Get time after execution
  int endTime = clock();

  for (auto i : primeVect)
    std::cout << i << "\n";

  // Print out the number of seconds
  std::cout << "Execution Time : "
            << (endTime - startTime) / double(CLOCKS_PER_SEC) << std::endl;

  system("pause");

  return 0;
}