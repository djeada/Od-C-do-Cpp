#include <iostream>
#include <memory>
#include <stdexcept>

struct Pool {
	int packet = 0;
    bool busy = false;
    
    void acquire() {
        std::cout << "Attempting to acquired a pool " << std::endl;
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


// implement RAII
struct Job {
	Pool& pool;
    
    Job(Pool& p, int packet) : pool(p) {
        pool.acquire();
        pool.packet = packet;
    }
    
    ~Job() {
    	pool.release();
    }
    
    void send() {
        std::cout << "Sending the packet= " << pool.packet << std::endl;
    }
};

int main() {
	Pool pool;
    
    /*
    try {
	    pool.acquire();
        throw std::runtime_error("some unexpected exception");
		pool.release();
    }
	catch (...) {
        std::cout << "An exception has been caught" << std::endl;
    }
    
    pool.acquire();
	pool.release();	
    */
    try {
    	Job job = Job(pool, 100);
        throw std::runtime_error("some unexpected exception");
    	job.send();
    }
   	catch (...) {
        std::cout << "An exception has been caught" << std::endl;
    }
    
    Job job2 = Job(pool, 10);
    job2.send();

	return 0;    
}
