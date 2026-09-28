#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <vector>

std::mutex vectLock;
std::vector<unsigned int> primeVect;

bool IsPrime(unsigned int value) {
  if (value < 2) {
    return false;
  }
  if (value == 2) {
    return true;
  }
  if (value % 2 == 0) {
    return false;
  }

  unsigned int limit = static_cast<unsigned int>(std::sqrt(value));
  for (unsigned int divisor = 3; divisor <= limit; divisor += 2) {
    if (value % divisor == 0) {
      return false;
    }
  }
  return true;
}

void FindPrimes(unsigned int start, unsigned int end) {
  std::vector<unsigned int> localPrimes;
  for (unsigned int value = start; value <= end; ++value) {
    if (IsPrime(value)) {
      localPrimes.push_back(value);
    }
  }

  std::lock_guard<std::mutex> guard(vectLock);
  primeVect.insert(primeVect.end(), localPrimes.begin(), localPrimes.end());
}

void FindPrimesWithThreads(unsigned int start, unsigned int end,
                           unsigned int numThreads) {
  if (numThreads == 0) {
    throw std::invalid_argument("Liczba watkow musi byc dodatnia.");
  }
  if (start > end) {
    return;
  }

  unsigned int count = end - start + 1;
  numThreads = std::min(numThreads, count);

  unsigned int baseSize = count / numThreads;
  unsigned int remainder = count % numThreads;
  std::vector<std::thread> threads;

  unsigned int rangeStart = start;
  for (unsigned int i = 0; i < numThreads; ++i) {
    unsigned int rangeSize = baseSize + (i < remainder ? 1u : 0u);
    unsigned int rangeEnd = rangeStart + rangeSize - 1;
    threads.emplace_back(FindPrimes, rangeStart, rangeEnd);
    rangeStart = rangeEnd + 1;
  }

  for (auto &thread : threads) {
    thread.join();
  }

  std::sort(primeVect.begin(), primeVect.end());
}

int main() {
  const auto startTime = std::chrono::steady_clock::now();

  FindPrimesWithThreads(1, 100000, 3);

  const auto endTime = std::chrono::steady_clock::now();
  const std::chrono::duration<double> elapsed = endTime - startTime;

  for (auto prime : primeVect) {
    std::cout << prime << '\n';
  }

  std::cout << "Execution Time : " << elapsed.count() << " s\n";
  return 0;
}
