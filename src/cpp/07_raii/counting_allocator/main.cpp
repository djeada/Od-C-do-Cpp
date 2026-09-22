// Goal: Count vector allocations, not execution time.

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

constexpr int FRAMES = 40;
constexpr int PARTICLES = 1'000'000;

// --------------------------------------------------
// 1. Count allocations
// --------------------------------------------------

struct Stats {
    std::size_t allocations = 0;
    std::size_t deallocations = 0;
};

template<class T>
struct CountingAllocator {

    using value_type = T;

    Stats* stats;

    explicit CountingAllocator(Stats* s) noexcept
        : stats(s) {}

    template<class U>
    CountingAllocator(const CountingAllocator<U>& other) noexcept
        : stats(other.stats) {}

    T* allocate(std::size_t n) {

        T* ptr = std::allocator<T>{}.allocate(n);

        ++stats->allocations;

        return ptr;
    }

    void deallocate(T* ptr, std::size_t n) noexcept {

        ++stats->deallocations;

        std::allocator<T>{}.deallocate(ptr, n);
    }

    template<class U>
    bool operator==(const CountingAllocator<U>& other) const noexcept {
        return stats == other.stats;
    }

    template<class U>
    bool operator!=(const CountingAllocator<U>& other) const noexcept {
        return !(*this == other);
    }
};

using Particles = std::vector<int, CountingAllocator<int>>;

// --------------------------------------------------
// 2. Shared workload
// --------------------------------------------------

void fill(Particles& particles) {

    for (int i = 0; i < PARTICLES; ++i)
        particles.push_back(i);
}

void report(const char* name, const Stats& stats,
            std::uint64_t checksum) {

    std::cout
        << name
        << "\n  allocations:   " << stats.allocations
        << "\n  deallocations: " << stats.deallocations
        << "\n  checksum:      " << checksum
        << "\n\n";
}

// --------------------------------------------------
// A. New vector every frame
// --------------------------------------------------

void scenario_a() {

    Stats stats;
    std::uint64_t checksum = 0;

    for (int frame = 0; frame < FRAMES; ++frame) {

        Particles particles{CountingAllocator<int>{&stats}};

        fill(particles);

        checksum += particles[frame];
    }

    report("A: Fresh vector", stats, checksum);
}

// --------------------------------------------------
// B. Reserve every frame
// --------------------------------------------------

void scenario_b() {

    Stats stats;
    std::uint64_t checksum = 0;

    for (int frame = 0; frame < FRAMES; ++frame) {

        Particles particles{CountingAllocator<int>{&stats}};

        particles.reserve(PARTICLES);

        fill(particles);

        checksum += particles[frame];
    }

    report("B: Reserve every frame", stats, checksum);
}

// --------------------------------------------------
// C. Reserve once and reuse
// --------------------------------------------------

void scenario_c() {

    Stats stats;
    std::uint64_t checksum = 0;

    {
        Particles particles{CountingAllocator<int>{&stats}};

        particles.reserve(PARTICLES);

        for (int frame = 0; frame < FRAMES; ++frame) {

            particles.clear();

            fill(particles);

            checksum += particles[frame];
        }
    }

    report("C: Reserve once + reuse", stats, checksum);
}

int main() {

    scenario_a();
    scenario_b();
    scenario_c();
}
