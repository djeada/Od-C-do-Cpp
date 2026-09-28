#include <iostream>
#include <stdexcept>

struct Pool {
  int packet = 0;
  bool busy = false;

  void acquire() {
    std::cout << "Attempting to acquire a pool" << std::endl;
    if (busy) {
      throw std::runtime_error("buffer is currently being used!");
    }
    busy = true;
    std::cout << "Acquired pool with packet = " << packet << std::endl;
  }

  void release() {
    busy = false;
    std::cout << "Releasing the pool" << std::endl;
  }
};

struct Job {
  Pool &pool;

  Job(Pool &p, int packet) : pool(p) {
    pool.acquire();
    pool.packet = packet;
  }

  Job(const Job &) = delete;
  Job &operator=(const Job &) = delete;
  Job(Job &&) = delete;
  Job &operator=(Job &&) = delete;

  ~Job() { pool.release(); }

  void send() {
    std::cout << "Sending the packet= " << pool.packet << std::endl;
  }
};

int main() {
  Pool pool;

  try {
    Job job(pool, 100);
    throw std::runtime_error("some unexpected exception");
    job.send();
  } catch (...) {
    std::cout << "An exception has been caught" << std::endl;
  }

  Job job2(pool, 10);
  job2.send();

  return 0;
}
